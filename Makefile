# Makefile for Huffman compressor/decompressor files
# By Eudis Duran
# November 3, 2009

FLAGS := -Wall
LD_FLAGS :=
LIBS := -lm
CXX := g++

TARGET :=huffman

OBJS :=init.o main.o co.o dec.o ibitstream.o obitstream.o node.o

FILES :=init.cpp main.cpp co.cpp dec.cpp ibitstream.cpp obitstream.cpp node.cpp \
      init.h co.h dec.h ibitstream.h obitstream.h node.h

$(TARGET) : $(OBJS)
		$(CXX) $(FLAGS) $(LD_FLAGS) $(OBJS) -o $(TARGET) $(LIBS)
	
main.o: main.cpp
		$(CXX) -c main.cpp -o main.o

init.o: init.cpp init.h
		$(CXX) -c init.cpp -o init.o

co.o: co.cpp co.h
		$(CXX) -c co.cpp -o co.o

dec.o: dec.cpp dec.h
		$(CXX) -c dec.cpp -o dec.o

ibitstream.o: ibitstream.cpp ibitstream.h
		$(CXX) -c ibitstream.cpp -o ibitstream.o

obitstream.o: obitstream.cpp obitstream.h
		$(CXX) -c obitstream.cpp -o obitstream.o

node.o: node.cpp node.h
		$(CXX) -c node.cpp -o node.o

.PHONY: clean
clean:
	-rm -f *.o

