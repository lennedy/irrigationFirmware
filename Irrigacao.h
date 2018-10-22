#include <TimeLib.h>
#include <TimeAlarms.h>
#include "Pinagem.h"
#include <Arduino.h>

class Irrigacao{

  public:
  Irrigacao();
  void config();
  void iniciarTudo();
  void pararTudo();

  

  private:
  void acionarBomba();
  void desligarBomba();
  void abrirValvulas();
  void fecharValvulas();  
};
