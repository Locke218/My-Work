//PURPOSE: creates individual stars
//---------------------------------

class Star
{
    //Variables
    float x, y;  
    float fade;
    
    //creates the star body
    PShape star, center, l1, l2;
    
   //CONSTRUCTOR
   public Star(){
     
     //Creating the star shape
       star = createShape(GROUP);
       
       fade = randomGaussian()*15 + randomGaussian()*40; //uses a Gaussian randomizor for the opaqueness of the stars
       
       //creating body
       strokeWeight(1);
       stroke(250, fade);
       fill(255, 200, 200, fade);
       center = createShape(ELLIPSE, 0, 0, 3, 3);
       l1 = createShape(LINE, -3, 0, 3, 0);
       l2 = createShape(LINE, 0, -4, 0, 4);
       
       star.addChild(center);
       star.addChild(l1);
       star.addChild(l2);
       
       //locations
       x = random(0, width);
       y = random(0, height);
   }
   
   //DRAWS TO SCREEN
   void draw(){
      shape(star, x, y); 
   }
  
}