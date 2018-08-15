LIB_PATH=$(shell pwd)/../lib
INCLUDE=-I$(LIB_PATH)/include
LIB=-L$(LIB_PATH)/lib

.PHONY:all
all:insert_cgi select_cgi
	
insert_cgi:insert_cgi.cpp common.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) -lmysqlclient
select_cgi:select_cgi.cpp common.cpp
	g++ -o $@ $^ $(INCLUDE) $(LIB) -lmysqlclient
.PHONY:clean
clean:
	rm -f insert_cgi select_cgi
