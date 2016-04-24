//Author: Zane Draper
//
//Purpose: To create the humans

//Extends the vehicle class for movement and obstacle avoidance
class Runner extends Vehicle {

  //PVector Variables
  PVector target = null;
  PVector steeringForce;
  
  //Death check and human image
  Float safeDistance;
  boolean dead;
  PImage human;


  //Constructor
  Runner(float x, float y, float r, float ms, float mf) {
      
    //call the super class' constructor and pass in necessary arguments
    super(x, y, r, ms, mf);

    //instantiate steeringForce vector to (0, 0)
    steeringForce = new PVector(0, 0);

    //creating and sizing the human image
    human = loadImage("human.png");
    human.resize(30, 30);
    
    //setting variables
    safeDistance = 50.00;
    dead = false;
  }

  //Abstract class methods
  
  //Method: calcSteeringForces()
  //Purpose: Based upon the specific steering behaviors this Seeker uses
  //         Calculates all of the resulting steering forces
  //         Applies each steering force to the acceleration
  //         Resets the steering force
  void calcSteeringForces(ArrayList obs) {
      
    //checks for nearest enemies
    steeringForce.sub(flee());
    
    //avoid obstacles
    for(int i = 0; i < obs.size(); i++){
      steeringForce.add(avoidObstacle(((Obstacle)obs.get(i)), safeDistance));
    }
    
    //keeps the npc in frame
    steeringForce.add(checkBounds());
    
    //if innactive, wander
    if(steeringForce.mag() == 0){
      steeringForce.add(wander());
    } 
    
    //limit this seeker's steering force to a maximum force
    steeringForce.limit(mForce);

    //apply this steering force to the vehicle's acceleration
    applyForce(steeringForce);

    //reset the steering force to 0
    steeringForce.set(0,0);
  }
  

  //Method: display()
  //Purpose: Finds the angle this seeker should be heading toward
  //         Draws this seeker as a triangle pointing toward 0 degreed
  //         All Vehicles must implement display
  void display() {
      
    //calculate the direction of the current velocity
    float angle = velocity.heading();   

    //draw this vehicle's body Image using proper translation and rotation
    pushMatrix();
      translate(position.x, position.y);
      rotate(angle);
      image(human, -15, -15);
    popMatrix();
    
    //If in debug mode, draw the forward and right vectors
    if(mode == true){
      stroke(200, 20, 20);
      strokeWeight(2);
      line(position.x, position.y, position.x + 30*forward.x, position.y + 30*forward.y);
      line(position.x, position.y, position.x + 20*right.x, position.y + 20*right.y);
    }
  }
  
  //Checks for nearby enemies and combines the force provided by them
  PVector flee() {
    
    //The reverse of the seek velocity
    PVector fleeVelocity = new PVector(0,0);

    //if within currentDist, then flee to some degree
    float currentDist = 100;
    
    //distance to zombie center
    PVector vecToCenter = new PVector(0, 0);

    //cycle zombies
    for (int i = 0; i < seekers.size(); i++) {

      // Create vecToCenter - a vector from the character to the center of the obstacle
      vecToCenter = (seekers.get(i).position.copy()).sub(position);

      // Find the distance to the obstacle
      Float distance = vecToCenter.mag();
      
      //collision detection
      if (distance < radius*4){
         dead = true; 
      }
      //else flee
      if (distance < currentDist) {
        fleeVelocity.add(seek(seekers.get(i).futurePos()));
      }
    }
    //limits the combined flee force
    fleeVelocity.limit(mSpeed);

    return fleeVelocity;
  }
}