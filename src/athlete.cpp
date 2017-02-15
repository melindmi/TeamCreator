#include "athlete.h"

#include <iostream>
///////////////////////////////
// Athlete
//////////////////////////////
std::string Athlete::getName()
{
  return name;
}

void Athlete::setName(std::string iName)
{
  name = iName;
}

std::string Athlete::getCountry()
{
  return country;
}

void Athlete::setCountry(std::string iCountry)
{
  country = iCountry;
}

std::string Athlete::getPosition()
{
  return position;
}

void Athlete::setPosition(std::string iPos)
{
  position = iPos;
}

int Athlete::getId()
{
  return id;
}

void Athlete::setId(int iId)
{
  id = iId;
}

bool Athlete::getIsInjured()
{
  return isInjured;
}

void Athlete::setIsInjured(bool iIsInjured)
{
  isInjured = iIsInjured;
}

std::string Athlete::getSquadName()
{
  return squadName;
}

void Athlete::setSquadName(std::string iSquad)
{
  squadName = iSquad;
}

int Athlete::getSquadId()
{
  return squadId;
}

void Athlete::setSquadId(int iSquadId)
{
  squadId = iSquadId;
}



