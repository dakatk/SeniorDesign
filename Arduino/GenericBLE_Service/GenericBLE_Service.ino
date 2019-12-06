#include <ArduinoBLE.h>

BLEService sineService("1111");
BLEFloatCharacteristic sineData("2222", BLERead | BLENotify);
BLEIntCharacteristic timeData("3333", BLERead | BLENotify);

void setup() {
  
  BLE.begin();

  BLE.setLocalName("Arduino BLE");
  
  BLE.setAdvertisedService(sineService);
  BLE.setAdvertisedServiceUuid(sineService.uuid());

  sineService.addCharacteristic(sineData);
  sineService.addCharacteristic(timeData);

  BLE.addService(sineService);

  sineData.writeValue(0.0f);
  timeData.writeValue(0);

  BLE.setAdvertisingInterval(50);
  BLE.advertise();
}

void loop() {

  BLEDevice central = BLE.central();

  if (central) {

    float t = 0.0f;
    int n = 0;

    while (central.connected()) {

      float newValue = sin(t);

      sineData.writeValue(newValue);
      timeData.writeValue(n);

      n ++;
      t += 0.0001f;

      if (t >= 2.0f * PI) {
        t = 0.0f;
      }

      delay(1);
    }
  }
  delayMicroseconds(10);
}
