#include "analyzer_config.h"

//----------------------------analyzer_config
analyzer_config::analyzer_config() 
{
}

//----------------------------~analyzer_config
analyzer_config::~analyzer_config()
{
}


//----------------------------analyzer_config
void analyzer_config::setconfiguration() 
{

 // set which collections
 phoid = "Medium"; // "Tight"; "Loose"; //Medium"; 
 eleid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 muoid = "Loose"; // "Tight"; "Loose"; //Medium"; 
 jetid = "Loose"; // "Tight"; "Loose";

 jetmatchdRcut = 0.4;
 objcleandRcut = 0.4;

 if (phoid = "Loose")  phoidbit=0;
 if (phoid = "Medium") phoidbit=1;
 if (phoid = "Tight")  phoidbit=2;

 if (eleid = "Loose")  eleidbit=0;
 if (eleid = "Medium") eleidbit=1;
 if (eleid = "Tight")  eleidbit=2;

 if (muoid = "Loose")  muoidbit=0;
 if (muoid = "Medium") muoidbit=1;
 if (muoid = "Tight")  muoidbit=2;

 if (jetid = "Loose")  aodcalojetidbit=0;
 if (jetid = "Tight")  aodcalojetidbit=1;

 //printf("setting config\n");

}