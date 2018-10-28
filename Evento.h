#ifndef EVENTO_H
#define EVENTO_H

#include <TimeLib.h>
#include <TimeAlarms.h>

struct DadoEvento{
  time_t horario;
  time_t duracao;
  bool habilitado;
};


class Evento{

  public:
  Evento::Evento();
  
  inline void setIdEvento(AlarmId evento){idEvento=evento;}
  inline void setIdDuracao(AlarmId duracao){idDuracao=duracao;}
  inline AlarmId getIdEvento(){return idEvento;}
  inline AlarmId getIdDuracao(){return idDuracao;}

  void enable(bool habilitado=true);

  void criarEvento(time_t horario, OnTick_t funcEvento, time_t duracao);
  void criarEvento(DadoEvento dado, OnTick_t funcEvento);
  void iniciar(OnTick_t funcDuracao);
  void finalizar();
  
  
  private:
  AlarmId idEvento;
  AlarmId idDuracao;
  time_t duracaoEvento;
  
};

#endif
