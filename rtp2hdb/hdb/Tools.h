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
const std::regex IMPR{R"(^.*\[ *(improper) *\].*)"};
const std::regex CMAP{R"(^.*\[ *(cmap) *\].*)"};
const std::regex BONDED{R"(^.*\[ *(bondedtypes) *\].*)"};

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}
#endif /* HDB_TOOLS_H_ */
