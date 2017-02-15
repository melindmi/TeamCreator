#include "teambuilder.h"
#include <stdexcept>
#include <iostream>
#include "exceptionmacros.h"

void TeamBuilder::setAllAthletes(std::vector<Athlete> iAllAthletes)
{
    allAthletes = iAllAthletes;
}

std::vector<Athlete> TeamBuilder::getAllAthletes()
{
  return allAthletes;
}

void TeamBuilder::setPositionsMap(std::map<std::string, int> iPositions)
{
  positions = iPositions;
}

std::map<std::string, int> TeamBuilder::getPositionsMap()
{
  return positions;
}

int TeamBuilder::getMaxPlayers()
{
  return maxPlayers;
}

void TeamBuilder::setMaxPlayers(int iMax)
{
    maxPlayers = iMax;
}

bool TeamBuilder::isEligible(Athlete iAthleteInfo)
{
  return ((positions[iAthleteInfo.getPosition()] > 0) 
                        && (!iAthleteInfo.getIsInjured()));
}

void TeamBuilder::createRugbyTeam(RugbyTeam& ioTeam)
{
  size_t i = 0;
  int nbPlayers = 0;
  while((nbPlayers < maxPlayers) && (i < allAthletes.size()) )
  {
    if(isEligible(allAthletes[i]))
    { 
        ioTeam.addPlayer(allAthletes[i]);
        positions[allAthletes[i].getPosition()]--;
        ++nbPlayers;
    }
    ++i;
  }
  
  if(nbPlayers < maxPlayers)
  {
    throw EXCEPTION("Unable to create a full team!");
  }
}

