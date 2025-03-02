void locate() {          //öne duvar gelirse sensöre göre versiyon              //çalışıyo
  if ((Llocator + Rlocator) / 2 > squareL && analogRead(MSens) < 110 || analogRead(MSens)>235) {  //cordinates[0]->x     cordinates[1]->y || analogRead(MSens) > 300
    switch (direction) {
      case 'U': cordinates[1]--; break;
      case 'R': cordinates[0]++; break;
      case 'D': cordinates[1]++; break;
      case 'L': cordinates[0]--; break;
    }
    a = 1;
    Llocator = 0;
    Rlocator = 0;
  }
}





/*void locate() {          //çalışıyo (iki motor ortalama versiyon)
  if ((Llocator + Rlocator) / 2 > squareL || analogRead(MSens) > 300) {  //cordinates[0]->x     cordinates[1]->y || analogRead(MSens) > 300
    switch (direction) {
      case 'U': cordinates[1]--; break;
      case 'R': cordinates[0]++; break;
      case 'D': cordinates[1]++; break;
      case 'L': cordinates[0]--; break;
    }
    a = 1;
    Llocator = 0;
    Rlocator = 0;
  }
}*/






/*void locate() {                  //çalışıyo gibimtrak (iki motor ayrı versiyon)
  if (Llocator > squareL) {  //cordinates[0]->x     cordinates[1]->y
    l = 1;
    analogWrite(L_Mpwm, 0);
  }
  if (Rlocator > squareR) {  //cordinates[0]->x     cordinates[1]->y
    r = 1;
    analogWrite(R_Mpwm, 0);
  }
  if (l == 1 && r == 1 || analogRead(MSens) > 300) { //
    a = 1;
    Llocator = 0;
    Rlocator = 0;
    switch (direction) {
      case 'U': cordinates[1]--; break;
      case 'R': cordinates[0]++; break;
      case 'D': cordinates[1]++; break;
      case 'L': cordinates[0]--; break;
    }
  }
}*/


void valSt() {  //KONTROL EDİLDİ valSt tek kalibreli versiyon
  if (analogRead(RSens) > sensor && Rfull1 == 0 && isCalibratedAdd == 0 && (Llocator + Rlocator) / 2 < 550) {
    Rfull1 = 1;
    isCalibratedAdd = 1;
    Rlocator = isWall;
    Llocator = isWall;
  }
  if (analogRead(RSens) < sensor && Rfull1 == 1 && isCalibratedRemove == 0 && (Llocator + Rlocator) / 2 < 550) {
    Rfull1 = 0;
    isCalibratedRemove = 1;
    Rlocator = notWall;
    Llocator = notWall;
  }
  if (analogRead(LSens) > sensor && Lfull1 == 0 && isCalibratedAdd == 0 && (Llocator + Rlocator) / 2 < 550) {
    Lfull1 = 1;
    isCalibratedAdd = 1;
    Rlocator = isWall;
    Llocator = isWall;
  }
  if (analogRead(LSens) < sensor && Lfull1 == 1 && isCalibratedRemove == 0 && (Llocator + Rlocator) / 2 < 550) {
    Lfull1 = 0;
    isCalibratedRemove = 1;
    Rlocator = notWall;
    Llocator = notWall;
  }
  if (left_pre != digitalRead(left_en)) {
    Llocator++;
    left_pre = digitalRead(left_en);
  }
  if (right_pre != digitalRead(right_en)) {
    Rlocator++;
    right_pre = digitalRead(right_en);
  }
}





/* 


void valSt() {  //KONTROL EDİLDİ valSt çok kalibreli versiyon
  if (analogRead(RSens) > sensor && Rfull1 == 0) {
    Rfull1 = 1;
    Rlocator = isWall;
    Llocator = isWall;
  }
  if (analogRead(RSens) < sensor && Rfull1 == 1) {
    Rfull1 = 0;
    Rlocator = notWall;
    Llocator = notWall;
  }
  if (analogRead(LSens) > sensor && Lfull1 == 0) {
    Lfull1 = 1;
    Rlocator = isWall;
    Llocator = isWall;
  }
  if (analogRead(LSens) < sensor && Lfull1 == 1) {
    Lfull1 = 0;
    Rlocator = notWall;
    Llocator = notWall;
  }
  if (left_pre != digitalRead(left_en)) {
    Llocator++;
    left_pre = digitalRead(left_en);
  }
  if (right_pre != digitalRead(right_en)) {
    Rlocator++;
    right_pre = digitalRead(right_en);
  }

}






*/











void saveWalls() {  //cordinates[0]->x     cordinates[1]->y    BURADA DUVAR YOKSA BİTİ KALDIRMAYI DA EKLE
                    //if ((Llocater + Rlocater) / 2 < (notWall-100))   //bulunduğu kare
  if (direction == 'U') {
    if (analogRead(RSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 1);
    } else {
      removeWall(cordinates[0], cordinates[1], 1);
    }
    if (analogRead(LSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 2);
    } else {
      removeWall(cordinates[0], cordinates[1], 2);
    }
    if (analogRead(MSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 0);
    } else {
      removeWall(cordinates[0], cordinates[1], 0);
    }
  } else if (direction == 'R') {  //SAĞ
    if (analogRead(RSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 3);
    } else {
      removeWall(cordinates[0], cordinates[1], 3);
    }
    if (analogRead(LSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 0);
    } else {
      removeWall(cordinates[0], cordinates[1], 0);
    }
    if (analogRead(MSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 1);
    } else {
      removeWall(cordinates[0], cordinates[1], 1);
    }
  } else if (direction == 'D') {
    if (analogRead(RSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 2);
    } else {
      removeWall(cordinates[0], cordinates[1], 2);
    }
    if (analogRead(LSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 1);
    } else {
      removeWall(cordinates[0], cordinates[1], 1);
    }
    if (analogRead(MSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 3);
    } else {
      removeWall(cordinates[0], cordinates[1], 3);
    }
  } else if (direction == 'L') {
    if (analogRead(RSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 0);
    } else {
      removeWall(cordinates[0], cordinates[1], 0);
    }
    if (analogRead(LSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 3);
    } else {
      removeWall(cordinates[0], cordinates[1], 3);
    }
    if (analogRead(MSens) > sensor) {
      addWall(cordinates[0], cordinates[1], 2);
    } else {
      removeWall(cordinates[0], cordinates[1], 2);
    }
  }
}
/* else if ((Llocater + Rlocater) / 2 > (notWall+100)) {  //bir sonraki kare (opsiyonel)
    if (direction == 'U') {
      if (analogRead(RSens) > sensor) {
        addWall(cordinates[0], max((cordinates[1] - 1), 0), 1);
      }
      if (analogRead(LSens) > sensor) {
        addWall(cordinates[0], max((cordinates[1] - 1), 0), 2);
      }
    } else if (direction == 'R') {
      if (analogRead(RSens) > sensor) {
        addWall(min(15, (cordinates[0] + 1)), cordinates[1], 3);
      }
      if (analogRead(LSens) > sensor) {
        addWall(min(15, (cordinates[0] + 1)), cordinates[1], 0);
      }
    } else if (direction == 'D') {
      if (analogRead(RSens) > sensor) {
        addWall(cordinates[0], min(15, (cordinates[1] + 1)), 2);
      }
      if (analogRead(LSens) > sensor) {
        addWall(cordinates[0], min(15, (cordinates[1] + 1)), 1);
      }
    } else if (direction == 'L') {
      if (analogRead(RSens) > sensor) {
        addWall(max((cordinates[0] - 1), 0), cordinates[1], 0);
      }
      if (analogRead(LSens) > sensor) {
        addWall(max((cordinates[0] - 1), 0), cordinates[1], 3);
      }
    }
  }*/