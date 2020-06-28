# ALPHA 0.1.1
* Second release (the first one was F'd)
	
# ALPHA 0.2.0
* New, argument based command system
	
# ALPHA 0.3.3
* New command: where
* Added the ability to create your game world on startup
* Added the ability to create amazons and dinosaurs with the same name
  * because of this, some commands require a type argument

# ALPHA 0.3.4
* Fixed some issues with the where command
* Some minor tweaks
	
# ALPHA 0.4.0
* New command: move
* Minor tweaks

# ALPHA 0.5.0
* New command: lookaround

# ALPHA 0.5.1
* Fixed an issue that caused a crash when attacking
* Fixed an issue that let an amazon move to the tile they were already on

# ALPHA 0.6.0
* Handling of dinosaurs reworked
* New commands: tame, geton, getoff

# ALPHA 0.6.5
* Doubled the lower and upper limits of the damage range
* Dinosaurs now spawn on random tiles
* Only the new command requires a type argument
* Formatted the output of lookaround to be more readable
* Fixed a crash when attacking a riding amazon
* Fixed a crash related to using the move command with invalid arguments

# ALPHA 0.6.6
* Fixed a typo in the output of the attack command
* Made the output of the attack command clearer
* Improvements to the output of the lookaround command

# ALPHA 0.6.7
* Removed command: where
* New command: status
* Only amazons on the same tile can attack each other
* The lookaround command now informs the player whether the selected amazon is on a dino
* Made the required world size format clearer
* Made the default spawn location for entities in help clearer

# ALPHA 0.7.0
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

# ALPHA 0.8.0
* Inventory system:
  * Amazons now have an inventory. Every item picked up by the amazons is stored here.
  * Different items have different quantity limits
  * Picked up guns have to be equipped before they can be used
* New commands: equip, drop
* Fixed a bug that caused the pickup command to not throw an error when using it without selecting an amazon first
* Fixed a bug causing dinos to not move with the amazons riding them

# ALPHA 0.8.1
* Fixed an issue that caused the status command to show "null null" when an amazon didn't have items
* Replaced some UTF-8 characters so Windows can display text properly

# ALPHA 0.8.2
* Fixed dead amazons being able to perform actions
* Fixed an issue where the tame command didn't throw an error when given a negative number
* Improved some outputs
* Micro-optimizations

# ALPHA 1.0.0
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

# ALPHA 1.0.1
* Changed the way listing is done
* Gépkatana renamed to katana
* Changed the way how dino movement is handled
* How amazon spawn is handled is now specified in help
* Fixed a bug that caused a walking amazon to be able to get off her dino
* Fixed a bug that caused a riding amazon to be able to get on her dino
* Fixed a bug that caused dinos to never appear on tiles after getting ridden
* Fixed a crash when trying to move to a coordinate containing 0
* Removed some legacy code

# ALPHA 1.1.0
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

# ALPHA 1.1.1
* Fixed a missing newline character in the output of the help command
* Minor code cleanup