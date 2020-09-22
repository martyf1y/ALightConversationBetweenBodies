//////SNAAAAAAAAAAAAAAAKKKKKKKKKEEEEEE

void Move() {
    
     if (stopgame)
  {
    //do nothing because of game over (stop playing)
  }
  else
  {
     //draw stationary stuff
  aTime+=1;

  snakeshineOn(applex, appley, 0, true); //The apple

     if ((aTime % 2)==0)
  {
   
    LEDdisplay();
    travel();
    checkdead();
  }
  }
  }  

void travel()
{
  for(int i=snakesize;i>0;i--)
  {
    if (i!=1)
    {
      //shift all the coordinates back one array
      headx[i]=headx[i-1];
      heady[i]=heady[i-1];
    }
    else
    {
      //move the new spot for the head of the snake, which is
      //always at headx[1] and heady[1].
      switch(angle)
      {
        case 0:
        headx[1]+=10;
        break;
        case 90:
        heady[1]-=10;
        break;
        case 180:
        headx[1]-=10;
        break;
        case 270:
        heady[1]+=10;
        break;
      }
    }
  }
  
}
void LEDdisplay()
{
  //is the head of the snake eating the apple?
  if (headx[1]==applex && heady[1]==appley)
  {
    //grow and spawn the apple somewhere away from the snake
    //(currently some of the code below might not be working, but the game still works.)
    snakesize+=round(random(3)+1);
    redo=true;
    while(redo)
    {
      applex=(round(random(31))+1)*10;
      appley=(round(random(40))+1)*10;
      snakeSpeed -=0.1;
      for(int i=1;i<snakesize;i++)
      {
        
        if (applex==headx[i] && appley==heady[i])
        {
          redo=true;
        }
        else
        {
          redo=false;
          i=1000;
        }
      }
    }
  }
  
         snakeshineOn(headx[1], heady[1], 255, false); //The head of the snake
         snakeshineOn(headx[snakesize], heady[snakesize], 0, false); //The tail of the snake

    // You wont need to insert the exact position for arduino, just have the right ID
   

}

void checkdead()
{
  for(int i=2;i<=snakesize;i++)
  {
    //is the head of the snake occupying the same spot as any of the snake chunks?
    if (headx[1]==headx[i] && heady[1]==heady[i])
    {
      stopgame=true;
    }
    //is the head of the snake hitting the walls?
    if (headx[1]>=320)
    {
      headx[1] = 0;
    }
    if(heady[1]>=410)
    {
      heady[1]= 0;
    }
    if(headx[1]<0)
    {
      headx[1] = 320-10;
    }
    if(heady[1]< 0)
    {
      heady[1]= 410 - 10;
    }
    
 
  }
}
void restart()
{
  //by pressing shift, all of the main variables reset to their defaults.
  headx[1]=200;
  heady[1]=200;
for(int i = 0; i < maxLEDs; i++){
   brightness[i] = 0;
 }
  
  for(int i=2;i<1000;i++)
  {
    headx[i]=0;
    heady[i]=0;
  }
  stopgame=false;
  applex=(round(random(31))+1)*10;
  appley=(round(random(40))+1)*10;
  snakesize=5;
  aTime=0;
  angle=0;
  redo=true;
}
int sinecolor(float percent)
{
  float slime = (sin(radians((((millis() +(255*percent))/255))*360)))*255;
 // int slime=(int)(sin(radians((((millis() +(255*percent)) % 255)/255)*360)))*255;
 // int slime = 255;
 Serial.print(slime);
  return slime;
}

void snakeshineOn(int pX, int pY, int bright, boolean apple){
 
  ///// Make sure to get LED brightness before we go any further!
   stripNum = (int)(map(pX, 0, 320, 0, 31));
     rowNum = (int)(map(pY, 0, 410, 0, 40));


 for(int n = 0; n < stripNum; n++){
    LEDNum += LEDsArray[n];
  }
   LEDNum += rowNum;
   if(rowNum < LEDsArray[stripNum]){
    brightness[LEDNum] = bright;
  //  stripNumArr[LEDNum] = stripNum;
  //  rowNumArr[LEDNum] = rowNum;    
    // You wont need to insert the exact position for arduino, just have the right ID
  
   ///// Make sure to get LED brightness before we go any further!
  int r ;
  int b ;
  int g ;
  if(apple){
   r = 255;
   g = 0;
   b = 0;
  }
  else if(brightness[LEDNum] > 0){
//   r = sinecolor(0.5);
//   b = sinecolor(1);
//   g = sinecolor(1);
   
 r = 0;
 g = 255;
 b = 0;
   // r = 235;
   // g = 200;
   // b = 20;
  }
  else {
     g = 0;
  r = 0;
  b = 0;
  }
  // This would just be the ID number
  strip.setPixelColor(LEDNum, r, g, b);
 }
  else if(apple)
  {
    applex=(round(random(31))+1)*10;
      appley=(round(random(40))+1)*10;
  } 
  
  LEDNum = 0;
  
  
  }

//controls:
void keyPressed()
{
 if (Serial.available()) 
   { // If data is available to read,
     val = Serial.read(); // read it and store it in val
   }
   if (val == 'R' && angle!=180 && (headx[1]+10)!=headx[2]) 
   { 
     digitalWrite(ledPin, HIGH); // turn the LED on
      angle=0;
   } 
   if (val == 'L' && angle!=0 && (headx[1]-8)!=headx[2]) {
     digitalWrite(ledPin, LOW); // otherwise turn it off
     angle=180;
   }
    if (val == 'U' && angle!=90 && (heady[1]+10)!=heady[2]) 
   { 
     digitalWrite(ledPin, HIGH); // turn the LED on
     angle=270;
   } 
   if (val == 'D' && angle!=270 && (heady[1]-10)!=heady[2]) {
     digitalWrite(ledPin, LOW); // otherwise turn it off
     angle=90;
   }
   delay(10); // Wait 10 milliseconds for next reading
   
}


