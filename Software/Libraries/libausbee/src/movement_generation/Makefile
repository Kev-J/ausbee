LDFLAGS=-lm
CFLAGS=-Wall -Wextra -ggdb -O0

test_quadramp: test_quadramp.o graphic.o quadramp.o vector2.o
	gcc ${CFLAGS} $^ -o $@ ${LDFLAGS}

test_quadramp.o: test_quadramp.c graphic.h quadramp.h vector2.h
	gcc ${CFLAGS} -c $<

quadramp.o: quadramp.c quadramp.h vector2.h
	gcc ${CFLAGS} -c $<

graphic.o: graphic.c graphic.h quadramp.h
	gcc ${CFLAGS} -c $<

vector2.o: vector2.c vector2.h
	gcc ${CFLAGS} -c $<

.PHONY: clean
clean:
	@ rm -f *.o
