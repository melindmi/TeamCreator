#ifndef TEAMJSONWRITERH
#define TEAMJSONWRITERH

#include "athlete.h"
#include "rugbyteam.h"
#include <string> 
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"

class TeamJSONWriter
{
  std::string filename;
  
  //add one team player information in a rapidjson string buffer
  void addTeamPlayer(Athlete iAthleteInfo, rapidjson::PrettyWriter<rapidjson::StringBuffer>& ioWriter );
  
  //put the output in a file  
  void generateResultFile(std::string& iContent);  
   
  public: 
    TeamJSONWriter(std::string iFilename);

    //create a file with the team 
    void writeTeamJSON(RugbyTeam iTeam);
    
    //create a string with the team
    std::string writeTeamString(RugbyTeam iTeam); 
};


#endif
