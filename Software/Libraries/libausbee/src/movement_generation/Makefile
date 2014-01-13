test_quadramp: test_quadramp.o graphic.o quadramp.o
	g++ -Wall -Wextra $^ -o $@

test_quadramp.o: test_quadramp.cpp graphic.h quadramp.h
	g++ -Wall -Wextra -c $<

quadramp.o: quadramp.cpp quadramp.h
	g++ -Wall -Wextra -c $<

graphic.o: graphic.cpp graphic.h quadramp.h
	g++ -Wall -Wextra -c $<

.PHONY: clean
clean:
	@ rm -f *.o
