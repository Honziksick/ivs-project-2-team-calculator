<h1>2. projekt IVS - Týmový projekt: Kalkulačka</h1>

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
![codecov](https://codecov.io/gh/Honziksick/ivs-project-2-team-calculator/graph/badge.svg?token=TYLF21ENO2)

## O projektu: Calm CatCalc

Podrobné informace o projektu jsou k nahlédnutí ve složce `info/` ve formátu Markdown či ve formátu PDF. Tato složka obsahuje mimo jiné zadání projektu, plán projektu a tipy & triky k tvorbě projektu od vůdce týmu.

## Autoři

**Tým: Calm CatCalc Coders 😺**
| **Jméno**             | **xlogin** | **Přezdívka** | **Kontakt**                 |
| --------------------- | ---------- | ------------- | --------------------------- |
| **Farkašovský Lukáš** | xfarkal00  | NormREE       | xfarkal00@stud.fit.vutbr.cz |
| **Hýža Pavel**        | xhyzapa00  | RyzaGrey      | xhyzapa00@stud.fit.vutbr.cz |
| **Kalina Jan**        | xkalinj00  | Honziksick    | xkalinj00@stud.fit.vutbr.cz |
| **Krejčí David**      | xkrejcd00  | DJmDavidus    | xkrejcd00@stud.fit.vutbr.cz |

## Prostředí

Ubuntu 64bit

## Licence

Projekt je distribuován s otevřenými zdrojovými texty pod licencí `GNU GPL v.3`

## Instalace
### 1) Pomocí instalačního balíku
1) Stáhněte si zvolený instalační balíček ze složky `install/`. <br>
2) Do příkazové řádky zadejte příkaz `sudo apt install ./<nazev_zvoleneho_baliku>`. <br>
3) Kalkulačku Calm CatCalc můžete spustit buď příkazem `catcalc` v příkazové řádce, nebo z aplikačního menu. Program na výpočet výběrové směrodatné odchylky (stddev) můžete spustit pomocí příkazu `stddev < input.txt` z příkazové řádky nebo opět z aplikačního menu. <br>
4) Doporučujeme si před prvním požitím aplikace Calm CatCalc průhlednout uživatelskou příručku - soubor `dokumentace.pdf` - nebo po spuštění aplikace kliknout na tlačítko "help" v levém horní rohu naší skvělé kalkulačky, které zobrazí stručný přehled všech možností použití. Pokud by Vás zajímaly další možnosti konzolové aplikace `stddev`, neváhejte a použijte příkaz `stddev -h`, který do terminálu vypíše podrobný manuál k této malé utilitce. <br>

### 2) Přímo ze zdrojových kódů
1) Naklonujte si tento repozitář, nebo si ho stáhněte ve formě `.zip` balíku. <br>
2) V příkazové řádce přejděte do složky `src/`, kde se nachází `Makefile` celého projektu (pokud používáte `make` poprvé, budete si ho muset nejdříve nainstalovat pomocí příkazu `sudo apt-get install make`). <br>
3) Instalaci následně provedete spuštěním příkazu `make` v adresáři `src/`. <br>
4) Pokud by vás zajímaly i další možnosti projektového `Makefile`, spusťe příkaz `make help`, který vypíše seznam všech příkazů, které Makefile obsahuje. <br>
5) Profiling programu je možné spustit příkazem `make profile FILE=<soubor.txt> PROF=<pocet_iteraci_profilovani>`. <br>

## Odinstalace
### 1) Prostřednictvím systémového příkazu apt
1) Pro odinstalaci kalkulačky Calm CatCalc zadejte do příkazové řádky příkaz `sudo apt remove calm-catcalc`. <br>
1) Pro odinstalaci programu na výpočet výběrvé směrodatné odchylky zadejte do příkazové řádky příkaz `sudo apt remove stddev`. <br>

### 2) Prostřednictvím Makefile
1) Stáhněte si ze složky `src/` projektový soubor `Makefile`. <br>
2) V příkazové řádce přejděte do složky, ve které se nachází projektový `Makefile`. <br>
3) Máte na výběr ze tří možností odinstalace: <br>
    - příkazem `make uninstall` odinstalujete jak kalkulačku Calm CatCalc tak i program stddev.
    - příkazem `make uninstall-catcalc` odinstalujete pouze kalkulačku Calm CatCalc.
    - příkazem `make uninstall-stddev` odinstalujete program stddev.

---

*Datum poslední úpravy: 25. 4. 2024, 2:19*
