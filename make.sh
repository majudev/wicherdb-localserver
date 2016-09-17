#!/bin/bash
if [ -e Wicher ]; then
	rm -r Wicher;
fi
mkdir -p Wicher/bin
echo "Making and copying WicherDB local server..."
cd WicherDB_Server
./make.sh
if [ "`uname | grep -c -i mingw`" != 0 ]; then
	cp bin/DebugServer.exe ../Wicher/bin/local_server.exe
else
	cp bin/DebugServer ../Wicher/bin/local_server
fi
if [ -e database.db ]; then
	cp database.db ../Wicher
fi
cd ..
echo "Making and copying Wicher..."
cd Wicher2.2
./make.sh
if [ "`uname | grep -c -i mingw`" != 0 ]; then
	cp bin/Wicher.exe ../Wicher/bin/Wicher.exe
else
	cp bin/Wicher ../Wicher/bin/Wicher
fi
cp -r icons ../Wicher
cp -r gui ../Wicher
cd ..
cd Starter
./make.sh
if [ "`uname | grep -c -i mingw`" != 0 ]; then
	cp Wicher.exe ../Wicher/Wicher.exe
else
	cp Wicher ../Wicher/Wicher
fi
cd ..
if [ "`uname -s`" == "Linux" ]; then
	echo "Compiling WicherDB-fakeclient..."
	cd wicherdb-fakeclient
	./make.sh
	cd ..
fi
