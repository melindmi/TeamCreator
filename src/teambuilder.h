#ifndef TEAMBUILDERH
#define TEAMBUILDERH

#include "athlete.h"
#include "rugbyteam.h"

#include <string>
#include <vector>

//Object storing the logic for the team creation
class TeamBuilder
{
  public:
    //check if an athlete is eligible to be part of the team
    bool isEligible(Athlete iAthleteInfo);
    
    //set the vector with all the athletes 
    void setAllAthletes(std::vector<Athlete> iAllAthletes);
    
    //get a vector with all the athletes
    std::vector<Athlete> getAllAthletes();
  
    //set the maximum number of players
    void setMaxPlayers(int iMax);

    //get the maximum number of players
    int getMaxPlayers();
    
    //set the map storing the number of players per position type
    void setPositionsMap(std::map<std::string, int> iPositions);

    //get the map storing the number of players per position type
    std::map<std::string, int> getPositionsMap();
    
    //create a rugby team from a vector of available athletes  
    //by checking if the constraints are respected 
    //Throw if unable to create a full team 
    void createRugbyTeam(RugbyTeam& ioTeam);
    
  private:
    std::vector<Athlete> allAthletes;
    std::map<std::string, int> positions;
    int maxPlayers;
};


#endif


