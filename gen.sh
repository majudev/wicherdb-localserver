#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
if [ "`uname -s`" == "Linux" ]; then
	echo "Linux found!"
	if [ "`uname -n`" == "debian" ]; then
		if [ "`whoami`" != "root" ]; then
			echo "You must be root to do this."
			exit
		fi
		if [ ! -d Wicher ]; then
			echo "You must build project to pack it."
			echo Run "./make.sh"
			exit
		fi
		mkdir /tmp/deb-pkg
		cd /tmp/deb-pkg
		mkdir DEBIAN
		if [ "`arch | grep -c 64`" != 0 ]; then
			cp $DIR/pkg-files/Debian/control64 DEBIAN/control
		else
			cp $DIR/pkg-files/Debian/control32 DEBIAN/control
		fi
		mkdir opt
		cp -r $DIR/Wicher opt
		mkdir -p usr/bin
		ln -s /opt/Wicher/Wicher usr/bin/Wicher
		ln -s /opt/Wicher/Wicher usr/bin/wicher
		ln -s /opt/Wicher/Wicher usr/bin/Wicher2.2
		mkdir -p usr/share/applications
		cp $DIR/pkg-files/Debian/Wicher.desktop usr/share/applications
		cd ..
		dpkg -b deb-pkg
		cp deb-pkg.deb $DIR
		rm -r deb-pkg
		rm deb-pkg.deb
		echo "Built!"
	else
		echo "You are not on Debian!"
		echo "Only Debian systems are supported."
	fi
else
	echo "Windows dude"
fi
