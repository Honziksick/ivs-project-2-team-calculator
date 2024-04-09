#
# Název projektu:   Calm CatCalc
#
# Soubor:           Makefile
# Autor:            Jan Kalina <xkalinj00>ma
# Datum:            20.03.2024
# Poslední změna:   07.04.2024
#
# Tým:      Calm CatCalc Coders
# Členové:  Farkašovský Lukáš    <xfarkal00>
#           Hýža Pavel           <xhyzapa00>
#           Kalina Jan           <xkalinj00>
#           Krejčí David         <xkrejcd00>
#
# Popis:    Tento soubor obsahuje Makefile pro projekt Calm CatCalc.
#


################################################################################
#                                                                              #
#                  ZÁKLADNÍ NASTAVENÍ A DEFINICE PRO MAKEFILE                  #
#                                                                              #
################################################################################

###                                             ###
#  Proměnné pro opakující se částí názvů souborů  #
###                                             ###

# Název projektu
EXECUTABLE = cat_calc_core
PROFILER = stddev
$(VERBOSE)SILENTOPT = -s


###                                         ###
#  Argumenty, které je možné předat Makefilu  #
###                                          ###

# Pokud je proměnná 'DATA_FILE' nastavena na '-1',
# tak pro profilování budou vygenerována náhodná data

DATA_FILE ?= -1
AUTO_GEN_DATA_FILE = auto_gen.txt


###                                 ###
#  Definice cest pro některé výstupy  #
###                                 ###

DOC_OUT_DIR = ../doc
PROFILE_OUT_DIR = ../profiling

###                                                                       ###
#  Definice cest k různým složkám obsahující zdrojové soubory ke kompilaci  #
###                                                                       ###

# Cesta ke zdrojovým souborům Google Test a Google Mock knihoven
GTEST_DIR = ./tests/googletest-src/googletest
GMOCK_DIR = ./tests/googletest-src/googlemock

# Cesta ke zdrojovým souborům matematické knihovny "Calm CatCalc Core" a testů
CORE_DIR = CalmCatCalc/core
TEST_DIR = tests
PROFILE_DIR = profiler


###                                                         ###
#  Deklarace cest k adresářům určeným pro kompilaci projektu  #
###                                                         ###

# Hlavní adresář pro zkompilovaný projekt a jeho podadresář pro Gtest knihovny
CORE_BUILD_DIR = build
TEST_BUILD_DIR = $(CORE_BUILD_DIR)/tests
COVERAGE_BUILD_DIR = $(CORE_BUILD_DIR)/coverage
PROFILE_BUILD_DIR = $(CORE_BUILD_DIR)/profiling


###                                   ###
#  Předdefinované flagy pro kompilátor  #
###                                   ###

# Flagy obsahující cesty k hlavičkovým souborům
CPPFLAGS += -I$(CORE_DIR) -I$(GTEST_DIR) -I$(GMOCK_DIR)

# Parametry pro archivaci objektových souborů
STANDARD = -std=c++17
WARNING = -Wall -Wextra -Werror -pedantic -pthread
DEBUG = -g
PROFILE = -pg
COVERAGE = -fprofile-arcs -ftest-coverage

# Flagy pro překlad matematické knihovny a testů
CXXFLAGS_CORE = $(STANDARD) -O2 $(WARNING) 
CXXFLAGS_DEV = $(STANDARD) -O0 $(WARNING) $(DEBUG) $(COVERAGE) $(PROFILE)


################################################################################
#                                                                              #
#                               PŘÍKAZY MAKEFILE                               #
#                                                                              #
################################################################################

# Příkaz '.PHONY' určuje, že následující příkazy nejsou nikdy soubory
.PHONY: all test coverage doc clean \
        clean-build clean-doc \
		test-coverage process-coverage

# Příkaz 'all' kompiluje hlavní projekt (TO-DO také profiler)
all: build-profiler build-core

build-core: $(CORE_BUILD_DIR)/$(EXECUTABLE).o
	@$(MAKE) $(SILENTOPT) move-coverage-data

# Příkaz 'test' sestaví knihovny GoogleTest a GoogleMock a spustí testy projektu
test: run-tests move-coverage-data

run-tests: $(CORE_BUILD_DIR)/$(EXECUTABLE)_test
	./$(CORE_BUILD_DIR)/$(EXECUTABLE)_test

# Příkaz 'coverage' vytvoří a zpracuje data o pokrytí kódu testy
coverage: build-coverage test-coverage process-coverage

# Příkaz 'profile' sestaví a spustí profiling matematické knihovny
profile:
	$(MAKE) $(SILENTOPT) build-profiler
	$(MAKE) $(SILENTOPT) rebuild-core
	@$(MAKE) $(SILENTOPT) clean-profile
	@rm -f $(PROFILE_BUILD_DIR)/gmon.out $(PROFILE_BUILD_DIR)/gmon.sum
	@rm -f $(PROFILE_BUILD_DIR)/$(AUTO_GEN_DATA_FILE) 2>/dev/null || true
	$(MAKE) $(SILENTOPT) run-first-profile
	@mv gmon.out gmon.sum
	$(MAKE) $(SILENTOPT) run-other-profile
	@gprof -s ./$(CORE_BUILD_DIR)/stddev gmon.out gmon.sum
	gprof ./$(CORE_BUILD_DIR)/stddev gmon.sum > gprof-report.txt
	@mv gmon.out $(PROFILE_BUILD_DIR)/
	@mv gmon.sum $(PROFILE_BUILD_DIR)/
	@mv -f $(AUTO_GEN_DATA_FILE) $(PROFILE_BUILD_DIR)/ 2>/dev/null || true
	mv gprof-report.txt $(PROFILE_OUT_DIR)/
	@$(MAKE) $(SILENTOPT) move-coverage-data

run-first-profile:
	if [ "$(DATA_FILE)" = "-1" ]; then \
        echo -1 > temp.txt; \
        $(CORE_BUILD_DIR)/stddev < temp.txt; \
        rm temp.txt; \
    else \
        $(CORE_BUILD_DIR)/stddev < $(DATA_FILE); \
    fi

run-other-profile:
	if [ "$(DATA_FILE)" = "-1" ]; then \
	    $(CORE_BUILD_DIR)/stddev < $(AUTO_GEN_DATA_FILE); \
    else \
        $(CORE_BUILD_DIR)/stddev < $(DATA_FILE); \
    fi


# Příkaz 'doc' vygeneruje dokumentaci k projektu
doc: clean-doc
	doxygen Doxyfile

# Příkaz 'clean-build' odstraní všechny soubory z adresáře 'build'
clean-build:
	rm -rf $(CORE_BUILD_DIR)

clean-core:
	@rm -f $(CORE_BUILD_DIR)/$(EXECUTABLE).o

# Příkaz 'clean-doc' odstraní všechny soubory z adresáře 'doc' (kromě /images)
clean-doc:
	find $(DOC_OUT_DIR) -mindepth 1 ! -path '$(DOC_OUT_DIR)/images*' -delete

clean-profile:
	rm -f $(PROFILE_OUT_DIR)/gprof-report.txt

# Příkaz 'clean' odstraní všechny soubory vytvořené během kompilace
clean: clean-build clean-doc clean-profile


################################################################################
#                                                                              #
#              KOMPILACE MATEMATICKÉ KNIHOVNY "Calm CatCalc Core"              #
#                                                                              #
################################################################################

# Objektový soubor závisí na zdrojovém a hlavičkovém souboru. Vytvoří složku pro
# výsledky kompilace, pokud neexistuje. Kompiluje zdrojový soubor do objektového.
$(CORE_BUILD_DIR)/$(EXECUTABLE).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	mkdir -p $(CORE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_CORE) -c $< -o $@


################################################################################
#                                                                              #
#          KOMPILACE GOOGLE TEST UNIT TESTŮ PRO MATEMATICKOU KNIHOVNU          #
#                                                                              #
################################################################################

# Testovací binární soubor do sebe linkuje všechny závislosti spojené s unit
# testy. Soubor závisí na objektovém souboru testů, objektovém souboru 
# matematické knihovny a Google Test knihovně. 
$(CORE_BUILD_DIR)/$(EXECUTABLE)_test: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o \
                              $(CORE_BUILD_DIR)/$(EXECUTABLE).o \
                              $(TEST_BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) $^ -o $@
	

# Objektový soubor testů závisí na zdrojovém souboru testů, hlavičkovém souboru
# matematické knihovny a hlavičkových souborech Google Test a Google Mock
# knihoven. Kompiluje zdrojový soubor testů do objektového souboru.
$(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o: $(TEST_DIR)/$(EXECUTABLE)_tests.cpp
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) -c $< -o $@


# Objektový soubor "gtest-all.o" závisí na zdrojových a hlavičkových souborech
# Google Test. Kompiluje zdrojový soubor "gtest-all.cc" do objektového souboru.
$(TEST_BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/*.cc
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) -c $(GTEST_DIR)/src/gtest-all.cc -o $@


# Objektový soubor "gtest_main.o" závisí na zdrojových a hlavičkových souborech
# Google Test. Kompiluje zdrojový soubor "gtest_main.cc" do objektového souboru
$(TEST_BUILD_DIR)/gtest_main.o: $(GTEST_DIR)/src/*.cc
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) -c $(GTEST_DIR)/src/gtest_main.cc -o $@


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
test-coverage: $(CORE_BUILD_DIR)/$(EXECUTABLE)_test
	@./$(CORE_BUILD_DIR)/$(EXECUTABLE)_test 2>/dev/null || true
	@$(MAKE) $(SILENTOPT) move-coverage-data

# Stavba matematické knihovny s přepínači pro generování pokrytí kódu
CXXFLAGS_CORE += $(COVERAGE)
build-coverage:
	@$(MAKE) $(SILENTOPT) clean-core
	@$(MAKE) $(SILENTOPT) build-core

move-coverage-data:
	@mkdir -p $(COVERAGE_BUILD_DIR)
	@mv -f $(CORE_BUILD_DIR)/*.gcda $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true
	@mv -f $(CORE_BUILD_DIR)/*.gcno $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true
	@mv -f $(TEST_BUILD_DIR)/*.gcda $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true
	@mv -f $(TEST_BUILD_DIR)/*.gcno $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true
	@mv -f $(PROFILE_BUILD_DIR)/stddev.gcno $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true
	@mv -f $(PROFILE_BUILD_DIR)/*.gcda $(COVERAGE_BUILD_DIR)/ 2>/dev/null || true


# Cíl 'process-coverage' zpracuje data/výstup o pokrytí kódu
# Volitelně: lcov --quiet --remove $(CORE_BUILD_DIR)/filtered_coverage.info \
# '*/cat_calc_core_tests.cpp' --output-file $(CORE_BUILD_DIR)/filtered_coverage.info
process-coverage:
	lcov --quiet --directory $(CORE_BUILD_DIR) --capture \
	--output-file $(CORE_BUILD_DIR)/coverage.info

	lcov --quiet --remove $(CORE_BUILD_DIR)/coverage.info '/usr/*' \
	--output-file $(CORE_BUILD_DIR)/filtered_coverage.info

	lcov --quiet --remove $(CORE_BUILD_DIR)/filtered_coverage.info \
	'*/googletest-src/*' --output-file $(CORE_BUILD_DIR)/filtered_coverage.info

	lcov --quiet --remove $(CORE_BUILD_DIR)/filtered_coverage.info \
	'*/profiler/*' --output-file $(CORE_BUILD_DIR)/filtered_coverage.info

	genhtml $(CORE_BUILD_DIR)/filtered_coverage.info \
	--output-directory $(COVERAGE_BUILD_DIR)
	
	@mv $(CORE_BUILD_DIR)/coverage.info $(COVERAGE_BUILD_DIR)/
	@mv $(CORE_BUILD_DIR)/filtered_coverage.info $(COVERAGE_BUILD_DIR)/


################################################################################
#                                                                              #
#                    PROFILER - VÝPOČET SMĚRODATNÉ ODCHYLKY                    #
#                                                                              #
################################################################################

# Stavba programu na výpočet směrodatné odchylky a stavba knihovny s '-pg'


rebuild-core: clean-core
	$(MAKE) build-core CXXFLAGS_CORE+="$(CXXFLAGS_CORE) $(DEBUG) $(PROFILE)"

build-profiler: rebuild-core build-stddev
	@$(MAKE) $(SILENTOPT) move-coverage-data

build-stddev: $(CORE_BUILD_DIR)/$(PROFILER)

$(PROFILE_BUILD_DIR)/$(PROFILER).o: $(PROFILE_DIR)/$(PROFILER).cpp
	mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) -c $< -o $@

$(CORE_BUILD_DIR)/$(PROFILER): $(PROFILE_BUILD_DIR)/$(PROFILER).o \
                          $(CORE_BUILD_DIR)/$(EXECUTABLE).o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_DEV) $^ -o $@
