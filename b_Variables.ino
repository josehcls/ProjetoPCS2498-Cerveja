
// Tempo
int time = 0;
int currentTime = 0;

unsigned long timeNow = 0;
unsigned long timeLast = 0;

//int hours = startingHour;
int minutesCounter = 0;    
int timeEstimate = 0;
int timeTemp = 0;

// Temperatures and Humidity
float immersionTemp = 0.0;
float localTemp = 0.0;
float localHumidity = 0.0;

int hop = 1; 

int heater1 = 0;
int heater2 = 0;

//int heaterElement1 = D3;
//int heaterElement2 = D4;

int iceNeeded = liters;

int switchState = 0;
int switch1 = 0;

int lastnext = 0;
int next = 0;

// Estados

int stage = 0;

#declare STANDY_BY 			0
#declare HEAT_TILL_MASH 	1
#declare MASHING 			2
#declare HEAT_TILL_BOIL 	3
#declare BOILING 			4
#declare COOLDOWN 			5
#declare PITCH_YEAST 		6
#declare FINISH 			7

int subStage = 0;