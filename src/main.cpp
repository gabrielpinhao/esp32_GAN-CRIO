#include <Arduino.h> // Obrigatório no PlatformIO

#define LED 23

bool piscando = false;        // Guarda o estado atual (se deve piscar ou não)
bool estadoLed = LOW;         // Guarda se o LED está aceso ou apagado agora
unsigned long tempoAnterior = 0; // Guarda a última vez que o LED mudou
const long intervalo = 2000;  // Tempo de pisca-pisca (2 segundos)

void setup() {
  Serial.begin(115200);       // Inicia a comunicação com o computador
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);     // Começa com o LED apagado
}

void loop() {
  // 1. Verifica se chegou alguma mensagem do Python
  if (Serial.available() > 0) {
    char comando = Serial.read(); // Lê o que o Python enviou
    
    if (comando == '1') {
      piscando = true;            // O Python mandou ligar
    } 
    else if (comando == '0') {
      piscando = false;           // O Python mandou desligar
      digitalWrite(LED, LOW);     // Garante que o LED não fique travado aceso
    }
  }

  // 2. Faz o LED piscar apenas se a variável "piscando" for verdadeira
  if (piscando) {
    unsigned long tempoAtual = millis(); // Vê que horas são agora
    
    // Se já passou o tempo do intervalo (2 segundos)
    if (tempoAtual - tempoAnterior >= intervalo) {
      tempoAnterior = tempoAtual; // Salva a hora atual para a próxima vez
      
      // Inverte o estado do LED (se está LOW vira HIGH, e vice-versa)
      estadoLed = !estadoLed;
      digitalWrite(LED, estadoLed);
    }
  }
}