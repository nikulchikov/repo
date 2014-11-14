
C++ = g++

PQXX_HOME = /home/libpqxx
INCLUDE = -I$(PQXX_HOME)/include

FLAGS   = -fpic -ftemplate-depth-40 -D__linux__ -D_HAVE_CONFIG -D__x86__ -D__OSVERSION__=2  -D_REENTRANT -w
LIBDIR  = -L$(QTDIR)/lib
LIBS    = -lstdc++ -lpthread -lpq

SERVICE_NAME = granika_ll

TS_LSTNR_SOURCE = ts_listener.cpp
TS_LSTNR_OBJECT = ts_listener.o

UDP_RCVR_SOURCE = udp_receiver.cpp
UDP_RCVR_OBJECT = udp_receiver.o

DB_SOURCE = pgdatabase.cpp
DB_OBJECT = pgdatabase.o

UTHREAD_SOURCE = uthread.cpp
UTHREAD_OBJECT = uthread.o

MAIN_SOURCE = main.cpp
MAIN_OBJECT = main.o

NODE_SOURCE = node.cpp
NODE_OBJECT = node.o

CHANNEL_SOURCE = channel.cpp
CHANNEL_OBJECT = channel.o

IMPULSE_SOURCE = impulse.cpp
IMPULSE_OBJECT = impulse.o

MESSAGE_SNDR_SOURCE = message_sndr.cpp
MESSAGE_SNDR_OBJECT = message_sndr.o

TZK_TS_SOURCE = tzk_ts.cpp
TZK_TS_OBJECT = tzk_ts.o

PQXX_OBJECT = $(PQXX_HOME)/src/.libs/libpqxx.a

TARGET = ./$(SERVICE_NAME)

OBJECTS = $(MAIN_OBJECT) $(DB_OBJECT) $(UDP_RCVR_OBJECT) $(UTHREAD_OBJECT) $(TS_LSTNR_OBJECT) $(IMPULSE_OBJECT) $(NODE_OBJECT) $(CHANNEL_OBJECT) \
$(MESSAGE_SNDR_OBJECT) $(TZK_TS_OBJECT)

all:$(OBJECTS) rm_backups
	$(C++) $(OBJECTS) $(PQXX_OBJECT) $(LIBDIR) $(LIBS) -o $(TARGET)

$(TZK_TS_OBJECT) : $(TZK_TS_SOURCE)
	$(C++) $(TZK_TS_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(TZK_TS_OBJECT)

$(MESSAGE_SNDR_OBJECT) : $(MESSAGE_SNDR_SOURCE)
	$(C++) $(MESSAGE_SNDR_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(MESSAGE_SNDR_OBJECT)

$(MAIN_OBJECT) : $(MAIN_SOURCE)
	$(C++) $(MAIN_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(MAIN_OBJECT)

$(DB_OBJECT) : $(DB_SOURCE)
	$(C++) $(DB_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(DB_OBJECT)

$(UDP_RCVR_OBJECT) : $(UDP_RCVR_SOURCE)
	$(C++) $(UDP_RCVR_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(UDP_RCVR_OBJECT)

$(TS_LSTNR_OBJECT) : $(TS_LSTNR_SOURCE)
	$(C++) $(TS_LSTNR_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(TS_LSTNR_OBJECT)

$(UTHREAD_OBJECT) : $(UTHREAD_SOURCE)
	$(C++) $(UTHREAD_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(UTHREAD_OBJECT)

$(IMPULSE_OBJECT) : $(IMPULSE_SOURCE)
	$(C++) $(IMPULSE_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(IMPULSE_OBJECT)

$(NODE_OBJECT) : $(NODE_SOURCE)
	$(C++) $(NODE_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(NODE_OBJECT)

$(CHANNEL_OBJECT) : $(CHANNEL_SOURCE)
	$(C++) $(CHANNEL_SOURCE) $(FLAGS) $(INCLUDE) -c -o $(CHANNEL_OBJECT)

clean:
	rm --force $(OBJECTS) $(TARGET)

install: all
	rm -f /usr/bin/$(SERVICE_NAME)
	cp $(SERVICE_NAME) /usr/bin/$(SERVICE_NAME)

rm_backups:
	rm --force *~
	rm --force ../../utils/*~
