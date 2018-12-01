
#ifndef analyzer_config_h
#define analyzer_config_h

#include "analyzer_globalvalues.h"

class analyzer_config : public analyzer_globalvalues {


public :

                  analyzer_config();
   virtual        ~analyzer_config(); 
   virtual void   setConfiguration();
   //void           initSelectionCategories( TString selcategory );
   void           initSelectionCategories();

   // bin names
   std::vector<TString> selbinnames;
   std::vector<TString> jetmultnames;
   std::vector<TString> tagmultnames;
   std::vector<TString> uncbinnames;
   //std::vector<TString> lepnames;
   // jetmultnames = Leading, Subleading, Third, Fourth, All
   //static const int SELBINNAMESIZE  = 8;        
   static const int SELBINNAMESIZE  = 21;  
   static const int JETMULTNAMESIZE = 5;  
   static const int TAGMULTNAMESIZE = 5;  
   static const int UNCBINNAMESIZE  = 3;

   Float_t pho_minPt;
   Float_t pho_maxEta;
   Float_t ele_minPt1;
   Float_t ele_minPt2;
   Float_t ele_maxEta;
   Float_t mu_minPt1;
   Float_t mu_minPt2;
   Float_t mu_maxEta;
   Float_t jet_minPt;
   Float_t jet_maxEta;

   Float_t tag_minIPsig;
   Float_t tag_minTA;
   Float_t tag_maxAmax;
   Float_t tag_shiftminIPsig;
   Float_t tag_shiftminTA;
   Float_t tag_shiftmaxAmax;
};

#endif
