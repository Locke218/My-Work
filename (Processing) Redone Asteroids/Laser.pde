//Author: Zane Draper
//
//Purpose: The bullets of the ship
//******************************************

class Laser
{
  //movement variables
  PVector position, velocity;
  
  //CONSTRUCTOR
   Laser(float x, float y){
     //initializing movement variables
     position = new PVector(x*5, y*5);
     velocity = new PVector(x * 20, y * 20);
   }
  
  //UPDATES AND DRAWS TO SCREEN
    void draw(PVector shipVelocity){
      //adss velocity and angled velocity
      position.add(velocity);
      position.add(shipVelocity);
      
      fill(0, 200, 0);
      ellipse(position.x, position.y, 5, 5); 
    }
  
}