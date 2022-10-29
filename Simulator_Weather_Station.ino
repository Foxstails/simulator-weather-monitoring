#include <dht.h>
#include <SD.h>
#include <Wire.h>
#include <MPU6050_light.h>
#define DHT22_PIN 5
#define CS_PIN 4

dht DHT;
//mpu setup
MPU6050 mpu(Wire);
unsigned long timer = 0;
//mode
char datain;
String cek_datain;
int maintenance = 0;
//temperature
int set_max_temp;
int set_min_temp;
//humidity
int set_max_humm;
int set_min_humm;
float temp_min = -40.0;
float temp_max = 80.0;
float humm_val ;
float temp_val ;
//SDcard
int save_data = 0;
int read_data = 0;
int number_data = 0;
File dataFile;
//interval sensor
int set_interval_sensor;
String status_val;
int interval_sensor = 1000;
unsigned long previousMillis = 0;
//stream sensor
int stream_sensor = 0;
int last_val_stream_sensor = 0;

void setup() {
  Serial.begin(115200);
  SD.begin(); // Initializing SD Card
  Wire.begin();
  Serial.println("Simulator Weather Station");
  //mpu
  byte status = mpu.begin();
  //setup mpu
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Wait Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.print("Done!\n");
  Serial.println("try type help or ?");
}

void loop() {
  if (Serial.available() > 0) {
    datain = Serial.read();
    if (datain == '\n') {
      if (cek_datain == "HELP" || cek_datain == "?") {
        Serial.println("TYPE COMMAND LIST ");
        delay(100);
        Serial.println("1.STREAM <value> ON/OFF");
        delay(100);
        Serial.println("2.SETTING <value> ON/OFF ");
        delay(100);
        Serial.println("3.SAVE DATA");
        delay(100);
        Serial.println("4.READ DATA");
        delay(100);
      } else if (cek_datain == "SETTING ON") {
        Serial.print("MODE SETTING \n");
        Serial.println("TYPE COMMAND LIST ");
        delay(100);
        Serial.println("1.SET TEMP RANGE");
        delay(100);
        Serial.println("2.SET INTERVAL");
        delay(100);
        Serial.println("3.STATUS");
        delay(100);
        maintenance = 1;
        stream_sensor = 0;
      } else  if (maintenance == 1) {
        //temp range
        if (cek_datain == "SET TEMP RANGE") {
          Serial.print("Set Max temp:");
          set_max_temp = 1;
        } else if (set_max_temp == 1) {
          temp_max = cek_datain.toFloat();
          Serial.println(temp_max);
          Serial.print("Set Min temp:");
          set_max_temp = 0;
          set_min_temp = 1;
         
        } else if (set_min_temp == 1) {
          temp_min = cek_datain.toFloat();
          Serial.println(temp_min);
          set_min_temp = 0;
           Serial.println("DONE");
          //status temp
        } else if (cek_datain == "STATUS") {
          Serial.println("STATUS");
          Serial.print("Interval(ms):");
          Serial.println(interval_sensor);
          Serial.print("temp max:");
          Serial.println(temp_max);
          Serial.print("temp min:");
          Serial.println(temp_min);
        } else if (cek_datain == "SETTING OFF") {
          Serial.println("EXIT SETTING");
          maintenance = 0;
          stream_sensor = last_val_stream_sensor;
        } else if (cek_datain == "SET INTERVAL") {
          Serial.print("Set interval sensor(ms):");
          set_interval_sensor = 1;
        } else if (set_interval_sensor == 1) {
          interval_sensor = cek_datain.toInt();
          Serial.println(interval_sensor);
          Serial.println("DONE");
          set_interval_sensor = 0;
        }
      } else if (cek_datain == "STREAM ON") {
        Serial.println("STREAM SENSOR ON");
        last_val_stream_sensor = 1;
        stream_sensor = last_val_stream_sensor;
      } else if (cek_datain == "STREAM OFF") {
        Serial.print("STREAM SENSOR OFF");
        last_val_stream_sensor = 0;
        stream_sensor = last_val_stream_sensor;
      } else if (cek_datain == "SAVE DATA") {
        number_data = 0;
        Serial.println("SAVE DATA");
        save_data = 1;
      } else if (cek_datain == "READ DATA") {
        stream_sensor = 0;
        Serial.println("READ DATA: ");
        stream_sensor = last_val_stream_sensor;
        read_data = 1;
      } else {
        Serial.println("try type help or ?");
      }
      cek_datain = "";
      datain = "";
    } else {
      cek_datain = cek_datain + (String)datain;
    }
  }

  if (read_data == 1) {
    save_data = 0;
    stream_sensor = 0;
    // Reading the file
    dataFile = SD.open("data.txt");
    if (dataFile) {
      // Reading the whole file
      while (dataFile.available()) {
        Serial.write(dataFile.read());
      }
      dataFile.close();
    }
    else {
      Serial.println("error opening data.txt");
    }
    read_data = 0;
  }
  // DISPLAY DATA
  if (stream_sensor == 1) {
    unsigned long currentMillis = millis();
    // READ DATA sensor
    mpu.update();
    int read_dht = DHT.read22(DHT22_PIN);
     humm_val = DHT.humidity;
     temp_val = DHT.temperature;
    if ((unsigned long)(currentMillis - previousMillis) >= interval_sensor) {
      if (save_data == 1) {
        Serial.print(number_data);
        Serial.print(".");
        // open SD card file (data.txt)
        dataFile = SD.open("data.txt", FILE_WRITE);
        // Write data to SD card file (data.txt)
        dataFile.print(number_data);
        dataFile.print(".");
        dataFile.print("humm:");
       
        dataFile.print(humm_val);
        dataFile.print("RH% ");
        dataFile.print("Temp:");
        
        dataFile.print(temp_val);
        dataFile.print("*C ");
        dataFile.print("P : ");
        dataFile.print(mpu.getAngleX());
        dataFile.print(" R : ");
        dataFile.print(mpu.getAngleY());
        dataFile.print(" Y: ");
        dataFile.println(mpu.getAngleZ());
        dataFile.print("STAT: ");
        if (temp_min > temp_val || temp_max< temp_val) {
          dataFile.print("DANGER ");
        } else {
          dataFile.print("GOOD");
        }
        dataFile.close();
        number_data++;
      }
      Serial.print("humm:");
      Serial.print(DHT.humidity, 1);
      Serial.print("RH% ");
      Serial.print("Temp:");
      Serial.print(DHT.temperature, 1);
      Serial.print("*C ");
      Serial.print("P : ");
      Serial.print(mpu.getAngleX());
      Serial.print(" R : ");
      Serial.print(mpu.getAngleY());
      Serial.print(" Y : ");
      Serial.println(mpu.getAngleZ());
      Serial.print("STAT: ");
      if (temp_min > temp_val || temp_max< temp_val) {
        Serial.println("DANGER ");
      } else {
        Serial.println("GOOD");
      }
      previousMillis = millis();
    }
  }
}
