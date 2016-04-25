#Asteroids 2.0
Author: Zane Draper

Platform: Processing

Language: Processing

**Description:**

* This game is a revamp of the classic Asteroids game. Much like last time, in this version, the player navigates their way through a field of asteroids. If they are hit, they die. The game using basic shapes for the asteroids and the shit, varying the size of the asteroids using a random variable.
* Unlike in the previous version though, the player's ship remains centered in the screen. The player instead navigates a much larger arena, moving through the asteroids instead of the asteroids coming to them. Also, the player can still shoot to destroy asteroids, but instead of just destroying the asteroid, asteroids that break up now drop resources which can be picked up for larger points and health.
* The player can recieve 3 hits before the game is over and their score is saved in a highscore list (provided they do well).
* Some other features are the movement system, which uses excelleration and deceleration to make movement more natural. There is also a trail of afterburn from the ship which creates a trail behind the player.

**Code:**
* Asteroids
	* The direction and speed are determined randomly
	* If the asteroid is whole, it is a red circle that will damage the player
	* If the asteroid is small, it is a blue square that can be picked up
	* The movement direction is affected by the rotation of the player
* Player
	* Uses basic physics acceleration equations for movement
	* The afterburn using randomly generated sizes and hues of blue
	* The afterburner circles fade to smaller sizes and opacity over time.
* Highscore
	* The score is compared and, if high enough, written to a text file

**Controls:**
* Use W to move forward and SPACE to fire
		
		
**Room for Improvement:**
* I would like to improve the actual asteroids and their movement a bit more. Their random generation leaves a little to be desired. Also, another concept for increased difficulty was leaving a corporeal trail that the player could run into, much like snake.
