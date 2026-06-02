#include <Arduino.h>

#define PINO_SAIDA 23 

// Variável global que poderá ser alterada via Python
unsigned int tempoDelay = 80; 

void setup() {
  Serial.begin(115200);         
  pinMode(PINO_SAIDA, OUTPUT);  

  digitalWrite(PINO_SAIDA, HIGH); 
}

void loop() {
  // Verifica se chegou algo do notebook
  if (Serial.available() > 0) {
    // Lê a string inteira até encontrar a quebra de linha (\n)
    String comandoRecebido = Serial.readStringUntil('\n'); 
    
    // Remove espaços em branco ou caracteres de retorno de carro (\r) do fim da string
    comandoRecebido.trim(); 

    if (comandoRecebido.length() > 0) {
      char acao = comandoRecebido.charAt(0); // Pega a primeira letra/número

      // Comando '1': Executa o pulso usando a variável tempoDelay
      if (acao == '1') {
        digitalWrite(PINO_SAIDA, LOW);   
        delayMicroseconds(tempoDelay);   // Usa a variável em vez do número fixo
        digitalWrite(PINO_SAIDA, HIGH);  
      } 
      
      // Comando '0': Desliga a saída
      else if (acao == '0') {
        digitalWrite(PINO_SAIDA, LOW); 
      } 
      
      // Comando '2': Liga a saída
      else if (acao == '2') {
        digitalWrite(PINO_SAIDA, HIGH); 
      }
      
      // Comando 'T': Atualiza o tempo de delay (Ex: Python envia "T150")
      else if (acao == 'T') {
        // Pega a string do segundo caractere em diante (os números)
        String valorStr = comandoRecebido.substring(1); 
        
        // Converte a string numérica para inteiro e salva na variável
        tempoDelay = valorStr.toInt(); 
        
        // Opcional: envia de volta ao Python para confirmar
        Serial.print("Novo tempo de delay: ");
        Serial.println(tempoDelay);
      }
    }
  }
}