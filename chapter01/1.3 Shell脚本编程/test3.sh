#####################################################################
#
#  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
#
#  File name: GPLE/ch01/1.3/test3.sh  
#
#  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
#
#  Date: 2016-3
#  
#  Description: 使用test命令测试文件
#
#  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
#
#####################################################################

#!/bin/bash

if [ -e file ] && [ -r file ]
then
	cat file
elif [ -e file ]
then
	chmod u+r file
	cat file
else
	touch file
fi