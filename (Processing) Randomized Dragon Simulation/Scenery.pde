//PURPOSE: provide changing background
//------------------------------------

class Scenery{
  
  //Moon shapes
    PShape moon, body, crevice1, crevice2, crevice3, crevice4;
    PShape moon2, body2, c1, c2, c3, c4;
    
    //variables and timing
    float m1x, m1y, m2x;
    float skyFade = 200;
    
    //array for stars
    ArrayList stars = new ArrayList();
  
  //CONSTRUCTOR
   public Scenery(){
     
     //Creates first moon using pieces
       moon = createShape(GROUP);
       
       noStroke();
       fill(color(255, 255, 154, 180));
       body = createShape(ELLIPSE, 0, 0, 100, 100);
       fill(color(255, 255, 204, 100));
       crevice1 = createShape(ELLIPSE, 30, 10, 20, 20);
       crevice2 = createShape(ELLIPSE, -30, -30, 10, 10);
       crevice3 = createShape(ELLIPSE, 30, -10, 5, 5);
       crevice4 = createShape(ELLIPSE, -15, 20, 25, 25);
       
       moon.addChild(body);
       moon.addChild(crevice1);
       moon.addChild(crevice2);
       moon.addChild(crevice3);
       moon.addChild(crevice4);
       
      //Creates second moon using pieces
       moon2 = createShape(GROUP);
       
       noStroke();
       fill(color(255, 255, 154, 180));
       body2 = createShape(ELLIPSE, 0, 0, 60, 60);
       fill(color(255, 255, 204, 100));
       c1 = createShape(ELLIPSE, 12, -5, 10, 10);
       c2 = createShape(ELLIPSE, -15, -20, 5, 5);
       c3 = createShape(ELLIPSE, 25, 10, 5, 5);
       c4 = createShape(ELLIPSE, -10, 20, 15, 15);
       
       moon2.addChild(body2);
       moon2.addChild(c1);
       moon2.addChild(c2);
       moon2.addChild(c3);
       moon2.addChild(c4);
       
       //Variables for moving the moons slowly
       m1x = 100;
       m1y = 100;
       m2x = width-40;
       
       //Generates the stars 1 time
       for(int i = 0; i < 40; i++){
          stars.add(new Star()); 
       }
   }
  
  //DRAW TO SCREEN
  void draw(){
    
    //Moves the moons slowly
    m1x+=.01;
    m1y-=.005;
    m2x-=.005;
    
    //draws all stars to screen
    for(int i = 0; i < stars.size(); i++){
      ((Star)stars.get(i)).draw();
    }
    
    //draws moons
    shape(moon, m1x, m1y);
    shape(moon2, m2x, 30);
    
    //covers the background for fade in and out effects
    fill(5, skyFade);
    rect(0, 0, width, height);
  }
  
}