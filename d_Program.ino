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

void heatTilMashTemp(){
		
}

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

void heatTilBoil(){
	
}

void coolDown(){
	
}

void addYeast(){
	
}

void finish(){
	
}
