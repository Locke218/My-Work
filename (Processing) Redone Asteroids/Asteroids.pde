//Author: Zane Draper
//
//Purpose: The visual component of the asteroids
//******************************************

class Asteroids
{
  //Variables

  //movement
  PVector position, velocity, direction;

  float radius;
  color colr;

  //CONSTRUCTOR
  public Asteroids(float opt) {
    //initialize velocity and color
    velocity = new PVector(0, 0);
    colr = color(140, 0, 0);

    //randomized radius
    radius = random(40, 100);


    //variation for the asteroids direction and speed
    if ( opt <= 1.75) {
      position = new PVector(random(-width/2, width/2), 0);
      if ( opt < .7) {
        position.y = 650;
        velocity.y = random(-2, 0);
      } else {
        position.y = -650;
        velocity.y = random(0, 2);
      }
      velocity.x = random(-2, 2);
    } else if ( opt > 1.75) {
      position = new PVector(0, random(-height/2, height/2));
      if ( opt < 2.25) {
        position.x = 650;
        velocity.x = random(-2, 0);
      } else {
        position.x = -650;
        velocity.x = random(0, 2);
      }
      velocity.y = random(-2, 2);
    } else if ( opt == 3) {
      position = new PVector(0, 0);
      velocity = new PVector(random(-.5, .5), random(-.5, .5));
    }
  }


  //DRAWS TO SCREEN
  void draw(PVector shipVelocity) {
    
    //Adding personal velocity and angled velocity
    position.add(velocity);
    position.add(shipVelocity);

    //fills current color
    fill(colr);
    
    //circle if large, square if small
    if (radius > 40)
      ellipse(position.x, position.y, radius, radius);
    else {
      pushMatrix();
      translate(position.x, position.y);
      rect(-radius/2, -radius/2, radius, radius);
      popMatrix();
    }
  }
}