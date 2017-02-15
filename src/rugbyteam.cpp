#include "rugbyteam.h"

#include <iostream>
//////////////////////////////
// RugbyTeam
/////////////////////////////

void RugbyTeam::addPlayer(Athlete iPlayer)
{
  athletes.push_back(iPlayer);  
}

std::vector<Athlete> RugbyTeam::getPlayers()
{
    return athletes;
}



