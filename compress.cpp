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




void writeBitsToStream(std::ofstream& stream, unsigned int value, int numBits) {
	static unsigned char buffer = 0;
	static int bitsWritten = 0;

	for (int i = 0; i < numBits; i++) {
		buffer <<= 1;
		if (value & (1 << (numBits - 1 - i))) {
			buffer |= 1;
		}
		bitsWritten++;

		if (bitsWritten == 8) {
			stream.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
			buffer = 0;
			bitsWritten = 0;
		}
	}
}





std::string  compress(std::map<std::string, int> docz, std::string input, int numBits, int numBitsoffset) {
	//利用字典对文本进行压缩  用到了一个map和一个vector两个数据结构
	std::unordered_map<std::string, int> hash_table;
	std::vector<char>hash_table2;
	std::string compress_output = "";
	char  ch1, ch2, ch3;
	int count = 0;
	bool judge1 = false;
	bool judge2 = false;
	std::map<std::string, int>::iterator it;
	std::ofstream compressfile(input + ".rp", std::ios::binary);
	if (compressfile.is_open()) {
		if (docz.size() > 0) {
			char label = 0;
			compressfile.write(&label, sizeof(label));
		}
		for (it = docz.begin(); it != docz.end(); ++it) {
			char label = 0;
			//	compressfile.write(&label, sizeof(label));
			std::string key = it->first;
			compressfile.write(key.c_str(), key.size());
			label = 0;
			//	char label = 0;
			compressfile.write(&label, sizeof(label));
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
				if (j == 0) {
					hash_table[temp] = count;
				}

				if (j == 0) { hash_table2.push_back(0); }
				else { hash_table2.push_back(key[j + 3]); }

				count++;
			}
		}
		char label = 0;
		compressfile.write(&label, sizeof(label));
		int i = 0;
		std::ifstream inputFile(input);
		if (inputFile.is_open()) {
			char c;
			while (inputFile.get(c)) {
				if (i == 0) { ch1 = c; }
				else if (i == 1) { ch2 = c; }
				else if (i == 2) { ch3 = c; }
				else {
					std::string buffertemp_com = "";
					buffertemp_com += ch1;
					buffertemp_com += ch2;
					buffertemp_com += ch3;
					buffertemp_com += c;
					auto it = hash_table.find(buffertemp_com);
					if (it != hash_table.end()) {
						compress_output += '(';
						char popo = 1;
						compressfile.write(&popo, sizeof(popo));
						compress_output += std::to_string(it->second);
						writeBitsToStream(compressfile, it->second, numBits);

						compress_output += ',';
						int match_number = 4;
						ch1 = ch2; ch2 = ch3; ch3 = c;
						i++;
						int itsecond2 = it->second;
						while (inputFile.get(c)) {
							if ((itsecond2 + 1) < hash_table2.size() && hash_table2[itsecond2 + 1] != 0 && c == hash_table2[itsecond2 + 1]) {
								//it = it2;
								itsecond2++;
								match_number++;
								ch1 = ch2; ch2 = ch3; ch3 = c;
							}
							else {
								ch1 = c;
								i++;
								if (inputFile.get(c)) {
									ch2 = c;
									i++;
								}
								else {
									compress_output += std::to_string(match_number);
									writeBitsToStream(compressfile, match_number, numBitsoffset);
									compress_output += ')';
									compress_output += ch1;
									compressfile.write(&ch1, sizeof(ch1));
									judge2 = true;
									break;
								}
								if (inputFile.get(c))
								{
									ch3 = c;
								}
								else {

									compress_output += std::to_string(match_number);

									writeBitsToStream(compressfile, match_number, numBitsoffset);

									compress_output += ')';

									compress_output += ch1;
									compressfile.write(&ch1, sizeof(ch1));
									compress_output += ch2;
									compressfile.write(&ch2, sizeof(ch2));
									judge2 = true;
									break;
								}

								break;
							}
							i++;
						}
						if (!judge2) {
							compress_output += std::to_string(match_number);

							writeBitsToStream(compressfile, match_number, numBitsoffset);

							compress_output += ')';
						}
						i += match_number;
						i -= 1;
						judge1 = false;
					}
					else {
						compress_output += ch1;
						compressfile.write(&ch1, sizeof(ch1));
						ch1 = ch2; ch2 = ch3; ch3 = c;
						judge1 = true;
					}
				}
				i++;
			}
			if (judge1) {
				compress_output += ch1;
				compressfile.write(&ch1, sizeof(ch1));
				compress_output += ch2;
				compressfile.write(&ch2, sizeof(ch2));
				compress_output += ch3;
				compressfile.write(&ch3, sizeof(ch3));
			}
			if (i == 0) { return  compress_output; }
			else if (i == 1) { compress_output += ch1; 	compressfile.write(&ch1, sizeof(ch1));  return  compress_output; }
			else if (i == 2) { compress_output += ch1;	compressfile.write(&ch1, sizeof(ch1)); compress_output += ch2;	compressfile.write(&ch2, sizeof(ch2)); return  compress_output; }
			else if (i == 3) { compress_output += ch1; 	compressfile.write(&ch1, sizeof(ch1)); compress_output += ch2;	compressfile.write(&ch2, sizeof(ch2)); compress_output += ch3;	compressfile.write(&ch3, sizeof(ch3)); return  compress_output; }


		}
		else {
			std::cout << "Failed to open the file." << std::endl;
		}
		compressfile.close();
	}
	return  compress_output;
}


