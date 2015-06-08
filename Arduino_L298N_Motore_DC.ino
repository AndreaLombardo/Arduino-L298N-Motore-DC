/*
 * L298N pilotare un motore DC con Arduino
 * Programmino per imparare il funzionamento del Modulo L298N e del suo utilizzo con Arduino
 *
 * Autore  : Andrea Lombardo
 * Web     : http://www.lombardoandrea.com
 * Post    : http://bit.ly/L298N-ARDUINO-MOTOREDC
 * Git     : https://github.com/AndreaLombardo/
 */ 

//definizione dei pin
static int pinAcceleratore = A0; //pin analogico deputato a leggere i valori del potenziometro
static int mA = 12; //pin digitale per determinare gli stati logici da inviare al modulo
static int mB = 13; //pin digitale per determinare gli stati logici da inviare al modulo
static int pinPotenza = 11; //pin digitale tramite il quale inviare un segnale di tipo PWM tramite la funzione analgWrite()

//variabili usate per gestire e mostrare i valori di operaizone
int accelerazione;  //valore letto dal pin A0
int potenza;  //valore in uscita dal pin 11

void setup() {
  //inizializzo la comunicazione seriale cosi da mostrare i valori nel Mointor Seriale
  Serial.begin(9600);

  //inizializzo variabili
  accelerazione = 0;
  potenza = 0;

  //definisco tipologia pin
  pinMode(pinAcceleratore, INPUT); //input in quanto legge il valore analogico del pin A0
  pinMode(mA, OUTPUT); //output perche' definisce lo stato logico del pin IN1 del modulo L298N
  pinMode(mB, OUTPUT); //output perche' definisce lo stato logico del pin IN2 del modulo L298N
  pinMode(pinPotenza, OUTPUT);  //output perche' definisce il valore PWM del pin EN1 del modulo L298N

  //pullDown sensore pinAcceleratore
  digitalWrite(pinAcceleratore, LOW);

  //Definisco il senso di marcia del motore
  /*
    mA |   mB  | Evento
  -----|-------|----------------------
  LOW  | LOW   | fermo
  LOW  | HIGH  | Movimento in un senso
  HIGH | LOW   | Movimento senso opposto
  HIGH | HIGH  | Fermo
  */
  
  digitalWrite(mA, LOW);
  digitalWrite(mB, HIGH);

}


void loop() {
  
  //leggo il valore analogico del potenziometro sul pin A0.
  accelerazione = analogRead(pinAcceleratore);
  
  /*
  Il range dei valori analogici e' da 0 a 1024 mentre il range dei valori PWM  e' da 0 a 255
  per mantenere questa proporzionalita' eseguo la mappatura dei valori
  */
  potenza = map(accelerazione, 0, 1024, 0, 255);

  //Invio i dati letti al Monitro seriale, cosi da poterli vedere a video
  Serial.print("Accelerazione = ");
  Serial.print(accelerazione);
  Serial.print(" - potenza = ");
  Serial.println(potenza);
  
  //invio costantemente il valore PWM della potenza in modo da far variare la velocita' del motore in base alla posizione del potenziometro
  analogWrite(pinPotenza, potenza);
}
