#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

// RFID
#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// MP3
SoftwareSerial dfpPlayerSerial(/*rx =*/3, /*tx =*/2);
DFRobotDFPlayerMini myDFPlayer;

void setupDFPlayer(){
  dfpPlayerSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(dfpPlayerSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(5);  //Set volume value (0~30).
}

void setupMFRC522(){
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522
  Serial.println(F("MFRC522 initialized"));
}

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC     
  setupDFPlayer();
  setupMFRC522();
}

void loop() {
  // put your main code here, to run repeatedly:
  static unsigned long timer = millis();
  
  if (millis() - timer > 10000) {
    timer = millis();
   
    myDFPlayer.playLargeFolder(01, 330);  //Play exact mp3 every 10 second.
    Serial.println("Playing next");
  }

  // Read available data
  if (myDFPlayer.available()) {
    logDetail(myDFPlayer.readType(), myDFPlayer.read()); //Log the detail message from DFPlayer to handle different errors and states.
  }

  if (mfrc522.PICC_IsNewCardPresent()) {
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
    Serial.println(readNtag213());
  }
}

/** On ne lit que la 1ere page */
int readNtag213(){
  byte blockAddr = 7;
  MFRC522::StatusCode status;
  byte buffer[32];
  byte size = sizeof(buffer);
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Read() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return -1;
  }
  return parseBuffer(buffer, 32); 
}

int parseBuffer(byte *buffer, byte bufferSize) {
    byte end = 0;
    for (byte i = 0; i < bufferSize; i++) {
      if(buffer[i]== 0xFE){
        end = i;
      }
    }
    return String((char*)buffer).substring(2,end).toInt();
}

void logDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}