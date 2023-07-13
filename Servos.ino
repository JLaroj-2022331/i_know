#include <Servo.h> 

#define LedPasillo 2
#define LedPatio 3
#define pin_Servo1 6
#define pin_Servo2 9
#define pin_Servo3 10
#define pin_Servo4 11

int buzzerPin = 4; 

Servo ServoCuarto;
Servo ServoEntrada;
Servo ServoGaraje;
Servo ServoToilet;
int suma;
String Respuesta;

int frecuencia  = 5000;
int si = 493.883;
int fa = 698.456;

void setup()
{
pinMode(buzzerPin, OUTPUT);
pinMode(LedPasillo, OUTPUT);
pinMode(LedPatio, OUTPUT);
Serial.begin(9600);
ServoCuarto.attach(pin_Servo1);
ServoEntrada.attach(pin_Servo2);
ServoGaraje.attach(pin_Servo3);
ServoToilet.attach(pin_Servo4); 
ServoCuarto.write(0);
ServoEntrada.write(0);
ServoGaraje.write(0);
ServoToilet.write(0);

}

void loop()
{
tone(buzzerPin, fa, 10000);
delay(250);
tone(buzzerPin, si, 10000);
delay(250);
noTone(buzzerPin);

Respuesta = Serial.readStringUntil('\n');

for(int i=0; i<6; i++)
{
 i=suma; 
}

switch(suma)
{
case 0:
if(Respuesta == String("9"))
{
   ServoCuarto.write(90);
   Serial.println("Servo Activo");
}
else if(Respuesta == String("10"))
{
   ServoCuarto.write(0);
   Serial.println("servo desactivado");  
}
break;
   
case 1:
if(Respuesta == String("11"))
{
   ServoEntrada.write(90);
   Serial.println("puerta abierta");
}
else if(Respuesta == String("12"))
{
   ServoEntrada.write(0);
   Serial.println("puerta cerrada");  
}

case 2:
if(Respuesta == String("13"))
{
ServoGaraje.write(0);
delay(1000);
ServoGaraje.write(45);
delay(1000);
ServoGaraje.write(90);
delay(1000);
ServoGaraje.write(135);
delay(1000);
ServoGaraje.write(180);
delay(1000);
}
else if(Respuesta == String("14"))
{
ServoGaraje.write(180);
delay(1000);
ServoGaraje.write(135);
delay(1000);
ServoGaraje.write(90);
delay(1000);
ServoGaraje.write(45);
delay(1000);
ServoGaraje.write(0);
delay(1000);
ServoGaraje.write(0);
}

case 3:
if(Respuesta == String("15"))
{
   ServoToilet.write(90);
   Serial.println("puerta abierta");
}
else if(Respuesta == String("16"))
{
   ServoToilet.write(0);
   Serial.println("puerta cerrada");  
}

case 4:
if(Respuesta == String("17"))
{
  digitalWrite(LedPasillo, HIGH);
   Serial.println("pasillo encendido");
}
else if(Respuesta == String("18"))
{
   digitalWrite(LedPasillo, LOW);  
   Serial.println("Pasillo apagado");  
}

case 5:
if(Respuesta == String("19"))
{
  digitalWrite(LedPatio, HIGH);
   Serial.println("patio iluminado");
}
else if(Respuesta == String("20"))
{
   digitalWrite(LedPatio, LOW);  
   Serial.println("Patio apagado");  
}
} 
}
