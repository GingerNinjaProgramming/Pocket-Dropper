# FGCT4015 - Fundamentals of Games Development

## Pocket Dropper

Name: Conner Reece Vian

Student NO : 2500411

Date: 5/12/2025

[Repository Link]("(https://github.com/GingerNinjaProgramming/Pocket-Dropper)")

[Build Link]("")

### Project Outline

My project is a simple 2D infinite dropper game in the same vein as something like Downwell (Downwell on Steam, s.d.) or Jetpack joyride (Studios, s.d.) being in the up and down instead of the left and right. The main loop of the game will consist of player infinity falling facing obstacles along the way. This fits to the theme of pocket as in the theming of the game the player is a item being dropped into someones pocket.

## Research

### Methodology

During my research I intend to be look for a combination of information on raylib and C++ as these are both topics that I am relatively new to and need to do research on to ensure I have enough knowledge to complete to project to an acceptable standard. Along with this I will be looking into examples of infinite runner,dropper games like Downwell and games like it and try and see what these games do well and what they don't. As understanding this will help inform my games development and what features I should implement and how to implement them in a way that works for the type of game Im making.

I am going to attempt to get as much play testing as possible for this project to help ensure the game goes in direction that a regular player would find fun to play and has features and optimizations that people want instead of spending my time adding features that may amount to nothing in the grand scheme of things. I will be approaching this testing with a unguided forward mindset to get a better idea of how a normal person would play my game.

### Sources

#### Mastering C++ a Beginners Guide

When doing research for this project I first looked at material on C++, as this was my first major time using C++. One such book was  __Mastering C++ a Beginners Guide__ (Bin Uzayr, 2022). I did this to help improve my C++ knowledge as at the time this was a new language to me and though familiar with programming I wanted to be sure that I don't miss any syntax differences between C++ and another language like C#.I used this source as a beginner in C++ it seemed easy to pick up and learn from along with being advised this book via word of mouth from people in my studies. I learned many things about C++ reading from this books including:

* Vectors
* Pointers 
* Data Types
* Header files
* C++ OOP techniques

This book was very useful in my early C++ journey allowing me to iron out the details and differences between C++ and any other programming languages giving me a good starting point to start coding in raylib. However, by its very nature, being a beginner guide it does not break down everything and a lot of other things still had to be learned from experience / prior knowledge so while being a good spring board for work many things still had to be learned from other means like in person lectures.

![image](https://file.garden/aSY-yx_ZmANpQe1l/Pocket-Dropper-Ref/DownwellGameplay.jpg)

Figma 1 - Frame of Downwell gameplay

#### Downwell - The Game

Along with above during my research I looked into a game called downwell to see if I could get any ideas from a preexisting work similar to what I want my own project to be like which has achieved popularity (Downwell (video game), 2025). I learned some things from doing this that would help inform my game as it went further from research to actually making including:

* Enemy Types
* Main Loop
* Techniques to make more fun
* Keep simplistic 
* General Art Direction 

This research was useful as in the space my games DNA shares a lot of similarities to this game and considering the fact that this game did this formula successfully it makes sense to take information from the best contenders in the space. A downside of the research is in hindsight it may of allowed the scope of the game to grow to a place where it did not reasonably need to be where, though I aim to make something good understanding my personal limitations is something I need to keep in mind to allow me to scope my project reasonably. Along with this researching all of this gave no actual info on how to implement these features leaving it more up to me to learn as I went though my creative journey.

#### Raylib Cheat-Sheet / Documentation

I also used the official raylib (raylib | A simple and easy-to-use library to enjoy videogames programming, s.d.) documentation and cheat sheet (raylib - cheatsheet, s.d.) as some of my sources when working on this project. This felt right as considering raylib is the framework (Raylib -- Easiest C/C++ Game Framework -- Now Even Better For Beginners!, 2024) im using for this project so by occam's razor would suggest that the offical documentation would be the best place to start when looking for infomation on raylib. On this documentation it:

* Directed me to other raylib libraries that I used **[See External Libraries]** 
* Gave me a place to see a lot of base raylib functions 
* Acted as a HUB to find other useful information and tools

![image](https://file.garden/aSY-yx_ZmANpQe1l/RaylibCheatSheet.png)

Figma 2 - Showing undescript nature of the Raylib Cheat Sheet

This research was helpful in my project as it helped inform me the basic functionality of raylib and how to get something functional setup to start working on. It was also positive to the development journey of my project as it helped direct me to other tools to that would go on to help me later. A downside of this source/s is that when it came to the cheat sheet it was not very in depth on functions on what they did more just having the function signature with a brief comment leaving me to sometimes have to do testing on how the functions work more precisely or going to other places to find what these functions do to see if they can fix my problem.


## Implementation

### Process

### New Approaches

- First time doing yadada and how learning that went

### User Testing

- Talk about how users felt on first test
- Show data
- Talk about second test / benchmark
- Qualitive and Quantitive 
- Guided or non guided 

## Instructions to Install / Run

To run the project [Download Zip](Pocket-Dropper.zip)

Then run the **.exe** inside of the extracted Zip file

## Reflection 

### Research Effectiveness 

- Was the research effective

### Positive analysis

### Negative analysis

### Next time

- wht u learnt and now want to do more of
- what is guiding intrests 


## Declared Assets

Version Control: **Git** / **Github**

IDE - **Clion** 

Engine - **Raylib**

Throughout the creation of this project I used a combination of github copilot and chatgpt to help debug problems. This is along with using AI to help create the initial boiler plate for the [CMakeLists](CMakeLists.txt) which was used to debug the entire the project.

I used mainly self made assets for this project with the only thing not directly made by me being the background music called Pixel Peeker Polka (Pixel Peeker Polka - faster, 2020) which is covered under creative commons license  allowing for use,altering,etc as long as the creator is credited 

- External Libarys:
    - Raylib-Aseprite (Loach, 2025) was used to facilitate aseprite files to be used as sprites in the game
    - RayMath (raylib/src/raymath.h at master · raysan5/raylib, s.d.) was used for easy access to alot of game math functions and classes
    - RayGUI (Ray, 2025) was used to facilitate a basic pause menu


## References 

### Game Sources 

Downwell on Steam (s.d.) At: https://store.steampowered.com/app/360740/Downwell/ (Accessed  24/11/2025).

Downwell (video game) (2025) In: Wikipedia. At: https://en.wikipedia.org/w/index.php?title=Downwell_(video_game)&oldid=1318898889 (Accessed  24/11/2025).


Studios, H. (s.d.) Jetpack Joyride Classic - Halfbrick. At: https://www.halfbrick.com/games/jetpack-joyride-classic (Accessed  24/11/2025).

### Academic Sources 

Bin Uzayr, S. (2022) Mastering C++: a beginner’s guide. (First) Boca Raton: CRC Press/Taylor & Francis Group. At: https://go.exlibris.link/3PMP0wMy (Accessed  24/11/2025).

### Documentation Sources

Get Started in raylib in 20 minutes! (2024) Directed by Programming With Nick. At: https://www.youtube.com/watch?v=RGzj-PF7D74 (Accessed  24/11/2025).

How to get raylib working with CMakeLists Clion linux (2021) Directed by Holographic Squid. At: https://www.youtube.com/watch?v=maR-qQqC0nM (Accessed  24/11/2025).

CLion Just Made Raylib Setup Too Easy (2025) Directed by Rambod Dev. At: https://www.youtube.com/watch?v=dg2HYv0-hlM (Accessed  24/11/2025).

raylib - cheatsheet (s.d.) At: https://www.raylib.com (Accessed  25/11/2025).

raylib (2025) In: Wikipedia. At: https://en.wikipedia.org/w/index.php?title=Raylib&oldid=1313652413 (Accessed  24/10/2025).


### Other

Loach, R. (2025) RobLoach/raylib-aseprite. At: https://github.com/RobLoach/raylib-aseprite (Accessed  24/11/2025).

Ray (2025) raysan5/raygui. At: https://github.com/raysan5/raygui (Accessed  24/11/2025).

raylib/src/raymath.h at master · raysan5/raylib (s.d.) At: https://github.com/raysan5/raylib/blob/master/src/raymath.h (Accessed  24/11/2025).

Raylib -- Easiest C/C++ Game Framework -- Now Even Better For Beginners! (2024) Directed by Gamefromscratch. At: https://www.youtube.com/watch?v=TgCwzMemb_M (Accessed  25/11/2025).


Pixel Peeker Polka - faster (2020) Directed by Kevin MacLeod. At: https://www.youtube.com/watch?v=JbspWYbuxgE

Licensed under Creative Commons: By Attribution 4.0 License
http://creativecommons.org/licenses/by/4.0/
