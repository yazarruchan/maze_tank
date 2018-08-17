#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Encoder.h>

MPU6050 mpu6050(Wire);

Encoder encSol(3,2);
Encoder encSag(20,21);
const int in1 = 6;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
const int in2 = 7;
const int in3 = 8;
const int in4 = 9;
int yol[10];
int trigPinSol = 22;
int echoPinSol = 23;  
int trigPinSag = 24;
int echoPinSag = 25;
int trigPinOn = 26;
int echoPinOn = 27;
int hiz =10;
int hiz2 =11;
int deneme=1; 
long newPosition, newPosition2;

long sureSol;
long sureSag;
long sureOn;
long uzaklikSol;
long uzaklikSag;
long uzaklikOn;
long oldPosition  = -999;
long oldPosition2 = -999;

void setup() {
  /*Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);// gyro sensörü için*/
  pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  Serial.println("Araba Çalıştı");
  
  pinMode(trigPinSol, OUTPUT);  //trig pini çıkış olarak ayarlandı
  pinMode(trigPinSag, OUTPUT);
  pinMode(trigPinOn, OUTPUT); 
  pinMode(echoPinSol,INPUT); // sol echo pini giriş olarak ayarlandı
  pinMode(echoPinSag,INPUT); // sağ echo pini giriş olarak ayarlandı
  pinMode(echoPinOn,INPUT); // ön echo pini giriş olarak ayarlandı
}

void loop() {
   /*
    for(int i=0; i<10 ;){
      if(Serial.available()>0){
        Serial.print("Yol ");
        Serial.print(i+1);
        Serial.println(" yazdiniz.");
       yol[i]=Serial.read();
       i++;
      }
   }
  
  for(int i=0; i<10 ;i++){
    Serial.print("Yol ");
    Serial.print(i);
    Serial.print(" ");
    Serial.println(yol[i]);
  }
  
  delay(5000);
*/
//  Uzaklık Sensörü Bölümü
  digitalWrite(trigPinSol, LOW);
  digitalWrite(trigPinSag, LOW);
  digitalWrite(trigPinOn, LOW);// sensör pasif hale getirildi 
  delayMicroseconds(5);
  digitalWrite(trigPinSol, HIGH);
  digitalWrite(trigPinSag, HIGH);
  digitalWrite(trigPinOn, HIGH);// Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPinSol, LOW);
  digitalWrite(trigPinSag, LOW);
  digitalWrite(trigPinOn, LOW);  // Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi
 
  sureSol = pulseIn(echoPinSol, HIGH); // ses dalgasının geri dönmesi için geçen sure ölçülüyor 
  sureSag = pulseIn(echoPinSag, HIGH); // ses dalgasının geri dönmesi için geçen sure ölçülüyor
  sureOn = pulseIn(echoPinOn, HIGH);
  uzaklikSol = sureSol /29.1/2;// ölçülen sure uzaklığa çevriliyor             
  uzaklikSag = sureSag /29.1/2;
  uzaklikOn = sureOn /29.1/2;
  if(uzaklikSol > 400)
    uzaklikSol = 400;          
  if(uzaklikOn > 400)
    uzaklikOn= 400;
  if(uzaklikSag > 400)
    uzaklikSag = 400;
 /* Serial.print("Sol ");  
  Serial.print(uzaklikSol); // hesaplanan uzaklık bilgisayara aktarılıyor 
  Serial.print(" CM - On ");
  Serial.print(uzaklikOn);
  Serial.print(" CM - Sag ");
  Serial.print(uzaklikSag);
  Serial.println(" CM.");  
*/
  
  
 // sictikMode();
  encoderDegerYazdir();



}

void diziHaraket(){
  
}


void sictikMode(){
  
  if( uzaklikSol > 30 && uzaklikOn < 15 ){
    Serial.println("kontrol_1");
    sola_don_kendi_ekseninde();
    duzGitOrtala(10);
    duzGitOrtala(10);
     
  }
  else if(uzaklikSag > 13 && uzaklikOn < 15){
    Serial.println("kontrol_2");
    saga_don_kendi_ekseninde();
    duzGitOrtala(10);
    duzGitOrtala(10);
  }
  else{
    Serial.println("kontrol_3");
    duzGitOrtala(10);
  }
  
}

void duzGitOrtala(int mesafe){
   if( uzaklikSol > 23 && uzaklikSag < 13 ){
  Serial.println("kontrol_4");
    ileri_x_kare_ikili(mesafe, 120, 170);
     
  }
  else if(uzaklikSag > 23 && uzaklikSol < 13){
    Serial.println("kontrol_5");
    ileri_x_kare_ikili(mesafe, 170, 120);
  }
  else{
    Serial.println("kontrol_6");
    ileri_x_kare_ikili(mesafe, 150, 150);
  }
}

void bir_kare_ileri(){
    analogWrite(hiz,  255);
    
    while(newPosition < 722){
      newPosition = encSol.read();
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
    analogWrite(hiz,  120);
    analogWrite(hiz2, 120);
// for(int i=0; i<kare_sayisi;i++){
    for(newPosition = encSol.read();newPosition < (kare_sayisi)*374;newPosition = encSol.read()){
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
        
        digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW); // in3, in4 ayaranacak.
        digitalWrite(in4, HIGH);
      }  
    }
    motorDurdur();
    delay(750);
// encoderDegerYazdir();
    encoderSifirla();
// delay(750);
//Serial.println("Encoder Sifirlandi.");
//encoderDegerYazdir();
}

void ileri_x_kare_ikili(int kare_sayisi, int hiz_1, int hiz_2){
    analogWrite(hiz,  hiz_1);
    analogWrite(hiz2, hiz_2);
    newPosition = encSol.read();
    newPosition2 = encSag.read();
    
    for(int i=0; i<kare_sayisi;i++){
      Serial.println("kontrol_7");
       while(newPosition < (i+1)*340 || newPosition2 < (i+1)*340){
         Serial.println("kontrol_8");
         if (newPosition != oldPosition || newPosition2 != oldPosition2) {
           Serial.println("kontrol_9");
           oldPosition = newPosition;
           oldPosition2 = newPosition2;
           encoderDegerYazdir();

         }
           
         digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
         digitalWrite(in2, HIGH);
         digitalWrite(in3, LOW); // in3, in4 ayaranacak.
         digitalWrite(in4, HIGH);
         newPosition = encSol.read();
         newPosition2 = encSag.read();
        
         } 
       }
     
     
    motorDurdur();
    encoderSifirla();
    Serial.print(kare_sayisi);
    Serial.println(" kare gitti.");
}

void ileri_100_mm(){
    analogWrite(hiz, 255);
    
    while (newPosition < 145){
      newPosition = encSol.read();
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
      newPosition = encSol.read();
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
    analogWrite(hiz,  135);
    analogWrite(hiz2, 135);

    for(newPosition = encSol.read();newPosition < 1460;newPosition = encSol.read()){
      if (newPosition != oldPosition) {
        oldPosition = newPosition;
        encoderDegerYazdir();
      }
        digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH); // in3, in4 ayaranacak.
        digitalWrite(in4, LOW);
      }
    /*float angle_old = mpu6050.getAngleZ();
    if(angle_old<265 && angle_old>275){
      if(angle_old<90){
        while(angle_old<265 && angle_old>275){
          digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
          digitalWrite(in2, HIGH);
          digitalWrite(in3, HIGH); // in3, in4 ayaranacak.
          digitalWrite(in4, LOW);
        }
      }
      else if(angle_old>90){
        while(angle_old<265 && angle_old>275){
          digitalWrite(in1, HIGH); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
          digitalWrite(in2, LOW);
          digitalWrite(in3, LOW); // in3, in4 ayaranacak.
          digitalWrite(in4, HIGH);
        }
      }
   }  */
  /*  while(angle_old-150<mpu6050.getAngleZ()){
      mpu6050.update();
             
      digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH); // in3, in4 ayaranacak.
      digitalWrite(in4, LOW);
        
      Serial.print(angle_old);
      Serial.print(" - ");
      Serial.println(mpu6050.getAngleZ());
    }*/
    motorDurdur();
    encoderSifirla();

}

void sola_don_kendi_ekseninde(){
     analogWrite(hiz,  135);
     analogWrite(hiz2, 135);
/*eski kod*/
     for(newPosition = encSol.read();newPosition > -1460;newPosition = encSol.read()){
       if (newPosition != oldPosition) {
         oldPosition = newPosition;
         encoderDegerYazdir();
     /*  }
     float angle_old = mpu6050.getAngleZ();
     delay(1000);
     while(angle_old+150>mpu6050.getAngleZ()){
       mpu6050.update();*/
      
       digitalWrite(in1, HIGH); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
       digitalWrite(in2, LOW);
       digitalWrite(in3, LOW); // in3, in4 ayaranacak.
       digitalWrite(in4, HIGH);
      
       
    }
    motorDurdur();
    encoderSifirla();
}
}

void doguya_don(){
    analogWrite(hiz,  250);
    analogWrite(hiz2, 250);
    
     float angle_old = gyro();
      
      if(angle_old<260 || angle_old>280){
        if(angle_old<90||angle_old>275){
          while(angle_old<265 || angle_old>280){
            angle_old=gyro();
            
            Serial.print("Saga Don - ");
            Serial.println(angle_old);
           
            digitalWrite(in1, LOW); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
            digitalWrite(in2, HIGH);
            digitalWrite(in3, HIGH); // in3, in4 ayaranacak.
            digitalWrite(in4, LOW);
          }
        }
       else if(angle_old>90||angle_old<275){
          while(angle_old<260 || angle_old>280){
            angle_old=gyro();
           
            Serial.print("Sola Don - ");
            Serial.println(angle_old);
            
            digitalWrite(in1, HIGH); // Duruma göre değiştirelecek ileri veya geri olamsına göre.
            digitalWrite(in2, LOW);
            digitalWrite(in3, LOW); // in3, in4 ayaranacak.
            digitalWrite(in4, HIGH);
         }
       }  
      Serial.println("------ Doguya Donuldu ------");
      }
     else{
      Serial.println("------ Arac Doguya Bakıyor ------");
      }
       
    motorDurdur();
    encoderSifirla();
}

void ortala(int solUzaklik, int sagUzaklik,int onUzaklik){
  int pozisyon = 0;
}

void encoderDegerYazdir(){
    Serial.print("Encoder Sol = ");
    Serial.print(encSol.read()); //ENKODERDEN GELEN BİLGİYİ GÖRÜNTÜLEMEK İÇİN
    Serial.print(" --- Encoder Sag = ");
    Serial.println(encSag.read());
}

void encoderSifirla(){
    delay(750);
    Serial.println("Sifirlanmadan Once");
    encoderDegerYazdir();
    encSol.write(0);
    encSag.write(0);
    oldPosition  = -999;
    oldPosition2 = -999;
}

void motorDurdur(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
}



float gyro(){
  float deger;
  mpu6050.update();
  deger=mpu6050.getAngleZ();
  if(deger>360){
    while(deger > 360){
      deger = deger -360;
    }
    return deger;
  }
  else if(mpu6050.getAngleZ()<0){
    while(deger < 0){
      deger = deger +360 ;
    }
    return deger;
  }
  else{
    return deger;
  }
}

