#include <Arduino.h>
#include <Arduino_CRSF.h>

CRSF crsf;

#define RSSI_LED1 A7
#define RSSI_LED2 A8
#define RSSI_LED3 A9
#define RSSI_LED4 A10

#define GENERAL_LED1 A11
#define GENERAL_LED2 A12

bool led = LOW;
long last_blink_millie = 0; 

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(115200);             // for serial monitor
  crsf.begin(&Serial3, 115200);     // for receiver

  // lambda [] (parameter) {function}
  // whatever function this lambda makes will be run whenever the updateChannels is ran
  // pointer to this function is passed into the m_dataReceivedCallback by onDataReceived 
  // m_channels which is the array holding channel values is passed into this fucntion and gets printed

  crsf.onDataReceived([](const uint16_t channels[]) {
    char buffer[100];
    sprintf(buffer, "%d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\t %d\n",
          channels[0],
          channels[1],
          channels[2],
          channels[3],
          channels[4],
          channels[5],
          channels[6],
          channels[7],
          channels[8],
          channels[9],
          channels[10],
          channels[11],
          channels[12],
          channels[13],
          channels[14],
          channels[15]);
    Serial.print(buffer); 
    digitalWrite(13, !digitalRead(13));
    // sprintf(buffer, "CH1: %d\tCH2: %d\tCH3: %d\tCH4: %d\tCH5: %d\tCH6: %d\tCH7: %d\tCH8: %d\n",
    //       channels[0],
    //       channels[1],
    //       channels[2],
    //       channels[3],
    //       channels[4],
    //       channels[5],
    //       channels[6],
    //       channels[7]);
    // Serial.print(buffer); 
  });
}

void loop()
{
    // Serial.println("hello");
    // delay(1000);
    // Serial.println(crsf.m_channels[0]);
    


    if (millis() - last_blink_millie > 100) {
        digitalWrite(RSSI_LED1, led);
        digitalWrite(RSSI_LED2, led);
        digitalWrite(RSSI_LED3, led);
        digitalWrite(RSSI_LED4, led);

        digitalWrite(GENERAL_LED1, led);
        digitalWrite(GENERAL_LED2, led);
        led = !led;
        last_blink_millie = millis();
    }

    delay(100);
    
   
}


void serialEvent3()
{
  // serialEvent3 is ran after each loop, its not a ISR
  crsf.readPacket();
  // digitalWrite(13, !digitalRead(13));
}