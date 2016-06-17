/* #include <ICSC.h> */

#define dirPin 3

#define motorPinOn 4

#define endStop1 9
#define endStop2 10


#define STOPPED 0
#define RUNNING 1

#define sw1_btn1Pin 11
#define sw1_btn2Pin 12



#define CV 0
#define CCV 1

int Status = STOPPED;
int curDir;



void setup() {
  
  pinMode(motorPinOn, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(sw1_btn1Pin, INPUT);
  pinMode(sw1_btn2Pin, INPUT);
  
  pinMode(endStop1, INPUT);
  pinMode(endStop2, INPUT);
  
  

  digitalWrite(dirPin, LOW);
  Status=STOPPED;
  Serial.begin(115200);

  Serial.print("Stage curtain simple motion control v1.0 (17-06-2016)\nStarting...\n\n");
  delay(3000);
}

void loop() {
  // static unsigned long ts = millis();


int  sw1_btn1State = digitalRead(sw1_btn1Pin);
int  sw1_btn2State = digitalRead(sw1_btn2Pin);
int  endStop1State = digitalRead(endStop1);
int  endStop2State = digitalRead(endStop2);

Serial.print("Btn-1: " ); Serial.print( sw1_btn1State); Serial.print("\t");
Serial.print("Btn-2: " ); Serial.print( sw1_btn2State); Serial.print("\t");
Serial.print("EndStop-1: " ); Serial.print( endStop1State); Serial.print("\t");
Serial.print("EndStop-2: " ); Serial.println( endStop2State);
  
    if ((endStop1State == HIGH && curDir == CV) && Status == RUNNING) {
      Serial.println("Endstop 1.");  
      stop();
    }

    if ((endStop2State == HIGH && curDir == CCV) && Status == RUNNING) {
      Serial.println("Endstop 2.");  
      stop();
    }

    
    if (sw1_btn1State == LOW && sw1_btn2State == LOW && Status==RUNNING) stop();


  
  if (sw1_btn1State == HIGH && Status!=RUNNING && endStop1State == LOW) {
      Serial.println("Btn-1");
      start(CV);
   }

  if (sw1_btn2State == HIGH && Status!=RUNNING && endStop2State == LOW) {
    Serial.println("Btn-2");
    start(CCV);
  }
   
  
  delay(50);
}


void start(int dir){

  

  switch (dir) {
    case CCV:
      digitalWrite(dirPin, HIGH);
      break;
    case CV:
      digitalWrite(dirPin, LOW);
      break;
  } 
  curDir=dir;

    Serial.print("Running: \t"); Serial.println(curDir);
    delay(100);
    
    digitalWrite(motorPinOn, HIGH);
  
 
  Status=RUNNING;

}

void stop() {
    Serial.println("Stop.");  
    digitalWrite(motorPinOn, LOW);
    Status=STOPPED;
    delay(500);
}



