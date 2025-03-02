void ledblink(int blinkcount) {
  for (int i = 0; i < blinkcount + 1; i++) {
    digitalWrite(LeftLed, LOW);
    digitalWrite(RightLed, LOW);
    delay(100);
    digitalWrite(LeftLed, HIGH);
    digitalWrite(RightLed, HIGH);
    delay(100);
  }
}

void quit() {
  if (analogRead(button) > 800) {
    Mstop();
    cordinates[0] = 0;
    cordinates[1] = 0;
    dirval = 1002;
    direction = 'D';
    digitalWrite(LeftLed, LOW);
    digitalWrite(RightLed, LOW);
    delay(1200);
    digitalWrite(LeftLed, HIGH);
    digitalWrite(RightLed, HIGH);
    delay(500);
    digitalWrite(LeftLed, LOW);
    digitalWrite(RightLed, LOW);
    while (true) {
      if (analogRead(button) > 800) {
        ledblink(2);
        //timeElapsed = millis();
        break;
      }
    }
  }
}

/*void checkTarget() {
  if (analogRead(QtrSens) < 50 && millis() > timeElapsed+3000) {
    whiteSeen = 1;
  }
}

void isTargetReached() {
  if (whiteSeen == 1) {
    Mstop();
    timeElapsed = millis();
    digitalWrite(LeftLed, LOW);
    while (true) {
      interval = millis()-timeElapsed;
      if (analogRead(button) > 800 || (interval > 4000)) {
        timeElapsed = millis();
        whiteSeen = 0;
        break;
      }
    }
  }
}*/
