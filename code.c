/**********************************************************************
 * Smart Multi-Zone Classroom Appliance Control System
 *
 * Controller : ESP32
 * Sensors    : 3 PIR Sensors + DHT22
 * Display    : 16x2 I2C LCD
 * Outputs    : 3 Relay Channels
 *
 * Author : Priyanshu Pandey
 *********************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);

//========================= PIR PINS =========================//

#define PIR_FRONT      13
#define PIR_MIDDLE     12
#define PIR_BACK       14

//======================== RELAY PINS ========================//

#define RELAY_FRONT    18
#define RELAY_MIDDLE   19
#define RELAY_BACK     23

//========================= CONSTANTS ========================//

#define RELAY_ON LOW
#define RELAY_OFF HIGH

//========================= ZONE DATA ========================//

struct Zone
{
    bool occupied;
    bool relayState;

    unsigned long lastMotion;

    unsigned long delayTime;

    byte pirPin;
    byte relayPin;

    String name;
};

Zone front;
Zone middle;
Zone back;

//===================== GLOBAL VARIABLES =====================//

float temperature = 0.0;
float humidity = 0.0;

unsigned long lcdTimer = 0;
unsigned long serialTimer = 0;

//====================== LCD FUNCTIONS =======================//

void lcdBootScreen()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("SMART CLASSROOM");

    lcd.setCursor(0,1);
    lcd.print("POWER CONTROL");

    delay(2000);

    lcd.clear();
}

void updateLCD()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temperature,1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(10,0);
    lcd.print("H:");
    lcd.print((int)humidity);

    lcd.setCursor(0,1);

    lcd.print(front.relayState ? "F" : "-");
    lcd.print(" ");

    lcd.print(middle.relayState ? "M" : "-");
    lcd.print(" ");

    lcd.print(back.relayState ? "B" : "-");
}

//==================== INITIALIZE ZONES ======================//

void initializeZones()
{

    front.pirPin = PIR_FRONT;
    front.relayPin = RELAY_FRONT;
    front.name = "Front";

    middle.pirPin = PIR_MIDDLE;
    middle.relayPin = RELAY_MIDDLE;
    middle.name = "Middle";

    back.pirPin = PIR_BACK;
    back.relayPin = RELAY_BACK;
    back.name = "Back";

}

//===================== TEMPERATURE ==========================//

void readEnvironment()
{

    humidity = dht.readHumidity();

    temperature = dht.readTemperature();

}

//=================== ADAPTIVE DELAY =========================//

unsigned long calculateDelay()
{

    if(temperature > 30)
    {
        return 600000;      //10 min
    }

    else if(temperature > 27)
    {
        return 420000;      //7 min
    }

    else
    {
        return 180000;      //3 min
    }

}

//====================== RELAY CONTROL =======================//

void relayON(Zone &zone)
{

    digitalWrite(zone.relayPin,RELAY_ON);

    zone.relayState=true;

}

void relayOFF(Zone &zone)
{

    digitalWrite(zone.relayPin,RELAY_OFF);

    zone.relayState=false;

}

//===================== MOTION CHECK =========================//

void checkMotion(Zone &zone)
{

    bool motion=digitalRead(zone.pirPin);

    if(motion)
    {

        zone.occupied=true;

        zone.lastMotion=millis();

        zone.delayTime=calculateDelay();

        relayON(zone);

    }

}

//===================== SERIAL OUTPUT ========================//

void serialReport()
{

    Serial.println("--------------------------------");

    Serial.print("Temperature : ");
    Serial.println(temperature);

    Serial.print("Humidity : ");
    Serial.println(humidity);

    Serial.print("Front : ");
    Serial.println(front.relayState);

    Serial.print("Middle : ");
    Serial.println(middle.relayState);

    Serial.print("Back : ");
    Serial.println(back.relayState);

}

//========================= SETUP ============================//

void setup()
{

    Serial.begin(115200);

    dht.begin();

    lcd.init();

    lcd.backlight();

    pinMode(PIR_FRONT,INPUT);
    pinMode(PIR_MIDDLE,INPUT);
    pinMode(PIR_BACK,INPUT);

    pinMode(RELAY_FRONT,OUTPUT);
    pinMode(RELAY_MIDDLE,OUTPUT);
    pinMode(RELAY_BACK,OUTPUT);

    digitalWrite(RELAY_FRONT,RELAY_OFF);
    digitalWrite(RELAY_MIDDLE,RELAY_OFF);
    digitalWrite(RELAY_BACK,RELAY_OFF);

    initializeZones();

    lcdBootScreen();

    Serial.println("System Started");

}




//====================== ZONE UPDATE ======================//

void updateZone(Zone &zone)
{

    checkMotion(zone);

    if(zone.relayState)
    {

        if((millis() - zone.lastMotion) > zone.delayTime)
        {

            relayOFF(zone);

            zone.occupied = false;

        }

    }

}

//==================== PROCESS ALL ZONES ==================//

void processZones()
{

    updateZone(front);

    updateZone(middle);

    updateZone(back);

}

//=================== DISPLAY SCHEDULER ===================//

void displayTask()
{

    if(millis() - lcdTimer >= 1000)
    {

        lcdTimer = millis();

        updateLCD();

    }

}

//==================== SERIAL SCHEDULER ===================//

void serialTask()
{

    if(millis() - serialTimer >= 2000)
    {

        serialTimer = millis();

        serialReport();

    }

}

//=================== SYSTEM STATUS =======================//

void systemStatus()
{

    if(front.relayState ||
       middle.relayState ||
       back.relayState)
    {

        Serial.println("System Active");

    }
    else
    {

        Serial.println("No Occupancy");

    }

}

//==================== MAIN LOOP ==========================//

void loop()
{

    readEnvironment();

    processZones();

    displayTask();

    serialTask();

    systemStatus();

    delay(100);

}
