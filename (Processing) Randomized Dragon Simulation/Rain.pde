//PURPOSE: for individual rain drops

class Rain
{
  //Variables
  float x, y;
  float xPrev, yPrev;
  float xGrav, yGrav;
   
   
  //CONSTRUCTOR
  public Rain()
  {
    //random variables for variety
    x = random(0,width + 60);
    y = 0;
    xGrav = -5;
    yGrav = random(8, 15);
    
  }
   
  //DRAWS TO SCREEN
  void draw()
  {
    //updating variables
    xPrev = x + 5;
    yPrev = y - 20;
    x += xGrav;
    y += yGrav;
    
    //visual of raindrops
    strokeWeight(1.3);
    stroke(100,70);
    fill(100);
    
    line(x, y, xPrev, yPrev);
    ellipse(x,y,1,1);
  }
}