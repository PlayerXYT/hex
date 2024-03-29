.PHONY: clean
.PHONY: delete
.PHONY: all
.PHONY: hex
.PHONY: unhex

all: bin/hex bin/unhex
hex: bin/hex
unhex: bin/unhex

bin/hex: obj/hex.o obj/common.o
	gcc -o bin/hex -s obj/hex.o obj/common.o

obj/hex.o: src/hex.c
	gcc -o obj/hex.o -c src/hex.c

bin/unhex: obj/unhex.o obj/common.o
	gcc -o bin/unhex -s obj/unhex.o obj/common.o

obj/unhex.o: src/unhex.c
	gcc -o obj/unhex.o -c src/unhex.c

obj/common.o: src/common.c src/common.h
	gcc -o obj/common.o -c src/common.c

clean:
	rm obj/* ; true > /dev/null

delete:
	rm obj/* ; true > /dev/null
	rm bin/* ; true > /dev/null
