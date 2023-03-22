#define TX_ 22
#define RX_ 19

String data = "123.12,321.32,456.65,789.98",
       delimiter = ",";
String splited[4];

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RX_, TX_);

  Serial.println(data);

  for (int i = 0; i < 4; i++)
  {
    splited[i] = data.substring(0, data.indexOf(delimiter));
    data.replace((splited[i] + ","), "");
  }

  Serial.println();
  Serial.println(splited[0]);
  Serial.println(splited[1]);
  Serial.println(splited[2]);
  Serial.println(splited[3]);
}

void loop() {
}
