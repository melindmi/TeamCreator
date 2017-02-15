#include "teambuilder.h"
#include "athlete.h"
#include "athletesreader.h"
#include "teamjsonwriter.h"

#include <iostream>

int rugby_main(int argc, char** argv)
{
  // TODO: Take input / output from argv
  std::string inputFilename = "rugby_athletes.json";
  std::string outputFilename = "new_rugby_team.json";
      
  std::vector<Athlete> allAthletes; 
  
  //read the information on the athletes from the input file 
  AthletesReader reader(inputFilename);
  reader.getAllAthletesFromFile(allAthletes);
  
  //instantiate a team builder and set information on how the team should be
  //set all existing athelets
  //set the maximum number of players in the team
  //set the maximum number of players per position type  
  TeamBuilder teamBuilder;
  teamBuilder.setAllAthletes(allAthletes);
  
  teamBuilder.setMaxPlayers(15);
  std::map<std::string, int> positions;
  positions["prop"] = 2;
  positions["hooker"] = 1;
  positions["lock"] = 2;
  positions["flanker"] = 2;
  positions["number-eight"] = 1;
  positions["scrum-half"] = 1;
  positions["out-half"] = 1;
  positions["centre"] = 2;
  positions["winger"] = 2;
  positions["full-back"] = 1; 
  teamBuilder.setPositionsMap(positions);

  //create the rugby team
  RugbyTeam rugbyTeam;
  teamBuilder.createRugbyTeam(rugbyTeam);  
  
  //write the team in a JSON file
  TeamJSONWriter writer(outputFilename);
  writer.writeTeamJSON(rugbyTeam);

  return 0;
}

int main(int argc, char** argv)
{
  return rugby_main(argc, argv);
}
