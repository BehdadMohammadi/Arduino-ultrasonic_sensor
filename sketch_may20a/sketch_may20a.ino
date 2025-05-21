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
  
  delay(3000);

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
    
    distance = ((float)duration*343*0.001)/2;
    
    Serial.println(distance);
   
  }
}
