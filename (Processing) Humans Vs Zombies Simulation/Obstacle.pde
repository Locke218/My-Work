//Author: Zane Draper
//
//Purpose: To create obstacles on the map

class Obstacle
{
  //Variables
  float radius;
  PVector position;
  PImage tree;

  //Constructor
  public Obstacle(float x, float y) {
    //Varying sizes
    radius = random(80, 150);

    //Initializing other variables
    position = new PVector(x, y);
    tree = loadImage("tree.png");
    tree.resize((int)radius, (int)radius);
  }

  //Draw To screen
  void display() {

    //Draws the image in the right location
    pushMatrix();
      translate(position.x, position.y);
      image(tree, -radius/2, -radius/2);
    popMatrix();
  }
}