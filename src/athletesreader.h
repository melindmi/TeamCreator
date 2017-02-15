#ifndef ATHLETESREADERH
#define ATHLETESREADERH

#include "athlete.h"
#include "squad.h"
#include <string>
#include <vector>
#include <map>

#include "include/rapidjson/document.h" 

//Object for reading the information for all the athletes from the JSON file
class AthletesReader
{
  public:

    AthletesReader();
    AthletesReader(std::string iFilename);
    ~AthletesReader();

    //get a vector with all the athletes by parsing the file "filename" 
    //if the filename is not set the vector of athletes will be empty
    //Throw if error 
    void getAllAthletesFromFile(std::vector<Athlete>& ioAllAthletes);
    
    //get a vector with all the athletes by parsing a string 
    //the string should be a valid JSON for format including the athelets
    //Throw if error
    void getAllAthletesFromString(std::vector<Athlete>& ioAllAthletes, std::string iAthletesStr);
    
    //set the filename
    void setFilename(std::string iFilename);

    //get the filename
    std::string getFilename();
    
    //get the information for all the squads
    std::map<int, Squad> getSquadsInfo(const rapidjson::Value& iSquadInfo);

  private:
    std::string filename;

    //convert the input JSON file into a string 
    //Throw if error
    std::string convertFileToString();

    //get all the information for a specific athlete in the list
    //return false if athlete is invalid
    //Throw if error
    bool getAthleteInfo(const rapidjson::Value& iAthleteInfo, Athlete& oNewAthlete);
   
    //get a string field from the JSON 
    bool getFieldAsString(const rapidjson::Value& iAthleteInfo, std::string iFieldName, std::string& oFieldValue);

    //get an int field from the JSON
    bool getFieldAsInt(const rapidjson::Value& iAthleteInfo, std::string iFieldName, int& oFieldValue);
    
    //get a bool field from the JSON
    bool getFieldAsBool(const rapidjson::Value& iAthleteInfo, std::string iFieldName, bool& oFieldValue);
};

#endif
