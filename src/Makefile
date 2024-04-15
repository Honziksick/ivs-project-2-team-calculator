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

# Název a spouštění programu pro profilování
PROFILER = stddev
STDDEV = ./$(BUILD_DIR)/$(PROFILER)

# Název ZIP archivu pro odevzdání projektu
PACK_NAME = xkalinj00_xfarkal00_xhyzapa00_xkrejcd00.zip


###                                       ###
#  Přepínače pro spouštění příkazu $(MAKE)  #
###                                       ###

# Spuštění 'make' v tichém režímu (bez výpisu událostí)
$(VERBOSE)SILENTOPT = -s


###                                ###
#  Proměnné týkající se profilování  #
###                                ###

# Pokud je proměnná 'FILE' nastavena na '-1',
# tak pro profilování budou vygenerována náhodná data
FILE ?= -1
AUTO_GEN_DATA_FILE = auto_gen.txt

# Počet dalších běhů profilování => celkem (1 + PROF_LOOP) běhů
PROF_LOOP = 10


###                                 ###
#  Definice cest pro některé výstupy  #
###                                 ###

# Adresář pro generování dokumentace
DOC_OUT_DIR = ../doc

# Adresář pro generování profilovacích dat
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
BUILD_DIR = ./build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
COVERAGE_BUILD_DIR = $(BUILD_DIR)/coverage
PROFILE_BUILD_DIR = $(BUILD_DIR)/profiling
PACK_DIR = ../pack

# Dočasné složky při balení projektu
TEMP_DIRS = PACK_REPO_DIR PACK_DOC_DIR PACK_INSTALL_DIR
PACK_REPO_DIR = $(PACK_DIR)/repo
PACK_DOC_DIR = $(PACK_DIR)/doc
PACK_INSTALL_DIR = $(PACK_DIR)/install


###                                   ###
#  Předdefinované flagy pro kompilátor  #
###                                   ###

# Flagy obsahující cesty k hlavičkovým souborům
CPPFLAGS += -I$(CORE_DIR) -I$(PROFILE_DIR) -I$(GTEST_DIR) -I$(GMOCK_DIR)

# Parametry pro archivaci objektových souborů
STANDARD = -std=c++17
WARNING = -Wall -Wextra -Werror -pedantic -pthread
DEBUG = -g
PROFILE = -pg
COVERAGE = -fprofile-arcs -ftest-coverage

# Flagy pro překlad matematické knihovny a testů
CXXFLAGS_STD = $(STANDARD) -O2 $(WARNING) 
CXXFLAGS_TEST = $(STANDARD) -O0 $(WARNING) $(DEBUG)
CXXFLAGS_COV = $(STANDARD) -O0 $(WARNING) $(DEBUG) $(COVERAGE)
CXXFLAGS_PROF = $(STANDARD) -O0 $(WARNING) $(DEBUG) $(PROFILE)


################################################################################
#                                                                              #
#                          ZÁKLADNÍ PŘÍKAZY MAKEFILE                           #
#                                                                              #
################################################################################

# Příkaz '.PHONY' určuje, že následující příkazy nejsou nikdy brány jako soubory
.PHONY: all clean test doc coverage profile \
        clean-build clean-core clean-doc clean-coverage clean-profile \
		build-core \
		run-test build-test build-test-libs \
		build-coverage build-test-coverage run-test-coverage process-coverage \
		build-profile run-first-profile run-another-profile

# Příkaz 'all' kompiluje hlavní projekt (TO-DO také profiler)
all: build-core build-profile

# Příkaz 'clean' odstraní všechny soubory vytvořené během kompilace
clean: clean-build clean-doc clean-profile clean-pack

# Příkaz 'test' sestaví knihovny GoogleTest a GoogleMock a spustí testy projektu
test: run-test build-test-libs run-test 

# Příkaz 'doc' vygeneruje dokumentaci k projektu
doc:
	$(MAKE) $(SILENTOPT) clean-doc
	doxygen Doxyfile

# Příkaz 'coverage' vytvoří a zpracuje data o pokrytí kódu testy
coverage: build-coverage build-test-coverage run-test-coverage process-coverage

# Příkaz 'profile' sestaví a spustí profiling matematické knihovny
profile:
	$(MAKE) build-profile

	$(MAKE) clean-profile
	rm -f $(PROFILE_BUILD_DIR)/gmon.out ./$(PROFILE_BUILD_DIR)/gmon.sum
	rm -f $(PROFILE_BUILD_DIR)/$(AUTO_GEN_DATA_FILE) 2>/dev/null || true

	$(MAKE) run-first-profile
	$(MAKE) run-another-profile

	gprof $(STDDEV) gmon.sum | tee gprof-report.txt | gprof2dot -s | dot -Gdpi=500 -Tpng -o gprof-report.png
	
	mv gmon.out ./$(PROFILE_BUILD_DIR)/
	mv gmon.sum ./$(PROFILE_BUILD_DIR)/
	mv -f $(AUTO_GEN_DATA_FILE) $(PROFILE_BUILD_DIR)/ 2>/dev/null || true

	mv gprof-report.txt $(PROFILE_OUT_DIR)/
	mv gprof-report.png $(PROFILE_OUT_DIR)/

# Příkaz 'pack' vytvoří ZIP archiv s projektem pro odevzdání
pack:
	mkdir -p $(PACK_DIR)

	rsync -av --progress ../.git $(PACK_REPO_DIR)/
	rsync -av --progress ../.github $(PACK_REPO_DIR)/
	rsync -av --progress ../.vscode $(PACK_REPO_DIR)/
	rsync -av --progress ../doc $(PACK_REPO_DIR)/
	rsync -av --progress ../mockup $(PACK_REPO_DIR)/
	rsync -av --progress ../plan $(PACK_REPO_DIR)/
	rsync -av --progress ../profiling $(PACK_REPO_DIR)/
	rsync -av --progress ../src/ $(PACK_REPO_DIR)/ --exclude build
	rsync -av --progress ../.editorconfig $(PACK_REPO_DIR)/
	rsync -av --progress ../.gitignore $(PACK_REPO_DIR)/
	rsync -av --progress ../LICENSE $(PACK_REPO_DIR)/
	rsync -av --progress ../README.md $(PACK_REPO_DIR)/

	$(MAKE) doc
	cp -r $(DOC_OUT_DIR)/ $(PACK_DOC_DIR)/
	@$(MAKE) $(SILENTOPT) clean-doc

	cd $(PACK_DIR) && zip -r ../$(PACK_NAME) ./
	rm -rf $(PACK_DIR)


################################################################################
#                                                                              #
#                        KONKRETIZOVANÉ PŘÍKAZY 'CLEAN'                        #
#                                                                              #
################################################################################

# Příkaz 'clean-build' odstraní všechny soubory z adresáře 'build'
clean-build:
	rm -rf $(BUILD_DIR)

# Příkaz 'clean-core' odstraní objektový soubor matematické knihovny 'CatCalc Core'
clean-core:
	@rm -f $(BUILD_DIR)/$(EXECUTABLE).o

# Příkaz 'clean-doc' odstraní všechny soubory z adresáře 'doc' (kromě /images)
clean-doc:
	find $(DOC_OUT_DIR) -mindepth 1 ! -path '$(DOC_OUT_DIR)/images*' -delete

# Příkaz 'clean-coverage' odstraní všechny soubory vytvořené během pokrytí kódu
clean-coverage:
	@rm -rf $(COVERAGE_BUILD_DIR)

# Příkaz 'clean-profile' odstraní všechny soubory vytvořené během profilování
clean-profile:
	rm -f $(PROFILE_OUT_DIR)/gprof-report.txt
	rm -f $(PROFILE_OUT_DIR)/gprof-report.png

clean-pack:
	rm -rf $(PACK_NAME)


################################################################################
#                                                                              #
#              KOMPILACE MATEMATICKÉ KNIHOVNY "Calm CatCalc Core"              #
#                                                                              #
################################################################################

# Příkaz 'build-core' sestaví matematickou knihovnu 'CatCalc Core'
build-core: $(BUILD_DIR)/$(EXECUTABLE).o

# Stavba objekotvého souboru matematické knihovny 'CatCalc Core'
$(BUILD_DIR)/$(EXECUTABLE).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_STD) -c $< -o $@


################################################################################
#                                                                              #
#          KOMPILACE GOOGLE TEST UNIT TESTŮ PRO MATEMATICKOU KNIHOVNU          #
#                                                                              #
################################################################################

# Příkaz 'run-test' spustí testy matematické knihovny 'CatCalc Core'
run-test: $(BUILD_DIR)/$(EXECUTABLE)_test
	./$(BUILD_DIR)/$(EXECUTABLE)_test

# Příkaz 'build-test' sestaví testy matematické knihovny 'CatCalc Core'
build-test: $(BUILD_DIR)/$(EXECUTABLE)_test

# Příkaz 'build-test-libs' sestaví knihovny Google Test a Google Mock
build-test-libs: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o \
                 $(BUILD_DIR)/$(EXECUTABLE).o \
                 $(TEST_BUILD_DIR)/gtest_main.a

# Příkaz 'build-test-libs' sestaví knihovny Google Test a Google Mock
build-test-debug: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug

# Stavba testu matematické knihovny 'CatCalc Core'
$(BUILD_DIR)/$(EXECUTABLE)_test: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o \
                              $(BUILD_DIR)/$(EXECUTABLE).o \
                              $(TEST_BUILD_DIR)/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) $^ -o $@
	
$(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o: $(TEST_DIR)/$(EXECUTABLE)_tests.cpp
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@

# Stavba debuggovací varianty testů s funkcí main
$(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug.o \
                                            $(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) $^ -o $@

$(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug.o: $(TEST_DIR)/$(EXECUTABLE)_tests_for_debug.cpp
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@

$(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o: $(CORE_DIR)/$(EXECUTABLE).cpp
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@


# Stavba objektových souborů Google Test knihoven
$(TEST_BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/*.cc
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(TEST_BUILD_DIR)/gtest_main.o: $(GTEST_DIR)/src/*.cc
	mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $(GTEST_DIR)/src/gtest_main.cc -o $@

# Stavba se statických knihovne pro Google Test
$(TEST_BUILD_DIR)/gtest.a: $(TEST_BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(TEST_BUILD_DIR)/gtest_main.a: $(TEST_BUILD_DIR)/gtest-all.o \
                                $(TEST_BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^


################################################################################
#                                                                              #
#                           GENEROVÁNÍ CODE COVERAGE                           #
#                                                                              #
################################################################################

# Příkaz 'build-coverage' sestaví knihovnu a testy s přepínači pro pokrytím kódu
build-coverage: $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o \
                $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage

# Příkaz 'build-test-coverage' sestaví testy s přepínači pro pokrytím kódu
build-test-coverage: build-test-libs $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage

# Příkaz 'run-test-coverage' spustí testy s pokrytím kódu
run-test-coverage:
	./$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage 2>/dev/null || true

# Příkaz 'process-coverage' zpracuje data o pokrytí kódu testy a vygeneruje
# pokrytí kódu ve formátu HTML
process-coverage:
	lcov --quiet --directory $(COVERAGE_BUILD_DIR) --capture \
	--output-file $(COVERAGE_BUILD_DIR)/coverage.info

	lcov --quiet --remove $(COVERAGE_BUILD_DIR)/coverage.info '/usr/*' \
	--output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	lcov --quiet --remove $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	'*/googletest-src/*' --output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	lcov --quiet --remove $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	'*/profiler/*' --output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	genhtml $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	--output-directory $(COVERAGE_BUILD_DIR)

# Stavba testů s přepínači pro profilování pomocí gprof
$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage:  \
                        $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage.o \
                        $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o \
                        $(TEST_BUILD_DIR)/gtest_main.a
	mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) $^ -o $@

$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage.o: $(TEST_DIR)/$(EXECUTABLE)_tests.cpp
	mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) -c $< -o $@

# Stavba matematické knihovny s přepínači pro pokrytí kódu
$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o: $(CORE_DIR)/$(EXECUTABLE).cpp
	mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) -c $< -o $@


################################################################################
#                                                                              #
#                    PROFILER - VÝPOČET SMĚRODATNÉ ODCHYLKY                    #
#                                                                              #
################################################################################

# Příkaz 'build-profile' sestaví profiler pro výpočet směrodatné odchylky
build-profile: $(BUILD_DIR)/$(PROFILER)

# Příkaz 'run-first-profile' spustí první běh profilování matematické knihovny
run-first-profile:
	if [ "$(FILE)" = "-1" ]; then \
		echo -1 > ./$(BUILD_DIR)/temp.txt; \
		$(STDDEV) < ./$(BUILD_DIR)/temp.txt; \
	else \
		$(STDDEV) < $(FILE); \
	fi; \
	mv gmon.out gmon.sum

# Příkaz 'run-another-profile' spustí další běhy profilování matematické knihovny
# Počet běhů lze nastavit pomocí proměnné 'PROF_LOOP' v hlavičce Makefile
run-another-profile:
	itr=1 ; while [ $$itr -le $(PROF_LOOP) ]; do \
		if [ "$(FILE)" = "-1" ]; then \
			$(STDDEV) < $(AUTO_GEN_DATA_FILE); \
			gprof -s $(STDDEV) gmon.out gmon.sum; \
			itr=`expr $$itr + 1`; \
		else \
			$(STDDEV) < $(FILE); \
			gprof -s $(STDDEV) gmon.out gmon.sum; \
			itr=`expr $$itr + 1`; \
		fi; \
	done

# Stavba objektového souboru programu 'stddev' pro výpočet směrodatné odchylky
$(PROFILE_BUILD_DIR)/$(PROFILER).o: $(PROFILE_DIR)/$(PROFILER).cpp
	mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) -c $< -o $@

# Stavba binárky programu 'stddev' pro výpočet směrodatné odchylky
$(BUILD_DIR)/$(PROFILER): $(PROFILE_BUILD_DIR)/$(PROFILER).o \
                          $(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(PROFILER).o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) $^ -o $@

# Stavba matematické knihovny s přepínači pro profilování pomocí gprof
$(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(PROFILER).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) -c $< -o $@
