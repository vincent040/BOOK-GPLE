V1 = /etc/init.d /home/vincent/.bashrc /usr/bin/man

A = $(dir $(V1))
B = $(notdir $(V1))
C = $(suffix $(V1))
D = $(basename $(V1))
E = $(addsuffix .bk,$(V1))
F = $(addprefix host:,$(V1))

V2 = my name is $(1) $(2)
G = $(call V2,Michael,Jackson)

V3 = $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH))))
H = $(call V3,nm)


all:
	echo $(A)
	echo $(B)
	echo $(C)
	echo $(D)
	echo $(E)
	echo $(F)
	echo $(G)
	echo $(H)
