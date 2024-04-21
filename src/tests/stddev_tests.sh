#!/bin/bash

################################################################################
#                                                                              #
# Název projektu:   Calm CatCalc                                               #
#                                                                              #
# Soubor:           stddev_tests.sh                                            #
# Autor:            Jan Kalina <xkalinj00>                                     #
# Datum:            16.04.2024                                                 #
# Poslední změna:   16.04.2024                                                 #
#                                                                              #
# Tým:      Calm CatCalc Coders                                                #
# Členové:  Farkašovský Lukáš    <xfarkal00>                                   #
#           Hýža Pavel           <xhyzapa00>                                   #
#           Kalina Jan           <xkalinj00>                                   #
#           Krejčí David         <xkrejcd00>                                   #
#                                                                              #
# Popis:    Testovací skript na testování programu na výpočet výběrové         #
#           směrodatné odchylky "stddev"                                       #
#                                                                              #
################################################################################


## 
#  Proměnné pro nastavení barev výstupu
#  Tento blok obsahuje "globální" proměnné používané pro nastavení
#  barev výstupu v terminálu.
##
GREEN='\033[0;32m'      # Kód zelené barvy
RED='\033[0;31m'        # Kód červené barvy
NORMAL='\033[0m'        # Kód bílé barvy


## 
#  Proměnné pro sledování průběhu testování
#  Tento blok obsahuje "globální" proměnné používané v testovacím skriptu.
##
testCnt=1                                   # Pořadí aktuálního testu (počítadlo)
passed=0                                    # Počítadlo úspěšných testů
failed=0                                    # Počítadlo NEúspěšných testů
testDir="./build/test/stddev_test_files"    # Složka s testovacími soubory
failedTests=()                              # Pole názvů NEúspěšných testů


##
#  Funkce pro spuštění jednoho testu
#  Tato funkce spustí testovací program s vstupem zadaným v souboru a porovná 
#  jeho výstup s očekávaným výstupem. Pokud se výstupy shodují, test je 
#  považován za úspěšný. Pokud se výstupy neshodují, test je považován za 
#  neúspěšný a je přidán do seznamu neúspěšných testů.
#
#  expectedOut: Očekávaný výstup
#  inputFile:   Vstupní soubor
##
run_test() {
    local expectedOut=${1}      # očekávaný výstup
    local inputFile=${2}        # vstupní soubor

    # Výpis označení testu
    echo -n -e "$testCnt. Running ./build/stddev < \"$inputFile\""

    # Spuštění testu
    local actualOut
    actualOut=$(./build/stddev < "$testDir/$inputFile" 2>&1)

    # Porovnání výstupu s očekávaným výstupem s přesností na 4 desetinná místa
    if [[ $(echo "$actualOut" | awk -F. '{print $1}') -eq \
          $(echo "$expectedOut" | awk -F. '{print $1}') ]] || \
       [[ "$actualOut" == "$expectedOut" ]]; then
        echo -e "${GREEN} [OK] ${NORMAL}"
        passed=$((passed + 1))
    else
        echo -e "${RED}[FAIL]${NORMAL}"
        echo "Expected: $expectedOut, Got: $actualOut"
        failed=$((failed + 1))
        failedTests+=("$inputFile")
    fi
    testCnt=$((testCnt + 1))        # inkrementace počítadla testů
}

# Seznam jednotlivých testů
run_test "0" "all_one.txt"
run_test "Error: Invalid input data (not a number)." "invalid_data.txt"
run_test "598347.0604" "10_nums.txt"
run_test "14.1189" "with_zeroes.txt"
run_test "5918.5819" "100_nums_1.txt"
run_test "100123.8524" "100_nums_2.txt"
run_test "5794.3761" "1k_nums_1.txt"
run_test "316288.5706" "1k_nums_2.txt"
run_test "5769.9063" "10k_nums_1.txt"
run_test "5777.0714" "10k_nums_2.txt"
run_test "6597.8344" "100k_nums_1.txt"

# Pokud je skript spuštěn s přepínačem --advanced, spustí se pokročilé testy
if [[ $1 == "yes" ]]; then
    run_test "32145.6167" "100k_nums_2.txt"
    run_test "11547.3305" "1M_nums.txt"
fi


# Výpis shrnutí na závěr testovací sady
echo -e "\nSummary:"
testCnt=$((testCnt - 1))
if [ $failed -eq 0 ]; then
    echo -e "${GREEN}Passed: $passed/$testCnt${NORMAL}"
    exit 0      # návratový kód 0 znamená úspěšné dokončení testů
else
    echo -e "Passed: $passed/$testCnt"
    echo -e "\nFailed tests:"
    for test in "${failedTests[@]}"; do
        echo -e "${RED}$test${NORMAL}"
    done
    exit 1      # návratový kód 1 znamená neúspěšné dokončení testů
fi