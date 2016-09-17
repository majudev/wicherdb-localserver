#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if ! [ -e bin ]; then
	mkdir bin
fi
if ! [ -e obj ]; then
	mkdir obj
fi
FLAGS="-O3 -Wall `pkg-config --cflags jansson` -Iinclude"
LIBS="`pkg-config --libs jansson`"
if [ "`uname | grep -c -i mingw`" != 0 ]; then
        LIBS="$LIBS -lws2_32"
fi
g++ -c $FLAGS src/Log.cpp -o obj/log.o
g++ -c $FLAGS src/Toolkit.cpp -o obj/toolkit.o
g++ -c $FLAGS src/DatabaseHelper.cpp -o obj/databasehelper.o
g++ -c $FLAGS src/DatabaseCreator.cpp -o obj/databasecreator.o
g++ -c $FLAGS src/DatabaseUpdater.cpp -o obj/databaseupdater.o
g++ -c $FLAGS src/DatabaseGetter.cpp -o obj/databasegetter.o
g++ -c $FLAGS src/DatabaseDropper.cpp -o obj/databasedropper.o
g++ -c $FLAGS src/DatabaseManager.cpp -o obj/databasemanager.o
g++ -c $FLAGS src/MessageParser.cpp -o obj/messageparser.o
g++ -c $FLAGS src/ConnectionManager.cpp -o obj/connectionmanager.o
g++ -c $FLAGS src/Main.cpp -o obj/main.o
g++ $FLAGS \
	obj/log.o\
	obj/toolkit.o\
	obj/databasehelper.o\
	obj/databasecreator.o\
	obj/databaseupdater.o\
	obj/databasegetter.o\
	obj/databasedropper.o\
	obj/databasemanager.o\
	obj/messageparser.o\
	obj/connectionmanager.o\
	obj/main.o\
	src/_main.cpp\
	$LIBS\
	-o bin/DebugServer
if [ -e bin/DebugServer ] && ! [ -h run ]; then
	ln -s bin/DebugServer run
fi
