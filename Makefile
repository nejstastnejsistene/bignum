default:
	gcc -Wall -o test test.c bignum.c
test:
	./test.py

.PHONY: default, test
