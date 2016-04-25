#Humans Vs. Zombies Flocking Algorithms

**Author:** Zane Draper

**Platform:** Processing

**Language:** Processing

**Description:**

* Version A:
	
  * This project was based around creating Autonomous Agents. The agents in this game thus far seek, flee, evaid, pursue chase and wander. All these functions are essential for creating a semi-lifelike NPC. The humans in this simulation begin the game by wandering. By using a simple rotation based off of the forward vector, the movement looks natural. Upon coming within a certain distance of an enemy, the human begins to flee in the opposite direction.
	
  * On the other hand, zombies begin pursuing the human. Humans are slightly faster then zombies, and groups are needed to corner humans. Upon contact between these zombies and humans, the human is destroyed and a zombie is created in its place. These zombies then likewise begin chasing other humans until none remain.
	
  * At any time, the user can activate Debug Mode, by clicking the 'P' button. To spawn new humans, click the mouse anywhere inside the screen.
	
* Version B:
	
  * The humans and zombies avoid obstacles at a distance, to look more natural. Evade is now also included in the simulation. Instead of running from a zombies current position, the humans run from the position they will soon be in. Likewise, zombies	now pursue the human they are chasing's future position. Proper images are used to represent humans and zombies. This is done using the futurePos()  method in the vehicle class. This led to the least maintenance in the code.

**Code:**
* Humans (Runner)
	* Humans inherit from Vehicle
	* They have a flee() method that calls seek()
	* In Debug, forward and right vectors can be seen
	* Are destroyed when touched
	* Evade() now avoids zombie future position
* Zombies (Seeker)
	* Zombies inherit from Vehicle
	* They have a chase() method that finds the closest human
	* In Debug, forward and right vectors can be seen
	* Spawn when humans die
	* Pursue() now moves to humans future position.
* Vehicle
	* Has a checkBounds() method
	* Contains a wander() method for when the npc's are inactive
	* smoothly avoids obstacles
* Obstacle Avoidance
	* Trees places in the scene are avoided by humans and zombies.
* Additional Features:
	* Press 'P' to bring up debug mode
	* Click with the mouse to spawn a new human
		
		
**Room for Improvement:**
* I would like to improve the animation used to create a more active scene. The boundary and obstacle movements could be smoother.
