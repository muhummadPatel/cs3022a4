CPP=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=imageops
FILES=image.o

$(EXE_NAME): driver.o $(FILES)
	$(CPP) -o $(EXE_NAME) $(FILES) driver.o $(CPPFLAGS)

image.o: image.cpp image.h
	$(CPP) -c -o image.o image.cpp $(CPPFLAGS)

driver.o: driver.cpp
	$(CPP) -c -o driver.o driver.cpp $(CPPFLAGS)

test:
	$(CPP) -c -o image.o image.cpp $(CPPFLAGS)
	$(CPP) -c -o test.o test.cpp $(CPPFLAGS)
	$(CPP) -o testimageops test.o image.o $(CPPFLAGS)
	./testimageops

clean:
	rm -f *.o $(EXE_NAME) testimageops
