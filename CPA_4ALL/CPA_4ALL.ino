#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
JOYSTICK_TYPE_GAMEPAD,
5, 0,
true, true, false,
true, true, false,
true, true,
false, false, false);

const int botao1 = 2;
const int botao2 = 3;
const int botao3 = 4;
const int botao4 = 5;
const int botao5 = 1;

const int joystickUp = 6;
const int joystickDown = 7;
const int joystickRight = 8;
const int joystickLeft = 9;

const int joystickAnalogX = A0;
const int joystickAnalogY = A1;

const int scrollLeft = A2;
const int scrollRight = A3;

const int CENTRO = 512;
const int DEADZONE = 100;

int aplicarDeadzone(int valor) {
  if (valor > CENTRO - DEADZONE && valor < CENTRO + DEADZONE) {
    return CENTRO;
  }

  if (valor <= CENTRO - DEADZONE) {
    return map(valor, 0, CENTRO - DEADZONE, 0, CENTRO);
  } else {
    return map(valor, CENTRO + DEADZONE, 1023, CENTRO, 1023);
  }
}

void setup() {
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(botao3, INPUT_PULLUP);
  pinMode(botao4, INPUT_PULLUP);
  pinMode(botao5, INPUT_PULLUP);

  pinMode(joystickUp, INPUT_PULLUP);
  pinMode(joystickDown, INPUT_PULLUP);
  pinMode(joystickRight, INPUT_PULLUP);
  pinMode(joystickLeft, INPUT_PULLUP);

  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
  Joystick.setRudderRange(0, 1023);
  Joystick.setThrottleRange(0, 1023);

  Joystick.begin(false);
  delay(1000);
}

void loop() {
  int AxisX = 512;
  int AxisY = 512;

  int currentUp = digitalRead(joystickUp);
  int currentDown = digitalRead(joystickDown);
  int currentRight = digitalRead(joystickRight);
  int currentLeft = digitalRead(joystickLeft);

  if (currentLeft == LOW) {
    AxisX = 0;
  } else if (currentRight == LOW) {
    AxisX = 1023;
  }

  if (currentUp == LOW) {
    AxisY = 0;
  } else if (currentDown == LOW) {
    AxisY = 1023;
  }

  Joystick.setXAxis(AxisX);
  Joystick.setYAxis(AxisY);

  Joystick.setRxAxis(analogRead(joystickAnalogX));
  Joystick.setRyAxis(analogRead(joystickAnalogY));

  int b1 = digitalRead(botao1);
  int b2 = digitalRead(botao2);
  int b3 = digitalRead(botao3);
  int b4 = digitalRead(botao4);
  int b5 = digitalRead(botao5);

  Joystick.setButton(0, !b1);
  Joystick.setButton(1, !b2);
  Joystick.setButton(2, !b3);
  Joystick.setButton(3, !b4);
  Joystick.setButton(4, !b5);

  int valEsq = aplicarDeadzone(analogRead(scrollLeft));
  int valDir = aplicarDeadzone(analogRead(scrollRight));

  Joystick.setRudder(valEsq);
  Joystick.setThrottle(valDir);

  Joystick.sendState();
  delay(10);
}