/////////////*************//////////////////*****************////////////////******************

//Sensör pinlerimizi tanımlıyoruz:
#define sensor_pin A0
#define buzzer_pin 9
//RGB LED'imizin çıkış pinlerini tanımlıyoruz:                           // GAZ SENSÖRÜ
#define led_r 7
#define led_g 6
#define led_b 5
//Sensörün çalışması için gerekli ön ısıtma süresini 5sn olarak belirliyoruz
#define preheat_time 5000
//Alarmın çalması için gerekli eşik değerini 300 olarak belirliyoruz.
#define threshold 300


////////////////*****************////////********///////////************///////////////

const int sensorMin = 0; // ALEV SENSÖRÜ EŞİKDEĞERLERİ
const int sensorMaks = 1024;
int buzzerPin = 2;      // BAZER DEĞERLERİ VE PİN İ
int C = 262;                                                           // ALEV SENSÖRÜ
int D = 294;
int E = 330;
int notalar[] = {C, D, E,};
#define led_A 13
#define led_B 12
#define led_C 11

///////////////////////************************///////////////////*******************/////////////

  #include <dht11.h> // dht11 kütüphanesini ekliyoruz.
  #define DHT11PIN 34 // DHT11PIN olarak Dijital 34"yi belirliyoruz.         // SICAKLIK SENSÖRÜ
  float a = 23;
  dht11 DHT11;
  int deger;

  /////////////////********************///////////////////******************//////////////////


void setup() {



  ///////////////////*******************///////////////////***************////////////

  //Alarm için kullanacağımız buzzer ve LED'leri çıkış olarak tanımlıyoruz
  pinMode(buzzer_pin, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
  //Varsayılan olarak LED'in sönük kalmasını sağlıyoruz
  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, HIGH);                                                                  // GAZ SENSÖRÜ
  digitalWrite(led_b, HIGH);
  //Sensör değerini seri monitörden görebilmemiz için seri haberleşmeyi başlatıyoruz:
  Serial.begin(9600);
  //İlk 5sn boyunca sensörün ısınmasını bekliyoruz. Bu esnada LED mavi renkte yanıyor:
  Serial.println("Sensor isitiliyor...");
  digitalWrite(led_b, LOW);
  delay(preheat_time);
  //Isıma işlemi için gereken 5sn süre tamamlandığında mavi LED'i söndürüyoruz:
  digitalWrite(led_b, HIGH);
  delay(1000);


  ///////////////////////*******************////////////////****************///////////////*************

  int i = 0;
  Serial.begin(9600);                                                                     // ALEV SENSÖRÜ
  pinMode (2, OUTPUT);
  pinMode(led_A, OUTPUT);
  pinMode(led_B, OUTPUT);
  pinMode(led_C, OUTPUT);

  //////////////////***********************///////////////////**********************//////////////////////******

  Serial.begin(9600); // Seri iletişimi başlatıyoruz.
  pinMode(32, OUTPUT);

  ///////////**************////////////******************/////////////*************/////////********
}


void loop() {



  /////////////*******************/////////////*************//////////////***********

  //analogRead() fonksiyonu ile sensör değerini ölçüyoruz ve bir değişken içerisinde tutuyoruz:
  int sensorValue = analogRead(sensor_pin);
  //Sensör değeri belirlediğimiz eşik değerinden yüksek ise alarm() fonksiyonunu çağırıyoruz:
  if (sensorValue > threshold)
    alarm(100);                                                                                 // GAZ SENSÖRÜ
  //Alarmın çalmadığı durumda LED'in yeşil yanmasını istiyoruz:
  else
    digitalWrite(led_g, LOW);
  //Sensör değerini bilgisayarımızdan görebilmek için seri monitöre yazıyoruz:

  

  ////////////////********************//////////////////**************////////////////////////////***************


  // put your main code here, to run repeatedly:
  int sensorDegeri = analogRead(A1);  // ALEV SENSÖRÜ ANALOG PİNİ
  int aralik = map(sensorDegeri, sensorMin, sensorMaks, 0, 2);
  switch (aralik) {
    case 0:
      digitalWrite(2, HIGH);
      digitalWrite(led_A, LOW);
      digitalWrite(led_B, HIGH);
      digitalWrite(led_C, HIGH);
      for (int i = 0 ; i < 3; i++) {
        tone(buzzerPin, notalar[i]);
        delay(200);
        noTone(buzzerPin);
        delay(50);
      }

      Serial.print("Sicaklik sensörü: ");
      Serial.println(deger);
      
      if (sensorValue > 300) {
        Serial.print("Gaz Sensörü : ");
        Serial.println("GAZ ALARM !!");
      }
      else {
        Serial.print("Gaz Sensörü : ");
        Serial.println(sensorValue);
      }
    

      Serial.print("Alev  Sensörü : ");                                                   // ALEV SENSÖRÜ
      Serial.println("**Yangin!**");

      break;

    case 1:
       Serial.print("Sicaklik sensörü: ");
      Serial.println(deger);
      if (sensorValue > 300) {
        Serial.print("Gaz Sensörü : ");
        Serial.println("GAZ ALARM !!");
      }
      else {
        Serial.print("Gaz Sensörü : ");
        Serial.println(sensorValue);
      }
      
      Serial.print("Alev  Sensörü : ");
      Serial.println("Ates Algilanmadi");
      digitalWrite(2, LOW);
      digitalWrite(led_A, HIGH);
      digitalWrite(led_B, HIGH);
      digitalWrite(led_C, LOW);
      break;
  }


  //////////////////////////////********************///////////////////****************///////////
 
    // Bir satır boşluk bırakıyoruz serial monitörde.
    Serial.println();
    // Sensörün okunup okunmadığını konrol ediyoruz.
    // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
    // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.
    int chk = DHT11.read(DHT11PIN);

    // Sensörden gelen verileri serial monitörde yazdırıyoruz.
   
                                                                          //   SICAKLIK SENSÖRÜ
      
    deger=((int)DHT11.temperature);
    if(deger >= a){
      digitalWrite(32,HIGH);
    }
    else{
      digitalWrite(32,LOW);
    }
    // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.

    delay(500);
    //////////************************///////////////////////***********************////////////////////////////****************
 
}



/////////////////*****************//////////////*************////////////////****************///++++++++++++++++++++//
//Alarm fonksiyonumuzu tanımlıyoruz. Bu fonksiyon parametre olarak buzzerın ötüp ve LED'in yanıp söneceği süreyi almakta.

void alarm(unsigned int duration)
{
  //Buzzer'ın 440Hz'te (la notası) ses üretmesini istiyoruz:
  tone(buzzer_pin, 550);
  //Normal durumda yeşil yanmakta olan LED'i söndürüp kırmızı renkte yakıyoruz:                       // GAZ SENSÖRÜ ALARM KISMI
  digitalWrite(led_r, LOW);
  digitalWrite(led_g, HIGH);
  delay(duration);
  noTone(buzzer_pin);
  digitalWrite(led_r, HIGH);
  digitalWrite(led_g, HIGH);
  delay(duration);
}
///////////*********************/////////////////////*********************///////////////////*****
