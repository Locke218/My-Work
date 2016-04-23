// main.js
// Dependencies: 
// Description: singleton object
// This object will be our main "controller" class and will contain references
// to most of the other objects in the game.

"use strict";

// if app exists use the existing copy
// else create a new object literal
var app = app || {};

/*
 .main is an object literal that is a property of the app global
 This object literal has its own properties and methods (functions)
 
 */
app.main = {
	//  properties
    WIDTH : 1700, 
    HEIGHT: 900,
    canvas: undefined,
    ctx: undefined,
	animationID: 0,
   	lastTime: 0,
	gameState: undefined,
	paused: false,
	
	//Audio stuff
	platforms: undefined,
	character: undefined,
	sound: undefined,
	bg1: undefined,
	bg2: undefined,
	plains: undefined,
	
	powerUp: undefined,
	
	screenS: {},

	//Game State enum
	SCREEN_STATE: Object.freeze({
		GAMEPLAY: 0,
		PAUSE: 1,
		START: 2,
		END: 3,
	}),
	
	//state of screen
	screenState: undefined,
	edo:undefined,
		
    // methods
	init : function() {
	
		//for debugging
		console.log("app.main.init() called");
		
		// initialize properties of canvas
		this.canvas = document.querySelector('canvas');
		this.canvas.width = this.WIDTH;
		this.canvas.height = this.HEIGHT;
		this.ctx = this.canvas.getContext('2d');
		
		//set up background images
		this.bg1 = new Image();
		this.bg2 = new Image();
		this.plains = new Image();
		
		this.bg1.src = "media/orangeMt.png";
		this.bg2.src = "media/pinkMt.png";
		this.plains.src = "media/plains.png";
		
		//initializes modules and globals
		this.platforms.init;
		this.character.init;
		initEnemy();
		initCoin();
		this.sound.init;
		
		//begins screen state add main menu
		this.screenState = this.SCREEN_STATE.START;

		//load level
		this.reset();
		this.drawMainScreen(this.ctx);
		
		// start the game loop
		this.update();
	},
	
	//clears the canvas
	reset: function(){
		this.ctx.fillStyle = "lightblue";
		this.ctx.clearRect(0,0,this.canvas.width,this.canvas.height);
	},
	
	//Draws to screen
	update: function(){
	
		//loops for animation
	 	this.animationID = requestAnimationFrame(this.update.bind(this));
		
		//level goes up every 100 points
		level = Math.floor(score/100);
		console.log(level);
		
		//intro screen (press shift to start)
		if(this.screenState ==  this.SCREEN_STATE.START){
			if(myKeys.keydown[myKeys.KEYBOARD.KEY_SHIFT]){
				this.screenState =  this.SCREEN_STATE.GAMEPLAY;
				this.sound.playBGAudio();
			}
		}
		
		//Game screen
		else if(this.screenState ==  this.SCREEN_STATE.GAMEPLAY){
		
			//Checks for jumping
			this.platforms.gravity(this.sound);
			
			//clears screen
			this.reset();
			
			//draws background
			this.drawBackground(this.ctx);
			
			//updates all enemy animations
			this.updateEnemies();
			
			//draws the platforms
			this.platforms.draw(this.ctx);
			
			//creates new platform
			if(this.platforms.platformLength() < 5 ){
				this.platforms.makePlatform(this.sound);
			}
			
			//draws the character
			this.character.draw(this.ctx, this.platforms.getPlatformState());
			
			//increments the timeKeeper global variable
			clock();
			
			//draws HUD showing score and timer
			this.drawHUD(this.ctx);
			
			//Checks for pause
			if(myKeys.keydown[myKeys.KEYBOARD.KEY_P]){
				this.screenState =  this.SCREEN_STATE.PAUSE;
				this.drawPauseScreen(this.ctx);
			}
			
			//shows death screen
			if(this.platforms.getPlatformState() == 2 || playTimer <= 0 || this.character.getDead()){
				this.screenState = this.SCREEN_STATE.END;
				this.drawDeathScreen(this.ctx);
			}
			
		}
		//Pause menu
		else if(this.screenState ==  this.SCREEN_STATE.PAUSE){
			this.drawPauseScreen(this.ctx);
			return
		}
		//death screen
		else if(this.screenState ==  this.SCREEN_STATE.END){
			if(myKeys.keydown[myKeys.KEYBOARD.KEY_SHIFT]){
				this.restart();
				this.screenState =  this.SCREEN_STATE.GAMEPLAY;
			}
		}
	},
	
	//draws score and timer
	drawHUD: function(ctx){
		ctx.save();
		ctx.textAlign = "right";
		ctx.textBaseline = "middle";
		ctx.fillStyle = "rgba(0, 0, 0, .8)";
		ctx.font = "20px Arial";
		ctx.fillText("Score: " + score, this.WIDTH - 100, 100);
		if(playTimer < 10){ 
			ctx.fillStyle = "red";
		}
		ctx.font = "50px Arial";
		ctx.fillText("" + playTimer, 100, 100);
		
		ctx.restore();
	},
	
	//pause screen
	drawPauseScreen: function(ctx){
		ctx.save();
		ctx.fillStyle = "rgba(255, 255, 255, .5)";
		ctx.fillRect(100, 100,this.WIDTH-200, this.HEIGHT-200);
		ctx.textAlign = "center";
		ctx.textBaseline = "middle";
		ctx.font = '125px "Edo"';
		ctx.fillStyle = "white";
		ctx.fillText("....PAUSED....", this.WIDTH/2, this.HEIGHT/3 - 20);
		ctx.fillStyle = "black";
		ctx.fillText("....PAUSED....", this.WIDTH/2, this.HEIGHT/3);
		ctx.fillStyle = "rgba(0, 0, 0, .8)";
		ctx.font = '55px Arial';
		ctx.fillText("Press 'U' to unpause", this.WIDTH/2, this.HEIGHT/2);
		ctx.fillStyle = "rgba(40, 40, 40, .8)";
		ctx.font = "40px Arial";
		ctx.fillText("Use the left and right arrow keys to move and up to jump.", this.WIDTH/2, this.HEIGHT/2 + 125);
		ctx.fillText("Use space to attack the enemies", this.WIDTH/2, this.HEIGHT/2 + 185);
		ctx.fillText("Fight enemies and collect coins to keep the timer running", this.WIDTH/2, this.HEIGHT/2 + 280);
		
		ctx.restore();
	},
	
	//intro screen
	drawMainScreen: function(ctx){
		ctx.save();
		ctx.fillStyle = "rgba(100, 255, 255, .5)";
		ctx.fillRect(100, 100,this.WIDTH-200, this.HEIGHT-200);
		ctx.textAlign = "center";
		ctx.textBaseline = "middle";
		ctx.fillStyle = "white";
		ctx.font = "110px Edo";
		ctx.fillText("Welcome to Survival Blitsz!", this.WIDTH/2, this.HEIGHT/3 - 20);
		ctx.fillStyle = "black";
		ctx.fillText("Welcome to Survival Blitsz!", this.WIDTH/2, this.HEIGHT/3);
		ctx.fillStyle = "rgba(0, 0, 0, .8)";
		ctx.font = "55px Arial";
		ctx.fillText("Press shift to begin", this.WIDTH/2, this.HEIGHT/2);
		ctx.fillStyle = "rgba(40, 40, 40, .8)";
		ctx.font = "35px Arial";
		ctx.fillText("Use the left and right arrow keys to move and up to jump.", this.WIDTH/2, this.HEIGHT/2 + 125);
		ctx.fillText("Use space to attack the enemies", this.WIDTH/2, this.HEIGHT/2 + 185);
		ctx.fillText("Fight enemies and collect coins to keep the timer running", this.WIDTH/2, this.HEIGHT/2 + 280);
		ctx.restore();
	},
	
	//death screen
	drawDeathScreen: function(ctx){
		ctx.save();
		ctx.fillStyle = "rgba(0, 0, 0, .5)";
		ctx.fillRect(100, 100,this.WIDTH-200, this.HEIGHT-200);
		ctx.textAlign = "center";
		ctx.textBaseline = "middle";
		ctx.fillStyle = "red";
		ctx.font = "125px Edo";
		ctx.fillText("....You have DIED....", this.WIDTH/2, this.HEIGHT/3 - 20);
		ctx.fillStyle = "rgba(0, 0, 0, .8)";
		ctx.fillText("....You have DIED....", this.WIDTH/2, this.HEIGHT/3);
		ctx.fillStyle = "rgba(200, 200, 200, .8)";
		ctx.font = "55px Arial";
		ctx.fillText("Press shift to restart", this.WIDTH/2, this.HEIGHT/2);
		ctx.fillStyle = "rgba(200, 200, 200, .8)";
		ctx.font = "35px Arial";
		ctx.fillText("Use the left and right arrow keys to move and up to jump.", this.WIDTH/2, this.HEIGHT/2 + 125);
		ctx.fillText("Use space to attack the enemies", this.WIDTH/2, this.HEIGHT/2 + 185);
		ctx.fillText("Fight enemies and collect coins to keep the timer running", this.WIDTH/2, this.HEIGHT/2 + 280);
		ctx.restore();
	},
	
	//pauses the game
	pauseGame: function(){
		this.screenState =  this.SCREEN_STATE.PAUSE;
		this.sound.stopBGAudio();
		this.paused = true;
		cancelAnimationFrame(this.animationID);
		
		this.update();
	},
	
	//resumes game
	resumeGame: function(){
		this.screenState =  this.SCREEN_STATE.GAMEPLAY;
		
		cancelAnimationFrame(this.animationID);
		this.sound.playBGAudio();
		this.paused = false;
		this.update();
	},
	
	//resets variables
	restart: function(){
		this.platforms.init();
		playTimer = 30;
		enemies = [];
		coins = [];
		this.character.rst();
		score = 0;
	},

	//cycles through global array of enemies and updates
	updateEnemies: function(){
		for(var i = 0; i < enemies.length; i++){
			enemies[i].update();
		}
	},
	
	//displays background on gameplay
	drawBackground: function(ctx){
		ctx.drawImage(this.bg2,0, 0, 957, 347, -150, 150, 1436, 521);
		ctx.drawImage(this.bg1,0, 0, 957, 347, this.WIDTH - 1350, 150, 1436, 521);
		ctx.drawImage(this.plains,0, 0, 1920, 1080, 0, 630, this.WIDTH, (this.WIDTH * 2) / 3);
	},

}; // end app.main