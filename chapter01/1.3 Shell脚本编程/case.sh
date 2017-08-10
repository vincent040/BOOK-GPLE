#####################################################################
#
#  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
#
#  File name: GPLE/ch01/1.3/case.sh  
#
#  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
#
#  Date: 2016-3
#  
#  Description: 演示shell脚本中case的用法
#
#  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
#
#####################################################################

#!/bin/bash

read VAR		# 从键盘接收一个用户输入

case $VAR in	# 判断用户输入的值$VAR
    1)	echo “one”	# 如果$VAR的值为1，则显示one
        ;;			# 每个分支都必须以双分号作为结束（最后一个分支除外）
    2)	echo “two”
        ;;
    *)	echo “unknown”	# 星号*是Shell中的通配符，代表任意字符。
esac