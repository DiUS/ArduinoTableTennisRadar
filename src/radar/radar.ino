#include <Multiplex7Seg.h>

enum sensorState {
  IDLE, GATHER
};

const int trigPin = A5; //Change to pin you use
const int echoPin = A4; //Here too
const int ledPin = A2; //Here too
const int thresholdDuration = 173 * 29 * 2;

int sensorState = IDLE;
long sampleDurations[50];
long sampleTimes[50];
int sampleIndex = 0;

byte digitPins[] = {9, 10, 11, 12}; // LSB to MSB
int noOfDigits = 4;

byte segmentPins[] = {2,3,4,5,6,7,8}; // seg a to g

void calculate();
void checkToGather();

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Multiplex7Seg::set(0, noOfDigits, digitPins, segmentPins); // initialize 
}

void loop() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, thresholdDuration);
  
  if (sensorState == IDLE) {
    checkToGather(duration);
  }
  
  if (sensorState == GATHER) {
    gather(duration);
  }
//  Multiplex7Seg::update();
}

void checkToGather(long duration) {
  if(duration > 0) {
    sensorState = GATHER;
    digitalWrite(ledPin, HIGH);
  }
}

void gather(long duration) {
  sampleDurations[sampleIndex] = duration;
  sampleTimes[sampleIndex++] = micros();
  if (sampleIndex == 49) {
    calculate();
    digitalWrite(ledPin, LOW);
    sensorState = IDLE;
    sampleIndex = 0;
  }
}

void calculate() {
  long lastDuration, firstDuration, lastTime, firstTime;

  firstDuration = sampleDurations[0];
  firstTime = sampleTimes[0];
  
  for (int i = 49; i >= 0; i--) {
    if (sampleDurations[i] > 0) {
      lastDuration = sampleDurations[i];
      lastTime = sampleTimes[i];
      break;
    }
  }
  
  Serial.println(firstDuration);
  Serial.println(lastDuration);
  Serial.println(firstTime);
  Serial.println(lastTime);
  
  float cms = microsecondsToCentimeters(abs((lastDuration - firstDuration)*1000));
  long time = abs(lastTime - firstTime);
  
  float velocity = ((float)cms/100000)/((float)time/1000000);

  Serial.print(velocity);
  Serial.println(" m/s");
 
  Multiplex7Seg::loadValue((int)(velocity*1000));  // Display incrementing value 
}

float microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds / 29 / 2);
}
