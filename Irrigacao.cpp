#include "Irrigacao.h"
#include "Evento.h"
Irrigacao::Irrigacao(){
  
}

void Irrigacao::config(){
  pinMode(SOLENOIDE1, OUTPUT);
  pinMode(SOLENOIDE2, OUTPUT);
  pinMode(SOLENOIDE3, OUTPUT);
  pinMode(MOTOR, OUTPUT);
}

void Irrigacao::iniciarTudo(){
  abrirValvulas();
  Alarm.delay(10000);
  acionarBomba();
}

void Irrigacao::pararTudo(){
  desligarBomba();
  Alarm.delay(10000);
  fecharValvulas();
}

void Irrigacao::acionarBomba(){
  digitalWrite(MOTOR, HIGH);
}

void Irrigacao::desligarBomba(){
  digitalWrite(MOTOR, LOW);
}

void Irrigacao::abrirValvulas(){
  digitalWrite(SOLENOIDE1, HIGH);  
  Alarm.delay(100);
  digitalWrite(SOLENOIDE2, HIGH);
  Alarm.delay(100);
  digitalWrite(SOLENOIDE3, HIGH);
}

void Irrigacao::fecharValvulas(){
  digitalWrite(SOLENOIDE1, LOW);
  Alarm.delay(100);
  digitalWrite(SOLENOIDE2, LOW);
  Alarm.delay(100);
  digitalWrite(SOLENOIDE3, LOW);
}
