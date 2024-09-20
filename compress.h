// Method3.h
#ifndef METHOD3_H
#define METHOD3_H
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


void writeBitsToStream(std::ofstream& stream, unsigned int value, int numBits);
std::string  compress(std::map<std::string, int> docz, std::string input, int numBits, int numBitsoffset);

#endif#pragma once
