#include <Wire.h> //I2C Arduino Library
#define addr 0x0D //I2C Address for The HMC5883
#define num 20
int sensorValues_x[num] = {0, };
int sensorValues_y[num] = {0, };
int sensorValues_z[num] = {0, };
int x, y, z, add=0, i, x1;

void filter();

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Wire.beginTransmission(addr); //start talking
  Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x01); // Set the Register
  Wire.endTransmission();
  Wire.beginTransmission(addr); //start talking
  Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x1D); // Set the Register
  Wire.endTransmission();
}

void loop() {

  Wire.beginTransmission(addr);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();

  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(addr, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //MSB  x
    x |= Wire.read() << 8; //LSB  x
    z = Wire.read(); //MSB  z
    z |= Wire.read() << 8; //LSB z
    y = Wire.read(); //MSB y
    y |= Wire.read() << 8; //LSB y
  }
  x1=x;
  filter();
  /*
  i++;

  if (i>=20 && i<=120)
  {
    if (x<-50)
      add+=-x-50;
    else
      add+=50+x;
     
    Serial.print(i);
    Serial.print(' ');
    Serial.print(add);
    Serial.print(' ');
    Serial.println(x);
    delay(100);
  }
  */
  Serial.print(x1);
  Serial.print(" ");
  Serial.println(x);
  delay(100);
}

void filter()
{
  for (int i = 0; i < num - 1; i++)
  {
    sensorValues_x[i] = sensorValues_x[i + 1];
    sensorValues_y[i] = sensorValues_y[i + 1];
    sensorValues_z[i] = sensorValues_z[i + 1];
  }

  sensorValues_x[num - 1] = x;
  sensorValues_y[num - 1] = y;
  sensorValues_z[num - 1] = z;
  float filter_x, filter_y, filter_z;
  filter_x=0;
  filter_y=0;
  filter_z=0;
  
  for (int i = 0; i < num; i++)
  {
    filter_x += sensorValues_x[i];
    filter_y += sensorValues_y[i];
    filter_z += sensorValues_z[i];
  }

  filter_x /= num;
  filter_y /= num;
  filter_z /= num;

  x = (int)filter_x;
  y = (int)filter_y;
  z = (int)filter_z;
}
