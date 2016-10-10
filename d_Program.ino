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
	lcd.setCursor(0,0);
	lcd.print("Estou pronta!");
	lcd.setCursor(0,1);
    lcd.print("Inicie no app!");
    ledPin = HIGH;

    while () { // ver quando recebe aperto de botao no app
    	terminal.println("Iniciando estágio de aquecimento de água");
    	terminal.flush();
    	ledPin = LOW;
    }
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

      terminal.println("Água aquecida./nColoque o saco com os grãos e prenda-o com cuidado./nAjeite o termômetro novamente.\nQuando pronto, clique em continuar");
      terminal.flush();
      ledPin = HIGH;

	    while () { // ver quando recebe aperto de botao no app
	    	terminal.println("Iniciando estágio de aquecimento de água");
	    	terminal.flush();
	    	ledPin = LOW;
	    }

      return;            
    }
  
  
  }
}

// 2
void mashing(){
	int time = millis() / 1000; //tempo em segundos
	bool done = false;
	int current_time;
	int stir = 1;

	while(not done) {
        if (immersionTemp < mashTemp - 2) {
			heater1 = HIGH;
		}

		else if (immersionTemp > mashTemp + 2) {
			heater1 = LOW;
		}
        
        current_time = millis()/1000;
        if(current_time >= time+mashTime*60){
			done = true;
			ledPin = HIGH;
			terminal.println("Brassagem acabou. Retire os grãos e deixe a tampa semi aberta. Aperte o botão quando o fizer.");
			terminal.flush();
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Brassagem acabou");
		}
		else if (current_time >= time*n*600){
			ledPin = HIGH;
			terminal.println("Hora de mexer!");
			terminal.flush();
			lcd.clear();
			lcd.setCursor(0,0);
			lcd.print("Hora de mexer!");
		}
		else if (ledPin == HIGH and) { // se o led estiver aceso e o usuario apertar o botao de que ja mexeu
			ledPin = LOW;
		}
	}

	while () { // ver quando recebe aperto de botao no app
    	terminal.println("Iniciando estágio de aquecimento de água");
    	terminal.flush();
    	ledPin = LOW;
    }
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
      terminal.println("Água aquecida.");
      terminal.flush();
      ledPin = HIGH;

	    while () { // ver quando recebe aperto de botao no app
	    	terminal.println("Iniciando estágio de fervura.");
	    	terminal.flush();
	    	ledPin = LOW;
	    }
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
