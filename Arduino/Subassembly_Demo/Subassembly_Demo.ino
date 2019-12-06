#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

BLEService gyroService("1111");
BLEFloatCharacteristic gyroData("2222", BLERead | BLENotify);

float x, y, z;

void setup() {
  
  BLE.begin();
  
  if (!IMU.begin()) { while(1); }

  BLE.setLocalName("Arduino BLE (Subassembly Demo)");
  
  BLE.setAdvertisedService(gyroService);
  BLE.setAdvertisedServiceUuid(gyroService.uuid());

  gyroService.addCharacteristic(gyroData);

  BLE.addService(gyroService);

  gyroData.writeValue(0.0f);

  BLE.setAdvertisingInterval(40);
  BLE.advertise();
}

void loop() {

  BLEDevice central = BLE.central();

  if (central) {

    while (central.connected()) {

    bool gyroAvailable = IMU.gyroscopeAvailable();

      if (gyroAvailable) {

        IMU.readGyroscope(x, y, z);

        gyroData.writeValue(z);
      }
      delay(1);
    }
  }
  delayMicroseconds(10);
}
