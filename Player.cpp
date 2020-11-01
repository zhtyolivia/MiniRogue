//
//  Player.cpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#include "Player.h"
#include "Dungeon.h"
using namespace std;

Player::Player(Dungeon *pp, int r, int c):Actor(pp, r, c)
{
    setDext(2);
    setMaxHit(20);
    setHitPoint(20);
    setArmor(2);
    setWeapon(new ShortSword(r,c));
    setStrength(2);
    m_inventory.push_back(getWeapon());
}

Player::~Player()
{
    for(vector<GameObject*>::iterator it = m_inventory.begin(); it != m_inventory.end(); it++)
    {
        delete *it;
    }
}

int Player::getMaxHit()
{
    return m_max_hit_point;
}

void Player::setMaxHit(int x)
{
    m_max_hit_point=x;
}

//if the player can move in the direction represented by c, move in that direction / attack monster in that direction.l
void Player::move(char c)
{
    if(trueWithProbability(0.1) && getHit()<m_max_hit_point)
        setHitPoint(getHit()+1);
    if(getSleep()>=1)
    {
        setSleep(getSleep()-1);
    }
    else
    {
        //if there is a monter in the direction represented by c, attack the monster
        //otherwise, move in that direction if possible
        switch (c) {
            case ARROW_UP:
                if(getDungeon()->getMonster(getRow()-1, getCol())!=nullptr) //if there is a monster in that direction
                {
                    attack(getDungeon()->getMonster(getRow()-1, getCol()));
                }
                //if the player can move in this direction, then move.
                else if(getDungeon()->m_game_grid[getRow()-1][getCol()]==' ' || getDungeon()->m_game_grid[getRow()-1][getCol()]=='>' || getDungeon()->m_game_grid[getRow()-1][getCol()]=='&' || getDungeon()->m_game_grid[getRow()-1][getCol()]==')' || getDungeon()->m_game_grid[getRow()-1][getCol()]=='?'){
                    setRow(getRow()-1);
                }
                break;
            case ARROW_DOWN:
                if(getDungeon()->getMonster(getRow()+1, getCol())!=nullptr) //if there is a monster in that direction
                {
                    attack(getDungeon()->getMonster(getRow()+1, getCol()));
                }
                //if the player can move in this direction, then move.
                else if(getDungeon()->m_game_grid[getRow()+1][getCol()]==' ' || getDungeon()->m_game_grid[getRow()+1][getCol()]=='>' || getDungeon()->m_game_grid[getRow()+1][getCol()]=='&' || getDungeon()->m_game_grid[getRow()+1][getCol()]==')' || getDungeon()->m_game_grid[getRow()+1][getCol()]=='?')
                    setRow(getRow()+1);
                break;
            case ARROW_LEFT:
                if(getDungeon()->getMonster(getRow(), getCol()-1)!=nullptr) //if there is a monster in that direction
                {
                    attack(getDungeon()->getMonster(getRow(), getCol()-1));
                }
                //if the player can move in this direction, then move.
                else if(getDungeon()->m_game_grid[getRow()][getCol()-1]==' ' || getDungeon()->m_game_grid[getRow()][getCol()-1]=='>' || getDungeon()->m_game_grid[getRow()][getCol()-1]=='&' || getDungeon()->m_game_grid[getRow()][getCol()-1]==')' || getDungeon()->m_game_grid[getRow()][getCol()-1]=='?')
                    setCol(getCol()-1);
                break;
            case ARROW_RIGHT:
                if(getDungeon()->getMonster(getRow(), getCol()+1)!=nullptr) //if there is a monster in that direction
                {
                    attack(getDungeon()->getMonster(getRow(), getCol()+1));
                }
                //if the player can move in this direction, then move.
                else if(getDungeon()->m_game_grid[getRow()][getCol()+1]==' ' || getDungeon()->m_game_grid[getRow()][getCol()+1]=='>' || getDungeon()->m_game_grid[getRow()][getCol()+1]=='&' || getDungeon()->m_game_grid[getRow()][getCol()+1]==')' ||getDungeon()->m_game_grid[getRow()][getCol()+1]=='?')
                    setCol(getCol()+1);
                break;
        }
    }//sleep time < 1
}

void Player::attack(Monster* m)
{
    //determine if the player has hit the monster using the formula
    if(randInt(1, getDext()+getWeapon()->getDext()) >= randInt(1, m->getDext()+m->getArmor()))
    {
        //subtract the damage from the monster's hit point
        m->setHitPoint(m->getHit()-(randInt(0, getStrength()+getWeapon()->getDamage()-1)));

        //if the user is using magic fang of sleep, then check if the defender is put to sleep
        if(getWeapon()->getName()=="magic fangs" && trueWithProbability(0.2))
        {
            int x = randInt(2, 6);
            m->setSleep(x);
            getDungeon()->m_message.push_back("Player "+getWeapon()->getAction()+' '+m->getName()+" and hits, putting "+m->getName()+" to sleep.");
        }
        //else: the player is using 
        else if(getWeapon()->getName()!="magic fangs"){
            getDungeon()->m_message.push_back("Player " +getWeapon()->getAction()+' '+m->getName()+" and hits.");
        }
        //check if the monster dies due to the dit. If so, remove the monster from the monster vector and let the monster drop whatever it may drop
        for(vector<Monster*>::iterator it = getDungeon()->m_monsters.begin(); it != getDungeon()->m_monsters.end(); it++)
        {
            if((*it)->getHit()<=0)
            {
                (*it)->drop();
                delete *it;
                getDungeon()->m_monsters.erase(it);
                break;//the player can only attck one monster at a time. Since previous dead monsters have been removed, break when the most recent dead monster is found.
            }
        }
    }
    else //the player did not hit the monster
    {
        getDungeon()->m_message.push_back("Player "+getWeapon()->getAction()+' '+m->getName()+" and misses.");
    }
}


void Player::pickUp()
{
    if(m_inventory.size()>=25)
        getDungeon()->m_message.push_back("Your knapsack is full; you can't pick that up.");
    else
    {
        for(vector<GameObject*>::iterator it = getDungeon()->m_objects.begin(); it != getDungeon()->m_objects.end(); it++)
        {
            //there might be multiple objects at the same spot, so need to check every object
            //if the player is standing on an object
            if(getRow()==(*it)->row() && getCol()==(*it)->col())
            {
                m_inventory.push_back(*it);
                getDungeon()->m_message.push_back("You pick up "+(*it)->getName());
                it=getDungeon()->m_objects.erase(it);
                break;
            }
        }
    }
}

void Player::changeWeapon()
{
    //note for myself: don't abandon the old weapon if object used is a weapon
    
    char c = getCharacter();
    
    int i = (int)c - 97; //i is the corresponding index of the object in the object inventory
    
    if(i>=m_inventory.size())//check the validity of input
    {
        clearScreen();
        return;
    }
    
    Weapon* weapon_check =  dynamic_cast<Weapon*>(m_inventory[i]);
    Scroll* scroll_check = dynamic_cast<Scroll*>(m_inventory[i]);
    
    if(weapon_check!=nullptr)
    {
        getDungeon()->m_message.push_back("You are wielding "+getWeapon()->getName());
        setWeapon(weapon_check);
    }
    else//nullptr
        getDungeon()->m_message.push_back("You can't wield "+scroll_check->getName());
}

void Player::read()
{
    char c = getCharacter();
        
    int i = (int)c - 97; //i is the corresponding index of the object in the object inventory
    
    if(i>=m_inventory.size())//check the validity of input
    {
        clearScreen();
        return;
    }
    Scroll* scroll_check = dynamic_cast<Scroll*>(m_inventory[i]);
    Weapon* weapon_check =  dynamic_cast<Weapon*>(m_inventory[i]);

    
    if(scroll_check != nullptr)
    {
        //update player's stats according to the scroll read
        //produce the corresponding message
        
        if(scroll_check->getName()=="scroll of teleportation")
        {
            //randomly move the player
            Coord temp = getDungeon()->randCoord();
            setRow(temp.row);
            setCol(temp.col);
            getDungeon()->m_message.push_back("You feel your body wrenched in space and time.");
        }
        
        else if(scroll_check->getName()=="scroll of strength")
        {
            //enhance strength
            setStrength(getStrength()+randInt(1, 3));
            getDungeon()->m_message.push_back("Your muscles bulge.");
        }
        else if(scroll_check->getName()=="scroll of enhance armor")
        {
            //increment armor point
            setArmor(getArmor()+randInt(1, 3));
            getDungeon()->m_message.push_back("Your armor glows blue.");
        }
        else if(scroll_check->getName()=="scroll of enhance health")
        {
            //increment max hit points
            setMaxHit(getMaxHit()+randInt(3, 8));
            getDungeon()->m_message.push_back("You feel your heart beating stronger.");
        }
        else //"scroll of enhance dexterity"
        {
            //increase dexterity by 1
            setDext(getDext()+1);
            getDungeon()->m_message.push_back("You feel like less of a klutz.");
        }
        //remove the scroll from the inventory
        for(vector<GameObject*>::iterator it = m_inventory.begin(); it != m_inventory.end(); it++)
        {
            if((*it)->row()==scroll_check->row() && (*it)->col()==scroll_check->col())
            {
                delete *it;
                m_inventory.erase(it);
                break;
            }
        }
    }
    else //nullptr
         getDungeon()->m_message.push_back("You can't read a "+weapon_check->getName());
}

void Player::printInventory()
{
    char letter = 'a';
    int i = 0;
    clearScreen();
    cout<<"Inventory:"<<endl;
    for(vector<GameObject*>::iterator it = m_inventory.begin(); it != m_inventory.end(); it++, i++)
        cout << static_cast<char>(letter+i) << ". " << (*it)->getName() << endl;
}
