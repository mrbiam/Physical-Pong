

float xPos = 0.0;
float yPos = 0.0;

float xVel = 0.0;
float yVel = 0.0;

float maxDirSpeed = 5;

float backgroundColor = 255;


void setup() {
  size(200, 200);
  background(backgroundColor); //White Background
  
  xPos = random(width-50) + 50;
  yPos = random(height-50) + 50;
  
  xVel = random(maxDirSpeed*2) - maxDirSpeed/2.0;
  yVel = random(maxDirSpeed*2) - maxDirSpeed/2.0;
}

void draw() {
  background(backgroundColor);
  
  ellipse(xPos, yPos, 10, 10);
  
  xPos = xPos + xVel;
  yPos = yPos + yVel;
  
  if (xPos <= 0) {
    xVel = -1 * xVel;
    xPos = 0; 
  } else if (xPos >= width) {
    xVel = -1 * xVel;
    xPos = width;
  }
  
  if (yPos <= 0) {
    yVel = -1 * yVel;
    yPos = 0; 
  } else if (yPos >= height) {
    yVel = -1 * yVel;
    yPos = height;
  }
  
  println(xVel, ", ", yVel,";");
}