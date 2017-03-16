#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

enum GameSize{
    Five = 5,
    Seven = 7,
    Nine = 9
};

enum TileState{
    OccupiedByBlue = 0,
    OccupiedByRed = 1,
    OccupiedByBlackHole = 2,
    Unoccupied = 3,
    ErrorState = 4
};

enum Player
{
    BluePlayer = 0,
    RedPlayer = 1,
};

enum Direction
{
    UpDirection = 0,
    RightDirection = -1,
    DownDirection = 2,
    LeftDirection = 1
};

struct GameStats{
    const int ActivePlayer;
    const int BluePoints;
    const int RedPoints;
    const int PointsToWin;
    GameStats(int player, int blue, int red, int win) : ActivePlayer(player),BluePoints(blue),RedPoints(red),PointsToWin(win){}
};

struct ActiveTile
{
    const int PosX;
    const int PosY;
    const bool Up;
    const bool Right;
    const bool Down;
    const bool Left;
    ActiveTile(int x=-1,int y=-1,bool up=false,bool right=false,bool down=false,bool left=false) : PosX(x),PosY(y), Up(up), Right(right), Down(down), Left(left){}
};

#endif // DATASTRUCTURES_H
