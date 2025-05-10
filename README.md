# Eter - Joc de Strategie Modern C++

Acesta este proiectul "Eter", un joc de strategie pentru 2 jucători, dezvoltat în Modern C++ ca parte a cursului "Modern C++ 2024-2025" la Informatică Aplicată. Jocul este inspirat de clasicele "X și O" sau "Connect 4", dar introduce elemente strategice noi, numere pe cărți și diverse moduri de joc.

Această implementare se concentrează pe modurile de joc **Antrenament (a)**, **Duelul Vrăjitorilor (b)** și **Duelul Elementelor (c)**, incluzând regulile speciale pentru **Iluzii** și **Explozii**, toate funcționând într-o interfață consolă.

## Cuprins

1.  [Reguli de Bază](#reguli-de-bază)
2.  [Reguli Speciale Implementate](#reguli-speciale-implementate)
    *   [Iluzii](#iluzii)
    *   [Explozii](#explozii)
3.  [Moduri de Joc Implementate](#moduri-de-joc-implementate)
    *   [1. Modul Antrenament (a)](#1-modul-antrenament-a)
    *   [2. Duelul Vrăjitorilor (b)](#2-duelul-vrăjitorilor-b)
    *   [3. Duelul Elementelor (c)](#3-duelul-elementelor-c)
4.  [Funcționalități Adiționale](#funcționalități-adiționale)
5.  [Tehnologii Folosite](#tehnologii-folosite)
6.  [Cerințe de Sistem și Compilare](#cerințe-de-sistem-și-compilare)
7.  [Instalare și Rulare](#instalare-și-rulare)
8.  [Principii de Dezvoltare](#principii-de-dezvoltare)
9.  [Funcționalități Planificate (Viitor)](#funcționalități-planificate-viitor)
10. [Autori](#autori)

## Reguli de Bază

Jocul se desfășoară pe o tablă pătratică (3x3 sau 4x4, în funcție de modul de joc). Fiecare jucător are un set de cărți numerotate (1-4) și, în unele moduri, o carte specială "Eter".

*   **Plasarea Cărților:**
    *   Pe un spațiu gol adiacent altor cărți.
    *   Deasupra altei cărți, dacă numărul cărții plasate este strict mai mare. Cărțile acoperite rămân pe tablă (formează teancuri).
    *   Cartea "Eter": se plasează doar pe spațiu gol, nu poate fi acoperită, are valoarea 1 la numărătoare și participă la condiția de câștig.
*   **Adiacență:** Nicio carte nu poate deveni izolată.
*   **Dimensiunea Tablei:** Tabla crește dinamic, dar nu poate depăși dimensiunea maximă stabilită (3x3 sau 4x4).
*   **Sfârșitul Jocului:**
    1.  Un jucător creează o linie/coloană/diagonală cu cărțile sale neacoperite.
    2.  Un jucător ocupă ultimul spațiu gol (oponentul mai are o tură).
    3.  Un jucător își joacă ultima carte (oponentul mai are o tură).
    4.  Dacă nu s-a câștigat prin linie, se numără punctele cărților vizibile; cel cu mai multe puncte câștigă.

## Reguli Speciale Implementate

Următoarele reguli speciale sunt active în toate modurile de joc implementate:

### Iluzii

*   O dată pe joc, fiecare jucător poate plasa o carte cu fața în jos (exclus Eter) pe un spațiu gol.
*   Propria iluzie nu poate fi acoperită de sine.
*   Oponentul poate încerca să acopere iluzia; cartea se întoarce. Dacă numărul oponentului e <=, cartea sa e eliminată din joc.
*   Iluziile participă la linii/coloane/diagonale și au valoarea 1 la numărătoarea finală.

### Explozii

*   O dată pe joc, când al doilea rând devine complet ocupat, jucătorul care l-a umplut poate activa explozia.
*   O carte de explozie (generată algoritmic, cu 2-4 efecte pe 3x3, 3-6 pe 4x4) indică pozițiile afectate. Efectul de "groapă" este mai rar.
*   Jucătorul poate roti cartea de explozie.
*   Efecte posibile: eliminare carte din joc, întoarcere carte în mână (nu poate fi folosită în tura următoare), creare groapă (spațiu blocat, teanc eliminat).
*   Dacă un efect creează cărți neadiacente, efectul se ignoră.

## Moduri de Joc Implementate

Următoarele moduri de joc sunt implementate și funcționale în consolă:

### 1. Modul Antrenament (a)

*   **Tabla:** 3x3
*   **Cărți/Jucător:** 7 cărți (1, 1, 2, 2, 3, 3, 4)
*   **Format Meci:** Cel mai bun din 3 jocuri (primul la 2 victorii câștigă meciul)
*   **Reguli Speciale Active:** Iluzii, Explozii.

### 2. Duelul Vrăjitorilor (b)

*   **Tabla:** 4x4
*   **Cărți/Jucător:** 10 cărți (1, 1, 2, 2, 2, 3, 3, 3, 4, Eter)
*   **Vrăjitori:** Fiecare jucător primește un vrăjitor aleatoriu și distinct, cu o putere magică unică.
    *   Puterea se activează o dată pe joc și consumă întreaga tură.
    *   Puterea se poate activa o singură dată pe meci.
    *   *Lista puterilor vrăjitorilor este conform specificațiilor proiectului.*
*   **Format Meci:** Cel mai bun din 5 jocuri (primul la 3 victorii câștigă meciul)
*   **Reguli Speciale Active:** Iluzii, Explozii.

### 3. Duelul Elementelor (c)

*   **Tabla:** 4x4
*   **Cărți/Jucător:** 10 cărți (1, 2, 2, 2, 3, 3, 3, 4, Eter)
*   **Puteri ale Elementelor:** Se aleg 2 puteri distincte ale elementelor, aleatoriu, la începutul meciului. Ambele puteri pot fi folosite de ambii jucători.
    *   O putere folosită de un jucător nu mai e disponibilă pentru celălalt jucător în acel joc.
    *   Puterea se activează o dată pe joc și consumă întreaga tură.
    *   *Lista puterilor elementelor este conform specificațiilor proiectului.*
*   **Format Meci:** Cel mai bun din 5 jocuri (primul la 3 victorii câștigă meciul)
*   **Reguli Speciale Active:** Iluzii, Explozii.

## Funcționalități Adiționale

*   **Salvare/Încărcare Joc:** Posibilitatea de a salva starea curentă a unui joc și de a o încărca ulterior pentru a continua.
*   **Interfață Consolă:** Toate interacțiunile se realizează prin intermediul consolei.

## Tehnologii Folosite

*   **Limbaj de Programare:** C++ (cu accent pe Modern C++)
*   **Management de Proiect:** Git, GitHub
*   **Compilator:** (ex: GCC, Clang, MSVC - compatibil cu C++17/20)
*   **Build System:** (ex: CMake - recomandat)

## Cerințe de Sistem și Compilare

*   Un compilator C++ modern (C++17 sau mai nou).
*   Git pentru clonarea repository-ului.
*   (Opțional, dar recomandat) CMake pentru generarea fișierelor de build.

## Instalare și Rulare

1.  **Clonați repository-ul:**
    ```bash
    git clone https://github.com/Lau-Tisca/EterGame # Înlocuiți cu link-ul corect dacă este altul
    cd EterGame # Sau numele folderului proiectului
    ```
2.  **Compilați proiectul:**
    *   **Cu CMake (recomandat):**
        ```bash
        mkdir build
        cd build
        cmake ..
        cmake --build . # Sau make, sau deschideți soluția generată în IDE (ex: Visual Studio)
        ```
    *   **Manual (exemplu cu g++):**
        ```bash
        # Navigați la folderul cu surse și compilați fișierele .cpp
        # g++ -std=c++17 main.cpp game.cpp player.cpp -o Eter (exemplu simplificat)
        ```
3.  **Rulați executabilul:**
    *   Din folderul `build` (dacă ați folosit CMake):
        ```bash
        ./Eter # Pe Linux/macOS
        Eter.exe # Pe Windows
        ```
    *   Sau direct, dacă ați compilat manual în folderul principal.

La pornire, veți fi întâmpinați de un meniu principal de unde puteți alege modul de joc, încărca un joc salvat etc.

## Principii de Dezvoltare

*   **Clean Code:** S-a urmărit scrierea unui cod curat, lizibil și mentenabil, conform recomandărilor din `CLEAN CODE TIPS`.
*   **Modern C++:** S-a pus accent pe utilizarea elementelor specifice Modern C++ (ex: `const ref`, `move semantics`, smart pointers, algoritmi STL, structuri de date moderne etc.), conform cerințelor proiectului.
*   **Modularitate:** Structurarea codului în clase și module logice pentru o mai bună organizare.

## Funcționalități Planificate (Viitor)

Conform cerințelor complete ale proiectului, următoarele funcționalități ar putea fi adăugate:

*   Implementarea modului de joc combinat **Duelul Vrăjitorilor + Duelul Elementelor (b+c)**.
*   Implementarea modurilor de joc **Turneu** și **Viteză**.
*   Dezvoltarea unei **interfețe grafice (GUI)** utilizând Qt.
*   Implementarea unui **sistem de recomandare** pentru mutări.
*   Adăugarea unui **element custom** pentru punctaj suplimentar.

## Autori

**Echipa Alt+F4**

*   **Tișcă Laurențiu-Ștefan** ([Lau-Tisca](https://github.com/Lau-Tisca))
*   **Vicas Antonio Samir**
*   **Iacob Giulia**
*   **Tiba Stefan Vlad**
