all: lab4_start.o lab4_main.o lab4_util.o
	ld -m elf_x86_64 lab4_start.o lab4_main.o lab4_util.o -o task0

lab4_main.o: lab4_main.c lab4_util.h
	gcc -m64 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_main.c -o lab4_main.o

lab4_util.o: lab4_util.c lab4_util.h
	gcc -m64 -Wall -ansi -c -nostdlib -fno-stack-protector lab4_util.c -o lab4_util.o
lab4_start.o: lab4_start.s
	nasm -f elf64 lab4_start.s -o lab4_start.o

.PHONY: clean

clean:
	rm -f *.o task0
