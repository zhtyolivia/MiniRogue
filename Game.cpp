// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance):m_dungeon(goblinSmellDistance)
{
    m_dungeon.displayGrid("");
}

void Game::play()
{
    cout << "Press q to exit game." << endl;
    char c = getCharacter();
    while(c!='q')
    {
        //player is dead?
        if(m_dungeon.getPlayer()->getHit()<=0)
        {
            cout<<"You lose"<<endl;
            break;
        }
        
        //player want to descend to next level?
        if(c=='>')
        {
            if(m_dungeon.getPlayer()->getRow()==m_dungeon.getStair().row && m_dungeon.getPlayer()->getCol()==m_dungeon.getStair().col)
                m_dungeon.nextLevel();
        }
        
        //palyer want to see the inventory?
        if(c == 'i')
        {
            m_dungeon.getPlayer()->printInventory();
        }
        if(c=='w')
        {
            m_dungeon.getPlayer()->printInventory();
            m_dungeon.getPlayer()->changeWeapon();
        }
        if(c=='r')
        {
            m_dungeon.getPlayer()->printInventory();
            m_dungeon.getPlayer()->read();
        }
        
        //player want to pick up an object?
        if(c=='g')
        {
            m_dungeon.getPlayer()->pickUp();
        }
        
        
        
        //palyer want to move?
        if(c==ARROW_RIGHT || c==ARROW_LEFT || c==ARROW_DOWN || c==ARROW_UP)
        {
            m_dungeon.getPlayer()->move(c);
            for(int i=0; i<m_dungeon.m_monsters.size(); i++)
            {
                m_dungeon.m_monsters[i]->move();
            }
        }
        //player wins?
        if(m_dungeon.getPlayer()->getRow()==m_dungeon.getIdol().row && m_dungeon.getPlayer()->getCol()==m_dungeon.getIdol().col)
        {
            m_dungeon.displayGrid("");
            cout<<"Congratulations, you won!"<<endl;
            break;
        }
        
        //cheat??
        else if(c=='c')
        {
            m_dungeon.getPlayer()->setStrength(9);
            m_dungeon.getPlayer()->setMaxHit(50);
            m_dungeon.getPlayer()->setHitPoint(50);
        }
        
        
        
    
        
        //print the grid
        m_dungeon.displayGrid("");
        
        c = getCharacter();
        
    }
    
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
