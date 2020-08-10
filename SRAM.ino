/*---------------- SRAM ------------*/

#define SRAM_CS1     10
#define SRAM_CS2     13  // Not used
#define SRAM_OE      11
#define SRAM_WE      12



void setDigitalOut()
{
  for (int i = 0; i <= 7; i++)
  {
    pinMode(i + 2, OUTPUT);
    digitalWrite(i + 2, LOW);
  }
}

void setByte(byte out)
{
  setDigitalOut();
  digitalWrite(2, out & 0x01);
  digitalWrite(3, out & 0x02);
  digitalWrite(4, out & 0x04);
  digitalWrite(5, out & 0x08);
  digitalWrite(6, out & 0x10);
  digitalWrite(7, out & 0x20);
  digitalWrite(8, out & 0x40);
  digitalWrite(9, out & 0x80);
}


void setDigitalIn()
{
  for (int i = 0; i <= 7; i++)
    pinMode(i + 2, INPUT);
}
byte readByte()
{
  setDigitalIn();
  byte temp_in = 0;
  temp_in = (digitalRead(2) * 1) + (digitalRead(3) * 2) + (digitalRead(4) * 4) + (digitalRead(5) * 8) + (digitalRead(6) * 16) + (digitalRead(7) * 32) + (digitalRead(8) * 64) + (digitalRead(9) * 128);
  return temp_in;
}
void setup() {
  Serial.begin(9600);

  pinMode(SRAM_CS1, OUTPUT);
  pinMode(SRAM_CS2, OUTPUT);
  pinMode(SRAM_OE, OUTPUT);
  pinMode(SRAM_WE, OUTPUT);

  for (int i = 0; i <= 15; i++)
    pinMode(i + 22, OUTPUT);

  Serial.println("Data writing to SRAM Start");
  setDigitalOut();
  digitalWrite(SRAM_CS1, LOW);
  for (int i = 0; i <= 15; i++)
    digitalWrite(i + 22, LOW);

  digitalWrite(SRAM_CS1, HIGH);
  digitalWrite(SRAM_OE, HIGH);
  digitalWrite(SRAM_WE, LOW);
  delay(200);

  setByte(29);
  delay(200);
  digitalWrite(SRAM_CS1, HIGH);
  digitalWrite(SRAM_OE, HIGH);
  digitalWrite(SRAM_WE, HIGH);
  Serial.println("Data writing complete");

  Serial.println("Data Reading to SRAM Start");
  digitalWrite(SRAM_CS1, LOW);
  digitalWrite(SRAM_OE, HIGH);
  digitalWrite(SRAM_WE, HIGH);
  delay(3);
  digitalWrite(SRAM_CS1, LOW);
  digitalWrite(SRAM_OE, HIGH);
  digitalWrite(SRAM_WE, HIGH);
  for (int i = 0; i <= 15; i++)
    digitalWrite(i + 22, LOW);
  delay(7);
  digitalWrite(SRAM_OE, LOW);
  delay(5);
  Serial.println(readByte());
  setDigitalIn();
  digitalWrite(SRAM_CS1, HIGH);
  digitalWrite(SRAM_WE, HIGH);
  digitalWrite(SRAM_OE, HIGH);
  delay(16);
  Serial.println("Data Reading complete ");
}

// the loop function runs over and over again forever
void loop() {

}
