//
//  Player.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//


#ifndef Player_hpp
#define Player_hpp

#include "GameObject.h"
#include "Actor.h"
#include "Monster.h"
#include "utilities.h"
#include <stdio.h>
#include<vector>

class Dungeon;

class Player : public Actor
{
public:
    Player(Dungeon *pp, int r, int c);
    void move(char c);
    void attack(Monster* m);
//    void attack(Actor* m);
    std::vector<GameObject*> m_inventory;
    void pickUp();
    void changeWeapon();
    void printInventory();
    //trivial accessor and mutator
    int getMaxHit();
    void setMaxHit(int x);
    ~Player();
    void read(); 
private:
    int m_max_hit_point;
};

#endif /* Player_hpp */
 
