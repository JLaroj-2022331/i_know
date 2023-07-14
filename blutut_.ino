#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

//Directivas de preprocesador.
#define relay_1 12
#define relay_2 13
#define relay_3 A1
#define relay_4 A2
#define LedPasillo 2
#define LedPatio 3
#define pin_Servo1 6
#define pin_Servo2 9
#define pin_Servo3 10
#define pin_Servo4 11

int buzzerPin = 4; 

char valor;
String estado;
int usuario=0;
int adc, cover;

//Constructores.
LiquidCrystal_I2C lcd(0x27,16,2);  
Servo ServoCuarto;
Servo ServoEntrada;
Servo ServoGaraje;
Servo ServoToilet;

//Configuraciones.
void setup() {
//Inicio la comunicación Serial.
Serial.begin(9600); 
//Declaro los pines de los relays como salidas.
pinMode(relay_1, OUTPUT);
pinMode(relay_2, OUTPUT);
pinMode(relay_3, OUTPUT);
pinMode(relay_4, OUTPUT);
pinMode(buzzerPin, OUTPUT);
pinMode(LedPasillo, OUTPUT);
pinMode(LedPatio, OUTPUT);
ServoCuarto.attach(pin_Servo1);
ServoEntrada.attach(pin_Servo2);
ServoGaraje.attach(pin_Servo3);
ServoToilet.attach(pin_Servo4); 
ServoCuarto.write(0);
ServoEntrada.write(0);
ServoGaraje.write(0);
ServoToilet.write(0);
//Inicializo la lcd.
lcd.init();
//Enciendo la luz del fondo.
lcd.backlight();
//Posiciono el Cursor, en la columna 6, fila 1
lcd.setCursor(6,0);
lcd.print("Casa");
//Posiciono el Cursor, en la columna 4, fila 2
lcd.setCursor(4,1);
lcd.print("Domotica");
delay(2000);
lcd.clear();
 
}

void loop() {
//Llama a la función del sensor de humo mq2.
mq2();
//Si el usuario, vale 1, ya se puede acceder a las funciones de la Casa.
if(usuario==1)
{
switch(valor){
//Si el dato entrante via bluetooth, es 1, se activara el primer relay, activando el bombillo.
case '1':
Serial.println("El bombillo 1, ha sido activado.");
digitalWrite(relay_1, LOW);
break;
//Si el dato entrante via bluetooth, es 2, se desactivara el primer relay, desactivando el bombillo.
case '2':
Serial.println("El bombillo 1, ha sido desactivado.");
digitalWrite(relay_1, HIGH);
break;
//Si el dato entrante via bluetooth, es 3, se activara el segundo relay, activando el bombillo.
case '3':
Serial.println("El bombillo 2, ha sido activado.");
digitalWrite(relay_2, LOW);
break;
//Si el dato entrante via bluetooth, es 4, se desactivara el segudno relay, desactivando el bombillo.
case '4':
Serial.println("El bombillo 2, ha sido desactivado.");
digitalWrite(relay_2, HIGH);
break;
//Si el dato entrante via bluetooth, es 5, se activara el tercer relay, activando el bombillo.
case '5':
Serial.println("El bombillo 3, ha sido activado.");
digitalWrite(relay_3, LOW);
break;
//Si el dato entrante via bluetooth, es 6, se desactivara el tercer relay, desactivando el bombillo.
case '6':
Serial.println("El bombillo 3, ha sido desactivado.");
digitalWrite(relay_3, HIGH);
break;
//Si el dato entrante via bluetooth, es 7, se activara el cuarto relay, activando el bombillo.
case '7':
Serial.println("El bombillo 4, ha sido activado.");
digitalWrite(relay_4, LOW);
break;
//Si el dato entrante via bluetooth, es 8, se desactivara el cuarto relay, desactivando el bombillo.
case '8':
Serial.println("El bombillo 4, ha sido desactivado.");
digitalWrite(relay_4, HIGH);
break;

case '9':
ServoCuarto.write(90);
Serial.println("Cuarto Abierto");
break;

case '10':
   ServoCuarto.write(0);
   Serial.println("Cuarto Cerrado");  
break;

case '11':
   ServoEntrada.write(90);
   Serial.println("puerta abierta");  
break;

case '12':
   ServoEntrada.write(0);
   Serial.println("puerta cerrada");    
break;

case '13':
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
  Serial.println("garaje abierto");    
break;

case '14':
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
  Serial.println("garaje Cerrado");    
break;

case '15':
   ServoToilet.write(90);
   Serial.println("baño abierto");   
break;

case '16':
   ServoToilet.write(0);
   Serial.println("baño cerrado");   
break;

case '17':
  digitalWrite(LedPasillo, HIGH);
  Serial.println("pasillo encendido"); 
break;

case '18':
   digitalWrite(LedPasillo, LOW);  
   Serial.println("Pasillo apagado"); 
break;

case '19':
  digitalWrite(LedPatio, HIGH);
  Serial.println("patio iluminado");
break;

case '20':
   digitalWrite(LedPatio, LOW);  
   Serial.println("Patio apagado");  
break;
}

}
//Si el puerto serie (Bluetooth) está disponible
if (Serial.available())
{
//Lee el dato entrante via Bluetooth
valor = Serial.read(); 
//Si el dato entrante es una A
if (valor == 'A')  
{
//Llama la función que muestra el mensaje en la pantalla LCD
texto();  
}
}
//Función del mensaje entrante.
}
void texto()
{
delay(30);
while (Serial.available())
{
//Lee el dato entrante y lo almacena en una variable tipo char
char c = Serial.read();  
//Crea una cadena tipo String con los datos entrates
estado += c;            
}
//Se verifica que la cadena tipo String tenga un largo mayor a cero
if (estado.length() > 0)   
{
//Muestra el mensaje en la pantalla LCD
Serial.println(estado);    

//Si la contraseña es correcta.
if(estado == String("CASADOMOTICA1"))
{
//Se cambia el valor del usuario a 1, quiere decir que ingreso a la casa.
usuario=1;
//Se imrpime en el monitor serial, que la contraseña es correcta.
Serial.println("La contraseña que ha ingresado, es correcta");
//Se imrpime en el lcd, que la contraseña es correcta.
lcd.setCursor(1,0);
lcd.print("La contrasena");
lcd.setCursor(2,1);
lcd.print("es correcta");
delay(1500);
lcd.clear();
lcd.setCursor(3,0);
lcd.print("Bienvenido");
delay(1500);
 
}
//Si la contraseña no es correcta.
else{
//Se cambia el valor del usuario a 0, quiere decir que el ingreso no fue posible.
usuario=0;
//Se imrpime en el monitor serial, que la contraseña es incorrecta.
Serial.println("La contraseña que ha ingresado, es incorrecta");
Serial.println("reintentelo de nuevo");
//Se imrpime en el lcd, que la contraseña es incorrecta.
lcd.setCursor(1,0);
lcd.print("La contrasena");
lcd.setCursor(2,1);
lcd.print("es incorrecta");
delay(1500);
lcd.clear();
lcd.setCursor(3,0);
lcd.print("Reintentelo");
delay(1500);
}
    
estado = "";      
}
}
//Funcion del sensor de humo MQ2.
void mq2()
{
//Se hace la lectura del pin analogico A0.
adc=analogRead(A0);
//Se usa la funcion map, para obtener un rango de 0 a 1024, para poder saber el valor del humo que ha detectado el sensor.
cover = map(adc,0,1024,0,100);
//Se imprime, la variable la cual se ha usado en la funcion map.
Serial.print("adc:");
Serial.print(adc);
return adc;
delay(200);
}
