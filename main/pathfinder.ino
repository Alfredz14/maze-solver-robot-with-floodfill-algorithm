char pathfinder() {  //cordinates[0]->x     cordinates[1]->y KONTRTOL EDİLDİ

  if (checkWall(cordinates[0], cordinates[1], 0) == 0) {
    Udist = ust;
  } else {
    Udist = 9999;
  }
  if (checkWall(cordinates[0], cordinates[1], 1) == 0) {
    Rdist = sag;
  } else {
    Rdist = 9999;
  }
  if (checkWall(cordinates[0], cordinates[1], 2) == 0) {
    Ldist = sol;
  } else {
    Ldist = 9999;
  }
  if (checkWall(cordinates[0], cordinates[1], 3) == 0) {
    Ddist = alt;
  } else {
    Ddist = 9999;
  }


  /*if (Rdist<Udist && Rdist < Ldist && Rdist < Ddist){  ŞÜPHELİ
    return 'R';
  } if (Ddist<Udist && Ddist < Ldist && Ddist < Rdist){
    return 'D';
  }  if (Ldist<Udist && Ldist < Rdist && Ldist < Ddist){
    return 'L';
  }  if (Udist<Rdist && Udist < Ldist && Udist < Ddist){
    return 'U';
  }*/
  if (Rdist <= Udist && Rdist <= Ldist && Rdist <= Ddist) {
    return 'R';
  }
  if (Ddist <= Udist && Ddist <= Ldist && Ddist <= Rdist) {
    return 'D';
  }
  if (Ldist <= Udist && Ldist <= Rdist && Ldist <= Ddist) {
    return 'L';
  }
  if (Udist <= Rdist && Udist <= Ldist && Udist <= Ddist) {
    return 'U';
  }
}


void move() {
  char directions[] = { 'U', 'R', 'D', 'L' };
  for (int i = 0; i < 4; i++) {
    if (directions[i] == direction) {
      currentIndex = i;
    }
    if (directions[i] == pathfinder()) {
      targetIndex = i;
    }
  }
  diff = targetIndex - currentIndex;
  if (diff < 0) {
    diff += 4;
  }
  if (diff == 1) {
    right();
  } else if (diff == 2) {
    if (analogRead(RSens) > analogRead(LSens)) {
      left();
      left();
    } else {
      right();
      right();
    }
  } else if (diff == 3) {
    left();
  }

  if (analogRead(MSens) < sensor) {
    straight();
  }

  /*int currentX = cordinates[0];
    int currentY = cordinates[1];
    if(currentX != cordinates[0] || currentY != cordinates[1]){
      Mstop();
      break;
    }*/
}
