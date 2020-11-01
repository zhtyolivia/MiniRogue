//
//  Actor.cpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#include "Actor.h"
#include "Dungeon.h"
#include "GameObject.h"

Actor::Actor(Dungeon* dp, int r, int c):m_dungeon(dp), m_row(r), m_col(c), m_sleep(0)
{}

Actor::~Actor()
{
//    delete m_dungeon;
//    delete m_current_weapon;
}

void Actor::setWeapon(Weapon *wp)
{
    m_current_weapon=wp;
}
void Actor::setHitPoint(int x)
{
    m_hit_point=x;
}
void Actor::setArmor(int x)
{
    m_armor_point=x;
}
void Actor::setStrength(int x)
{
    m_strength=x;
}
void Actor::setDext(int x)
{
    m_dexterity=x;
}
void Actor::setSleep(int x)
{
    if(m_sleep<x)
        m_sleep=x;
}
int Actor::getRow()
{
    return m_row;
}
int Actor::getCol()
{
    return m_col;
}
int Actor::getHit()
{
    return m_hit_point;
}
int Actor::getArmor()
{
    return m_armor_point;
}
int Actor::getStrength()
{
    return m_strength;
}
int Actor::getDext()
{
    return m_dexterity;
}
int Actor::getSleep()
{
    return m_sleep;
}
void Actor::setRow(int r)
{
    m_row=r;
}
void Actor::setCol(int c)
{
    m_col=c;
}
Dungeon* Actor::getDungeon()
{
    return m_dungeon;
}

Weapon* Actor::getWeapon()
{
    return m_current_weapon;
}

