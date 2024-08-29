#define LEDPIN 11

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    pinMode(LEDPIN, OUTPUT);
}

void loop() {
    // Turn the LED on and notify the Raspberry Pi
    digitalWrite(LEDPIN, HIGH);  // Turn the LED on
    Serial1.println("LED_ON");   // Notify the Raspberry Pi
    Serial.println("LED_ON sent");
    delay(5000);  // Wait for 1 second

    // Turn the LED off and notify the Raspberry Pi
    digitalWrite(LEDPIN, LOW);   // Turn the LED off
    Serial1.println("LED_OFF");  // Notify the Raspberry Pi
    Serial.println("LED_OFF sent");
    delay(5000);  // Wait for 1 second
}

