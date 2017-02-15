#include "athletesreader.h"

#include <streambuf>
#include <fstream>
#include <iostream>
#include "exceptionmacros.h"

AthletesReader::AthletesReader()
{
}

AthletesReader::AthletesReader(std::string iFilename) : filename(iFilename)
{
}

AthletesReader::~AthletesReader()
{}

void AthletesReader::setFilename(std::string iFilename)
{
  filename = iFilename;
}

std::string AthletesReader::getFilename()
{
  return filename;
}

std::string AthletesReader::convertFileToString()
{
  std::string retStr;
  std::ifstream json_file(filename.c_str());
  if(json_file)
  {
    try
    {
      //construct using 2 iterators: one from the begining and one from the end
      retStr = (std::string( (std::istreambuf_iterator<char>(json_file)), (std::istreambuf_iterator<char>()) ));
    }
    catch(...)
    {
      throw EXCEPTION("Error converting the file into string!");
    }
  }
  return retStr;
}

void AthletesReader::getAllAthletesFromString(std::vector<Athlete>& ioAllAthletes, std::string iAthletesStr)
{
  //create a document object from a string
  rapidjson::Document document;
  try
  { 
    document.Parse(iAthletesStr.c_str());
  }
  catch(...)
  {
    throw EXCEPTION("Error parsing the input string!");
  } 

  if(document.IsObject())
  {
    try
    {
      if(document.HasMember("athletes") && document.HasMember("squads"))
      {
        //parse the json member "athletes"
        const rapidjson::Value& athletes = document["athletes"];
        const rapidjson::Value& squads = document["squads"];
        if(athletes.IsArray())
        {
          if(squads.IsArray())
          {
            std::map<int, Squad> squadsMap = getSquadsInfo(squads);
            for(rapidjson::SizeType i = 0; i <  athletes.Size(); ++i)
            {
              const rapidjson::Value& athleteInfo = athletes[i]; 
              Athlete newAthlete;
              //if the information on the athlete has been found
              if(getAthleteInfo(athleteInfo, newAthlete)); 
              { 
                //add the squad related information for this athlete
                std::string sqName = squadsMap[newAthlete.getSquadId()].getName();
                if(!sqName.empty())
                {
                  newAthlete.setSquadName(sqName);
                  
                  //push the athlete to the vector
                  ioAllAthletes.push_back(newAthlete);
                }
                else
                {
                  throw EXCEPTION("Unable to find the squad name for the squad id");
                }
              }
            }
          }
          else
          {
            throw EXCEPTION("The member squads is not an array! ");
          }
        }
        else
        {
          throw EXCEPTION("The member athletes is not an array! ");
        }
      }
      else
      {
        throw EXCEPTION("Has no members athletes and/or squads! ");
      }
    }
    catch(...)
    {
      throw EXCEPTION("Error getting the athletes info!");
    }
  }
  else
  {
    throw EXCEPTION("The file is not a valid JSON file!");
  }

}

void AthletesReader::getAllAthletesFromFile(std::vector<Athlete>& ioAllAthletes)
{
  std::string athletesStr = convertFileToString();

  getAllAthletesFromString(ioAllAthletes, athletesStr); 
}

bool AthletesReader::getFieldAsString(const rapidjson::Value& iAthleteInfo, std::string iFieldName, std::string& oFieldValue)
{
    if(iAthleteInfo.HasMember(iFieldName.c_str()) 
                  && iAthleteInfo[iFieldName.c_str()].IsString())
    {
      oFieldValue = iAthleteInfo[iFieldName.c_str()].GetString();
    }
    else
    {
      return false;
    }
  return true;
}

bool AthletesReader::getFieldAsInt(const rapidjson::Value& iAthleteInfo, std::string iFieldName, int& oFieldValue)
{
    if(iAthleteInfo.HasMember(iFieldName.c_str()) && 
              iAthleteInfo[iFieldName.c_str()].IsInt())
    {
      oFieldValue = iAthleteInfo[iFieldName.c_str()].GetInt();
    }
    else
    {
      return false;
    }
  return true;
}

bool AthletesReader::getFieldAsBool(const rapidjson::Value& iAthleteInfo, std::string iFieldName, bool& oFieldValue)
{
    if(iAthleteInfo.HasMember(iFieldName.c_str()) && 
                iAthleteInfo[iFieldName.c_str()].IsBool())
    {
      oFieldValue = iAthleteInfo[iFieldName.c_str()].GetBool();
    }
    else
    {
      return false;
    }
  return true;
}

bool AthletesReader::getAthleteInfo(const rapidjson::Value& iAthleteInfo, Athlete& oNewAthlete)
{
  //local object for Athlete
  Athlete newAthlete;
  //the name, the position, the squad id and squad name of the athlete are mandatory
  //if they are missing the athlete will not be considered valid
  try
  {
    std::string aStrValue;
    if(getFieldAsString(iAthleteInfo, "name", aStrValue))
    {
        newAthlete.setName(aStrValue);
    }
    else 
       return false;

    if(getFieldAsString(iAthleteInfo, "country", aStrValue))
    {
        newAthlete.setCountry(aStrValue);
    }

    if(getFieldAsString(iAthleteInfo, "position", aStrValue))
    {
        newAthlete.setPosition(aStrValue);
    }
    else 
       return false;

    int aIntValue;
    if(getFieldAsInt(iAthleteInfo, "id", aIntValue))
    {
        newAthlete.setId(aIntValue);
    }

    bool aBoolValue;
    if(getFieldAsBool(iAthleteInfo, "is_injured", aBoolValue))
    {
        newAthlete.setIsInjured(aBoolValue);
    }

    if(getFieldAsInt(iAthleteInfo, "squad_id", aIntValue))
    {
        newAthlete.setSquadId(aIntValue);
    }
    else
      return false;
  }
  catch(std::exception &e)
  {
    throw FORWARD_EXCEPTION("Error parsing the rapidjson document", e);
  }
  catch(...)
  {
    throw EXCEPTION("Error parsing the rapidjson document");
  }
  
  oNewAthlete = newAthlete;

  return true;
}

std::map<int, Squad> AthletesReader::getSquadsInfo(const rapidjson::Value& iSquadInfo)
{
  std::map<int, Squad> squads;
  for(rapidjson::SizeType i = 0; i <  iSquadInfo.Size(); ++i)
  {
    if(iSquadInfo[i].HasMember("name") && iSquadInfo[i].HasMember("id"))
    {
      if(iSquadInfo[i]["name"].IsString() && iSquadInfo[i]["id"].IsInt())
      {
        Squad sq;
        sq.setName(iSquadInfo[i]["name"].GetString());
        sq.setId(iSquadInfo[i]["id"].GetInt());
        squads[iSquadInfo[i]["id"].GetInt()] = sq;
      }
      else
      {
        throw EXCEPTION("in JSON file the squads members name and/or id do not have the good type, string and int");
      }
    }
    else
    {
      throw EXCEPTION("Squads member from JSON file has no members name and/or id");
    }
  }  

  return squads;
}
