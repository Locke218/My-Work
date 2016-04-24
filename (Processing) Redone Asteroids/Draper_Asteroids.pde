//Homework: #2 Asteroids
//Author: Zane Draper
//
//Purpose: Main class, runs the program
//******************************************

//Variable Declarations
float last;
float xVel, yVel;

//Main Ship
Ship ship;

//Arrays for large number of occurances
ArrayList asteroids;
ArrayList shots;
ArrayList exhaust;
ArrayList highscores;

//For button presses and play mode
boolean forward;
boolean left, right;
boolean fire;
boolean play;

//Included font
PFont font;

//File IO
BufferedReader reader;
String line;

//MAIN SETUP FUNCTION
void setup(){
  size(1000, 1000);
  
  //Included font
  font = loadFont("Pokemon_RS-48.vlw");
  
  //Reading in highscores file
  ReadHighscores();
  
  //Resets everything
  Initialize();
}

//Draws Everything to the Screen
void draw(){
  
  //Moves between menu and gameplay
  if(!play) MenuMode();
  else GameMode();  
}


//MODE FOR GAMEPLAY
void GameMode(){
  background(10);
  
  //Keeps track of number of asteroids being moved in game
  if(asteroids.size() >= 250){
     asteroids.remove(0); 
  }
  
  //Keeps ship updated with button presses
  ship.update(forward, right, left);
  
  //Spawns a new asteroids every certain number of milliseconds
  if( millis() - last > 300){
     asteroids.add(new Asteroids(random(0, 3)));
     last = millis();
  }
  
  //The trail given by the ship moving
  exhaust.add(new Afterburn(-sin(radians(ship.rotation)), -cos(radians(ship.rotation))));
  
  
  //line(width/2 - 50, height/2, width/2 + 50, height/2);
  
  //First matrix for rotation exhaust below the ship
  pushMatrix();
  
    translate(width/2, height/2);
    rotate(radians(ship.rotation));
    
    //Only called if ship is alive
    if(ship.alive){
      for( int k = 0; k < exhaust.size(); k++){
         Afterburn r = ((Afterburn)exhaust.get(k));
         r.draw(ship.angledVelocity); 
         if(r.fade <= 0) exhaust.remove(k);
      }
    }
    
  popMatrix();
  
  //Draws ship to screen
  ship.draw();
  
  //Second matrix (same rotation) for asteroids above ship
  pushMatrix();
  
    translate(width/2, height/2);
    rotate(radians(ship.rotation));
    
    //Cycles through asteroids
    for( int k = 0; k < asteroids.size(); k++){
       Asteroids asteroid = ((Asteroids)asteroids.get(k));
       asteroid.draw(ship.angledVelocity); 
       
       //Checks for collision with other objects
       if(Collision(asteroid) && (asteroid.position.x < 800 && asteroid.position.x > -800 && asteroid.position.y < 800 && asteroid.position.y > -800)){
          asteroids.remove(k); 
       }
    }
    
    //Cycles through shots
    for( int k = 0; k < shots.size(); k++){
       Laser r = ((Laser)shots.get(k));
       r.draw(ship.angledVelocity); 
       if(r.position.y < -800 || r.position.y > 800 || r.position.x > 800 || r.position.x < -800) shots.remove(k);
    }
  
    //line(-50, 0, 50, 0);
    
  popMatrix();
  
  //PRinting score and health to screen
  fill(100, 100, 200);
  textSize(25);
    text("Score: " + ship.score, 10, 40);
  
  if(ship.health > 100) ship.health = 100;
  
  text("Health: " + ship.health + "%", width - 130, 40);
  
  //Checks for end of game scenario
  if(ship.explosions.size() == 0 && ship.exCount >=100){
    SaveScore();
    play = false;
  }
}


//WHEN IN MAIN MENU MODE
void MenuMode(){
  background(10);  
  
  //Main menu text
  fill(200, 0,0);
  textFont(font, 48);
  textSize(120);
      text("Asteroids 2:", width/2 - 250, height/3);
  fill(140, 0,0);
  textSize(70);
      text("Meteor Miner", width/2 - 80, height/3+70);
  textSize(30);
      text("HighScores:", width/2 - 80, height/3+170);
  stroke(140, 0,0);
      line(width/2-80, height/3+175, width/2+50, height/3+175);
  textSize(30);
      text("Click anywhere to begin", width/2-130, height/2 + 400);
  
  //prints all highscores to the screen
  for(int i = 0; i < highscores.size(); i++){
    if((int)highscores.get(i) == ship.score){
      fill(0, 0, 200);
    }
    else fill(0, 200, 0);
    textSize(30);
    text(" " + highscores.get(i), width/2 - 30, height/3+220+(i *40));
  }
}


//Checks for when certain keys are pressed down
void keyPressed(){
  //Movement and rotation
    if( key == 'a') left = true;
    else if( key == 'd') right = true;
    else if( key == 'w') forward = true;
    
  //Firing
    if( key == ' '){ 
      if(fire == true){
        shots.add(new Laser(-sin(radians(ship.rotation)), -cos(radians(ship.rotation))));
        fire = false;
      }
    }
}

//When on main menu, starts game
void mouseClicked(){
   Initialize();
   play = true;
}



//Resets variables when certain keys are released
void keyReleased(){
    if( key == 'a') left = false;
    else if( key == 'd') right = false;
    else if( key == 'w') forward = false;
    
    if( key == ' ') fire = true;
}


 //CHECKS COLLISION BETWEEN OBJECTS
boolean Collision(Asteroids current){
  float distance;
  float distance2;
   
  //Collision bettwen asteroids and shots
  for(int i = 0; i < shots.size(); i++){
   Laser l = (Laser)shots.get(i);
    
   //calculates distance between centers
   distance = sqrt(pow((l.position.x - current.position.x), 2) + pow((l.position.y - current.position.y), 2));
      
   //if touching
   if(distance <= (current.radius + 5)/2){
     
     //removes shot
     shots.remove(i);
     
     //if larger, if breaks into smaller pieces
     if(current.radius > 40){
       
         Asteroids a;
         
         //creates four new pieces
         for(int o = 0; o < 4; o++){
           a = new Asteroids(3);
           a.position = new PVector(current.position.x, current.position.y);
           a.velocity = new PVector(current.velocity.x+a.velocity.x, current.velocity.y+a.velocity.y);
           a.radius = current.radius/2;
           if(a.radius < 40) a.colr = color(0,0, 200);
           asteroids.add(a);
         }
         //destroys original
         return true;
     }
     //destroys original
     else return true;
   }
  }
  
  //distance from ship
  distance = sqrt(pow((-5 - current.position.x), 2) + pow((0- current.position.y), 2));
  //distance from tip
  distance2 = sqrt(pow((0 - current.position.x), 2) + pow((-25- current.position.y), 2));
  
  //if touching
  if((distance <= (current.radius + 22)/2) || (distance2 <= (current.radius + 4)/2)){
    
    //if the ship isnt already hit and blue square adds health and score
    if(current.radius < 40 && !ship.hit){
      ship.score += 10*(int)current.radius;
      ship.health += (int)(current.radius/2);
      return true;
    }
    
    //otherwwise the ship takes a hit
    else if(!ship.hit){
      ship.health -= (int)(current.radius/2);
      ship.hit = true;
      
     Asteroids a;
     
     //the larger asteroid breaks into smaller pieces
     for(int o = 0; o < 4; o++){
       a = new Asteroids(3);
       a.position = new PVector(current.position.x, current.position.y);
       a.velocity = new PVector(current.velocity.x+a.velocity.x, current.velocity.y+a.velocity.y);
       a.radius = current.radius/2;
       if(a.radius < 40) a.colr = color(0,0, 200);
       asteroids.add(a);
     }
     //destroys original
     return true;
    }
  }
  //no collision
  return false;
}

//SETS AND RESETS VARIABLES
void Initialize(){
  
  //initializing variables
  ship = new Ship();
  asteroids = new ArrayList();
  shots = new ArrayList();
  exhaust = new ArrayList();
  
  //sets other variables
  last = millis();
  forward = false;
  left = false;
  right = false;
  fire = true;
  play = false;
}


//READS THE HIGHSCORE FILE
void ReadHighscores(){
  highscores = new ArrayList();
  
  //finds the text file
  reader = createReader("HighScores.txt");
  
  //Checks for info while watching for errors
  try {
    while((line = reader.readLine()) != null){
      highscores.add(Integer.parseInt(line));
    }
  } catch (IOException e) {
    
  }
  
}

//SAVING SCORE AT END OF GAME
void SaveScore(){
    
  //Checks to see if score is high enough and places it in the right spot
    for(int j = 0; j < highscores.size(); j++){
      
      if(ship.score > (int)highscores.get(j) ){
        
      ArrayList newScores = new ArrayList();
      
        for(int k = 0; k < j; k++){
          newScores.add((int)highscores.get(k));
        }
        
          newScores.add(ship.score);
        for(int k = j + 1; k < highscores.size(); k++){
          newScores.add((int)highscores.get(k - 1));
        }
        
        highscores = new ArrayList();
        for(int k = 0; k < 5; k++ ){
          highscores.add((int)newScores.get(k));
        }
        break;
      }
    }
    
    //Outputs new (or old) highscores
    PrintWriter output = createWriter("HighScores.txt");
    for(int k = 0; k < highscores.size(); k++){
       output.println((int)highscores.get(k)); 
    }
    output.flush();
    output.close();
}