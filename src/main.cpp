#include <Arduino.h>

#include "morse_code.hpp"

MorseCodeWriter morse(GPIO_NUM_22, 100);

void taskMorseCodeWriter(void *parameters)
{
  while (true)
  {
    morse.writeLoop();
    vTaskDelay(100);
  }
}

void setup()
{
  Serial.begin(115200);

  Serial.setTimeout(10000);
  Serial.readString();
  xTaskCreatePinnedToCore(
      taskMorseCodeWriter,   // Function that should be called
      "taskMorseCodeWriter", // Name of the task (for debugging)
      1024,                  // Stack size (bytes)
      NULL,                  // Parameter to pass
      2,                     // Task priority
      NULL,                  // Task handle
      0);
}

void loop()
{
  char line[128];
  Serial.print("Ready!\n");
  int x = Serial.readBytesUntil('\n', line, 127);
  if (x > 0)
  {
    line[x + 1] = '\0';
    Serial.printf("\nSend:!%s\n", line);
    morse.queue(line);
  }
}