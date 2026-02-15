# sfwall - Simple (Feh) Wallpaper Manager

* KISS
* Easy one line configuration
* Mallable - easy copy paste code to create, and load different wallpaper folders/pictures (flavors)
* Portable for all linux and BSD systems with just two files (nob and sfwall)

!WARNING! 
THIS DOES NOT WORK WITH FULL DESKTOP ENVIRONMENT SYSTEM SUCH AS KDE, GNOME, ETC. IT USES IT'S OWN BLOAT WALLPAPER MANAGER THAT OVERRIDES FEH.

There is a solution - disable KDE/Gnome wallpaper engine. 

## How-to

open editor 
change line 15 user to your account name
    `#define WF_FOLDER "/home/user/Pictures/Wallpaper/"` 

to bootstrap, 
    `cc -o nob nob.c`

If you make any changes in sfwallp.c, all you have to do is run 
    `./nob`

`cp ./sfwall /usr/bin`
`cd /usr/bin && chmod 755 ./sfwall`

## FAQ

1) why not use bash? 
    A) Because bash is not portable and scripting bash is painful.
    
2) why not add feature that pulls images from sites
    A) Because everybody has different taste. They already have their own wallpapers.
    B) Link breaks all the time, requires maintenance. It's annoying.
    C) Modern wallpaper sites block webcrawl / scrappers thus makes it painful.
    D) Pulling images from random sites will give you high and lows resolution with terrible shots.
    
3) May I pull your wallpapers? 
    A) No becase I will have to add credits and license. Another layer of problems. 
    
4) Why not use other wallpaper manager? 
    A) bloat
    B) Different languages
    C) Doesn't do well with date correspondence to seasons sorting system
    D) It's either random pick any image, or select image. It sucks. It's annoying.

5) If it's bloat then why feh is the only dependency? Isn't that not suckless?!
    A) feh is well documented, and well implemented. 
    B) Written in pure C.
    C) Widely used in nearly all linux and bsd. It is typically installed by default.
    D) I don't want to write yet another wallpaper header which then would make it a dependency. Feh already did the leg work.
    
6) Wayland support?
    A) Feh is specifically designed for X11 and xLibre. That would require rewrite. 
    B) Use wayland alternatives
    
7) No more questions. Leave me alone. 

