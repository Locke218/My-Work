//AUTHOR: Prof. Anthony Jefferson
//
//PURPOSE: Setting up the .sound module for audio
//
//***************************************************************
//***************************************************************

"use strict";

var app = app || {};

// define the .sound module and immediately invoke it in an IIFE
app.sound = (function(){

	//Output for debugging
	//console.log("sound.js module loaded");
	
	//Variables
	var bgAudio = undefined;
	var effectAudio = undefined;
	var currentEffect = 0;
	var currentDirection = 1;
	var jumpEffect = "media/jump.mp3";
	var coinEffect = "media/coin.ogg";
	
	//initializes audio variables
	function init(){
		bgAudio = document.querySelector("#bgAudio");
		bgAudio.volume=0.1;
		effectAudio = document.querySelector("#effectAudio");
		effectAudio.volume = 0.06;
	}
		
	//Stops audio while paused or in menu
	function stopBGAudio(){
		bgAudio.pause();
		bgAudio.currentTime = 0;
	}
	
	//plays an audio effect based on text input
	function playEffect(effectName){
		//Jump sound effect
		if(effectName == "jump"){
			effectAudio.src = jumpEffect;
		}
		//Coin pickup sound effect
		else if(effectName =="coin"){
			effectAudio.src = coinEffect;
		}
		//plays sound 
		effectAudio.play();
	}
	
	//Resumes background music
	function playBGAudio(){
		bgAudio.play();
	}
	
	//sets up function calls
	return{
		init:init,
		stopBGAudio: stopBGAudio,
		playEffect: playEffect,
		playBGAudio: playBGAudio,
	};
}());