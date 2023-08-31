void calibratePressureSensor()  {
  pressureConnected = bmp.begin(BMP280_ADDRESS_ALT);

  if (pressureConnected)  {
    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_NONE,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X2,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_NONE,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500    /* Standby time. */
    );

    float total;
    for (int i = 0; i < 50; i++) {
      int tmp = bmp.readPressure();
      total += tmp;
      delay(100);
    }

    averagePressure = total / 50;
  }
  
  digitalWrite(25, HIGH); //LED on for ready
}


void scan_Pressure()  {
  //Actual values peak at 300, 500 if pushing.
  long getReading = abs(bmp.readPressure() - averagePressure - pressureZero);
  getReading = constrain(getReading, 0, pressureSensitivity);

  //currentPressure = (currentPressure * nfilter) + (getReading * filter);
  currentPressure = getReading;
}
