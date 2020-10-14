Playfair: main.o EncryptionManager.o Playfair.o
	g++ -o Playfair main.o EncryptionManager.o Playfair.o

main.o: main.cpp
	g++ -std=gnu++11 -o main.o -c main.cpp

EncryptionManager.o: EncryptionManager.cpp
	g++ -std=gnu++11 -o EncryptionManager.o -c EncryptionManager.cpp

Playfair.o: playfair.cpp
	g++ -std=gnu++11 -o Playfair.o -c Playfair.cpp

clean: 
	rm -f Playfair *.o
