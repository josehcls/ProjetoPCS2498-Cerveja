#include <BlynkSimpleStream.h>

void standBy();
void heatTilMashTemp();
void mashing();
void heatTilBoil();
void coolDown();
void addYeast();
void finish();

void printTemperaturesAndHumidity ();


void loop()
{
  Blynk.run();
  switch (estado) {
      case 0:
        standBy();
        break;
      case 1:
      	heatTilMashTemp();
        break;      
      case 2:
      mashing();
        break;      

      case 3:
      heatTilBoil();
        break;      

      case 4:
      coolDown();
        break;      

      case 5:
      addYeast();
        break;      
        
      case 6:
        finish();
        break;
  }
 }
