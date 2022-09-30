// Incluimos librería fauxmoESP para poder usar el servido de alexa en el programa
#include <fauxmoESP.h>
// La libreia WiFi, nos ayuda a conectar nuestro modulo a internet
#ifdef ESP32
#include <WiFi.h>
#endif
// Libreria para el manejo de lcd con I2C
#include "LiquidCrystal_I2C.h"

// Bounce es una libreria que nos ayuda a manejar botones
#include "Bounce2.h"
// Definimos el pin para el led
#define LED_1 5
// Definimos el id que le daremos al led en el servidor de alexa
#define ID_1 "Led 1"
// Definimos SSID y Password de la red a la que conectaremos nuestro módulo
#define WIFI_SSID "NOVA3"
#define WIFI_PASS "12345678"

// INICIA DECLARACION DE VARIABLES Y CONSTANTES
fauxmoESP fauxmo; // Objeto para el manejo del servidor de alexa con el programa
int i = 0;
LiquidCrystal_I2C lcd( 0x27, 16, 2 ); // Objeto para el manejo del lcd
const byte buttonPin = 15; // Definimos el pin del boton de inicio
bool juego = true;
unsigned long tiempoInicio;
unsigned long duracion = 5 * 60000;
unsigned long pausa;
enum EstadoJuego { ACTIVO, INACTIVO };
EstadoJuego estadoJuego = EstadoJuego :: INACTIVO;
Bounce buttonBounce = Bounce();

void wifiSetup() {
  WiFi.mode( WIFI_STA ); // Definimos el wifi como modo de estación
  Serial.printf( "( WIFI ) Conectando a: %s", WIFI_SSID );
  WiFi.begin( WIFI_SSID, WIFI_PASS ); // Iniciamos la conección del módulo a internet
  while ( WiFi.status() != WL_CONNECTED ) {
    Serial.print( "." );
    delay( 100 );
  }
  Serial.println();
  Serial.printf( "( WIFI ) STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID(),
  WiFi.localIP().toString().c_str() );
}

void setup() {
  Serial.begin( 9600 ); // Iniciamos el puerto serie del modulo
  pinMode( 2, OUTPUT );
  pinMode( buttonPin, INPUT_PULLUP ); // Hacemos que el pin del boton de inicio sea entrada pullup
  pinMode( 18, INPUT ); // El pin 18 será la comunicacion entre el MEGA y el módulo
  buttonBounce.attach( buttonPin ); // Otorgamos el valor del boton de inicio a la libreria bounce
  lcd.init(); // Iniciamos lcd
  lcd.backlight(); // Prendemos la luz del lcd
  lcd.setCursor( 0, 0 ); // Posicionamos el cursor
  lcd.print( "Escape room" ); // Imprimimos en el lcd
  pinMode( LED_1, OUTPUT ); // Ponemos como salida en pin del led
  digitalWrite( LED_1, LOW ); // Apagamos el led
  wifiSetup(); // Ejecutamos el setup del WiFi
  fauxmo.createServer( true ); // Creamos el servidor de alexa
  fauxmo.setPort( 80 ); // Seteamos el puerto 80 como comunicacion del servidor y el módulo
  fauxmo.enable( true ); // Habilitamos el puerto
  fauxmo.addDevice( ID_1 ); // Agregamos el dispositivo con el id que le dimos al inicio
  fauxmo.onSetState( [] ( unsigned char device_id, const char * device_name, bool
                          state, unsigned char valor ) {
                            Serial.printf( "[MAIN] Device #%d (%s) state: %s value: %d\n", device_id,
                            device_name, state ? "ON" : "OFF", valor );
                            if ( strcmp ( device_name, ID_1 ) == 0 ) {
                              digitalWrite( LED_1, state ? HIGH : LOW );
                            }
                          }); // Lectura de los dispositivos que se han agregado en el servidor
}

void loop() {
  int serial = digitalRead( 18 ); // Leemos si se recibe alguna señal de la placa MEGA
  if ( serial == 1 ) {
    estadoJuego = EstadoJuego :: INACTIVO; // De recibir la señal de la placa MEGA, el estado de juego pasará a inactivo, parando el reloj y dar por terminado el juego
  }
  buttonBounce.update(); // Actualiza el estado del botón de inicio
  unsigned long tiempo = millis();
  switch ( estadoJuego ) { // Evalua el estado de juego
    case EstadoJuego :: INACTIVO: // Si esta inactivo...
      if ( buttonBounce.fell() ) { // Condiciona si se preciona el botón
        estadoJuego = EstadoJuego :: ACTIVO; // De ser así pasa el estadoJuego como activo
        tiempoInicio = tiempo;
      }
    break;
    case EstadoJuego :: ACTIVO: // Si esta activo...
      if ( buttonBounce.fell() ) { // Condiciona si se preciona el botón
        estadoJuego = EstadoJuego :: INACTIVO; // De ser así pasa el estadoJuego como activo
        pausa = ( tiempo - tiempoInicio ) + pausa;
      }
      unsigned long tiempoRestante = duracion - ( tiempo - tiempoInicio ) - pausa;
      // Valor para llevar el conteo regresivo de tiempo
      int minutos = tiempoRestante / 60000; // Calcula los minutos restantes
      int segundos = ( tiempoRestante / 1000 ) % 60; // Calcula los segundos restantes
      char formatoTiempo[ 6 ]; // Arreglo de caracteres que almacenará el tiempo en formato
      sprintf( formatoTiempo, "%02d:%02d", minutos, segundos ); // Damos formato tipo MM:SS con las variables de minutos y segundos
      Serial.println( formatoTiempo );
      lcd.setCursor( 0, 1 ); // Seteamos el cursor del lcd
      lcd.print( formatoTiempo ); // Imprimimos en formatoTiempo en lcd
    break;
  }
  fauxmo.handle(); // manejamos el objeto fauxmo para posibles operaciones o
  funciones que quiera ejecutar el servidor de alexa
}
