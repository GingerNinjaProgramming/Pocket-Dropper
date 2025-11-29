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

![image](https://file.garden/aSY-yx_ZmANpQe1l/Pocket-Dropper-Ref/ExerptOfBook.png)

Figma 1 - Excerpt of Mastering C++ a Beginners Guide (Bin Uzayr, 2022)

#### Mastering C++ a Beginners Guide

When doing research for this project I first looked at material on C++, as this was my first major time using C++. One such book was  __Mastering C++ a Beginners Guide__ (Bin Uzayr, 2022). I did this to help improve my C++ knowledge as at the time this was a new language to me and though familiar with programming I wanted to be sure that I don't miss any syntax differences between C++ and another language like C#.I used this source as a beginner in C++ it seemed easy to pick up and learn from along with being advised this book via word of mouth from people in my studies. I learned many things about C++ reading from this books including:

* Vectors
* Pointers 
* Data Types
* Header files
* C++ OOP techniques

This book was very useful in my early C++ journey allowing me to iron out the details and differences between C++ and any other programming languages giving me a good starting point to start coding in raylib. However, by its very nature, being a beginner guide it does not break down everything and a lot of other things still had to be learned from experience / prior knowledge so while being a good spring board for work many things still had to be learned from other means like in person lectures.

![image](https://file.garden/aSY-yx_ZmANpQe1l/Pocket-Dropper-Ref/DownwellGameplay.jpg)

Figma 2 - Frame of Downwell gameplay

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

![image](https://file.garden/aSY-yx_ZmANpQe1l/Pocket-Dropper-Ref/RaylibCheatSheet.png)

Figma 3 - Showing undescript nature of the Raylib Cheat Sheet

This research was helpful in my project as it helped inform me the basic functionality of raylib and how to get something functional setup to start working on. It was also positive to the development journey of my project as it helped direct me to other tools to that would go on to help me later. A downside of this source/s is that when it came to the cheat sheet it was not very in depth on functions on what they did more just having the function signature with a brief comment leaving me to sometimes have to do testing on how the functions work more precisely or going to other places to find what these functions do to see if they can fix my problem.


## Implementation

### Process

Describe your technical and creative approach, including:

* Planning, ideation, and iteration
* Feedback received and how it was integrated
* New tools, workflows, or systems explored

When I was planning my project I wanted something that would be easy to make the basics of that would allow me to use different techniques while still allowing for relative scalability if that is in the cards.  

Coming into this project I had a background of C# programming which is a language which focuses heavily on Object Orientated Principles (Clark, 2011) this meant that when it came to programming my project in C++ I attempted to replicate some of the same methodology and ideas that come from a OOP mind set along with picking up on some functional programming (Functional Programming Paradigm, 23:53:03+00:00). These principles both being described in **Design Patterns: Elements of Reusable Object-Oriented Software** (Design Patterns, 2025).

I began my project development with the core functionality of the game, this being the dropping of the player. When starting out my development of my game I started coding it logically as a form of skydiving sim with the player perpetually falling with different obstacles randomly spawning requiring the player to move out of the way. This worked similar to logic of how outer wilds moving between planets works **(CITATION NEEDED)** where instead of moving the player it would move the world around the player instead giving the illusion of the player moving when in reality they have not moved an inch. Towards this I begun working on a physics system involving drag and terminal velocity to make this sky diving esc system fun to play with and begun working on this. However after a week of trying this I begun to relies that the current state of the game and the current idea of the games logic was not working as physics systems had a lot more complexities than i initially relzsed and I begun to notice making the game like this went against one of the cores of my planning which was a simple and easy to prototype base game so at this moment a week into my project I decided to pivot my games logic into a more conventionally design dropper where the player is infinity falling with mini randomly generated platforms and enemy's around for the player to dodge/eliminate. This works based on a basic falling mechanic where the player has both a vector2 for its location and a vector to define its velocity which is added to its location every frame, modifying these values is how player movement is managed in code. Therefore when the player is not on the platform a constantforce will be added to the players y force allowing for the player to fall and to allow for the player to fall quicker the longer they have been falling the movement force pushing down on the player upon the system recognizing the player is falling begins to use a more conventional approach using a combination of a constant gravity value, the players preset weight value, the players falling time and the frames delta time to allow for the player to slowly and exponentionaly speed up the longer they have been falling.

```cpp
void UpdatePlayer(Player &player){
        UpdateAsepriteTag(&player.currentAnimation.baseTag);
        Vector2 previousPos(player.x,player.y);

        if (!player.isTouchingGround && player.movementVelocity.y >= 0) {
            player.isFalling = true;
            player.timeFallingDown += GetFrameTime();
            player.movementVelocity.y = GRAVITY * player.weight * (1 + player.timeFallingDown) * GetFrameTime();
        }else if (player.movementVelocity.y < 0) {
            player.movementVelocity.y += 1;
        }else {
            player.isFalling = false;
        }

        player.x += player.movementVelocity.x;
        player.y += player.movementVelocity.y;

        HandleMissedCollision(player, previousPos);
        HandlePlayerState(player);

        player.movementVelocity.x *= (float)player.currentFriction / 10;

        //Works to ensure that it clamps at zero for purposes of some checks
        if (abs (player.movementVelocity.x) < 0.1f) {
            player.movementVelocity.x = 0;
        }
    }
```

Figma 4 - Update Player Function

Along with this I implemented more advanced collision detection to ensure the increased speed of the player does not allow the player to move so fast as to miss collisions completely. To do this i took advantage of how in raylib since you have to deal with frame drawing your self I can do more precise checks before the player has even been drawn. The way this was done was just after the players position value was updated but importantly before the next time the player was drawn to the frame a new function is called using the player and the players previous position. Inside the function it creates an imaginary box using the players previous location and the players possible new position as points to draw this box from. This box is then used to do a collision check, checking if there is anything the player shold collide with between these points in space and if something is detected, aka the player missed a collision due to high speed or other reasons, the players y is set to a position on top of the object to where it should of reasonably collided with it, as if it actually hit the object and didn't phase right past it. In practice this performs a type of sweeping motion between the players current position and the position it wants to be checking if its allowed to do that movement or if it needs to be changed.

```cpp
 void HandleMissedCollision(Player &player,Vector2 previousPos) {
        float x = fminf(player.x, previousPos.x);
        float y = fminf(player.y, previousPos.y);
        float width = fabsf(player.x - previousPos.x);
        float height = fabsf(player.y - previousPos.y);

        Rectangle checkRect = {x,y,width,height};

        for (auto platform : PlatformUtils::platforms) {
            if (CheckCollisionRecs(checkRect, platform.body.AsRect())){
                //Collision should of happened but didnt
                PlayerUtils::HandleFloorCollision(player); //Run regular collision code
                player.y = platform.body.position.y - player.spawnRadius; //Put player ontop of collided platform
                std::cout << "Collision missed" << std::endl;
                return; //Collision has been found
            }
        }

        for (auto enemy : Enemys::enemys) {
            if (CheckCollisionRecs(checkRect, enemy->body.AsRect())){
                //Collision should of happened but didnt
                PlayerUtils::HandleFloorCollision(player); //Run regular collision code
                player.y = enemy->body.AsRect().y - player.spawnRadius; //Put player ontop of collided platform
                std::cout << "Collision missed" << std::endl;
                return; //Collision has been found
            }
        }
    }
```

Figma 5 - HandleMissedCollision Function

Along with this is added two basic enemies, one being a patroling enemy that has a random chance to spawn along side one of the platforms moving left and right across the screen on the y axis it was spawned being able to be jumped on by the player resulting in a kill by the player once its hit points are reduced to zero. The other enemy while being more primitive has a random chance to spawn underneath a platform and then proceed to follow the player being activated once the player falls past it, this enemy can be killed in the same way or out right ignored if your moving past it fast enough.

### New Approaches

This project was my first time using C++ and it led to new discoveries about computer programming and the hidden detail behind it as is expected from a lower level language that works closer with the computers hardware unlike another language like C#. Along with this it was also my first time using raylib and compared to other tools I have used in the past like unreal and unity, raylib was a lot more a DIY programming experience with a lot of the things you take for granted in a normal engine being things you have to manually make yourself like for example collision systems which while raylib has features to allow for collision it is still something you have to build yourself. This does however allow for a lot more creative expression in your system as it is completely up to you how these systems are designed allowing you to create them to the needs of your project rather than having to mess around with pre-made systems that may not completely fit the needs of your project. One early thing i relised when doing the rendering for my project is that as computer screens draw from left to right row by row the rendering in code adhears to this rule as well making for some interesting things that needed to be accounted for in code. These being that the y value increased as you went down instead of as you move up as is typical in most game engines meaning the coord (0,0) in space actually represents the top-left of your screen rather than the bottom left as would be expected typically, then as well when it came to drawing objects on the screen it would be drawn using the x and y as the top left point of the element then drawing the width and height right and down from this point. This meant when it came to determining exact positioning of elements on the screen extra logic needed to be implemented to get the center point of anything in the screen to ensure that when it came to things like collision checking it was using the accurate positioning of the character at the time.

### User Testing

- Talk about how users felt on first test
- Show data
- Talk about second test / benchmark
- Qualitive and Quantitive 
- Guided or non guided 

When it came to user testing admittedly this is one of the weaker parts of my project but despite this I still have some user testing at the start of my project and nearer to the end of my development cycle. 

## Instructions to Install / Run

To run the project [Download Zip](Pocket-Dropper.zip)

Then run the **.exe** inside of the extracted Zip file

## Reflection 

### Research Effectiveness 

The research into downwell and C++/Raylib as a whole was very useful on the general approach to the game in the first place along with the actual programming work on raylib which aided in the early development of the game. Along with this the videos on raylib I watched proved mostly helpful in the development process. However admittedly some tutorials proved unhelpful as they were either too old to be applicable like with tutorials on the compiler (CITATION NEEDED) or the mechanics being shown/created were too spesfic to fit for the problem I had resulting in some wasted time going back and forwards though a video just to relise it was not what i needed anyway before making it myself.

### Positive analysis

On my positive reflection, functionally this fits the brief along with including a lot of different concepts along with have a generally clean code thoughout the project. The game successfully shows similar mechinanics to what it is based off along with have animations, audio and mostly functioning mechanics. Additionally thoughout my code I managed to make it in a way keeping the systems modular and easily reuseable in other projects with little / no changes needed

### Negative analysis

On my more objective negative analysis, the game while functioning was not actually as fun as I wanted it to be and was not particularly fun nor did it have much re-playability. Additionally during the project I do not believe i worked on sprites/sound as much as I could of showing how the project lacks in these two areas. I belive this may of been due to lacking user testing early on in project and in the future i need to ensure i do more testing more often to give my game better direction.

### Next time

Next time Im going to try and focus more on early prototypes when working on the game giving more time on working on the games core mechanics and allowing time to make the core of the game fun to play before deep diving on making the code efficient. This would also further help solve my other problem as being able to generate good functioning prototypes as quick as possible as early as possible further helps gives me more user feedback which can then ensure a better project once I leave the prototyping phase. Along with this I think during my future projects I am going to try and consult more of my peers during development as I took a extremely independent mindset during the project which could of been to my projects determent especially in the fun department.

As far as whats guiding my intrests for future projects I had a lot of fun building reuseable and good systems that can be used thoughout my project and possibly to be used in later projects, when working on more projects thoughout my studies I want to continue to build more systems like this and possibly at some point build full on plugins and libarys for things like raylib,unreal,etc (CITATION NEEDED)

## Declared Assets

Version Control: **Git** / **Github**

IDE - **Clion** 

Engine - **Raylib**

Throughout the creation of this project I used a combination of github copilot and chatgpt to help debug problems. This is along with using AI to help create the initial boiler plate for the [CMakeLists](CMakeLists.txt) which was used to debug the entire the project.

- AI used:
    - **GPT5** for general question and code questions 
    - In-IDE **Github copilot** used for code questions, debugging in areas and creation of my debugger

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

Clark, D. (2011) Beginning C# Object-Oriented Programming. Berkeley, CA: Apress. At: http://link.springer.com/10.1007/978-1-4302-3531-6 (Accessed  26/11/2025).

Functional Programming Paradigm (23:53:03+00:00) At: https://www.geeksforgeeks.org/blogs/functional-programming-paradigm/ (Accessed  26/11/2025).


Design Patterns (2025) In: Wikipedia. At: https://en.wikipedia.org/w/index.php?title=Design_Patterns&oldid=1314328185 (Accessed  26/11/2025).


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
