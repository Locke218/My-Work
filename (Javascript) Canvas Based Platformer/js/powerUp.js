//AUTHOR: Zane Draper (ME)
//
//PURPOSE: Setting up some global coin functions for creating coins
//
//***************************************************************
//***************************************************************

"use strict";

//Image Variables
var coinSpin = new Image();
var coinGrabbed = new Image();

//Variables for arrays and animation
var coins;
var frameIndex;
var tickCount;

//Sets up the first platform and platform array
function initCoin(){
	//loading coin images
	coinSpin.src = "media/coins.png";
	coinGrabbed.src = "media/coinGrab.png";
	
	//setup for variables
	frameIndex = 0;
	tickCount = 0;
	
	//set up variables
	coins = [];
}

//creates an coin to place on a platform
function createCoin(sound){
	//setup coin object
	var coin = {};
	
	//Add variables to object
	coin.rand = (Math.floor((Math.random() * 10) + 1))/10;
	coin.x = 0;
	coin.y = 0;
	coin.tickFrame = 1;
	coin.points = 10;
	coin.time = 2;
	coin.frameIndex = 1;
	coin.checkDraw = true;
	coin.grabbed = false;
	
	//Adds grab method (For picking up coins and increment score/timer)
	coin.grab = function(){
		if(this.grabbed == false){
			this.grabbed = true;
			this.tickFrame = 0;
			score += this.points;
			playTimer += this.time;
			this.checkDraw = false;
			sound.playEffect("coin");
		}
	}
	
	//Adds draw method for displaying coins
	coin.draw = function(ctx, x, y, length){
		
		//sets coin location
		this.x = x+(length * this.rand);
		this.y = y - 75;
		
		//checks for character overlap (pickup coin if yes)
		if((this.x < 100 && this.x > 70) && (this.y < 550 )){ this.grab();}
		else if(this.checkDraw == true){this.grabbed = false;}
		
		//updates coin image if not picked up
		if(this.grabbed == false){
			ctx.drawImage(coinSpin,100*this.frameIndex, 0, 100, 100, this.x, this.y, 50, 50);
			this.frameIndex++;
			if (this.frameIndex > 9){
				this.frameIndex = 0;}
		}
		//if picked up, switch animation to this
		else{
			if(this.tickFrame < 9)
			ctx.drawImage(coinGrabbed,128*this.tickFrame, 0, 128, 128, this.x - 25, this.y - 25, 128, 128);
				this.tickFrame++;
		}
	}
	
	//Add coin to coin array
	coins.push(coin);
	
	//returns new coin
	return coin;
}


