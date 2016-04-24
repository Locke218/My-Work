//PURPOSE: creates circles to show fire
//-------------------------------------

class Fire
{
  
  //variables
  float x, xRate, y, yRate, rad, fade, fadeRate, radRate;
  float c;
  
  //Constructor - takes in height
  public Fire(float yIn){
    
    //variables
    y = yIn + 10;
    x = width/2 -50;
    rad = 3;
    fade = 255;
    
    //random to change color, fade, and angle for variety
    fadeRate= random(3,10);
    radRate= random(.3,1.4);
    yRate = random(-.7,.7);
    xRate = random(4, 7);
    c = random(0,100);
  }
  
  //updates and draws to screen
  void draw(){
    
      //changing variables for effect
     x+=xRate;
     y+=yRate;
     fade-=fadeRate;
     rad +=radRate;
     
     //the actual visual component
     noStroke();
     fill(255, c, 0, fade);
     ellipse(x, y, rad, rad);
  }
  
  
  
  
}