#include "tests.h"
#include "athlete.h"
#include "athletesreader.h"
#include "teambuilder.h"
#include "teamjsonwriter.h"
#include <iostream>
#include <fstream>

#include "include/rapidjson/document.h" 

std::string jsonStr = "{ \"athletes\" : " 
"[ { \"name\" : \"Meagan Gill\" , "
"    \"position\" : \"prop\", "
"    \"squad_id\" : 0, "
"    \"is_injured\" : true }, " 
"{   \"name\" : \"Hillary Wiggins\" , "
"    \"position\" : \"full-back\", " 
"    \"squad_id\" : 1, " 
"    \"is_injured\" : false}, "
"{    \"name\" : \"Bright Hicks\" , "
"     \"position\" : \"centre\", " 
"     \"squad_id\" : 2, " 
"     \"is_injured\" : true }  ], " 
" \"squads\" :  "
" [ { \"name\" : \"Squad 0\", "
"     \"id\" : 0 }, "
"   { \"name\" : \"Squad 1\", "
"     \"id\" : 1 }, "
"   { \"name\" : \"Squad 2\", "
"     \"id\" : 2 } "
" ] }";

bool testSetGetAthleteName()
{
  Athlete a;
  a.setName("Toto");

  return (a.getName() == "Toto"); 
}

bool testSetGetAthletePosition()
{
  Athlete a;
  a.setPosition("prop");

  return (a.getPosition() == "prop");
}

bool testSetGetAthleteIsInjured()
{
  Athlete a;
  a.setIsInjured(false);

  return (!a.getIsInjured());
}

bool testSetGetAthleteCountry()
{
  Athlete a;
  a.setCountry("Romania");

  return (a.getCountry() == "Romania");
}

bool testSetGetAthleteId()
{
  Athlete a;
  a.setId(0);

  return (a.getId() == 0);
}

bool testSetGetAthleteSquadName()
{
  Athlete a;
  a.setSquadName("Test");

  return (a.getSquadName() == "Test");
}

bool testGetAllAthletesFromString()
{
  bool ret = true;
  AthletesReader ar;
  std::vector<Athlete> allAthletes;
  try
  {
    ar.getAllAthletesFromString(allAthletes, jsonStr); 
  }
  catch(...)
  {
    ret = false;
  }

  ret = ret && (allAthletes.size() == 3);
  ret = ret && (allAthletes[0].getName() == "Meagan Gill");
  ret = ret && (allAthletes[0].getSquadId() == 0);
  ret = ret && (allAthletes[1].getName() == "Hillary Wiggins");
  ret = ret && (allAthletes[1].getSquadId() == 1);
  ret = ret && (allAthletes[2].getName() == "Bright Hicks");
  ret = ret && (allAthletes[2].getSquadId() == 2);

  return ret;
}

bool testGetAllAthletesFromStringFailed()
{
  bool ret = true;
  AthletesReader ar;
  std::vector<Athlete> allAthletes;
  std::string str = "...";
  try
  {
    ar.getAllAthletesFromString(allAthletes, str); 
  }
  catch(...)
  {
    ret = false;
  }

  return !ret;
}

bool testGetAllAthletesFromFile()
{
  bool ret = true;
  AthletesReader ar;
  ar.setFilename("testdata/test.json");

  ret = ret && (ar.getFilename() == "testdata/test.json");

  std::vector<Athlete> allAthletes;

  ar.getAllAthletesFromFile(allAthletes); 

  ret = ret && (allAthletes.size() == 3);
  ret = ret && (allAthletes[0].getName() == "Meagan Gill");
  ret = ret && (allAthletes[0].getSquadId() == 1);
  ret = ret && (allAthletes[1].getName() == "Hillary Wiggins");
  ret = ret && (allAthletes[1].getSquadId() == 0);
  ret = ret && (allAthletes[2].getName() == "Bright Hicks");
  ret = ret && (allAthletes[2].getSquadId() == 9);

  return ret;
}

bool testGetSquadsInfo()
{
  bool ret = true;

  AthletesReader ar;
  rapidjson::Document document;
  document.Parse(jsonStr.c_str());
  const rapidjson::Value& squads = document["squads"];
  std::map<int, Squad> squadsMap = ar.getSquadsInfo(squads);

  ret = ret && (squadsMap[0].getId() == 0); 
  ret = ret && (squadsMap[0].getName() == "Squad 0"); 
  ret = ret && (squadsMap[1].getId() == 1); 
  ret = ret && (squadsMap[1].getName() == "Squad 1"); 
  ret = ret && (squadsMap[2].getId() == 2); 
  ret = ret && (squadsMap[2].getName() == "Squad 2"); 
  ret = ret && (squadsMap.size() == 3);
  return ret;
}

bool testIsEligibleYes()
{
  bool ret = true;

  Athlete a;
  a.setName("Thomas");
  a.setPosition("prop");
  a.setSquadId(3);
  a.setSquadName("Squand 3");
  a.setIsInjured(false);

  TeamBuilder tb;
  std::map<std::string, int> posMap;
  posMap["prop"] = 2;
  posMap["centre"] = 1;
  tb.setPositionsMap(posMap);
  tb.setMaxPlayers(3);

  ret = ret && (tb.isEligible(a));

  return ret;    
}

bool testIsEligibleNo()
{
  bool ret = true;

  Athlete a;
  a.setName("Thomas");
  a.setPosition("prop");
  a.setSquadId(3);
  a.setSquadName("Squand 3");
  a.setIsInjured(true);

  TeamBuilder tb;
  std::map<std::string, int> posMap;
  posMap["prop"] = 2;
  posMap["centre"] = 1;
  tb.setPositionsMap(posMap);
  tb.setMaxPlayers(3);

  ret = ret && (!tb.isEligible(a));

  return ret;    
}

bool testWriteTeamString()
{
  bool ret = true;

  RugbyTeam team;
  Athlete a;
  a.setName("Thomas");
  a.setPosition("prop");
  a.setSquadId(3);
  a.setSquadName("Squand 3");
  a.setIsInjured(false);
  team.addPlayer(a);

  TeamJSONWriter tjw("output.json");
  std::string teamStr = tjw.writeTeamString(team);

  ret = ret && (!teamStr.empty());
  std::string tstr = "{\n"
    "    \"athletes\": [\n"
    "        {\n"
    "            \"name\": \"Thomas\",\n"
    "            \"position\": \"prop\",\n"
    "            \"squad_id\": 3,\n"
    "            \"squad_name\": \"Squand 3\"\n"
    "        }\n"
    "    ]\n"
    "}" ;

  ret = ret && (teamStr == tstr);
  return ret;
}

bool testWriteTeamJSON()
{
  bool ret = true;

  RugbyTeam team;
  Athlete a;
  a.setName("Thomas");
  a.setPosition("prop");
  a.setSquadId(3);
  a.setSquadName("Squand 3");
  a.setIsInjured(false);
  team.addPlayer(a);

  std::string filename = "testdata/output.json";
  TeamJSONWriter tjw(filename);
  tjw.writeTeamJSON(team);

  std::ifstream json_file(filename.c_str());
  std::string content;
  try
  {
    content = (std::string( (std::istreambuf_iterator<char>(json_file)), (std::istreambuf_iterator<char>()) ));
  }
  catch(...)
  {
    ret = false;
  }

  std::string tstr = "{\n"
    "    \"athletes\": [\n"
    "        {\n"
    "            \"name\": \"Thomas\",\n"
    "            \"position\": \"prop\",\n"
    "            \"squad_id\": 3,\n"
    "            \"squad_name\": \"Squand 3\"\n"
    "        }\n"
    "    ]\n"
    "}" ;

  ret = ret && (content == tstr);

  return ret;
}

bool testCreateRugbyTeamFailed()
{
  TeamBuilder builder;
  std::map<std::string , int> teamMap;
  teamMap["prop"] = 2;
  teamMap["centre"] = 1;
  builder.setPositionsMap(teamMap);
  builder.setMaxPlayers(3);

  Athlete a;
  std::vector<Athlete> allAthletes;
  allAthletes.push_back(a);

  builder.setAllAthletes(allAthletes);
  RugbyTeam team;

  try
  {  
    builder.createRugbyTeam(team);
  }
  catch(...)
  {
    //exception because there are not enough players
    return true; 
  }

  return false;
}

bool testCreateRugbyTeamOk()
{
  bool ret = true;

  TeamBuilder builder;
  std::map<std::string , int> teamMap;
  teamMap["prop"] = 2;
  teamMap["centre"] = 1;
  builder.setPositionsMap(teamMap);
  builder.setMaxPlayers(3);

  Athlete a;
  a.setName("Thomas");
  a.setPosition("prop");
  a.setSquadId(3);
  a.setSquadName("Squand 3");
  a.setIsInjured(false);

  Athlete b;
  b.setName("Erik");
  b.setPosition("prop");
  b.setSquadId(2);
  b.setSquadName("Squand 2");
  b.setIsInjured(false);

  Athlete c;
  c.setName("Test");
  c.setPosition("centre");
  c.setSquadId(2);
  c.setSquadName("Squand 2");
  c.setIsInjured(false);

  std::vector<Athlete> allAthletes;
  allAthletes.push_back(a);
  allAthletes.push_back(b);
  allAthletes.push_back(c);

  builder.setAllAthletes(allAthletes);
  RugbyTeam team;

  try
  {  
    builder.createRugbyTeam(team);
  }
  catch(...)
  {
    ret = false; 
  }
  //check the positions map
  teamMap = builder.getPositionsMap();
  std::map<std::string, int>::iterator it;
  for(it = teamMap.begin(); it!=teamMap.end(); ++it)
  {
    if(it->second != 0)  //if the position was not completely filled
      ret = false;
  }

  return ret;
}

bool testGetAllAthletes()
{
  bool ret = true; 

  TeamBuilder builder;
  Athlete a, b, c;
  std::vector<Athlete> allAthletes;
  allAthletes.push_back(a);
  allAthletes.push_back(b);
  allAthletes.push_back(c);

  builder.setAllAthletes(allAthletes);
  ret = ret && (builder.getAllAthletes().size() == 3);

  return ret;
}

bool testGetMaxPlayers()
{
  bool ret = true;
  TeamBuilder builder;
  builder.setMaxPlayers(5);

  ret = ret && (builder.getMaxPlayers() == 5);

  return ret;
}

int main()
{
  // TODO: Use a test suite library (like gtest)
  std::cout << "testSetGetAthleteName: "<<(testSetGetAthleteName() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testSetGetAthletePosition: "<<(testSetGetAthletePosition() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testSetGetAthleteIsInjured: "<<(testSetGetAthleteIsInjured() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testSetGetAthleteCountry: "<<(testSetGetAthleteCountry() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testSetGetAthleteId: "<<(testSetGetAthleteId() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testSetGetAthleteSquadName: "<<(testSetGetAthleteSquadName() ? "OK" : "FAILED") <<std::endl; 
  std::cout << "testGetAllAthletesFromString: "<< (testGetAllAthletesFromString() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testGetAllAthletesFromStringFailed: "<< (testGetAllAthletesFromStringFailed() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testGetAllAthletesFromFile: "<< (testGetAllAthletesFromFile() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testGetSquadsInfo: "<< (testGetSquadsInfo() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testIsEligibleYes: "<< (testIsEligibleYes() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testIsEligibleNo: "<< (testIsEligibleNo() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testWriteTeamString: "<< (testWriteTeamString() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testWriteTeamJSON: "<< (testWriteTeamJSON() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testCreateRugbyTeamFailed: "<< (testCreateRugbyTeamFailed() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testCreateRugbyTeamOk: "<< (testCreateRugbyTeamOk() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testGetAllAthletes: "<< (testGetAllAthletes() ? "OK": "FAILED") <<std::endl; 
  std::cout << "testMaxPlayers: "<< (testGetMaxPlayers() ? "OK": "FAILED") <<std::endl; 

  return 0;
}
