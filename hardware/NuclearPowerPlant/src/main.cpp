char c;
 
#include <SoftwareSerial.h> 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

SoftwareSerial BTserial(2, 3); // RX, TX
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Enter AT commands or approximate your card reader...:");
  Serial.println();

  BTserial.begin(9600);
}
 
void loop() 
{

  if (BTserial.available())
  {
    Serial.write(BTserial.read());
  }
  
  if (Serial.available())
  {
    BTserial.write(Serial.read());
  }

  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
    // Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "D9 A7 DD 56" || content.substring(1) == "99 56 AE 47")
  {
    Serial.println("Authorized access =)");
    Serial.println();
    delay(3000);
  }
  else 
  {
    Serial.println(" Access denied");
  }
}