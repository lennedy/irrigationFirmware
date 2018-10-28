#include "Evento.h"

Evento::Evento(){
  idEvento =  dtINVALID_ALARM_ID;
  idDuracao = dtINVALID_ALARM_ID;  
}

void Evento::enable(bool habilitado){
  
  if(habilitado){
    Alarm.enable(idEvento);
    Alarm.enable(idDuracao);
  }
  else{
    Alarm.disable(idEvento);
    Alarm.disable(idDuracao);
  }
}

void Evento::criarEvento(time_t horario, OnTick_t funcEvento, time_t duracao){
  idEvento = Alarm.alarmRepeat(horario, funcEvento);
}

void Evento::iniciar(OnTick_t funcDuracao){
  idDuracao = Alarm.timerOnce(duracaoEvento, funcDuracao);  
}

void Evento::criarEvento(DadoEvento dado, OnTick_t funcEvento){
  criarEvento(dado.horario, funcEvento, dado.duracao);
  enable(dado.habilitado);
}

void Evento::finalizar(){
  Alarm.free(idDuracao);
  idDuracao = dtINVALID_ALARM_ID;
}
