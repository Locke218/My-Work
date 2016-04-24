//Author: Zane Draper
//
//Purpose: To run the main game logic

//Arrays need for repetitive objects
ArrayList<Runner> runners;
ArrayList<Seeker> seekers;
ArrayList obstacles;

//Debug mode and Background image
boolean mode;
PImage bg;

//Tells how far ahead the pursue and evade look
int time;

//Initialize everything
void setup() {
  size(1000, 1000);
  
  //Initialize arrays
  runners = new  ArrayList<Runner>();
  seekers = new  ArrayList<Seeker>();
  
  //Populate the arrays with npc
  for(int i = 0; i < 5; i++){
    runners.add(new Runner(random(30, width-30), random(30, height-30), 6, 1.05, 0.4));
  }
  for(int i = 0; i < 8; i++){
    seekers.add(new Seeker(random(30, width-30), random(30, height-30), 6, 1, 0.1));
  }
  
  //Creates obstacles on the map
  obstacles = new ArrayList();
  obstacles.add(new Obstacle(200, 450)); 
  obstacles.add(new Obstacle(600, 800)); 
  obstacles.add(new Obstacle(500, 200)); 
  obstacles.add(new Obstacle(800, 500)); 
  obstacles.add(new Obstacle(600, 100)); 
  
  //Sets the background image
  bg = loadImage("grass.png");
  time = 4;
  
}

//Draws everything to the screen
void draw() {
  //clears image
  background(bg);
  
  //draws eclipse at mouse location
  fill(50, 50, 200);
  ellipse(mouseX, mouseY, 20, 20);
  
  //Update and Draw the npcs
  for(int i = 0; i < runners.size(); i++){
    runners.get(i).update(obstacles);
    runners.get(i).display();
  }
  
  for(int i = 0; i < seekers.size(); i++){
    seekers.get(i).update(obstacles);
    seekers.get(i).display();
  }
  
  //displays obstacles
  for(int i = 0; i < 5; i++){
     ((Obstacle)obstacles.get(i)).display(); 
  }
  
  //checks for Zombie/Human collision
  zombieSpawn();
}

//Spawn Human at mouse click location
void mouseClicked(){
   humanSpawn(mouseX, mouseY);
}

//Use P to turn debug on and off
void keyPressed(){
   if(key == 'p'){
     if(mode == true)
        mode = false;
     else mode = true;
   }
}

//On Collision, destroy human and create zombie
void zombieSpawn(){
    for(int i = 0; i < runners.size(); i++){ //Check for death variable
       if(runners.get(i).dead == true){
         seekers.add(new Seeker(runners.get(i).position.copy().x, runners.get(i).position.copy().y, 6, 1, 0.1));
         runners.remove(i);
       }
    }
}

//On click spawn a new human npc
void humanSpawn(float x, float y){
    runners.add(new Runner(x, y, 6, 1, 0.1));
}