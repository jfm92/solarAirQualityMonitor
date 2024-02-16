#include "SAQMAux.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

Adafruit_BME680 bme;

float hum_weighting = 0.25; // so hum effect is 25% of the total air quality score
float gas_weighting = 0.75; // so gas effect is 75% of the total air quality score

int   humidity_score, gas_score;
float gas_reference = 2500;
float hum_reference = 40;
int   getgasreference_count = 0;
int   gas_lower_limit = 10000;  // Bad air quality limit
int   gas_upper_limit = 300000; // Good air quality limit

static void GetGasReference(){
    int readings = 10;
  for (int i = 1; i <= readings; i++) { // read gas for 10 x 0.150mS = 1.5secs
    gas_reference += bme.readGas();
  }
  gas_reference = gas_reference / readings;
}

static std::string CalculateIAQ(int score) {
  std::string IAQ_text;
  score = (100 - score) * 5;

  if      (score >= 250)                  IAQ_text = "Hazardous";
  else if (score >= 150 && score <= 249 ) IAQ_text = "Unhealthy +";
  else if (score >= 100 && score <= 149 ) IAQ_text = "Unhealthy";
  else if (score >= 50 && score <= 99 ) IAQ_text = "Bad";
  else if (score >=  20 && score <= 49 ) IAQ_text = "Good";
  else if (score >=  00 && score <=  19 ) IAQ_text = "Excellent";

  return IAQ_text;
}

static int GetHumidityScore() {  //Calculate humidity contribution to IAQ index
  float current_humidity = bme.readHumidity();
  if (current_humidity >= 38 && current_humidity <= 42) // Humidity +/-5% around optimum
    humidity_score = 0.25 * 100;
  else
  { // Humidity is sub-optimal
    if (current_humidity < 38)
      humidity_score = 0.25 / hum_reference * current_humidity * 100;
    else
    {
      humidity_score = ((-0.25 / (100 - hum_reference) * current_humidity) + 0.416666) * 100;
    }
  }
  return humidity_score;
}

static int GetGasScore() {
  //Calculate gas contribution to IAQ index
  gas_score = (0.75 / (gas_upper_limit - gas_lower_limit) * gas_reference - (gas_lower_limit * (0.75 / (gas_upper_limit - gas_lower_limit)))) * 100.00;
  if (gas_score > 75) gas_score = 75; // Sometimes gas readings can go outside of expected scale maximum
  if (gas_score <  0) gas_score = 0;  // Sometimes gas readings can go outside of expected scale minimum
  return gas_score;
}

bool BME680Init(){
    bool succeed = false;

    if(bme.begin()){
        bme.setTemperatureOversampling(BME680_OS_8X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_4X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme.setGasHeater(320, 150);

        GetGasReference();

        Serial.println("BME680 Initialization completed.");

        succeed = true;
    }

    return succeed;
}

void BME680Measurements(struct BME680readings *readings){
    if(bme.performReading()){
        readings->temperature = bme.temperature;
        readings->pressure = bme.pressure / 100.0;
        readings->humidity = bme.humidity;

        humidity_score = GetHumidityScore();
        gas_score      = GetGasScore();
        
        float air_quality_score = humidity_score + gas_score;

        if ((getgasreference_count++) % 5 == 0) GetGasReference();
        readings->airQualityLevel = CalculateIAQ(air_quality_score);
    }
}