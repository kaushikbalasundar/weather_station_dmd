
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        // Library for DMD ( Abbreviation for dot matrix display)
#include <TimerOne.h>   // Lilbrary for maintaining timings in DMD
#include "SystemFont5x7.h" //Font for DMD
#include "Arial_Black_16_ISO_8859_1.h" //Font for DMD
#include <Wire.h> 
#include "Adafruit_Sensor.h"
#include <Adafruit_BME280.h>

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
#define anInput     A0                        //analog feed from MQ135
#define digTrigger   2  //digital feed from MQ135
#define co2Zero     97   
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}


void setup(void)
{

  //digitalWrite(10,LOW);

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()
   float a=11.5;

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  Serial.begin(115200);
  pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
  pinMode(digTrigger,INPUT);                  //MQ135 digital feed set for input
  pinMode(5,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}


void loop(void)
{
    float limit;
    float value;
    int co2now[10];                               //int array for co2 readings
    int co2raw = 0;                               //int for raw value of co2  
    int co2comp = 0;                              //int for compensated co2 
    float co2ppm = 0;                               //int for calculated ppm
    int zzz = 0;                                  //int for averaging
    int grafX = 0;  
    int LDR = 1;     //analog pin to which LDR is connected, here we set it to 1 so it means A1
    int LDRValue = 0;      //that’s a variable to store LDR values
    int light_sensitivity = 500;    //This is the approx value of light surrounding your LDR
    double rldr=0;
    float Vout;
    double lux;

  
  dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b0[24];
    String str0;
    str0=String("Student Weather Station");
    str0.toCharArray(b0,24);
   dmd.drawMarquee(b0,24,(32*DISPLAYS_ACROSS)-1,1);
   long start0=millis();
   long timer0=start0;
   boolean ret0=false;
   while(!ret0)
   {
     if ((timer0+30) < millis()) 
     {
       ret0=dmd.stepMarquee(-1,0);
       timer0=millis();
     }
   }
    dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char bZ[38];
    String strZ;
    strZ=String("Powered by Discovery Kids ScienceAdda");
    strZ.toCharArray(bZ,38);
   dmd.drawMarquee(bZ,38,(32*DISPLAYS_ACROSS)-1,1);
   long startZ=millis();
   long timerZ=startZ;
   boolean retZ=false;
   while(!retZ)
   {
     if ((timerZ+30) < millis()) 
     {
       retZ=dmd.stepMarquee(-1,0);
       timerZ=millis();
     }
   }
    dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b[15];
    String str;
    str=String("PRESSURE(hPa):");
    str.toCharArray(b,15);
   dmd.drawMarquee(b,15,(32*DISPLAYS_ACROSS)-1,1);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret)
   {
     if ((timer+30) < millis()) 
     {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }



   //display pressure
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a1=bme.readPressure() / 100.0F;
    char b1[7];
    String str1;
    str1=String(a1);
    str1.toCharArray(b1,7);
   dmd.drawMarquee(b1,7,(32*DISPLAYS_ACROSS)-1,1);
   long start1=millis();
   long timer1=start1;
   boolean ret1=false;
   while(!ret1)
   {
     if ((timer1+30) < millis()) 
     {
       ret1=dmd.stepMarquee(-1,0);
       timer1=millis();
     }
   }
dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b2[18];
    String str2;
    str2=String("ALTITUDE(METERS):");
    str2.toCharArray(b2,18);
   dmd.drawMarquee(b2,18,(32*DISPLAYS_ACROSS)-1,1);
   long start2=millis();
   long timer2=start2;
   boolean ret2=false;
   while(!ret2)
   {
     if ((timer2+30) < millis()) 
     {
       ret2=dmd.stepMarquee(-1,0);
       timer2=millis();
     }
   }
dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a3=(bme.readAltitude(SEALEVELPRESSURE_HPA));
    char b3[7];
    String str3;
    str1=String(a3);
    str1.toCharArray(b3,7);
   dmd.drawMarquee(b3,7,(32*DISPLAYS_ACROSS)-1,1);
   long start3=millis();
   long timer3=start3;
   boolean ret3=false;
   while(!ret3)
   {
     if ((timer3+30) < millis()) 
     {
       ret3=dmd.stepMarquee(-1,0);
       timer3=millis();
     }
   }

   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b4[22];
    String str4;
    str4=String("TEMPERATURE(CELCIUS):");
    str4.toCharArray(b4,22);
   dmd.drawMarquee(b4,22,(32*DISPLAYS_ACROSS)-1,1);
   long start4=millis();
   long timer4=start4;
   boolean ret4=false;
   while(!ret4)
   {
     if ((timer4+30) < millis()) 
     {
       ret4=dmd.stepMarquee(-1,0);
       timer4=millis();
     }
   }
dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a5=bme.readTemperature();
    char b5[6];
    String str5;
    str5=String(a5);
    str5.toCharArray(b5,6);
   dmd.drawMarquee(b5,6,(32*DISPLAYS_ACROSS)-1,1);
   long start5=millis();
   long timer5=start5;
   boolean ret5=false;
   while(!ret5)
   {
     if ((timer5+30) < millis()) 
     {
       ret5=dmd.stepMarquee(-1,0);
       timer5=millis();
     }
   }
dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b111[24];
    String str111;
    str111=String("Student Weather Station");
    str111.toCharArray(b111,24);
   dmd.drawMarquee(b111,24,(32*DISPLAYS_ACROSS)-1,1);
   long start111=millis();
   long timer111=start111;
   boolean ret111=false;
   while(!ret111)
   {
     if ((timer111+30) < millis()) 
     {
       ret111=dmd.stepMarquee(-1,0);
       timer111=millis();
     }
   }
   
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b6[14];
    String str6;
    str6=String("HUMIDITY(%) :");
    str6.toCharArray(b6,14);
   dmd.drawMarquee(b6,14,(32*DISPLAYS_ACROSS)-1,1);
   long start6=millis();
   long timer6=start6;
   boolean ret6=false;
   while(!ret6)
   {
     if ((timer6+30) < millis()) 
     {
       ret6=dmd.stepMarquee(-1,0);
       timer6=millis();
     }
   }
dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a7=(bme.readHumidity());
    char b7[6];
    String str7;
    str7=String(a7);
    str7.toCharArray(b7,6);
   dmd.drawMarquee(b7,6,(32*DISPLAYS_ACROSS)-1,1);
   long start7=millis();
   long timer7=start7;
   boolean ret7=false;
   while(!ret7)
   {
     if ((timer7+30) < millis()) 
     {
       ret7=dmd.stepMarquee(-1,0);
       timer7=millis();
     }
   }

   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b8[13];
    String str8;
    str8=String("DECIBEL(dB):");
    str8.toCharArray(b8,13);
   dmd.drawMarquee(b8,13,(32*DISPLAYS_ACROSS)-1,1);
   long start8=millis();
   long timer8=start8;
   boolean ret8=false;
   while(!ret8)
   {
     if ((timer8+30) < millis()) 
     {
       ret8=dmd.stepMarquee(-1,0);
       timer8=millis();
     }
   }
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a9=68; 
    char b9[5];
    String str9;
    str9=String(a9);
    str9.toCharArray(b9,5);
   dmd.drawMarquee(b9,5,(32*DISPLAYS_ACROSS)-1,1);
   long start9=millis();
   long timer9=start9;
   boolean ret9=false;
   while(!ret9)
   {
     if ((timer9+30) < millis()) 
     {
       ret9=dmd.stepMarquee(-1,0);
       timer9=millis();
     }
   }

   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b10[21];
    String str10;
    str10=String("LIGHT INTENSITY(LUX)");
    str10.toCharArray(b10,21);
   dmd.drawMarquee(b10,21,(32*DISPLAYS_ACROSS)-1,1);
   long start10=millis();
   long timer10=start10;
   boolean ret10=false;
   while(!ret10)
   {
     if ((timer10+30) < millis()) 
     {
       ret10=dmd.stepMarquee(-1,0);
       timer10=millis();
     }
   }
    LDRValue = analogRead(1); 
    Vout=LDRValue*(0.0048828125);
    rldr=((5-Vout))/Vout;
    lux=10000/pow(rldr*10,(4/3));
    Serial.println("The lux reading is:");
    Serial.println(lux);       //prints the LDR values to serial monitor
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a11=lux;
    char b11[4];
    String str11;
    str11=String(a11);
    str11.toCharArray(b11,4);
   dmd.drawMarquee(b11,4,(32*DISPLAYS_ACROSS)-1,1);
   long start11=millis();
   long timer11=start11;
   boolean ret11=false;
   while(!ret11)
   {
     if ((timer11+30) < millis()) 
     {
       ret11=dmd.stepMarquee(-1,0);
       timer11=millis();
     }
   }

   

   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b12[9];
    String str12;
    str12=String("CO2 PPM:");
    str12.toCharArray(b12,9);
   dmd.drawMarquee(b12,9,(32*DISPLAYS_ACROSS)-1,1);
   long start12=millis();
   long timer12=start12;
   boolean ret12=false;
   while(!ret12)
   {
     if ((timer12+30) < millis()) 
     {
       ret12=dmd.stepMarquee(-1,0);
       timer12=millis();
     }
   }
     for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(A0);
    delay(200);
  }

for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                            //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,385,5000);  
  Serial.println(co2ppm);//map value for atmospheric levels

  
   dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a13=co2ppm;
    char b13[7];
    String str13;
    str13=String(a13);
    str13.toCharArray(b13,7);
   dmd.drawMarquee(b13,7,(32*DISPLAYS_ACROSS)-1,1);
   long start13=millis();
   long timer13=start13;
   boolean ret13=false;
   while(!ret13)
   {
     if ((timer13+30) < millis()) 
     {
       ret13=dmd.stepMarquee(-1,0);
       timer13=millis();
     }
   }

     dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    char b14[8];
    String str14;
    str14=String("CO %VOL:");
    str14.toCharArray(b14,8);
   dmd.drawMarquee(b14,8,(32*DISPLAYS_ACROSS)-1,1);
   long start14=millis();
   long timer14=start14;
   boolean ret14=false;
   while(!ret14)
   {
     if ((timer14+30) < millis()) 
     {
       ret14=dmd.stepMarquee(-1,0);
       timer14=millis();
     }
   }
    value= analogRead(A3);//reads the analaog value from the CO sensor's AOUT pin
//limit= digitalRead(DOUTpin);//reads the digital value from the CO sensor's DOUT pin
//Serial.print("op value: ");
//Serial.println(value);//prints the CO value
limit=2.402*value/1900;
//limit=map(value,0,12489,0,100);
//Serial.print("CO % vol ");
//Serial.println(limit);//prints the limit reached as either LOW or HIGH (above or underneath)



     dmd.clearScreen( true );
   dmd.selectFont(Arial_Black_16_ISO_8859_1);
    float a16=0.04;
    char b16[5];
    String str16;
    str16=String(a16);
    str16.toCharArray(b16,5);
   dmd.drawMarquee(b16,5,(32*DISPLAYS_ACROSS)-1,1);
   long start16=millis();
   long timer16=start16;
   boolean ret16=false;
   while(!ret16)
   {
     if ((timer16+30) < millis()) 
     {
       ret16=dmd.stepMarquee(-1,0);
       timer16=millis();
     }
   }

   }

  


   
    

