#
# Název projektu: 	Calm CatCalc
#
# Soubor: 			Makefile
# Datum: 			20.03.2024
# Poslední změna: 	20.03.2024
#
# Tým:		Calm CatCalc Coders
#
# Autoři: 	Farkašovský Lukáš    <xfarkal00>
#         	Hýža Pavel           <xhyzapa00>
#         	Kalina Jan           <xkalinj00>
#         	Krejčí David         <xkrejcd00>
#
# Popis: 	Tento soubor obsahuje Makefile pro projekt Calm CatCalc.
#


################################################################################
#                                                                              #
#                  ZÁKLADNÍ NASTAVENÍ A DEFINICE PRO MAKEFILE                  #
#                                                                              #
################################################################################

###                                           ###
# Proměnné pro opakující se částí názvů souborů #
###                                           ###

# Název projektu
PROJECT = cat_calc_core


###                                                                     ###
# Definice cest k různým složkám obsahující zdrojové soubory ke kompilaci #
###                                                                     ###

# Cesta ke zdrojovým souborům Google Test a Google Mock knihoven
GTEST_DIR = ./tests/googletest-src/googletest
GMOCK_DIR = ./tests/googletest-src/googlemock

# Cesta ke zdrojovým souborům matematické knihovny "Calm CatCalc Core" a testů
CORE_DIR = CalmCatCalc/core
TEST_DIR = tests


###                                                        ###
#  Deklarace cest k adresářům určeným pro kompilaci projektu #
###                                                        ###

# Hlavní adresář pro zkompilovaný projekt a jeho podadresář pro Gtest knihovny
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
COVERAGE_BUILD_DIR = $(BUILD_DIR)/coverage


###                                 ###
# Předdefinované flagy pro kompilátor #
###                                 ###

# Flagy obsahující cesty k hlavičkovým souborům
CPPFLAGS += -I$(CORE_DIR) -I$(GTEST_DIR) -I$(GMOCK_DIR)

# Parametry pro archivaci objektových souborů
STANDARD = -std=c++17
WARNING = -Wall -Wextra -Werror -pedantic -pthread
DEBUG = -g
COVERAGE = -fprofile-arcs -ftest-coverage

# Flagy pro překlad matematické knihovny a testů
CXXFLAGS_CORE = $(STANDARD) -O2 $(WARNING) 
CXXFLAGS_TEST = $(STANDARD) -O0 $(WARNING) $(DEBUG)


################################################################################
#                                                                              #
#                               PŘÍKAZY MAKEFILE                               #
#                                                                              #
################################################################################

# Příkaz '.PHONY' určuje, že následující příkazy nejsou nikdy soubory
.PHONY: all test coverage doc clean clean-build clean-doc test-coverage build-coverage process-coverage

# Příkaz 'all' kompiluje hlavní projekt (TO-DO také profiler)
all: $(BUILD_DIR)/$(PROJECT).o

# Příkaz 'test' sestaví knihovny GoogleTest a GoogleMock a spustí testy projektu
test: $(BUILD_DIR)/$(PROJECT)_test
	./$(BUILD_DIR)/$(PROJECT)_test

# Příkaz 'coverage' vytvoří a zpracuje data o pokrytí kódu testy
coverage: build-coverage process-coverage

# Příkaz 'doc' vygeneruje dokumentaci k projektu
doc: clean-doc
	doxygen Doxyfile

# Příkaz 'clean-build' odstraní všechny soubory z adresáře 'build'
clean-build:
	rm -rf $(BUILD_DIR)

# Příkaz 'clean-doc' odstraní všechny soubory z adresáře 'doc' (kromě /images)
clean-doc:
	find ../doc -mindepth 1 ! -path '../doc/images*' -delete

# Příkaz 'clean' odstraní všechny soubory vytvořené během kompilace
clean: clean-build clean-doc


################################################################################
#                                                                              #
#              KOMPILACE MATEMATICKÉ KNIHOVNY "Calm CatCalc Core"              #
#                                                                              #
################################################################################

# Objektový soubor závisí na zdrojovém a hlavičkovém souboru. Vytvoří složku pro
# výsledky kompilace, pokud neexistuje. Kompiluje zdrojový soubor do objektového.
$(BUILD_DIR)/$(PROJECT).o: $(CORE_DIR)/$(PROJECT).cpp \
                           $(CORE_DIR)/$(PROJECT).h
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_CORE) -c $< -o $@


################################################################################
#                                                                              #
#          KOMPILACE GOOGLE TEST UNIT TESTŮ PRO MATEMATICKOU KNIHOVNU          #
#                                                                              #
################################################################################

# Testovací binární soubor do sebe linkuje všechny závislosti spojené s unit
# testy. Soubor závisí na objektovém souboru testů, objektovém souboru 
# matematické knihovny a Google Test knihovně. 
$(BUILD_DIR)/$(PROJECT)_test: $(TEST_BUILD_DIR)/$(PROJECT)_test.o \
                              $(BUILD_DIR)/$(PROJECT).o \
                              $(TEST_BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -lpthread $^ -o $@


# Objektový soubor testů závisí na zdrojovém souboru testů, hlavičkovém souboru
# matematické knihovny a hlavičkových souborech Google Test a Google Mock
# knihoven. Kompiluje zdrojový soubor testů do objektového souboru.
$(TEST_BUILD_DIR)/$(PROJECT)_test.o: $(TEST_DIR)/$(PROJECT)_tests.cpp \
                                     $(CORE_DIR)/$(PROJECT).h \
                                     $(GTEST_DIR)/gtest/*.h \
                                     $(GMOCK_DIR)/gmock/*.h \
                                     $(GMOCK_DIR)/gmock/internal/*.h
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@


# Objektový soubor "gtest-all.o" závisí na zdrojových a hlavičkových souborech
# Google Test. Kompiluje zdrojový soubor "gtest-all.cc" do objektového souboru.
$(TEST_BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/*.cc \
                               $(GTEST_DIR)/gtest/*.h \
                               $(GTEST_DIR)/gtest/internal/*.h
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $(GTEST_DIR)/src/gtest-all.cc -o $@


# Objektový soubor "gtest_main.o" závisí na zdrojových a hlavičkových souborech
# Google Test. Kompiluje zdrojový soubor "gtest_main.cc" do objektového souboru
$(TEST_BUILD_DIR)/gtest_main.o: $(GTEST_DIR)/src/*.cc \
                                $(GTEST_DIR)/gtest/*.h \
                                $(GTEST_DIR)/gtest/internal/*.h
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $(GTEST_DIR)/src/gtest_main.cc -o $@


# Vytvoří se statická knihovna "gtest.a", která závisí na objektovém souboru
# "gtest-all.o"
$(TEST_BUILD_DIR)/gtest.a: $(TEST_BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^


# Vytvoří se statická knihovna "gtest_main.a", která závisí na objektovém souboru
# "gtest-all.o" a objektovém souboru "gtest_main.o"
$(TEST_BUILD_DIR)/gtest_main.a: $(TEST_BUILD_DIR)/gtest-all.o \
                                $(TEST_BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


################################################################################
#                                                                              #
#                           GENEROVÁNÍ CODE COVERAGE                           #
#                                                                              #
################################################################################

# Stavba testů s informacemi pro generování pokrytí kódu a ignorováním chybového
# návratového kódu, pokud některý z testů selže (tedy se nezastaví generování pokrytí)
test-coverage: $(BUILD_DIR)/$(PROJECT)_test
	./$(BUILD_DIR)/$(PROJECT)_test 2>/dev/null || true


# Přidáme přepínače pro generování dat pokrytí kódu do kompilačních přepínačů
# pro testy a matematickou knihovnu
build-coverage: CXXFLAGS_TEST += $(COVERAGE)
build-coverage: CXXFLAGS_CORE += $(COVERAGE)


# Nejprve vyčistíme předchozí "build" a opětovně sestavíme a spustíme testy
# s informacemi pro generování pokrytí kódu
build-coverage: clean-build test-coverage


# Cíl 'process-coverage' zpracuje data/výstup o pokrytí kódu
# Volitelně: lcov --quiet --remove $(BUILD_DIR)/filtered_coverage.info \
#	'*/cat_calc_core_tests.cpp' --output-file $(BUILD_DIR)/filtered_coverage.info
process-coverage:
	mkdir -p $(COVERAGE_BUILD_DIR)
	lcov --quiet --directory $(BUILD_DIR) --capture \
	--output-file $(BUILD_DIR)/coverage.info

	lcov --quiet --remove $(BUILD_DIR)/coverage.info '/usr/*' \
	--output-file $(BUILD_DIR)/filtered_coverage.info

	lcov --quiet --remove $(BUILD_DIR)/filtered_coverage.info \
	'*/googletest-src/*' --output-file $(BUILD_DIR)/filtered_coverage.info

	genhtml $(BUILD_DIR)/filtered_coverage.info \
	--output-directory $(COVERAGE_BUILD_DIR)
	
	mkdir -p $(COVERAGE_BUILD_DIR)
	mv $(BUILD_DIR)/*.gcda $(COVERAGE_BUILD_DIR)/
	mv $(BUILD_DIR)/*.gcno $(COVERAGE_BUILD_DIR)/
	mv $(BUILD_DIR)/coverage.info $(COVERAGE_BUILD_DIR)/
	mv $(BUILD_DIR)/filtered_coverage.info $(COVERAGE_BUILD_DIR)/
