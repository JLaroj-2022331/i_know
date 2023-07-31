//Librerias.
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

//Directivas de preprocesador.
#define relay_1 12
#define relay_2 13
#define relay_3 A1
#define relay_4 A2
#define LedPasillo 2
#define LedPatio 4
#define pin_Servo1 3
#define pin_Servo2 6
#define pin_Servo3 5
#define pin_Servo4 9
int buzzerPin = 4; 
char valor;
String estado;
int usuario=0;
const int Radarpin_habitacion=8;
const int Radarpin_entrada=10;
const int Radarpin_x=11;
const int Radarpin_y=A3;
int pin_mq2 = A0;
int buzzer_pin = 7;

float si_septima = 3951.07;
float do_septima = 2093.00;
//Constructores.
LiquidCrystal_I2C lcd(0x27,16,2);  
Servo Servo_habitacion;
Servo Servo_entrada;
Servo Servo_garage;
Servo Servo_sanitario;

//Configuraciones.
void setup() {
//Inicio la comunicación Serial.
Serial.begin(9600); 
//Declaro los pines de los relays como salidas.
pinMode(relay_1, OUTPUT);
pinMode(relay_2, OUTPUT);
pinMode(relay_3, OUTPUT);
pinMode(relay_4, OUTPUT);
//Declaro el pin del buzzer, como salida.
pinMode(buzzer_pin,OUTPUT);
//Declaro el pin de los leds, como salida.
pinMode(LedPasillo, OUTPUT);
pinMode(LedPatio, OUTPUT);
//Declaro a los pines de los sensores RCWL-0516, como entradas.
pinMode(Radarpin_habitacion,INPUT);  
pinMode(Radarpin_entrada,INPUT);
pinMode(Radarpin_x,INPUT);
pinMode(Radarpin_y,INPUT);    
//Declaro el pin digital del sensor MQ2, como entrada.
pinMode(pin_mq2,INPUT);
//Declaro en que pin se va a encontrar cada servo motor.
Servo_habitacion.attach(pin_Servo1);
Servo_entrada.attach(pin_Servo2);
Servo_garage.attach(pin_Servo3);
Servo_sanitario.attach(pin_Servo4); 
//Inicializo los 4 servomotores, con un giro de 0 grados.
Servo_habitacion.write(0);
Servo_entrada.write(0);
Servo_garage.write(0);
Servo_sanitario.write(0);
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
//Declaro la variable "mq_estado", como una variable booleana, para que interprete entre dos condiciones logicas, false o true, cuando lea el pin del sensor mq2.
boolean mq_estado = digitalRead(pin_mq2);
//Si el sensor mq2, esta activo, quiere decir que no detecta presensia de gas, por lo tanto desactivara el buzzer.
if(mq_estado)
{
Serial.println("No hay ningun gas");
lcd.setCursor(1,0);
lcd.print("nada detectado");
lcd.setCursor(3,1);
lcd.print("todo bien");
noTone(buzzer_pin);
}
//En caso de que no este activo, quiere decir que si hay gas, por lo tanto se activara el buzzer.
else{
Serial.println("Gas detectado");
lcd.setCursor(1,0);
lcd.print("GAS DETECTADO");
lcd.setCursor(3,1);
lcd.print("PELIGRO!!!");
tone(buzzer_pin, si_septima,700);
delay(800);
}
//Si el usuario, vale 1, ya se puede acceder a las funciones de la Casa.
if(usuario==1)
{
switch(valor){
//Si el dato entrante via bluetooth, es 1, se activara el primer relay, activando el bombillo.
case '1':
  Serial.println("El bombillo 1, ha sido activado.");
  digitalWrite(relay_1, LOW);
  lcd.setCursor(3,0);
  lcd.print("bombillo 1 ");
  lcd.setCursor(5,3);
  lcd.print("activo");
break;
//Si el dato entrante via bluetooth, es 2, se desactivara el primer relay, desactivando el bombillo.
case '2':
  Serial.println("El bombillo 1, ha sido desactivado.");
  digitalWrite(relay_1, HIGH);
  lcd.setCursor(3,0);
  lcd.print("bombillo 1 ");
  lcd.setCursor(3,3);
  lcd.print("desactivado");
break;
//Si el dato entrante via bluetooth, es 3, se activara el segundo relay, activando el bombillo.
case '3':
  Serial.println("El bombillo 2, ha sido activado.");
  digitalWrite(relay_2, LOW);
  lcd.setCursor(3,0);
  lcd.print("bombillo 2 ");
  lcd.setCursor(5,3);
  lcd.print("activo");
break;
//Si el dato entrante via bluetooth, es 4, se desactivara el segudno relay, desactivando el bombillo.
case '4':
  Serial.println("El bombillo 2, ha sido desactivado.");
  digitalWrite(relay_2, HIGH);
  lcd.setCursor(3,0);
  lcd.print("bombillo 2 ");
  lcd.setCursor(3,3);
  lcd.print("desactivado");
break;
//Si el dato entrante via bluetooth, es 5, se activara el tercer relay, activando el bombillo.
case '5':
  Serial.println("El bombillo 3, ha sido activado.");
  digitalWrite(relay_3, LOW);
  lcd.setCursor(3,0);
  lcd.print("bombillo 3 ");
  lcd.setCursor(5,3);
  lcd.print("activo");
break;
//Si el dato entrante via bluetooth, es 6, se desactivara el tercer relay, desactivando el bombillo.
case '6':
  Serial.println("El bombillo 3, ha sido desactivado.");
  digitalWrite(relay_3, HIGH);
  lcd.setCursor(3,0);
  lcd.print("bombillo 3 ");
  lcd.setCursor(3,3);
  lcd.print("desactivado");
break;
//Si el dato entrante via bluetooth, es 7, se activara el cuarto relay, activando el bombillo.
case '7':
  Serial.println("El bombillo 4, ha sido activado.");
  digitalWrite(relay_4, LOW);
  lcd.setCursor(3,0);
  lcd.print("bombillo 4 ");
  lcd.setCursor(5,3);
  lcd.print("activo");
break;
//Si el dato entrante via bluetooth, es 8, se desactivara el cuarto relay, desactivando el bombillo.
case '8':
  Serial.println("El bombillo 4, ha sido desactivado.");
  digitalWrite(relay_4, HIGH);
  lcd.setCursor(3,0);
  lcd.print("bombillo 4 ");
  lcd.setCursor(3,3);
  lcd.print("desactivado");
break;
//Si el dato entrante via bluetooth, es b, el servomotor hara un giro de 90°, abriendo la puerta de la habitacion.
case 'b':
  Servo_habitacion.write(90);
  Serial.println("La puerta de la habitacion ha sido abierta");
  lcd.setCursor(3,0);
  lcd.print("Habitacion ");
  lcd.setCursor(5,3);
  lcd.print("abierta");
break;
//Si el dato entrante via bluetooth, es c, el servomotor hara un giro de 0°, cerrando la puerta de la habitacion.
case 'c':
  Servo_habitacion.write(0);
  Serial.println("La puerta de la habitacion ha sido cerrada");  
  lcd.setCursor(3,0);
  lcd.print("Habitacion ");
  lcd.setCursor(5,3);
  lcd.print("Cerrada");
break;
//Si el dato entrante via bluetooth, es d, el servomotor hara un giro de 90°, abriendo la puerta de la entrada de la casa.
case 'd':
  Servo_entrada.write(90);
  Serial.println("La puerta principal ha sido abierta.");  
  lcd.setCursor(0,0);
  lcd.print("Puerta principal");
  lcd.setCursor(0,3);
  lcd.print("ha sido abierta");
break;
//Si el dato entrante via bluetooth, es e, el servomotor hara un giro de 0°, cerrando la puerta de la entrada de la casa.
case 'e':
  Servo_entrada.write(0);
  Serial.println("La puerta principal ha sido cerrada.");  
  lcd.setCursor(0,0);
  lcd.print("Puerta principal");
  lcd.setCursor(0,3);
  lcd.print("ha sido cerrada");  
break;
//Si el dato entrante via bluetooth, es f, el servomotor hara giros con una secuencia ascende de 45°, abriendo la compuerta del garage.
case 'f':
  abrirPuerta;
  lcd.setCursor(2,0);
  lcd.print("El Garaje a");
  lcd.setCursor(2,3);
  lcd.print("Sido abierto");
break;

//Si el dato entrante via bluetooth, es g, el servomotor hara giros con una secuencia descendente de 45°, cerrando la compuerta del garage.
case 'g':
  cerrarPuerta;
  lcd.setCursor(2,0);
  lcd.print("El Garaje a");
  lcd.setCursor(2,3);
  lcd.print("Sido cerrado");
break;
//Si el dato entrante via bluetooth, es h, el servomotor hara un giro de 90°, abriendo la puerta del sanitario.
case 'h':
  Servo_sanitario.write(90);
  lcd.setCursor(1,0);
  lcd.print("El Sanitario a");
  lcd.setCursor(2,3);
  lcd.print("Sido abierto");
break;
//Si el dato entrante via bluetooth, es i, el servomotor hara un giro de 0°, cerrando la puerta del sanitario.
case 'i':
  Servo_sanitario.write(0);
  lcd.setCursor(1,0);
  lcd.print("El Sanitario a");
  lcd.setCursor(2,3);
  lcd.print("Sido cerrado");
break;
}


}
//En caso de que el usuario sea 0, es decir que la contraseña sea incorrecta, el sistema de seguridad se habilitara, junto  con el buzzer.
if(usuario==0)
{
//Variables que leen los pines de los radares RCWL-0516
int valuer_habitacion=digitalRead(Radarpin_habitacion);
int valuer_entrada=digitalRead(Radarpin_entrada);
int valuer_x=digitalRead(Radarpin_x);
int valuer_y=digitalRead(Radarpin_y);
//En caso de que cualquier sensor se active, se emitira una alarma por medio del buzzer.
if((((valuer_habitacion==HIGH)||(valuer_entrada==HIGH))||(valuer_x==HIGH))||(valuer_y==HIGH))
{
Serial.println("Detecte algo");
lcd.setCursor(3,0);
lcd.print("PRECENCIA");
lcd.setCursor(3,3);
lcd.print("DETECTADA");
tone(buzzer_pin, si_septima, 300);
delay(400);
tone(buzzer_pin, do_septima, 300);
delay(400);

//En caso de que ningun sensor se active, el buzzer se desactivara.
}
else{
Serial.println("No detecte nada");
lcd.setCursor(1,0);
lcd.print("nada detectado");
lcd.setCursor(3,1);
lcd.print("todo bien");
noTone(buzzer_pin);

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

void cerrarPuerta(){
  int angulo=0;
  do{
    angulo=angulo+1;
    Servo_garage.write(angulo);
    delay(50);
    }while(angulo<90);
}

void abrirPuerta(){
  int angulo =90;
  do{
    angulo=angulo-1;
    Servo_garage.write(angulo);
    delay(50);
    }while(angulo>0);  
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
