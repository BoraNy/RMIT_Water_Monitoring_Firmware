#define UART0_TX 1
#define UART0_RX 3
#define UART1_TX 10
#define UART1_RX 9
#define UART2_TX 17
#define UART2_RX 16

#define TX_ 22
#define RX_ 19

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_, TX_);
}

void loop() {

  if (Serial1.available() > 0) {
    Serial.println(char(Serial1.read()));
  }
}
