# Playfair

## Scurt istoric
Desi atribuit baronului Lyon Playfair, acest algorit a fost inventat de Charles Wheatstone; fiind prezentat si publicat pentru prima oara la 26 martie 1854. Initial a fost respins de "British Foreign Office" pe motiv ca e prea complicat si greu de inteles.

Dupa crearea algoritmului, baronul Playfair a insistat si a convins guvernul britanic sa il adopte pentru uz oficial; acesta fiind si motivul pentru care ii poarta numele. Algoritmul a fost utilizat "in original" de catre armata britanica in razboiul din Africa de Sud, iar versiuni modificate ale acestuia au fost utilizate in Primul Razboi Mondial de armata britanica, precum si in Al Doilea Razboi Mondial de catre armata australiana.

## Descrierea algoritmului Playfair
### Criptarea Playfair
Criptarea Playfair implica parcurgerea urmatorilor pasi:
1. Prelucrarea textului ce urmeaza a fi criptat
2. Prelucrarea cheii de criptare
3. Construirea matricei de criptare
4. Construirea mesajului criptat

#### 1. Prelucrarea textului ce urmeaza a fi criptat
Textul ce urmeaza a fi criptat trebuie sa fie format exclusiv din majuscule, fara spatii, semne de punctuatie, caractere speciale sau cifre. Astfel, intrucat textul de baza poate fi o propozitie, fraza, paragraf, etc., se impune o prelucrare prealabila si transformarea acestuia intr-un sir cursiv de majuscule, dupa cum urmeaza:
- Spatiile se inlocuiesc cu caracterul X
- Literele mici se transforma in majuscule ('a' -> 'A, 'b -> 'B' etc.)
- Litera 'J' se va transforma in litera 'I'
- Orice alt caracter este ignorat (sters)
Algoritmul de criptare presupune gruparea textului obtinut in perechi de litere, astfel, daca numarul total de caractere este impart, se va adauga 'X' la sfarsitul acestuia pentru a genera ultima pereche completa. Deasemenea, daca o pereche contine doua litere identice, a doua litera se va inlocu cu 'Z'.
> Nota: Algoritmul propriu-zis nu obliga utilizarea unor caractere anume pentru inlocuire, ci recomanda sa se foloseasca cele mai putin utilizate litere dintr-o anumita limba. Astfel, caracterele 'X', respectiv'Z' reprezinta alegerea noastra.

Exemplu:
| Element         | Valoare                                            |
|-----------------|----------------------------------------------------|
| Sirul de baza   | Andreea o va ajuta pe Maria, apoi va pleca.        |
| Sirul prelucrat | ANDREEAOVAAJUTAPEMARIAAPOIVAPLECA                  |
| Perechi generate| AN DR EZ AO VA AI UT AP EM AR IA AP OI VA PL EC AX |

#### 2. Prelucrarea cheii de criptare
Cheia de criptare se prelucreaza _dupa aceeasi metoda_ prin care se prelucreaza textul ce urmeaza a fi criptat, cu mentiunea ca, in cazul cheii de criptare, nu este necesar avem un numar par de caractere.

Exemplu:
| Element          | Valoare                 |
|------------------|-------------------------|
| Cheia de criptare| Aici este cheia secreta |
| Cheia prelucrata | AICIESTECHEIASECRETA    |

#### 3. Construirea matricii de criptare
Matricea de criptare este un tabel de 5 x 5 elemente si se construieste dupa urmatorul algoritm:
- incepand din coltul din stanga sus, se completeaza pe fiecare rand cu caracterele de la cheia de crptare prelucrata, **luate in mod unic**
- se completeaza restul celulelor cu literele alfabetului ramase, deasemenea **in mod unic**

Pe baza exemplului de mai sus, matricea de criptare este urmatoarea:
|       | 1 | 2 | 3 | 4 | 5 |
|-------|---|---|---|---|---|
| **1** | A | I | C | E | S |
| **2** | T | H | R | B | D |
| **3** | F | G | K | L | M |
| **4** | N | O | P | Q | U |
| **5** | V | W | X | Y | Z |
> Nota: Cu cat cheia utilizata este mai lunga, cu atât textul criptat va fi mai greu de criptanalizat. Se recomanda folosirea unei fraze / propozitii de lungime medie (3-5 cuvinte scurte).

#### 4. Construirea mesajului criptat
Mesajul criptat se construieste pe baza matricii de criptare luand fiecare pereche de litere si aplicand dupa urmatorul algoritm:
- daca cele doua litere sunt pozitionate pe acelasi rand, se vor inlocui cu literele aflate pe pozitia **din dreapta** (in cazul in care o litera este ultima in rand, se va inlocui, circular, cu prima litera din acel rand). Spre exemplu, perechea **IE** se va inlocui cu **CS**, iar perechea **IS** se va inlocui cu **CA**
- daca cele doua litere sunt pozitionate pe aceeasi coloana, se vor inlocui cu literele aflate pe ceeasi coloana, dar pe randul imediat **urmator** (in cazul in care o litera este ultima din coloana, se va inlocui, circular cu prima litera din aceeasi coloana). Spre exemplu, perechea **TN** se va inlocui cu **FV**, iar perechea **TV** se va inlocui cu **FA**
- daca literele se afla atat pe randuri, cat si pe coloane diferite, se va aplica **regula dreptunghiului**, astfel incat prima litera se va inlocui cu litera de pe acelasi rand, dar corespunzatoare coloanei celei de-a doua litere, iar a doua cu litera de pe acelasi rans, dar corespunzatoare coloanei pe care se fla prima litera. Spre exemplu, perechea **AL** se va inlocui cu **EF**

Continuand exemplul de mai sus, se obtine urmatorul mesajul criptat:
| Element           | Valoare                                                        |
|-------------------|----------------------------------------------------------------|
| **Sirul de baza** | **Andreea o va ajuta pe Maria, apoi va pleca.**                |
| Sirul prelucrat   | ANDREZAXOXVAXAIUTAXPEXMARIAXAPOIXVAXPLECAX                     |
| Perechi generate  | AN DR EZ AX OX VA XA IU TA XP EX MA RI AX AP OI XV AX PL EC AX |
| Perechi criptate  | TV TB SY CV PW AT VC SO FT CX CY FS HC CV CN WH YW CV QK SE CV |
| **Mesaj criptat** | **TVTBSYCVPWATVCSOFTCXCYFSHCCVCNWHYWCVQKSECV**                 |

### Decriptarea Playfair
Dupa cum se poate intui, procesul de decriptare este similar cu cel al criptarii. Intrucat mesajul de decriptat este deja formatat, in principiu se sare peste pasul referitor la formatarea textului.
Astfel, algoritmul de decriptare presupune urmatorii pasi:
- Prelucrarea cheii de decriptare
- Construirea matricii de decriptare
- Decriptarea propriu-zisa

#### 1. Prelucrarea cheii de decriptare
Cheia de decriptare se prelucreaza in mod identic cu modul in care se prelucreaza cheia de criptare: se elimina spatiile, semnele de punctuatie si se transforma intr-un sir de majuscule.

#### 2. Contruirea matricii de decriptare
Intrucat avem aceeasi cheie de decriptare, matricea de decriptare este identica cu matricea de criptare, prezentata mai sus.

#### 3. Decriptarea propriu-zisa
Acesta este algoritmul _invers_ celui folosit la criptare. Astfel, luand fiecare pereche de litere aplicam urmatorul algoritm:
- daca cele doua litere sunt pozitionate pe acelasi rand, se vor inlocui cu literele aflate pe pozitia **din stanga** (in cazul in care o litera este prima in rand, se va inlocui, circular, cu ultima din acel rand). Spre exemplu, perechea **IE** se va inlocui cu **AC**, iar perechea **AE** se va inlocui cu **SC**
- daca cele doua litere sunt pozitionate pe aceeasi coloana, se vor inlocui cu literele aflate pe ceeasi coloana, dar pe randul imediat **anterior** (in cazul in care o litera este prima din coloana, se va inlocui, circular cu ultima litera din aceeasi coloana). Spre exemplu, perechea **TN** se va inlocui cu **AF**, iar perechea **AN** se va inlocui cu **VF**
- daca literele se afla atat pe randuri, cat si pe coloane diferite, se va aplica **regula dreptunghiului**, astfel incat prima litera se va inlocui cu litera de pe acelasi rand, dar corespunzatoare coloanei celei de-a doua litere, iar a doua cu litera de pe acelasi rans, dar corespunzatoare coloanei pe care se fla prima litera. Spre exemplu, perechea **AL** se va inlocui cu **EF**

Dupa generarea sirului decriptat, 'X' se inlocuieste cu spatiu, pentru a genera textul final decriptat.

Mergand pe exemplul de mai sus, se obtine urmatorul mesajul decriptat:
| Element            | Valoare                                                        |
|--------------------|----------------------------------------------------------------|
| **Sirul criptat**  | **TVTBSYCVPWATVCSOFTCXCYFSHCCVCNWHYWCVQKSECV**                 |
| Perechi criptate   | TV TB SY CV PW AT VC SO FT CX CY FS HC CV CN WH YW CV QK SE CV |
| Perechi decriptate | AN DR EZ AX OX VA XA IU TA XP EX MA RI AX AP OI XV AX PL EC AX |
| Sir decriptat      | ANDREZAXOXVAXAIUTAXPEXMARIAXAPOIXVAXPLECAX                     |
| **Mesaj criptat**  | **ANDREZA O VA AIUTA PE MARIA APOI VA PLECA**                  |
