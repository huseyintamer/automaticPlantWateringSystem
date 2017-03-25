
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
  Projede 
  Mutfak aydınlatması ve televizyonu kontrol etmek için (aç-kapa)
  ses tanıma modülü kullanılmıştır.
  Bu modül sesinize oldukça hızlı tepki vermektedir.
  Cihaz öncelikle usb to ttl dönüştürücü ile bilgilsayara bağlanır
  ses komutlarını yüklemek için seri porttan AT komutları verilir
  ses komutları yüklendikten sonra kütüphanesi eklenerek projeniz 
  için geliştirilebilir.
 Donanim
  220V Röleler ve Ses tanıma modülü kullanılmaktadır.
  
 VoiceRecognitionV3 Kütüphanesi
 https://github.com/elechouse/VoiceRecognitionV3
  SES TANIMA MODÜLÜ BAĞLANTISI
   2   ------->     TX
   3   ------->     RX
*/


VR myVR(2,3);    // 2:RX 3:TX, Olarak tanımlanmıştır

uint8_t records[7]; // kayıt edilebilen ses sayısı
uint8_t buf[64];

int mutfak = 4;
int televizyon = 5;



#define mutfakacRecord    (0)
#define mutfakkapatRecord   (1) 
#define televizyonacRecord    (2)
#define televizyonkapatRecord   (3) 




/**
  @brief   İmzayı yazdır , Eğer karakter görünmezse, 
           okunaklı değer yazdır.
  @param   buf     --> Komut Uzunlupu
           len     --> parametre sayısı
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}


void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);

  
  Serial.begin(115200);
  Serial.println("Ses Tanıma Modülü Başlatılıyor..");
  
  pinMode(mutfak, OUTPUT);
    pinMode(televizyon, OUTPUT);
      pinMode(perde, OUTPUT);
        pinMode(salon, OUTPUT);
          pinMode(ketil, OUTPUT);
    

  if(myVR.clear() == 0){
    Serial.println("Tanımlama temizlendi.");
  }else{
    Serial.println("Modül Bulunamadı.");
    Serial.println("Lütfen Baglantiyi kontrol edin ve sistemi yeniden başlat.");
    while(1);
  }
  
  if(myVR.load((uint8_t)mutfakacRecord) >= 0){
    Serial.println("onRecord");
  }
  
  if(myVR.load((uint8_t)mutfakkapakRecord) >= 0){
    Serial.println("offRecord");
     }
  
  if(myVR.load((uint8_t)televizyonacRecord) >= 0){
    Serial.println("onRecord");
  }
  
  if(myVR.load((uint8_t)televizyonkapatRecord) >= 0){
    Serial.println("offRecord");
       }
   } 
}

void loop()
{
 int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case mutfakkacRecord:
        
        digitalWrite(mutfak, HIGH);
       
  break;
      case  mutfakkapatRecord:
       
                    
        digitalWrite(mutfak, LOW);

        break;
           case televizyonacRecord:
           
        digitalWrite(televizyon, HIGH);
        
      case televizyonkapatRecord:
       
              
        digitalWrite(televizyon, LOW);
    break;
 
      default:
        Serial.println("Kayıt fonksiyonu algılayamadı");
        break;
    }
    
    printVR(buf);
  }
}




