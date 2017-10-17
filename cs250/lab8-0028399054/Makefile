
all: main

main:
	gcc -o MPP -c MPP.c
	gcc -o volu -c volu.c
	gcc -g -o main main.s MPP volu -lwiringPi

clean:
	rm main
