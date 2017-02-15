#ifndef SQUADH
#define SQUADH

#include <string>

class Squad
{
  public:
    //get the squad id
    int getId();
    
    //set the squad id
    void setId(int iId);

    //get the squad name
    std::string getName();

    //set the squad name
    void setName(std::string iName);    

  private:
    int id;
    std::string name;

};


#endif
