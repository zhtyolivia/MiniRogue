//
//  Coord.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#ifndef Coord_hpp
#define Coord_hpp

#include <stdio.h>

class Coord
{
public:
    int row;
    int col;
    Coord();
    Coord(int r, int c);
};

struct Room
{
    Coord topLeft;
    Coord topRight;
    Coord botmLeft;
    Coord botmRight;
    int length;
    int height;
};

#endif /* Coord_hpp */


