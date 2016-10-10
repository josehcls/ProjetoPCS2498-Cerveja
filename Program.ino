float getTemperaturaImersao ()
{
  sensors.requestTemperatures();
  return lcd.print(sensors.getTempCByIndex(0));
}

float getTemperaturaAmbiente ()
{
  return lcd.print(dht.readTemperature());
}

float getUmidadeAmbiente ()
{
  return dht.readHumidity();
}

void heatTilMashTemp() {
		
}

void mashing() {
	
}

void heatTilBoli() {
	
}

void coolDown() {
	
}

void finish() {
	
}