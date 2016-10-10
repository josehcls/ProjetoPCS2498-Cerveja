float getImersionTemp ()
{
  sensors.requestTemperatures();
  return lcd.print(sensors.getTempCByIndex(0));
}

float getLocalTemp ()
{
  return lcd.print(dht.readTemperature());
}

float getLocalHumidity ()
{
  return dht.readHumidity();
}

void printTemperaturesAndHumidity ()
{
  lcd.setCursor(0,0);
  lcd.print("I:");
  lcd.print(getImersionTemp());
  lcd.print(" A:");
  lcd.print(getLocalTemp());
  
  lcd.setCursor(0,1);
  lcd.print("Umd: ");
  lcd.print(getLocalHumidity());
  lcd.print("%");
}

void standBy(){
	
}

void heatTilMashTemp(){
		
}

void mashing(){
	
}

void heatTilBoil(){
	
}

void coolDown(){
	
}

void addYeast(){
	
}

void finish(){
	
}
