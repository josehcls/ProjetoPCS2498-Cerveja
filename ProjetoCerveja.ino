void heatTilMashTemp();
void printTemperaturesAndHumidity ();

void loop()
{
  standBy();
  heatTilMashTemp();
  mashing();
  heatTilBoil();
  coolDown();
  addYeast();
  finish();
 }
