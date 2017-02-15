#ifndef ATHLETEH 
#define ATHLETEH

#include <string>

//Object storing all the information related to an athlete
class Athlete 
{
  public: 
    //get the athlete name
    std::string getName();

    //set the athlete name
    void setName(std::string iName);
    
    //get the athlete country
    std::string getCountry();

    //set the athlete country
    void setCountry(std::string iCountry);
    
    //get the athlete position
    std::string getPosition();
    
    //set the athlete position
    void setPosition(std::string iPos);
    
    //get the athlete id
    int getId();

    //set the athlete id
    void setId(int iId);
    
    //get the athlete is_injured 
    bool getIsInjured();
  
    //set the athlete is_injured
    void setIsInjured(bool iIsInjured);    

    //get the squad name
    std::string getSquadName();

    //set the squad name
    void setSquadName(std::string iSquad);
    
    //get the squad id
    int getSquadId();

    //set the squad id
    void setSquadId(int iSquadId);

  private:
    std::string name;
    std::string country;
    std::string position;
    int id;
    bool isInjured;
    std::string squadName;
    int squadId;

};

#endif
