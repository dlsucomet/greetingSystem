
/////////////////////////////
// 
//

int calibrationTime = 30;   // Time to calibrate sensor GH-71C8     

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped

long unsigned int pause = 2000;// system pause to denote the stop of motion
// Notes to play  
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
 
int led = 12;
int led2 = 11;
int led3 = 10;
const int buzzerPin = 8; //buzzer to arduino pin 9

boolean lockLow = true;
boolean takeLowTime;  
boolean inBetween = false;

int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
int counter = 0;
 

/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
//LOOP

void loop(){
  
     if(digitalRead(pirPin) == HIGH){
       if(lockLow){  
         //makes sure we wait for a transition to LOW before any further output is made:
         lockLow = false;            
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec"); 
         delay(50); 
         inBetween = true;
         }         
         takeLowTime = true;
       }

     if(digitalRead(pirPin) == LOW){       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state

       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           inBetween = false;
           }
       }
          if(inBetween){ // In between motion detected and motion ended, It will initiate a Loop that plays the song
             digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
             delay(100);               // wait for a second
             digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
             delay(100); 
          
             digitalWrite(led2, HIGH);
             delay(100);
             digitalWrite(led2, LOW);
             delay(100);
            
             digitalWrite(led3, HIGH);
             delay(100);
             digitalWrite(led3, LOW);
             delay(100);
            //Play first section
            firstSection();
           if (digitalRead(pirPin) == HIGH){
              //Play second section
              secondSection();
           }
     }   
  }
  void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
 
  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    digitalWrite(led, HIGH);
    delay(duration);
    digitalWrite(led, LOW);
  }else
  {
    digitalWrite(led2, HIGH);
    delay(duration);
    digitalWrite(led2, LOW);
  }
 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
 
  delay(20);
 
  //Increment counter
  counter++;
}
void firstSection()
{
  if (digitalRead(pirPin) == HIGH){  // Always read the sensor output so the song will stop when person walks away.
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
  delay(200);
  }
  if (digitalRead(pirPin) == HIGH){
    beep(eH, 500);
    beep(eH, 500);
    beep(eH, 500);  
    beep(fH, 350);
    beep(cH, 150);
    beep(gS, 500);
    beep(f, 350);
    beep(cH, 150);
    beep(a, 650);
  }
}
 
void secondSection()
{
  if (digitalRead(pirPin) == HIGH){
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
  }
  if (digitalRead(pirPin) == HIGH){
  delay(200);
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
  }
 
}
