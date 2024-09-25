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

				if (strings[i].size() <= strings[i + 1].size() && strings[i] == strings[i + 1].substr(0, strings[i].size())) {
					out.insert(i);
					node = strings[i + 1];
					nodeint = i + 1;
				}
				else {
					if (preorder2[strings[i]] < preorder2[strings[i + 1]]) { node = strings[i + 1]; out.insert(i); nodeint = i + 1; }
					else { node = strings[i]; out.insert(i + 1); nodeint = i; }
				}
			}
			else { node = strings[i + 1]; nodeint = i + 1; }
		}
		else {
			if (strings[i].substr(0, 4) == strings[i + 1].substr(0, 4)) {
				if (strings[i].size() <= strings[i + 1].size() && strings[i] == strings[i + 1].substr(0, strings[i].size())) {
					out.insert(i);
					node = strings[i + 1];
					nodeint = i + 1;
				}
				else {
					if (preorder2[strings[i + 1]] > preorder2[strings[nodeint]]) { node = strings[i + 1]; out.insert(nodeint); }
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








class TrieNode {
public:
	char value;  
	int count;  
	std::unordered_map<char, TrieNode*> children;  
	bool isEndOfWord;  

	TrieNode(char val) : value(val), count(0), isEndOfWord(false) {}
};


class Trie {
public:
	TrieNode* root;
	Trie() {
		root = new TrieNode('\0');  
	}


	void insert(const std::string& word, int frequency) {
		TrieNode* node = root;
		for (char ch : word) {
			if (node->children.find(ch) == node->children.end()) {
				node->children[ch] = new TrieNode(ch);  
			}
			node = node->children[ch];
			node->count += frequency;  
		}
		node->isEndOfWord = true;  
	}

	void preorderTraversal(TrieNode* node, std::string currentPrefix, std::unordered_map<std::string, int>& result) {
		if (node == nullptr) return;  

		if (node->isEndOfWord) {
			if (currentPrefix.size() >= 4) {
				result[currentPrefix] = node->count;
			} 
		}
		bool judge = true;
		for (auto& child : node->children) {
			if (judge) {
				preorderTraversal(child.second, currentPrefix + child.first, result);
				judge = false;
			}
			else {
				std::string currentPrefix1 = "" + std::string(1, child.first);
				preorderTraversal(child.second, currentPrefix1, result);
			}
		}
	}
};


class PrefixForest {
public:
	std::vector<Trie*> tries;  

	void addWordToForest(const std::string& word, int frequency, int threshold) {
		if (frequency < threshold) return;  

		for (Trie* trie : tries) {
			TrieNode* node = trie->root;
			bool prefixMatch = true;
			bool prefix = true;
			int sum = 0;
			for (char ch : word) {
				sum++;
				if (node->children.find(ch) == node->children.end()) {
					if (prefix) {
						prefixMatch = false; 
					}
					break;
				}
				prefix = false;
				node = node->children[ch];
			}

			
			if (prefixMatch) {
				if (sum == word.size()) {
					return;  
				}
				else {
					trie->insert(word, frequency); 
					return; 
				}
			}
		}

		
		Trie* newTrie = new Trie();
		newTrie->insert(word, frequency);
		tries.push_back(newTrie);
	}

	void storePreorderTraversal(std::unordered_map<std::string, int>& result) {
		for (Trie* trie : tries) {
			trie->preorderTraversal(trie->root, "", result);
		}
	}
};







std::vector<std::string> removeSubstrings(std::vector<std::pair<std::string, int>> strings, int frequencyThreshold) {
	
	std::vector<std::string>result;
	std::unordered_map<std::string, int>  preorder2;
	PrefixForest forest;
	// 构建前缀森林
	for (const auto& entry : strings) {
		forest.addWordToForest(entry.first, entry.second, frequencyThreshold);
	}

	forest.storePreorderTraversal(preorder2);
	for (const auto& pair : preorder2) {
		result.push_back(pair.first);
	}
	std::sort(result.begin(), result.end());
	std::vector<std::string>result2 = inremoveSubstrings(result, preorder2);
	return result2;
}




struct MyStruct {
	std::string a;
	int b;
};
struct Compare {
	bool operator()(const MyStruct& x, const MyStruct& y) {
		return x.b > y.b; 
	}
};

bool cmp_value2(const std::pair<std::string, int>& left, const std::pair<std::string, int>& right) {
	return left.second > right.second;
}
bool cmp_value3(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
	return a.second < b.second;
}



std::map<std::string, int>  create_dic(std::unordered_map<std::string, int>map1, int k) {
	std::vector<std::pair<std::string, int>> topKeys;
	//没必要的操作？
	for (int i = 0; i < k; ++i) {
		auto it = std::max_element(map1.begin(), map1.end(), [](const auto& a, const auto& b) {
			return a.second < b.second;
			});
		if (it != map1.end()) {
			topKeys.push_back(*it);
			map1.erase(it->first);
		}
	}
	for (auto it = map1.begin(); it != map1.end(); ++it) {
		topKeys.push_back(*it);
	}
	std::map<std::string, int>docz;
	int count = 0;
	std::sort(topKeys.begin(), topKeys.end(), cmp_value2);
	std::vector<std::string> topKeystemp = removeSubstrings(topKeys,12);
	for (const auto& pair : topKeystemp) {
		docz[pair] = count;
	}
	return docz;
}
