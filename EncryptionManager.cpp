//
//  EncryptionManager.cpp
//  Playfair
//
//  Created by Eugen Marin and Elena Marin on 14/10/2020.
//

#include "EncryptionManager.h"
#include "Playfair.h"

const string KEY 		= "info.key";
const string OUTPUT 	= "out.txt";


// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
EncryptionManager::EncryptionManager(ENCRYPTION_TYPE etype, bool show_all)
{
	this->_type = etype;
	this->_show_all = show_all;
	this->readKey();
}

// -----------------------------------------------------------------------------
// run
//		Public function that starts encryption/decryption either by displaying menu
//		or by parsing an input file
//
//	@param IN  encrypt:		If true, it will encrypt the input. Otherwise it will decrypt it
//	@param IN  filename:	The name of the file to be encrypted or decrypted
// -----------------------------------------------------------------------------
void EncryptionManager::run(bool encrypt, const string & filename)
{
	if (filename.empty())
	{
		// In this case, encrypt parameter is ignored
		this->printMainMenu();
	}
	else
	{
		string input, output, info;
		this->readFile(filename, input);
		if (input.empty())
		{
			this->printResult(encrypt, -1, std::string());
			return;
		}
		Playfair playfair(this->_key, this->_show_all);
		int result = (encrypt) ? playfair.encrypt(input, output) : playfair.decrypt(input, output);
		if (result == 0)
		{
			this->writeFile(OUTPUT, output);
			info = "Please see ";
			info.append(OUTPUT);
		}
		this->printResult(encrypt, result, info);
	}
}

// -----------------------------------------------------------------------------
// Reads the key file
// -----------------------------------------------------------------------------
void EncryptionManager::readKey()
{
	ifstream file (KEY);
	if (file.is_open())
	{
		getline(file, this->_key);
		file.close();
	}
}

// -----------------------------------------------------------------------------
// Reads the full text from a file and appends it to content
// -----------------------------------------------------------------------------
void EncryptionManager::readFile(const string & filename, string & content)
{
	ifstream file (filename);
	if (file.is_open())
	{
		string sline;
		while (getline(file, sline)) 
		{
			content.append(sline);
			content.append("\n");
		}
		file.close();
	}
}

// -----------------------------------------------------------------------------
// Writes the full text to a file
// -----------------------------------------------------------------------------
void EncryptionManager::writeFile(const string & filename, const string & content)
{
	ofstream file (filename);
	if (file.is_open())
	{
		file << content;
		file.close();
	}
}


// -----------------------------------------------------------------------------
// Displays a menu and let user to choose between encryption and decryption
// -----------------------------------------------------------------------------
void EncryptionManager::printMainMenu()
{
	int op = -1;
	string input, output;
	int operation_result = -1;
	
	if (this->_key.empty()) {
		cout << "EncryptionManager Error: Key file not found !!! " << endl << endl;
		exit(EXIT_FAILURE);
	}
	
	Playfair playfair(this->_key, this->_show_all);
	while (op != 0)
	{
		cout << endl << endl;
		cout << "=====================================" << endl;
		cout << "Playfair - Main menu" << endl;
		cout << "=====================================" << endl;
		cout << "1. Encrypt a text" << endl;
		cout << "2. Decrypt a text" << endl;
		cout << "0. EXIT" << endl;
		cout << "=====================================" << endl;
		cout << "Please, select an option: ";
		cin >> op;
		cout << endl;
		
		if (op == 0)
			return;
		if (op == 1)
		{
			cout << "Plain text:      ";
			cin.ignore();
			getline(cin, input);
			operation_result = playfair.encrypt(input, output);
			printResult(true, operation_result, output);
		}
		if (op == 2)
		{
			cout << "Encrypted text:  ";
			cin.ignore();
			std::getline(std::cin, input);
			operation_result = playfair.decrypt(input, output);
			printResult(false, operation_result, output);
		}
	}
}

// -----------------------------------------------------------------------------
// DDisplays the encrypted or decrypted text or error message
// -----------------------------------------------------------------------------
void EncryptionManager::printResult(bool encrypt, int res, const string & output)
{
	if (res == 0)
	{
		string header = (encrypt) ? "Encrypted text:  " : "Plain text:      ";
		cout << header << output << endl;
	}
	else
	{
		string header = (encrypt) ? "Encryption error " : "Decryption error ";
		cout << header << " (Code: " << res << ")" << endl;
	}

}
