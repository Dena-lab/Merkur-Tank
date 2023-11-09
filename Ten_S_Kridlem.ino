#include <hcsr04.h>

//gnd bila   vcc zelena
#define TRIG 3    //modra
#define ECHO 2    //fialova
HCSR04 hcsr04(TRIG, ECHO, 20, 4000);

//vcc cervena    gnd hneda
#define s0 8    //zluta     
#define s1 9    //oranzova
#define s2 10   //modra
#define s3 11   //fialova
#define out 12  //zelena

int data=0;    
int red = 0;
int green = 0;
int blue = 0;


#define A1A A0    //oranzova
#define A1B A1    //zluta
#define B1A A2    //hneda
#define B1B A3    //cervena
#define ENA 5
#define ENB 6

void setup(){
  Serial.begin(9600);

  pinMode(s0,OUTPUT);   
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(out,INPUT); 

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(A1A, OUTPUT);
  pinMode(A1B, OUTPUT);
  pinMode(B1A, OUTPUT);
  pinMode(B1B, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  
  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  
  digitalWrite(A1A, HIGH);
  digitalWrite(A1B, LOW);
  digitalWrite(B1A, HIGH);
  digitalWrite(B1B, LOW);
  analogWrite(ENA, 196);
  analogWrite(ENB, 196);
}

void loop() {

   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red value= "); 
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration      and stops when "out" is HIGH again
   red = (map(data,60,15,0,100));  
   Serial.print(red);      
   Serial.print("\t");          
   delay(20);
                      
   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue value= ");
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   blue = (map(data,80,11,0,100)); 
   Serial.print(blue);         
   Serial.print("\t");          
   delay(20);

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green value= ");
   data=pulseIn(out,LOW);  //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   green = (map(data,80,20,0,100));
   Serial.print(green);          
   Serial.print("\t");          
   delay(20);


   if (red > green-5 && red < green+5 && red > blue-5 && red < blue+5 &&
       green > red-5 && green < red+5 && green > blue-5 && green < blue+5 &&
       blue > green-5 && blue < green+5 && blue > red-5 && blue < red+5) {
     Serial.print("WHITE");

   } else if (red < 0 && green < 0 && blue < 5) {
     Serial.print("BLACK");

   } else if (red > green && red > blue) {
     Serial.print("RED");

   } else if (green > red && green > blue) {
     Serial.print("GREEN");

   } else if (blue > red && blue > green) {
     Serial.print("BLUE");

   }
   Serial.print("\t");

   Serial.print(hcsr04.ToString());
   Serial.print("\t");
   Serial.print("mm");

   Serial.print("\t");

   Serial.println();

   delay(200);
}
