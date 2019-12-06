#include <Arduino_LSM9DS1.h>

#define MAX_COUNT 500

int count = 0;
bool done = false;

float accelDataX[MAX_COUNT];
float accelDataY[MAX_COUNT];
float gyroData[MAX_COUNT];

void setup() {

  Serial.begin(9600);

  while(!Serial);

  if (!IMU.begin()) {
    
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void printArray(float data[500]) {

  Serial.print("[");

  for (int i = 0; i < 500; i ++) {
    
    Serial.print(String(data[i]));

    if (i != 499) {
      Serial.print(",");
    }
  }
  Serial.println("]");
}

void loop() {

  if (done) {
    return;
  }

  if (count >= MAX_COUNT) {

    done = true;

    printArray(accelDataX);
    printArray(accelDataY);
    printArray(gyroData);
  }

  float x, y, z;

  bool accelAvailable = IMU.accelerationAvailable();

  if (accelAvailable) {

    IMU.readAcceleration(x, y, z);

    accelDataX[count] = x;
    accelDataY[count] = y;
  }

  bool gyroAvailable = IMU.gyroscopeAvailable();

  if (gyroAvailable) {

    IMU.readGyroscope(x, y, z);

    gyroData[count] = z;
  }

  if (gyroAvailable && accelAvailable) {
    count ++;
  }
  
  delay(2);
}
