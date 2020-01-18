# Project-Space-Invaders
Exam task for GP (Gevorderd Programmeren)

Build status: [![Build Status](https://travis-ci.com/BasilRommens/Project-Space-Invaders.svg?token=ngBY2shRs4ANxmwKfR7w&branch=master)](https://travis-ci.com/BasilRommens/Project-Space-Invaders)

Site: https://basilrommens.github.io/Project-Space-Invaders/

## Coordinate system

The coordinate system used to drive this game is by default \[-4, 4\]x\[-3, 3\].

## Downloading and playing the game

```bash
$ git clone https://github.com/BasilRommens/Project-Space-Invaders
$ cd Project-Space-Invaders
$ chmod +x run.sh
$ ./run.sh
```

## Controls

| Control Key   | Control       |
| :-----------: | :------------ |
| A             | Move left     |
| D             | Move left    |
| SPACE         | Fire a bullet |
| ESC           | Quit the game |
| R | Replay the game when a victory or game over message shows on screen |

## Config files

> All the variable names that are used here have no default value therefore no variable can be excluded!

### Game
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
|Type             | The type of the file to be read ("game")| string |
|Levels| Contains a list to the level files| list\[string\] |

### Level
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
|Type | The type of the file to be read ("level")|string|
|Enemies| The enemies that will be read from the file provided|string|
|Player| The player will be parsed from the filestring that is provided|string|
|World|The world file to process|string|

### World
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
|Type| The type of the file that we are supposed to read ("world")| string|
|Image|The image that is supposed to represent the world| string|
|End| The virtual line in the given coordinate system that marks when the aliens will end the game| double|

### Hitbox
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
|Width| The width of the hitbox measured to the left|double|
|Height| The height of a hitbox measured downwards|double|

### Position
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
|x| The x position on the scale of the world coordinate system | double |
|y| The y position on the scale of the world coordinate system | double |

### Bullet
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
| Type             | The type of the entity ("bullet")    |string|
| Damage             | The total damage that a bullet will do    |double|
|Image| The image to be used for the bullet|string|
| HitBox           | The hitbox of a bullet measured from the top left of the bullet |Hitbox (see above)|

### Player
| Variable name|Description|Variable type|
| :--- | :--- | :--- |
| Type| The type of the entity ("player") | string |
| Position | The position of the player in the coordinate system given (always measured from top left) | Position (see above)|
|HSpeed| The horizontal speed of the player this will get updated every frame with every click of button | double|
|Image| The image to represent the player on screen| string|
|HP| The total amount of HP the player has (damage is done by bullets)|double |
|Bullet | The file that is used to represent a bullet of the player | string |
|Hitbox| The hitbox of the player measured from the top left of the player| Hitbox (see above)|

### Enemies

Instead of handling the parameter Ships in enemies as a list of entities, we will see it as one entity that will be handled

| Variable name|Description|Variable type|
| :--- | :--- | :--- |
| Type| The type of the entity ("enemy") | string |
|HSpeed| The horizontal speed of the player this will get updated every frame | double|
|VSpeed| The vertical speed of the enemy this will get updated every time the enemy hits the wall | double|
| Position | The position of the enemy in the coordinate system given (always measured from top left) | Position (see above)|
|Image| The image to represent the enemy on screen| string|
|HP| The total amount of HP the enemy has (damage is done by bullets)|double |
|Bullet | The file that is used to represent a bullet of the enemy | string |
|Hitbox| The hitbox of the enemy measured from the top left of the enemy| Hitbox (see above)|

## Creating and opening the documentation

You are supposed to be in the root of the project in order to be able to create the documentation. Subsequently you need to execute the following bash commands.
> Doxygen is required to be installed on the PC

```bash
$ cd doc
$ doxygen Doxyfile
```

To be able to open the files you then need to navigate to the html directory and open the index file with following commands.
```bash
$ cd html
$ xdg-open index.html
```