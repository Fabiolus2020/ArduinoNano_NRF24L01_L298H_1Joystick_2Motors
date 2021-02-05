// Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

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

//#define enA 10   // Note: Pin 9 in previous video ( pin 10 is used for the SPI communication of the NRF24L01)
#define in1 4
#define in2 5
//#define enB 3   // Note:  Pin 10 in previous video
#define in3 6
#define in4 7



//int motorSpeedA = 0;
//int motorSpeedB = 0;

void setup() {

  while (!Serial);

  Serial.begin(9600);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;

  //set the address
  myRadio.openReadingPipe(0, address);

  myRadio.startListening();
  // pinMode(enA, OUTPUT);
  // pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void loop() {
  if ( myRadio.available())
  {

    myRadio.read( &data, sizeof(data) );

    // Serial.print("X : ");
    // Serial.println(data.joyposX);
    // Serial.print("Y : ");
    //  Serial.println(data.joyposY);



    // X-axis used for forward and backward control
    if (data.joyposX < 470) {
      // Set Motor A backward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if (data.joyposX > 550) {
      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B forward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

    }



    // Y-axis used for left and right control
    //this is left
    else if (data.joyposY < 470) {

      // Set Motor A forward
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Set Motor B backward
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

    }


    else if (data.joyposY > 550) {

      // Set Motor A forward
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Set Motor B backward
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

    }

    else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }

  }

}
