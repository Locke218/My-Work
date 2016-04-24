//Author: Zane Draper
//
//Purpose: Shows momentum of the ship
//******************************************

class Afterburn
{
  
  //Variable Declarations
  
  //movement
  PVector position, velocity;
  
  //variables
  float x, xRate, y, yRate, rad, fade, fadeRate, radRate;
  float c;
  
  //Constructor - takes in height
  public Afterburn(float xIn, float yIn){
    
    //variables
    position = new PVector(xIn*-10, yIn*-10);
    rad = 20;
    fade = 255;
    
    //random to change color, fade, and angle for variety
    fadeRate= random(3,10);
    radRate= random(.3,1);
    velocity = new PVector( yIn*random(-.3,.3), xIn*random(-.3, .3));
    
    //xRate = direction.x*random(4, 7);
    c = random(0,100);
  }
  
  //updates and draws to screen
  void draw(PVector shipVelocity){
    
      //changing variables for effect
     position.add(velocity);
     position.add(shipVelocity);
     
     //changing the fade rate
     fade-=fadeRate;
     rad-=radRate;
     
     //the actual visual component
     noStroke();
     fill(c, c, 255, fade);
     ellipse(position.x, position.y, rad, rad);
  }
  
  
  
  
}