#pragma once
#include <Arduino.h>

class LedPWM
{
public:
  LedPWM(uint8_t pin);

  void init();

  void set_time(uint32_t value);
  void set_duty(uint8_t value);
  void run_led(uint32_t periodMs, uint8_t dutyPercent);
  void start_led();
  int32_t get_time();
  int32_t get_duty();

  void update();

private:
  uint8_t _pin;

  int32_t _setDuty = 0;
  int32_t _setTime = 0;

  int32_t _periodMs = 0;
  int32_t _onTimeMs = 0;

  int32_t _lastToggle = 0;

  int32_t _duty = 0;
  bool _state = false;
  bool _isRunning = false;

  void apply();
};
