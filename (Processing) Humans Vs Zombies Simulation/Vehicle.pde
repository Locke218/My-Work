//Author: Zane Draper
//
//Purpose: To create template for npc's

abstract class Vehicle {
  
  //vectors for moving a vehicle
  PVector position, acceleration, velocity;
  PVector forward, right;
  PVector wander;
  
  //floats to describe vehicle movement and size
  float mass, radius, mSpeed, obSpeed, mForce, speed, wanderSpeed, last;

  //Constructor
  Vehicle(float x, float y, float r, float ms, float mf) {
    //Basic vectors for movement
    acceleration = new PVector(0,0);
    velocity = new PVector(random(-.1, .1),random(-.1, .1));
    forward = new PVector(0,0);
    right = new PVector(0,0);
    
    //vector for when wondering
    wander = new PVector(0,0);
  
    //Assign parameters to class fields
    position = new PVector(x, y);
    radius = r;
    mSpeed = ms;
    mForce = mf;
    mass = 1;
    speed = 0;
    wanderSpeed = 1;
    last = millis();
  }

  //Abstract methods
  
  //every sub-class Vehicle must use these functions
  abstract void calcSteeringForces(ArrayList obs);
  abstract void display();

  //Class methods
  
  //Method: update()
  //Purpose: Calculates the overall steering force within calcSteeringForces()
  //         Applies movement "formula" to move the position of this vehicle
  //         Zeroes-out acceleration 
  void update(ArrayList obs) {
    
    //calculate steering forces by calling calcSteeringForces()
    calcSteeringForces(obs);
    
    //add acceleration to velocity, limit the velocity, and add velocity to position
    velocity.add(acceleration);
    velocity.limit(speed);
    position.add(velocity);
    
    //calculate forward and right vectors
    forward = (velocity.copy()).normalize();
    right.set(forward.y, -forward.x);
    
    //reset acceleration
    acceleration.set(0,0);
    
    if( mode == true){
      fill(200, 50, 50);
      ellipse(position.copy().x + (forward.copy().mult(mSpeed * time)).x, position.copy().y + (forward.copy().mult(mSpeed * time)).y, 5, 5);
    }
  }

  
  //Method: applyForce(force vector)
  //Purpose: Divides the incoming force by the mass of this vehicle
  //         Adds the force to the acceleration vector
  void applyForce(PVector force) {
    acceleration.add(PVector.div(force, mass));
  }
  
  //Steering Methods
  
  //Method: seek(target's position vector)
  //Purpose: Calculates the steering force toward a target's position
  PVector seek(PVector target){
    
    //Calculation for speed and arrival (lowers speed on approach)
    speed = target.dist(position)/20;
    if(speed > mSpeed) speed = mSpeed;
      
    //write the code to seek a target!
    PVector desiredVelocity = new PVector(0,0);
    
    //vector to desired object
    desiredVelocity = (target.copy()).sub(position);
    
    (desiredVelocity.normalize()).mult(mSpeed);
    
    //Getting the difference
    PVector steeringForce = desiredVelocity.sub(velocity);
    
    return steeringForce;

  }
  
  //Method intended to avoid environmental obstacles
  PVector avoidObstacle (Obstacle obPos, float safeDistance) {
    PVector steer = new PVector(0, 0);
    
      // Create vecToCenter - a vector from the character to the center of the obstacle
      PVector vecToCenter = (obPos.position.copy()).sub(position);
      
      // Find the distance to the obstacle
      Float distance = vecToCenter.mag();
      
      // Return a zero vector if the obstacle is too far to concern us
      // Use safe distance to determine how large the “safe zone” is
      if(sqrt(sq(distance)) > safeDistance+obPos.radius/2){
         return new PVector(0,0); 
      }
      
      // Return a zero vector if the obstacle is behind us
      // (dot product of vecToCenter and forward is negative)
      if((vecToCenter.dot(forward)) < 0 ){
         return new PVector(0,0); 
      }
      
      // Use the dot product of the vector to obstacle center (vecToCenter) and the unit vector
      // to the right (right) of the vehicle to find the distance between the centers
      // of the vehicle and the obstacle
      // Compare this to the sum of the radii and return a zero vector if we can pass safely
      Float rightDist = vecToCenter.dot(right);
      
      if(rightDist > (obPos.radius + 15)){
         return new PVector(0,0); 
      }
      
      // If we get this far we are on a collision course and must steer away!
      // Use the sign of the dot product between the vector to center (vecToCenter) and the
      // vector to the right (right) to determine whether to steer left or right
      
      // For each case calculate desired velocity using the right vector and maxSpeed
      PVector desiredVel = new PVector(0,0);
      if(rightDist > 0) {
         desiredVel = right.mult(-mSpeed*2); 
      }
      else {
         desiredVel = right.mult(mSpeed*2); 
      }
      
      // Compute the force required to change current velocity to desired velocity
      steer = PVector.add(desiredVel, velocity);
      
      // Consider multiplying this force by safeDistance/dist to increase the relative weight
      // of the steering force when obstacles are closer.
      //steer.mult(safeDistance/rightDist);
      
    return steer;
  }
  
  //Keep the npc in the frame
  PVector checkBounds(){
    //Vectors for steering away from the outside
    PVector steer = new PVector(0,0);
    PVector center = new PVector(width/2, height/2);
    
    //checks for out of bounds
    if(position.x >= width - 50 || position.x <= 50 || position.y >= height - 50 || position.y <= 50){
      PVector desiredVelocity = center.sub(position);
      
      //get and regulate the wander so we don't keep heading towards the outside
      wander = desiredVelocity.copy().normalize().mult(10);
      
      //create seperate steering for for when not wandering
      (desiredVelocity.normalize()).mult(mSpeed*2);
    
      //return the desired force
      steer = desiredVelocity.add(velocity);
      
    }
    
    return steer;
  }
  
  //Method for wandering when not in/being pursued
  PVector wander(){
    //Force of the wander
    PVector wanderF = new PVector(0,0);
    
    //checks for initializing wander vector
    if(wander.x == 0 && wander.y == 0){
     PVector baseV;
     
     //creates a vector and then randomly rotates it
     wander = new PVector(10,0);
     wander.rotate(random(0, 360));
     
     //move the wander away from the origin point
     baseV = PVector.add(wander, position);
     
     //now use seek to move in the direction desired
     wanderF.add(seek(baseV));
    }
    //every few times per second turn one way or another
    else if( (millis() - last) > 400){
     PVector baseV;
     
     //grabs the forward vector
     wander = forward.copy().mult(10);
     
     //rotates it a little for a turn
     wander.rotate(random(-.3, .3));
     
     //moves this new wander away from the origin
     baseV = PVector.add(wander, position);
     
     //seek that point
     wanderF.add(seek(baseV));
     
     //update for time keeping
     last = millis();
    }
    else{
      
     //the rest of the time we just head for the wander point
     PVector baseV = PVector.add(wander, position);
     
     wanderF.add(seek(baseV));
    }
    
    return wanderF;
  }
  
  
  //Returns the future position for evade and pursue
  PVector futurePos(){
    
    PVector futurePos = PVector.add(position.copy(), forward.copy().mult(5 * time));
    
    if(mode == true){
      fill(20, 200, 10);
      ellipse(futurePos.x, futurePos.y, 10, 10);
    }
    
    return futurePos;
  }
}