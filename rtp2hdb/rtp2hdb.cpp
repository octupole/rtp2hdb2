//============================================================================
// Name        : rtp2hdb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options.hpp>
#include <regex>

#include "Tools.h"
namespace po = boost::program_options;
using namespace std;

#include <fstream>
#include <iterator>
#include <string>
#include <map>
using std::string;
using std::vector;
using std::map;
using namespace std;

int main(int ac, char* av[])
{
    string fileI,fileO;
    bool verbose=false;
    try {
        po::options_description desc("Allowed options:");
        po::variables_map vm;
        desc.add_options()
            ("help,h", "produce help message")
            ("verbose,v", "verbose mode")
            ("force","force to find hydrogens in protein residues and polymer units. Results will be wrong "
            		"for those hydrogens. It might be wrong for others.")
            ("rtp,i", po::value<string>(&fileI),"rtp file to process")
            ("hdb,o", po::value<string>(&fileO),"hdb file to generate")
        ;

        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            cout << desc << "\n";
            return 1;
        }
        if(!vm.count("rtp")){
            cout << desc << "\n";
            return 1;
        }
        if(vm.count("verbose")) verbose=true;
        if(fileI.find(".rtp") == string::npos) fileI.append(".rtp");

        if(!vm.count("hdb")){
        	fileO=fileI;
        	fileO.replace(fileO.find("rtp"),3,"hdb");
        }
        if(fileO.find(".hdb") == string::npos) fileO.append(".hdb");

        if(verbose) {
        	cout << "Output rtp filename was set to " << fileI << ".\n";
        	cout << "Output hdb filename was set to " <<  fileO << ".\n";
        }
    }
    catch(std::exception & e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }

    ifstream ifs(fileI.c_str());
    ofstream ofs(fileO.c_str());

    if(!ifs){cout << "Could not open input file!\n";}
    stringstream ss;
    ss<< ifs.rdbuf();

    string sstr=ss.str();
    vector<string> strs=split(sstr,'\n');
    map<string,vector<string>> residues;
    string name;

    for(size_t o{0};o<strs.size();o++){
    	vector<string> st0=split(strs[o],';');
    	if(st0.size() == 0 ) continue;
    	if(st0[0].find_first_not_of(' ') == std::string::npos) continue;
        std::cmatch m,mb;
        std::regex_match(st0[0].c_str(),m,RESNAME);
        std::regex_match(st0[0].c_str(),mb,BONDED);

        if(m.size() == 2){
        	name=m[1];
        	residues[name]=vector<string>();
        }else if(mb.size() == 2){
        	name=mb[1];
        	residues[name]=vector<string>();
        }else{
        	residues[name].push_back(st0[0]);
        }
    }
    map<string,vector<string>> connect;
    for(auto it=residues.begin();it!=residues.end();it++){
    	vector<string> conn=residues[it->first];
        for(size_t o{0};o<conn.size();o++){
            std::cmatch m,mb;
            bool ok_atoms=std::regex_match(conn[o].c_str(),m,ATOMS);
            bool ok_bonds=std::regex_match(conn[o].c_str(),mb,BONDS);
            bool ok_imprs=std::regex_match(conn[o].c_str(),m,IMPR);
            bool ok_cmaps=std::regex_match(conn[o].c_str(),m,CMAP);

            if(mb.size() == 2){
            	connect[it->first]=vector<string>();
            } else {

            }
        }

    	for(size_t o{0};o< it->second.size();o++){
    		cout << o << " " <<it->second[o]<<endl;
    	}
    }

//
//
//    cout << "Gromacs hydrogen bond file \"" << fileO << "\" has been created \n";
    return 0;
}
