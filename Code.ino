#include <Keypad.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include<LiquidCrystal_I2C.h>
#define ONE_WIRE_BUS 25
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,16,2);
float Celcius=0;
const byte ROWS = 4;
const byte COLS = 3;
float temp_set=0; 
char keys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {4,16,17,5}; //R1,R2,R3,R4
//connect to the column pinouts of the keypad
byte colPins[COLS] = {18,19,23};//C1,C2,C3
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup()
{
  pinMode(26, OUTPUT);
  pinMode(32, OUTPUT);
  digitalWrite(27,LOW);
  Serial.begin(9600);
  sensors.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("1.Tea 2.Coffee");
  delay(3000);
  lcd.clear();
  lcd.print("3.Water");
  delay(3000);
  lcd.clear();
  temp_set=GetNumber();
  lcd.clear();
  lcd.print("Temp Set=");
  lcd.print(temp_set);
  lcd.print(" C");
  delay(3000);
  lcd.clear();
}
void loop()
{
  sensors.requestTemperatures(); 
  Celcius=sensors.getTempCByIndex(0);
  lcd.setCursor(3,0);
  lcd.print("Live Temp:");
  lcd.setCursor(4,1);
  lcd.print(Celcius);
  lcd.print(" C");
  delay(1000);
  lcd.clear();
  if(Celcius>=temp_set)
  {
      digitalWrite(32,HIGH);
      digitalWrite(26, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(26, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);    
  }
}
int GetNumber()
{
   int num = 0;
   char key = keypad.getKey();
    while(key != '#')
    {
        switch (key)
        {
           case NO_KEY:
              break;
  
           case '1': 
              lcd.print(key);
              Serial.print(key);
              num = 50;
              break;

           case '2':
              lcd.print(key);
              Serial.print(key);
              num = 55;
              break;

           case '3':
              lcd.print(key);
              Serial.print(key);
              num = 45;
              break;
              
           case '*':
              num = 0;
              lcd.clear();
              key = keypad.getKey();
              temp_set=GetNumber();
              break;
        }
        key = keypad.getKey();
     }
   return num;
}
