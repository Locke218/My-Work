//PURPOSE: Creates and maintains main kite
//----------------------------------------


class Dragon
{
  
  //Variables
  float t = 0.0;
  float[] midH = new float[15];
  float outputVal;
  float noiseScale = .01;
  int l;
  boolean open;
  float last;
  float fireTime, tillNxtFire;

  //Arrays
  ArrayList fire;
  
  //Parts of the images
  PImage img, img2, img3, img4;


  //CONSTRUCTOR
  public Dragon(  ) {

    //Sets timing variables
    fireTime = 800;
    tillNxtFire = millis() + random(800, 2500);
    l = 0;
    open = true;

    //Loads parts of dragons
    img = loadImage("dragonBody.png");
    img2 = loadImage("dragonTail.png");
    img3 = loadImage("dragonHeadTop.png");
    img4 = loadImage("dragonHeadBottom.png");
    
    //Prepares Arrays
    fire = new ArrayList();

    //sets starting times for y locations
    for (int i=0; i < midH.length; i++) {
      midH[i] = 0.0;
    }
  }

  //DRAWS TO SCREEN
  void Draw() {

    //Creates the kite string
    strokeWeight(1);
    fill(255, 255, 255, 255);
    stroke(255, 255, 255, 150);
    line(0, 500, width/2 - 100, midH[0]);
    line(0, 500, width/2-175, midH[5]);

    //Draws the dragon to screen
    for (int i = midH.length - 1; i >= 0; i--) {
      if (i == 0) {
        Head(img3, img4, midH[i]); //Special function for the head
      } 
      else if (i == midH.length-1) image(img2, width/2-(20*i)-120, midH[i]);
      else image(img, width/2-(20*i) - 100, midH[i]);
    }

    float xoff = t;

    //Sets the y location of the body parts
    for (int i = 0; i < width; i++) {
      float y = noise(xoff)*height;    //Sets location using PERLIN for smoothness

      for (int j = 0; j < midH.length; j++) {
        if ( i == width/2 - (j*2) ) {
          midH[j] = y;
        }
      }
      xoff += 0.01;

    }

    //moves time forward for PERLIN
    t += 0.01;


    //when active, it draws fire to the screen
    for (int i = 0; i < fire.size(); i++) {
      Fire r = ((Fire)fire.get(i));
      r.draw();
      if (r.x > width) {
        fire.remove(i);
      }
    }
  }

  //Provides rotation of head for dragon
  void Head(PImage img1, PImage img2, float i) {

    BreatheFire(); //when jaw is open, fire is created

    //Rotated bottom jaw
    pushMatrix();
      translate(width/2-90, i-10);
      rotate(radians(l));
      image(img2, -40, -52);
    popMatrix();
    
    //rotates top jaw
    pushMatrix();
      translate(width/2-80, i);
      rotate(radians(-l));
      image(img1, -45, -63);
    popMatrix();
  }

  //CREATES FIRE WHEN NEEDED
  void BreatheFire() {
    
    //If jaw is opening fire is being created
    if ( open && millis() >= tillNxtFire) {
      l++;
      fire.add(new Fire(midH[0]));
      fire.add(new Fire(midH[0]));
      if ( l >= 20) {
        open = false;
        fireTime = millis() + random(500, 1200);
      }
    } 
    
    //if closing, fire stops
    else if ( !open && millis() >= fireTime ) {
      l--;
      if ( l <= 0) {
        open = true;
        tillNxtFire = millis() + random(1000, 3000);
      }
    } 
    
    //if jaw is open, fire continues
    else if (!open) {
      fire.add(new Fire(midH[0])); 
      fire.add(new Fire(midH[0]));
    }
  }
}