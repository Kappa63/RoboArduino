/*
Author: Karim Q.
Date: 17/5/24
*/
#define MATHEMATICAL_INF 1000

#define ROWS 6
#define COLUMNS 6
#define CELL_DRIVE_TIME 350
#define STOP_DELAY 500

#define RIGHT_IR A0
#define FRONT_IR A1
#define LEFT_IR A2

#define RIGHT_THRESHOLD_SPEED 100
#define RIGHT_SPEED 9
#define RIGHT_IN1 8
#define RIGHT_IN2 7

#define LEFT_THRESHOLD_SPEED 100
#define LEFT_SPEED 3
#define LEFT_IN3 6
#define LEFT_IN4 5

#define VIEW_THRESHOLD 300

struct point
{
    int x;
    int y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
};

enum direction{
  Right, Front, Left, Back
};

int qPos = 0;
int gScores[ROWS*COLUMNS];
int fScores[ROWS*COLUMNS];
int startPnt;
int endPnt;
int PQueue[ROWS*COLUMNS][3];
int starPath[ROWS*COLUMNS];
int f;
int h;
int pnt;
int nextPnt;
int tempGScore;
int tempFScore;

direction curDirection;
int curPos;

void setup(){
  curDirection = Front;
  curPos = 0;
  pinMode(RIGHT_SPEED, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);

  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(LEFT_IN3, OUTPUT);
  pinMode(LEFT_IN4, OUTPUT);

  pinMode(FRONT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_IR, INPUT);

  PQueue[qPos][0] = 0;
  PQueue[qPos][1] = 0;
  PQueue[qPos][2] = startPnt;
  qPos++;
  for(int i=0; i<ROWS*COLUMNS; i++){
    gScores[i] = MATHEMATICAL_INF;
    fScores[i] = MATHEMATICAL_INF;   
  }
  int originManhattan = 0+manhattanDistance(intToPoint(startPnt), intToPoint(endPnt));
  a = intToPoint(ROWS*COLUMNS-1);
  endPnt = pointToInt(point(a.x/2, a.y/2));
  gScores[startPnt] = 0;
  fScores[startPnt] = originManhattan;
  PQueue[qPos][0] = originManhattan;
  PQueue[qPos][1] = originManhattan;
  PQueue[qPos][2] = startPnt;
  qPos++;

  Serial.begin(9600);

  // AStar();
}

void loop(){
}

point intToPoint(int a){
  int y = a/ROWS;
  int x = a%ROWS;
  return point(x+1, y+1); 
}

int pointToInt(point a){
  int y = a.y-1;
  int x = a.x-1;
  return (y*ROWS)+x;
}

int manhattanDistance(point a, point b){
    return abs(a.x-b.x)+abs(a.y-b.y);
}

bool checkDir(direction d){
  if(d == Front)
    return (analogRead(FRONT_IR) <= VIEW_THRESHOLD);
  if(d == Right)
    return (analogRead(RIGHT_IR) <= VIEW_THRESHOLD);
  if(d == Left)
    return (analogRead(LEFT_IR) <= VIEW_THRESHOLD);
}

void goToPoint(int pos){
  int dist = manhattanDistance(intToPoint(curPos, pos));
  if(dist > 1){
    int theoArray1[20];
    int theoArray2[20];
    int finArray[20];
    int tPos = curPos;
    int i=0;
    while(tPos != startPnt){
      tPos = starPath[tPos];
      theoArray1[i++] = tPos;
    }
    tPos = pos;
    int j=0;
    int k=0;
    bool pathFound = false;
    while(tPos != startPnt){
      tPos = starPath[tPos];
      theoArray2[j++] = tPos;
      for(k=0; k<i; k++){
        if(theoArray2[j-1] == theoArray1[k]){
          pathFound = true;
          break;
        }
      }
      if(pathFound) break;
    }
    int m = 0;
    for(m=0; m<k; m++){
      finArray[m] = theoArray1[m];
    }
    for(int n=j-1; n>=0; n--){
      finArray[m++] = theoArray2[n];
    }
    
    for(int n=0; n<m; n++){
      movePoint(finArray[n]);
    }
  } else {
    movePoint(pos);
  }
}

void movePoint(int n){
  switch(n-curPos){
    case COLUMNS:
      switch(curDirection){
        case Front:
          turnRight90();
          moveSqrs(1);
          break;
        case Right:
          moveSqrs(1);
          break;
        case Left:
          turnRight90();
          turnRight90();
          moveSqrs(1);
          break;
        case Back:
          turnLeft90();
          moveSqrs(1);
          break;
      }
      break;
    case -COLUMNS:
      switch(curDirection){
        case Front:
          turnLeft90();
          moveSqrs(1);
          break;
        case Right:
          turnLeft90();
          turnLeft90();
          moveSqrs(1);
          break;
        case Left:
          moveSqrs(1);
          break;
        case Back:
          turnRight90();
          moveSqrs(1);
          break;
      }
      break;
    case 1:
      switch(curDirection){
        case Front:
          moveSqrs(1);
          break;
        case Right:
          turnLeft90();
          moveSqrs(1);
          break;
        case Left:
          turnRight90();
          moveSqrs(1);
          break;
        case Back:
          turnLeft90();
          turnLeft90();
          moveSqrs(1);
          break;
      }
      break;
    case -1:
      switch(curDirection){
        case Front:
          turnRight90();
          turnRight90();
          moveSqrs(1);
          break;
        case Right:
          turnRight90();
          moveSqrs(1);
          break;
        case Left:
          turnLeft90();
          moveSqrs(1);
          break;
        case Back:
          moveSqrs(1);
          break;
      }
      break;
  }

}

void moveSqrs(int n){
  for(int i=0; i<n; i++)
    moveForward();
  switch(curDirection){
    case Front:
      curPos += 1*n;
      break;
    case Left:
      curPos += -COLUMNS*n;
      break;
    case Right:
      curPos += COLUMNS*n;
      break;
    case Back:
      curPos += -1*n;
      break;
  }
}

void stopMotor() {
  analogWrite(RIGHT_SPEED, 0);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, LOW);

  analogWrite(LEFT_SPEED, 0);
  digitalWrite(LEFT_IN3, LOW);
  digitalWrite(LEFT_IN4, LOW);
  delay(STOP_DELAY);
}

void moveForward() {
  Serial.println("Move Forward");
  for(int i=0; i<CELL_DRIVE_TIME;){
    if(checkDir(Left) && !checkDir(Right)){
      turnRight();
    }
    else if(!checkDir(Left) && checkDir(Right)){
      turnLeft();
    }
    else if(!checkDir(Front)){
      i++;
      analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
      digitalWrite(RIGHT_IN1, LOW);
      digitalWrite(RIGHT_IN2, HIGH);

      analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
      digitalWrite(LEFT_IN3, HIGH);
      digitalWrite(LEFT_IN4, LOW);
    } else{
      break;
    }
    delay(1);
  }
  stopMotor();
}

void moveBackward() {
  Serial.println("Move Backward");
  analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);

  analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
  digitalWrite(LEFT_IN3, LOW);
  digitalWrite(LEFT_IN4, HIGH);
}

void turnLeft() {
  Serial.println("Turn Left");
  analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
  digitalWrite(RIGHT_IN1, LOW);
  digitalWrite(RIGHT_IN2, HIGH);

  analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
  digitalWrite(LEFT_IN3, LOW);
  digitalWrite(LEFT_IN4, HIGH);
}

void turnRight(){
  Serial.println("Turn Right");
  analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
  digitalWrite(RIGHT_IN1, HIGH);
  digitalWrite(RIGHT_IN2, LOW);

  analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
  digitalWrite(LEFT_IN3, HIGH);
  digitalWrite(LEFT_IN4, LOW);
}

void turnLeft90() {
  Serial.println("Turn Left 90");
  bool lPrev = checkDir(Left), rPrev = checkDir(Right), fPrev = checkDir(Front);
  while(((lPrev == checkDir(Left)) || (rPrev == checkDir(Right))) &&
        ((lPrev == checkDir(Left)) || (fPrev == checkDir(Front))) &&
        ((fPrev == checkDir(Front)) || (rPrev == checkDir(Right)))){
    analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
    digitalWrite(RIGHT_IN1, LOW);
    digitalWrite(RIGHT_IN2, HIGH);

    analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
    digitalWrite(LEFT_IN3, LOW);
    digitalWrite(LEFT_IN4, HIGH);
  }
  stopMotor();
  switch(curDirection){
    case Front:
      curDirection = Left;
      break;
    case Left:
      curDirection = Back;
      break;
    case Right:
      curDirection = Front;
      break;
    case Back:
      curDirection = Right;
      break;
  }
}

void turnRight90(){
  Serial.println("Turn Right 90");
  bool lPrev = checkDir(Left), rPrev = checkDir(Right), fPrev = checkDir(Front);
  while(lPrev == checkDir(Left) || rPrev == checkDir(Right) &&
        lPrev == checkDir(Left) || fPrev == checkDir(Front) &&
        fPrev == checkDir(Front) || rPrev == checkDir(Right)){
    analogWrite(RIGHT_SPEED, RIGHT_THRESHOLD_SPEED);
    digitalWrite(RIGHT_IN1, HIGH);
    digitalWrite(RIGHT_IN2, LOW);

    analogWrite(LEFT_SPEED, LEFT_THRESHOLD_SPEED);
    digitalWrite(LEFT_IN3, HIGH);
    digitalWrite(LEFT_IN4, LOW);
  }
  stopMotor();
  switch(curDirection){
    case Front:
      curDirection = Right;
      break;
    case Left:
      curDirection = Front;
      break;
    case Right:
      curDirection = Back;
      break;
    case Back:
      curDirection = Left;
      break;
  }
}

void AStar(){
  while (qPos != 0){
    f = MATHEMATICAL_INF;
    h = MATHEMATICAL_INF;
    for(int i=0; i<qPos; i++)
      if(f > PQueue[i][0]){
        f = PQueue[i][0];
        h = PQueue[i][1];
        pnt = PQueue[i][2];
      } else if(f == PQueue[i][0] && h > PQueue[i][1]){
        f = PQueue[i][0];
        h = PQueue[i][1];
        pnt = PQueue[i][2];
      }
    qPos--;
    goToPoint(pnt);
    if(pnt == endPnt || pnt == endPnt+1 || endPnt == pnt+COLUMNS || endPnt == pnt+COLUMNS+1) break;
    if(!checkDir(Front)){
      switch(curDirection){
        case Front:
          nextPnt = pnt+1;
          break;
        case Back:
          nextPnt = pnt-1;
          break;
        case Right:
          nextPnt = pnt+COLUMNS;
          break;
        case Left:
          nextPnt = pnt-COLUMNS;
          break;
      };
      tempGScore = gScores[pnt];
      tempFScore = tempGScore+manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
      if (tempFScore < fScores[nextPnt]){
        gScores[nextPnt] = tempGScore;
        fScores[nextPnt] = tempFScore;
        PQueue[qPos][0] = tempFScore;
        PQueue[qPos][1] = manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
        PQueue[qPos][2] = nextPnt;
        qPos++;
        starPath[nextPnt] = pnt;
      }
    }
    if(!checkDir(Right)){
      switch(curDirection){
        case Front:
          nextPnt = pnt+COLUMNS;
          break;
        case Back:
          nextPnt = pnt-COLUMNS;
          break;
        case Right:
          nextPnt = pnt-1;
          break;
        case Left:
          nextPnt = pnt+1;
          break;
      };
      tempGScore = gScores[pnt];
      tempFScore = tempGScore+manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
      if (tempFScore < fScores[nextPnt]){
        gScores[nextPnt] = tempGScore;
        fScores[nextPnt] = tempFScore;
        PQueue[qPos][0] = tempFScore;
        PQueue[qPos][1] = manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
        PQueue[qPos][2] = nextPnt;
        qPos++;
        starPath[nextPnt] = pnt;
      }
    } 
    if(!checkDir(Left)){
      switch(curDirection){
        case Front:
          nextPnt = pnt-COLUMNS;
          break;
        case Back:
          nextPnt = pnt+COLUMNS;
          break;
        case Right:
          nextPnt = pnt+1;
          break;
        case Left:
          nextPnt = pnt-1;
          break;
      };
      tempGScore = gScores[pnt];
      tempFScore = tempGScore+manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
      if (tempFScore < fScores[nextPnt]){
        gScores[nextPnt] = tempGScore;
        fScores[nextPnt] = tempFScore;
        PQueue[qPos][0] = tempFScore;
        PQueue[qPos][1] = manhattanDistance(intToPoint(nextPnt), intToPoint(endPnt));
        PQueue[qPos][2] = nextPnt;
        qPos++;
        starPath[nextPnt] = pnt;
      }
    }
  }
}
