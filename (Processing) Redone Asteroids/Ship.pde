//Author: Zane Draper
//
//Purpose: Contains visuals and movements for the ship
//******************************************

class Ship
{

  //Movement variables
  PVector position, velocity, angledVelocity, acceleration;

  //basic variables
  float minSpeed, maxSpeed, rotation;
  int score, health, hitCount, exCount;
  color colr = color(240, 240, 240);

  boolean hit = false;
  boolean alive = true;

  //for death scene
  ArrayList explosions;

  //CONSTRUCTOR
  public Ship() {
    //basic variables
    minSpeed = .5;
    maxSpeed = 8;
    rotation = 0;
    hitCount = 0;
    exCount = 0;

    //movement initialization
    position = new PVector(width/2, height/2);
    velocity = new PVector(minSpeed, 0);
    acceleration = new PVector(.05, 0);
    angledVelocity = new PVector(0, 0);

    score = 0;
    health = 100;

    explosions = new ArrayList();
  }

  //DRAWS TO SCREEN
  void draw() {
    //if alive, then it shows ship
    if (alive) {
      fill(colr);
      triangle(position.x, position.y-30, position.x-15, position.y+15, position.x+15, position.y+15);
    } 
    
    //if dead, it shows the explosion
    else {
      
      //it only explodes for a few seconds
      exCount++;
      if (exCount < 100)
        explosions.add(new Explosion());
      
      
      //cycles thorugh explosions
      for (int x = 0; x < explosions.size(); x++) {
        Explosion ex = (Explosion)explosions.get(x);
        ex.draw();
        if (ex.fade <= 0) explosions.remove(x);
      }
    }
  }


  //Acceleration that effects the whole screen
  void accelerate() {
    velocity.add(acceleration);
    velocity.limit(maxSpeed);
  }

  //Decceleration that effects the whole screen
  void deccelerate() {
    if (velocity.x > minSpeed)
      velocity.sub(acceleration);
  }

  //UPDATES THE IMAGE
  void update(boolean f, boolean r, boolean l) {
    
    //checks for death
    if (health <= 0) {
      alive = false;
    }
    
    //immunizes the ship after taking a hit for a short time
    if (hit && hitCount <= 30) {
      hitCount++;
      colr = color(250, 120, 30);
    } else {
      hitCount = 0;
      hit = false;
      colr = color(240, 240, 240);
    }

    //health cannot exceed 100
    if (health > 100) health = 100;

    //checks for rotation and forward momentum
    if (f && alive) {
      accelerate();
    }
    if (!f) {
      deccelerate();
    }
    if (l) {
      rotation += 1;
    } else if (r) {
      rotation -= 1;
    }
    
    //loops rotation
    if (rotation >= 360) rotation = 0;
    else if ( rotation < 0) rotation = 358;

    //trig rotation for everything else
    angledVelocity.y = cos(radians(rotation))*velocity.x;
    angledVelocity.x = sin(radians(rotation))*velocity.x;
  }
}