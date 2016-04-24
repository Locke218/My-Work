//HMWK #1 Rolling on Random
//By Zane Draper

//I had a slight confusion of dates, so this Project will be using 1 of my GRACE DAYS. Thank you.


//PURPOSE: Set up and display Project
//------------------------------------


//DECLARING ASSETS

Dragon dragon;  //Main Kite
Scenery scene;  //Provides Background


//Arrays for re-occuring objects
ArrayList rain;
ArrayList kites;
ArrayList kites2;

//Variables for manipulating timing and effects
float last;
float rainFrequency;
float t = 0.0;
float weatherTime;
float kiteTime;
boolean raining;

//INITIALIZATION of PROJECT
void setup() {
  
  //Basic stuff
  size(800, 400);
  smooth();
  
  //Custom Classes - no input
  dragon = new Dragon();
  scene = new Scenery();
  
  //Arrays
  kites = new ArrayList();
  kites2 = new ArrayList();
  rain = new ArrayList();
  
  //Basic timing variables
  raining = true;
  last = 0;
  weatherTime = millis() + 8000;
  kiteTime = millis() + 600;
}


void draw() {
  
  //Clearing Background
  background(color(0, 0, 30));

  //Draws the background
  scene.draw();
  
  //Cycles through background kites (for depth effect)
  for(int k = 0; k < kites2.size(); k++){
     Kites kite = (Kites)kites2.get(k);
     kite.draw(); 
     if(kite.x <= -100 || kite.x >= width+400){ //Removes if off screen
        kites2.remove(k);
     }
  }

  //Main Kite - drawn between kite layers
  dragon.Draw();
  
  //Cycles through top kite layer (for depth effect)
  for(int k = 0; k < kites.size(); k++){
     Kites kite = (Kites)kites.get(k);
     kite.draw(); 
     if(kite.x <= -100 || kite.x >= width+400){ //Removes if off screen
        kites.remove(k);
     }
  }
  
  //Timing for creating kite
  KitePopulate();

  //Controls Rain pattern
  Weather();

}

//CONTROLS RAIN AND BACKGROUND
void Weather(){
    
    //Allows rain to fall and fade out when ending
    if( raining ){
      if(millis() > weatherTime){ //must overcome a random gap of time
        raining = false;
        weatherTime = millis() + map(noise(t), 0, 1, 10000, 20000);  //Uses PERLIN noise to decide time gap
      }
       RainGenerator(); //Makes the rain fall
       
      if( scene.skyFade < 200) scene.skyFade+=.5; //Fades the color of the background for Transistion
    }
    
    //Allows for fade in of Rain when starting
    else if( !raining ){
      if( scene.skyFade > 1){ //Fades the color of the background in transistion
        scene.skyFade-=.5;
       RainGenerator(); //lets rain fall for certain amount of time
        
      }
      
      //Changes variables to allow rain
      if(millis() > weatherTime){
        raining = true;
        weatherTime = millis() + map(noise(t), 0, 1, 10000, 20000);  //Uses PERLIN noise to decide time gap
      }
      
    }
}


//ADDS RAIN TO RAIN ARRAY
void RainPopulate() {
  float i = random(1, scene.skyFade/20); //Decide on number of rain to produce at once

  for (int k = 0; k < i; k++) {
    rain.add(new Rain()); //Adds rain to array
  }
}


//Times the gap between producing rain for calmer moments
void RainGenerator() {

  rainFrequency = (noise(t)*height)/5;   //Uses PERLIN noise

  t += .001; //Moves time forward for Perlin

  if (millis()-(last+rainFrequency)>0) { //populates rain when time gap has passed
    RainPopulate(); 
    last = millis();
  }
  
  //Removes and draws rain when needed
  for (int i = 0; i < rain.size(); i++) {
    Rain r = ((Rain)rain.get(i));
    r.draw();
    if (r.y > height) {
      rain.remove(i);
    }
  }
}

//ADDS KITES TO SCENE
void KitePopulate(){
  if( millis() >= kiteTime){ //When time gap has passed
      float m = random(0,3);  //Decides if kite is in front or back
      if(m <= 1){
         kites.add(new Kites(1)); //adds kite to front
      }
      if(m >= 2){
         kites2.add(new Kites(2)); //adds kite to background
      }
     kiteTime = millis() + (randomGaussian()*200 + 4000); //Uses GAUSSIAN to decide the next time gap for relative consistency
  }
  
  
  
}