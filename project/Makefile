CC=../cLEMENCy/neat/neatcc/ncc
LD=../cLEMENCy/neat/neatld/nld
LIBC=../cLEMENCy/neat/neatlibc
OBJ=main.o

.PHONY: clean

all: bin

bin: ${OBJ}
	${LD} -f -o $@ -L $(LIBC) -lc $(OBJ)


${OBJ}: %.o: %.c
	${CC} -I$(LIBC) $< -o $@

clean:
	-rm *~
	-rm *.o
	-rm *.map

