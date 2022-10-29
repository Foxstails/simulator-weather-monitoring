# Technical Test Embedded Engineer eFishery

## Simulator Weather Station 

Simulator Weather Station dapat memonitoring suhu dan kelembaban udara sekitar;
Di lengkapi dengan sensor IMU yang dapat melihat pergerakkan orientasi sensor;
Dapat di Aplikasikan sebagai alat memonitoring kualitas udara sekitar contoh muatan balon atmosfer yang biasa di gunakan BRIN;
> Video : (on Progress);
### FITUR

- Terdapat Pilihan Type Command untuk memudahkan user untuk mengoperasikannya
- Bisa diatur interval dan range temperature

### Hardware
Arduino NANO , MPU6050 , SD CARD Modulle dan DHT22;

### Simulator
Wokwi; 
link https://wokwi.com/projects/346831652294492756;

### SD Card - Arduino Nano

| SDCARD Module |Arduino Nano| 
| ------------- | ---------- |
| VCC           | 5V         |                                               
| GND           | GND        |                                               
| MISO          | D12        |                           
| MOSI          | D11        |                           
| SCK           | D13        |
| CS            | D10        |


### MPU 6050 - Arduino Nano

| MPU 6050 | Arduino Nano |
| ------   | -------      |
| SCL      | A5           |
| SDA      | A6           |
| VCC      | 5V           |
| GND      | GND          |

### DHT22

| DHT22  | Arduino Nano|
| ------ | -------     |
| VCC    | 5V          |
| GND    | GND         |
| SDA    | D5          |

### External Library
- MPU6050_light : https://github.com/rfetick/MPU6050_light;
- DHTlib : https://github.com/RobTillaart/DHTlib;

### Catatan 
>1.Dikarenakan keterbatasan dalam pengadaan hardware realnya jadi hanya bisa menggunakan simulator pada web wokwi saja;
>2.Beberapa fitur hanya sederhana saja dikarenakan keterbatasan simulasi pada wokwi;

> email : dimastrilaksonoip@gmail.com;

