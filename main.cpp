#include "lz4.h"
#include "compress.h"
#include "uncompress.h"
#include "DicGeneration.h"
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
#include <chrono>
using namespace std;
int main() {
	string input = "C:\\Users\\Lenovo\\Desktop\\urls2.txt";
	unordered_map<string, int>map1;
	map<string, int>  doc;
	map1 = lz4_compress(input, 4000, 100, 15);
	doc = create_dic(map1, 1000);
	for (auto it = doc.begin(); it != doc.end(); ++it) {
		std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
	}
	string output = compress(doc, input, 12, 4);
	string compressfile = "C:\\Users\\Lenovo\\Desktop\\urls2.txt.rp";
	string output2 = uncompress(compressfile, 12, 4);

}


