#define LED_1 3 // LED 1 goes to pin 3
#define LED_2 2 // LED 2 goes to pin 2

int LED_STATE_1 = LOW; // Start LED 1 Off
int LED_STATE_2 = LOW; // Start LED 2 Off
bool LED_OR_TIME = false; // If false prompt for LED, if true prompt of interval
int SEL_LED = 0; // Select LED
bool PRINT_SCREEN = true; // Print to serial monitor flag

unsigned long LED_1_TIME = millis(); // Time stamp for LED 1
unsigned long LED_2_TIME = millis(); // Time stamp for LED 2

unsigned long LED_1_WAIT = 1500; // Set LED 1 default interval to 1500
unsigned long LED_2_WAIT = 500; // Set LED 2 default interval to 500

void checkSerial() {

  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil('\n');  // Read until newline
    incomingString.trim();                                 // Remove leading/trailing whitespace
    Serial.println(incomingString); // Print user input to serial monitor for feedback
    // If flag is false select LED
    if(!LED_OR_TIME){
      SEL_LED = incomingString.toInt(); // Turn serial monitor string to int
      PRINT_SCREEN = true; // Allow serial monitor to be printed to again
      LED_OR_TIME = !LED_OR_TIME; // Toggle LED flag to interval flag
    }
    else{
      PRINT_SCREEN = true; // Allow serial monitor to be printed to again
      LED_OR_TIME = !LED_OR_TIME; // Toggle interval flag to LED flag

      if(SEL_LED == 1){
        LED_1_WAIT = incomingString.toInt(); // Set intervale for LED 1
      }
      else if(SEL_LED == 2){
        LED_2_WAIT = incomingString.toInt(); // Set interval for LED 2
      }
      else{
        // Should never reach but if LED selected is > 2 or < 1 then do nothing
        return;
      }

    }
  }
}

void setup() {
  // put your setup code here, to run once:

pinMode(LED_1, OUTPUT); // Setup LED 1 pin as output 
pinMode(LED_2, OUTPUT); // Setup LED 2 pin as outpt

Serial.begin(9600); // Start serial monitor session with 9600 baud
Serial.println(""); 
}



void loop() {
checkSerial(); // Check if there is data in serial monitor
// If serial monitor can be printed too and is looking for LED
if(PRINT_SCREEN && !LED_OR_TIME){
  Serial.print("What LED? (1 or 2) ");
  PRINT_SCREEN = false;
}
// If serial monitor can be printed too and is looking for interval timing
else if(PRINT_SCREEN && LED_OR_TIME){
  Serial.print("What interval (in msec) ");
  PRINT_SCREEN = false;
}
// Check LED 1 timing interval
if(millis() - LED_1_TIME > LED_1_WAIT){
  LED_STATE_1 = !LED_STATE_1; // Toggle LED 1 state
  digitalWrite(LED_1,LED_STATE_1); // Update LED 2 state
  LED_1_TIME = millis(); // Reset LED 1 timer
}

//Check LED 2 timing interval
if(millis() - LED_2_TIME > LED_2_WAIT){
  LED_STATE_2 = !LED_STATE_2; // Toggle LED 2 state
  digitalWrite(LED_2,LED_STATE_2); // Update LED 2 state
  LED_2_TIME = millis(); // Reset LED 2 timer
}


}
