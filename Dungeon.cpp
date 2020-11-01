//
//  Dungeon.cpp
//  project 3.2
//
//  Created by Olivia on 5/17/20.
//  Copyright © 2020 Olivia. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "utilities.h"
#include "Dungeon.h"

using namespace std;

//checked
Dungeon::Dungeon(int goblinSmellDistance)
{
    m_goblin_smell_distance=goblinSmellDistance;
    m_level=0;
    
    generateRoomsAndCorridors();
    
    updateGameGrid();
    
    m_stairs=randCoord();
    m_idol=Coord(0,0);
    
    Coord player_coord = randCoord();
    addPlayer(player_coord.row, player_coord.col);
    
    addMonster();
    addGameObjects();
}



bool Dungeon::roomsOverlap(Room r1, Room r2) const
{
    // if there is no space between rooms horizontally, rooms overlap
    if (r1.topLeft.col > r2.botmRight.col + 1 || r2.topLeft.col > r1.botmRight.col + 1)
        return false;
    
    // if there is no space between rooms vertically, rooms overlap
    if (r1.topLeft.row > r2.botmRight.row + 1 || r2.topLeft.row > r1.botmRight.row + 1)
        return false;
    
    return true;
}

bool compare(const Room& r1, const Room& r2) 
{
    return r1.topLeft.col<r2.topLeft.col;
}

//generate rooms and corridors, record the empty spaces into m_empty vector
void Dungeon::generateRoomsAndCorridors()
{
    //initializing m_grid 
    for(int i=0; i<18; i++)
        for(int j=0; j<70; j++)
            m_grid[i][j]='#';
    
    std::vector<Room> room_vec;
    int count = 0;
    int length, height;
    while(count<5)
    {
        Room temp_room;
        //randomly generate the size of the room
        length=randInt(6, 16);
        height=randInt(3, 7);
        //randomly generate the position of the room
        temp_room.topLeft.col = randInt(1, 68-length);
        temp_room.topLeft.row = randInt(1, 16-height);
        temp_room.topRight.row=temp_room.topLeft.row;
        temp_room.topRight.col=temp_room.topLeft.col+length-1;
        temp_room.botmLeft.row=temp_room.topLeft.row+height-1;
        temp_room.botmLeft.col=temp_room.topLeft.col;
        temp_room.botmRight.row=temp_room.botmLeft.row;
        temp_room.botmRight.col=temp_room.topRight.col;
        
        //check if the newly generate room is apart from the already existing rooms
        bool overlap=false;
        for(int i=0; i<room_vec.size(); i++)
        {
            if(roomsOverlap(temp_room, room_vec[i]))
                overlap=true;
        }
        
        //if the new room is apart from the previous rooms, record the position of the room
        if(!overlap)
        {
            room_vec.push_back(temp_room);
            count++;
            for (int r = temp_room.topLeft.row; r <= temp_room.botmLeft.row; r++)
                for (int c = temp_room.topLeft.col; c <= temp_room.topRight.col; c++)
                    m_grid[r][c] = ' ';
        }
    }
    
    //arranging the rooms from left to right
    std::sort(room_vec.begin(), room_vec.end(), compare);
    
    //randomly generate four corridors
    for(int i=0; i<4; i++)
    {
        
        Room left_room, right_room;
        Coord start, turn, end;
        
        left_room=room_vec[i];
        right_room=room_vec[i+1];
        
        //two situations:
        //1: there is a path from the right edge of the left room to the right room
        //2: there is a path from the top/bottom edge of the left room to the left room
        
        //case 1: start from the right edge of the left room
        if(left_room.botmRight.col<=right_room.topRight.col)
        {
            //generate start from the right edge of the left room
            start.col=left_room.topRight.col;
            start.row=randInt(left_room.topRight.row, left_room.botmRight.row);
            
            //then the row of the turning point equals the row of the starting point
            turn.row=start.row;
            
            //case 1.1:
            //if there is a horizontal path from the starting point to the right room, then don't make a turn
            if(start.row>=right_room.topLeft.row && start.row<=right_room.botmLeft.row)
            {
                end.col=right_room.topLeft.col;
                //mark these positions as room
                for(int i=start.col; i<=end.col;i++)
                    m_grid[start.row][i]=' ';
            }
            
            //case 1.2:
            //need to make a turn to reach the right room
            else
            {

                int temp;

                if(left_room.topRight.col>right_room.topLeft.col)
                    temp=left_room.topRight.col;
                else
                    temp=right_room.topLeft.col;

                end.col=1+randInt(temp, right_room.topRight.col);
                turn.col=end.col;

                if(start.row>right_room.botmRight.row)
                    end.row=right_room.botmLeft.row;
                else
                    end.row=right_room.topLeft.row;

                for(int i=start.col; i<=turn.col; i++)
                    m_grid[start.row][i]=' ';
                
                if(end.row>turn.row)
                {
                    for(int i=turn.row; i<=end.row; i++)
                        m_grid[i][turn.col]=' ';
                }

                else{
                    for(int i=end.row; i<=turn.row; i++)
                        m_grid[i][turn.col]=' ';
                }
            }
        }
        
        //case 2: start from the rop/bottom of the left room to the bottom/top of the right room
        else{
            if(left_room.botmRight.row>right_room.topLeft.row)
            {
                end.row=left_room.botmRight.row;
                start.row=right_room.topLeft.row;
            }
            else{
                start.row=left_room.topLeft.row;
                end.row=right_room.botmLeft.row;
            }
            start.col=randInt(right_room.topLeft.col, right_room.topRight.col);
            for(int i=start.row; i<=end.row; i++)
                m_grid[i][start.col]=' ';
        }
    }
    
    //record the empty space
    for(int i=0; i<18; i++)
    {
        for(int j=0; j<70; j++)
        {
            if(m_grid[i][j]==' ')
                m_empty.push_back(Coord(i,j));
            else
                m_grid[i][j]='#';
        }
    }
}//end of generateRoomsAndCorridors()

void Dungeon::addPlayer(int r, int c)
{
    m_player = new Player(this, r, c);
}

Coord Dungeon::randCoord()
{
    //randomly choose a coord from the m_empty vector
    int x = randInt(0, (int)m_empty.size()-1);
    Coord temp = m_empty[x];
    
    //delete the coord from m_empty
    for (vector<Coord> :: iterator i = m_empty.begin(); i != m_empty.end(); i++)
    {
        if(i->row==temp.row && i->col==temp.col)
        {
            m_empty.erase(i);
            break;
        }
    }
    return temp;
}

Monster* Dungeon::randAMonster()
{
    //generate a random position of the monster
    Coord x = randCoord();
    Monster* temp = nullptr;
    
    //generate a monster based on which level the player is on
    int rand;
    
    if(m_level<=1)
    {
        rand=randInt(0, 1);
        switch (rand) {
            case 0:
                temp = new SnakeWoman(this, x.row, x.col);
                break;
            case 1:
                temp = new Goblin(this, x.row, x.col,m_goblin_smell_distance);
                break;
        }
    }
    else if(m_level==2)
    {
        rand=randInt(0, 2);
        switch (rand) {
            case 0:
                temp = new SnakeWoman(this, x.row, x.col);
                break;
            case 1:
                temp = new Goblin(this, x.row, x.col,m_goblin_smell_distance);
                break;
            case 2:
                temp = new Bogeyman(this, x.row, x.col);
                break;
        }
    }
    else //m_level >= 3
    {
        rand=randInt(0,3);
        switch (rand) {
            case 0:
                temp = new SnakeWoman(this, x.row, x.col);
                break;
            case 1:
                temp = new Goblin(this, x.row, x.col,m_goblin_smell_distance);
                break;
            case 2:
                temp = new Bogeyman(this, x.row, x.col);
                break;
            default:
                temp = new Dragon(this, x.row ,x.col);
                break;
        }
    }
    return temp;
}

void Dungeon::addMonster()
{
    int count = randInt(2, 5*(m_level+1)+1);
    for(int i=0; i<count; i++)
        m_monsters.push_back(randAMonster());
}

GameObject* Dungeon::randGameObject()
{
    //randomly choose a coord from the m_empty vector
    Coord c = randCoord();
    
    GameObject* temp;
    
    int rand=randInt(0, 7);
    switch (rand)
    {
        case 0:
            temp = new Mace(c.row, c.col);
            break;
        case 1:
            temp = new ShortSword(c.row, c.col);
            break;
        case 2:
            temp = new LongSword(c.row, c.col);
            break;
        case 3:
            temp = new MagicAxe(c.row, c.col);
            break;
        case 4:
            temp = new Scroll("scroll of teleportation", c.row,c.col);
            break;
        case 5:
            temp = new Scroll("scroll of enhance health",c.row,c.col);
            break;
        case 6:
            temp = new Scroll("scroll of enhance dexterity", c.row,c.col);
            break;
        case 7:
            temp = new Scroll("scroll of raise strength", c.row,c.col);
            break;
        default:
            temp = new Scroll("scroll of improve armor", c.row,c.col);
            break;
    }
    return temp;
}

void Dungeon::addGameObjects()
{
    int num = randInt(2, 3);
    for(int i=1; i<=num; i++)
        m_objects.push_back(randGameObject());
}

void Dungeon::nextLevel()
{
    m_level++;
    
    m_empty.clear();
    
    for(vector<Monster*>::iterator it = m_monsters.begin(); it != m_monsters.end(); )
    {
        delete *it;
        it= m_monsters.erase(it);
    }
    
    for(vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end();)
    {
        delete *it;
        it = m_objects.erase(it);
    }
        
    generateRoomsAndCorridors();

    updateGameGrid();
    
    Coord player_coord = randCoord();
    m_player->setRow(player_coord.row);
    m_player->setCol(player_coord.col);
    
    addMonster();
    addGameObjects();
    
    m_stairs=randCoord();
    
    if(m_level==4)
        m_idol=randCoord();
}

Dungeon::~Dungeon()
{
    for(vector<GameObject*>::iterator it = m_objects.begin(); it != m_objects.end(); it++)
    {
        delete *it;
    }
    for(vector<Monster*>::iterator it = m_monsters.begin(); it != m_monsters.end(); it++)
    {
        delete *it;
    }
    delete m_player;
}

Monster* Dungeon::getMonster(int r, int c)
{
    for(vector<Monster*>::iterator it = m_monsters.begin(); it != m_monsters.end(); it++)
    {
        if((*it)->getRow()==r && (*it)->getCol()==c)
            return *it; 
    }
    return nullptr;
}

Coord Dungeon::getStair()
{
    return m_stairs;
}

Coord Dungeon::getIdol()
{
    return m_idol;
}

Player* Dungeon::getPlayer()
{
    return m_player;
}

//sets the gameGrid equal to the grid
void Dungeon::updateGameGrid()
{
    for ( int i = 0; i < 70; i++) {
        for ( int j = 0; j < 18; j++) {
            m_game_grid[j][i] = m_grid[j][i];
        }
    }
}

void Dungeon::fillGameGrid(){
    
    //add monsters and stairs to the gameGrid
    for (int i =0; i < m_monsters.size(); i++) {
        m_game_grid[m_monsters[i] -> getRow()][m_monsters[i] -> getCol()] = m_monsters[i]->getType();
    }
    m_game_grid[m_stairs.row][m_stairs.col] = STAIR;
    

}

//checked 
void Dungeon::displayGrid(string msg)
{
    clearScreen();
    cout << endl;
    
    //update and fill the gameGrid
    updateGameGrid();
    fillGameGrid();
    
    //add the items monsters and stairs to the grid first
    for (int i = 0; i < m_objects.size(); i++) {
        m_grid[m_objects[i]->row()][m_objects[i]->col()] = m_objects[i]->getType();
    }
    
    for (int i =0; i < m_monsters.size(); i++) {
        m_grid[m_monsters[i]->getRow()][m_monsters[i]->getCol()] = m_monsters[i]->getType();
    }
    
    if ( m_level < 4)
        m_grid[m_stairs.row][m_stairs.col] = STAIR;
    //only show the idol for level 4
    if (m_level == 4)
        m_grid[m_idol.row][m_idol.col] = GOLDEN_IDOL;
    for (int r = 0; r < 18; r++)
    {
        for (int c = 0; c < 70; c++){
            if (r == (m_player->getRow()) && c == m_player->getCol())
                cout << PLAYER;
            else
                cout << m_grid[r][c];
        }
        cout << endl;
    }
    //remove the monsters items and stairs from the grid after each display
    for (int i = 0; i < m_monsters.size(); i++) {
        m_grid[m_monsters[i] -> getRow()][m_monsters[i] -> getCol()] = ' ';
    }
    for (int i = 0; i< m_objects.size(); i++) {
        m_grid[m_objects[i]->row()][m_objects[i]->col()] = ' ';
    }
    
    m_grid[m_stairs.row][m_stairs.col] = ' ';
    
    //print out the players attributes each turn
    cout << "Dungeon Level: "<< m_level<<", Hit points: "<< m_player->getHit()<<", Armor: "<< m_player->getArmor()<<" Strength: "<<m_player->getStrength()<<", Dexterity: "<< m_player->getDext() <<endl;
    cout << endl;
    
    //print out all the actions that took place that turn
    for (vector<string> :: iterator s = m_message.begin(); s != m_message.end(); s++) {
        cout << *s << endl;
        s = m_message.erase(s);
        s--;
    }
}


