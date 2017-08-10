//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.1/namesapce.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了C语言中的名字空间的细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

struct apple
{
	int apple;
};

int main(void)
{
	struct apple sweet_fruit;
	sweet_fruit.apple = 100;

	double apple = 3.14;

apple:
	if(apple == 0)
		goto apple;

	return 0;
}
