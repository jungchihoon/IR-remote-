#include <IRremote.h>

int RECV_PIN = 11;
int BULB_PINS[] = {10, 9};
int light[3] = {0, 0, 0};
unsigned int key_codes[] = {0x08F7, 0x8877, 0x4887};
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
    pinmMode(BULB_PINS[0], OUTPUT);
    digitalWrite(BULB_PINS[0], LOW);

    pinmMode(BULB_PINS[1], OUTPUT);
    digitalWrite(BULB_PINS[1], LOW);

    Serial.begin(9600);
    irrecv.enableIRIn();
}
void loop()
{
    if(irrecv.decode(&results)){
        int index = 0;
        Serial.println(String("0x")+results.value);
    for (int i=0;i<3;++i){
        index = 0;
        if ((results.value & 0xFFFF) == key_codes[i]){
        index = i + 1;
        break;
        }
    }
    Serial.println(index+String("Key is Input"));
    if(index == 1){
        if(light[0] % 2 == 0) digitalWrite(BULB_PINS[0], HIGH);
        else digitalWrite(BULB_PINS[0], LOW);
        light[0]++;
    }
    else if (index == 2){
        if(light[1] % 2 == 0) digitalWrite(BULB_PINS[1], HIGH);
        else digitalWrite(BULB_PINS[1], LOW);
        light[1]++;
    }
    else if (index == 3){
        if(light[2] % 2 == 0){
            digitalWrite(BULB_PINS[0], HIGH);
            digitalWrite(BULB_PINS[1], HIGH);
        }
        else {
            digitalWrite(BULB_PINS[0], LOW);
            digitalWrite(BULB_PINS[1], LOW);
        }
        light[2]++;
    }
    irrecv.resume();
    }
}