#include <Arduino.h>
#include <U8g2lib.h>
/*#include <SPI.h>
#include <Wire.h>
*/
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
  u8g2.begin();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration*0.034/2;
  char str[10];
  Serial.print("Daljina: ");
  Serial.println(distance);
  if(distance < 20)
  {
    digitalWrite(7, HIGH);
    if(distance < 15)
    {
      digitalWrite(6, HIGH);
      if(distance < 10)
      {
        digitalWrite(5, HIGH);
        if(distance < 5)
        {
          digitalWrite(4, HIGH);
        }else{
          digitalWrite(4, LOW);
        }
      }else{
        digitalWrite(5, LOW);
      }
    }else{
      digitalWrite(6, LOW);
    }
  }else{
    digitalWrite(7, LOW);
  }

  sprintf(str, "%d", distance);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_crox4hb_tr);
  u8g2.setCursor(0, 15);
  u8g2.print("daljina: ");
  u8g2.print(distance);
  u8g2.print(" cm");
  u8g2.sendBuffer();
  
  delay(100);
}
