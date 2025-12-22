# Orthodox Canonical Form

In C++ (e nel modulo 02 di 42) Orthodox Canonical Form vuol dire, in pratica:
“Ogni classe che scrivi deve dichiarare e definire esplicitamente questi 4 metodi speciali:
* costruttore di default
* costruttore di copia
* operatore di assegnazione di copia
* distruttore”
Così tutte le tue classi hanno la stessa “forma standard” e si comportano in modo prevedibile quando vengono create, copiate, assegnate e distrutte.

## Struttura header / sorgente

Header: MyClass.hpp
contiene solo la definizione della classe:
- dichiarazione dei membri privati
- dichiarazione dei 4 metodi canonici
- eventuali altri metodi.
Esempio (generico, non legato all’esercizio):

```c++
#ifndef MYCLASS_HPP
#define MYCLASS_HPP

class MyClass {
public:
    MyClass();                          // default
    MyClass(const MyClass& other);      // copy ctor
    MyClass& operator=(const MyClass& other); // copy assign
    ~MyClass();                         // dtor

private:
    int _value;
};

#endif
```

## Sorgente: MyClass.cpp

```c++
#include "MyClass.hpp"
#include <iostream>

MyClass::MyClass() : _value(0) {
    std::cout << "Default constructor called\n";
}

MyClass::MyClass(const MyClass& other) : _value(other._value) {
    std::cout << "Copy constructor called\n";
}

MyClass& MyClass::operator=(const MyClass& other) {
    std::cout << "Copy assignment operator called\n";
    if (this != &other) {
        this->_value = other._value;
    }
    return *this;
}

MyClass::~MyClass() {
    std::cout << "Destructor called\n";
}
```

### Default constructor
```c++
MyClass();
```
* Crea un oggetto “vuoto”, con valori iniziali sensati.

### Copy constructor

```cpp
MyClass(const MyClass& other);
```

Crea un nuovo oggetto copiando un oggetto già esistente.
Serve per decidere come copiare i dati (copia profonda, log, ecc.).

```c++
MyClass a;
MyClass b(a);      // usa il costruttore di copia
MyClass c = a;     // anche qui, costruttore di copia
```

### Copy assignment operator

```c++
MyClass& operator=(const MyClass& other);
```

* Viene chiamato quando assegni un oggetto già esistente ad un altro:
```c++
MyClass a;
MyClass b;
b = a;            // operatore di assegnazione di copia
```

### Destructor

```c++
~MyClass();
```
## SHALLOW COPY → “COPIA SUPERFICIALE”
È la copia automatica che farebbe il compilatore se tu non definisci nulla.
Significa:
* Copio solo il puntatore, non la memoria a cui punta.
Visivamente:
```c++
a.value -----> [ 42 ]

b (copia superficiale):
b.value -----> SAME memory [ 42 ]
```
👉 Quindi a e b condividono lo stesso int in memoria.
Se uno lo modifica, cambia anche per l’altro.
Se uno fa delete value, l’altro rimane con un puntatore “marcio” → 💥 crash.

## DEEP COPY → “COPIA PROFONDA”
Questa la scrivi tu nel copy constructor / operator=.
Significa:
* Copio il contenuto e alloco nuova memoria per la copia.
Visivamente:
```c++
a.value -----> [ 42 ]

b (copia profonda):
b.value -----> [ 42 ]   // diversa memoria!
```
👉 a e b sono veramente indipendenti.
Modificare uno non tocca l’altro.

# 📌 QUINDI, LA DIFFERENZA VERA È:
**Tipo di copia -> Cosa copia ->	Conseguenza**
**Shallow copy -> copia il puntatore -> a e b puntano allo stesso dato**
**Deep copy -> copia il dato in una nuova memoria	-> a e b sono indipendenti**

# Esempi pratici:
*** costruttore di copia superficiale**
*** costruttore di copia profonda**
*** operatore di assegnazione di copia**

### Classe di riferimento

```c++
class Box {
private:
    int* value;   // memoria dinamica
public:
    Box();                         // default
    Box(const Box& other);         // copy constructor
    Box& operator=(const Box&);    // copy assignment
    ~Box();                        // destructor
};

//Il suo default constructor:
Box::Box() {
    value = new int(0);
}
```
## COSTRUTTORE DI COPIA SUPERFICIALE (SHALLOW COPY)
Copia solo il puntatore, quindi i due oggetti condividono lo stesso int.
```c++
Box::Box(const Box& other) {
    // SHALLOW COPY: copio solo l’indirizzo
    this->value = other.value;
}
//🔍 Effetto visivo:
a.value ----> [ 42 ]
b.value ----> [ 42 ]   // stessa cella!
```
👉 Se cambi *b.value, cambia anche *a.value.
👉 Se distruggi a, “rompi” b.

## COSTRUTTORE DI COPIA PROFONDA (DEEP COPY)
Crea NUOVA memoria e copia il valore.
```c++
Box::Box(const Box& other) {
    // DEEP COPY: nuova memoria, stesso dato
    this->value = new int(*other.value);
}
//🔍 Effetto visivo:
a.value ----> [ 42 ]
b.value ----> [ 42 ]   // altra cella, indipendente
```
👉 Se cambi *b.value, *a.value NON cambia.
👉 Nessun rischio di double delete.

## OPERATORE DI ASSEGNAZIONE DI COPIA
Serve quando l’oggetto esiste già e deve diventare uguale ad un altro:
```c++
Box& Box::operator=(const Box& other) {
    if (this != &other) {                 // evita auto-assegnazione
        delete this->value;               // libero la memoria attuale
        this->value = new int(*other.value);  // deep copy
    }
    return *this;
}
```
⚠️ Perché si fa delete?
Perché l’oggetto ha già un valore allocato prima dell’assegnazione.

# Come funzionano in generale i floating-point
I numeri in virgola mobile (float, double) non vengono memorizzati esattamente come li scriviamo, ma in binario usando lo standard IEEE-754.
Alcuni numeri decimali non hanno una rappresentazione finita in binario, ad esempio:
* 0.1
* 0.2
* 0.3
→ Il computer li rappresenta con un’approssimazione.
🔍 Esempio:
```c++
0.1 in binario diventa qualcosa come:
0.0001100110011001100110011... (periodico infinito)
```
e quindi viene troncato/approssimato.
Conseguenza:
operazioni come:
```c++
0.1 + 0.2 == 0.3   // false
```
non danno il risultato che un umano si aspetterebbe.

## Come viene rappresentato un floating-point (IEEE-754)

Un numero reale viene “smontato” in tre parti:

```css
[ sign | exponent | mantissa ]
```
* sign = 0 positivo, 1 negativo
* exponent = esponente “sbiasato”
* mantissa = cifre significative
Il numero salvato in memoria usa la forma:
```scss
(-1)^sign × (1.mantissa) × 2^(exponent - bias)
```
Il bias serve a permettere esponenti negativi senza usare bit di segno separati
(es. per float: bias = 127).
🔍 Esempio:
Se in memoria trovi:
* sign = 0
* exponent salvato = 130
* mantissa = …
Allora l’esponente reale è:
```scss
130 − 127 = 3
```
e il numero rappresentato sarà:
```css
1.mantissa × 2^3
```
## Perché la stampa (cout) mostra cifre strane
Quando fai:
```c++
std::cout << x;
```
il computer deve convertire il valore binario (IEEE-754) in un numero decimale leggibile.
Questa conversione non è perfetta e può rivelare le approssimazioni interne.
Per evitare numeri troppo lunghi, C++ stampa solo un certo numero di cifre “sensate”.
A volte però possono apparire valori come:
```c++
0.30000000000000004
```
🔍 Esempio:
```c++
std::cout << (0.1 + 0.2);
// può stampare: 0.30000000000000004
```
Perché?
* 0.1 e 0.2 sono approssimati
* la loro somma è un’altra approssimazione
* convertire in decimale fa emergere la piccola differenza
Per vedere più o meno cifre puoi usare:
```c++
#include <iomanip>
std::cout << std::setprecision(20) << x;
```
**I numeri floating-point (float/double) non possono rappresentare in modo esatto molti numeri decimali, perché vengono memorizzati in binario seguendo lo standard IEEE-754. Numeri come 0.1 o 0.2 diventano frazioni binarie infinite e vengono approssimati.**
Un floating-point è composto da tre parti:
```c++
sign | exponent (con bias) | mantissa
//e rappresenta un numero secondo la formula:
(-1)^sign × (1.mantissa) × 2^(exponent - bias)
```
Poiché la mantissa ha un numero limitato di bit, la precisione è limitata.
Per questo operazioni come 0.1 + 0.2 non risultano esatte.
Quando stampiamo un floating-point, il computer converte il valore binario in decimale tramite algoritmi di formattazione (Dragon4/Grisu). Questa conversione può mostrare le piccole approssimazioni interne, producendo output come:
```txt
0.30000000000000004
```

### Riassunto Finale 
**→ I floating-point non rappresentano esattamente molti numeri decimali.**
**→ Vengono salvati come binari normalizzati: sign + exponent + mantissa.**
**→ Il valore reale è approssimato → piccoli errori nei calcoli.**
**→ Durante la stampa, la conversione da binario a decimale può mostrare questi errori.**
**→ È normale vedere output come 0.30000000000000004.**

# Fixed-point


Èun intero che tu interpreti come:
```c++
valore / (2^fractional_bits)
```
Esempio (esattamente quello di Module 02):
* _fractionalBits = 8
* valore interno = 256
* numero reale = 256 / 256 = 1.0

**Nel fixed-point:**
la precisione è costante
l’errore massimo è noto
Con 8 bit frazionari:
```text
precisione = 1 / 256 ≈ 0.00390625
```

### Come lavora davvero un fixed-point
🔹 Un fixed-point è:
un intero che TU interpreti come se avesse la virgola in una posizione fissa
Nel Module 02:
_fractionalBits = 8
quindi la “virgola” è 8 bit da destra
fattore di scala = 2⁸ = 256

**Esempi pratici**
* **Esempio 1 — rappresentare 1.0**
Con fixed-point a 8 bit frazionari:
```c++
1.0 × 256 = 256
```
👉 dentro _rawBits c’è:
```c++
_rawBits = 256
```
Ma TU lo interpreti come:
```c++
256 / 256 = 1.0
```
⚠️ Importante: la CPU vede solo 256 (un int)
La “virgola” è solo nella tua testa / nel tuo codice.

* **Esempio 2 — rappresentare 0.5**
```c++
0.5 × 256 = 128
_rawBits = 128
```
Interpretazione:
```c++
128 / 256 = 0.5
```

* **Esempio 3 — rappresentare 42.42**
```c++
42.42 × 256 ≈ 10859
_rawBits = 10859
```
Interpretazione:
```c++
10859 / 256 ≈ 42.421875
```

* **Operazioni: perché è potente**
➕ Somma
Supponiamo:
```c++
A = 1.5 → 1.5 × 256 = 384
B = 2.0 → 2.0 × 256 = 512
```
Somma:
```c++
384 + 512 = 896
```
Interpretazione:
```c++
896 / 256 = 3.5
```
👉 nessun errore strano
👉 solo interi
