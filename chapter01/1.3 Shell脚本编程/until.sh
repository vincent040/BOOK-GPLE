#####################################################################
#
#  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
#
#  File name: GPLE/ch01/1.3/until.sh  
#
#  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
#
#  Date: 2016-3
#  
#  Description: 演示shell脚本中until的用法
#
#  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
#
#####################################################################

#!/bin/bash

declare -i n=0

until [ $n -gt 100 ]
do
	echo "$n"
	n=$n + 1
done