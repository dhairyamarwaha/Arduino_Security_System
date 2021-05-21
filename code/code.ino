#include <Keypad.h>
#define red_LED 11 // defining the red led
#define green_LED 10 // defining the green led
#define buzzer 12 // defining the buzzer


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'}, // Defining the keys of the keypad
  {'7','8','9','C'},
  {'S','0','H','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

String v_passcode="";

void setup(){
  Serial.begin(9600); 
  Serial.println("Press A on the keypad to enter password");
  pinMode(red_LED, OUTPUT); // Setting the red led as output
  pinMode(green_LED, OUTPUT); // Setting the green led as output
  pinMode(buzzer, OUTPUT); // Setting the buzzer as output
}

void loop(){
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    //Serial.println(key);
    
    v_passcode = v_passcode + key;
    
    if(key=='A')
    {
        Serial.println("Enter Password : ");
        Serial.println("Press D on the keypad to submit the password");
        v_passcode="";
    }
    
    if(key=='D')
    {
        Serial.println(v_passcode);
          //Serial.println(v_passcode);
          
          if (v_passcode=="1234D")// setting the password
        {
          Serial.println("Password verified ! Access granted"); // Accepting the authorized password
          Serial.println("You can proceed");
          digitalWrite(red_LED, LOW); // Switching off the red led
          digitalWrite(green_LED, HIGH); // Switching on the green led
          delay(10000);
          digitalWrite(green_LED, LOW); // Switching off the buzzer
        }
          else
        {
            Serial.println("Password not verified : Access Denied"); // Rejecting the unauthorized password
            Serial.println("Please enter a valid password");
            digitalWrite(red_LED, HIGH); // Switching on the red led
            digitalWrite(green_LED, LOW); // Switching off the green led
            tone(buzzer,500 ); // Triggering the buzzer
            delay(10000);
            digitalWrite(red_LED, LOW); // Switching off the red led
            noTone(buzzer); // Swithching off the buzzer
        }      
    }        
  }
}
