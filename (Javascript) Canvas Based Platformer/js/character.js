//AUTHOR: Zane Draper (ME)
//
//PURPOSE: Setting up the main character's animation and interaction
//
//***************************************************************
//***************************************************************

"use strict";

var app = app || {};

// define the .character module and immediately invoke it in an IIFE
app.character = (function(){

	//Animation Images
	var charStand = new Image();
	var charRun = new Image();
	var charAttack = new Image();
	var charJump = new Image();
	var charDeath = new Image();
	
	//Variables for Animation
	var frameIndex;
	var tickTime;
	var attacking;
	var dead;

	//Sets up the character images and variables
	function init(){
	
		//loading images
		charStand.src = "media/MainC_Stand.png";
		charRun.src = "media/MainC_Run.png";
		charAttack.src = "media/MainC_Attack.png";
		charJump.src = "media/MainC_Jump.png";
		charDeath.src = "media/MainC_Death.png";
			
		attacking = false;
		dead = false;
		frameIndex = 0;
		tickTime = 2;
	}
	
	//Draws the character (checks for mode)
	function draw(ctx, gameState){
	
		//draws dif images in different states
		if(attacking == true){
			ctx.drawImage(charAttack,134*frameIndex + 10, 0, 130, 116, 100, 484, 100, 90);
		}
		else if(gameState == 1 || gameState == 2){
			ctx.drawImage(charJump,270, 0, 90, 117, 100, 484, 70, 90);
		}
		else if(myKeys.keydown[myKeys.KEYBOARD.KEY_RIGHT]){
			ctx.drawImage(charRun,93*frameIndex, 0, 85, 115, 100, 484, 70, 90);
		}
		else{
			ctx.drawImage(charStand,0, 0, 60, 119, 100, 484, 46, 90);
		}
		
		//updates frameIndex
		update();
	}
	
	//updates key frame and if attacking
	function update(){
	
		//Increments frameIndex for animation
		if(timeKeeper%tickTime == 0){
			if(frameIndex < 9)
				frameIndex++;
			else{ 
				if(attacking == true){
					attacking = false;
					tickTime = 2;
				}
				frameIndex = 0;
			}
		}
		
		//Attack with SPACE - check for press, then switch variable
		if(myKeys.keydown[myKeys.KEYBOARD.KEY_SPACE] && attacking == false){
			attacking = true;
			frameIndex = 0;
			tickTime = 1;
		}
		
		//Cycle through enemies and see if enemies are in range & attacking
		for(var i = 0; i < enemies.length; i++){
			//Ranged Attack
			if(enemies[i].type == 1){
				if(enemies[i].x < 160 && enemies[i].x > 110 && enemies[i].y < 500 && enemies[i].state == enemyState.STATES.ATTACKING){
					dead = true;
				}
			}
			//Close Attack
			else if(enemies[i].type == 2){
				if(enemies[i].kunaiActive == true && enemies[i].kunaiX < 110 && enemies[i].kunaiX > 100 && enemies[i].y < 500){
					dead = true;
					enemies[i].kunaiActive = false;
					enemies[i].kunaiX = 200;
				}
			}
		}
		
		//Checks for enemy damage
		attack();
	}
	
	//Attacks enemies (checks for in-range enemy)
	function attack(){
		if(attacking == true){
			if(enemies[0].x < 185 && enemies[0].y < 650 && enemies[0].state != enemyState.STATES.DEAD){
				enemies[0].die();
			}
		}
	}
	
	//returns the dead variable
	function getDead(){
		return dead;
	}
	
	//resets dead for game restart
	function rst(){
		dead = false;
	}
	
	//Sets up function calls
	return{
		init: init,
		draw: draw,
		getDead: getDead,
		rst: rst,
	};
}());