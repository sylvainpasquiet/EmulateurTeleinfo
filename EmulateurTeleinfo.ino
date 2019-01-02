#include <SoftwareSerial.h>

SoftwareSerial cptSerial(4, 3,true);

void setup() 
{
  //Serial.begin(1200,SERIAL_8N1);
  //Serial.begin(1200,SERIAL_7E1);
  cptSerial.begin(1200);     // opens serial port, sets data rate to 1200 bps
}

char trame[100];

uint8_t checksum(char* trame)
{
  uint8_t myCS = 32;
  for (uint8_t i=0;i<strlen(trame);i++) myCS +=(int) (trame[i]);
  return((myCS & 0x3F) + 0x20);
}

unsigned long HC=0;
unsigned char IINST=0;
unsigned short PAPP=0;

void loop()
{
  uint8_t myCS;
  cptSerial.write(0x02);
  
  strcpy(trame,"ADCO 000000000001 \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  strcpy(trame,"OPTARIF HC.. \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  strcpy(trame,"ISOUSC 45 \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  HC++;
  sprintf(trame, "HCHC %09d \0", HC);
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));
  
  strcpy(trame,"HCHP 003191256 \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));
  
  strcpy(trame,"PTEC HP.. \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  IINST++;
  sprintf(trame, "IINST %03d \0", IINST);
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  strcpy(trame,"IMAX 060 \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));
  
  PAPP++;
  sprintf(trame, "PAPP %05d \0", PAPP);
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));
  
  strcpy(trame,"HHPHC A \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));

  strcpy(trame,"MOTDETAT 000000 \0");
  cptSerial.print(trame);
  cptSerial.println((char) checksum(trame));
  
  cptSerial.write(0x03);
}

