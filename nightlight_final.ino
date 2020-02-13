//NightLight - Soap Dish
//Lisa Liu & Heather Hsueh
//HCID521 Winter Quarter 2020
//Fade code: https://www.arduino.cc/en/Tutorial/DimmingLEDs
//Photocell code: https://learn.adafruit.com/photocells/using-a-photocell

int redPin = 6;
int greenPin = 5;
int bluePin = 3;

int redVal   = 255; // Variables to store the values to send to the pins
int greenVal = 1;   // Initial values are Red full, Green and Blue off
int blueVal  = 1;

int i = 0;     // Loop counter    
int wait = 5; // 50ms (.05 second) delay; shorten for faster fades
int DEBUG = 0; // DEBUG counter; if set to 1, will write values back via serial

void setup() {
  Serial.begin(9600); //for photocell
  pinMode(redPin, OUTPUT); //for rgb LED
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
}

void loop() {
  
  // photocell code
  int photocell1 = analogRead(A0);
  int ledVal = map((photocell1), 300, 600, 255, 0);
  //analogWrite(11, ledVal);
  //Serial.print(",");
  //Serial.println(ledVal);
  delay(wait*2); 

  //LED code
  if (photocell1 < 200) {  // if detected light is less than (shadow of phone), start lights
 
    i += 1;      // Increment counter
    if (i < 255) // First phase of fades
        {
          redVal   -= 1; // Red down
          greenVal += 1; // Green up
          blueVal   = 1; // Blue low
        }
        else if (i < 509) // Second phase of fades
        {
          redVal    = 1; // Red low
          greenVal -= 1; // Green down
          blueVal  += 1; // Blue up
        } 
        else if (i < 763) // Third phase of fades
        {
          redVal  += 1; // Red up
          greenVal = 1; // Green low
          blueVal -= 1; // Blue down
        }
    else // Re-set the counter, and start the fades again
        {
          i = 1;
        }  
    
      analogWrite(redPin, redVal);   // Write current values to LED pins
      analogWrite(greenPin, greenVal); 
      analogWrite(bluePin, blueVal);
    
  } else // stop lights
  {
      analogWrite(redPin, 255);   // Write current values to LED pins
      analogWrite(greenPin, 255); 
      analogWrite(bluePin, 255);
  }

  if (DEBUG) { // If we want to read the output
    DEBUG += 1;     // Increment the DEBUG counter
    if (DEBUG > 10) // Print every 10 loops
    {
      DEBUG = 1;     // Reset the counter

      Serial.print(i);       // Serial commands in 0004 style
      Serial.print("\t");    // Print a tab
      Serial.print("R:");    // Indicate that output is red value
      Serial.print(redVal);  // Print red value
      Serial.print("\t");    // Print a tab
      Serial.print("G:");    // Repeat for green and blue...
      Serial.print(greenVal);
      Serial.print("\t");    
      Serial.print("B:");    
      Serial.println(blueVal); // println, to end with a carriage return
    }
  }
  delay(wait); // Pause for 'wait' milliseconds before resuming the loop

}
