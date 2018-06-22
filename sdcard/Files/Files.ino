/*
  SD card basic file example

  note: do not use LTO (Link Time Optimization) with this sketch.
  ref: http://www.stm32duino.com/viewtopic.php?t=2092

 This example shows how to create and destroy an SD card file
 The circuit:
SD card attached to SPI 2 bus as follows:
 ** MOSI - PB14
 ** MISO - PB15
 ** CLK - PB13
 ** CS - PB12
 ** VCC - 5V
 ** GND - GND

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 22/06/2018
by Jacob Jarick

 This example code is in the public domain.

 */
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  for(byte i = 0; i< 10; i++)
  {
    Serial.print(i);
    Serial.print('.');
    delay(1000); // wait for win10 to init usb serial
  }
  Serial.println();

  Serial.print("\nInitializing SD card...");
  SPI.setModule (2);  // SPI port 2 (5v port)
  SPI.setClockDivider(SPI_CLOCK_DIV2);  

  Serial.print("Initializing SD card...");

  if (!SD.begin(PB12)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating example.txt...");
  myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }

  // delete the file:
  Serial.println("Removing example.txt...");
  SD.remove("example.txt");

  if (SD.exists("example.txt")) {
    Serial.println("example.txt exists.");
  } else {
    Serial.println("example.txt doesn't exist.");
  }
}

void loop() {
  // nothing happens after setup finishes.
}



