/* Ben Eater 6502 Computer
 *  Script to read data in from the address lines of the 6502 and print to screen
 * Arduino MEGA2560
 * 
*/
#define CLOCK 2
#define READ_WRITE 3

#define ARDUINO_EXT_CLOCK 12
#define CLK_SPEED 1

const char ADDR[] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
const char DATA[] = {39, 41, 43, 45, 47, 49, 51, 53};


void setup() 
{
  // Read in the clock pin, to trigger the function when a clock pulse is detected
  pinMode(CLOCK, INPUT);
  pinMode(READ_WRITE, INPUT);  

  // Use the Arduino to generate a Clock pulse
  pinMode(ARDUINO_EXT_CLOCK, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  for(int n = 0; n < 16; n += 1)
  {
    pinMode(ADDR[n], INPUT);
  }

  for(int n = 0; n < 8; n += 1)
  {
    pinMode(DATA[n], INPUT);
  }

  // Detect clok pulse and use this as trigger to log out address & data lines
  attachInterrupt(digitalPinToInterrupt(CLOCK), onClock, RISING);
  
  Serial.begin(57600);
}

void onClock()
{
  char output[15];
  
  unsigned int address = 0;
  
  for(int n = 0; n < 16; n += 1)
  {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    Serial.print(bit);
    address = (address << 1) + bit;
  }
  
  Serial.print("    ");

  unsigned int data = 0;
  for(int n = 0; n < 8; n += 1)
  {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    Serial.print(bit);
    data = (data << 1) + bit;
  }

  sprintf(output, "    %04x  %c  %02x", address, digitalRead(READ_WRITE) ? 'r' : 'w', data);
  Serial.println(output);  
}

void loop() 
{
  // Create a clock pusle if not using an external clock
  
  digitalWrite(ARDUINO_EXT_CLOCK, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  delay(CLK_SPEED);                              // wait for a second

  digitalWrite(ARDUINO_EXT_CLOCK, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  delay(CLK_SPEED);
}
