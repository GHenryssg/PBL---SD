all:
	gcc -Wall Main.c -o Main -lintelfpgaup -lpthread -std=c99
	sudo ./Main
	