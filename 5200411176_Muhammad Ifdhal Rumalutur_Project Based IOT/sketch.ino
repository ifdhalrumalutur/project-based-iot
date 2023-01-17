//5200411176
//MUHAMMAD IFDHAL RUMALUTUR
//IOT Praktik - IX

#include <LiquidCrystal_I2C.h>
#include "DHTesp.h"
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLwIkyi8Qm"
#define BLYNK_DEVICE_NAME "MonitoringSuhu"
#include <BlynkSimpleEsp32.h>//library blynk untuk esp32
char auth[] = "o-btHIrHLVuIEp0FAUlAlsl2YwkISTDK";//token blynk

const int DHT_PIN = 15;
LiquidCrystal_I2C lcd(0x27,20,4);


BlynkTimer timer;
DHTesp dhtSensor;

float t , h;
int ledPin = 18;
int buzPin = 5;
String status = "";
String lampu = "";
String buzzer = "";

void send(){
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, status);
  Blynk.virtualWrite(V3, lampu);
  Blynk.virtualWrite(V4, buzzer);

}

void setup() {
  
  pinMode(ledPin, OUTPUT);
  pinMode(buzPin, OUTPUT);
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Kondisi Saat Ini");
  
  timer.setInterval(100, send);//mengatur waktu pengiriman nilai sensor ke blynk setiap 1 detik
  Blynk.begin(auth, "Wokwi-GUEST", "");

  
}

void loop() {
  suhu();
  Blynk.run();
  timer.run();
}
void sound(){
  tone (buzPin, 100, 800);
  delay(50);
  noTone(5);
  delay(50);
}
void suhu(){
TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  h = data.humidity;
  t = data.temperature;
  if (t < 18){
  status = " Suhu Dingin";
  lampu = "Lampu : On";
  buzzer = "Buzzer: Off";
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Hum: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println("Suhu Dingin");
  Serial.println("----------");
  lcd.setCursor(0,1); 
  lcd.print("TEMP: ");
  lcd.print(t);
  lcd.setCursor(0,2);
  lcd.print("HUM: ");
  lcd.print(h);
  lcd.setCursor(0,3);
  lcd.print("Suhu Dingin");
  digitalWrite(ledPin, HIGH);
  delay(1000);
  }else if ((t > 18) and (t <40)){
  status = "Suhu Normal";
  lampu = "Lampu : Off";
  buzzer = "Buzzer: Off";
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Hum: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println("Suhu Normal");
  Serial.println("----------");
  lcd.setCursor(0,1); 
  lcd.print("TEMP: ");
  lcd.print(t);
  lcd.setCursor(0,2);
  lcd.print("HUM: ");
  lcd.print(h);
  lcd.setCursor(0,3);
  lcd.print("Suhu Normal");
  digitalWrite(ledPin, LOW);
  delay(1000);
  }else if ((t > 40)){
  status = "Suhu Panas";
  lampu = "Lampu : Off";
  buzzer = "Buzzer: On";
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Hum: ");
  Serial.print(h);
  Serial.println(" %");
  Serial.println("Suhu Panas");
  Serial.println("----------");
  lcd.setCursor(0,1); 
  lcd.print("TEMP: ");
  lcd.print(t);
  lcd.setCursor(0,2);
  lcd.print("HUM: ");
  lcd.print(h);
  lcd.setCursor(0,3);
  lcd.print("Suhu Panas");
  digitalWrite(ledPin, LOW);
  sound();
  delay(1000);
  }
}
