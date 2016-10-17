//Para o botão de Próximo
BLYNK_WRITE(V27)
{
    if (param.asInt())
    {
        lastnext = next;    //Atualiza next
        next = 1;
    }
    else
    {
        lastnext = next;    //Atualiza next
        next = 0;
    }

    if ((lastnext == 0)and(next == 1))    //
    {
        goButton = true;
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

String getElapsedTime (int secondsReference)
{
    currentTime = millis() / 1000;
    
    String elapsedTime = String((currentTime - secondsReference) / 60);
    elapsedTime += ":";
    elapsedTime += String((currentTime - secondsReference) % 60);

    return elapsedTime;
}

String getRemainingTime (int secondsReference, int totalTime)
{
    currentTime = millis() / 1000;
    int elapsedTime = current - secondsReference

    if (elapsedTime < 0) elapsedTime = 0;

    String remainingTime = String((totalTime - elapsedTime) / 60);
    remainingTime += ":";
    remainingTime += String((totalTime - elapsedTime) % 60);

    return remainingTime;
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

void standBy()
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Estou pronta!");
    lcd.setCursor(0,1);
        lcd.print("Inicie no app!");
        digitalWrite(LEDPIN,HIGH);

    if(goButton)
    {
        terminal.println("Iniciando estágio de aquecimento de água");
        terminal.flush();
        digitalWrite(LEDPIN,LOW);
        stage = HEAT_TILL_MASH;
        subStage = 0;
    }
}

void heatTilMashTemp()
{
    if (subStage == 0)
    {
        goButton = false;
        time = millis() / 1000; //tempo em segundos
        subStage = 1;
    }

    updateTempAndHumidity();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1:AQUECENDO ");
    lcd.print(mashTemp);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(getElapsedTime(time));
    lcd.print("  ");
    lcd.print(immersionTemp);
    lcd.print("C");
    
    if (immersionTemp < mashTemp - 2)
    {
        // Ativa Aquecedores
        heater1 = HIGH;
        heater2 = HIGH;  
    }
        
    if (immersionTemp > mashTemp)
    {
        // Desativa Aquecedores ate que os graos sejam colocados
        heater1 = LOW;
        heater2 = LOW;

        if (subStage == 1)
        {
            terminal.println("Água aquecida.");
            terminal.println("Coloque o saco com os grãos e prenda-o com cuidado.")
            terminal.println("Ajeite o termômetro novamente");
            terminar.println("Quando pronto, clique em continuar");
            terminal.flush();
            subStage = 2;
        }

        digitalWrite(LEDPIN,HIGH);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("AQUECIMENTO OK!"); 
        lcd.setCursor(0,1);
        lcd.print(getElapsedTime(time));
        lcd.print("  ");
        lcd.print(immersionTemp);
        lcd.print("C");

        if (goButton)
        {         
            digitalWrite(LEDPIN,LOW);
            stage = MASHING;
            subStage = 0;
        }
        
    }
}

void mashing(){
    if (subStage == 0)
    {
        time = millis() / 1000; //tempo em segundos
        int stir = 1;
        subStage = 1;    
    }

        lcd.clear();
        if (subStage == 2)
        lcd.setCursor(0,0);
        lcd.print("2:BRASSAGEM "); 
        lcd.print(mashTemp);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print(getRemainingTime(time, mashTime));
        lcd.print("  ");
        lcd.print(immersionTemp);
        lcd.print("C");


    if (immersionTemp < mashTemp - 2) {
        heater1 = HIGH;
    }

    else if (immersionTemp > mashTemp + 2) {
        heater1 = LOW;
    }
            
    currentTime = millis() / 1000;
    
    if (currentTime >= time + mashTime*60)
    {
        digitalWrite(LEDPIN,HIGH);
        if (subStage == 1)
        {
            terminal.println("Brassagem acabou. Retire os grãos e deixe a tampa semi aberta.");
            terminal.println("Aperte o botão quando o fizer.");
            terminal.flush();  
            subStage = 2
        }

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BRASSAGEM OK");
        lcd.setCursor(0,1);
        lcd.print(getRemainingTime(time, mashTime));
        lcd.print("  ");
        lcd.print(immersionTemp);
        lcd.print("C");

    }
    else if (currentTime >= time*stir*600)
    {
        digitalWrite(LEDPIN,HIGH);
        terminal.println("Hora de mexer!");
        terminal.flush();
        
        stir++;
    }
    else if(NOT_BOTAO)
    {
        digitalWrite(LEDPIN,LOW);
    }
    

    if (goButton && subStage == 2)
    {
        terminal.println("Iniciando estágio de aquecimento do mosto para fervura");
        terminal.flush();
        digitalWrite(LEDPIN,LOW);
        stage = HEAT_TILL_BOIL;
        subStage = 0;
    }
}

// 3
void heatTilBoil(){
    while (1) 
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("1:AQUECENDO ");
        lcd.print(mashTemp);
        lcd.print("C");
        lcd.setCursor(0,1);
        lcd.print(getElapsedTime(time));
        lcd.print("  ");
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
        lcd.print("00:00    TI:");
        lcd.print(immersionTemp);
        lcd.print("C");

        heater1 = HIGH;
        heater2 = HIGH;
        
        currentTime = millis()/1000;
        if (currentTime >= hopTime[hop] && hopTime[hop] != -1)
        {
                terminal.println("ADD HOP " + String(hop));
                terminal.flush();
                hop++;    
        }
        else if (currentTime >= boilTime && hopTime[hop] == -1)
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
