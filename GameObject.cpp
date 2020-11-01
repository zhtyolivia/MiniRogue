//
//  GameObject.cpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#include "GameObject.h"
using namespace std;

GameObject::~GameObject()
{}

GameObject::GameObject( string name, int row, int col):m_col(col), m_row(row), m_name(name)
{}

char GameObject::getType()
{
    return m_type;
}
int GameObject::row()
{
    return m_row;
}
int GameObject::col()
{
    return m_col;
}
string GameObject::getName()
{
    return m_name;
}
string GameObject::getAction()
{
    return m_action;
}
void GameObject::setRow(int x)
{
    m_row=x;
}
void GameObject::setCol(int x)
{
    m_col=x;
}
void GameObject::setType(char c)
{
    m_type=c;
}
void GameObject::setName(string s)
{
    m_name=s;
}
void GameObject::setAction(string s)
{
    m_action=s;
}

/*============WEAPON==============*/

Weapon::Weapon( string name, int dex, int damage, int row, int col) : GameObject(name, row, col)
{
    m_dext_bonus = dex;
    m_damage = damage;
    setType('(');
}


int Weapon::getDext()
{
    return m_dext_bonus;
}

int Weapon::getDamage()
{
    return m_damage;
}

/*============MACE==============*/

Mace::Mace(int row, int col):Weapon("Mace", 0, 2, row, col)
{
    setAction("swings mace at");
}

/*============SHORTSWORD==============*/

ShortSword::ShortSword(int row, int col):Weapon("Short sword", 0 , 2, row, col)
{
    setAction("slashes short sword at");
}
/*============LONGSWORD==============*/

LongSword::LongSword(int row, int col):Weapon("Long sword", 2, 4, row, col)
{
    setAction("swings long sword at");
}

/*============MAGICAXE==============*/

MagicFang::MagicFang(int row, int col):Weapon("magic fangs", 5, 5, row,  col) 
{
    setAction("strikes magic fangs at");
}

/*============MAGICFANG==============*/

MagicAxe::MagicAxe(int row, int col):Weapon("magic axe", 3, 2, row, col) 
{
    setAction("chops magic axe at");
}

/*============SCROLL==============*/

Scroll::Scroll( string name, int row, int col) : GameObject (name, row, col)
{
    setType('?');
}
