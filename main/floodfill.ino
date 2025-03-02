

bool checkWall(int x, int y, int direction) { 
  int wallcheck1 = (y * 16 + x) / 2;
  int wallcheck2 = (y * 16 + x) % 2;
  if (wallcheck2 == 0) {
    switch (direction) {
      case 0: return bitRead(wall[wallcheck1], 7);  // up
      case 1: return bitRead(wall[wallcheck1], 6);  // right
      case 2: return bitRead(wall[wallcheck1], 5);  // left
      case 3: return bitRead(wall[wallcheck1], 4);  // down
    }
  } else {
    switch (direction) {
      case 0: return bitRead(wall[wallcheck1], 3);  // up
      case 1: return bitRead(wall[wallcheck1], 2);  // right
      case 2: return bitRead(wall[wallcheck1], 1);  // left
      case 3: return bitRead(wall[wallcheck1], 0);  // down
    }
  }
  return false;
}

void addWall(int x, int y, int direction) {  //ÇALIŞIYO
  int wallcheck1 = (y * 16 + x) / 2;
  int wallcheck2 = (y * 16 + x) % 2;
  if (wallcheck2 == 0) {
    switch (direction) {
      case 0:  // up
        bitSet(wall[wallcheck1], 7);
        if (wallcheck1 > 7) {
          bitSet(wall[wallcheck1 - 8], 4);
        }
        break;
      case 1:  // right
        bitSet(wall[wallcheck1], 6);
        bitSet(wall[wallcheck1], 1);
        break;
      case 2:  // left
        bitSet(wall[wallcheck1], 5);
        if (wallcheck1 % 8 != 8) {
          bitSet(wall[wallcheck1 - 1], 2);
        }
        break;
      case 3:  // down
        bitSet(wall[wallcheck1], 4);
        if (wallcheck1 < 120) {
          bitSet(wall[wallcheck1 + 8], 7);
        }
        break;
    }
  } else {
    switch (direction) {  //DİĞER KAREYİ DE EKLE
      case 0:             // up
        bitSet(wall[wallcheck1], 3);
        if (wallcheck1 > 7) {
          bitSet(wall[wallcheck1 - 8], 0);
        }
        break;
      case 1:  // right
        bitSet(wall[wallcheck1], 2);
        if (wallcheck1 % 8 != 7) {
          bitSet(wall[wallcheck1 + 1], 5);
        }
        break;
      case 2:  // left
        bitSet(wall[wallcheck1], 1);
        bitSet(wall[wallcheck1], 6);
        break;
      case 3:  // down
        bitSet(wall[wallcheck1], 0);
        if (wallcheck1 < 120) {
          bitSet(wall[wallcheck1 + 8], 3);
        }
        break;
    }
  }
}

void removeWall(int x, int y, int direction) {
  int wallcheck1 = (y * 16 + x) / 2;
  int wallcheck2 = (y * 16 + x) % 2;
  if (wallcheck2 == 0) {
    switch (direction) {
      case 0:  // up
        if (wallcheck1 > 7) {
          wall[wallcheck1] &= ~(1 << 7);
          wall[wallcheck1 - 8] &= ~(1 << 4);
        }
        break;
      case 1:  // right
        wall[wallcheck1] &= ~(1 << 6);
        wall[wallcheck1] &= ~(1 << 1);
        break;
      case 2:  // left 
        if (wallcheck1 % 8 != 0) {
          wall[wallcheck1] &= ~(1 << 5);
          wall[wallcheck1-1] &= ~(1 << 2);
        }
        break;
      case 3:  // down
        if (wallcheck1 < 120) {
          wall[wallcheck1] &= ~(1 << 4);
          wall[wallcheck1+8] &= ~(1 << 7);
        }
        break;
    }
  } else {
    switch (direction) {  
      case 0:             // up BURDA KALDI
        if (wallcheck1 > 7) {
          wall[wallcheck1] &= ~(1 << 3);
          wall[wallcheck1-8] &= ~(1 << 0);
        }
        break;
      case 1:  // right
        if (wallcheck1 % 8 != 7) {
          wall[wallcheck1] &= ~(1 << 2);
          wall[wallcheck1+1] &= ~(1 << 5);
        }
        break;
      case 2:  // left
        wall[wallcheck1] &= ~(1 << 1);
        wall[wallcheck1] &= ~(1 << 6);
        break;
      case 3:  // down
        if (wallcheck1 < 120) {
          wall[wallcheck1] &= ~(1 << 0);
          wall[wallcheck1+8] &= ~(1 << 3);
        }
        break;
    }
  }
}



void calculateMazeDistances() {  //ÇALIŞIYO
  // Clear squares
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 16; j++) {
      squares[i][j] = 255;  // Use max value to indicate unvisited
    }
  }

  // Mark destination squares as 0
  squares[7][7] = 0;
  squares[7][8] = 0;
  squares[8][7] = 0;
  squares[8][8] = 0;


  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 16; j++) {
      for (int k = 0; k < 16; k++) {
        if (squares[j][k] == i) {
          if (squares[j][k - 1] == 255 && k > 0 && checkWall(j, k, 0) == 0) {  // üst
            squares[j][k - 1] = i + 1;
          }
          if (squares[j + 1][k] == 255 && j < 15 && checkWall(j, k, 1) == 0) {  // sağ
            squares[j + 1][k] = i + 1;
          }
          if (squares[j - 1][k] == 255 && j > 0 && checkWall(j, k, 2) == 0) {  // sol

            squares[j - 1][k] = i + 1;
          }
          if (squares[j][k + 1] == 255 && k < 15 && checkWall(j, k, 3) == 0) {  // alt
            squares[j][k + 1] = i + 1;
          }
        }
      }
    }
  }
}
