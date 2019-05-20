
Debian
====================
This directory contains files used to package yucoind/yucoin-qt
for Debian-based Linux systems. If you compile yucoind/yucoin-qt yourself, there are some useful files here.

## yucoin: URI support ##


yucoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install yucoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your yucoinqt binary to `/usr/bin`
and the `../../share/pixmaps/yucoin128.png` to `/usr/share/pixmaps`

yucoin-qt.protocol (KDE)

