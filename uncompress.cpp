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



int readBitsFromStream(std::ifstream& stream, int numBits) {
	static unsigned char buffer = 0;
	static int bitsRemaining = 0;

	int result = 0;

	for (int i = 0; i < numBits; i++) {
		if (bitsRemaining == 0) {
			stream.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
			bitsRemaining = 8;
		}

		result <<= 1;
		result |= (buffer & 0x80) ? 1 : 0;
		buffer <<= 1;
		bitsRemaining--;
	}

	return result;
}


std::string   uncompress(std::string input, int numBitsToRead, int numBitsToReadoffset) {
	std::map<std::string, int> docz;
	std::unordered_map<std::string, int> hash_table;
	std::vector<std::vector<char>>  doc;
	std::string output;
	int count = 0;
	std::map<std::string, int>::iterator it;
	std::ofstream uncompressfile(input.substr(0, input.size() - 3), std::ios::binary);
	if (uncompressfile.is_open()) {
		std::ifstream decompressfile(input, std::ios::binary);
		char doczchar;
		decompressfile.read(&doczchar, sizeof(doczchar));
		while (doczchar == 0) {
			std::string doctemp = "";
			decompressfile.read(&doczchar, sizeof(doczchar));
			if (doczchar == 0) { break; }
			while (doczchar != 0) {
				doctemp += doczchar;
				decompressfile.read(&doczchar, sizeof(doczchar));
			}
			docz[doctemp] = 0;
			//	decompressfile.read(&doczchar, sizeof(doczchar));
		}
		//decompressfile.seekg(-1, std::ios_base::cur);
		for (it = docz.begin(); it != docz.end(); ++it) {
			std::string key = it->first;
			for (int j = 0; j < key.length() - 3; j++) {
				std::vector<char> docnum;
				std::string temp = "";
				docnum.push_back(key[j]);
				temp += key[j];
				docnum.push_back(key[j + 1]);
				temp += key[j + 1];
				docnum.push_back(key[j + 2]);
				temp += key[j + 2];
				docnum.push_back(key[j + 3]);
				temp += key[j + 3];
				hash_table[temp] = count;
				doc.push_back(docnum);
				count++;
			}
		}
		int numberRead;
		char charRead;
		// 循环读取文件中的数字，直到文件结束
		while (!decompressfile.eof()) {
			decompressfile.read(&charRead, sizeof(charRead));
			if (decompressfile.eof()) { break; }
			if (charRead != 1) {
				output += charRead;
				uncompressfile.write(&charRead, sizeof(charRead));
			}
			else {
				int num1 = readBitsFromStream(decompressfile, numBitsToRead);
				int num2 = readBitsFromStream(decompressfile, numBitsToReadoffset);

				num2 -= 4;
				for (int j = 0; j < doc[num1].size(); j++) {
					output += doc[num1][j];
					uncompressfile.write(&doc[num1][j], sizeof(doc[num1][j]));
				}
				if (num2 > 0) {
					for (int j = 1; j <= num2; j++) {
						output += doc[num1 + j][3];
						uncompressfile.write(&doc[num1 + j][3], sizeof(doc[num1 + j][3]));
					}
				}
			}

		}
		// 关闭文件
		decompressfile.close();
		uncompressfile.close();
	}
	return output;
}