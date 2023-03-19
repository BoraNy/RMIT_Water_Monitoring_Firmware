const int numberOfValue = 3;
String pieces[numberOfValue];
float firstValue, secodeValue, thirdValue, lastValue = 0;
String readString = ""; /* Read String from Serial */
uint8_t Index = 0;
uint8_t lastIndex = 0;

void setup() {
  Serial.begin(9600);
  if (!Serial) {
    Serial.print("Check Serial Connection");
    while (1)
      ;
  } else {
    Serial.println(" Ready for Serial Read ");
  }
}

void loop() {
  // Check for data coming in from serial
  if (Serial.available() > 0) {
    // Read the first byte and store it as a char
    char ch = Serial.read();
    // Do all the processing here since this is the end of a line
    if (ch == '\n') {
      for (int i = 0; i < readString.length(); i++) {
        // Loop through each character and check if it's a comma
        if (readString.substring(i, i + 1) == ",") {
          // Grab the piece from the last index up to the current position and store it
          pieces[Index] = readString.substring(lastIndex, i);
          lastIndex = i + 1;
          Index++;
        }
        if (i == readString.length() - 1) {
          // Grab the last part of the string from the lastIndex to the end
          pieces[Index] = readString.substring(lastIndex, i);
        }
      }
      // Clear out string and Indexs to get ready for the next incoming string
      readString = "";
      Index = 0;
      lastIndex = 0;
    } else {
      readString += ch;
    }
  }
  firstValue = pieces[0].toFloat();
  secodeValue = pieces[1].toFloat();
  thirdValue = pieces[2].toFloat();
  lastValue = pieces[3].toFloat();
  Serial.print(firstValue);
  Serial.print(" ");
  Serial.print(secodeValue);
  Serial.print(" ");
  Serial.print(thirdValue);
  Serial.print(" ");
  Serial.println(lastValue);
}