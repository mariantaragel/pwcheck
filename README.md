# Password checker

9,8 / 10

## Popis projektu

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena.

## Detailní specifikace

Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

### Překlad

Program překládejte s následujícími argumenty:

```sh
$ gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck
``` 

### Syntax spuštění

Program se spouští v následující podobě: (./pwcheck značí umístění a název programu):


```sh
./pwcheck LEVEL PARAM [--stats]
``` 

Program je spouštěn se dvěma pevně zadanými argumenty LEVEL a PARAM a s jedním volitelným argumentem --stats, případně zadaným na třetí pozici:

<strong>LEVEL</strong> - celé číslo v intervalu [1, 4], které určuje požadovanou úroveň bezpečnosti (viz níže)<br />
<strong>PARAM</strong> - kladné celé číslo, které určuje dodatečný parametr pravidel (viz níže)<br />
<strong>--stats</strong> - pokud je zadané, určuje, zda se na konci programu mají vypsat souhrnné statistiky analyzovaných hesel

### Úrovně bezpečnosti (kontrolovaná pravidla)

Jsou definovány celkem 4 úrovně bezpečnosti vyjádřeny pomocí 4 pravidel. Úroveň bezpečnosti určuje, že hesla musí splňovat všechna pravidla na dané a nižší úrovni.

Některá pravidla jsou parametrizovatelná celým číslem zadaným pomocí argumentu programu PARAM. V následujícím seznamu je tento parametr označen jako X.

Seznam pravidel:

1. Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
2. Heslo obsahuje znaky z alespoň X skupin (v případě, že je číslo X větší než 4, myslí se tím všechny skupiny). Uvažované skupiny jsou:<br />
    - malá písmena (a-z)<br />
    - velká písmena (A-Z)<br />
    - čísla (0-9)<br />
    - speciální znaky<br />
3. Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
4. Heslo neobsahuje dva stejné podřetězce délky alespoň X.

### Statistiky

Pokud je zadaný argument programu --stats, program musí na konec výstupu vypsat celkové statistiky ve formátu:

```sh
Statistika:
Ruznych znaku: NCHARS
Minimalni delka: MIN
Prumerna delka: AVG
``` 

NCHARS - počet různých znaků vyskytujících se napříč všemi hesly<br />
MIN - délka nejkratšího hesla (resp. hesel)<br />
AVG - průměrná délka hesla (aritmetický průměr) zaokrouhlená na 1 desetiné místo
