
#define L_Mdir 7
#define L_Mpwm 9
#define R_Mdir 8
#define R_Mpwm 10

#define left_en 4
#define right_en 5

#define LSens A2  //left sensor
#define MSens A1  //orta sensör
#define RSens A0  //sağ sensör
#define SensPin 12
#define QtrSens A3

#define button A6

#define LeftLed 11
#define RightLed 6

#define sag squares[cordinates[0] + 1][cordinates[1]]
#define sol squares[cordinates[0] - 1][cordinates[1]]
#define alt squares[cordinates[0]][cordinates[1] + 1]
#define ust squares[cordinates[0]][cordinates[1] - 1]



int cordinates[2] = { 0, 0 };  //0,0
int dirval = 1002;             //0-> up  1->right 2->down 3->left    sağa dönerken arttır (:
char direction = 'D';
char targetDirection;
int isWall = 110;   //65  //65 iyiydi alışık kareden
int notWall = 135;  //70 //180 iyiydi alışık kareden


bool Lfull1 = 0;
bool Rfull1 = 0;
bool Lfull2 = 0;
bool Rfull2 = 0;
int offset = 0;

int Udist = 0;
int Rdist = 0;
int Ldist = 0;
int Ddist = 0;
int smallest;

int currentIndex = 0;
int targetIndex = 0;
int diff = 0;

//int l = 0;
//int r = 0;
int a = 0;



byte wall[128] = {
  0b10101000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00110001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00100101
};

/*
byte wall[128] = {
  0b10101000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001000, 0b10001100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000001, 0b00010000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00001000, 0b11000010, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000100,
  0b00110001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00010001, 0b00100101
};
*/

byte squares[16][16];

int interval = 0;

int dif = 0;
bool isCalibratedAdd = 0;
bool isCalibratedRemove = 0;


//sensor
int sensor = 148;  //135    170 sensor strtaight 270 ve sensor
int frontSens = 0;
int rightSens = 0;

bool whiteSeen = 0;
//int timeElapsed = 0;

//setting
int turncount = 227;

//speed
int Lspeed = 102;
int Rspeed = 100;  //153

//encoder
int Lcounter = 0;
int Rcounter = 0;
int left_pre = 0;
int right_pre = 0;
int Llocator = 0;
int Rlocator = 0;

int squareL = 630;
int squareR = 580;

int targetL = 290;


void setup() {
  Serial.begin(9600);
  pinMode(L_Mdir, OUTPUT);
  pinMode(L_Mpwm, OUTPUT);
  pinMode(R_Mdir, OUTPUT);
  pinMode(R_Mpwm, OUTPUT);


  pinMode(LSens, INPUT);
  pinMode(RSens, INPUT);
  pinMode(MSens, INPUT);
  pinMode(SensPin, OUTPUT);
  digitalWrite(SensPin, HIGH);

  pinMode(left_en, INPUT);
  pinMode(right_en, INPUT);

  pinMode(button, INPUT);
  pinMode(LeftLed, OUTPUT);
  pinMode(RightLed, OUTPUT);

  digitalWrite(RightLed, LOW);
  digitalWrite(LeftLed, LOW);




  while (true) {
    if (analogRead(button) > 800) {
      ledblink(4);
      break;
    }
  }

}



void loop() {

  saveWalls();
  calculateMazeDistances();
  move();
  quit();
  //isTargetReached();
}

