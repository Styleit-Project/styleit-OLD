
Debian
====================
This directory contains files used to package styleitd/styleit-qt
for Debian-based Linux systems. If you compile styleitd/styleit-qt yourself, there are some useful files here.

## styleit: URI support ##


styleit-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install styleit-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your styleitqt binary to `/usr/bin`
and the `../../share/pixmaps/styleit128.png` to `/usr/share/pixmaps`

styleit-qt.protocol (KDE)

