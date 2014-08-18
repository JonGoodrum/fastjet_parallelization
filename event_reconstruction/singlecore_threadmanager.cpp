//author Jon Goodrum
#include "fastjet/ClusterSequence.hh"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <time.h>
using namespace fastjet;


    // a void used to copy the processed jets to a .txt file
    void printjets(std::vector<PseudoJet> jets, bool append);


int main (int argc , char *argv[]){

  // initialize objects
  bool append = false ;
  bool repeat = true ;
  time_t timer1 = time(NULL);
  std::string this_line;
  std::vector<fastjet::ClusterSequence::Tile> * tiles;
  fastjet::ClusterSequence::ThreadManager * tman = new fastjet::ClusterSequence::ThreadManager;
  tman->singleCore();


   // do for every event on the data file:
   // (assuming successive events are in the same file and separated by "#END")
  while(repeat){
    repeat = false ;
    std::vector<fastjet::PseudoJet> particles;  
    double px, py , pz, E;

    // read the event data from the file
    while (std::cin >> px >> py >> pz >> E)
    {
      particles.push_back(fastjet::PseudoJet(px,py,pz,E));
      // terminate program if complete
      if (particles.empty())
      {
        time_t timer2 = time(NULL);
        time_t seconds = difftime(timer2,timer1);
        std::cout << "Elapsed time: " << seconds << "\n";
        return 42;
      }
    }
   
    // choose a jet definition
    double R = 0.7;
    JetDefinition jet_def(cambridge_algorithm, R, E_scheme, N2PoorTiled);

    // run the clustering, extract the jets
    ClusterSequence cs(particles, jet_def, tman, tiles);
    std::vector<PseudoJet> jets = sorted_by_pt(cs.inclusive_jets());

    // print the jets to a file
    printjets(jets , append);
    
    // check to see if more events are present
    std::cin.clear();
    getline( std::cin , this_line , '\n' );
    if (this_line == "#END"){
      repeat = true ;
      append = true ;
    }

  }//end While(repeat)
  
  
  time_t timer2 = time(NULL);
  time_t seconds = difftime(timer2,timer1);
  std::cout << "Elapsed time: "  << seconds << "\n";
}//end Main()

//   TODO : When compiling with gcc, you can use the following:
//   g++ singlecore_threadmanager.cpp -o SCTM  `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` -pthread -std=c++11
//  To run, you can execute the following:
//   sudo ./SCTM < some_input_event.dat










//-----------------------------------------------------------------------------
//This void is used to display the processed jets
void printjets(std::vector<PseudoJet> jets , bool append){

  std::ofstream PrintToFile;
  
  //decides which file to write to.  Appends or re-writes the file.
  if(!append)
    {PrintToFile.open ("sctm_results.txt");}
  else
    {PrintToFile.open ("sctm_results.txt", std::ios::app|std::ios::ate);}
  

  //  prints out the jets
  PrintToFile << "\n##################################################\n\n        pt y phi\n";
  for (unsigned i = 0; i < jets.size(); ++i){
    PrintToFile << "jet " << i << ": "<< jets[i].perp() << " " 
                   << jets[i].rap() << " " << jets[i].phi() << "\n";
    std::vector<PseudoJet> constituents = jets[i].constituents();
    for (unsigned j = 0; j < constituents.size(); j++){
      PrintToFile << "    constituent " << j << "'s pt: " << constituents[j].perp()
           << "\n";
    }
  }
  PrintToFile.close();
}
//-----------------------------------------------------------------------------
