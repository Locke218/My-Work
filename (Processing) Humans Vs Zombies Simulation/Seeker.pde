//Author: Zane Draper
//
//Purpose: To create the zombies

//Extended from Vehicles for movement and such
class Seeker extends Vehicle {

  //seeking target
  //set to null for now
  PVector target = null;

  //overall steering force for this Seeker accumulates the steering forces
  //  of which this will be applied to the vehicle's acceleration
  PVector steeringForce;

  //safeDistance and zombie image
  Float safeDistance;
  PImage zombie;

  //Constructor
  Seeker(float x, float y, float r, float ms, float mf) {

    //call the super class' constructor and pass in necessary arguments
    super(x, y, r, ms, mf);

    //instantiate steeringForce vector to (0, 0)
    steeringForce = new PVector(0, 0);

    //setting up zombie image
    zombie = loadImage("zombie.png");
    zombie.resize(30, 30);
    safeDistance = 50.00;
  }

  //Abstract class methods

  //Method: calcSteeringForces()
  //Purpose: Based upon the specific steering behaviors this Seeker uses
  //         Calculates all of the resulting steering forces
  //         Applies each steering force to the acceleration
  //         Resets the steering force
  void calcSteeringForces(ArrayList obs) {

    //checks chase for the index of closest human
    int l = 0;
    if ((l = chase()) != 100) {

      //if in debug mode, display red line
      stroke(200, 50, 50);
      if (mode == true)
        line(runners.get(l).position.x, runners.get(l).position.y, futurePos().x, futurePos().y);

      //direct zombie towards human
      steeringForce.add(seek(runners.get(l).futurePos()));
    }

    //gets force from obstacle avoidance
    for (int i = 0; i < obs.size(); i++) {
      steeringForce.add(avoidObstacle(((Obstacle)obs.get(i)), safeDistance));
    }

    //if innactive wander
    if (steeringForce.mag() == 0) {
      steeringForce.add(wander());
    } 

    //remain in bounds
    steeringForce.add(checkBounds());

    //limit this seeker's steering force to a maximum force
    steeringForce.limit(mForce);

    //apply this steering force to the vehicle's acceleration
    applyForce(steeringForce);

    //reset the steering force to 0
    steeringForce.set(0, 0);
  }


  //Method: display()
  //Purpose: Finds the angle this seeker should be heading toward
  //         Draws this seeker as a triangle pointing toward 0 degreed
  //         All Vehicles must implement display
  void display() {

    //calculate the direction of the current velocity
    float angle = velocity.heading();   

    //draw this vehicle's body PShape using proper translation and rotation
    pushMatrix();
    translate(position.x, position.y);
    rotate(angle);
    image(zombie, -15, -15);
    popMatrix();

    //if in debug mode, show linking lines
    if (mode == true) {
      stroke(200, 20, 20);
      strokeWeight(2);
      line(position.x, position.y, position.x + 30*forward.x, position.y + 30*forward.y);
      line(position.x, position.y, position.x + 20*right.x, position.y + 20*right.y);
    }
  }

  //checks for closest human to pursue
  int chase() {

    //variables
    float currentDist = 100;
    int currentTarget = 100;
    PVector vecToCenter = new PVector(0, 0);

    stroke(50, 50, 200, 40);

    for (int i = 0; i < runners.size(); i++) {

      // Create vecToCenter - a vector from the character to the center of the obstacle
      vecToCenter = (runners.get(i).position.copy()).sub(position);

      //if in debug mode, show lines to all humanspp
      if (mode == true) {
        line(position.x, position.y, runners.get(i).futurePos().x, runners.get(i).futurePos().y);
      }

      // Find the distance to the obstacle
      Float distance = vecToCenter.mag();

      //shows which human is closest
      if (distance < currentDist) {
        currentDist = distance;
        currentTarget = i;
      }
    }

    return currentTarget;
  }
}