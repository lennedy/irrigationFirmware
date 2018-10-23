#include "Irrigacao.h"
#include "Evento.h"
#include "EEPROM.h"
#include <Wire.h>
#include "DS3231.h"


#define ENDERECO_EEPROM 0

struct DadoEvento{
  time_t horario;
  time_t duracao;
  bool habilitado;
};

struct DadosEventos{
  DadoEvento evento1;
  DadoEvento evento2; 
  DadoEvento evento3;
};

Irrigacao irrigacao;
Evento event1, event2, event3;
RTClib RTC;

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  DadosEventos dadosEventos;
  DateTime now = RTC.now();


  setTime(now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); // set time to Saturday 8:29:00am Jan 1 2011

  EEPROM.get(ENDERECO_EEPROM, dadosEventos);

  event1.criarEvento(dadosEventos.evento1.horario, evento1, dadosEventos.evento1.duracao);
  event1.enable(dadosEventos.evento1.habilitado);
  event2.criarEvento(dadosEventos.evento2.horario, evento2, dadosEventos.evento2.duracao);
  event2.enable(dadosEventos.evento2.habilitado);
  event3.criarEvento(dadosEventos.evento3.horario, evento3, dadosEventos.evento3.duracao);  
  event3.enable(dadosEventos.evento3.habilitado);
}

void loop() {
  digitalClockDisplay();
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

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
