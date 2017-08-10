////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.5/wav_player.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用SDL播放wav格式音频数据
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_config.h"

struct wave
{
	SDL_AudioSpec spec;
	Uint8   *sound;      /* Pointer to wave data */
	Uint32   soundlen;   /* Length of wave data */
	int      soundpos;   /* Current play position */
} wave;

// 画进度条
void draw_progress_bar(int left, int len)
{
	int i;
	for(i=0; i<20; i++)
		printf("\b");

	printf("[");
	int n=((1-(float)left/len)*100) / 10;

	for(i=0; i<=n; i++)
		printf("-");

	printf(">");

	for(i=0; i<9-n; i++)
		printf(" ");

	printf("] %.1f%%", (1-(float)left/len)*100);
	fflush(stdout);
}


// 音频解码回调函数
void deal_audio(void *unused, Uint8 *stream, int len)
{
	Uint8 *waveptr;
	int    waveleft;

	waveptr = wave.sound + wave.soundpos;
	waveleft = wave.soundlen - wave.soundpos;

	while(waveleft <= len)
	{
		memcpy(stream, waveptr, waveleft);
		stream += waveleft;
		len -= waveleft;
		waveptr = wave.sound;
		waveleft = wave.soundlen;
		wave.soundpos = 0;

		printf("\n");
		SDL_CloseAudio();
		SDL_FreeWAV(wave.sound);
		SDL_Quit();

		exit(0);
	}
	memcpy(stream, waveptr, len);
	wave.soundpos += len;

	draw_progress_bar(waveleft, wave.soundlen);
}

int main(int argc, char *argv[])
{
	// 初始化音频子系统
	SDL_Init(SDL_INIT_AUDIO);
	
	// 加载WAV文件
	SDL_LoadWAV(argv[1], &wave.spec,
			&wave.sound, &wave.soundlen);

	// 指定音频数据处理回调函数
	wave.spec.callback = deal_audio;

	// 启动音频设备
	SDL_OpenAudio(&wave.spec, NULL);
	SDL_PauseAudio(0);

	printf("\npress Enter to pause and unpause.\n");
	static int pause_on = 1;
	while(1)
	{
		// 按下回车键，暂停或播放
		getchar();
		SDL_PauseAudio(pause_on++);

		if(!(pause_on%=2)) printf("stoped.\n");
	}

	return 0;
}
