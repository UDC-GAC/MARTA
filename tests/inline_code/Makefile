FLAGS_KERNEL:= -O3 -flto -mfma
FLAGS_MAIN:=  -O1 -flto -finline-functions

all: kernel.c main.c
	gcc -c $(FLAGS_KERNEL) kernel.c
	gcc $(FLAGS_MAIN) kernel.o main.c -o main.o