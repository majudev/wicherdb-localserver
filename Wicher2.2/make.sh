#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if ! [ -e bin ]; then
	mkdir bin
fi
if ! [ -e obj ]; then
	mkdir obj
fi
FLAGS="-O3 -Wall -Iinclude `pkg-config --cflags gtkmm-3.0 jansson`"
LIBS="`pkg-config --libs gtkmm-3.0 jansson` -lboost_thread -lboost_system"
if [ "`uname | grep -c -i mingw`" != 0 ]; then
	LIBS="$LIBS -lws2_32"
fi
g++ -c $FLAGS src/Toolkit.cpp -o obj/toolkit.o
g++ -c $FLAGS src/Dialogger.cpp -o obj/dialogger.o
g++ -c $FLAGS src/Splash/RunServer.cpp -o obj/runserver.o #-I../boost-1.61.0/include
g++ -c $FLAGS src/Splash/Splash.cpp -o obj/splash.o
g++ -c $FLAGS src/Database.cpp -o obj/database.o
g++ -c $FLAGS src/DatabaseQuery.cpp -o obj/databasequery.o
g++ -c $FLAGS src/sha256.cpp -o obj/sha256.o
g++ -c $FLAGS src/Main/Builder.cpp -o obj/builder.o
g++ -c $FLAGS src/Toolbar/ToolbarOptions.cpp -o obj/toolbaroptions.o
g++ -c $FLAGS src/Toolbar/ToolbarInfo.cpp -o obj/toolbarinfo.o
g++ -c $FLAGS src/SignalWindows/CreateTypeWindow.cpp -o obj/createtypewindow.o
g++ -c $FLAGS src/SignalWindows/CreateItemWindow.cpp -o obj/createitemwindow.o
g++ -c $FLAGS src/SignalWindows/CreateWZWindow.cpp -o obj/createwzwindow.o
g++ -c $FLAGS src/SignalWindows/CreatePZWindow.cpp -o obj/createpzwindow.o
g++ -c $FLAGS src/SignalWindows/InfoTypeWindow.cpp -o obj/infotypewindow.o
g++ -c $FLAGS src/SignalWindows/AddItemsWindow.cpp -o obj/additemswindow.o
g++ -c $FLAGS src/SignalWindows/InfoItemWindow.cpp -o obj/infoitemwindow.o
g++ -c $FLAGS src/SignalWindows/InfoWZWindow.cpp -o obj/infowzwindow.o
g++ -c $FLAGS src/SignalWindows/InfoPZWindow.cpp -o obj/infopzwindow.o
g++ -c $FLAGS src/SignalWindows/SignalWindows.cpp -o obj/signalwindows.o
g++ -c $FLAGS src/ListsManager/StateManager.cpp -o obj/statemanager.o
g++ -c $FLAGS src/ListsManager/Refresh.cpp -o obj/refresh.o
g++ -c $FLAGS src/ListsManager/ColumnModels.cpp -o obj/columnmodels.o
g++ -c $FLAGS src/ListsManager/Constructor.cpp -o obj/constructor.o
g++ -c $FLAGS src/ListsManager/ListsSignals.cpp -o obj/listssignals.o
g++ -c $FLAGS src/ListsManager/ListsEditSignals.cpp -o obj/listseditsignals.o
g++ -c $FLAGS src/Main/Main.cpp -o obj/main.o
g++ $FLAGS \
	obj/toolkit.o\
	obj/dialogger.o\
	obj/runserver.o\
	obj/splash.o\
	obj/database.o\
	obj/databasequery.o\
	obj/sha256.o\
	obj/builder.o\
	obj/toolbaroptions.o\
	obj/toolbarinfo.o\
	obj/createtypewindow.o\
	obj/createitemwindow.o\
	obj/createwzwindow.o\
	obj/createpzwindow.o\
	obj/infotypewindow.o\
	obj/additemswindow.o\
	obj/infoitemwindow.o\
	obj/infowzwindow.o\
	obj/infopzwindow.o\
	obj/signalwindows.o\
	obj/statemanager.o\
	obj/refresh.o\
	obj/columnmodels.o\
	obj/constructor.o\
	obj/listssignals.o\
	obj/listseditsignals.o\
	obj/main.o\
	src/main.cpp\
	$LIBS\
	-o bin/Wicher
if [ -e bin/Wicher ] && ! [ -h run ]; then
	ln -s bin/Wicher run
fi
