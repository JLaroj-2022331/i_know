#include <SoftwareSerial.h>
SoftwareSerial ok(10, 11);

void setup() 
{
Serial.begin(9600);
ok.begin(38400);
pinMode(12, OUTPUT);
}

char recibir;
void loop() 
{
if(ok.available())
{
recibir = ok.read();
Serial.println(recibir);

if(recibir == '1')
{
  digitalWrite(12, HIGH);
}
if(recibir == '2')
{
  digitalWrite(12, LOW);
}
}
}
