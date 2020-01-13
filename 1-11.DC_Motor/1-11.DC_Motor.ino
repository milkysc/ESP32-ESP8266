const int MOTORAP = 2;
const int MOTORAM = 0;
const int MOTORBP = 4;
const int MOTORBM = 5;
byte speed = 255;
void setup() {
  // put your setup code here, to run once:
  pinMode(MOTORAP, OUTPUT); //Left Backward
  pinMode(MOTORAM, OUTPUT); //Left Forward
  pinMode(MOTORBP, OUTPUT); //Right Forward
  pinMode(MOTORBM, OUTPUT); //Right Backward
}

#if 1
void loop()
{
  forward();
  delay(3000);
  backward();
  delay(3000);
}

void backward()
{
  analogWrite(MOTORAP, 0);
  analogWrite(MOTORAM, speed);
  analogWrite(MOTORBP, 0);
  analogWrite(MOTORBM, speed);
  
}

void forward()
{
  analogWrite(MOTORAP, speed);
  analogWrite(MOTORAM, 0);
  analogWrite(MOTORBP, speed);
  analogWrite(MOTORBM, 0);
}
#else
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(MOTORAP, 1);
  digitalWrite(MOTORAM, 0);
  digitalWrite(MOTORBP, 1);
  digitalWrite(MOTORBM, 0);
  delay(3000);
  digitalWrite(MOTORAP, 0);
  digitalWrite(MOTORAM, 1);
  digitalWrite(MOTORBP, 0);
  digitalWrite(MOTORBM, 1);
  delay(3000);
}
#endif
