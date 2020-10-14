//
//  main.cpp
//  Playfair
//
//  Created by Eugen Marin and Elena Marin on 12/10/2020.
//

#include "EncryptionManager.h"

void encrypt(const string & filename);
void decrypt(const string & filename);
void printUsageError();

// -----------------------------------------------------------------------------
// Everything starts here .... :-)
// -----------------------------------------------------------------------------
int main(int argc, const char * argv[])
{
	switch (argc)
	{
		case 1:		// No arguments
		{
			EncryptionManager manager(PLAYFAIR, false);
			manager.run(true);
		}
			break;
		case 2:		// One argument. It MUST be -a or --all
			if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0)
			{
				EncryptionManager manager(PLAYFAIR, true);
				manager.run(true);
			}
			else
			{
				printUsageError();
				return -1;
			}
			break;
		case 3:		// Two arguments. They must be -e file or -d file
			if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0)
			{
				EncryptionManager manager(PLAYFAIR, false);
				manager.run(true, argv[2]);  		// encrypt file (argv[2])
			}
			else
			{
				if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0)
				{
					EncryptionManager manager(PLAYFAIR, false);
					manager.run(false, argv[2]);	// decrypt file (argv[2])
				}
				else
				{
					printUsageError();
					return -1;
				}
			}
			break;
		case 4:		// Three arguments. Must be -a -e file  or    -a -d file
			if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "--all") == 0)
			{
				if (strcmp(argv[2], "-e") == 0 || strcmp(argv[2], "--encrypt") == 0)
				{
					EncryptionManager manager(PLAYFAIR, true);
					manager.run(true, argv[3]);  				// encrypt file (argv[3])
				}
				else
				{
					if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "--decrypt") == 0)
					{
						EncryptionManager manager(PLAYFAIR, true);
						manager.run(false, argv[3]);			// decrypt file (argv[3])
					}
					else
					{
						printUsageError();
						return -1;
					}
				}
			}
			else
			{
				printUsageError();
				return -1;
			}
			break;
		default:
			printUsageError();
			return -1;
	}
	return 0;
}



void printUsageError()
{
	cout << endl << endl;
	cout << "Usage: playfair [options filename]" << endl;
	cout << "\t If no option, the application will request you to manually input the text" << endl << endl;
	cout << "\t Options:" << endl;
	cout << "\t -a | --all \t\t\t\tDisplays all information of the encryption/decryption process" << endl;
	cout << "\t -e | --encrypt filename\t\t Encrypt the text from the specified filename" << endl;
	cout << "\t -d | --decrypt filename\t\t Decrypt the text from the specified filename" << endl;
	cout << "\t In all cases, the key is searched in the info.key file, from the same directory" << endl;
	cout << "\t Outputs: out.txt file, in the same path" << endl << endl;
	cout << "Sample: playfair -a -e file.txt" << endl;
	cout << "        playfair --all --encrypt file.txt" << endl << endl;
}
