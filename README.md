# My dwm build
"dwm is an extremely fast, small, and dynamic window manager for X." 
Based on release 6.4

## Features

* Less sucking - [suckless](https://suckless.org) software
* [Swallowing]() windows - no useless terminals
* [Fullscreening windows]() with SUPER+f
* Extensible status monitor support thanks to [statuscmd]()
* Better looks and easier theming with [alpha](), [bar height]() and [gaps]() options and [xresources support]()
* Better usability with [attachbottom](),  [swaptags](), [warp](), [movestack](), [stack rotating](), [pertag]() and [zoomswap]()
* Better floating windows with [resizecorners](), [savefloats](), [togglefloatingcenter](), [moveresize](). 
* A better multi-head experience with [sendmoncenter](), [statusallmons](), 
* A dwm.desktop entry for use with login managers

## Depedencies

Requires
* Xlib header files for building
* **Optionaly** Some scripts from my dotfiles for power management
* **Optionaly** [pass](https://www.passwordstore.org/) for passmenu integration
* **Optionaly** [dmenu](https://tools.suckless.org/dmenu/) to launch programs

## Status Bar

To set the bar text:
```sh
xsetroot -name "THIS IS THE BAR"
```

You can use a simple while loop in your .xprofile/.xinitrc to keep track of time
```sh
while xsetroot -name "$(date)"; do
	sleep 1
done &
exec dwm
```

## Planned additions

* [tagothermon]() - after I find or make a view patch to go along with it.
* A single head branch for single headed setups.
* Expanded Xresources support - curenly lacking support for (and not limited
  to) alpha, bar height and gap options.
* An acurate man page.

## Insllation 

You're not the target audience of suckless if you need this but here it is:
```sh
git clone https://github.com/ThePolishHussar/dwm.git
cd dwm
make
sudo make install
make clean
```

## Configuration

Modification Should be done in the source code. Simple things like colors and
fonts can be adjusted in config.(def.)h. Extra features usually require writing
a function or 2 in dwm.c and calling it somehow.

###  Xresources

You can modify the following in your ~/.Xresources file or using xrdb. These are defined in config.def.h
```
font
dmenufont
normbgcolor
normbordercolor
normfgcolor
selbgcolor
selbordercolor
selfgcolor
borderpx
snap
showbar
topbar
nmaster
resizehints
mfact
```
