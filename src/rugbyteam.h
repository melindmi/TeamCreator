#ifndef RUGBYTEAMH
#define RUGBYTEAMH

#include "athlete.h"

#include <string>
#include <vector>
#include <map>

//Object storing the information related to a rugby team
class RugbyTeam 
{
  public:
    
    //add an athlete in the list of players for this team
    void addPlayer(Athlete iPlayer); 

    //get the list of players
    std::vector<Athlete> getPlayers();

  private:
    std::vector<Athlete> athletes;
};

#endif
