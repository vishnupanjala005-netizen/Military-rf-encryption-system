#include <VirtualWire.h>
#include <string.h>

#define BTN1 2
#define BTN2 3
#define TX_PIN 12

void encrypt(char *data) {
    while (*data) {
        *data ^= 0x0F;   // simple XOR encryption
        data++;
    }
}

void setup() {
    pinMode(BTN1, INPUT);
    pinMode(BTN2, INPUT);

    vw_set_tx_pin(TX_PIN);
    vw_setup(2000);
}

void loop() {
    char msg[10];

    if (digitalRead(BTN1)) {
        strcpy(msg, "A1");
    } 
    else if (digitalRead(BTN2)) {
        strcpy(msg, "B2");
    } 
    else {
        strcpy(msg, "00");
    }

    encrypt(msg);

    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx();

    delay(500);
}
