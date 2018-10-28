#include "Irrigacao.h"
#include "Evento.h"
#include "EEPROM.h"
#include <Wire.h>
#include "DS3231.h"
#include "Print.h"

#define ENDERECO_EEPROM 0

struct DadosEventos{
  DadoEvento evento1;
  DadoEvento evento2; 
  DadoEvento evento3;
};

Irrigacao irrigacao;
Evento event1, event2, event3;
RTClib RTC;
Exibir p;

void setup() {
  p.config();

  DadosEventos dadosEventos;
  DateTime now = RTC.now();

  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); // set time to Saturday 8:29:00am Jan 1 2011

  EEPROM.get(ENDERECO_EEPROM, dadosEventos);

  event1.criarEvento(dadosEventos.evento1, evento1);
  event2.criarEvento(dadosEventos.evento2, evento2);
  event3.criarEvento(dadosEventos.evento3, evento3);  

}

void loop() {
  p.digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

void evento1() {
  Serial.println("Ligar bomba manhã");
  //Timer que determinará quanto tempo ficará ligada a água
  event1.iniciar(desligar);
  irrigacao.iniciarTudo();
}

void evento2() {
  Serial.println("Ligar bomba noite");
  //Timer que determinará quanto tempo ficará ligada a água
  event2.iniciar(desligar); 
  irrigacao.iniciarTudo();
}

void evento3() {
  Serial.println("Ligar bomba noite");
  //Timer que determinará quanto tempo ficará ligada a água
  event3.iniciar(desligar);
  irrigacao.iniciarTudo();
}

void desligar() {
  Serial.println("This timer only triggers once, stop the 2 second timer");

  event1.finalizar();
  event2.finalizar();
  event3.finalizar();

  irrigacao.pararTudo();
}
