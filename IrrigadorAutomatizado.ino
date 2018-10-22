#include "Irrigacao.h"
#include "EEPROM.h"

#define ENDERECO_EEPROM 0

struct DadoEvento{
  time_t Horario;
  time_t duracao;
  bool habilitado;
};

struct DadosEventos{
  DadoEvento evento1;
  DadoEvento evento2; 
  DadoEvento evento3;
};

AlarmId idDesligar1,idDesligar2,idDesligar3;
AlarmId idEvento1, idEvento2, idEvento3;
Irrigacao irrigacao;

void setup() {
  DadosEventos dadosEventos;
  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

  // Criação de alarmes. Depois essa criação deverá ficar em alguma função específica de comunicação
  // Deve-se ler os valores do alarme da memória EEPROM

  EEPROM.get(ENDERECO_EEPROM, dadosEventos);
  
  idEvento1 = Alarm.alarmRepeat(6,30,0, evento1);  // 6:30am every day
  dadosEventos.evento1.habilitado ? Alarm.enable(idEvento1) : Alarm.disable(idEvento1);
  idEvento2 = Alarm.alarmRepeat(16,30,0,evento2);  // 16:30pm every day
  dadosEventos.evento2.habilitado ? Alarm.enable(idEvento2) : Alarm.disable(idEvento2);  
  idEvento3 = Alarm.alarmRepeat(16,30,0,evento3);  // 16:30pm every day
  dadosEventos.evento3.habilitado ? Alarm.enable(idEvento3) : Alarm.disable(idEvento3);
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

void evento1() {
  Serial.println("Ligar bomba manhã");
  //Timer que determinará quanto tempo ficará ligada a água
  idDesligar1 = Alarm.timerOnce(1*60, desligar);
  irrigacao.iniciarTudo();
}

void evento2() {
  Serial.println("Ligar bomba noite");
  //Timer que determinará quanto tempo ficará ligada a água
  idDesligar2 = Alarm.timerOnce(1*60, desligar);  
  irrigacao.iniciarTudo();
}

void evento3() {
  Serial.println("Ligar bomba noite");
  //Timer que determinará quanto tempo ficará ligada a água
  idDesligar3 = Alarm.timerOnce(1*60, desligar);  
  irrigacao.iniciarTudo();
}

void desligar() {
  Serial.println("This timer only triggers once, stop the 2 second timer");
  // use Alarm.free() to disable a timer and recycle its memory.
  Alarm.free(idDesligar1);
  Alarm.free(idDesligar2);
  Alarm.free(idDesligar3);
  // optional, but safest to "forget" the ID after memory recycled
  idDesligar1 = dtINVALID_ALARM_ID;
  idDesligar2 = dtINVALID_ALARM_ID;
  idDesligar3 = dtINVALID_ALARM_ID;
  // you can also use Alarm.disable() to turn the timer off, but keep
  // it in memory, to turn back on later with Alarm.enable().

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
