#ifndef METHOD4_H
#define METHOD4_H
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


//std::vector<std::string> removeSubstrings(std::vector<std::string> strings, std::unordered_map<std::string, int>  preorder2);std::vector<std::pair<std::string, int
std::vector<std::string> removeSubstrings(std::vector<std::pair<std::string, int>>topKeys, int frequencyThreshold);
std::map<std::string, int>  create_dic(std::unordered_map<std::string, int>map1, int k);

#endif#pragma once#pragma once
