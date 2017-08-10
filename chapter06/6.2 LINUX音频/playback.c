//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.2/playback.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用alsa库API实现播放wav格式音频文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4audio.h"

#if __BYTE_ORDER == __LITTLE_ENDIAN

	#define RIFF ('F'<<24 | 'F'<<16 | 'I'<<8 | 'R'<<0)
	#define WAVE ('E'<<24 | 'V'<<16 | 'A'<<8 | 'W'<<0)
	#define FMT  (' '<<24 | 't'<<16 | 'm'<<8 | 'f'<<0)
	#define DATA ('a'<<24 | 't'<<16 | 'a'<<8 | 'd'<<0)

	#define LE_SHORT(val) (val) 
	#define LE_INT(val)   (val) 

#elif __BYTE_ORDER == __BIG_ENDIAN

	#define RIFF ('R'<<24 | 'I'<<16 | 'F'<<8 | 'F'<<0)
	#define WAVE ('W'<<24 | 'A'<<16 | 'V'<<8 | 'E'<<0)
	#define FMT  ('f'<<24 | 'm'<<16 | 't'<<8 | ' '<<0)
	#define DATA ('d'<<24 | 'a'<<16 | 't'<<8 | 'a'<<0)

	#define LE_SHORT(val) bswap_16(val) 
	#define LE_INT(val)   bswap_32(val) 

#endif  


int get_bits_per_sample(wav_format *wav, snd_pcm_format_t *snd_format)  
{     
    if (LE_SHORT(wav->format.fmt) != WAV_FMT_PCM)
        return -1;
      
    switch (LE_SHORT(wav->format.bits_per_sample))
    {  
    case 16:  
        *snd_format = SND_PCM_FORMAT_S16_LE;  
        break;  
    case 8:  
        *snd_format = SND_PCM_FORMAT_U8;  
        break;  
    default:  
        *snd_format = SND_PCM_FORMAT_UNKNOWN;  
        break;  
    }  
  
    return 0;  
}  


ssize_t write_pcm_to_device(pcm_container *pcm, size_t wcount)  
{  
    ssize_t r;  
    ssize_t result = 0;  
    uint8_t *data = pcm->period_buf;  
  
    if(wcount < pcm->frames_per_period)
    {  
        snd_pcm_format_set_silence(pcm->format,   
                    data + wcount * pcm->bytes_per_frame,   
                    (pcm->frames_per_period - wcount) * pcm->channels);  

        wcount = pcm->frames_per_period;  
    }  

    while(wcount > 0)
    {
        r = snd_pcm_writei(pcm->handle, data, wcount);  

        if(r == -EAGAIN || (r >= 0 && (size_t)r < wcount))
        {  
            snd_pcm_wait(pcm->handle, 1000);  
        }
        else if(r == -EPIPE)
        {  
            snd_pcm_prepare(pcm->handle);  
            fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");  
        }
        else if(r == -ESTRPIPE)
        {              
            fprintf(stderr, "<<<<<<<<<<<<<<< Need suspend >>>>>>>>>>>>>>>\n");          
        }
        else if(r < 0)
        {  
            fprintf(stderr, "Error snd_pcm_writei: [%s]\n", snd_strerror(r));  
            exit(-1);
        }  
        if(r > 0)
        {  
            result += r;  
            wcount -= r;  
            data += r * pcm->bytes_per_frame;  
        }  
    }  
    return result;  
}  
 

int set_params(pcm_container *pcm, wav_format *wav)  
{  
    snd_pcm_hw_params_t *hwparams;  
    uint32_t buffer_time, period_time;  
  
    // A) 分配参数空间
    //    以PCM设备能支持的所有配置范围初始化该参数空间
    snd_pcm_hw_params_alloca(&hwparams);  
    snd_pcm_hw_params_any(pcm->handle, hwparams);
  
    // B) 设置访问方式为“帧连续交错方式”
    snd_pcm_hw_params_set_access(pcm->handle, hwparams,
                        SND_PCM_ACCESS_RW_INTERLEAVED);
  
    // C) 根据WAV文件的格式信息，设置量化参数
    snd_pcm_format_t format;  
    get_bits_per_sample(wav, &format);
    snd_pcm_hw_params_set_format(pcm->handle, hwparams,
                                               format);
    pcm->format = format;  
  
    // D) 根据WAV文件的格式信息，设置声道数
    snd_pcm_hw_params_set_channels(pcm->handle, hwparams,
                         LE_SHORT(wav->format.channels));
    pcm->channels = LE_SHORT(wav->format.channels);  
  
    // E) 根据WAV文件的格式信息，设置采样频率
    //    如果声卡不支持WAV文件的采样频率，则
    //    选择一个最接近的频率
    uint32_t exact_rate = LE_INT(wav->format.sample_rate);
    snd_pcm_hw_params_set_rate_near(pcm->handle,
                                hwparams, &exact_rate, 0);
  
    // F) 设置buffer大小为声卡支持的最大值
    //    并将处理周期设置为buffer的1/4的大小
    snd_pcm_hw_params_get_buffer_size_max(hwparams,
                                 &pcm->frames_per_buffer);

    snd_pcm_hw_params_set_buffer_size_near(pcm->handle,
                       hwparams, &pcm->frames_per_buffer);

    pcm->frames_per_period = pcm->frames_per_buffer / 4;
    snd_pcm_hw_params_set_period_size(pcm->handle,
                    hwparams, pcm->frames_per_period, 0);
    snd_pcm_hw_params_get_period_size(hwparams,
                             &pcm->frames_per_period, 0);

    // G) 将所设置的参数安装到PCM设备中
    snd_pcm_hw_params(pcm->handle, hwparams);
  
    // H) 由所设置的buffer时间和周期
    //     分配相应的大小缓冲区
    pcm->bits_per_sample =
                  snd_pcm_format_physical_width(format);
    pcm->bytes_per_frame = pcm->bits_per_sample/8 *
                         LE_SHORT(wav->format.channels);
    pcm->period_buf =
              (uint8_t *)malloc(pcm->frames_per_period *
                                  pcm->bytes_per_frame);
  
    return 0;  
}  

int check_wav_format(wav_format *wav)  
{  
    if (wav->head.id!= RIFF ||  
        wav->head.format!= WAVE ||  
        wav->format.fmt_id!= FMT ||  
        wav->format.fmt_size != LE_INT(16) ||  
        (wav->format.channels != LE_SHORT(1) &&
            wav->format.channels != LE_SHORT(2)) ||  
        wav->data.data_id!= DATA)
    {  
        fprintf(stderr, "non standard wav file.\n");  
        return -1;  
    }  
  
    return 0;  
}  
  

int get_wav_header_info(int fd, wav_format *wav)  
{  
    int n1 = read(fd, &wav->head, sizeof(wav->head)); 
    int n2 = read(fd, &wav->format, sizeof(wav->format));
    int n3 = read(fd, &wav->data,   sizeof(wav->data));
  
    if(n1 != sizeof(wav->head) ||
       n2 != sizeof(wav->format) ||
       n3 != sizeof(wav->data))
    {
        fprintf(stderr, "get_wav_header_info() failed\n");
        return -1;
    }
  
    // if(check_wav_format(wav) < 0)
    //     return -1;
  
    return 0;
}


ssize_t read_pcm_from_wav(int fd, void *buf, size_t count)  
{  
    ssize_t result = 0, res;  
  
    while(count > 0)
    {  
        if ((res = read(fd, buf, count)) == 0)  
            break;  
        if (res < 0)  
            return result > 0 ? result : res;  
        count -= res;  
        result += res;  
        buf = (char *)buf + res;  
    }  
    return result;  
}  
  
  
void play_wav(pcm_container *pcm, wav_format *wav, int fd)  
{  
    int load, ret;  
    off64_t written = 0;  
    off64_t c;  
    off64_t total_bytes = LE_INT(wav->data.data_size);  

    uint32_t period_bytes =
                pcm->frames_per_period * pcm->bytes_per_frame;
  
    load = 0;  
    while (written < total_bytes)
    {
        // 一次循环地读取一个完整的周期数据
        do
        {  
            c = total_bytes - written;
            if (c > period_bytes)
                c = period_bytes;
            c -= load;
  
            if (c == 0)
                break;
            ret = read_pcm_from_wav(fd,
                                pcm->period_buf + load, c);

            if(ret < 0)
            {
                fprintf(stderr, "read() failed.\n");  
                exit(-1);  
            }  

            if (ret == 0)  
                break;  
            load += ret;  
        } while ((size_t)load < period_bytes);  
  
        /* Transfer to size frame */
        load = load / pcm->bytes_per_frame;  
        ret = write_pcm_to_device(pcm, load);  
        if (ret != load)  
            break;  
          
        ret = ret * pcm->bytes_per_frame;  
        written += ret;  
        load = 0;  
    }  
}  
  
int main(int argc, char *argv[])  
{   
    if(argc != 2)
    {  
        fprintf(stderr, "Usage: %s <FILENAME>\n", argv[1]);  
        exit(1);  
    }
      
    // 1：定义存储WAV文件格式信息的结构体wav
    //    定义存储PCM设备相关信息的结构体playback
    wav_format *wav = calloc(1, sizeof(wav_format));  
    pcm_container *playback = calloc(1, sizeof(pcm_container));

    // 2：打开WAV文件
    //    获取其相关音频信息
    int fd = open(argv[1], O_RDONLY);  
    get_wav_header_info(fd, wav);

    // 3：以回放方式打开PCM设备
    //    并根据从WAV文件的头部获取音频信息，设置PCM设备参数
    snd_pcm_open(&playback->handle, "default", SND_PCM_STREAM_PLAYBACK, 0); 
    set_params(playback, wav);
  
    // 4：将WAV文件中除了头部信息之外的PCM数据读出，并写入PCM设备
    play_wav(playback, wav, fd);  
  
    // 5：正常关闭PCM设备
    snd_pcm_drain(playback->handle);  
    snd_pcm_close(playback->handle);  
  
    // 6：释放相关资源
    free(playback->period_buf);  
    free(playback);  
    free(wav);  
    close(fd);  

    return 0;  
}  

