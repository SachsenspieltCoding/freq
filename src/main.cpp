#include <Arduino.h>

float freq, freqsum, freqavg = 0;
int y1, y2, cycle, x0count = 0;

int threshold = 12;
int interval = 1000; // How long a measurement take in ms
int resolution = 50; // The resolution of measurement in µs

int time1, time2 = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  cycle += 1;
  time1 = millis();
  x0count = 0;

  do
  {
    y2 = analogRead(A0);

    if ((y1 - threshold) * (y2 - threshold) < 0)
    {
      x0count += 1;
    }

    y1 = y2;
    time2 = millis() - time1;

    delayMicroseconds(resolution);
  } while (time2 < interval);

  freq = x0count / 2 / (interval / 1000.0);
  freqsum += freq;
  freqavg = freqsum / cycle;

  Serial.println("Cycle: " + String(cycle) + " Frequency: " + String(freqavg) + "Hz");
}