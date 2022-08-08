//
//  Playfair.cpp
//  Playfair
//
//  Created by Eugen Marin and Elena Marin on 12/10/2020.
//
#include "Playfair.h"
#include <algorithm>
#include <iostream>

#define USE_STL_FEATURES 

/**
 * @brief Construct a new Playfair:: Playfair object
 * 
 * @param key Encryption / decryption key
 * @param show_detailed_info If true it will display detailed infrormation
 */
Playfair::Playfair(const std::string & key, bool show_detailed_info)
{
	this->_show_all_info =  show_detailed_info;
	
	if (key.length() == 0)
		return;
	this->_key = this->convertToUpper(key);
	if (this->_key.length() == 0)
		return;
	
	this->buildTable();
}


/**
 * @brief Public function that takes a plain text and encrypts it using the _key
 * 
 * @param plain_text Text to be encrypted
 * @param encrypted_text Resulted text after encryption
 * 
 * @returns 0 if success or a negative value
 */
int Playfair::encrypt(const std::string & plain_text, /*out*/ std::string & encrypted_text)
{
	string s = this->convertToUpper(plain_text);
	vector<string> pair_array;
	this->buildPairs(s, pair_array);
	
	if (_show_all_info)
	{
		this->printDetailedInfoHeader();
		cout << "  Pair of values:  ";
		for_each (pair_array.begin(), pair_array.end(), [](string & e) { cout << e << " "; });
		cout << endl;
		cout << "  Encrypted pairs: ";
	}
	
	encrypted_text.clear();
	for (auto elem : pair_array)
	{
		this->getEncryptedPair(elem);
		if (_show_all_info)
			cout << elem << " ";
		encrypted_text.append(elem);
	}
	
	if (_show_all_info)
	{
		this->printDetailedInfoFooter();
	}
	
	return 0;
}

/**
 * @brief Public function that takes an ecrypted text and decrypts it using the _key
 * 
 * @param encrypted_text Text to be decrypted
 * @param plain_text Resulted text after decryption
 * 
 * @returns 0 if success or a negative value
 */
int Playfair::decrypt(const std::string & encrypted_text, /*out*/ std::string & plain_text)
{
	string s = this->convertToUpper(encrypted_text);
	vector<string> pair_array;
	this->buildPairs(s, pair_array);
	
	if (_show_all_info)
	{
		this->printDetailedInfoHeader();
		cout << "  Pair of values:  ";
		for_each (pair_array.begin(), pair_array.end(), [](string & e) { cout << e << " "; });
		cout << endl;
		cout << "  Decrypted pairs: ";
	}
	
	plain_text.clear();
	for (auto elem : pair_array)
	{
		this->getDecryptedPair(elem);
		if (_show_all_info)
			cout << elem << " ";
		plain_text.append(elem);
	}
	
	if (_show_all_info)
	{
		this->printDetailedInfoFooter();
	}
	
	for (string::size_type i = 0; i < plain_text.length(); i++)
	{
		switch (plain_text[i])
		{
		case 'Q':
			plain_text[i] = ' ';
			break;
		case 'W':
			plain_text[i] = '\n';
			break;
		case 'Y':
			if (i > 0 && i % 2 == 1)				// Only if it's an even character
				plain_text[i] = plain_text[i - 1];
			break;
		default:
			break;
		}
	}
	
	return 0;
}

// -----------------------------------------------------------------------------
// printTable
//		Public function that displays the table in matrix format
// -----------------------------------------------------------------------------
void Playfair::printTable()
{
	cout << endl;
	cout << "  Playfair Table:" << endl;
	cout << "  +-----------------------------------+" << endl;
	cout << "  |     |  1  |  2  |  3  |  4  |  5  |" << endl;
	cout << "  +-----+-----+-----+-----+-----+-----+" << endl;
	int i = 1;
	for (auto row : this->_table)
	{
		cout << "  |  " << i++ << "  |";
		int j = 1;
		for (auto elem : row)
		{
			cout << "  " << elem << "  ";
			if (j < 5)	cout << " ";
			else		cout << "|";
			j++;
		}
		cout << endl;
		if (i < 6)
			cout << "  +-----+                             +" << endl;
	}
	cout << "  +-----------------------------------+" << endl;

}

// -----------------------------------------------------------------------------
// convertToUpper
//		Private function that converts all characters to uppercase 
//		For each character c it checks:
//			if between 65 and  90 (ASCII codes: 'A' = 65, 'Z' = 90) keep it as is
//			if between 97 and 122 (ASCII codes: 'a' = 97, 'z' = 122) keep c - 32 (e.g. 'a' -> 'A', 'b' -> 'B')
//			if SPACE or TAB, replace with 'Q'
//			if NEW LINE, replace with 'W'
//			if other value, ignore it
// 			make I/J => use 73 for both 'I' and 'J'
//
//	@param IN  s:		Text to be converted
//	@returns string:	Converted string.
// -----------------------------------------------------------------------------
std::string Playfair::convertToUpper(const std::string & s)
{
	string result = s;

#ifdef USE_STL_FEATURES

	for_each (result.begin(), result.end(), [](char & c) {
		c = toupper(c);
	});

	replace(result.begin(), result.end(), 'J', 'I');
	replace(result.begin(), result.end(), ' ', 'Q');
	replace(result.begin(), result.end(), '\t', 'Q');
	replace(result.begin(), result.end(), '\n', 'W');

	// Remove all special characters
	result.erase(
		remove_if (result.begin(), result.end(), [](char & c) {
    		return (isalpha(c) == false && isspace(c) == false && c != '\t' && c != '\n');  
		}), 
		result.end()
	);

#else
	stringstream res;
	
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 65 && s[i] <= 90)			// Already upper case, keep it
			res << (char)s[i];
		else
		{
			if (s[i] >= 97 && s[i] <= 122)		// Lower case, convert it to upper case
				res << (char)(s[i] - 32);
			else
			{
				switch (s[i])
				{
					case ' ':				// SPACE or TAB
					case '\t':				// replace with 'Q'
						res << 'Q';
						break;
					case '\n':				// NEW LINE, replace with 'W'
						res << 'W';
						break;
					default:
						break;
				}
			}
		}
	}
	res.flush();

	result = res.str();
	replace(result.begin(), result.end(), 'J', 'I');
#endif	
	return result;

}

// -----------------------------------------------------------------------------
// buildTable
//		Creates 5x5 Playfair table starting to the key
// -----------------------------------------------------------------------------
void Playfair::buildTable()
{
	char c;
	
	// First, let's clear the _table
	this->_table.clear();
	
	vector<char> row;
	
	// Add the key characters (unique)
	for (int k = 0; k < this->_key.length(); k++)
	{
		c = this->_key[k];
		// check if c already exists in row vector or in the table
		if (std::find(row.begin(), row.end(), c) == row.end() && this->isNewChar(c) == true)
		{
			row.push_back(c);
			if (row.size() == 5)
			{
				this->_table.push_back(row);
				row.clear();
				if (this->_table.size() == 5)	// We just filled the whole table with the KEY
					return;
			}
		}
	}
	
	// Now, start adding all remaining characters
	c = 65;
	while (c <= 90)
	{
		// check if c already exists in row vector or in the table
		if (std::find(row.begin(), row.end(), c) == row.end() && this->isNewChar(c) == true)
		{
			row.push_back(c);
			if (row.size() == 5)
			{
				this->_table.push_back(row);
				row.clear();
				if (this->_table.size() == 5)	// We just filled the whole table with the KEY
					return;
			}
		}
		c++;									// Move to next character
		if (c == 'J')							// If next character is 'J', ignore it and move to next one
			c++;
	}
}

// -----------------------------------------------------------------------------
// buildPair
//		Creates a vector of 2-char strings. It replaces the doubles with Y and
//		padds the last character with Q is odd number of chars
//
//	@param IN  input:		String to be parsed
//	@param OUT output:		Resulted vector of strings
// -----------------------------------------------------------------------------
void Playfair::buildPairs(const std::string & input, /*out*/std::vector<std::string> & output)
{
	output.clear();
	string temp = input;
	if (temp.length() % 2 == 1)
		temp.push_back('Q');			// Add 'Q' (as SPACE) if odd number of characters
	
	string row;
	for (auto it : temp)
	{
		row.push_back(it);
		if (row.length() == 2)
		{
			// Replace with 'Y' if same characters
			if (row[0] == row[1])
			{
				// Corner case: if both are already 'Y', make the second one 'Q'
				row[1] = (row[0] == 'Y') ? 'Q' : 'Y';
			}
			
			// Now, add row in the vector
			output.push_back(row);
			row.clear();
		}
	}
}

// -----------------------------------------------------------------------------
// getEncryptedPair
//		Parses the table and gets the corresponding pair characters
//
//	@param elem:	String to be parsed and replaced with the corresponsing characters
// -----------------------------------------------------------------------------
void Playfair::getEncryptedPair(std::string & elem)
{
	// Search the positions in the table
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	
	this->findCharacterInTable(elem[0], x1, y1);
	this->findCharacterInTable(elem[1], x2, y2);
		
	if (x1 == x2)			// Same row, take the elem from the "right"
	{
		y1 = (y1 < 4) ? y1 + 1 : 0;
		y2 = (y2 < 4) ? y2 + 1 : 0;
	}
	else					// Different row
	{
		if (y1 == y2)		// Same column, take the element from "bottom"
		{
			x1 = (x1 < 4) ? x1 + 1 : 0;
			x2 = (x2 < 4) ? x2 + 1 : 0;
		}
		else				// Different row, different column
		{
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}
	}
	
	elem[0] = this->getCharOnPos(x1, y1);
	elem[1] = this->getCharOnPos(x2, y2);
}

// -----------------------------------------------------------------------------
// getDecryptedPair
//		Parses the table and gets the corresponding pair characters
//
//	@param elem:	String to be parsed and replaced with the corresponsing characters
// -----------------------------------------------------------------------------
void Playfair::getDecryptedPair(std::string & elem)
{
	// Search the positions in the table
	int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
	
	this->findCharacterInTable(elem[0], x1, y1);
	this->findCharacterInTable(elem[1], x2, y2);
		
	if (x1 == x2)			// Same row, take the elem from the "left"
	{
		y1 = (y1 > 0) ? y1 - 1 : 4;
		y2 = (y2 > 0) ? y2 - 1 : 4;
	}
	else					// Different row
	{
		if (y1 == y2)		// Same column, take the element from "top"
		{
			x1 = (x1 > 0) ? x1 - 1 : 4;
			x2 = (x2 > 0) ? x2 - 1 : 4;
		}
		else				// Different row, different column
		{
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}
	}
	
	elem[0] = this->getCharOnPos(x1, y1);
	elem[1] = this->getCharOnPos(x2, y2);
	
}


// -----------------------------------------------------------------------------
// findCharacterInTable
//		Retrieves the x and y of the character c in _table
//
//	@param IN  c:		Character to be found
// 	@param OUT x, y:	Row and column of the character.
// -----------------------------------------------------------------------------
void Playfair::findCharacterInTable(char c, int & x, int & y)
{
	int i = 0;
	int j = 0;
	for (auto row : this->_table)
	{
		for (auto ch : row)
		{
			if (ch == c)
			{
				x = i;
				y = j;
				return;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

// -----------------------------------------------------------------------------
// findCharacterInTable
//		Retrieves the character at the specified position
//
// 	@param IN x, y:	Row and column of the character.
// -----------------------------------------------------------------------------
char Playfair::getCharOnPos(int x, int y)
{
	int i = 0, j = 0;
	for (auto row : this->_table)
	{
		if (i == x)
		{
			for (char ch : row)
			{
				if (j == y)
				{
					return ch;
				}
				j++;
			}
		}
		i++;
	}
	return 'X';
}

// -----------------------------------------------------------------------------
// isNewChar
//		Private function that checks if the current char is already in the table
//
//	@param IN  c:		Character to be checked for
//	@returns true if the character is new to the table (not found)
// -----------------------------------------------------------------------------
bool Playfair::isNewChar(char c)
{
	bool res = true;
	
	if (this->_table.empty() == false)
	{
		for (auto & row : this->_table)
		{
			for (auto & character : row)
			{
				if (character == c)
				{
					res = false;
					break;
				}
			}
		}
	}
	
	return res;
}

// -----------------------------------------------------------------------------
// Utility functions
//
void Playfair::printDetailedInfoHeader()
{
	cout << endl;
	cout << "--- BEGIN: ALL DETAILED INFO ------------------------------" << endl;
	this->printTable();
	cout << "  Key:             " << this->_key << endl;
}

void Playfair::printDetailedInfoFooter()
{
	cout << endl << endl;
	cout << "--- END ALL DETAILED INFO --------------------------------" << endl;
	cout << endl << endl;
}
