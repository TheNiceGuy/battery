battery
=======

This is a small program that will check your battery status and print it.

Installation
------------

	make
	make install
	
Uninstallation
--------------

	make uninstall

Usage
-----

With xsetroot, I can display the output of this program  to the top right corner of my screen in dwm. Here is a small script that you can put in your ~/.xinitrc if you want to use this battery in dwm.

	while true; do
		xsetroot -name "$(battery)"
		sleep 1
	done &
	
	exec dwm
	
![Alt text](/img/screenshot01.png "screenshot01.png")
