#include <iostream>
#include <stdio.h>
#include <cmath>
 
double countevents(TString Tsample){
 
 Double_t ntotal = 0;
 Double_t nevents = 0;

 char* listdir;
 listdir = getenv ("listdir");
 TString Tlistdir = TString(listdir);
 TString fulllistname = Tlistdir+"/"+Tsample+".list";
 TString fulloutname   = Tlistdir+"/"+Tsample+".info";

 printf("Tsample : %s \n",fulllistname.Data());

 std::fstream inputfile;
 inputfile.open(fulllistname);
 if( !inputfile.good() ) { 
   std::cerr << "Cannot open the file: \"" << fulllistname+"\""<<std::endl;
   abort();
 }

 // lines read from file variables to count number of events
 std::string inputline = ""; 
 TString Tinputline = ""; 

 int count = 0;
 while( std::getline(inputfile, inputline) ) { 
  if( inputfile.fail() ) continue;

  count++;

  Tinputline = inputline;
  if( Tinputline.Contains("/store/group") ){  // if filename

   // open file
   TFile* theFile;
   theFile = TFile::Open("root://cmseos.fnal.gov/"+Tinputline);

   // get histogram
   TH1F* h_nevents;
   h_nevents = (TH1F*)theFile->Get("lldjNtuple/hEvents");
   //h_nevents = (TH1F*)theFile->Get("noCutSignature_COUNT");

   // add bin contents to total count
   nevents=h_nevents->GetBinContent(1);
   ntotal+=nevents;
   if(count%100 == 0) printf("Print every 100 files: root://cmseos.fnal.gov/%s \n events: %.1f \n",Tinputline.Data(),nevents);

   theFile->Close();

  } // if line contains /store/group
 } //while getline
 inputfile.close();

 // append nrevents to list file
 FILE * outfile;
 outfile = fopen (fulloutname,"w");
 fprintf (outfile, "nrevents: %.1f \n",ntotal);
 fclose (outfile);

 printf("--total: %.1f\n",ntotal);
 return ntotal;
 
}
