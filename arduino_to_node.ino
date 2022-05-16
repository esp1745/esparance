#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 7
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
ThreeWire myWire(10,9,8); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

LiquidCrystal_I2C lcd(0x27,20,4);
const char* SERVER_NAME="http://esparance.atwebpages.com/sensordata.php";
String PROJECT_API_KEY="Hello world"; 
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;


void setup(){
  Serial.begin(9600);
    Serial.print("");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
    RtcDateTime now = Rtc.GetDateTime();
    delay(5000);
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.print("Welcome to computer science department!");
  delay(1000);
      for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) { 
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

      
  }
   

}

void loop(){
  lcd.clear();
     DHT.read(DHT11_PIN);
    Serial.print(" temp:");
    Serial.print(DHT.temperature);
   Serial.print(" humi:");
    Serial.println(DHT.humidity);
    delay(3000);

        RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    delay(3000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);



}