//
//  EncryptionManager.h
//  Playfair
//
//  Created by Eugen Marin and Elena Marin on 14/10/2020.
//

#ifndef EncryptionManager_h
#define EncryptionManager_h

#include <string>
#include <iostream>
#include <fstream>
using namespace std;


enum ENCRYPTION_TYPE {
	PLAYFAIR
};

class EncryptionManager
{
public:
	EncryptionManager(ENCRYPTION_TYPE etype, bool show_all);
	void 			run(bool encrypt, const string & filename = std::string());

private:
	ENCRYPTION_TYPE _type;
	bool			_show_all;
	string			_key;
	
	
	void			readKey();
	void			readFile(const string & filename, string & content);
	void			writeFile(const string & filename, const string & content);
	void			printMainMenu();
	void 			printResult(bool encrypt, int res, const string & output);
};

#endif /* EncryptionManager_h */
