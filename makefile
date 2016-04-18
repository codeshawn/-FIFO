#
# brief : fifo
# author: zhuzhixiang
# date: 2016-04-06
#

CC			=g++
TAR         =fifo
SRC         =$(wildcard *.cpp)

OBJ         =$(patsubst %.cpp,%.o, $(SRC))

INC         =-I.
CF          =-c -g -Wall
LIB         =-lpthread
		
$(TAR):$(OBJ)
	$(CC) -g -o $@ $^ $(LIB)
	rm -rf $(OBJ)

$(OBJ):%.o:%.cpp
	$(CC) $(CF) $< $(INC) -o $@

.PHONY:clean
clean:
	rm -rf $(OBJ) $(TAR)

