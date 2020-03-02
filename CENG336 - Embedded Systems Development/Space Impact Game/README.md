# SpaceImpact
A simple space impact game written in assembly for PIC18F8722 based architecture. You may recall "SpaceImpact" game if you visit [here](https://en.wikipedia.org/wiki/Space_Impact) :smile:.

Codes are developed on MPLAB X IDE with `mpasm v5.83` compiler. Implementation was a part of my Embedded Systems Course in METU.

## How to Run?
If you have a PIC18F8722 based board and MPLAB X IDE installed (with `mpasm` compiler) on your computer, you can create a project in IDE and insert `main.asm` in there. Then you should be able to load and run it on your board and game will be ready to play!

## Internal Details
Game is played in an 6x6 area in which the asteroids and spaceship are both illustrated with leds. To start the game `RG0` button; to move the spaceship down `RG2` button; to move up `RG3` button and to fire a laser beam `RG1` button is used. 

As soon as game starts asteroids get being spawned from the other end of the map with 500 ms periods and as the game continues this period decreases (this feature has been implemented for creating an appalling game).

If you shoot an asteroid your score gets incremented and your score will be always displayed on 7 Segment Display.

### Authors
* Yavuz Selim Yesilyurt
* Alper Kocaman