#include <BH1750.h>

#include <Wire.h>

#define MAX 16

const int BUTTON_PIN = 9;  // 按鍵的接腳
int leda = 10;
int buttonState = 0;   // 按鈕的狀態
bool doing = false;

int tim=0;
int led[4]={0,30,60,90};
int open(int);
float total=0;

BH1750 lightMeter;

void setup() {
 Serial.begin(9600);
 Wire.begin();          //監控埠開啟
 
 pinMode(10,OUTPUT);    //0
 pinMode(11,OUTPUT);    //30
 pinMode(12,OUTPUT);    //60
 pinMode(13,OUTPUT);    //90  4led on

 pinMode(BUTTON_PIN, INPUT_PULLUP); //設定按鈕的接腳為輸入，因為我們要讀取它的狀態

 
  lightMeter.begin();
  Serial.println(F("BH1750 Test")); // title
}

void loop() {
    buttonState = digitalRead(BUTTON_PIN);

          
   if(buttonState == LOW){          //如果按鍵按了
    doing = true;
  }
  if(doing){
    for(int tim = 0; tim <= 3 ; tim++){
        total=0;
        leda = 10;
        digitalWrite(leda+tim,HIGH);
        float luxe=open(tim+10);  
        digitalWrite(leda+tim,LOW);
        
        Serial.print("Light ");
        Serial.print(led[tim]);
        Serial.print(" :");  
        Serial.print(luxe);
        Serial.println(" lx");
        
        delay(100);
    }
    
    Serial.println("The experiment end!!!Please take another or end");
    
    doing = false;
    delay(500);      
  }
delay(100);
}
int open(int test){
  
  float big=0;
  float small=999999;
  
  for(int i=0;i<MAX;i++){
    float lux = lightMeter.readLightLevel();
    big = (lux>big) ? lux : big;
    small = (lux<small) ? lux : small;
    total += lux;
    delay(2000/MAX);   
  }

  analogWrite(test, 0);
  total=total-big-small;
  
  return total/(MAX-2); //取max次平均
  
}
