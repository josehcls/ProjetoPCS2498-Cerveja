 //Para o botão de Próximo
BLYNK_WRITE(V27)
{
  if (param.asInt())
  {
    lastnext = next;  //Atualiza next
    next = 1;
  }
  else
  {
    lastnext = next;  //Atualiza next
    next = 0;
  }

  if ((lastnext == 0)and(next == 1))  //
  {
    NOT_BOTAO = false;
  } 
}

float getImmersionTemp ()
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

float getLocalTemp ()
{
  return dht.readTemperature();
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
    digitalWrite(LEDPIN,HIGH);

 // ver quando recebe aperto de botao no app
  if(!NOT_BOTAO){
    terminal.println("Iniciando estágio de aquecimento de água");
    terminal.flush();
    digitalWrite(LEDPIN,LOW);
    estado += 1;
    NOT_BOTAO = true;
  }
}

// 1
void heatTilMashTemp()
{
  while (1)
  {
    NOT_BOTAO = true;
    
    lcd.setCursor(0,0);
    lcd.print("1:AQUECENDO ");
    lcd.print(mashTemp);
    lcd.print("C");
    lcd.setCursor(0,1);
    //lcd.print("00:00  TI:");
    lcd.print(immersionTemp);
    //lcd.print("C");
  
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
      digitalWrite(LEDPIN,HIGH);

      while (NOT_BOTAO) {
        delay(1000); 
        Blynk.run();
        lcd.setCursor(0,1);
        lcd.print(immersionTemp);
        } // ver quando recebe aperto de botao no app
        
      terminal.println("Iniciando estágio de aquecimento de água");
      terminal.flush();
      digitalWrite(LEDPIN,LOW);

      return;            
    }
  }
}

// 2
void mashing(){
  time = millis() / 1000; //tempo em segundos
  bool done = false;  
  int stir = 1;  

  while(not done) {
    Blynk.run();
    if (immersionTemp < mashTemp - 2) {
      heater1 = HIGH;
    }

    else if (immersionTemp > mashTemp + 2) {
      heater1 = LOW;
    }
        
    current_time = millis()/1000;
    if(current_time >= time+mashTime*60) {
      done = true;
      digitalWrite(LEDPIN,HIGH);
      terminal.println("Brassagem acabou. Retire os grãos e deixe a tampa semi aberta. Aperte o botão quando o fizer.");
      terminal.flush();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Brassagem acabou");
    }
    else if (current_time >= time*stir*600){
      digitalWrite(LEDPIN,HIGH);
      terminal.println("Hora de mexer!");
      terminal.flush();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Hora de mexer!");
      stir++;
    }
    else if (NOT_BOTAO) { // se o led estiver aceso e o usuario apertar o botao de que ja mexeu
      digitalWrite(LEDPIN,LOW);
    }
  }

  while (NOT_BOTAO); // ver quando recebe aperto de botao no app
  terminal.println("Iniciando estágio de aquecimento de água");
  terminal.flush();
  digitalWrite(LEDPIN,LOW);
}

// 3
void heatTilBoil(){
  while (1) 
  {
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
        digitalWrite(LEDPIN,HIGH);

        while (NOT_BOTAO); // ver quando recebe aperto de botao no app
        terminal.println("Iniciando estágio de fervura.");
        terminal.flush();
        digitalWrite(LEDPIN,LOW);
        return;            
    }
  }
}

void boil()
{  
  time = millis() / 1000;
  while(1)
  {    
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
    
    current_time = millis()/1000;
    if (current_time >= hopTime[hop] && hopTime[hop] != -1)
    {
        terminal.println("ADD HOP " + String(hop));
        terminal.flush();
        hop++;  
    }
    else if (current_time >= boilTime && hopTime[hop] == -1)
    {
        heater1 = HIGH;
        heater2 = HIGH;
        return;
    }
  }
}

void coolDown(){
  while (1){
    lcd.setCursor(0,0);
    lcd.print("1:ESFRIANDO, T =");
    lcd.setCursor(0,1);
    lcd.print(immersionTemp);
    lcd.print(" C");

    updateTempAndHumidity();

    if (immersionTemp < yeastPitchTemperature){
      terminal.println("Água resfriada. Vá para o próximo estágio para receber instruções das próximas etapas.");
      terminal.flush();
      digitalWrite(LEDPIN,HIGH);

      while(NOT_BOTAO); // ver quando recebe aperto de botao no app
      terminal.println("Iniciando estágio de fermentação");
      terminal.flush();
      digitalWrite(LEDPIN,LOW);
    return;            
    }
  }
}

void addYeast(){
  terminal.println("Transfira para novo recipiente, adicione a levedura, feche o recipiente e coloque em lugar escuro por 30 dias");
  terminal.flush();
  digitalWrite(LEDPIN,HIGH);

  while(NOT_BOTAO); // ver quando recebe aperto de botao no app
  terminal.println("Iniciando estágio de finalização");
  terminal.flush();
  digitalWrite(LEDPIN,LOW);
}

void finish(){
  terminal.println("Parabéns! Em 30 dias você terá uma deliciosa cerveja! Saúde!");
  terminal.flush();
}
