#include <dht.h>
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(60, 8);
int neoB;
int pv;
int pp = A0;
int piezoPin = 9;
int buzzerPin = 9;
int buttonPin = 10;
uint32_t color;
uint32_t color1 = strip.Color(255, 0, 0);
uint32_t color2 = strip.Color(0, 0, 255);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int toneFreq = 200;

dht DHT;
const int photoPin = A0 ;
#define DHT11_PIN 7

void setup() {
  int chk = DHT.read11(DHT11_PIN);
  Serial.begin(9600);
  strip.clear();
  strip.show();
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
 // tone(piezoPin, 200);
  neoB = 200;
  light();
  HandLCD();
 buzz();
  
}

void light() {
  strip.begin();
  pv = analogRead(pp);
  Serial.println(neoB);
  neoB = map(pv, 0, 350, 200, 50);
  strip.setBrightness(neoB);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    if (i % 2 == 0) {
      color = color1;
    }
    if (i % 2 == 1) {
      color = color2;
    }
  }
   strip.show();
}

void HandLCD(){
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature * 1.8 + 32);
  lcd.print((char)223);
  lcd.print("F");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(1000);
  lcd.clear();
}

void buzz(){
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  if (buttonState==HIGH)
  {
//    Serial.println("button");
    tone(buzzerPin, toneFreq);
  } 
  else
  {
    noTone(buzzerPin);
//    Serial.println("no button");
  }
}
