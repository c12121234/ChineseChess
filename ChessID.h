#ifndef CHESSID_H
#define CHESSID_H

enum Team
{
    ZERO = 0,
    RED = 1,
    BLACK = 2
};

enum Direction
{
    PLUSX = 0,
    MINUSX = 1,
    PLUSY = 2,
    MINUSY = 3
};

enum CHARACTER
{
    KING = 1,
    QUEEN = 2,
    BISHOP = 3,
    KNIGHT = 4,
    TOWER = 5,
    CANNON = 6,
    MINIMON = 7
};
#endif // CHESSID_H
