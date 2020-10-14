#ifndef __PLAYFAIR_H__
#define __PLAYFAIR_H__

#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Playfair
{
public:
	Playfair(const std::string & key, bool show_detailed_info);
	int encrypt(/*in*/ const std::string & plain_text, /*out*/ std::string & encrypted_text);
	int decrypt(/*in*/ const std::string & encrypted_text, /*out*/ std::string & plain_text);

	bool _show_all_info;
	
private:
	std::string 					_key;
	std::vector <std::vector<char> > _table;
	
	std::string		convertToUpper(const std::string & s);
	void			buildTable();
	void			buildPairs(const std::string & input, /*out*/std::vector<std::string> & output);

	void			getEncryptedPair(std::string & elem);
	void			getDecryptedPair(std::string & elem);
	
	void			findCharacterInTable(char c, int & x, int & y);
	char			getCharOnPos(int x, int y);
	bool			isNewChar(char c);
	
	void 			printTable();
	
	void 			printDetailedInfoHeader();
	void 			printDetailedInfoFooter();
};

#endif
