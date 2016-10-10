float getImmersionTemp ()
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

void updateTempAndHumidity()
{
  immersionTemp = getImmersionTemp ();
  localTemp = getLocalTemp ();
  localHumidity = getLocalHumidity ();
}

void printTemperaturesAndHumidity ()
{
  lcd.setCursor(0,0);
  lcd.print("I:");
  lcd.print(immersionTemp);
  lcd.print(" A:");
  lcd.print(localTemp);
  
  lcd.setCursor(0,1);
  lcd.print("Umd: ");
  lcd.print(localHumidity);
  lcd.print("%");
}

// 0
void standBy(){
	
}

// 1
void heatTilMashTemp()
{
  while (1)
  {
    lcd.setCursor(0,0);
    lcd.print("1:AQUECENDO ");
    lcd.print(mashTemp);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("00:00  TI:");
    lcd.print(immersionTemp);
    lcd.print("C");
  
    // Ativa Aquecedores
    heater1 = HIGH;
    heater2 = HIGH;

    updateTempAndHumidity();
      
    if (immersionTemp > mashTemp)
    {
      // Desativa Aquecedores ate que os graos sejam colocados
      heater1 = LOW;
      heater2 = LOW;

      //terminal.println("Água aquecida./nColoque o saco com os grãos e prenda-o com cuidado./nAjeite o termômetro novamente.\nQuando pronto, clique em continuar");
      //terminal.flush();
      return;            
    }
  
  
  }
}

// 2
void mashing(){
	
}

// 3
void heatTilBoil(){
	lcd.setCursor(0,0);
  lcd.print("3:AQUECENDO ");
  lcd.print(boilTemp);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("00:00  TI:");
  lcd.print(immersionTemp);
  lcd.print("C");


  heater1 = HIGH;
  heater2 = HIGH;

  if (immersionTemp > boilTemp)
    {      
      //terminal.println("Aquecendo a água para a Fervura.");
      //terminal.flush();
      return;            
    }
}

void boil(){
  
  lcd.setCursor(0,0);
  lcd.print("4:FERVENDO ");
  lcd.print(boilTemp);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("00:00  TI:");
  lcd.print(immersionTemp);
  lcd.print("C");

  heater1 = HIGH;
  heater2 = HIGH;
  
  
  
}

void coolDown(){
	
}

void addYeast(){
	
}

void finish(){
	
}
