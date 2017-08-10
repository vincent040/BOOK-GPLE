#!/usr/bin/awk -f

BEGIN{
	age = 0
	score = 0
}
{
	if(NR==1)
	{
		print $0
		printf "================================"
		print  "================================"
	}
	else
	{
		age+=$5
		score+=$6
		print $0
	}
}
END{
	printf "================================"
	print  "================================"
	print "Average:\t\t\t\t\t"age/NR ",\t" score/NR
}
