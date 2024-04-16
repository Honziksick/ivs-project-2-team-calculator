################################################################################
#                                                                              #
# Název projektu:   Calm CatCalc                                               #
#                                                                              #
# Soubor:           Makefile                                                   #
# Autor:            Jan Kalina <xkalinj00>                                     #
# Datum:            20.03.2024                                                 #
# Poslední změna:   07.04.2024                                                 #
#                                                                              #
# Tým:      Calm CatCalc Coders                                                #
# Členové:  Farkašovský Lukáš    <xfarkal00>                                   #
#           Hýža Pavel           <xhyzapa00>                                   #
#           Kalina Jan           <xkalinj00>                                   #
#           Krejčí David         <xkrejcd00>                                   #
#                                                                              #
# Popis:    Tento soubor obsahuje Makefile pro projekt Calm CatCalc.           #
#                                                                              #
################################################################################

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
STDDEV_TEST = stddev_tests.sh
STDDEV_TEST_PACK = stddev_test_files.tar.gz

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

# Očekávaný název automaticky generovaného vstupního souboru
AUTO_GEN_DATA_FILE = auto_gen.txt

# Počet dalších běhů profilování => celkem (1 + PROF) běhů
PROF = 10


###                                ###
#  Nastavitelné proměnné prostředí   #
###                                ###

### FILE: ## Název souboru s daty pro profilování (pokud není nastaveno, použije se náhodná data)
FILE ?= -1

### PROF: ## Určuje počet dalších běhů profilování => celkem (1 + PROF) běhů
PROF = 10

### ADV: ## Pokud je nastavena na 'yes', spustí se pokročilé testy programu "stddev"
ADV=no


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
GUI_DIR = CalmCatCalc/cat_calc_gui
TEST_DIR = tests
PROFILE_DIR = profiler


###                                                         ###
#  Deklarace cest k adresářům určeným pro kompilaci projektu  #
###                                                         ###

# Hlavní adresář pro zkompilovaný projekt a jeho podadresář pro Gtest knihovny
BUILD_DIR = ./build
TEST_BUILD_DIR = $(BUILD_DIR)/test
COVERAGE_BUILD_DIR = $(BUILD_DIR)/coverage
PROFILE_BUILD_DIR = $(BUILD_DIR)/profile
GUI_BUILD_DIR = $(BUILD_DIR)/gui
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

# Flagy pro překlad různých částí projektu
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
.PHONY: all install build clean doc help pack test profile coverage \
        clean-build clean-core clean-coverage clean-doc clean-pack clean-profile \
        update-dep install-dep upgrade-dep add-to-path \
        build-core build-gui \
        build-test build-test-libs build-test-debug run-core-test run-stddev-test \
        build-profile run-first-profile run-next-profile prep-stddev-test \
        build-coverage build-test-coverage process-coverage \
        pack-repo pack-doc pack-install

### all: ## Instaluje kalulačku "Calm CatCalc" a program "stddev" pro profilování
all: install build add-to-path

### help: ## Vypíše nápovědu k použití Makefile
help:
	@{ \
	echo "Proměnné:"; \
	grep -E '### [A-Z\_]+:.*?## .*$$' $(MAKEFILE_LIST) | \
	grep -v "grep -E '###.*:.*?## .*$$'" | \
	sort -f | \
	awk 'BEGIN {FS = ":.*?## "}; \
	{gsub(/### /, "", $$1); \
	printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'; \
	echo ""; \
	echo "Příkazy:"; \
	grep -E '### [a-z\-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
	grep -v "grep -E '###.*:.*?## .*$$'" | \
	sort -f | \
	awk 'BEGIN {FS = ":.*?## "}; \
	{gsub(/### /, "", $$1); \
	printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'; \
	} | less -R

### clean: ## Odstraní všechny soubory vytvořené během kompilace
clean: clean-build clean-doc clean-profile clean-pack

### test: ## Sestaví knihovny GoogleTest a GoogleMock a spustí testy projektu
test: build-test-libs run-core-test 

### doc: ## Vygeneruje dokumentaci k projektu
doc:
	$(MAKE) $(SILENTOPT) clean-doc
	doxygen Doxyfile

### coverage: ## Vytvoří a zpracuje data o pokrytí kódu testy
coverage: build-coverage build-test-coverage run-test-coverage process-coverage

### profile: ## Sestaví a spustí profiling matematické knihovny
profile:
	$(MAKE) $(SILENTOPT) install-prof-dep
	$(MAKE) build-profile

	$(MAKE)  $(SILENTOPT) clean-profile
	rm -f $(PROFILE_BUILD_DIR)/gmon.out ./$(PROFILE_BUILD_DIR)/gmon.sum
	rm -f $(PROFILE_BUILD_DIR)/$(AUTO_GEN_DATA_FILE) 2>/dev/null || true

	$(MAKE) $(SILENTOPT) run-first-profile
	$(MAKE) $(SILENTOPT) run-next-profile

	gprof $(STDDEV) gmon.sum | tee gprof-report.txt | gprof2dot -s | dot -Gdpi=500 -Tpng -o gprof-report.png
	
	@mv gmon.out ./$(PROFILE_BUILD_DIR)/
	@mv gmon.sum ./$(PROFILE_BUILD_DIR)/
	@mv -f $(AUTO_GEN_DATA_FILE) $(PROFILE_BUILD_DIR)/ 2>/dev/null || true

	mv gprof-report.txt $(PROFILE_OUT_DIR)/
	mv gprof-report.png $(PROFILE_OUT_DIR)/

### build-gui: ## Sestaví grafické uživatelské rozhraní kalkulačky "Calm CatCalc"
build-gui:
	@mkdir -p $(GUI_BUILD_DIR)
	@cp $(GUI_DIR)/CMakeLists.txt $(GUI_BUILD_DIR)/
	cd $(GUI_BUILD_DIR) && cmake . && make
	sudo chmod 0700  /run/user/1000/
	@cd build && ln -snf gui/cat_calc_gui CalmCatCalc

### pack: ## Vytvoří ZIP archiv s projektem pro odevzdání
pack:
	$(MAKE) $(SILENTOPT) clean-pack
	mkdir -p $(PACK_DIR)

	$(MAKE) pack-repo
	$(MAKE) pack-doc
	$(MAKE) pack-install

	cd $(PACK_DIR) && zip -r ../$(PACK_NAME) ./
	rm -rf $(PACK_DIR)

################################################################################
#                                                                              #
#                  CÍLE PRO INSTALACI A AKTUALIZACI ZÁVISLOSTÍ                 #
#                                                                              #
################################################################################

### build: ## Sestaví "Calm CatCalc" s GUI a program "stddev" pro profilování
build: build-gui build-profile

### install: ## Aktualizuje seznam balíčků, instaluje a aktualizuje závislosti
install: update-dep install-dep upgrade-dep

### install-dep: ## Nainstaluje závislosti potřebné pro kompilaci projektu
install-dep: install-gui-dep install-doc-dep install-dev-dep install-prof-dep install-pack-dep

### install-gui-dep: ## Nainstaluje závislosti potřebné pro GUI kalkulačky
install-gui-dep:
	sudo apt-get install -y qtbase5-dev
	sudo apt-get install -y qt6-base-dev

### install-doc-dep: ## Nainstaluje závislosti potřebné pro generování dokumentace
install-doc-dep:
	sudo apt-get install -y doxygen

### install-dev-dep: ## Nainstaluje závislosti potřebné pro vývoj a testování
install-dev-dep: install-prof-dep
	sudo apt-get install -y binutils
	sudo apt-get install -y lcov

### install-prof-dep: ## Nainstaluje závislosti potřebné pro profilování
install-prof-dep:
	sudo apt-get install -y libcairo2-dev
	sudo apt-get install -y python3-pip
	sudo apt-get install -y graphviz
	sudo apt-get install -y tar
	sudo pip3 install gprof2dot

### install-pack-dep: ## Nainstaluje závislosti potřebné pro balení projektu
install-pack-dep:
	sudo apt-get install -y rsync
	sudo apt-get install -y zip

### update-dep: ## Aktualizuje seznam dostupných balíčků
update-dep:
	sudo apt-get update -y

### upgrade-dep: ## Aktualizuje závislosti potřebné pro kompilaci projektu
upgrade-dep:
	sudo apt-get upgrade -y
	sudo pip3 install --upgrade gprof2dot

### add-to-path: ## Přidá spustitelný soubor kalkulačky do systémové cesty
add-to-path: $(GUI_BUILD_DIR)/cat_calc_gui
	if [ $< -nt /usr/local/bin/catcalc ]; then \
		sudo cp $< /usr/local/bin/catcalc; \
	fi

################################################################################
#                                                                              #
#                        SPECIALIZOVANÉ PŘÍKAZY 'CLEAN'                        #
#                                                                              #
################################################################################

### clean-build: ## Odstraní všechny soubory z adresáře 'build'
clean-build:
	rm -rf $(BUILD_DIR)

### clean-core: ## Odstraní objektový soubor matematické knihovny "CatCalc Core"
clean-core:
	rm -f $(BUILD_DIR)/$(EXECUTABLE).o

### clean-doc: ## Odstraní všechny soubory z adresáře 'doc' (kromě /images)
clean-doc:
	find $(DOC_OUT_DIR) -mindepth 1 ! -path '$(DOC_OUT_DIR)/images*' -delete

### clean-coverage: ## Odstraní všechny soubory vytvořené během pokrytí kódu
clean-coverage:
	rm -rf $(COVERAGE_BUILD_DIR)

### clean-profile: ## Odstraní všechny soubory vytvořené během profilování
clean-profile:
	rm -f $(PROFILE_OUT_DIR)/gprof-report.txt
	rm -f $(PROFILE_OUT_DIR)/gprof-report.png

### clean-pack: ## Odstraní ZIP archiv s projektem pro odevzdání
clean-pack:
	rm -f ../$(PACK_NAME)


################################################################################
#                                                                              #
#              KOMPILACE MATEMATICKÉ KNIHOVNY "Calm CatCalc Core"              #
#                                                                              #
################################################################################

### build-core: ## Sestaví matematickou knihovnu "CatCalc Core"
build-core: $(BUILD_DIR)/$(EXECUTABLE).o

# Stavba objekotvého souboru matematické knihovny "CatCalc Core"
$(BUILD_DIR)/$(EXECUTABLE).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_STD) -c $< -o $@


################################################################################
#                                                                              #
#          KOMPILACE GOOGLE TEST UNIT TESTŮ PRO MATEMATICKOU KNIHOVNU          #
#                                                                              #
################################################################################

### run-core-test: ## Spustí testy matematické knihovny "CatCalc Core"
run-core-test: $(BUILD_DIR)/$(EXECUTABLE)_test
	./$(BUILD_DIR)/$(EXECUTABLE)_test

### build-test: ## Sestaví testy matematické knihovny "CatCalc Core"
build-test: $(BUILD_DIR)/$(EXECUTABLE)_test

### build-test-libs: ## Sestaví knihovny Google Test a Google Mock
build-test-libs: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o \
                 $(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o \
                 $(TEST_BUILD_DIR)/gtest_main.a \
				 $(TEST_BUILD_DIR)/gtest.a

### build-test-debug: ## Sestaví program s funkcí 'main()' pro debuggování knihovny
build-test-debug: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug

# Stavba testu matematické knihovny "CatCalc Core"
$(BUILD_DIR)/$(EXECUTABLE)_test: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o \
                              $(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o \
                              $(TEST_BUILD_DIR)/gtest_main.a \
							  $(TEST_BUILD_DIR)/gtest.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) $^ -o $@

$(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o: $(CORE_DIR)/$(EXECUTABLE).cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@
	
$(TEST_BUILD_DIR)/$(EXECUTABLE)_test.o: $(TEST_DIR)/$(EXECUTABLE)_tests.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@

# Stavba debuggovací varianty testů s funkcí main
$(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug: $(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug.o \
                                            $(TEST_BUILD_DIR)/$(EXECUTABLE)-debug.o
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) $^ -o $@

$(TEST_BUILD_DIR)/$(EXECUTABLE)_test_debug.o: $(TEST_DIR)/$(EXECUTABLE)_tests_for_debug.cpp
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $< -o $@

# Stavba objektových souborů Google Test knihoven
$(TEST_BUILD_DIR)/gtest-all.o: $(GTEST_DIR)/src/*.cc
	@mkdir -p $(TEST_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_TEST) -c $(GTEST_DIR)/src/gtest-all.cc -o $@

$(TEST_BUILD_DIR)/gtest_main.o: $(GTEST_DIR)/src/*.cc
	@mkdir -p $(TEST_BUILD_DIR)
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

### build-coverage: ## Sestaví knihovnu a testy s přepínači pro pokrytím kódu
build-coverage: $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o \
                $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage

### build-test-coverage: ## Sestaví testy s přepínači pro pokrytím kódu
build-test-coverage: build-test-libs $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage

### run-test-coverage: ## Spustí testy s pokrytím kódu
run-test-coverage:
	./$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage 2>/dev/null || true

### process-coverage: ## Zpracuje data o pokrytí kódu a vygeneruje HTML výstup
process-coverage:
	lcov --quiet --directory $(COVERAGE_BUILD_DIR) --capture \
	--output-file $(COVERAGE_BUILD_DIR)/coverage.info

	@lcov --quiet --remove $(COVERAGE_BUILD_DIR)/coverage.info '/usr/*' \
	--output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	@lcov --quiet --remove $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	'*/googletest-src/*' --output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	@lcov --quiet --remove $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	'*/profiler/*' --output-file $(COVERAGE_BUILD_DIR)/filtered_coverage.info

	genhtml $(COVERAGE_BUILD_DIR)/filtered_coverage.info \
	--output-directory $(COVERAGE_BUILD_DIR)

# Stavba testů s přepínači pro profilování pomocí gprof
$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage:  \
                        $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage.o \
                        $(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o \
                        $(TEST_BUILD_DIR)/gtest_main.a
	@mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) $^ -o $@

$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)_test-coverage.o: $(TEST_DIR)/$(EXECUTABLE)_tests.cpp
	@mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) -c $< -o $@

# Stavba matematické knihovny s přepínači pro pokrytí kódu
$(COVERAGE_BUILD_DIR)/$(EXECUTABLE)-coverage.o: $(CORE_DIR)/$(EXECUTABLE).cpp
	@mkdir -p $(COVERAGE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_COV) -c $< -o $@


################################################################################
#                                                                              #
#                    PROFILER - VÝPOČET SMĚRODATNÉ ODCHYLKY                    #
#                                                                              #
################################################################################

### build-profile: ## Sestaví profiler pro výpočet směrodatné odchylky
build-profile: $(BUILD_DIR)/$(PROFILER)

### run-first-profile: ## Spustí první běh profilování matematické knihovny
run-first-profile:
	if [ "$(FILE)" = "-1" ]; then \
		echo -1 > ./$(BUILD_DIR)/temp.txt; \
		$(STDDEV) < ./$(BUILD_DIR)/temp.txt; \
	else \
		$(STDDEV) < $(FILE); \
	fi; \
	mv gmon.out gmon.sum

### run-next-profile: ## Spustí další běhy profilování matematické knihovny
# Počet běhů lze nastavit pomocí proměnné 'PROF' v hlavičce Makefile
run-next-profile:
	itr=1 ; while [ $$itr -le $(PROF) ]; do \
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

### run-stddev-test: ## Spustí testy programu pro výpočet směrodatné odchylky
run-stddev-test: build-profile
	@mkdir -p $(PROFILE_BUILD_DIR)
	$(MAKE) $(SILENTOPT) prep-stddev-test
	$(TEST_BUILD_DIR)/$(STDDEV_TEST) $(ADV)
	@mv gmon.out ./$(PROFILE_BUILD_DIR)/

### prep-stddev-test: ## Připraví testovací data pro program pro výpočet směrodatné odchylky
prep-stddev-test:
	@mkdir -p $(TEST_BUILD_DIR)
	cp tests/$(STDDEV_TEST_PACK) $(TEST_BUILD_DIR)/
	tar -xzf $(TEST_BUILD_DIR)/$(STDDEV_TEST_PACK) -C $(TEST_BUILD_DIR)/
	@cp tests/$(STDDEV_TEST) $(TEST_BUILD_DIR)/

	if [ ! -x $(TEST_BUILD_DIR)/$(STDDEV_TEST) ]; then \
		sudo chmod a+x $(TEST_BUILD_DIR)/$(STDDEV_TEST); \
	fi

# Stavba objektového souboru programu "stddev" pro výpočet směrodatné odchylky
$(PROFILE_BUILD_DIR)/$(PROFILER).o: $(PROFILE_DIR)/$(PROFILER).cpp
	@mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) -c $< -o $@

# Stavba binárky programu "stddev" pro výpočet směrodatné odchylky
$(BUILD_DIR)/$(PROFILER): $(PROFILE_BUILD_DIR)/$(PROFILER).o \
                          $(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(PROFILER).o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) $^ -o $@

# Stavba matematické knihovny s přepínači pro profilování pomocí gprof
$(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(PROFILER).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	@mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) -c $< -o $@


################################################################################
#                                                                              #
#                  ZABALENÍ PROJEKTU PRO ODEVZDÁNÍ do '.ZIP'                   #
#                                                                              #
################################################################################

### pack-repo: ## Zkopíruje požadované složky repozitáře do složky pro odevzdání
pack-repo:
	rsync -av --progress ../.git $(PACK_REPO_DIR)/
	rsync -av --progress ../.github $(PACK_REPO_DIR)/
	rsync -av --progress ../.vscode $(PACK_REPO_DIR)/
	rsync -av --progress ../doc $(PACK_REPO_DIR)/
	rsync -av --progress ../mockup $(PACK_REPO_DIR)/
	rsync -av --progress ../plan $(PACK_REPO_DIR)/
	rsync -av --progress ../profiling $(PACK_REPO_DIR)/
	rsync -av --progress ../src $(PACK_REPO_DIR)/ --exclude build
	rsync -av --progress ../.editorconfig $(PACK_REPO_DIR)/
	rsync -av --progress ../.gitignore $(PACK_REPO_DIR)/
	rsync -av --progress ../LICENSE $(PACK_REPO_DIR)/
	rsync -av --progress ../README.md $(PACK_REPO_DIR)/

### pack-doc: ## Vygeneruje dokumentaci pro účely odevzdání do složky pro odevzdání
pack-doc:
	$(MAKE) $(SILENTOPT) doc
	cp -r $(DOC_OUT_DIR)/ $(PACK_DOC_DIR)/
	@$(MAKE) $(SILENTOPT) clean-doc

### pack-install: ## Zkopíruje instalátor do složky pro odevzdání
pack-install:
	@echo "NULL"