#define IN3 22 //Declara el giro del motor a la izquierda
#define IN4 23 //Declara el giro del motor a la derecha
#define ENA 26 //Permite la activación de un motor en el puente H
#define EncA 19 //Manda pulsos al encoder
#define EncB 18 //Lee los pulsos del encoder

volatile long pulses = 0; //Ponemos los pulsos en cero

void IRAM_ATTR PulsesCounter(){
  if (digitalRead(EncB) == HIGH){     // si B es HIGH, sentido horario
    pulses++ ;        // incrementa PULSES en 1
  }
  else {          // si B es LOW, sentido anti horario
    pulses-- ;        // decrementa el PULSES en 1
  }
}

void setup() { //Declara las variables del puente H como outputs y las del encoder como inputs
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(EncA,INPUT);
  pinMode(EncB,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING); //Cada vez que hacemos una interrupción llamamos al PulseCounter
  Serial.begin(115200); //Inicializamos el serial en 115200 baudios
}

void loop() {
  int anterior, posterior; //declaramos las variables anterior y posterior
  digitalWrite(IN3,LOW); //apagamos giro a la izquierda
  digitalWrite(IN4,HIGH); //encendemos giro a la derecha
  digitalWrite(ENA,HIGH); //habilitamos el motor a través del puente H
  Serial.println("Dextrógiro"); //Imprimimos "Dextrógiro"
  anterior = pulses; //Definimos "anterior" como la cantidad de pulsos

  delay(3000); //Esperamos 3 segundos
  
  posterior = pulses; //Definimos "posterior" como la cantidad de pulsos actual
  Serial.print("Número de vuletas: "); //Imprimimos el cartel del número de vueltas
  Serial.println((anterior-posterior)/373); //Definimos la resta entre los pulsos anteriores y los actuales, 
  //como los pulsos que realmente dio, los convertimos a vueltas dividiendo entre 373 (cantidad de pulsos en una vuelta a la derecha)

  digitalWrite(IN3,LOW); //apagamos giro a la izquierda
  digitalWrite(IN4,LOW); //apagamos giro a la derecha
  digitalWrite(ENA,HIGH); //habilitamos el motor a través del puente H

  delay(2000); //Esperamos 2 segundos

  digitalWrite(IN3,HIGH); //encendemos giro a la izquierda
  digitalWrite(IN4,LOW); //apagamos giro a la derecha
  digitalWrite(ENA,HIGH); //habilitamos el motor a través del puente H
  Serial.println("Levógiro"); //Imprimimos "Levógiro"
  anterior = pulses; //Definimos "anterior" como la cantidad de pulsos

  delay(3000); //Esperamos 3 segundos

  digitalWrite(IN3,LOW); //apagamos giro a la izquierda
  digitalWrite(IN4,LOW); //apagamos giro a la derecha
  digitalWrite(ENA,HIGH); //habilitamos el motor a través del puente H
  Serial.print("Número de vueltas: "); //Imprimimos el cartel del número de vueltas
  posterior = pulses; //Definimos "posterior" como la cantidad de pulsos actual
  Serial.println((anterior - posterior)/450); //Definimos la resta entre los pulsos anteriores y los actuales,
  //como los pulsos que realmente dio, los convertimos a vueltas dividiendo entre 450(cantidad de pulsos en una vuelta a la izquierda)

  delay(2000); //Esperamos 2 segundos

}
