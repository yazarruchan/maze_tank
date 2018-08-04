#include <Encoder.h>

Encoder enc(2,4);
Encoder enc2(3,5);
const int in1 = 6;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;

/*int trigPin = 12; // Sensorun trig pini Arduinonun 6 numaralı ayağına bağlandı */
/*int echoPinSol = 13;  // Sensorun echo pini Arduinonun 7 numaralı ayağına bağlandı */
/*int echoPinSag = 11;
int echoPinOn = 10;*/
int hiz =10;
int hiz2 =11;
int deneme=1;
long newPosition, newPosition2;
/*long sureSol;
long sureSag;
long sureOn;
long uzaklikSol;
long uzaklikSag;
long uzaklikOn;*/
long oldPosition  = -999;
long oldPosition2 = -999;

void setup() {
  pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
 /* pinMode(trigPin, OUTPUT);  //trig pini çıkış olarak ayarlandı 
 / pinMode(echoPinSol,INPUT); // sol echo pini giriş olarak ayarlandı
 / pinMode(echoPinSag,INPUT); // sağ echo pini giriş olarak ayarlandı
 / pinMode(echoPinOn,INPUT); // ön echo pini giriş olarak ayarlandı*/
  
}
 



void loop() {
  
  //Serial.println("Calismasina son");
  for(int sayac; sayac<3; sayac++){
  //Serial.print(3-sayac);
  //Serial.println(" saniye.");
  delay(1000);
  }
 // encoderDegerYazdir();
  Serial.print(deneme);
  Serial.println(". deneme");
  ileri_x_kare(1);
  deneme++;
 
 /* Uzaklık Sensörü Bölümü
  digitalWrite(trigPin, LOW);  // sensör pasif hale getirildi 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); // Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  // Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
 
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
    newPosition = enc.read();
  
    if (newPosition != oldPosition) {
      oldPosition = newPosition;
      encoderDegerYazdir();
      }
    
    digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW); // in3, in4 ayaranacak.
    digitalWrite(in4, HIGH);
  }

  analogWrite(hiz,  0);
}

void ileri_x_kare(int kare_sayisi){
  
  analogWrite(hiz,  150);
  analogWrite(hiz2, 150);
 for(int i=0; i<kare_sayisi;i++){
    for(newPosition = enc.read();newPosition < (i+1)*740;newPosition = enc.read()){
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
       // encoderDegerYazdir();
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);

    }
  
  }
 motorDurdur();
 delay(1000);
 encoderDegerYazdir();
 
 encoderSifirla();
 delay(750);
//Serial.println("Encoder Sifirlandi.");
 //encoderDegerYazdir();
}

void ileri_x_kare_ikili(int kare_sayisi){
  analogWrite(hiz,  150);
  analogWrite(hiz2, 150);
 for(int i=0; i<kare_sayisi;i++){
    while(newPosition < (i+1)*500 || newPosition2 < (i+1)*950){
      newPosition = enc.read();
      if (newPosition != oldPosition || newPosition2 != oldPosition2) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
    }
  }
 motorDurdur();
 encoderSifirla();
}

void ileri_100_mm(){
  analogWrite(hiz, 255);
  while (newPosition < 145){
    newPosition = enc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
    }
 motorDurdur();
  encoderSifirla();
}

void ileri_x_mm(){// yapım aşamasında
  analogWrite(hiz, 255);
  while (newPosition < 145){
    newPosition = enc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW); // in3, in4 ayaranacak.
      digitalWrite(in4, HIGH);
    }
   motorDurdur();
   encoderSifirla();
}

void saga_don_kendi_ekseninde(){

  analogWrite(hiz, 255);
  while (newPosition < 220){// arabayı yaptıktan sonra değişecek.
     newPosition = enc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        }
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre. SOL1
      digitalWrite(in2, HIGH); // SOL 2
      digitalWrite(in3, HIGH); // in3, in4 ayaranacak. SAĞ 1
      digitalWrite(in4, LOW);// SAĞ 2
    }
  motorDurdur();
  encoderSifirla();
}

void sola_don_kendi_ekseninde(){

  analogWrite(hiz, 255);
  while (newPosition < 220){// arabayı yaptıktan sonra değişecek.
     newPosition = enc.read();
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        }
      digitalWrite(in1, HIGH); // Duruma göre değiştirelecek ileri veya geri olamsına göre. SOL1
      digitalWrite(in2, LOW); // SOL 2
      digitalWrite(in3, LOW); // in3, in4 ayaranacak. SAĞ 1
      digitalWrite(in4, HIGH);// SAĞ 2
    }
  motorDurdur();
  encoderSifirla();
}

void ortala(int solUzaklik, int sagUzaklik,int onUzaklik){
  int pozisyon = 0;
}

void encoderDegerYazdir(){
    Serial.print("Encoder 1 = ");
    Serial.print(enc.read()); //ENKODERDEN GELEN BİLGİYİ GÖRÜNTÜLEMEK İÇİN
    Serial.print(" --- Encoder 2 = ");
    Serial.println(enc2.read());
   
}

void encoderSifirla(){
    delay(750);
    enc.write(0);
    enc2.write(0);
    oldPosition  = -999;
    oldPosition2 = -999;
    
}

void motorDurdur(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
}

