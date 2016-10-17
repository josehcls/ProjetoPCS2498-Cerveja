// 

char auth[] = "d839d81fcfab4cc5ac4496279be3abd2";

//How many KiloWatt are your heating elements combined?

int KiloWatt = 2;

//Temperature and times in recipe:

float mashTemp = 28.0; // Temp in celcius
float boilTemp = 30.0; // Temp in celcius, set to max 99

int mashTime = 2; // number of minutes you are going to mash
int boilTime = 3; // number of minutes you are going to boil
int fermentTimeprimary = 23; // Number of days you are going to ferment
int fermentTimeSecondary = 22; // Number of days you are going to ferment in secondary, set to zero if you do not plan on using secondary fermenting, this is often not required. 


int yeastPitchTemperature = 24; // The ideal pitch temperature for your yeast, in celcius.

int fermentationTemperatureMin = 20; // Minimum Temp that the yeast can thrive in, in celcius.    
int fermentationTemperatureMax = 24; // Maximum Temp that the yeast can thrive in, in celcius.    

// after how many minutes of boiling the wort should this hop be added? 
// last value must be -1
int hopTime[5] = {1,2,3,-1};

//Liters you will make

int liters = 20; //The number of liters of boiled wort you are planning on having AFTER the boil.

