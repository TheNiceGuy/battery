battery
=======

This is a small program that will check your battery status and print it.

Configuration
-------------

The file src/global.h have some define that you can change. You'll probably only need to change the ADAPTER define to yours. You can find it by typing that command:

	$ ls -l /sys/class/power_supply/
	total 0
	lrwxrwxrwx 1 root root 0 Mar 24 20:08 ACAD
	lrwxrwxrwx 1 root root 0 Mar 24 20:08 BAT1      #this one is mines

Installation
------------

	$ make
	$ sudo make install
	
Uninstallation
--------------

	$ sudo make uninstall

Usage
-----

With xsetroot, I can display the output of this program  to the top right corner of my screen in dwm. Here is a small script that you can put in your ~/.xinitrc if you want to use this battery in dwm.

	#!/bin/sh

	while true; do
		xsetroot -name "| $(battery) |"
		sleep 1
	done &
	
	exec dwm
	
![Alt text](/img/screenshot01.png "screenshot01.png")
