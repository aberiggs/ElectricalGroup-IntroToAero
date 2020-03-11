
#include <Servo.h>
Servo servo;
int pos = 0;
#include<Wire.h>
int LED_RED = 2;
const int MPU=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  pinMode(LED_RED, OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  servo.attach(2);
  servo.write(pos);
}
void loop(){
  digitalWrite(LED_RED, LOW);
  int LastX = AcX;
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read();  

  /*
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(AcX);
  Serial.print(" | Y = "); Serial.print(AcY);
  Serial.print(" | Z = "); Serial.println(AcZ); 
  
  Serial.print("Gyroscope: ");
  Serial.print("X = "); Serial.print(GyX);
  Serial.print(" | Y = "); Serial.print(GyY);
  Serial.print(" | Z = "); Serial.println(GyZ);
  Serial.println(" ");
  */

  Serial.println("Last X");
  Serial.println(LastX);
  int Difference = LastX-AcX;
  pos = random(180);
  if (Difference > 2000) {                                
        servo.write(pos);           
        delay(2000);    
  }
  Serial.println("Difference");
  Serial.println(Difference);
  Serial.println();
  delay(1000);
}
