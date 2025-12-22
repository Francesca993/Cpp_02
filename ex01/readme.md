# ex01

### Regola base
**_rawBits contiene il valore “scalato”**
**valore reale ≈ _rawBits / 256**

* Fixed(int) (int → fixed)
Esempio: Fixed b(10);
int = 10
lo trasformi in raw così:
raw = 10 * 256 = 2560 (equivalente a 10 << 8)
quindi dentro l’oggetto:
_rawBits = 2560
Controllo:
toFloat() farà 2560 / 256 = 10.0
toInt() farà 2560 >> 8 = 10

* Fixed(float) (float → fixed)
Esempio: Fixed c(42.42f);
float = 42.42
raw ideale = 42.42 * 256 = 10859.52
ma _rawBits è un int, quindi devi arrotondare:
raw = roundf(10859.52) = 10860
quindi:
_rawBits = 10860
Controllo:
toFloat() = 10860 / 256 = 42.421875
vedi perché nel subject viene 42.4219 (stampato con meno cifre)
👉 Qui capisci il “non è perfettamente preciso”: lo step minimo è 1/256 ≈ 0.00390625.

* toFloat() (fixed → float)
Esempio: se _rawBits = 128
toFloat() = 128 / 256 = 0.5
Esempio: se _rawBits = 1
toFloat() = 1 / 256 = 0.00390625 (il famoso epsilon)

* toInt() (fixed → int)
Esempio: prendi Fixed x(42.42f) sopra:
_rawBits = 10860
toInt() = 10860 >> 8
cioè 10860 / 256 ma troncato = 42
Esempio: Fixed y(1.99f)
raw ideale: 1.99*256 = 509.44 → round = 509
toInt() = 509 >> 8 = 1
👉 quindi non arrotonda a 2, tronca.

### << in C++ tra numeri → bitwise left shift (spostamento a sinistra)
10 << 8 = sposta i bit di 10 a sinistra di 8 posizioni
Partiamo da 10.
🔢 10 in binario
10 = 00000000 00000000 00000000 00001010
Ora fai:
10 << 8
cioè:
00000000 00000000 00001010 00000000
👉 hai aggiunto 8 zeri a destra

**Cosa succede numericamente?**
Ogni shift a sinistra di 1 bit = moltiplica per 2
Quindi:
10 << 1 = 10 × 2 = 20
10 << 2 = 10 × 4 = 40
…
10 << 8 = 10 × 2⁸ = 10 × 256 = 2560
👉 10 << 8 è IDENTICO a 10 * 256

Confronto diretto (importantissimo)
Queste due righe sono equivalenti:
_rawBits = value * 256;
_rawBits = value << 8;

### shift a destra >>?
Serve per tornare indietro:
_rawBits >> 8
= divide per 256 (troncando)
Ecco perché:
toInt() usa >> 8
Fixed(int) usa << 8

**Perché c’è quella f alla fine?**
In C/C++ i numeri con la virgola senza suffisso sono double per default.
Quindi:
42.42    // è un double
42.42f   // è un float

Perché in ex01 serve proprio float?
Nel tuo Fixed.hpp hai scritto:
Fixed(const float _value);
👉 Questo costruttore accetta SOLO float, non double.
Se scrivi:
Fixed c(42.42);
succede questo:
42.42 è un double
il compilatore deve convertirlo in float
con -Wall -Wextra -Werror → warning = errore
quindi non compila