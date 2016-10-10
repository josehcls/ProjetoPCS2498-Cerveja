float getImersionTemp ()
{
  sensors.requestTemperatures();
  return lcd.print(sensors.getTempCByIndex(0));
}

float getLocalTemp ()
{
  return lcd.print(dht.readTemperature());
}

float getLocalUmidity ()
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
