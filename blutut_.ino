
#include <LedControl.h>
#include <Ticker.h>

int valorS, ok;
int seg;

volatile static bool estado_mq2;
void isr_sensor(void); 

LedControl lc=LedControl(11,13,10,1);
Ticker isr_accion_SensorG(isr_sensor, 2000);

void setup()
{
Serial.begin(9600);
lc.shutdown(0,false);
lc.setIntensity(0,4);
lc.clearDisplay(0);
isr_accion_SensorG.start(); 
}
void loop()
{
isr_accion_SensorG.update();
}

void copo_God()
{
byte copo_nieve[8]=
{
  B00111100,       
  B10011011,
  B01011010,
  B00111100,
  B11100111,
  B00111100,
  B01011010,
  B10011001
};

for(int i=0; i<8;i++)
{
lc.setRow(0,i,copo_nieve[i]);
}}
void llama_good()
{

byte llama[8]=
{
  B00000101,        
  B00000010,
  B00011100,
  B00101010,
  B01000011,
  B11000011,
  B01100010,
  B00111100
};  

for(int i=0; i<8;i++)
{
lc.setRow(0,i,llama[i]);
}}
void isr_sensor(void)
{
valorS=analogRead(A5);
ok = map(valorS,0,1024,0,100);
Serial.print("adc:");
Serial.print(valorS);
Serial.println("   porcentaje:");
Serial.println(ok);
Serial.println(valorS);
if(valorS>400)
{
if(seg==0)
{
parpadeo();}
if(seg==1)
{
llama_good();
}
}

else{
copo_God();
seg=0;
}
}

void parpadeo()
{
llama_good();
delay(1000);  
lc.clearDisplay(0);
delay(1000);
llama_good();
delay(1000);  
lc.clearDisplay(0);
delay(1000);
llama_good();
delay(1000);  
seg=1;
}
