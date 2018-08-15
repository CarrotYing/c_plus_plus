WORK_PATH=$(shell pwd)
BIN=myHttp
SRC=myHttp.c main.c
CC=gcc
LDFLAGS=-lpthread -DDEBUG

.PHONY:$(BIN) cgi
all:$(BIN) cgi  

$(BIN):$(SRC)
	$(CC) -o $@ $^ $(LDFLAGS)
cgi:
	cd cgi/calculate; make clean; make; cd -	
	cd cgi/sql;make clean; make;cd -

.PHONY:clean
clean:
	rm -f $(BIN)
	cd cgi/calculate; make clean;  cd -
	cd cgi/calculate; make clean; cd -

