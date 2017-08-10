////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.6/media_player.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用SDL和FFmpeg实现简易多媒体播放器
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include <signal.h>

#define LCD_WIDTH  800
#define LCD_HEIGHT 480

#define BLOCK   1
#define UNBLOCK 0

void show_on_screen(SDL_Overlay *bmp, AVFrame *frame,
					AVCodecContext *videoCodecCtx, struct SwsContext *swsCtx)
{
	SDL_LockYUVOverlay(bmp);

	AVPicture pict;
	SDL_Rect rect;

	pict.data[0] = bmp->pixels[0];
	pict.data[1] = bmp->pixels[2];
	pict.data[2] = bmp->pixels[1];

	pict.linesize[0] = bmp->pitches[0];
	pict.linesize[1] = bmp->pitches[2];
	pict.linesize[2] = bmp->pitches[1];

	sws_scale(swsCtx, (uint8_t const * const *)frame->data,
			  frame->linesize, 0, videoCodecCtx->height, pict.data,
			  pict.linesize);

	printf("frame->linesize[0]: %d\n", frame->linesize[0]);
	printf("frame->linesize[1]: %d\n", frame->linesize[1]);
	printf("frame->linesize[2]: %d\n", frame->linesize[2]);

	printf("videoCodecCtx->height: %d\n", videoCodecCtx->height);

	SDL_UnlockYUVOverlay(bmp);

	rect.x = 0;
	rect.y = 0;
	rect.w = videoCodecCtx->width;
	rect.h = videoCodecCtx->height;

	SDL_DisplayYUVOverlay(bmp, &rect);
}


// ====================== 音频处理流程 ==================== //

struct PacketQueue
{
	AVPacketList *front, *rear;
	int nb_packets;
	int size;
	SDL_mutex *mutex;
	SDL_cond  *cond;
};

struct PacketQueue *audio_queue = NULL;
bool quit = false;

bool queue_is_empty(struct PacketQueue *audio_queue)
{
	return audio_queue->nb_packets == 0;
}

int packet_queue_put(AVPacket *packet)
{
	// printf("[%d]: %s\n", __LINE__, __FUNCTION__);

	AVPacketList *new = av_malloc(sizeof(AVPacketList));
	new->pkt = *packet;
	new->next = NULL;

	SDL_LockMutex(audio_queue->mutex);

	if(queue_is_empty(audio_queue))
	{
		audio_queue->front = audio_queue->rear = new;
	}
	else
	{
		audio_queue->rear->next = new;
		audio_queue->rear = new;
	}

	audio_queue->nb_packets++;
	audio_queue->size += new->pkt.size;

	SDL_CondSignal(audio_queue->cond);

	SDL_UnlockMutex(audio_queue->mutex);

	return 0;
}

int packet_queue_get(AVPacket *pkt, int block)
{
	// printf("[%d]: %s\n", __LINE__, __FUNCTION__);

	AVPacketList *pktList;
	int ret;

	SDL_LockMutex(audio_queue->mutex);

	while(1)
	{
		if(quit)
		{
			ret = -1;
			break;
		}

		// 如果当前队列为空，则根据block选择阻塞等待或者无功而返
		while(queue_is_empty(audio_queue))
		{
			if(block == 1)
			{
				SDL_CondWait(audio_queue->cond, audio_queue->mutex);
			}
			else
			{
				ret = 0;
				break;
			}
		}

		// 取出队列中的队头元素，放置到pkt中
		pktList = audio_queue->front;
		audio_queue->front = pktList->next;
		pktList->next = NULL;

		audio_queue->nb_packets--;
		audio_queue->size = pktList->pkt.size;
		*pkt = pktList->pkt;

		av_free(pktList);
		ret = 1;
		break;	
	}

	SDL_UnlockMutex(audio_queue->mutex);
	return ret;
}

int audio_decode_frame(AVCodecContext *audioCodecCtx, uint8_t *audio_buf, int audio_buf_size)
{
	static AVPacket pkt;
	static AVFrame frame;

	static uint8_t *audio_pkt_data = NULL;
	static int audio_pkt_size = 0;

	int raw_data_used, data_decoded = 0;

	while(1)
	{
		while(audio_pkt_size > 0)
		{
			int got_frame = 0;

			// 将pkt中的包根据audioCodecCtx信息解码，放到frame中
			raw_data_used = avcodec_decode_audio4(audioCodecCtx, &frame, &got_frame, &pkt);
			if(raw_data_used < 0)
			{
				// 当前包解码出错，放弃并取下一个包
				audio_pkt_size = 0;
				break;
			}

			audio_pkt_data += raw_data_used;
			audio_pkt_size -= raw_data_used;

			if(got_frame)
			{
				// 计算解码后得到的字节数data_decoded，拷贝这么多个字节到audio_buf中
				data_decoded = av_samples_get_buffer_size(NULL, audioCodecCtx->channels,
													  frame.nb_samples, audioCodecCtx->sample_fmt, 1);
				memcpy(audio_buf, frame.data[0], data_decoded);
			}
			if(data_decoded <= 0)
			{
				// 没有解码到数据，解码下一帧
				printf("[%d]: %s\n", __LINE__, __FUNCTION__);
				continue;
			}

			// 成功解码到data_decoded个字节的数据
			return data_decoded;
		}

		if(pkt.data != NULL)
		{
			av_free_packet(&pkt);
		}

		if(quit)
		{
			return -1;
		}

		// 从队列中取一个包，放到pkt中，若当前无包则阻塞等待
		packet_queue_get(&pkt, BLOCK);
		audio_pkt_data = pkt.data;
		audio_pkt_size = pkt.size;
	}
}

void audio_callback(void *userdata, uint8_t *stream, int len)
{
	AVCodecContext *audioCodecCtx = (AVCodecContext *)userdata;
	
	int len1, audio_size;

	static uint8_t  audio_buf[192000 * 3 / 2];
	static uint32_t audio_buf_size = 0;
	static uint32_t audio_buf_index = 0;

	while(len > 0)
	{
		if(audio_buf_index >= audio_buf_size)
		{
			audio_size = audio_decode_frame(audioCodecCtx, audio_buf, audio_buf_size);
			if(audio_size < 0)
			{
				audio_buf_size = 1024;
				bzero(audio_buf, audio_buf_size);
			}
			else
			{
				audio_buf_size = audio_size;
			}

			audio_buf_index = 0;
		}

	    len1 = audio_buf_size - audio_buf_index;

	    if(len1 > len)
	    {
	    	len1 = len;
	    }
	    memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);
	    len -= len1;
	    stream += len1;
	    audio_buf_index += len1;
	}
}

void packet_queue_init(struct PacketQueue *audio_queue)
{
	bzero(audio_queue, sizeof(*audio_queue));

	audio_queue->front = audio_queue->rear = NULL;
	audio_queue->nb_packets = audio_queue->size = 0;

	audio_queue->mutex = SDL_CreateMutex();
	audio_queue->cond  = SDL_CreateCond();
}

void *turn_on_audio(void *param)
{
	struct args
	{
		AVFormatContext *fc;
		int as;
	};

	AVFormatContext *fmtCtx = ((struct args *)param) -> fc;
	int audioStream = ((struct args *)param) -> as;

	// 定义音频处理相关结构体
	AVCodecContext  *audioCodecCtx = NULL;
	AVCodec         *audioCodec = NULL;
	AVDictionary    *audioDict = NULL;

	SDL_AudioSpec   *wanted_spec = malloc(sizeof(SDL_AudioSpec));
	SDL_AudioSpec   *spec        = malloc(sizeof(SDL_AudioSpec));


	// 获取音频解码信息并存储到SDL中的wanted_spec备用
	audioCodecCtx = fmtCtx->streams[audioStream]->codec;

	wanted_spec->freq = audioCodecCtx->sample_rate;
	wanted_spec->format = AUDIO_S16SYS;
	wanted_spec->channels = audioCodecCtx->channels;
	wanted_spec->silence = 0;
	wanted_spec->samples = 1024;
	wanted_spec->callback = audio_callback; // 当有音频数据时自动回调该函数
	wanted_spec->userdata = audioCodecCtx;

	// 使用期望的wanted_spec属性打开音频设备，实际属性存储到spec中
	bzero(spec, sizeof(*spec));
	SDL_OpenAudio(wanted_spec, spec);

	// 打开音频解码器
	audioCodec = avcodec_find_decoder(audioCodecCtx->codec_id);
	avcodec_open2(audioCodecCtx, audioCodec, &audioDict);

	// 初始化音频处理队列，并置静音等待音频数据开始播放
	audio_queue = malloc(sizeof(*audio_queue));
	packet_queue_init(audio_queue);
	SDL_PauseAudio(0);
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <video>\n", argv[0]);
		exit(1);
	}

	// 音视频格式信息结构上下文
	AVFormatContext *fmtCtx = NULL;

	// 定义视频处理相关结构体
	AVCodecContext  *videoCodecCtx = NULL;
	AVCodec         *videoCodec = NULL;

	AVFrame         *frame = NULL;
	AVPacket        *packet = malloc(sizeof(AVPacket));

	struct SwsContext *swsCtx = NULL;
	AVDictionary      *videoDict = NULL;

	// 注册所有的格式和编解码器
	av_register_all();

	// 打开多媒体文件，并获取其格式属性，后面两个NULL代表不指定格式
	avformat_open_input(&fmtCtx, argv[1], NULL, NULL);

	// 获取流信息
	avformat_find_stream_info(fmtCtx, NULL);

	// 查找第一个视频流和音频流
	int videoStream = -1;
	int audioStream = -1;

	int i;
	for(i=0; i<fmtCtx->nb_streams; i++)
	{
		if(fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO
			 && videoStream < 0)
		{
			videoStream = i;
		}

		if(fmtCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO
			 && audioStream <0)
		{
			audioStream = i;
		}
	}
	if(videoStream < 0 || audioStream < 0)
	{
		printf("Can't find audio stream.\n");
		exit(1);
	}

	printf("videoStream: %d\n", videoStream);
	printf("audioStream: %d\n", audioStream);

	// ====================== 音频处理流程 ==================== //
	pthread_t tid;
	struct
	{
		AVFormatContext *fc;
		int as;
	}args = {fmtCtx, audioStream};
	pthread_create(&tid, NULL, turn_on_audio, (void *)&args);


	// ====================== 视频处理流程 ==================== //
	// 获取视频的解码相关信息，并取得视频解码器
	videoCodecCtx = fmtCtx->streams[videoStream]->codec;
	videoCodec    = avcodec_find_decoder(videoCodecCtx->codec_id);
	printf("code id: %d\n", videoCodecCtx->codec_id);
	if(videoCodec == NULL)
	{
		printf("Can't find video decoder:%s\n", strerror(errno));
		exit(1);
	}

	// 打开视频解码器
	avcodec_open2(videoCodecCtx, videoCodec, &videoDict);

	// 分配帧缓冲，并设置图像转换信息
	frame = av_frame_alloc();
	swsCtx = sws_getContext(videoCodecCtx->width, videoCodecCtx->height, videoCodecCtx->pix_fmt,
							videoCodecCtx->width, videoCodecCtx->height, PIX_FMT_YUV420P,
							SWS_BILINEAR, NULL, NULL, NULL);


	// *********** 设置SDL，为显示视频做准备 **************** //
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

	SDL_Surface *screen = NULL;
	SDL_Overlay *bmp    = NULL;
	screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT, 0, 0);
	bmp    = SDL_CreateYUVOverlay(videoCodecCtx->width, 
		                          videoCodecCtx->height,
								  SDL_YV12_OVERLAY, screen);
	// ****************************************************** //

	int finished = 0;
	while(av_read_frame(fmtCtx, packet) >= 0)
	{
		if(packet->stream_index == videoStream)
		{
			// 将数据从packet中解码出来，放入frame中
			avcodec_decode_video2(videoCodecCtx, frame, &finished, packet);
			if(finished)
			{
				printf("[%d]%u\n", __LINE__, frame->pts);
				printf("[%d]%u\n", __LINE__, frame->key_frame);

				show_on_screen(bmp, frame, videoCodecCtx, swsCtx);
				av_free_packet(packet);
			}
		}
		else if(packet->stream_index == audioStream)
		{
			packet_queue_put(packet);
		}
		else
		{
			av_free_packet(packet);
		}
	}

	av_free(frame);
	avcodec_close(videoCodecCtx);
	avformat_close_input(&fmtCtx);

	SDL_Quit();
	exit(0);

	return 0;
}