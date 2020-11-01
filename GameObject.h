//
//  GameObject.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <stdio.h>

class GameObject{
    
public:
    GameObject(std::string name, int row, int col);
    virtual ~GameObject();
    
    char getType();
    int row();
    int col();
    std::string getName();
    std::string getAction();
    
    void setRow(int x);
    void setCol(int x);
    void setType(char c);
    void setName(std::string s);
    void setAction(std::string s);
    
private:
    char m_type;
    int m_row;
    int m_col;
    std::string m_action;
    std::string m_name;
    
};

/*============WEAPON==============*/

class Weapon : public GameObject{
public:
    Weapon(std::string name, int dext, int dmage, int row, int col);
    int getDext();
    int getDamage();
private:
    int m_dext_bonus;
    int m_damage;
    
};

/*============MACE==============*/

class Mace : public Weapon{
public:
    Mace( int row, int col);
};

/*============SHORTSWORD==============*/

class ShortSword : public Weapon{
public:
    ShortSword( int row, int col);
};

/*============LONGSWORD==============*/

class LongSword : public Weapon{
public:
    LongSword( int row, int col);
};

/*============MAGICAXE==============*/

class MagicAxe : public Weapon{
public:
    MagicAxe( int row, int col);
};

/*============MAGICFANG==============*/

class MagicFang : public Weapon{
public:
    MagicFang( int row, int col);

};

/*============SCROLL==============*/

class Scroll : public GameObject{
public:
    Scroll(std::string name, int row, int col);
};



#endif /* GameObject_hpp */
