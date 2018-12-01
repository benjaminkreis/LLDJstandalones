#include <iostream>
#include <stdio.h>
#include <cmath>
 
double findTTavgweight(TString Tsample){

 // start stopwatch
 TStopwatch sw; 
 sw.Start();
 
 Double_t avgweight;

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

 // initialize histogram
 TH1F* h_totalSF;
 TH1F* h_tmpSF;

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

   h_tmpSF  = (TH1F*)theFile ->Get("lldjNtuple/hTTSF")->Clone("h_tmpSF") ;
   h_tmpSF  ->SetDirectory(0) ;
   if(count==1){ h_totalSF = (TH1F*)h_tmpSF->Clone("h_totalSF"); }
   else{ h_totalSF->Add(h_tmpSF); }
   h_totalSF->SetDirectory(0) ;

   theFile->Close();

  } // if line contains /store/group
 } //while getline
 inputfile.close();

 avgweight = h_totalSF->GetMean();

 // append ttsf to list file
 FILE * outfile;
 outfile = fopen (fulloutname,"a");
 fprintf (outfile, "ttsf: %.6f \n",avgweight);
 fclose (outfile);

 printf("--avgweight: %.6f\n",avgweight);

 sw.Stop();
 std::cout << "Real Time: " << sw.RealTime()/60.0 << std::endl;
 std::cout << "CPU Time: " << sw.CpuTime()/60.0 << std::endl;
 std::cout << "Done with " << Tsample << std::endl;

 return avgweight;
 
}
