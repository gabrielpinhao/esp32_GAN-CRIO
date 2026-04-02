#include <Arduino.h>

#define PINO_PWM 23

// Configurações do PWM (API Clássica)
const int canalPWM = 0;       // O ESP32 possui 16 canais independentes (0 a 15)
const int frequencia = 50;    // Frequência de 50 Hz
const int resolucao = 16;     // Resolução de 16 bits (0 a 65535)
const int dutyCycle50 = 58982; // Valor para 50% de Duty Cycle

void setup() {
  Serial.begin(115200);       // Inicia a comunicação com o computador

  // 1. Configura as propriedades do canal PWM
  ledcSetup(canalPWM, frequencia, resolucao);

  // 2. Conecta o canal PWM ao pino físico
  ledcAttachPin(PINO_PWM, canalPWM);

  // 3. Garante que inicie com o PWM desligado (escrevendo no CANAL, e não no pino)
  ledcWrite(canalPWM, 0);     
}

void loop() {
  // Verifica se chegou alguma mensagem do Python
  if (Serial.available() > 0) {
    char comando = Serial.read(); // Lê o que o Python enviou
    
    if (comando == '1') {
      // O Python mandou ligar: Aciona a onda quadrada a 50% no canal
      ledcWrite(canalPWM, dutyCycle50); 
    } 
    else if (comando == '0') {
      // O Python mandou desligar: Zera o duty cycle do canal
      ledcWrite(canalPWM, 0); 
    }
  }
}