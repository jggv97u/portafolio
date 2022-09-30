// Libreria Keypad: es un controlador que necesita el sketch para poder leer lo
tecleado en la membrana matriz.
#include <Keypad.h>
// Libreria Bounce2: ayuda para manejar la lectura digital de los botones y tener
un major control de ellos dentro del programa
#include <Bounce2.h>
// Libreria Servo: la libreria contiene funciones y métodos preescritos para lograr
hacer funcionar el servomotor con mayor facilidad
#include <Servo.h>

//=================== Declaracion de pines
// Instancia a la libreria servo
Servo servo;
// Declaracion de los pines para el sketch de la secuencia de botones.
const byte boton1 = 10;
const byte boton2 = 11;
const byte boton3 = 12;
const byte boton4 = 13;
// Declaracion del pin que leera el valor de la foto resistencia
const byte pinFotoRes = 3;
// Declaracion para los leds para el sketch de la secuencia de botones
const byte led1 = 45;
const byte led2 = 46;
const byte led3 = 47;
const byte led4 = 48;
// Delcaracion para los pines del display de 7 segmetos 4 dígitos
const int A = 38;
const int B = 39;
const int C = 40;
const int D = 41;
const int E = 42;
const int F = 43;
const int G = 44;

const int N = 7;
// Declaracion para los pines del display de 7 segmentos
const int a = 25;
const int b = 27;
const int c = 24;
const int d = 31;
const int e = 30;
const int f = 23;
const int g = 26;
// Declaracion de los pines para los switches
const int int1 = 34;
const int int2 = 35;
const int int3 = 36;
const int int4 = 37;
// Declaracion de los pines para los led del sketch del potenciometro
const int ledE1 = 0;
const int ledE2 = 1;
const int ledE3 = 2;
// Declaracion de los pines para los potenciometros
const int pinLed1 = 49;
const int pinLed2 = 50;
const int pinLed3 = 51;
// Declaracion de los pines para filas y columnas de la membrana matriz
const byte pinesFilas [ FILAS ] = { 9, 8, 7, 6 };
const byte pinesColumnas [ COLUMNAS ] = { 5, 4, 3, 2 };
// Declaracion de valores constante utilizados durante el programa
const char DIGITOS [ 14 ] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
'A', 'B', 'C', 'D' };
const byte FILAS = 4;
const byte COLUMNAS = 4;
const int objetivo = 128;
const int tolerancia = 5;
const int SEGMENTOS[ N ] = { A, B, C, D, E, F, G };
const char keys [ FILAS ] [ COLUMNAS ] = {
{ '1', '2', '3', 'A' },

{ '4', '5', '6', 'B' },
{ '7', '8', '9', 'C' },
{ '*', '0', '#', 'D' }
};
const int NUMEROS[ 14 ][ 7 ] = {
/*0*/ { 1, 1, 1, 1, 1, 1, 0 },
/*1*/ { 0, 1, 1, 0, 0, 0, 0 },
/*2*/ { 1, 1, 0, 1, 1, 0, 1 },
/*3*/ { 1, 1, 1, 1, 0, 0, 1 },
/*4*/ { 0, 1, 1, 0, 0, 1, 1 },
/*5*/ { 1, 0, 1, 1, 0, 1, 1 },
/*6*/ { 1, 0, 1, 1, 1, 1, 1 },
/*7*/ { 1, 1, 1, 0, 0, 0, 0 },
/*8*/ { 1, 1, 1, 1, 1, 1, 1 },
/*9*/ { 1, 1, 1, 1, 0, 1, 1 },
/*A*/ { 1, 1, 1, 0, 1, 1, 1 },
/*B*/ { 0, 0, 1, 1, 1, 1, 1 },
/*C*/ { 1, 0, 0, 1, 1, 1, 0 },
/*D*/ { 0, 1, 1, 1, 1, 0, 1 }
};
const int OFF = LOW;
// Declaracion de variables utilizadas durante el programa
// Objeto teclado el cual se utilizara para el funcionamiento de la membrana matriz
Keypad teclado = Keypad( makeKeymap( keys ), pinesFilas, pinesColumnas,
FILAS,COLUMNAS );
// Objetos buttonBounce para intanciar a la libreria bounce
Bounce buttonBounce1 = Bounce();
Bounce buttonBounce2 = Bounce();
Bounce buttonBounce3 = Bounce();
Bounce buttonBounce4 = Bounce();
char datos;
char TECLA;
char CLAVE[ 5 ];
int NUM [ 4 ] = { 1, 2, 3, 4 };
char CLAVE_MAESTRA[ 5 ];

byte INDICE = 0;
int luz = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int cve [ 5 ] = { 3, 1, 4, 2 };
int leds = 0;
int valor1 = 0;
int valor2 = 0;
int valor3 = 0;
int numRandom = 0;
int nivel = 1;
int i1 = 0;
int i2 = 0;
int i3 = 0;
int i4 = 0;
bool btn1 = false;
bool btn2 = false;
bool btn3 = false;
bool btn4 = false;
bool juegoGanado = false;

void setup() {
// Iniciamos el puerto Serie a 9600
Serial.begin( 9600 );
// Iniciamos el servo indicando el puerto
servo.attach( 53 );
// Declaraciones de puertos de entrada( Lectura )
pinMode( 34, INPUT );
pinMode( pinFotoRes, INPUT );
pinMode( ledE1, INPUT );
pinMode( ledE2, INPUT );
pinMode( ledE3, INPUT );
pinMode( 22, INPUT );

// Declaracion de puertos de salida( Escritura )
pinMode( pinLed1, OUTPUT );
pinMode( pinLed2, OUTPUT );
pinMode( pinLed3, OUTPUT );
pinMode( 33, OUTPUT );
pinMode( 32, OUTPUT );
pinMode( 31, OUTPUT );
pinMode( 30, OUTPUT );
pinMode( 29, OUTPUT );
pinMode( 28, OUTPUT );
pinMode( 27, OUTPUT );
pinMode( 26, OUTPUT );
pinMode( 25, OUTPUT );
pinMode( 24, OUTPUT );
pinMode( 23, OUTPUT );
pinMode( led1, OUTPUT );
pinMode( led2, OUTPUT );
pinMode( led3, OUTPUT );
pinMode( led4, OUTPUT );
pinMode( 52, OUTPUT );
// Declaracion de puerto de entrada para botones pull-up
pinMode( boton1, INPUT_PULLUP );
pinMode( boton2, INPUT_PULLUP );
pinMode( boton3, INPUT_PULLUP );
pinMode( boton4, INPUT_PULLUP );
// Otorgamos la lectura de los botones a la libreria bounce, para su manejo
buttonBounce1.attach( boton1 );
buttonBounce2.attach( boton2 );
buttonBounce3.attach( boton3 );
buttonBounce4.attach( boton4 );
// Ejecutamos funciones de inicio
limpiar();
generarClave();
// Declaracion de puertos de salida para los pines del display 7 segmentos 4
digitos

for ( int i = 0; i < N; i++ ) {
pinMode( SEGMENTOS[ i ], OUTPUT );
digitalWrite( SEGMENTOS[ i ], OFF );//apagar
}
// Cerrar la caja
int a = 511;
int angulo = map( a, 0, 1023, 0, 180 );
servo.write( angulo );
}

void loop() {
// Sentencia switch que llevará el control del juego mediante la variable nivel
switch ( nivel ) {
case 1:
// Ejecucion del primer nivel en la funcion Switch Sketch
switchSketch();
break;
case 2:
// Ejecucion del segundo nivel en la funcion botones
botones();
break;
case 3:
// Ejecucion del tercer nivel en la funcion potenciometro
potenciometro();
break;
case 4:
// Ejecucion del cuarto nivel en la funcion fotoresistencia
fotoresistencia();
break;
case 5:
// Ejecucion para que el jugador, pueda ingresar el código y abrir la caja
code();
break;
case 6:

// Ejecucion de la funcion servomoton
servomotor();
// Envio de señal al ESP32
digitalWrite( 52, HIGH );
break;
default:
// Sentencia por default para cuando el juego termine
Serial.println( "Juego terminado: felicidades, ganaste" );
break;
}
}

// La funcion servomotor se encarga que al ejecutar el código, se mueva de tal
manera que deje libre la cerradura de la caja y pueda abrir
void servomotor () {
int a = 1023;
int angulo = map( a, 0, 1023, 0, 180 );
servo.write( angulo );
Serial.println( angulo );
nivel++;
}

// La funcion fotoresistencia mide la intencidad la luz que emitirá un led al
terminar uno de los niveles, condicionado a que si recibe la luz suficiente, muestre
un digito de la clabe y cambie de nivel
void fotoresistencia () {
luz = analogRead( pinFotoRes );
luz = map( luz, 0, 974, 0, 10 );
luz = constrain( luz, 0, 10 );
Serial.println( luz );
if ( luz > 5 ) {
imprimeDigito( CLAVE_MAESTRA[ ( nivel - 1) ] );
nivel++;
}
}

// La función potenciometro se encarga de dar lectura a los potenciometros y variar
valores que con un calculo y con un nivel de tolerancia, cuando enciendan los tres,
genere otro numero de la clave y cambie de nivel
void potenciometro () {
// read the input on analog pin 0:
sensorValue1 = analogRead( ledE1 );
sensorValue2 = analogRead( ledE2 );
sensorValue3 = analogRead( ledE3 );
// print out the value you read:
valor1 = max( sensorValue1, sensorValue2 );
valor2 = abs( sensorValue2 - sensorValue3 );
valor3 = ( sensorValue3 + sensorValue2 ) / 2;
valor1 = map( valor1, 0, 1010, 0, 255 );
valor1 = constrain( valor1, 0, 255 );
valor2 = map( valor2, 0, 1010, 0, 255 );
valor2 = constrain( valor2, 0, 255 );
valor3 = map( valor3, 0, 1010, 0, 255 );
valor3 = constrain( valor3, 0, 255 );
bool a1 = false;
bool a2 = false;
bool a3 = false;
if ( abs( valor1 - objetivo ) > tolerancia ) {
a1 = false;
digitalWrite( pinLed1, LOW );
} else {
a1 = true;
digitalWrite( pinLed1, HIGH );
}
if ( abs( valor2 - objetivo ) > tolerancia ) {
a2 = false;
digitalWrite( pinLed2, LOW );
} else {
a2 = true;
digitalWrite( pinLed2, HIGH );

}
if ( abs( valor3 - objetivo ) > tolerancia ) {
a3 = false;
digitalWrite( pinLed3, LOW );
} else {
a3 = true;
digitalWrite( pinLed3, HIGH );
}
if ( a1 && a2 && a3 ){
imprimeDigito( CLAVE_MAESTRA[ ( nivel - 1) ] );
nivel++;
apagarLeds();
}
}

// La funcion imprimir, recibe como parámetro el numero que tendra que aparecer en
display de 7 segmentos y 4 digitos
void imprimir( int num ){
for ( int i = 0; i < N; i++ ){ // Recorre los segmentos mientras i sea menor que
N
digitalWrite( SEGMENTOS[ i ], NUMEROS[ num ][ i ] ); // Enciende los segmentos
necesarios, según sea el número seleccionado
}
}

// La funcion generar clave
void generarClave() {
for ( int i = 0; i < 4; i++ ) { // Recorre mientras i sea menor que 4
int num = numRand( 1 ); // Generamos un numero aleatorio que almacenamos en una
variable entera
CLAVE_MAESTRA [ i ] = DIGITOS [ num ]; // Con ayuda del arreglo constante
DIGITOS en la posicion del numero aleatorio asignamos al indice del arreglo
CLAVE_MAESTRA e
}
}

// La funcion numRand recibe una variable entera como parámetro

int numRand( int a ) {
if ( a == 1 )
return rand()%13; // Si el valor recibido es igual a 1 generamos un numero
aleatorio del 1 al 13
else
return ( rand()%4 + 1 ); // Sino el valor generado será del 1 al 4
}

// Funcion para apagar display
void apagarDisplay () {
digitalWrite( a, LOW );
digitalWrite( b, LOW );
digitalWrite( c, LOW );
digitalWrite( d, LOW );
digitalWrite( e, LOW );
digitalWrite( f, LOW );
digitalWrite( g, LOW );
}

// Funcion del primer nivel del juego
void switchSketch() {
if ( digitalRead( 34 ) == HIGH && digitalRead( 35 ) == LOW && digitalRead( 36 )
== HIGH && digitalRead( 37 ) == LOW ) { // Segun la posicion de cada switch se toma
lee cada switch, hasta llegar a la posicion correcta
imprimeDigito( CLAVE_MAESTRA[ ( nivel - 1) ] ); // Se imprime el primer dígito
de la clava
nivel++; // Se sube de nivel y termina éste sketch
}
}

// Sketch botones: segundo nivel del juego
void botones () {
secuenciaLed(); // Encendemos los leds
leds = 1;
// Actualizamos los bounce de cada botón
buttonBounce1.update();

buttonBounce2.update();
buttonBounce3.update();
buttonBounce4.update();
if ( buttonBounce3.fell() || btn3 ){ // La secuencia inicia con el botón 3
// Si se preciona el botón 3...
digitalWrite( led3, LOW ); // Apagamos el led 3
btn3 = true; // Cambiamos la variable como control de que botones ya hemos
presionado
if ( buttonBounce1.fell() || btn1 ) { // Checa si ya se ha presionado el botón
1
digitalWrite( led1, LOW ); // Apagamos el led 1
btn1 = true; // Cambiamos la variable como control de que botones ya hemos
presionado
if ( buttonBounce4.fell() || btn4 ) { // Checa si ya se ha presionado el
botón 4
digitalWrite( led4, LOW ); // Apagamos el led 4
btn4 = true; // Cambiamos la variable como control de que botones ya hemos
presionado
if ( buttonBounce2.fell() || btn2 ) { // Checa si ya se ha presionado el
botón 2
digitalWrite( led2, LOW ); // Apagamos el led 2
btn2 = true; // Cambiamos la variable como control de que botones ya
hemos presionado
imprimeDigito( CLAVE_MAESTRA[ ( nivel - 1) ] ); // Estando presionados
todos los botones en orden, imprime el segundo dígito de la clave
nivel++; // Cambia de nivel
} else if ( buttonBounce1.fell() || buttonBounce4.fell() ||
buttonBounce3.fell() ) {
leds = 0;
secuenciaLed();
leds = 1;
btn2 = false;
}
} else if ( buttonBounce1.fell() || buttonBounce2.fell() ||
buttonBounce3.fell() ) {
leds = 0;
secuenciaLed();
leds = 1;

btn4 = false;
}
} else if ( buttonBounce3.fell() || buttonBounce2.fell() ||
buttonBounce4.fell() ) {
leds = 0;
secuenciaLed();
leds = 1;
btn1 = false;
}
} else if ( buttonBounce1.fell() || buttonBounce2.fell() || buttonBounce4.fell()
) {
leds = 0;
secuenciaLed();
leds = 1;
btn3 = false;
}
}

// La funcion secuenciaLed, prende los leds para el sketch de secuencia de botones
void secuenciaLed () {
if ( leds == 0 ) {
digitalWrite( led3, HIGH );
digitalWrite( led1, HIGH );
digitalWrite( led4, HIGH );
digitalWrite( led2, HIGH );
}
}

// La funcion secuenciaLed, apaga los leds para el sketch de secuencia de botones
void apagarLeds () {
digitalWrite( led1, LOW );
digitalWrite( led2, LOW );
digitalWrite( led3, LOW );
digitalWrite( led4, LOW );
digitalWrite( pinLed1, LOW );

digitalWrite( pinLed2, LOW );
digitalWrite( pinLed3, LOW );
}

// impirmeDigito recibe como paramtro un caracter obtenido del arreglo constante
DIGITO
void imprimeDigito( char dig ) {
// El switch evalua el valor de la variable reciida en el parámetro y segun sea
el caso, envia un valor entero a la funcion imprimir para que imprima el dígito en
el display
switch ( dig ) {
case '0':
imprimir( 0 );
break;
case '1':
imprimir( 1 );
break;
case '2':
imprimir( 2 );
break;
case '3':
imprimir( 3 );
break;
case '4':
imprimir( 4 );
break;
case '5':
imprimir( 5 );
break;
case '6':
imprimir( 6 );
break;
case '7':
imprimir( 7 );
break;

case '8':
imprimir( 8 );
break;
case '9':
imprimir( 9 );
break;
case 'A':
imprimir( 10 );
break;
case 'B':
imprimir( 11 );
break;
case 'C':
imprimir( 12 );
break;
case 'D':
imprimir( 13 );
break;
}
}

// code no es un nivel como tal pero es un escalon para superar el juego, aquí se
lee el dígito tecleado en la membrana matriz para ir guardando en un arreglo y a
su vez ir mostrando en el display de 4 dígitos, los dígitos tecleados, una vez
tecleados 4 dígitos éstos se comparan con la clave maestra y de ser iguales, abre
la caja
void code() {
TECLA = teclado.getKey();
if ( TECLA && INDICE < 4 ) {
CLAVE[ INDICE ] = TECLA;
INDICE++;
} else {
limpiar();
digito ( 1 );
numero ( CLAVE[ 0 ] );
limpiar();

digito ( 2 );
numero ( CLAVE[ 1 ] );
limpiar();
digito ( 3 );
numero ( CLAVE[ 2 ] );
limpiar();
digito ( 4 );
numero ( CLAVE[ 3 ] );
}
juegoGanado = !strcmp( CLAVE_MAESTRA, CLAVE ) ? true : false ;
if ( juegoGanado ) {
nivel++;
}
}

// digito recibe un parametro entero, el cual, su valor se evalua en un switch y
enciendo dígito correspondiente del display de 4 dígitos
void digito ( int x ) {
digitalWrite( 33, HIGH );
digitalWrite( 32, HIGH );
digitalWrite( 29, HIGH );
digitalWrite( 28, HIGH );
switch( x ) {
case 1: digitalWrite( 33, LOW ); break;
case 2: digitalWrite( 32, LOW ); digitalWrite( 33, LOW ); break;
case 3: digitalWrite( 29, LOW ); break;
case 4: digitalWrite( 28, LOW ); break;
}
}

// numero recibe una variable entrea que se evalua en un switch y según el caso,
manda llamar a la funcion correspondiente, para encender los segmentos según el
número recibido
void numero ( int x ) {
switch ( x ) {

case '0': cero(); break;
case '1': uno(); break;
case '2': dos(); break;
case '3': tres(); break;
case '4': cuatro(); break;
case '5': cinco(); break;
case '6': seis(); break;
case '7': siete(); break;
case '8': ocho(); break;
case '9': nueve(); break;
case 'A': letraA(); break;
case 'B': letraB(); break;
case 'C': letraC(); break;
case 'D': letraD(); break;
//case '*': ast(); break;
//case '#': gat(); break;
}
}

// La funcion limpiar, apaga todos los segmentos del display en el dígito
seleccionado
void limpiar() {
digitalWrite( 25, LOW );
digitalWrite( 27, LOW );
digitalWrite( 24, LOW );
digitalWrite( 31, LOW );
digitalWrite( 30, LOW );
digitalWrite( 23, LOW );
digitalWrite( 26, LOW );
}

// Funciones que encienden/apagan los segmentos según el numero descrito en su
cabecera
void cero() {
digitalWrite( a, HIGH );

digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, LOW );
}

void uno() {
digitalWrite( a, LOW );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, LOW );
digitalWrite( e, LOW );
digitalWrite( f, LOW );
digitalWrite( g, LOW );
}

void dos() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, LOW );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, LOW );
digitalWrite( g, HIGH );
}

void tres() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, LOW );

digitalWrite( f, LOW );
digitalWrite( g, HIGH );
}
void cuatro() {
digitalWrite( a, LOW );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, LOW );
digitalWrite( e, LOW );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void cinco() {
digitalWrite( a, HIGH );
digitalWrite( b, LOW );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, LOW );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void seis() {
digitalWrite( a, HIGH );
digitalWrite( b, LOW );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void siete() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );

digitalWrite( d, LOW );
digitalWrite( e, LOW );
digitalWrite( f, LOW );
digitalWrite( g, LOW );
}
void ocho() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void nueve() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, LOW );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void letraA() {
digitalWrite( a, HIGH );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, LOW );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void letraB() {
digitalWrite( a, LOW );

digitalWrite( b, LOW );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, HIGH );
}
void letraC() {
digitalWrite( a, HIGH );
digitalWrite( b, LOW );
digitalWrite( c, LOW );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, HIGH );
digitalWrite( g, LOW );
}
void letraD() {
digitalWrite( a, LOW );
digitalWrite( b, HIGH );
digitalWrite( c, HIGH );
digitalWrite( d, HIGH );
digitalWrite( e, HIGH );
digitalWrite( f, LOW );
digitalWrite( g, HIGH );
}
