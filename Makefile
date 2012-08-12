
test.exe:	test.c x86utils.c x86utils.h
	gcc -Wall -o test test.c x86utils.c