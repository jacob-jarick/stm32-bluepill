/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
  SD card attached to SPI 2 bus as follows:
  MOSI - PB14
  MISO - PB15
  CLK - PB13
  CS - PB12
  VCC - 5V
  GND - GND

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald
  modified 23/06/2018
  by Jacob Jarick

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>

File root;
File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  for (byte i = 0; i < 10; i++)
  {
    Serial.print(i);
    Serial.print('.');
    delay(1000); // wait for win10 to init usb serial
  }
  Serial.println();

  // -----------------------------------------------------------------
  // init SD Card
  
  Serial.print("\nInitializing SD card...");
  SPI.setModule(2);  // SPI port 2 (5v port)
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  if (!SD.begin(PB12)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // -----------------------------------------------------------------

  printDirectory();
  
  String filename = csv_name(1);

  myFile = SD.open(filename, FILE_WRITE);
  String text = String("Hello World");
  myFile.println(text);
  Serial.println(text);
  myFile.close();

  

  Serial.println("done!");
}

String csv_name(bool mode)
{
  int count = count_dir() + 1;
  Serial.print("File Count: ");
  Serial.println(count);

  char fname[7];
  sprintf(fname, "%07d", count);

  String f;
  if (mode)
  {
    f = String(String(fname) + "C.CSV");
  }
  else
  {
    f = String(String(fname) + "D.CSV");
  }

  Serial.print("File name: ");
  Serial.println(f);

  return f;
}

void loop() {
  // nothing happens after setup finishes.
}

int count_dir()
{
  File dir = SD.open("/");
  int c = 0;
  while (true)
  {
    File entry =  dir.openNextFile();
    if (! entry)
      break;  // no more files

    c++;
  }
  dir.close();
  return c;
}

void printDirectory() {

    File dir = SD.open("/");

  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      //printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
  dir.close();
}


