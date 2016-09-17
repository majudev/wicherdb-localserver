#!/bin/bash
if [ -d Wicher ]; then
	echo "Removing Wicher package..."
	rm -r Wicher
fi
echo "Cleaning Wicher..."
cd Wicher2.2
./clean.sh
cd ..
echo "Cleaning WicherDB local server..."
cd WicherDB_Server
./clean.sh
cd ..
if [ "`uname`" == "Linux" ]; then
	echo "Cleaning WicherDB-fakeclient..."
	cd wicherdb-fakeclient
#	./clean.sh
	cd ..
fi
