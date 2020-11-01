//
//  Monster.cpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#include<stack>
#include "Monster.h"
#include "Dungeon.h"
#include "Player.h"
using namespace std;

/*===================*/
/*===========MONSTER============*/
/*===================*/

Monster::Monster(Dungeon* dp, int r, int c):Actor(dp, r, c)
{}

char Monster::getType()
{
    return m_type;
}

void Monster::setType(char c)
{
    m_type=c;
}

string Monster::getName()
{
    return m_name;
}

void Monster::setName(string s)
{
    m_name=s;
}

bool Monster::canDropHere()
{
    for(vector<GameObject*>::iterator it = getDungeon()->m_objects.begin(); it != getDungeon()->m_objects.end(); it++)
    {
        if((*it)->row()==getRow() || (*it)->col()==getCol())
            return false;
    }
    return true;
}

void Monster::attack(Player *p)
{
    if(getSleep()<=0)
    {
        //determine if the monster has hit the player using the formula
        if(randInt(1, getDext()+getWeapon()->getDext())>=randInt(1, p->getDext()+p->getArmor()))
        {
            getDungeon()->m_message.push_back(getName()+' '+getWeapon()->getAction()+" the Player and hits.");
            //decrease player's hit point
            p->setHitPoint(p->getHit()-randInt(0, getStrength()+getWeapon()->getDamage()-1));
        }
        else //the monster did not hit the player, make no changes to stats, push back message
        {
            getDungeon()->m_message.push_back(getName()+' '+getWeapon()->getAction()+" the Player and misses.");
        }
    }
    else
        setSleep(getSleep()-1);
}

bool Monster::canMove(int r, int c)
{
    if(r>=18 || c>= 70 || r<0 || c<0)
        return false;
    bool check = getDungeon()->m_game_grid[r][c]!=' ' && getDungeon()->m_game_grid[r][c]!='>' && getDungeon()->m_game_grid[r][c]!='&' && getDungeon()->m_game_grid[r][c]!=')' && getDungeon()->m_game_grid[r][c]!='?';
    return !check;
}

void Monster::move()
{
    if(canSmell() && getSleep()<1)
    {
        //note for myself: attack if possible, otherwise move
        
        int r = getRow()-getDungeon()->getPlayer()->getRow();
        //r positive: monster is below player, need to move upward
        //r negative: monster is above player, need to move downward
        
        int c =getCol()-getDungeon()->getPlayer()->getCol();
        //c positive: monster is to the right of player, need to move to the left
        //c negative: monster is to the left of player, need to move to the right
        
        //if the monster is beside the player, attack the player
        if((r==0 && c==1) || (r==0 && c==-1) || (r==1 && c==0) || (r==-1 && c==0))
            attack(getDungeon()->getPlayer());
        
        //else if the monster is to the right of the player
        else if(c>0)
        {
            if(canMove(getRow(), getCol()-1))
                setCol(getCol()-1);
            //if can't move left, move up or down
            else if(r<0 && canMove(getRow()+1, getCol()))
                setRow(getRow()+1);
            else if(r>0 && canMove(getRow()-1, getCol()))
                setRow(getRow()-1);
        }
        else if(c<0)
        {
            if(canMove(getRow(), getCol()+1))
                setCol(getCol()+1);
            else if(r<0 && canMove(getRow()+1, getCol()))
                setRow(getRow()+1);
            else if(r>0 && canMove(getRow()-1, getCol()))
                setRow(getRow()-1);
        }
        else // c==0
        {
            if(r>0 && canMove(getRow()+1, getCol()))
                setRow(getRow()+1);
            else if(r<0 && canMove(getRow()-1, getCol()))
                setRow(getRow()-1);
        }
    } // end of if(canSmell())
    else if(getSleep()>=1)
        setSleep(getSleep()-1);
}

Monster::~Monster()
{}

bool Monster::canSmell()
{
    return false;
}

/*===================*/
/*============BOGEYMAN=============*/
/*===================*/

Bogeyman::Bogeyman(Dungeon* dp, int r, int c):Monster(dp, r, c)
{
    setType('B');
    setDext(randInt(2, 3));
    setHitPoint(randInt(5, 10));
    setWeapon(new ShortSword(r,c));
    setArmor(2);
    setStrength(randInt(2, 3));
    setName("the bogeymen");
}

bool Bogeyman::canSmell() 
{
    int r = abs(getRow()-getDungeon()->getPlayer()->getRow());
    int c = abs(getCol()-getDungeon()->getPlayer()->getCol());
    
    return r+c <=5;
}

void Bogeyman::drop()
{
    //check if there already exists a game object below the monster
    if(canDropHere()) 
    {
        if(trueWithProbability(0.1))
        {
            getDungeon()->m_objects.push_back(new MagicAxe(getRow(), getCol()));
        }
    }
}

/*===================*/
/*============SNAKEWOMAN=============*/
/*===================*/

SnakeWoman::SnakeWoman(Dungeon* dp, int r, int c):Monster(dp, r, c)
{
    setType('S');
    setHitPoint(randInt(3, 6));
    setWeapon(new MagicFang(r,c)); 
    setStrength(2);
    setDext(3);
    setArmor(3);
    setName("the snakewoman");
}

bool SnakeWoman::canSmell()
{
    int r = abs(getRow()-getDungeon()->getPlayer()->getRow());
    int c = abs(getCol()-getDungeon()->getPlayer()->getCol());
    
    return r+c <=3;
}

void SnakeWoman::drop()
{
    if (canDropHere()) {
        if(trueWithProbability(1/3))
        {
            getDungeon()->m_objects.push_back(new MagicFang(getRow(), getCol())); 
        }
    }
}

void SnakeWoman::attack(Player *p)
{
    if(getSleep()<=0)
    {
        /*
         attackerPoints = attackerDexterity + weaponDexterityBonus;
         defenderPoints = defenderDexterity + defenderArmorPoints;
         if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
             attacker has hit defender
         */
        int attacker = getDext()+getWeapon()->getDext();
        int defender = p->getDext()+p->getArmor();
        if(randInt(1, attacker)>=randInt(1, defender))
        {
            p->setHitPoint(p->getHit()-randInt(0, getStrength()+getWeapon()->getDamage()-1));
            // In addition to the regular hit point damage magic fangs of sleep do when the attacker hits the defender,
            // there is a 1 in 5 chance that the magic fangs of sleep will put the defender to sleep.
            if(trueWithProbability(0.2))
            {
                getDungeon()->getPlayer()->setSleep(randInt(2, 6));
                getDungeon()->m_message.push_back(getName()+' '+getWeapon()->getAction()+" the player and hits, putting the player to sleep.");
            }
            else
            {
                getDungeon()->m_message.push_back(getName()+' '+getWeapon()->getAction()+" the player and hits.");
            }
        }
        else //the snakewoman did not hit the player
        {
            getDungeon()->m_message.push_back(getName()+' '+getWeapon()->getAction()+" the Player and misses.");
        }
    }
    else
        setSleep(getSleep()-1);
    
}

/*===================*/
/*============DRAGON=============*/
/*===================*/

Dragon::Dragon(Dungeon* dp, int r, int c):Monster(dp, r, c)
{
    setType('D');
    setHitPoint(randInt(20, 25));
    setWeapon(new LongSword(r,c));
    setStrength(4);
    setDext(4);
    setArmor(4);
    setName("the dragon");
}

void Dragon::drop()
{
    if(canDropHere())
    {
        int temp = randInt(0, 5);
        switch (temp) {
            case 0:
                getDungeon()->m_objects.push_back(new Scroll("scroll of teleportation", getRow(), getCol()));
                break;
            case 1:
                getDungeon()->m_objects.push_back(new Scroll("scroll of strength", getRow(), getCol()));
                break;
            case 2:
                getDungeon()->m_objects.push_back(new Scroll("scroll of enhance armor", getRow(), getCol()));
                break;
            case 3:
                getDungeon()->m_objects.push_back(new Scroll("scroll of enhance health", getRow(), getCol()));
                break;
            default:
                getDungeon()->m_objects.push_back(new Scroll("scroll of enhance dexterity", getRow(), getCol()));
                break;
        }
    }
}

void Dragon::move()
{
    if(trueWithProbability(0.1) && getHit()<m_initial_hit)
        setHitPoint(getHit()+1);
    int r = getRow()-getDungeon()->getPlayer()->getRow();
    int c =getCol()-getDungeon()->getPlayer()->getCol();
    if((r==0 && c==1) || (r==0 && c==-1) || (r==1 && c==0) || (r==-1 && c==0))
        attack(getDungeon()->getPlayer());
}

/*===================*/
/*============GOBLIN=============*/
/*===================*/

Goblin::Goblin(Dungeon* dp, int r, int c, int dist):Monster(dp, r, c)
{
    setType('G');
    setHitPoint(randInt(15, 20));
    setWeapon(new ShortSword(r,c));
    setStrength(3);
    setDext(1);
    setArmor(1);
    setName("the goblin");
    m_smell_dist=dist;
}

//sr is the starting row; sc is the starting column; er is the ending row; rc is the ending col.
//n is the depth of this recursion.
//check is a two dimensional array. When passed to this function, every entry of check should be set to false.
//when calling this function, need to set n=0.
// note for myself: whenever a path is not valid (too long for the monster to smell or no empty space), return m_smell_distance
int Goblin::smartMove(int sr, int sc, int er, int ec, int n, bool check[18][70])
{
    //originially I let the function return 0 if the starting position is equal to the ending position, but the monster "reaching" the player means they are next to each other istead of staying at the same position, so I let the function return -1 if starting position is the same as the ending position.
    if(sr == er && sc == ec)
        return -1;
    
    // if the depth of the current search exceeds the goblin's smell distance, return the smell distance so that this path won't be checked later
    if(n > m_smell_dist )
        return m_smell_dist;
    
    // mark the current position as checked
    check[sr][sc] = true;
    
    // the four ints means the length of the optimal path if the goblin moves in that position
    // I set the initial values of the four variables to be the goblin small distance because if the goblin cannot move in a certain direction, then make no change to the number to indicate that the path is not feasible.
    int down=m_smell_dist, up=m_smell_dist, right=m_smell_dist, left=m_smell_dist;
    
    // The if statements checks if we can find a path in one of the directions and if that direction has been chcked already
    // I chose to check canMove first to make sure the code does not go out of bound.
    if(canMove(sr + 1, sc) && check[sr + 1][sc] == false)
        down = 1 + smartMove(sr + 1, sc, er, ec, n + 1, check);
    if(canMove(sr - 1, sc) && check[sr - 1][sc] == false)
        up = 1 + smartMove(sr - 1, sc, er, ec, n + 1, check);
    if(canMove(sr, sc + 1) && check[sr][sc + 1] == false)
        right = 1 + smartMove(sr, sc + 1, er, ec, n + 1, check);
    if(canMove(sr, sc - 1) && check[sr][sc - 1] == false)
        left = 1 + smartMove(sr, sc - 1, er, ec, n + 1, check);
    // Now, the four variables either = the length of the optimal paths from four directions, or = goblin smell distance meaning that the path is not feasible.
    
    // mark the current position as not visited
    check[sr][sc] = false;
    
    // the possibility that the monster will move only exists in the first call of this recursion,
    // because otherwise the monster will probably move multuple times in one turn.
    // so we need to check the depth of the current recurssive call.
    if(n==0)
    {
        if(down < m_smell_dist && down <= up && down <= right && down <= left)
            setRow(getRow()+1);
        else if(up < m_smell_dist && down <= right&& up <= left)
            setRow(getRow()-1);
        else if(right < m_smell_dist && right <= left)
            setCol(getCol()+1);
        else if(left < m_smell_dist)
            setCol(getCol()-1);
    }
    else // not the first function call, return the shorted distance so far 
    {
        int temp1 = min(down, up);
        int temp2 = min(right, left);
        return min(temp1, temp2); // return the length of the shortest path among the four
    }
    return m_smell_dist;
}

void Goblin::drop()
{
    if(canDropHere())
    {
        if(trueWithProbability(1/3))
        {
            if(trueWithProbability(0.5))
                getDungeon()->m_objects.push_back(new MagicAxe(getRow(), getCol()));
            else
                getDungeon()->m_objects.push_back((new MagicFang(getRow(), getCol())));
        }
    }
}

//goblin moves in a special way
void Goblin::move()
{
    if(getSleep()<=0)
    {
        //attack if possible
        int r = getRow()-getDungeon()->getPlayer()->getRow();
        int c =getCol()-getDungeon()->getPlayer()->getCol();
        if ((r==0 && c==1) || (r==0 && c==-1) || (r==1 && c==0) || (r==-1 && c==0))
            attack(getDungeon()->getPlayer());
        //if not, move
        else
        {
            int r1 = getRow();
            int c1 = getCol();
            bool check[18][70]={0};
            smartMove(r1, c1, getDungeon()->getPlayer()->getRow(), getDungeon()->getPlayer()->getCol(), 0, check);
        }
    }
    else
    {
        setSleep(getSleep()-1);
    }
}
