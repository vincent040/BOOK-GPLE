#####################################################################
#
#  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
#
#  File name: GPLE/ch01/1.3/for.sh  
#
#  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
#
#  Date: 2016-3
#  
#  Description: 演示shell中for循环语句的用法
#
#  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
#
#####################################################################

#!/bin/bash

files=`ls`

for a in $files
do
	if [ -f $a ]
	then
		wc -l $a
	fi
done