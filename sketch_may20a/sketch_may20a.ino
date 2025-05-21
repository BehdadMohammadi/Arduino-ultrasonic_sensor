int trig = 9;
int echo = 2;
int duration;
float distance;
float meter;

unsigned long  time_start = 0;
unsigned long  time_end = 0;
int flag = 0;

boolean toggle1 = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  pinMode(echo, INPUT);

  pinMode(13, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(echo), measure, CHANGE);

  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();

  
  delay(6000);
}

void loop() {
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
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
    
    distance = ((float)duration*343*0.001)/2;
    
    Serial.println(distance);
   
  }
}


ISR(TIMER1_COMPA_vect)
{
  //timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }
}
