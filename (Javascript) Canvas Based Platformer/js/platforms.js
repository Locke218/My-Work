//AUTHOR: Zane Draper (ME)
//
//PURPOSE: Setting up the moving platforms and 
//
//***************************************************************
//***************************************************************

"use strict";

var app = app || {};

// define the .platform module and immediately invoke it in an IIFE
app.platforms = (function(){

	//For debugging purposes
	console.log("platforms.js module loaded");
	
	//Array Variables (For holding multiples of objects)
	var platformArr = [];
	var coinsPlaced = [];
	var platformS = {};

	//Game State Enum
	platformS.GAME_STATE = Object.freeze({
		WALKING: 0,
		FALLING: 1,
		DEAD: 2,
	});
	
	//Variables for updating platform movement
	var platformState;
	var jumpPressed;
	var gravityValue;
	var speed;
	
	//Sets up the first platform and platform array
	function init(){
	
		//Initialize y movement (none)
		gravityValue = 0;
		jumpPressed = false;
	
		//Sets up the platform array
		platformArr = [];
		
		//Two empty objects for first platforms
		var p = {};
		var p2 = {};
		
		//First platform setup
		p.x = 25;
		p.y = 550;
		p.length = Math.floor((Math.random() * 1000) + 500);
		
		//Second platform setup
		p2.x = p.x + p.length + Math.floor((Math.random() * 200) + 30);
		p2.y = p.y + Math.floor((Math.random() * 70) + 70);
		p2.length = Math.floor((Math.random() * 1000) + 500);
		
		//State of platform (for movement)
		platformState = platformS.GAME_STATE.WALKING;
		
		//adds platforms to array
		platformArr.push(p);
		platformArr.push(p2);
		
		//Sets speed of character (all movement contained in this class
		speed = 7;
	}
	
	//Implements gravity (Movement contained in this class, not character)
	function gravity(sound){
	
		//Listens for jump key
		if(myKeys.keydown[myKeys.KEYBOARD.KEY_UP] && !jumpPressed){
		
			//sets up y movement, changes state and plays the sound efect
			gravityValue = 7.00;
			jumpPressed = true;
			platformState = platformS.GAME_STATE.FALLING;
			sound.playEffect("jump");
		}
		
		//If the current first platform is behind character, fall
		if(platformArr[0].x + platformArr[0].length < 100){
			platformState = platformS.GAME_STATE.FALLING;
		}
		
		//Checks to see if character is off the ground
		if(platformState == platformS.GAME_STATE.FALLING){
		
			//implements gravity movement on all current platforms
			for(var i = 0; i < platformArr.length; i++){
				platformArr[i].y += gravityValue;
			}
			
			//decrements gravity
			gravityValue -= .18;
			
			//If the character falls between platforms, die
			if(platformArr[0].y < 300 && platformArr[1].y < 350 ){
				platformState = platformS.GAME_STATE.DEAD;
			}
			//If platform is beneath character, change state to walking
			else if(platformArr[0].x + platformArr[0].length > 100 && platformArr[0].y <= 550 && platformArr[0].y >= 540){
				platformState = platformS.GAME_STATE.WALKING;
				gravityValue = 0.00;
				jumpPressed = false;
			}
			//If next platform if under player, change state to walking
			else if(platformArr[1].x < 100  && platformArr[1].y <= 550 && platformArr[1].y >= 540){
				platformState = platformS.GAME_STATE.WALKING;
				gravityValue = 0.00;
				jumpPressed = false;
			}
		}
	}
	
	//Draws the platforms - also updates their location based off of key input
	function draw(ctx){
		for(var i = 0; i < platformArr.length; i++){
			
			//Checks to see if the platform is moving
			if(myKeys.keydown[myKeys.KEYBOARD.KEY_RIGHT]){
				platformArr[i].x-=speed;
				
				if(platformArr[i].enemy != undefined)
					platformArr[i].enemy.increment(speed);
			}
			
			//Draws the platforms
			var length = platformArr[i].length;
			var x = platformArr[i].x;
			var y = platformArr[i].y;
			
			ctx.beginPath(); 
			ctx.lineWidth="1";
			ctx.strokeStyle="green";
			ctx.fillStyle="green"; // Green path
			
			ctx.moveTo(x, y + 40);
			ctx.lineTo(x + length, y + 40);
			ctx.lineTo(x + length + 100, y - 20);
			ctx.lineTo(x + 100, y - 15);
			ctx.stroke(); // Draw it
			ctx.fill();
			
			ctx.beginPath();
			ctx.fillStyle="#8B4513";
			ctx.strokeStyle="#8B4513"; // Purple path
			ctx.moveTo(x, y + 40);
			ctx.lineTo(x + length, y + 40);
			ctx.lineTo(x + length, y + 1000);
			ctx.lineTo(x, y + 1000);
			ctx.fill();
			
			ctx.beginPath();
			ctx.fillStyle="#A0522D";
			ctx.strokeStyle="#A0522D"; // Purple path
			ctx.moveTo(x + length, y + 1000);
			ctx.lineTo(x + length, y + 40);
			ctx.lineTo(x + length + 100, y - 20);
			ctx.lineTo(x + length + 100, y + 1000);
			ctx.fill();
			
			//checks for enemies, draws
			if(platformArr[i].enemy != undefined){
				platformArr[i].enemy.draw(ctx, x, y, length);
			}
		
			//checks for coins, draws
			if(platformArr[i].coinNum != undefined){
				for(var j = 0; j < platformArr[i].coinNum; j ++){
					platformArr[i].coinPt[j].draw(ctx, x, y, length);
				}
			}

		}
		
		//Removes off screen platforms
		if(platformArr[1].x <= -20){
			
			//removes any enemies on platform from global array
			if(platformArr[0].enemy != undefined){
				enemies.shift();
			}
			
			//removes any coins on platform from global array
			if(platformArr[1].coinNum != undefined){
				for(var i = 0; i < platformArr[1].coinNum; i ++){
					coins.shift();
				}
			}
			
			//removes platform
			platformArr.shift();
		}
	}
	
	//Gets length of platform
	function platformLength(){
		return platformArr.length;
	}
	
	//Creates a new platform
	function makePlatform(sound){
	
		//create new platform object
		var p = {};
		
		//gets variable for previous platform
		var length = platformArr.length - 1;
		var rand = Math.floor((Math.random() * 50) + 20);
		
		//sets new platform up based on location of previous
		p.x = platformArr[length].x + platformArr[length].length + Math.floor((Math.random() * 5*rand) + rand);
		p.y = platformArr[length].y + Math.floor((Math.random() * (rand + 30)) + rand + rand/2);
		p.length = Math.floor((Math.random() * 1000) + 500);
		
		//random variable for chance enemy
		rand = Math.floor((Math.random() * 100) + 1);
		
		//tries to add enemy
		if(rand < (30 + (10 * level))){
			p.enemy = createEnemy();
		}
		
		//coins
		p.coinPt = [];
		
		//creates number of coins based off of platform length
		var coinNum = Math.floor( (p.length/100) / 3);
		p.coinNum = coinNum;
		for(var i = 0; i < p.coinNum; i ++){
			p.coinPt[i] = createCoin(sound);
		}
		
		//adds platform to array of platforms
		platformArr.push(p);
	}
	
	//returns platform state
	function getPlatformState(){
		return platformState;
	}
	
	//Sets up function calls
	return{
		init: init,
		draw: draw,
		makePlatform: makePlatform,
		platformLength: platformLength,
		gravity: gravity,
		getPlatformState: getPlatformState,
	};
}());