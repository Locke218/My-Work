//Author: Zane Draper
//
//Purpose: Shows the death of the ship
//******************************************

class Explosion
{
  
  //variables
  
  //movement
  PVector position, velocity;
  float rad, fade, fadeRate, radRate;
  float c;
  
  //CONSTRUCTOR
  public Explosion(){
    
    //sets movement
    position = new PVector(width/2, height/2);
    velocity = new PVector(random(-1, 1), random(-1, 1));
    
    //variables
    rad = 5;
    fade = 255;
    
    //random to change color, fade, and angle for variety
    fadeRate= random(3,5);
    radRate= random(.3,1);
    c = random(0,100);
  }
  
  //updates and draws to screen
  void draw(){
    
      //changing variables for effect
     position.add(velocity);
     fade-=fadeRate;
     rad +=radRate;
     
     //the actual visual component
     noStroke();
     fill(255, c, 0, fade);
     ellipse(position.x, position.y, rad, rad);
  }
  
}