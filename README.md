# Playfair

## Scurt istoric
Desi atribuit baronului Lyon Playfair, acest algorit a fost inventat de Charles Wheatstone; fiind prezentat si publicat pentru prima oara la 26 martie 1854. Initial a fost respins de "British Foreign Office" pe motiv ca e prea complicat si greu de inteles.

Dupa crearea algoritmului, baronul Playfair a insistat si a convins guvernul britanic sa il adopte pentru uz oficial; acesta fiind si motivul pentru care ii poarta numele. Algoritmul a fost utilizat "in original" de catre armata britanica in razboiul din Africa de Sud, iar versiuni modificate ale acestuia au fost utilizate in Primul Razboi Mondial de armata britanica, precum si in Al Doilea Razboi Mondial de catre armata australiana.

## Descrierea algoritmului Playfair
Cifrul Playfair este un sistem de criptare simetric, bazat pe o cheie unica: aceeasi cheie este folosita atat pentru criptare, cat si pentru decriptare. Acest cifru face parte din categoria primitivelor criptografice de substitutie poligramica, ce presupun modificarea pozitiei unui caracter din textul clar in textul criptat, fara a-i modifica valoarea.
### Criptarea Playfair
Criptarea Playfair implica parcurgerea urmatorilor pasi:
1. Prelucrarea textului ce urmeaza a fi criptat
2. Prelucrarea cheii de criptare
3. Construirea matricei de criptare
4. Construirea mesajului criptat

#### 1. Prelucrarea textului ce urmeaza a fi criptat
Textul ce urmeaza a fi criptat trebuie sa fie format exclusiv din majuscule, fara spatii, semne de punctuatie, caractere speciale sau cifre. Astfel, intrucat textul de baza poate fi o propozitie, fraza, paragraf, etc., se impune o prelucrare prealabila si transformarea acestuia intr-un sir cursiv de majuscule, dupa cum urmeaza:
- Spatiile si caracterul TAB se vor inlocui cu caracterul 'Q'
- Caracterul '\n' (RETURN) se va inlocui cu 'W'
- Literele mici se transforma in majuscule ('a' -> 'A, 'b -> 'B' etc.)
- Litera 'J' se va transforma in litera 'I'
- Orice alt caracter este ignorat (sters)
Algoritmul de criptare presupune gruparea textului obtinut in perechi de litere, astfel, daca numarul total de caractere este impart, se va adauga 'Q' la sfarsitul acestuia pentru a genera ultima pereche completa, considerandu-se de fapt un spatiu. Deasemenea, algoritmul considera si o posibilitatea ca intr-un grup de caractere sa existe dubluri, situatie in care a doua litera se inlocuieste cu 'Y'.
> Nota: Algoritmul propriu-zis nu obliga utilizarea unor caractere anume pentru inlocuire, ci recomanda sa se foloseasca cele mai putin utilizate litere dintr-o anumita limba. Statistic, in limba romana, cele mai rar utilizate litere sunt 'Q' si 'W', urmate de 'Y' (https://commons.wikimedia.org/wiki/File:Frecvența_literelor_română.png).

Exemplu:
| Element         | Valoare                                                                             |
|-----------------|-------------------------------------------------------------------------------------|
| Sirul de baza   | Andreea cripteaza mesajul folosind un algoritm cunoscut                             |
| Sirul prelucrat | ANDREYAQCRIPTEAZAQMESAIULQFOLOSINDQUNQALGORITMQCUNOSCUTQ                            |
| Perechi generate| AN DR EY AQ CR IP TE AZ AQ ME SA IU LQ FO LO SI ND QU NQ AL GO RI TM QC UN OS CU TQ |

#### 2. Prelucrarea cheii de criptare
Cheia de criptare se prelucreaza _dupa aceeasi metoda_ prin care se prelucreaza textul ce urmeaza a fi criptat, cu mentiunea ca, in cazul cheii de criptare, nu este necesar sa avem un numar par de caractere.

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
- daca cele doua litere sunt pozitionate pe acelasi rand, se vor inlocui cu literele aflate pe pozitia **din dreapta** (in cazul in care o litera este ultima in rand, se va inlocui, circular, cu prima litera din acel rand). Spre exemplu, in mesajul nostru, perechea **DR** se va inlocui cu **TB**
- daca cele doua litere sunt pozitionate pe aceeasi coloana, se vor inlocui cu literele aflate pe ceeasi coloana, dar pe randul imediat **urmator** (in cazul in care o litera este ultima din coloana, se va inlocui, circular cu prima litera din aceeasi coloana). Spre exemplu, perechea **AN** se va inlocui cu **TV**
- daca literele se afla atat pe randuri, cat si pe coloane diferite, se va aplica **regula dreptunghiului**, traseul fiind pe verticala, de la cea de-a doua litera, catre prima. Astfel, prima litera se va inlocui cu litera de pe acelasi rand, dar corespunzatoare coloanei celei de-a doua litere, iar a doua cu litera de pe acelasi rans, dar corespunzatoare coloanei pe care se fla prima litera. Spre exemplu, in mesajul nostru, perechea **AQ** se va inlocui cu **EN**

Continuand exemplul de mai sus, se obtine urmatorul mesajul criptat:
| Element           | Valoare                                                                             |
|-------------------|-------------------------------------------------------------------------------------|
| **Sirul de baza** | **Andreea cripteaza mesajul folosind un algoritm cunoscut**                         |
| Sirul prelucrat   | ANDREYAQCRIPTEAZAQMESAIULQFOLOSINDQUNQALGORITMQCUNOSCUTQ                            |
| Perechi generate  | AN DR EY AQ CR IP TE AZ AQ ME SA IU LQ FO LO SI ND QU NQ AL GO RI TM QC UN OS CU TQ |
| Perechi criptate  | TV TB BE EN RK CO BA SV EN LS AI SO QY GN GQ AC UT UN OU EF OW HC DF PE NO UI SP BN |
| **Mesaj criptat** | **TVTBBEENRKCOBASVENLSAISOQYGNGQACUTUNOUEFOWHCDFPENOUISPBN**                        |

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
- daca cele doua litere sunt pozitionate pe acelasi rand, se vor inlocui cu literele aflate pe pozitia **din stanga** (in cazul in care o litera este prima in rand, se va inlocui, circular, cu ultima din acel rand). Spre exemplu, perechea **TB** se va inlocui cu **DR**
- daca cele doua litere sunt pozitionate pe aceeasi coloana, se vor inlocui cu literele aflate pe ceeasi coloana, dar pe randul imediat **anterior** (in cazul in care o litera este prima din coloana, se va inlocui, circular cu ultima litera din aceeasi coloana). Spre exemplu, perechea **TV** se va inlocui cu **AN**
- daca literele se afla atat pe randuri, cat si pe coloane diferite, se va aplica **regula dreptunghiului**, astfel incat prima litera se va inlocui cu litera de pe acelasi rand, dar corespunzatoare coloanei celei de-a doua litere, iar a doua cu litera de pe acelasi rans, dar corespunzatoare coloanei pe care se fla prima litera. Spre exemplu, perechea **EN** se va inlocui cu **AQ**

Dupa generarea sirului decriptat, 'X' se inlocuieste cu spatiu, pentru a genera textul final decriptat.

Mergand pe exemplul de mai sus, se obtine urmatorul mesajul decriptat:
| Element            | Valoare                                                                             |
|--------------------|-------------------------------------------------------------------------------------|
| **Sirul criptat**  | **TVTBBEENRKCOBASVENLSAISOQYGNGQACUTUNOUEFOWHCDFPENOUISPBN**                        |
| Perechi criptate   | TV TB BE EN RK CO BA SV EN LS AI SO QY GN GQ AC UT UN OU EF OW HC DF PE NO UI SP BN |
| Perechi decriptate | AN DR EY AQ CR IP TE AZ AQ ME SA IU LQ FO LO SI ND QU NQ AL GO RI TM QC UN OS CU TQ |
| Sir decriptat      | ANDREYAQCRIPTEAZAQMESAIULQFOLOSINDQUNQALGORITMQCUNOSCUTQ                            |
| **Mesaj criptat**  | **ANDREEA CRIPTEAZA MESAIUL FOLOSIND UN ALGORITM CUNOSCUT**                         |

## Limitari ale algoritmului Playfair
Cifrul Playfair se bazeaza pe lista de 25 de caratere majuscule ale alfabetului latin, pe inlocuirea caracterelor speciale si inlocuirea spatiului si a literelor duble cu o litera "cea mai putin folosita din punct de vedere statistic" intr-o anumita limba. Deasemenea, acest algoritm trateaza 'I' si 'J' ca fiind aceeasi litera: 'I'.
Dupa cum se vede, "MESAJUL" a fost decriptat ca "MESAIUL".



