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


struct MyStruct {
	std::string a;
	int b;
};
struct Compare {
	bool operator()(const MyStruct& x, const MyStruct& y) {
		return x.b > y.b; // 按照 b 的值进行比较
	}
};
void deleteMinValueElement(std::unordered_map<std::string, int>& hash_table) {
	if (hash_table.empty()) {
		std::cout << "Hash table is empty!" << std::endl;
		return;
	}

	int min_value = std::numeric_limits<int>::max();
	std::string min_key;

	// Find the element with the minimum value
	for (const auto& pair : hash_table) {
		if (pair.second < min_value) {
			min_value = pair.second;
			min_key = pair.first;
		}
	}

	// Delete the element with the minimum value
	hash_table.erase(min_key);
}
std::unordered_map<std::string, int>  lz4_compress(std::string str, int inputlen, int spacesavingk, int offset) {
	std::ifstream inputFile(str);
	std::unordered_map<std::string, int>map1;
	std::unordered_map<std::string, int> hash_table;
	std::priority_queue<MyStruct, std::vector<MyStruct>, Compare> minHeap;
	int spacesavingcount = 0;
	std::string bufferstr="";
	int count = 0;
	int bufferlen = 0;
	bool judge = false;
	int judgenum = 0;
	int deletenum = 0;

	if (inputFile.is_open()) {
		std::string line;
		while (std::getline(inputFile, line)) {
			if (line.size() >= 4) {
				if (!judge) {
					hash_table[line.substr(0, 4)] = count;
					bufferlen++;
					bufferstr += line[3];
					count++;
					judgenum = 3;
				}
				else { judgenum = 0; }
				int i = 0;
				if (!judge) {
					 i = 4;
				}
				else {  i = 0; }
				for (; i < line.size()-3; i++) {
					auto it = hash_table.find(line.substr(i,4));
					if (it != hash_table.end()) {
						int i_i = i;
						std::string match_str = line.substr(i, 4);
						int itsecond = it->second + 1;
						while (1) {
							i++;
							if ((i+3) < line.size()&&itsecond < count && line[i+3] == bufferstr[itsecond-deletenum]) {
								match_str += line[i+3];
								itsecond++;
							}
							else {
								i--;
								if (map1.count(match_str)) {
									map1[match_str] += match_str.size();
								}
								else {
									if (spacesavingcount < spacesavingk) {
										map1[match_str] = 2 * match_str.size();
										spacesavingcount++;
										MyStruct s1 = { match_str,2 * match_str.size() };
										minHeap.push(s1);
									}
									else {
										MyStruct minElement = minHeap.top();
										while (minElement.b != map1[minElement.a]) {
											MyStruct s1 = { minElement.a, map1[minElement.a] };
											minHeap.pop();
											minHeap.push(s1);
											minElement = minHeap.top();
										}
										map1.erase(minElement.a);
										map1[match_str] = 1 + minElement.b;
										minHeap.pop();
										MyStruct s1 = { match_str, 2 };
										minHeap.push(s1);
									}
								}
								for (int j = i_i; j <= i; j++) {
									if (bufferlen < inputlen) {
										hash_table[line.substr(j - judgenum, 4)] = count + (3 - judgenum);
										bufferstr += line[j];
										count++;
										bufferlen++;
									}
									else {
										deleteMinValueElement(hash_table);
										bufferstr.erase(0, 1);
										hash_table[line.substr(j - judgenum, 4)] = count + (3 - judgenum);
										bufferstr += line[j];
										count++;
										deletenum++;
									}
								}
								break;
							}

						}

					
					}
					else {
						if (bufferlen < inputlen) {
							hash_table[line.substr(i-judgenum, 4)] = count+(3-judgenum);
							bufferstr+=line[i];
							count++;
							bufferlen++;
						}
						else {
							deleteMinValueElement(hash_table);
							bufferstr.erase(0, 1);
							hash_table[line.substr(i-judgenum, 4)] = count + (3-judgenum);
							bufferstr += line[i];
							count++;
							deletenum++;
						}
					}
					//count++;
				}
				for (; i < line.size();i++) {
					bufferstr += line[i];
					count++;
				}
				bufferstr += '\n';
				count++;
			}
			else {
				for (int i = 0; i < line.size(); i++) {
					bufferstr += line[i];
					count++;
				}
				bufferstr += '\n';
				count++;			
			}
			judge = true;
		}
	
	}
	else {
		std::cout << "Failed to open the file." << std::endl;
	}
	std::unordered_map<std::string, int>map2;
	for (auto it = map1.begin(); it != map1.end(); ++it) {
		for (int i = 0; i < it->first.size(); i += offset) {
			if ((i + offset) <= it->first.size()) { map2[it->first.substr(i, offset)] = it->second; }
			else {
				if (it->first.substr(i).length() >= 4) {
					map2[it->first.substr(i)] = it->second;
				}
			}
		}
	}
	return map2;
}