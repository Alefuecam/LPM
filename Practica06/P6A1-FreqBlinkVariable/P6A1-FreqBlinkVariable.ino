#define Rojo 17        // Asigna el PIN 17 el LED rojo
#define Amarillo 16    // Asigna el PIN 16 LED amarillo
#define Verde 4        // Asigna el PIN 4 para el LED verde
#define ButLed 2       // Asigna el PIN 2 para el LED controlado por botón
#define ButtonA 23     // Asigna el PIN 23 para el botón A
#define ButtonB 22     // Asigna el PIN 22 para el botón B

int factor = 1;          // Factor que se usa para multiplicar el tiempo de retardo
int tiempo = 20;         // Tiempo base de retardo en milisegundos
int buttonStateA;        // Variable para el botón A
int buttonStateB;        // Variable para el botón B

void setup() {
  // Configura los pines de los LEDs como salidas
  pinMode(Rojo, OUTPUT);
  pinMode(Amarillo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(ButLed, OUTPUT);

  // Configura los pines de los botones como entradas
  pinMode(ButtonA, INPUT);
  pinMode(ButtonB, INPUT);

  // Inicia la comunicación serial en 115200 baudios
  Serial.begin(115200);
}

void loop() {
  // Ciclo de semáforo
  digitalWrite(Rojo, LOW);        // Apaga el LED rojo
  digitalWrite(Verde, HIGH);      // Enciende el LED verde
  delay(factor*tiempo);           // Espera por un periodo de tiempo
  digitalWrite(Verde, LOW);       // Apaga el LED verde
  digitalWrite(Amarillo, HIGH);   // Enciende el LED amarillo
  delay(factor*tiempo);           // Espera por un periodo de tiempo
  digitalWrite(Amarillo, LOW);    // Apaga el LED amarillo
  digitalWrite(Rojo, HIGH);       // Enciende el LED rojo
  delay(factor*tiempo);           // Espera por un periodo de tiempo

  buttonStateA = digitalRead(ButtonA);   // Lee el estado actual del botón A
  buttonStateB = digitalRead(ButtonB);   // Lee el estado actual del botón B

  // Comprueba si el botón A fue presionado
  if (buttonStateA){
    Serial.println("Botón A presionado");  // Imprime que el botón A está presionado
    factor++;                             // Incrementa el factor por 1
    digitalWrite(ButLed,HIGH);           // Enciende el LED controlado por botón
    delay(tiempo);                       // Espera por un periodo de tiempo
    digitalWrite(ButLed,LOW);            // Apaga el LED controlado por botón
    delay(tiempo);                       // Espera por un periodo de tiempo
  }

  // Comprueba si el botón B fue presionado
  if (buttonStateB){
    Serial.println("Botón B presionado");  // Imprime que el botón B está presionado
    factor--;                             // Decrementa el factor por 1
    digitalWrite(ButLed,HIGH);           // Enciende el LED controlado por botón
    delay(tiempo);                       // Espera por un periodo de tiempo
    digitalWrite(ButLed,LOW);            // Apaga el LED controlado por botón
    delay(tiempo);                       // Espera por un periodo de tiempo
  }
  
  Serial.println(factor*tiempo); //Imrime el tiempo actual multiplicado por el factor a la consola serial
}
