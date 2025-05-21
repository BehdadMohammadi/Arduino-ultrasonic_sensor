int trig = 9;
int echo = 2;
int duration;
float distance;
float meter;

unsigned long  time_start = 0;
unsigned long  time_end = 0;
int flag = 0;

boolean toggle1 = 0;

void setup()
{
  
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  pinMode(echo, INPUT);

  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(echo), measure, CHANGE);

  cli();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  TIMSK1 |= (1 << OCIE1A);

  sei();

  delay(3000);
}

void loop()
{
  
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

ISR(TIMER1_COMPA_vect)
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}
