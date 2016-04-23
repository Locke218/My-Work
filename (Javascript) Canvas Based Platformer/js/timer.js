//AUTHOR: Zane Draper (ME)
//
//PURPOSE: Setting up the main character's animation and interaction
//
//***************************************************************
//***************************************************************

"use strict";

console.log("timer.js module loaded");

var lastTime = 0;	
var playTimer = 30;
var timeKeeper = 0;
var score = 0;
var level = 0;

//time between frames
function deltaTime(){
	var now,fps;
	now = (+new Date); 
	fps = 1000 / (now - this.lastTime);
	fps = clamp(fps, 12, 60);
	
	this.lastTime = now; 
	return 1/fps;
}

//returns play timer
function getPlayTimer(){
	return playTimer;
}

//basically the update method (wanted to be clever with naming)
function clock(){
	timeKeeper++;
	
	if(timeKeeper%60 == 0){
		playTimer--;
		if(timeKeeper == 120) timeKeeper = 0;
		if(playTimer <0) playTimer = 0;
	}
}