void straightL(int lenght) {
  analogWrite(R_Mpwm, Rspeed);
  analogWrite(L_Mpwm, Lspeed);
  digitalWrite(L_Mdir, LOW);
  digitalWrite(R_Mdir, HIGH);
  Lcounter = 0;
  Rcounter = 0;
  while (true) {
    if (analogRead(RSens) > 150 && analogRead(LSens) > 150) {
      dif = analogRead(RSens) - analogRead(LSens);
      analogWrite(R_Mpwm, Rspeed + (dif / 20));
      analogWrite(L_Mpwm, Lspeed - (dif / 20));
    } else if (analogRead(RSens) > 150) {
      analogWrite(R_Mpwm, Rspeed + (analogRead(RSens) - 350) / 10);
      analogWrite(L_Mpwm, Lspeed);
    } else if (analogRead(LSens) > 150)  //150
    {
      analogWrite(L_Mpwm, Lspeed + (analogRead(LSens) - 350) / 10);
      analogWrite(R_Mpwm, Rspeed);
    } else {
      analogWrite(L_Mpwm, Lspeed);
      analogWrite(R_Mpwm, Rspeed);
    }
    for (int i = 0; i < 100; i++) {
      val();
    }
    if (Lcounter > lenght || Rcounter > lenght) {
      Mstop();
      break;
    }
  }
}

void straight() {
  //l = 0;
  //r = 0;
  a = 0;
  isCalibratedRemove = 0;
  isCalibratedAdd = 0;
  if (analogRead(LSens) > sensor) {
    Lfull1 = 1;
  } else {
    Lfull1 = 0;
  }
  if (analogRead(RSens) > sensor) {
    Rfull1 = 1;
  } else {
    Rfull1 = 0;
  }
  while (true) {
    digitalWrite(L_Mdir, LOW);
    digitalWrite(R_Mdir, HIGH);
    for (int i = 0; i < 100; i++) {
      valSt();
    }
    if (analogRead(RSens) > sensor && analogRead(LSens) > sensor) {  //ikiside
      dif = (analogRead(RSens)) - analogRead(LSens);
      analogWrite(R_Mpwm, Rspeed + (dif / 20));
      analogWrite(L_Mpwm, Lspeed - (dif / 20));
    } else if (analogRead(RSens) > sensor) {
      if (analogRead(RSens) > targetL) {
        analogWrite(R_Mpwm, Rspeed + (analogRead(RSens) - targetL) / 30);  //350 bölü 10 tek sağ
      } else {
        analogWrite(R_Mpwm, Rspeed + (analogRead(RSens) - targetL) / 15);  //350 bölü 10 tek sağ
      }
      analogWrite(L_Mpwm, Lspeed);
    } else if (analogRead(LSens) > sensor)  //150
    {
      if (analogRead(LSens) > targetL) {
        analogWrite(L_Mpwm, Lspeed + (analogRead(LSens) - targetL) / 30);  //350 bölü 10 tek sol
      } else {
        analogWrite(L_Mpwm, Lspeed + (analogRead(LSens) - targetL) / 15);  //350 bölü 10 tek sol
      }
      analogWrite(R_Mpwm, Rspeed);
    } else {
      analogWrite(L_Mpwm, Lspeed);
      analogWrite(R_Mpwm, Rspeed);
    }
    locate();
    //checkTarget();
    if (a == 1) {
      Mstop();
      digitalWrite(LeftLed, LOW);
      digitalWrite(RightLed, LOW);
      delay(100);
      digitalWrite(LeftLed, HIGH);
      digitalWrite(RightLed, HIGH);
      break;
    }
  }
}
void Mstop() {
  analogWrite(L_Mpwm, 0);
  analogWrite(R_Mpwm, 0);
}