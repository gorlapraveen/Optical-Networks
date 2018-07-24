int floatswitch = 7;

void setup() {
pinMode(floatswitch,INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
 int x = digitalRead(floatswitch);
 Serial.println(x);
}
