//
//  Actor.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <stdio.h>
class Dungeon;
class Weapon;

class Actor
{
public:
    Actor(Dungeon *pp, int r, int c);
    virtual ~Actor();
    
    //accessors
    int getRow();
    int getCol();
    int getMaxhit();
    int getHit();
    int getArmor();
    int getStrength();
    int getDext();
    int getSleep();
    Dungeon* getDungeon();
    Weapon* getWeapon();
    
    //mutators
    void setHitPoint(int x);
    void setArmor(int x);
    void setStrength(int x);
    void setDext(int x);
    void setSleep(int x);
    void setWeapon(Weapon* wp);
    void setRow(int r);
    void setCol(int c);
    
private:
    int m_row;
    int m_col;
    int m_hit_point;
    int m_armor_point;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    Dungeon* m_dungeon;
    Weapon* m_current_weapon;

    
};

#endif /* Actor_hpp */
