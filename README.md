# Password checker

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

## Implementační detaily

### Vstupní data (seznam hesel)

Seznam hesel je programu předán na standardním vstupu (stdin). Každé heslo je zadáno na samostatném řádku a obsahuje pouze ASCII textová data, kromě znaku nového řádku. Maximální délka hesla je 100 znaků, jinak se jedná o nevalidní data. Program musí podporovat neomezený počet hesel na vstupu.

### Výstup programu

Program na standardní výstup (stdout) vypisuje hesla ze vstupního seznamu, každé na samostatný řádek, která splňují požadovanou úroveň bezpečnosti zadanou jako argument programu LEVEL. Hesla musí být vypsána beze změny a ve stejném pořadí, v jakém se objevila na vstupu.

Za výstupním seznamem hesel pak program volitelně vypisuje statistiku (viz. Statistiky).

### Omezení v projektu

Je zakázané použít následující funkce:

<ul>
    <li>volání funkcí z knihoven string.h a ctype.h - cílem projektu je naučit se implementovat dané funkce ručně</li>
    <li>volání z rodiny malloc a free - práce s dynamickou pamětí není v tomto projektu zapotřebí</li>
    <li>volání z rodiny fopen, fclose, fscanf, ... - práce se soubory (dočasnými) není v tomto projektu žádoucí</li>
    <li>volání funkce exit</li>
</ul>

## Příklady vstupů a výstupů

Pomocný soubor se seznamem hesel:

```
$ cat hesla.txt
1234567890
Password
Heslo123
Mojevelmidlouhehesloscislem0
IZP2021:fit@vut.cz
```

Příklady spuštění:

```
./pwcheck 1 1 <hesla.txt
Password
Heslo123
Mojevelmidlouhehesloscislem0
IZP2021:fit@vut.cz
```

```
./pwcheck 2 3 <hesla.txt
Heslo123
Mojevelmidlouhehesloscislem0
IZP2021:fit@vut.cz
```

```
./pwcheck 3 2 <hesla.txt
Heslo123
Mojevelmidlouhehesloscislem0
IZP2021:fit@vut.cz
```

```
./pwcheck 4 2 <hesla.txt
Heslo123
IZP2021:fit@vut.cz
```

```
./pwcheck 2 4 --stats <hesla.txt
IZP2021:fit@vut.cz
Statistika:
Ruznych znaku: 36
Minimalni delka: 8
Prumerna delka: 14.4
```
