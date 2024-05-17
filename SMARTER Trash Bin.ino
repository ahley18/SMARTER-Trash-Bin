#include <Servo.h>

//mga servo
Servo lidServo;
Servo sealServo;
Servo lockServo;


long duration;
float distanceCm;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

//mga sensors
int trigPin = 8;
int echoPin = 9;
int button = 4;
int buttonState = 0;
int mRight = 6;
int mLeft = 5;
int heat = 7;
int led = 13;
int mPull = 3;


void setup() {
  // put your setup code here, to run once:
  pinMode(heat, OUTPUT);
  pinMode(led, OUTPUT);
  for(int x = 0; x<=1; x++){
    digitalWrite(heat,0);
    digitalWrite(led,1);
    delay(500);
    digitalWrite(led,0);
    delay(500);
  }
  lidServo.attach(10);
  sealServo.attach(11);
  lockServo.attach(12);
  pinMode(button, INPUT_PULLUP);
  pinMode(mRight, OUTPUT);
  pinMode(mLeft, OUTPUT);
  pinMode(mPull, OUTPUT);

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  

}

void pagbukas(){
  for(int i = 0; i<=60; i++){
    lidServo.write(i);
    delay(2);
  }
  delay(3000);
  for(int i = 60; i>=0; i--){
    lidServo.write(i);
    delay(10);
  }
}
void allStop(){
    digitalWrite(mRight, 0);
    digitalWrite(mLeft, 0);
    digitalWrite(mPull, 0);
    digitalWrite(heat, 0);
    sealServo.write(0);
    lockServo.write(80);
    lidServo.write(0);
  }

void motorSeal(){
  digitalWrite(mRight, 1);
  digitalWrite(mLeft, 0);
  digitalWrite(mPull, 0);

}

void motorRelease(){
  digitalWrite(mRight, 0);
  digitalWrite(mLeft, 0);
  digitalWrite(mPull, 1);
  delay(200);
  digitalWrite(mPull,0);

}

void motorEject(){

  lockServo.write(80);

  delay(500);
  digitalWrite(mRight, 0);
  digitalWrite(mLeft, 1);
  digitalWrite(mPull, 0);
  delay(5000);
  
  for(int i = 0; i<=80; i++){
    lockServo.write(i);
    delay(10);
  }

}


void loop() {
  // put your main code here, to run repeatedly:
// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(10);

  buttonState = digitalRead(button);

  if(distanceCm<=35){
    pagbukas();
  }

  if (buttonState == LOW) {
    Serial.println("1");
    delay(250);
    digitalWrite(heat, 0);
    delay(7000);

    /*for(int i = 0; i<=90; i++){
    lidServo.write(i);
    delay(5);
  }*/

    motorSeal();
    Serial.println("Seal");
    delay(5000);
    sealServo.write(110);
    Serial.println("Sealing plastic");
    delay(10000);
    motorRelease();
    Serial.println("Releasing plastic");
    sealServo.write(0);
    delay(1000);
    motorEject();
    Serial.println("Eject");
    delay(5000);

    /*for(int i = 90; i>=0; i--){
    lidServo.write(i);
    delay(10);
    }*/
  }
  else{
    Serial.println("0");
    delay(10);
    allStop();
  }
}
