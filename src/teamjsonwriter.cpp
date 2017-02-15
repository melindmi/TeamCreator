#include "teamjsonwriter.h"

#include <fstream>

TeamJSONWriter::TeamJSONWriter(std::string iFilename) : filename(iFilename)
{
}

std::string TeamJSONWriter::writeTeamString(RugbyTeam iTeam)
{
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
  //Start the JSON object
  writer.StartObject();
  writer.Key("athletes");
  writer.StartArray();  
  
  std::vector<Athlete> teamAthletes = iTeam.getPlayers(); 
  for(size_t i=0; i<teamAthletes.size(); ++i)
  {
    addTeamPlayer(teamAthletes[i], writer);
  }

  writer.EndArray();
  writer.EndObject(); 

  return  buffer.GetString();
}

void TeamJSONWriter::writeTeamJSON(RugbyTeam iTeam)
{
  std::string team = writeTeamString(iTeam); 
  generateResultFile(team);
}

void TeamJSONWriter::addTeamPlayer(Athlete iAthleteInfo, rapidjson::PrettyWriter<rapidjson::StringBuffer>& ioWriter)
{
  
  ioWriter.StartObject();
  ioWriter.Key("name");
  ioWriter.String(iAthleteInfo.getName().c_str());
  ioWriter.Key("position");
  ioWriter.String(iAthleteInfo.getPosition().c_str());
  ioWriter.Key("squad_id");
  ioWriter.Int(iAthleteInfo.getSquadId());
  ioWriter.Key("squad_name");
  ioWriter.String(iAthleteInfo.getSquadName().c_str());
  ioWriter.EndObject();
}

void TeamJSONWriter::generateResultFile(std::string & iContent)
{
  std::ofstream outFile;
  outFile.open(filename.c_str());
  outFile << iContent;
  outFile.close(); 
}
