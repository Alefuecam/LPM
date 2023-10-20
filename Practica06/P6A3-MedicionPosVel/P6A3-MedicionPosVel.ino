#define IN3 23 //Declara el giro del motor a la izquierda
#define IN4 22 //Declara el giro del motor a la derecha
#define ENB 27 //Permite la activación de un motor en el puente H
#define EncA 19 //Manda pulsos al encoder
#define EncB 18 //Lee los pulsos del encoder

volatile long pulses = 0; //Hago que los pulsos inicien en cero
int velocidad = 25; //La velocidad inicia en 25 (10% de 255)
long tiempo =0; //El tiempo inicia en cero
long pulso_anterior = 0; //El pulso anterior inicia en cero
long actual = 0; //El pulso actual inicia en cero
long tiempo_anterior=0; //El tiempo anterior inicia en cero

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
  pinMode(ENB,OUTPUT);
  pinMode(EncA,INPUT);
  pinMode(EncB,INPUT);

  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING); //Cada vez que hacemos una interrupción llamamos al PulseCounter
  Serial.begin(115200); //Inicializamos el serial en 115200 baudios
}

void loop() {
  tiempo = micros()/1000; //Dividimos lo que nos da a función micros (tiempo en microsegundos desde que se inicia el programa) 
  //entre 1000 para tener el tiempo en milisegundos

  if (tiempo < 3000){ //Si el tiempo es menor a 3 segundos, la velocidad es 25 (10% de 255)
    velocidad = 25;
  }

  if (tiempo >= 3000 && tiempo < 6000){ //Si el tiempo es entre 3 y 6 segundos, la velocidad es 75 (30% de 255)
    velocidad = 75;
  }

  if (tiempo >= 6000 && tiempo <= 9000){ //Si el tiempo es entre 6 y 9 segundos, la velocidad es 127 (50% de 255)
    velocidad = 127;
  }

  if (tiempo > 9000 && tiempo <= 12000){ //Si el tiempo es entre 9 y 12 segundos, la velocidad es 255 (100%)
    velocidad = 255;
  }

  if (tiempo >12000 ){ //Si el tiempo es mayor a 12 segundos, la velocidad es 0
    velocidad = 0;
  }

  if (tiempo % 200 == 0){ //Cada vez que estemos en 2 milisegundos, imprimirá lo siguiente

    int diferencia_tiempo = tiempo - anterior; //Calcula la diferencia entre el tiempo anterior y el actual
    int diferencia_pulsos = puses - pulso_anterior; //Calcula la diferencia entre el pulso anterior y el actual
    int angulos = diferencia_pulsos/diferencia_tiempo*360; //Calcula el ángulo haciendo la división entre las dos diferencias

    Serial.print("Pulsos: "); //Imprime los pulsos
    Serial.print(pulses);
    Serial.print("  ---  ");
    Serial.print("Angulo: ");
    Serial.print(angulos); //Imprime el ángulo
    Serial.print(" -- ");
    Serial.print("W: ");
    Serial.print(float(revoluciones/60)); //Imprime las revoluciones por segundo (dividiendo las revoluciones por minuto entre 60 segundos)
    Serial.print(" [rps] -- ");
    Serial.print(revoluciones); //Imprime las revoluciones por minuto
    Serial.print("[rpm] -- ");
    Serial.print(2.0*3.1416*revoluciones/60.0); //Calcula los radianes por segundo y los imprime
    Serial.println(" [rad/s]");
  }

  digitalWrite(IN3,HIGH); //Enciende el motor hacia la izquierda
  digitalWrite(IN4,LOW); //Apaga el motor hacia la derecha
  analogWrite(ENA,velocidad); //Ajusta la velocidad del motor al parámetro "velocidad" señalado anteriormente
}
