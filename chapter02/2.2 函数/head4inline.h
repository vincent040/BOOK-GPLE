//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.2/head4inline.h  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 求两个整数中的最大值，并将该函数设计为内联函数
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _HEAD4INLINE_H_
#define _HEAD4INLINE_H_

#include <stdio.h>
#include <stdlib.h>

inline max_value(int x, int y)
{
	return x>y? x : y;
}

#endif
