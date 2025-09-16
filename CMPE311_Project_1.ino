#define LED_1 3
#define LED_2 2

int LED_STATE_1 = LOW; // Start LED 1 Off
int LED_STATE_2 = LOW; // Start LED 2 Off
bool LED_OR_TIME = false;
int SEL_LED = 0;
bool PRINT_SCREEN = true;

unsigned long LED_1_TIME = millis();
unsigned long LED_2_TIME = millis();

unsigned long LED_1_WAIT = 1500;
unsigned long LED_2_WAIT = 500;

void checkSerial() {

  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil('\n');  // Read until newline
    incomingString.trim();                                 // Remove leading/trailing whitespace
    Serial.println(incomingString); // Print user input to serial monitor for feedback
    if(!LED_OR_TIME){
      
      SEL_LED = incomingString.toInt();
      PRINT_SCREEN = true;
      LED_OR_TIME = !LED_OR_TIME;
    }
    else{
      PRINT_SCREEN = true;
      LED_OR_TIME = !LED_OR_TIME;

      if(SEL_LED == 1){
        LED_1_WAIT = incomingString.toInt();
      }
      else if(SEL_LED == 2){
        LED_2_WAIT = incomingString.toInt();
      }
      else{
        return;
      }

    }
  }
}

void setup() {
  // put your setup code here, to run once:

pinMode(LED_1, OUTPUT);
pinMode(LED_2, OUTPUT);

Serial.begin(9600);
Serial.println("");
}



void loop() {
checkSerial();
if(PRINT_SCREEN && !LED_OR_TIME){
  Serial.print("What LED? (1 or 2) ");
  PRINT_SCREEN = false;
}
else if(PRINT_SCREEN && LED_OR_TIME){
  Serial.print("What interval (in msec) ");
  PRINT_SCREEN = false;
}

if(millis() - LED_1_TIME > LED_1_WAIT){
  LED_STATE_1 = !LED_STATE_1;
  digitalWrite(LED_1,LED_STATE_1);
  LED_1_TIME = millis();
}

if(millis() - LED_2_TIME > LED_2_WAIT){
  LED_STATE_2 = !LED_STATE_2;
  digitalWrite(LED_2,LED_STATE_2);
  LED_2_TIME = millis();
}


}
