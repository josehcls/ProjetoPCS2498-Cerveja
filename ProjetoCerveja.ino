#include <BlynkSimpleStream.h>

void standBy();
void heatTilMashTemp();
void mashing();
void heatTilBoil();
void boil();
void coolDown();
void addYeast();
void finish();

// Estados
int stage;
#define STANDY_BY 0
#define HEAT_TILL_MASH 1
#define MASHING 2
#define HEAT_TILL_BOIL 3
#define BOILING  4
#define COOLDOWN 5
#define PITCH_YEAST 6
#define FINISH 7
int subStage;

void loop()
{
    Blynk.run();
    switch (stage) 
    {
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
