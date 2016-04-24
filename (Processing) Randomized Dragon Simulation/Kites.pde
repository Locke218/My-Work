//PURPOSE: shows passing kites

class Kites
{
  //Variables
  
  //Custom shpae
  PShape kite;
  
  float r, g, b, size;
  float x, y, ti, yArea, xSpeed, scl;
  
  public Kites(int m ){
    
    //time component
    ti = 0;
    
    //random colors
    r = randomGaussian()*45 +150;
    g = randomGaussian()*45 +150;
    b = randomGaussian()*45 +150;
    
    //changes size, speed based on background/front position
    if(m == 1){
      x = width + 100;
      xSpeed = randomGaussian()*1 + 3;
      yArea = random(220, 400);
      scl = random(1, 2);
    }
    else if(m == 2){
      x = width + 100;
      xSpeed = randomGaussian()*1 + 2;
      yArea = random(20, 200);
      scl = random(.3, .8);
    }
    
    //components of visual kite
    fill(r, g, b, 200);
    stroke(200, 200, 200, 180);
    
    kite = createShape();
    kite.beginShape();
      kite.vertex(-50, -25);
      kite.vertex(-15, -15);
      kite.vertex(25, 25);
      kite.vertex(-25, 10);
    kite.endShape(CLOSE);
    
    
  }
  
  //DRAWS TO SCREEN
  void draw(){
    
    //colors lines
    fill(155, 0, 155, 200);
    stroke(200, 200, 200, 180);
    
    //varies height for effect
    y = yArea + ((noise(ti)*30)-15);  //perlin
    ti += .01;
    
    //translates left
    x-=xSpeed;
    
    //movement and scale for kite
    pushMatrix();
          
      translate(x, y);
      scale(scl);
      shape(kite, 0, 0);
      line(-50, -25, 25, 25);
      line(-15, -15, -25, 10);
    popMatrix();
    
    //kite string
      line(x, y, x-100, 400);
  }
  
}