#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


long cardNumberMax = 1978250;
long cardNumberTwo = 208540;
Servo lock;

MFRC522 mfrc522(10, 9);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16, 2);
  lock.attach(8);
  
  lcd.setCursor(0, 0);
  lcd.print("Door locked");
  lcd.setCursor(0, 1);
  lcd.print("Please authorize");
}

void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  long code=0;
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    code=((code+mfrc522.uid.uidByte[i])*10);
  }
  
  Serial.println(code);
  if (code == cardNumberMax)
  { 
    lock.write(180);
    lcd.setCursor(0, 0);
    lcd.print("Door opened");
    lcd.setCursor(0, 1);
    lcd.print("Welcome Max     ");
    delay (5000);
    lcd.setCursor(0, 0);
    lcd.print("Door locked");
    lcd.setCursor(0, 1);
    lcd.print("Please authorize");
    lock.write(90);
  } 
  if (code == cardNumberTwo)
  { 
    lcd.setCursor(0, 0);
    lcd.print("Door locked");
    lcd.setCursor(0, 1);
    lcd.print("No access       ");
    delay (5000);
    lcd.setCursor(0, 0);
    lcd.print("Door locked");
    lcd.setCursor(0, 1);
    lcd.print("Please authorize");
    lock.write(90);
  } 
}
