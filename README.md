# Dinosaur Riding Machine Gun Wielding Amazons

## C++ edition
*I've switched to C++ for several reasons, none of which I'm going to explain here. This is the main one, all versions from here on are only C++ ones, and the Java edition is deprecated.*

### ALPHA 1.3.3
* Fixed a bug that caused Braindrainers to leave attacked riding amazons in an invalid state at the end of turns.
* Fixed a bug that caused Braindrainers to attack dead amazons at the end of turns.
* Fixed a bug that caused end-of-turn Braindrainer attacks to potentially mismanage the amazon registry.
* Fixed a rare bug that could cause attacks to report incorrectly.
* Small performance optimizations.

### ALPHA 1.3.2
* Fixed a bug that caused crashes under some very specific circumstances around items.
* Fixed a bug that resulted in infinite loops in various situations if an amazon had more than ~2 billion items.
* Fixed a bug that resulted in infinite loops in some specific situations if a tile had more than ~2 billion dinos or items.
* Fixed a bug that resulted in an infinite loop if a player's command was longer than ~2 billion characters.

### ALPHA 1.3.1
* Changed the lookaround command to display coordinates instead of directions.
* Coordinates are now displayed as (x, y) instead of x;y for better readability.

### ALPHA 1.3.0
* Switched language to C++.
* Changed the game language to English.
* The game no longer has a terminal of its own.
* The exit command can no longer be used to quit the game before selecting a gamemode.
* When a dino that's being ridden dies, its amazon automatically gets off of it.
* Ending turns no longer clears the players' amazon selection.
* Ending turns no longer clears the terminal.
* The map is no longer rotated for the second player.
* Massively improved the help menu.
* Fixed a bug resulting in braindrainers not attacking amazons at the end of rounds.
* Fixed lots of bugs around random-based mechanics.
* Changed several algorithms to faster and more reliable ones.

## Java edition
*I started this project using Java, but when I created this repo, I was well into a couple months of development. So most of the Java source here was decompiled using JD, and, well,  it didn't turn out to be very good. Besides the last java commit, neither of them compile actually, although they don't require a lot of tinkering. If you want to try a java version, the last commit containing java code is original and untouched, try that. This edition is deprecated, though.*

### ALPHA 1.2.1
* Updated the help menu and made its existence more apparent
* Optimizations

### ALPHA 1.2.0
* New enemy: the Braindrainer
  * Spawns randomly, moves around the map after each turn, and attacks amazons moving onto their tile
* Major code cleanup

### ALPHA 1.1.2
* Already selected amazons can no longer be reselected
* Fixed an OCD triggering asymetry in the end-of-turn markers
* Fixed a bug causing multiple weapons to spawn on the same tile
* Major code cleanup

### ALPHA 1.1.1
* Fixed a missing newline character in the output of the help command
* Minor code cleanup

### ALPHA 1.1.0
* The game now has its own user interface
  * UTF-8 characters are now supported
* Player switches now retain the event log of the players
  * Added some lines to indicate where switches happened
* Removed a hidden feature :(
* Commands are now case insensitive
* References to tiles changed to fields
* Renamed katana back to gépkatana
* Renamed to pistol to pisztoly
* Reworked the way taming works when multiple dinos are available
* Improved outputs
* Fixed a typo when listing amazons

### ALPHA 1.0.1
* Changed the way listing is done
* Gépkatana renamed to katana
* Changed the way how dino movement is handled
* How amazon spawn is handled is now specified in help
* Fixed a bug that caused a walking amazon to be able to get off her dino
* Fixed a bug that caused a riding amazon to be able to get on her dino
* Fixed a bug that caused dinos to never appear on tiles after getting ridden
* Fixed a crash when trying to move to a coordinate containing 0
* Removed some legacy code

### ALPHA 1.0.0
* New 2 player system:
  * The game can now be played by 2 players
  * New turn based mechanics
  * The player who kills all of their opponent's possible spawns wins
* New commands: steps, end, list
* Movement system tweaked:
  * Coordinates are now horizontal-vertical
  * Limited movement to surrounding tiles
* Improved some outputs
* Players can now quit before generating a world
* Fixed an exception when taming dinos
* Micro-optimizations

### ALPHA 0.8.2
* Fixed dead amazons being able to perform actions
* Fixed an issue where the tame command didn't throw an error when given a negative number
* Improved some outputs
* Micro-optimizations

### ALPHA 0.8.1
* Fixed an issue that caused the status command to show "null null" when an amazon didn't have items
* Replaced some UTF-8 characters so Windows can display text properly

### ALPHA 0.8.0
* Inventory system:
  * Amazons now have an inventory. Every item picked up by the amazons is stored here.
  * Different items have different quantity limits
  * Picked up guns have to be equipped before they can be used
* New commands: equip, drop
* Fixed a bug that caused the pickup command to not throw an error when using it without selecting an amazon first
* Fixed a bug causing dinos to not move with the amazons riding them

### ALPHA 0.7.0
* World generation reworked:
  * Instead of inputting size, players can now choose from world presets
  * Dinos now auto-spawn on random tiles depending on the preset
  * World size also depends on the chosen preset
* Weapon system reworked:
  * Weapons now auto-spawn on random tiles
  * They can be picked up by amazons
  * Weapons are now organized into different categories: pistol, shotgun, etc.
* New command: pickup
* The new command no longer requires a type argument
* Status command extended to accomodate the new features

### ALPHA 0.6.7
* Removed command: where
* New command: status
* Only amazons on the same tile can attack each other
* The lookaround command now informs the player whether the selected amazon is on a dino
* Made the required world size format clearer
* Made the default spawn location for entities in help clearer

### ALPHA 0.6.6
* Fixed a typo in the output of the attack command
* Made the output of the attack command clearer
* Improvements to the output of the lookaround command

### ALPHA 0.6.5
* Doubled the lower and upper limits of the damage range
* Dinosaurs now spawn on random tiles
* Only the new command requires a type argument
* Formatted the output of lookaround to be more readable
* Fixed a crash when attacking a riding amazon
* Fixed a crash related to using the move command with invalid arguments

### ALPHA 0.6.0
* Handling of dinosaurs reworked
* New commands: tame, geton, getoff

### ALPHA 0.5.1
* Fixed an issue that caused a crash when attacking
* Fixed an issue that let an amazon move to the tile they were already on

### ALPHA 0.5.0
* New command: lookaround

### ALPHA 0.4.0
* New command: move
* Minor tweaks

### ALPHA 0.3.4
* Fixed some issues with the where command
* Some minor tweaks

### ALPHA 0.3.3
* New command: where
* Added the ability to create your game world on startup
* Added the ability to create amazons and dinosaurs with the same name
  * because of this, some commands require a type argument

### ALPHA 0.2.0
* New, argument based command system

### ALPHA 0.1.1
* Second release (the first one was F'd)