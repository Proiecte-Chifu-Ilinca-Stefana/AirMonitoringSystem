#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include  <Adafruit_SSD1306.h>
#include  <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int senzorDhtPin = 7;
int senzorType = 11;

int ledRosu = 8;
int ledVerde = 9;

DHT dht(senzorDhtPin,  senzorType);

void setup() {
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Proiect pmp");
  delay(5000);
  pinMode(A0, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRosu, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  lcd.clear();

}

void loop() {
  lcd.print("Caliate aer: ");
 int mq_value = analogRead(A0);
 lcd.print(mq_value);
 if (mq_value <= 50.0){
    digitalWrite (ledVerde, HIGH);
    digitalWrite (ledRosu, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Buna!");

 }else{
    digitalWrite (ledRosu, HIGH);
    digitalWrite (ledVerde, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Atentie!");

 }
 delay(5000);
 lcd.clear();
 float h = dht.readHumidity();
 if(isnan(h)){
    lcd.print(" Nu merge ceva");
    return;
 }
  if (h >= 30.0 && h <= 50.0){
    digitalWrite (ledVerde, HIGH);
    digitalWrite (ledRosu, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Normala!");

 }else{
    digitalWrite (ledRosu, HIGH);
    digitalWrite (ledVerde, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Atentie!");

 }
 lcd.setCursor(0,0);
 lcd.print("Umiditate:");
 lcd.print(h);
 lcd.print("%");
 delay(5000);
 lcd.clear();
 float t = dht.readTemperature();
 if (t >= 25.0 || t <= 10.0){
    digitalWrite (ledRosu, HIGH);
    digitalWrite (ledVerde, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Anormala!");

 }else{
    digitalWrite (ledVerde, HIGH);
    digitalWrite (ledRosu, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Acceptabila!");
 }
 if(isnan(h)){
    lcd.print("Ceva nu merge");
    return;
 }
 lcd.setCursor(0,0);
 lcd.print("Temp:");
 lcd.print(t);
 lcd.print("C");
 delay(5000);
 lcd.clear();

}
