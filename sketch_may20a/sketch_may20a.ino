int trig = 9;
int echo = 2;
int duration;
float distance;
float meter;

unsigned long  time_start = 0;
unsigned long  time_end = 0;
int flag = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  pinMode(echo, INPUT);
  Serial.println("Test");
  attachInterrupt(digitalPinToInterrupt(echo), measure, CHANGE);
  delay(6000);
}

void loop() {
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  

  
//  duration = pulseIn(echo, HIGH);
//
//  Serial.print("Echo: ");
//  Serial.println(duration);
//  
//  if(duration>=38000){
//    Serial.print("Out range");
//  }
//  else
//  {
//    distance = (duration*0.0343)/2;
//    Serial.print(distance);
//    Serial.print("cm");
//    meter = distance/100;
//    Serial.print("\t");
//    Serial.print(meter);
//    Serial.println("m");
// }
// 
 Serial.println(duration);
 delay(1000);

}

void measure()
{
  if (flag == 0)
  {
    flag = 1;
    time_start = micros();
  }
  else
  {
    flag = 0;
    time_end = micros();

    duration = time_end - time_start;
 
  }
}
