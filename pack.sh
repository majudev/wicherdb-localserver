#!/bin/bash
#./make.sh
cd Wicher
x=0
for i in `ldd bin/Wicher`; do
	if [ $x -eq 2 ]; then
		if [ "`echo $i | grep -c -F '/c/Windows'`" -eq 0 ]; then
			echo "cp $i bin";
			cp $i bin
		fi
	fi
	x=$((x+1))
	if [ $x -gt 3 ]; then
		x=0
	fi
done;
mkdir -p share/icons
mkdir -p share/themes
cp -r /mingw64/share/themes/Default share/themes
cp -r /mingw64/share/gtk-3.0 share
cp -r /mingw64/share/icons/Adwaita share/icons
rm -r share/icons/Adwaita/cursors
rm -r share/icons/Adwaita/22x22
rm -r share/icons/Adwaita/24x24
rm -r share/icons/Adwaita/48x48
rm -r share/icons/Adwaita/64x64
rm -r share/icons/Adwaita/96x96
rm -r share/icons/Adwaita/128x128
rm -r share/icons/Adwaita/256x256
rm database.db
../rcedit.exe "Wicher.exe" --set-icon "../Starter/icon.ico"
cd ..
