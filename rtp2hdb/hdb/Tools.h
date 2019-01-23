/*
 * constants.h
 *
 *  Created on: Jan 22, 2019
 *      Author: marchi
 */

#ifndef HDB_TOOLS_H_
#define HDB_TOOLS_H_
#include <string>
#include <regex>
#include <vector>
#include <sstream>
const std::regex RESNAME{R"(^.*\[ *([A-Z][A-Z0-9]*) *\].*)"};
const std::regex ATOMS{R"(^.*\[ *(atoms) *\].*)"};
const std::regex BONDS{R"(^.*\[ *(bonds) *\].*)"};
const std::regex IMPR{R"(^.*\[ *(imp.*) *\].*)"};
const std::regex CMAP{R"(^.*\[ *(cmap) *\].*)"};
const std::regex BONDED{R"(^.*\[ *(bonded.*) *\].*)"};
using std::string;
using std::vector;
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	// Get the first occurrence
	size_t pos = data.find(toSearch);

	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos =data.find(toSearch, pos + replaceStr.size());
	}
}

std::vector<std::string> split(const std::string& s, string del=" ")
{
	const string ranstr{"$3EA"};
	string temp{s};
	if(del.find_first_not_of('\t') != std::string::npos) findAndReplaceAll(temp,"\t"," ");

	if(del.find_first_not_of(' ') != std::string::npos){
		findAndReplaceAll(temp," ",ranstr);
		findAndReplaceAll(temp,del," ");
	}

	std::istringstream iss(temp);
	std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
	                                 std::istream_iterator<std::string>());
	if(del.find_first_not_of(' ') != std::string::npos){
		for(auto & o: tokens){
			findAndReplaceAll(o,ranstr," ");
		}
	}
   return tokens;
}
void eraseBlanks(string & str){
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

#endif /* HDB_TOOLS_H_ */
