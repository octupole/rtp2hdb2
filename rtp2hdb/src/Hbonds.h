/*
 * Hbonds.h
 *
 *  Created on: Jan 23, 2019
 *      Author: marchi
 */

#ifndef SRC_HBONDS_H_
#define SRC_HBONDS_H_
#include <string>
#include <vector>
#include <map>
using std::string;
using std::vector;
using std::map;

class Hbonds {
	map<string,vector<string>> neigh;
public:
	Hbonds();
	virtual ~Hbonds();
};

#endif /* SRC_HBONDS_H_ */
