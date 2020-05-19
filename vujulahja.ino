// include the lcd display library
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // wire the switch to pin 7. The pin is HIGH if switch is pressed and LOW if not.
  pinMode(7, INPUT);
  // wire the buzzer to GND and pin 6. Set pin 6 to OUTPUT
  pinMode(6, OUTPUT);
}

/* stat = short for status. Checks if switch is pressed or not. LOW or HIGH.
 * Set up the global variables to be used in loop() and the array that save the
 * two most recent times. Long integers because integers in arduino are 2 bytes.*/

short int stat = digitalRead(7);
long int start = 0;
long int ended = 0;
long int tim = 0;
long int times[] = {0,0};

void loop() {
  //zero the timer after each loop.
  start = 0;
  ended = 0;
  // print the time to the LCD
  lcd.setCursor(0, 0);
  stat = digitalRead(7);
  lcd.print("AIKA:");
  lcd.setCursor(8,0);
  lcd.print("EDELLINE");
  lcd.setCursor(8,1);
  lcd.print(times[1]/100);
  lcd.print(".");
  if(times[1] - times[1]/100 * 100 < 10){
    lcd.print("0");
  }
  lcd.print(times[1] - times[1]/100 * 100);
  lcd.print("s");
  
  // start the stopwatch sequence when the swich is pressed.
  if (stat == HIGH){
    lcd.clear();
    start = millis();
    while(stat == HIGH){
      // print place filler stuff while the switch is on
      lcd.setCursor(0,0);
      lcd.print("KELLOTA!!!!!");
      lcd.setCursor(0,1);
      stat = digitalRead(7);
      ended = millis();
      lcd.print((ended-start)/10);
      }
      // make place for the new time.
      // save the time to the array as hundreths of seconds.
      times[1] = times[0];
      times[0] = (ended - start)/10;
      
      // if the most recent time is shorter make a small sound from the buzzer.
      if ( times[0] < times[1]){
        for(int i = 0; i<2; i++){
          tone(6, 800);
          delay(100);
          noTone(6);
          delay(100);
        }
      }
   }  
}

