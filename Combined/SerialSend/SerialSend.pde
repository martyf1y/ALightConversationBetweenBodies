import processing.serial.*;

Serial myPort;  // Create object from Serial class

void setup() 
{
  size(200,200); //make our canvas 200 x 200 pixels big
  String portName = Serial.list()[3]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw()
{

}
  
 
void keyPressed()
{
  if (key == CODED)
  {
    //what key was pressed? is the previous angle the opposite direction?
    //we wouldn't want to go backwards into our body, that would hurt!
    //also, is the previous body segment in front of the direction? 
    //(based on the previous question, but added for secure turning without suicide)
    if (keyCode == RIGHT)
    {
       myPort.write('R');         //send a 1
   println("R");   
    }
    if (keyCode == LEFT)
    {
       myPort.write('L');         //send a 1
          println("L");   

    }
     if (keyCode == DOWN)
    {
       myPort.write('D');         //send a 1
   println("D");   
    }
    if (keyCode == UP)
    {
       myPort.write('U');         //send a 1
          println("U");   

    }
  }
}