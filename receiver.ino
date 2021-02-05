#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 myRadio(8, 9); // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

struct package
{
  int joyposX;
  int joyposY;
};

typedef struct package Package;
Package data;



const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B

const int B1A = 4;//define pin 8 for B1A
const int B1B = 5;//define pin 9 for B1B


void setup() {
  while (!Serial);

  Serial.begin(9600);
  myRadio.begin();
  //set the address
  myRadio.openReadingPipe(0, address);
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  //Set module as receiver
  myRadio.startListening();
  pinMode(IN1, OUTPUT); // define pin as output
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( myRadio.available())
  {

    myRadio.read( &data, sizeof(data) );

    // Serial.print("X : ");
    // Serial.println(data.joyposX);
    //Serial.print("Y : ");
    //Serial.println(data.joyposY);
    // Serial.print("potValue : ");
    //Serial.println(data.potValue);
    delay(10);

    if (data.joyposX > 510)
    {
      // This is forward
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    else if (data.joyposX < 480)
    {
      // This is backward
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

    }

    else if (data.joyposY < 480)
    {
      // This is right
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);

    }

    else if (data.joyposY > 520)
    {
      // This is right
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);

    }

    else
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
    }
  }
}
