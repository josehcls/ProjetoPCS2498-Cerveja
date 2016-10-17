#include <BlynkSimpleStream.h>

void standBy();
void heatTilMashTemp();
void mashing();
void heatTilBoil();
void boil();
void coolDown();
void addYeast();
void finish();

void printTemperaturesAndHumidity ();


void loop()
{
    Blynk.run();
    switch (estado) {
            case STANDY_BY:
                standBy();
                break;
                
            case HEAT_TILL_MASH:
              	heatTilMashTemp();
                break; 
                         
            case MASHING:
                mashing();
                break;            

            case HEAT_TILL_BOIL:
                heatTilBoil();
                break;            

            case BOILING:
                boil();
                break;

            case COOLDOWN:
                coolDown();
                break;            

            case PITCH_YEAST:
                addYeast();
                break;            
                
            case FINISH:
                finish();
                break;
    }
 }
