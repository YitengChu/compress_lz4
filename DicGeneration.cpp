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




std::vector<std::string> inremoveSubstrings(std::vector<std::string> strings, std::unordered_map<std::string, int>  preorder2) {
	std::set<int>out;
	std::string node;
	int nodeint;
	for (int i = 0; i < strings.size() - 1; i++) {
		if (i == 0) {
			if (strings[i].substr(0, 4) == strings[i + 1].substr(0, 4)) {
				if (strings[i].size() <= strings[i + 1].size()) {
					if (strings[i] == strings[i + 1].substr(0, strings[i].size())) {
						out.insert(i);
						node = strings[i + 1];
						nodeint = i + 1;
					}
					else {

						int matchtempremove = 0;
						int len = std::min(strings[i].length(), strings[i + 1].length());
						for (int j = 0; j < len; ++j) {
							if (strings[i][j] != strings[i + 1][j]) {
								break;
							}
							matchtempremove++;
						}
						int maxtemp1 = 0, maxtemp2 = 0;
						for (int j = matchtempremove; j < strings[i].size(); j++) {
							if (preorder2[strings[i].substr(j - 3, 4)] > maxtemp1) { maxtemp1 = preorder2[strings[i].substr(j - 3, 4)]; }
						}
						for (int j = matchtempremove; j < strings[i + 1].size(); j++) {
							if (preorder2[strings[i + 1].substr(j - 3, 4)] > maxtemp2) { maxtemp2 = preorder2[strings[i + 1].substr(j - 3, 4)]; }
						}
						if (maxtemp1 <= maxtemp2) { node = strings[i + 1]; out.insert(i); nodeint = i + 1; }
						else { node = strings[i]; out.insert(i + 1); nodeint = i; }

					}

				}
				else {
					int matchtempremove = 0;
					int len = std::min(strings[i].length(), strings[i + 1].length());
					for (int j = 0; j < len; ++j) {
						if (strings[i][j] != strings[i + 1][j]) {
							break;
						}
						matchtempremove++;
					}
					int maxtemp1 = 0, maxtemp2 = 0;
					for (int j = matchtempremove; j < strings[i].size(); j++) {
						if (preorder2[strings[i].substr(j - 3, 4)] > maxtemp1) { maxtemp1 = preorder2[strings[i].substr(j - 3, 4)]; }
					}
					for (int j = matchtempremove; j < strings[i + 1].size(); j++) {
						if (preorder2[strings[i + 1].substr(j - 3, 4)] > maxtemp2) { maxtemp2 = preorder2[strings[i + 1].substr(j - 3, 4)]; }
					}
					if (maxtemp1 <= maxtemp2) { node = strings[i + 1]; out.insert(i); nodeint = i + 1; }
					else { node = strings[i]; out.insert(i + 1); nodeint = i; }
				}
			}
			else { node = strings[i + 1]; nodeint = i + 1; }

		}
		else {
			if (strings[i].substr(0, 4) == strings[i + 1].substr(0, 4)) {
				if (strings[i].size() <= strings[i + 1].size()) {
					if (strings[i] == strings[i + 1].substr(0, strings[i].size())) {
						if (out.count(i) > 0) {

							int matchtempremove = 0;
							int len = std::min(node.length(), strings[i + 1].length());
							for (int j = 0; j < len; ++j) {
								if (node[j] != strings[i + 1][j]) {
									break;
								}
								matchtempremove++;
							}
							int maxtemp1 = 0, maxtemp2 = 0;
							for (int j = matchtempremove; j < node.size(); j++) {
								if (preorder2[node.substr(j - 3, 4)] > maxtemp1) { maxtemp1 = preorder2[node.substr(j - 3, 4)]; }
							}
							for (int j = matchtempremove; j < strings[i + 1].size(); j++) {
								if (preorder2[strings[i + 1].substr(j - 3, 4)] > maxtemp2) { maxtemp2 = preorder2[strings[i + 1].substr(j - 3, 4)]; }
							}
							if (maxtemp1 <= maxtemp2) { node = strings[i + 1]; out.insert(nodeint); }
							else { out.insert(i + 1); }

						}
						else {
							out.insert(i);
							node = strings[i + 1];
							nodeint = i + 1;
						}
					}
					else {

						int matchtempremove = 0;
						int len = std::min(node.length(), strings[i + 1].length());
						for (int j = 0; j < len; ++j) {
							if (node[j] != strings[i + 1][j]) {
								break;
							}
							matchtempremove++;
						}
						int maxtemp1 = 0, maxtemp2 = 0;
						for (int j = matchtempremove; j < node.size(); j++) {
							if (preorder2[node.substr(j - 3, 4)] > maxtemp1) { maxtemp1 = preorder2[node.substr(j - 3, 4)]; }
						}
						for (int j = matchtempremove; j < strings[i + 1].size(); j++) {
							if (preorder2[strings[i + 1].substr(j - 3, 4)] > maxtemp2) { maxtemp2 = preorder2[strings[i + 1].substr(j - 3, 4)]; }
						}
						if (maxtemp1 <= maxtemp2) { node = strings[i + 1]; out.insert(nodeint); }
						else { out.insert(i + 1); }

					}
				}
				else {
					int matchtempremove = 0;
					int len = std::min(node.length(), strings[i + 1].length());
					for (int j = 0; j < len; ++j) {
						if (node[j] != strings[i + 1][j]) {
							break;
						}
						matchtempremove++;
					}
					int maxtemp1 = 0, maxtemp2 = 0;
					for (int j = matchtempremove; j < node.size(); j++) {
						if (preorder2[node.substr(j - 3, 4)] > maxtemp1) { maxtemp1 = preorder2[node.substr(j - 3, 4)]; }
					}
					for (int j = matchtempremove; j < strings[i + 1].size(); j++) {
						if (preorder2[strings[i + 1].substr(j - 3, 4)] > maxtemp2) { maxtemp2 = preorder2[strings[i + 1].substr(j - 3, 4)]; }
					}
					if (maxtemp1 <= maxtemp2) { node = strings[i + 1]; out.insert(nodeint); }
					else { out.insert(i + 1); }
				}
			}
			else {
				node = strings[i + 1]; nodeint = i + 1;
			}

		}
	}
	std::vector<std::string>result;
	for (int i = 0; i < strings.size(); i++) {
		if (out.count(i) > 0) {}
		else { result.push_back(strings[i]); }
	}
	return result;
}









std::vector<std::string> removeSubstrings(std::vector<std::pair<std::string, int>> strings) {
	std::set<std::string> mySet;
	std::vector<std::string>result;
	std::unordered_map<std::string, int>  preorder2;

	for (int i = 0; i < strings.size(); i++) {
		if (i == (strings.size() - 1)) {
			if (mySet.find(strings[i].first) != mySet.end()) { preorder2[strings[i].first] += strings[i].second; }
			else { result.push_back(strings[i].first);  mySet.insert(strings[i].first);           preorder2[strings[i].first] = strings[i].second; }
			break;
		}
		if (strings[i].first.substr(0, 4) == strings[i + 1].first.substr(0, 4)) {
			int number = 4;
			while (number < strings[i].first.size() && number < strings[i + 1].first.size()) {
				if (strings[i].first[number] != strings[i + 1].first[number]) {

					if (mySet.find(strings[i].first.substr(0, number)) != mySet.end()) { preorder2[strings[i].first.substr(0, number)] += strings[i].second; }
					else { result.push_back(strings[i].first.substr(0,number));  mySet.insert(strings[i].first.substr(0,number));    preorder2[strings[i].first.substr(0, number)] = strings[i].second;
					}


					if (strings[i + 1].first.substr(number).size()<4||mySet.find(strings[i + 1].first.substr(number)) != mySet.end()) { preorder2[strings[i+1].first.substr(number)] += strings[i+1].second; }
					else { result.push_back(strings[i + 1].first.substr(number));  mySet.insert(strings[i + 1].first.substr(number));   preorder2[strings[i+1].first.substr(number)] = strings[i + 1].second;
					}


					if (strings[i].first.substr(number).size() < 4 || mySet.find(strings[i].first.substr(number)) != mySet.end()) { preorder2[strings[i].first.substr( number)] += strings[i].second; }
					else { result.push_back(strings[i].first.substr(number));  mySet.insert(strings[i].first.substr(number)); preorder2[strings[i].first.substr(number)] = strings[i].second;
					}

					break;
				}
				number++;
			}
			if (number == strings[i].first.size()) {
				if (mySet.find(strings[i].first) != mySet.end()) {
					preorder2[strings[i].first] += strings[i].second;
				}
				else {
					result.push_back(strings[i].first);  mySet.insert(strings[i].first);
					preorder2[strings[i].first] = strings[i].second;
				}

				if (strings[i + 1].first.substr(number).size() < 4 || mySet.find(strings[i + 1].first.substr(number)) != mySet.end()) {
					preorder2[strings[i + 1].first.substr(number)] += strings[i + 1].second;
				}
				else { result.push_back(strings[i + 1].first.substr(number));  mySet.insert(strings[i + 1].first.substr(number));
				preorder2[strings[i + 1].first.substr(number)] = strings[i + 1].second;
				}			
			}
		/*	if (number == strings[i+1].first.size()) {
				if (mySet.find(strings[i+1].first) != mySet.end()) {
					preorder2[strings[i + 1].first] += strings[i + 1].second;
				}
				else {
					result.push_back(strings[i+1].first);  mySet.insert(strings[i+1].first);
					preorder2[strings[i + 1].first] = strings[i + 1].second;
				}
				if (strings[i].first.substr(number).size() < 4 || mySet.find(strings[i].first.substr(number)) != mySet.end()) {
					preorder2[strings[i].first.substr(number)] += strings[i].second;
				}
				else { result.push_back(strings[i].first.substr(number));  mySet.insert(strings[i].first.substr(number));
				preorder2[strings[i].first.substr(number)] = strings[i].second;
				}
				i++;
			}*/
		}
		else {
			if (mySet.find(strings[i].first) != mySet.end()) { preorder2[strings[i].first] += strings[i].second; }
			else { result.push_back(strings[i].first);  mySet.insert(strings[i].first);           preorder2[strings[i].first] = strings[i].second; }
		}
	}
	std::sort(result.begin(), result.end());
	std::vector<std::string>result2=inremoveSubstrings(result, preorder2);
	return result2;
}




struct MyStruct {
	std::string a;
	int b;
};
struct Compare {
	bool operator()(const MyStruct& x, const MyStruct& y) {
		return x.b > y.b; // 按照 b 的值进行比较
	}
};

bool cmp_value2(const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) {
	return left.first < right.first;
}
/*bool cmp_value3(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
	return a.second < b.second;
}*/



std::map<std::string, int>  create_dic(std::unordered_map<std::string, int>map1,int k) {
	std::vector<std::pair<std::string, int>> topKeys;
	//没必要的操作？
	/*for (int i = 0; i < k; ++i) {
		auto it = std::max_element(map1.begin(), map1.end(), [](const auto& a, const auto& b) {
			return a.second < b.second;
			});
		if (it != map1.end()) {
			topKeys.push_back(*it);
			map1.erase(it->first);
		}
	}*/
	for (auto it = map1.begin(); it != map1.end(); ++it) {
		topKeys.push_back(*it);
}
	std::map<std::string, int>docz;
	int count = 0;
	std::sort(topKeys.begin(), topKeys.end(), cmp_value2);
	std::vector<std::string> topKeystemp = removeSubstrings(topKeys);
	for (const auto& pair : topKeystemp) {
		docz[pair] = count;
	}
	return docz;
}
