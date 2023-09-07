void calibratePressureSensor()  {
  pressureConnected = (bmp1.begin(BMP280_ADDRESS_ALT) && bmp2.begin(BMP280_ADDRESS));

  if (pressureConnected)  {
    //Bellows
    bmp1.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_NONE,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X1,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_OFF,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_1    /* Standby time. */
    );
    
    //Atmosphere
    bmp2.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_NONE,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500    /* Standby time. */
    );

    float total;
    for (int i = 0; i < 50; i++) {
      float tmp = abs(bmp1.readPressure() - bmp2.readPressure());
      total += tmp;
      delay(50);
    }

    pressureDiff = total / 50;
  }
  
  digitalWrite(25, HIGH); //LED on for ready
}


void scan_Pressure()  {
  //Actual values peak at 300, 500 if pushing.
  float getReading = constrain(abs(bmp1.readPressure() - bmp2.readPressure() - pressureDiff) - pressureZero, 0, 500); //Arbitrary max value

  currentPressure = (currentPressure * nfilter) + (getReading * filter);
}
