#ifndef PG550_EXAM_SNAKESTRUCT_H
#define PG550_EXAM_SNAKESTRUCT_H

typedef struct SnakeBody {
    int iDirection; // up == 0, left == 1, down == 2 and right == 3. none == -1
    int iX;
    int iY;
} SnakeBody;

typedef struct Snake {
    int iSnakeSize;
    int iSnakeMaxSize;
    SnakeBody *paSnakeBody;
} Snake;

typedef struct Food {
    bool bFoodOnBoard;
    int iX;
    int iY;
} Food;

enum SnakeGamePixel {
    GRASS,
    HEAD,
    BODY,
    TAIL,
    FOOD,
};

enum SnakeGameDirection {
    UP,
    LEFT,
    DOWN,
    RIGHT,
};

#endif //PG550_EXAM_SNAKESTRUCT_H
