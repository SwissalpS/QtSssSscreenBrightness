README.md
# Qt SwissalpS Screen Brightness #
Target Audience: Users of Fedora 27 on iMac12,2 and possibly others.

## DEPENDENCIES ##

- stdbuf
- xrandr
- awk
- linux OS (possibly works on OSX too, if other dependencies are met)
- iMac12,2 (possibly works on other models too)


## FEATURE LIST ##

- allows adjusting screen brightness with a slider
- allows boosting to over 100% (this will blow-out quickly)

Basically a GUI-wrapper for:
- getting brightness of first display:
	stdbuf -o0 xrandr --verbose | awk '/Brightness/ { print $2; exit }';

- setting brightness:
	xrandr --output eDP --brightness <value>

Tested on Fedora 27 with Gnome 3.26.2 (classic mode) running on iMac12,2
Compiled with Qt 5.10


## Authors Info ##

Luke Zimmermann aka SwissalpS
SwissalpS@LukeZimmermann.com

## Version Info ##
20180313_230200

## Where to get from ##
- **git** https://github.com/SwissalpS/QtSssSscreenBrightness.git
- **git** git@github.com:SwissalpS/QtSssSscreenBrightness.git
