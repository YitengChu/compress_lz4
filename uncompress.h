// Method2.h
#ifndef METHOD2_H
#define METHOD2_H

#include<iostream>
#include<fstream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include<map>
#include<string>
#include <queue>
#include<algorithm>
#include<set>

int readBitsFromStream(std::ifstream& stream, int numBits);
std::string   uncompress(std::string input, int numBitsToRead, int numBitsToReadoffset);

#endif#pragma once
