//
//  Dungeon.hpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//



#ifndef Dungeon_hpp
#define Dungeon_hpp

#include<vector>
#include "Player.h"

#include "GameObject.h"
#include "Coord.h"
#include <stdio.h>
class Monster;

class Dungeon
{
public:
    Dungeon(int goblinSmellDistance);
    ~Dungeon();
    
    void nextLevel();
    Monster* getMonster(int r, int c);
    
    Coord getStair();
    Coord getIdol();
    Player* getPlayer();
    int getLevel();
    
    void displayGrid(std::string msg);
    
    
    std::vector<std::string> m_message;
    std::vector<GameObject*> m_objects;
    std::vector<Monster*> m_monsters;
    
    char m_game_grid[18][70];

    char m_grid[18][70];
    
    Coord randCoord();

    
private:
    
    //helper functions
    bool roomsOverlap(Room r1, Room r2) const;
    void generateRoomsAndCorridors();
    void addPlayer(int r, int c);
    Monster* randAMonster();
    void addMonster();
    GameObject* randGameObject();
    void addGameObjects();
    void fillGameGrid();
    void updateGameGrid();
    
    
    //symbols
    const char WALL = '#';
    const char PLAYER = '@';
    const char EMPTY = ' ';
    const char GOLDEN_IDOL = '&';
    const char STAIR = '>';
    const char WEdAPON = ')';
    const char SCROLL = '?';
    const char BOGEYMAN = 'B';
    const char SNAKEWOMAN = 'S';
    const char DRAGON = 'D';
    const char GOBLIN = 'G';
    
    //other member variables
    
    int m_level;
    int m_goblin_smell_distance;
    std::vector<Coord> m_empty;
    
    Player* m_player;
    
    Coord m_stairs;
    Coord m_idol;
    
    

};



bool compare(const Room& r1, const Room& r2);


#endif /* Dungeon_hpp */
