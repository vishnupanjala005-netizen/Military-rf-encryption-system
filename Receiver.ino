#include <VirtualWire.h>
#include <string.h>

#define RX_PIN 11

char receivedData[20];

// Decryption function (same XOR used in transmitter)
void decrypt(char *data) {
  while (*data) {
    *data ^= 0x0F;   // reverse XOR
    data++;
  }
}

void setup() {
  Serial.begin(9600);

  vw_set_rx_pin(RX_PIN);   // RX data pin
  vw_setup(2000);          // bitrate (must match transmitter)
  vw_rx_start();           // start receiver
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Check if message received
  if (vw_get_message(buf, &buflen)) {
    buf[buflen] = '\0';   // null terminate

    strcpy(receivedData, (char*)buf);
    decrypt(receivedData);

    Serial.print("Received: ");
    Serial.println(receivedData);
  }
}
