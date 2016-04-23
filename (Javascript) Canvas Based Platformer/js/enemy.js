//AUTHOR: Zane Draper (ME)
//
//PURPOSE: Setting up the moving platforms and 
//
//***************************************************************
//***************************************************************

"use strict";

//Image Variables
var enemyStand = new Image();
var enemyRun = new Image();
var enemyAttack = new Image();
var enemyJump = new Image();
var enemyDeath = new Image();
var enemyKunai = new Image();
var kunai = new Image();

//Sets up global variables
var enemies;
var frameIndex;

//Create an enemy state
var enemyState = {};

//creates an enum to describe enemy state
enemyState.STATES = Object.freeze({
	STANDING: 0,
	ATTACKING: 1, 
	RUNNING: 2,
	DEAD: 3,
});

//Sets up the enemy images
function initEnemy(){
	//loading enemy images
	enemyStand.src = "media/Enemy_Stand.png";
	enemyRun.src = "media/Enemy_Run.png";
	enemyAttack.src = "media/Enemy_Attack.png";
	enemyJump.src = "media/Enemy_Jump.png";
	enemyDeath.src = "media/Enemy_Death.png";
	enemyKunai.src = "media/Enemy_Kunai.png";
	kunai.src = "media/kunai.png";
	
	//sets up variables
	frameIndex = 0;
	enemies = [];
}

//creates an enemy to place on a platform
function createEnemy(){

	//creates new enemy objects
	var enemy = {};
	
	//adds enemy variables (lots of them)
	enemy.runDistance = 0;
	enemy.state = enemyState.STATES.STANDING;
	enemy.rand = (Math.floor((Math.random() * 5) + 5))/10;
	enemy.x = 0;
	enemy.y = 1000;
	enemy.tickFrame = 1;
	enemy.points = 100;
	enemy.time = 5;
	enemy.playForward = true;
	enemy.coolDown = false
	enemy.coolDownTime = 60;
	
	//chooses a enemy type (ranged or melee)
	enemy.type = Math.floor((Math.random() * 2) + 1);
	if(enemy.type == 1)
		enemy.coolDownTime = 60;
	else if(enemy.type == 2){
		enemy.coolDownTime = 120;
	}
	
	//adds kunai for the ranged attackers
	enemy.kunaiActive = true;
	enemy.kunaiX = 0;
	
	//this is the draw function for the enemies
	enemy.draw = function(ctx, x, y, length){
	
		//sets the enemy position, accounting for movement
		this.x = x+(length * this.rand) - this.runDistance;
		this.y = y - 75;
		
		//If Dead, cycle through death animation
		if(this.state == enemyState.STATES.DEAD){
			ctx.drawImage(enemyDeath,1215 - 122*this.tickFrame, 0, 120, 122, this.x - 20, this.y, 90, 90);
			
			if(this.tickFrame < 9)
				this.tickFrame++;
		}
		//If attacking, cycle through attacking animation
		else if(this.state == enemyState.STATES.ATTACKING){
			if(this.type == 1)
				ctx.drawImage(enemyAttack,1335 - 134*this.tickFrame, 0, 130, 116, this.x - 20, this.y, 100, 90);
			else if(this.type == 2)
				ctx.drawImage(enemyKunai,950 - 95*this.tickFrame, 0, 90, 114, this.x - 20, this.y, 72, 90);
			
			if((timeKeeper%3) == 0){
				if(this.tickFrame < 7 && this.playForward == true){
					this.tickFrame+=1;
					if(this.tickFrame == 7){
						this.playForward = false;
					}
				}
				else if(this.tickFrame > 1 && this.playForward == false){
					this.tickFrame-=1;
					if(this.tickFrame == 1){
						this.state = enemyState.STATES.STANDING;
						this.playForward = true;
						this.coolDown = true;
					}
				}
			}		
		}
		//If running, cycle through running animation
		else if(this.state == enemyState.STATES.RUNNING){
			
			ctx.drawImage(enemyRun,930 - 93*this.tickFrame, 0, 90, 115, this.x - 20, this.y, 70, 90);
			
			if(timeKeeper%3 == 0){
				if(this.tickFrame == 9)
					this.tickFrame = 0;
				if(this.tickFrame < 9)
					this.tickFrame++;
			}
			
			//accounts for movement on platform
			this.runDistance += 3;
		}
		//displays standing image if not doing anything
		else if(this.state == enemyState.STATES.STANDING){
			ctx.drawImage(enemyStand,0, 0, 60, 119, this.x, this.y, 46, 90);
		}
		
		//draws kunai if ranged type and it is active
		if(this.type == 2 && this.kunaiActive == true){
			ctx.drawImage(kunai,0, 0, 120, 43, this.kunaiX, this.y+30, 60, 20);
		}
	}
	
	//this cycles through and sets the character to dead
	enemy.die = function(){
		this.tickFrame = 1;
		this.state = enemyState.STATES.DEAD;
		score += this.points
		playTimer += this.time;
	}
	
	//object method that updates the enemy
	enemy.update = function(){
		//makes sure the enemy isnt dead first
		if(this.state != enemyState.STATES.DEAD){
			//checks for attacking, but waits between attacks
			if(this.y < 600 && this.x < 200 && this.state != enemyState.STATES.ATTACKING && this.coolDown == false){
				this.state = enemyState.STATES.ATTACKING;
				this.tickFrame = 1;
			}
			//cycles through the cooldown phase between attacks
			else if(timeKeeper%this.coolDownTime == 0){
				this.coolDown = false;
			}
			//if melee type, run at the character
			if(this.type == 1 && this.state == 0){
				if(this.y < 500 && this.x > 200){
					this.state = enemyState.STATES.RUNNING;
				}
			}
			//if ranged, through kunai at the player when he is on the platform
			else if(this.type == 2 && this.state == 0 && this.coolDown == false){
				if(this.y < 500 && this.x > 200 && this.x < 800){
					this.state = enemyState.STATES.ATTACKING;
					this.kunaiActive = true;
					this.kunaiX = this.x;
				}
			}
		}
		//updates kunai location in relation to platform
		if(this.type == 2 && this.kunaiActive == true){
			this.kunaiX-= 8;
			if(this.kunaiX < -20) this.kunaiActive = false;
		}
	}
	
	//object method that updates the location of kunai based on speed of character
	enemy.increment = function(speed){
		if(this.type == 2){
			this.kunaiX -= speed;
		}
	}
	
	//Adds this to enemy array
	enemies.push(enemy);
	
	return enemy;
}