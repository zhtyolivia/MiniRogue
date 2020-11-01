//
//  Monster.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//



#include <stdio.h>
#include<iostream>
#include "Actor.h"

class Player;
class Dungeon;

#ifndef MONSTER_INCLUDED
#define MONSTER_INCLUDED

class Monster : public Actor
{
public:
    Monster(Dungeon* dp, int r, int c);
    virtual ~Monster();

    char getType();
    void setType(char c);
    std::string getName();
    void setName(std::string s);
    
    virtual void move();
    virtual void drop() = 0;
    virtual bool canSmell();
    virtual void attack(Player* p);
    
    bool canDropHere();
    bool canMove(int r, int c);


private:
    char m_type;
    std::string m_name;
    
};

#endif /* MONSTER_INCLUDED */



/*============BOGEYMAN=============*/

#ifndef BOGEYMAN_INCLUDED
#define BOGEYMAN_INCLUDED

class Bogeyman : public Monster
{
public:
    Bogeyman(Dungeon* dp, int r, int c);
    bool canSmell();
    void drop();
};

#endif/*BOGEYMAN_INCLUDED*/

/*============SNAKEWOMAN=============*/

#ifndef SNAKEWOMAN_INCLUDED
#define SNAKEWOMAN_INCLUDED

class SnakeWoman : public Monster 
{
public:
    SnakeWoman(Dungeon* dp, int r, int c);
    bool canSmell();
    void drop();
    void attack(Player* p);
};

#endif/*SNAKEWOMAN_INCLUDED*/

/*============DRAGON=============*/

#ifndef DRAGON_INCLUDED
#define DRAGON_INCLUDED

class Dragon : public Monster
{
public:
    Dragon(Dungeon* dp, int r, int c);
    void drop();
    void move();
private:
    int m_initial_hit;
};

#endif/*DRAGON_INCLUDED*/

/*============GOBLIN=============*/

#ifndef GOBLIN_INCLUDED
#define GOBLIN_INCLUDED

class Goblin : public Monster
{
public:
    Goblin(Dungeon* dp, int r, int c, int dist);
    void drop();
    void move();
private:
    //helper function
    int smartMove(int gY, int gX, int pY, int pX, int n, bool v[18][70]);
    int m_smell_dist;
};

#endif /*GOBLIN_INCLUDED*/
