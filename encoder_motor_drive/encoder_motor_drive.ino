/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
#include <Encoder.h>
int yon = 1;
Encoder myEnc(2,3);
const int in1 = 6;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;

int trigPin = 12; /* Sensorun trig pini Arduinonun 6 numaralı ayağına bağlandı */
int echoPinSol = 13;  /* Sensorun echo pini Arduinonun 7 numaralı ayağına bağlandı */
int echoPinSag = 11;
int echoPinOn = 10;
int hiz =5;
int hiz2 =4;

long newPosition;
long sureSol;
long sureSag;
long sureOn;
long uzaklikSol;
long uzaklikSag;
long uzaklikOn;
long oldPosition  = -999;

void setup() {
  pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPinSol,INPUT); /* sol echo pini giriş olarak ayarlandı */
  pinMode(echoPinSag,INPUT); /* sağ echo pini giriş olarak ayarlandı */
  pinMode(echoPinOn,INPUT); /* ön echo pini giriş olarak ayarlandı */
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  analogWrite(hiz2,  255);
  ileri_x_kare(30);
  Serial.println(myEnc.read());
  delay(500);
  Serial.println(myEnc.read()); 
}
 



void loop() {
 // digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi 
 // delayMicroseconds(5);
 // digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
 // delayMicroseconds(10);
 // digitalWrite(trigPin, LOW);  /* Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi */ 
 /*
  sureSol = pulseIn(echoPinSol, HIGH); // ses dalgasının geri dönmesi için geçen sure ölçülüyor 
  sureSag = pulseIn(echoPinSag, HIGH); // ses dalgasının geri dönmesi için geçen sure ölçülüyor
  sureOn = pulseIn(echoPinOn, HIGH);
  uzaklikSol = sureSol /29.1/2;// ölçülen sure uzaklığa çevriliyor             
  uzaklikSag = sureSag /29.1/2;
  uzaklikOn = sureOn /29.1/2;
  if(uzaklikSol > 200)
    uzaklikSol = 200;          
  if(uzaklikOn > 200)
    uzaklikOn= 200;
  if(uzaklikSag > 200)
    uzaklikSag = 200;
  Serial.print("Sol ");  
  Serial.print(uzaklikSol); // hesaplanan uzaklık bilgisayara aktarılıyor 
  Serial.print(" CM - On ");
  Serial.print(uzaklikOn);
  Serial.print(" CM - Sag ");
  Serial.print(uzaklikSag);
  Serial.println(" CM.");  
  */
 
  
}



void bir_kare_ileri(){
  analogWrite(hiz,  255);
 
  while(newPosition < 722){
    newPosition = myEnc.read();
  
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
      Serial.println(newPosition);
      }
    
    digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW); // in3, in4 ayaranacak.
    digitalWrite(in4, HIGH);
  }

  analogWrite(hiz,  0);
}

void ileri_x_kare(int kare_sayisi){
  analogWrite(hiz,  255);
 for(int i=0; i<kare_sayisi;i++){
    while(newPosition < (i+1)*722){
      newPosition = myEnc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
    }

 }
  analogWrite(hiz,  0);
  delay(750);
  myEnc.write(0);
}

void ileri_100_mm(){
  analogWrite(hiz, 255);
  while (newPosition < 145){
    newPosition = myEnc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
  }
}

void ileri_x_mm(){// yapım aşamasında
  analogWrite(hiz, 255);
  while (newPosition < 145){
    newPosition = myEnc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
  }
}

void saga_don_kendi_ekseninde(){

  analogWrite(hiz, 255);
  while (newPosition < 220){// arabayı yaptıktan sonra değişecek.
     newPosition = myEnc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre. SOL1
      digitalWrite(in2, HIGH); // SOL 2
      digitalWrite(in3, HIGH); // in3, in4 ayaranacak. SAĞ 1
      digitalWrite(in4, LOW);// SAĞ 2
  }
  
}

void sola_don_kendi_ekseninde(){

  analogWrite(hiz, 255);
  while (newPosition < 220){// arabayı yaptıktan sonra değişecek.
     newPosition = myEnc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        Serial.println(newPosition);
        }
      digitalWrite(in1, HIGH); // Duruma göre değiştirelecek ileri veya geri olamsına göre. SOL1
      digitalWrite(in2, LOW); // SOL 2
      digitalWrite(in3, LOW); // in3, in4 ayaranacak. SAĞ 1
      digitalWrite(in4, HIGH);// SAĞ 2
  }
  
}

