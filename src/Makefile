################################################################################
#                                                                              #
# Název projektu:   Calm CatCalc                                               #
#                                                                              #
# Soubor:           Makefile                                                   #
# Autor:            Jan Kalina <xkalinj00>                                     #
# Datum:            20.03.2024                                                 #
# Poslední změna:   20.04.2024                                                 #
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
        update-dep install-dep upgrade-dep add-to-path set-env-var \
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
	cd $(DOC_OUT_DIR)/html && grep -v 'target="_self">resources\|target="_self">doc' files.html > temp.html && mv temp.html files.html
	

### coverage: ## Vytvoří a zpracuje data o pokrytí kódu testy
coverage: build-coverage build-test-coverage run-test-coverage process-coverage

### profile: ## Sestaví a spustí profiling matematické knihovny
profile: install-prof-dep build-profile run-profile
	
### build-gui: ## Sestaví grafické uživatelské rozhraní kalkulačky "Calm CatCalc"
build-gui: set-env-var
	@mkdir -p $(GUI_BUILD_DIR)
	@cp $(GUI_DIR)/CMakeLists.txt $(GUI_BUILD_DIR)/
	cd $(GUI_BUILD_DIR) && cmake . && make
	sudo chmod 0700  /run/user/1000/
	cd build && sudo ln -snf gui/cat_calc_gui CalmCatCalc

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
install-dep: install-gui-dep install-doc-dep install-dev-dep install-pack-dep

### install-gui-dep: ## Nainstaluje závislosti potřebné pro GUI kalkulačky
install-gui-dep:
	sudo apt-get install -y qtbase5-dev
	sudo apt-get install -y qt6-base-dev
	sudo apt-get install -y qt6-wayland
	sudo apt-get install -y qtwayland5

### install-doc-dep: ## Nainstaluje závislosti potřebné pro generování dokumentace
install-doc-dep:
	sudo apt-get install -y doxygen

### install-dev-dep: ## Nainstaluje závislosti potřebné pro vývoj a testování
install-dev-dep: install-prof-dep
	sudo apt-get install -y binutils
	sudo apt-get install -y lcov
	sudo apt-get install -y less
	sudo apt-get install -y cmake

### install-prof-dep: ## Nainstaluje závislosti potřebné pro profilování
install-prof-dep:
	sudo apt-get install -y libcairo2-dev
	sudo apt-get install -y python3-pip
	sudo apt-get install -y graphviz
	sudo apt-get install -y tar
	sudo apt-get install -y neofetch
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
	sudo apt-get upgrade -y qtbase5-dev
	sudo apt-get upgrade -y qt6-base-dev
	sudo apt-get upgrade -y qtwayland5
	sudo apt-get upgrade -y qt6-wayland
	sudo apt-get upgrade -y doxygen
	sudo apt-get upgrade -y binutils
	sudo apt-get upgrade -y lcov
	sudo apt-get upgrade -y less
	sudo apt-get upgrade -y cmake
	sudo apt-get upgrade -y libcairo2-dev
	sudo apt-get upgrade -y python3-pip
	sudo apt-get upgrade -y graphviz
	sudo apt-get upgrade -y tar
	sudo apt-get upgrade -y neofetch
	sudo apt-get upgrade -y rsync
	sudo apt-get upgrade -y zip
	sudo pip3 install --upgrade gprof2dot

### add-to-path: ## Přidá spustitelný soubor kalkulačky do systémové cesty
add-to-path: $(GUI_BUILD_DIR)/cat_calc_gui
	sudo cp $< /usr/local/bin/catcalc

### set-env-var: ## Nastaví proměnnou prostředí QT_QPA_PLATFORM=wayland, pokud ještě není nastavena
set-env-var:
	@{ \
	if ! awk '/export QT_QPA_PLATFORM=wayland/ {found=1} END {exit !found}' ~/.profile; then \
		echo "" >> ~/.profile; \
		echo "export QT_QPA_PLATFORM=wayland" >> ~/.profile; \
		. ~/.profile; \
	fi; \
	} 

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

### clean-doc: ## Odstraní všechny soubory z adresáře 'doc' (kromě ./resources/)
clean-doc:
	find $(DOC_OUT_DIR) -mindepth 1 ! -path '$(DOC_OUT_DIR)/resources*' -delete

### clean-coverage: ## Odstraní všechny soubory vytvořené během pokrytí kódu
clean-coverage:
	rm -rf $(COVERAGE_BUILD_DIR)

### clean-profile: ## Odstraní všechny soubory vytvořené během profilování
clean-profile:
	rm -f $(PROFILE_OUT_DIR)/flat-profile.txt
	rm -f $(PROFILE_OUT_DIR)/gprof-report.md
	rm -f $(PROFILE_OUT_DIR)/gprof-report.png
	@mkdir -p $(PROFILE_OUT_DIR)
	@if [ ! -f $(PROFILE_OUT_DIR)/.placeholder ]; then \
		touch $(PROFILE_OUT_DIR)/.placeholder; \
	fi

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

### run-profile: ## Spustí profiling matematické knihovny
run-profile: $(BUILD_DIR)/$(PROFILER)
	$(MAKE)  $(SILENTOPT) clean-profile
	rm -f $(PROFILE_BUILD_DIR)/gmon.out ./$(PROFILE_BUILD_DIR)/gmon.sum
	rm -f $(PROFILE_BUILD_DIR)/$(AUTO_GEN_DATA_FILE) 2>/dev/null || true

	$(MAKE) $(SILENTOPT) run-first-profile
	$(MAKE) $(SILENTOPT) run-next-profile

	$(MAKE) $(SILENTOPT) process-profile

### process-profile: ## Zpracuje data o profilování a vygeneruje jejich výstup
process-profile:
	gprof $(STDDEV) gmon.sum | tee flat-profile.txt | gprof2dot -s | dot -Gdpi=400 -Tpng -o gprof-report.png
	
	@mv gmon.out ./$(PROFILE_BUILD_DIR)/
	@mv gmon.sum ./$(PROFILE_BUILD_DIR)/
	@mv -f $(AUTO_GEN_DATA_FILE) $(PROFILE_BUILD_DIR)/ 2>/dev/null || true

	mv flat-profile.txt $(PROFILE_OUT_DIR)/
	mv gprof-report.png $(PROFILE_OUT_DIR)/

	$(MAKE) $(SILENTOPT) filter-profile

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

### filter-report: ## Zpracuje data o profilování a vygeneruje markdown report
filter-profile:
	@awk 'NR < 6 || /catMath|catStddev|main/ || /----------/ {print} \
	/the percentage of the total running time of the/ {print; p=1} p && !/index \
	% time    self  children    called     name/ {print} /index % time    self  \
	children    called     name/ {print; p=0; q=1} q && /catMath|catStddev|main/ \
	{print} /This table describes the call tree of the program, and was sorted by/ \
	{print; q=0; r=1} r && !/Index by function name/ {print} /Index by function name/ \
	{print; r=0; s=1} s && /catMath|catStddev|main/ {print}' \
	$(PROFILE_OUT_DIR)/flat-profile.txt > $(PROFILE_OUT_DIR)/temp1.txt

	@awk '{if(/index % time    self  children    called     name/ || \
	/catMath|catStddev|main/) {sub(/\(.*/, ""); sub(/\[abi:cxx11\]/, ""); print} \
	else print}' $(PROFILE_OUT_DIR)/temp1.txt > $(PROFILE_OUT_DIR)/temp2.txt

	@awk 'NR == 1 || $$0 != prev {print} {prev = $$0}' $(PROFILE_OUT_DIR)/temp2.txt > \
	$(PROFILE_OUT_DIR)/temp1.txt

	@awk '{gsub(/(catMath[a-zA-Z0-9_::]+|catStddev[a-zA-Z0-9_::]+|main[a-zA-Z0-9_::]+)/, \
	"&()"); print}' $(PROFILE_OUT_DIR)/temp1.txt > $(PROFILE_OUT_DIR)/temp2.txt

	@awk 'BEGIN {print "# Zpráva z Gprof\n## Informace o systému"}' > \
	$(PROFILE_OUT_DIR)/gprof-report.md

	@neofetch --off | awk '{sub(/[ \t]+$$/, "", $$0); if(NR==1) print "**"$$0"**"; \
	else if(/Memory/) {print "- **"$$1"** " substr($$0, index($$0,$$2)); exit} else \
	if(/Theme/ || /Icons/) next; else if(NR>2) print "- **"$$1"** " \
	substr($$0, index($$0,$$2))}' | sed -r 's/\x1b\[[0-9;]*[mK]//g' | \
	sed 's/\x1b\[[?][0-9;]*[hl]//g' >> $(PROFILE_OUT_DIR)/gprof-report.md

	@awk 'BEGIN {print "\n## Flat profile\n### Každý vzorek je počítán jako 0.01 sekundy."}' \
	>> $(PROFILE_OUT_DIR)/gprof-report.md

	@awk 'BEGIN {print "| Time [%] | Cumulative [s] | Self [s] | Calls | Self [ms/call] | \
	Total [ms/call] | Name |"; print "|:---:|:---:|:---:|:---:|:---:|:---:|---|"} \
	NR>=6 {if (/the percentage of the total running time of the/) exit; else \
	printf("| %s | %s | %s | %s | %s | %s | %s |\n", $$1, $$2, $$3, $$4, $$5, $$6, $$7)}' \
	$(PROFILE_OUT_DIR)/temp2.txt >> $(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN {print "\n\n<br>\n\n- `%`:\n  - **=** Procento celkové doby běhu programu využité \
	touto funkcí.\n- `Cumulative seconds`:\n  - **=** Běžný součet sekund přiřazených této funkci a \
	těm, které jsou uvedeny nad ní.\n- `Self seconds`:\n  - **=** Počet sekund přiřazených pouze \
	této funkci.\n  - Toto je hlavní kritérium pro toto seřazení.\n- `Calls`:\n  - **=** Počet volání \
	této funkce, pokud je tato funkce profilována, jinak prázdné.\n- `Self ms/call`:\n  - **=** \
	Průměrný počet milisekund strávených v této funkci na volání, pokud je tato funkce profilována, \
	jinak prázdné.\n- `Total ms/call`:\n  - **=** Průměrný počet milisekund strávených v této funkci \
	a jejích potomcích na volání, pokud je tato funkce profilována, jinak prázdné.\n- `Name`:\n  - \
	**= Název funkce**\n  - Toto je vedlejší kritérium pro toto seřazení.\n  - Index ukazuje umístění \
	funkce v seznamu *gprof*.\n  - Pokud je index v závorce, ukazuje, kde by se objevil v seznamu *gprof*, \
	pokud by byl vytištěn.\n\n<br>\n\n# Graf volání (call graph)\n"}' >> $(PROFILE_OUT_DIR)/gprof-report.md

	@awk '/granularity: each sample hit covers 4 byte\\(s\\) for / {split($$9, a, "%"); \
	split($$11, b, " "); print "- `granularity` **=** každý vzorek pokrývá 4 bajty pro " a[1] \
	"% z " b[1] " sekundy\\n\\n<br>\\n"}' $(PROFILE_OUT_DIR)/temp2.txt >> $(PROFILE_OUT_DIR)/gprof-report.md

	@awk '\
	BEGIN {\
		print_table = 0;\
		print "| Index | Time [%] | Self | Children | Called | Name |"; \
		print "|:-----:|:--------:|:----:|:--------:|:------:|------|"; \
	}\
	/index % time    self  children    called     name/ {\
		print_table = 1;\
		next;\
	}\
	/This table describes the call tree of the program, and was sorted by/ { \
		print_table = 0; \
	}\
	print_table == 1 { \
		if ($$0 ~ /^-+$$/) { \
			print "| | | | | | |\n| | | | | | |"; \
		} else if ($$0 ~ /^\[/) { \
			if ($$5 == "main") { \
				printf("| %s | %s | %s | %s | | %s %s |\n", $$1, $$2, $$3, $$4, $$5, $$6);\
			} else {\
				printf("| %s | %s | %s | %s | %s | %s |\n", $$1, $$2, $$3, $$4, $$5, \
				substr($$0, index($$0,$$6), length($$6)));\
			}\
		} else {\
			printf("| | | %s | %s | %s | %s |\n", $$1, $$2, $$3, substr($$0, index($$0,$$4), length($$4)));\
		}\
	}\
	' $(PROFILE_OUT_DIR)/temp2.txt >> $(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN{print "<br>\n\nTato tabulka popisuje strom volání programu a byla seřazena \
	podle celkového času stráveného v každé funkci a jejích potomcích.\n\nKaždý záznam v \
	této tabulce se skládá z několika řádků. Řádek s indexovým číslem na levém okraji \
	uvádí aktuální funkci. Řádky nad ním uvádějí funkce, které tuto funkci volaly, a \
	řádky pod ním uvádějí funkce, které tato funkce volala. Tento řádek uvádí:\n\n- \
	`index`\n  - Jedinečné číslo přidělené každému prvku tabulky.\n  - Indexová čísla \
	jsou seřazena numericky.\n  - Indexové číslo je vytisknuto vedle každého názvu \
	funkce, aby bylo snazší zjistit, kde je funkce v tabulce.\n- `time [%]`\n  - Toto \
	je procento z *celkového* času, které bylo stráveno v této funkci a jejích \
	potomcích."}' >> $(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN{print "\n  - Vzhledem k různým hlediskům, vyloučenými funkcemi atd. se \
	tyto čísla NESEČTOU na 100%.\n- `self`\n  - Toto je celkové množství času \
	stráveného v této funkci.\n- `children`\n  - Toto je celkové množství času, které \
	do této funkce přenesly její potomci.\n- `called`\n  - Toto je počet volání \
	funkce.\n  - Pokud funkce volala sama sebe rekurzivně, číslo zahrnuje pouze \
	nerekurzivní volání a je následováno `+` a počtem rekurzivních volání.\n- `name` - \
	Název aktuální funkce.\n  - Indexové číslo je vytisknuto za ním.\n  - Pokud je \
	funkce členem cyklu, číslo cyklu je vytisknuto mezi názvem funkce a indexovým \
	číslem.\n\n<br>\n\n"}' >> $(PROFILE_OUT_DIR)/gprof-report.md	
	
	@awk 'BEGIN{print "**Pro rodiče funkce mají pole následující významy:**\n\n- `self`\n  \
	- Toto je množství času, které bylo přímo přeneseno z funkce do tohoto rodiče.\n- \
	`children`\n  - Toto je množství času, které bylo přeneseno z potomků funkce do \
	tohoto rodiče.\n- `called`\n  - Toto je počet volání, které tento rodič provedl \
	funkci `/` celkový počet volání funkce.\n  - Rekurzivní volání funkce nejsou zahrnuta \
	v čísle za `/`.\n- `name` - Toto je název rodiče.\n  - Indexové číslo rodiče je \
	vytisknuto za ním.\n  - Pokud je rodič členem cyklu, číslo cyklu je vytisknuto mezi \
	názvem a indexovým číslem.\n- ***Pokud nelze určit rodiče funkce, pole jsou \
	prázdná.***\n\n<br>\n\n"}' >> $(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN{print "**Pro potomky funkce mají pole následující významy:**\n\n- `self`\n  \
	- Toto je množství času, které bylo přímo přeneseno z potomka do funkce.\n- \
	`children`\n  - Toto je množství času, které bylo přeneseno z potomků potomka do \
	funkce.\n- `called`\n  - Toto je počet volání, které funkce provedla tomuto \
	potomku `/` celkový počet volání potomka.\n  - Rekurzivní volání potomkem nejsou \
	uvedena v čísle za `/`.\n- `name`\n  - Toto je název potomka.\n  - Indexové číslo \
	potomka je vytisknuto za ním.\n  - Pokud je potomek členem cyklu, číslo cyklu je \
	vytisknuto mezi názvem a indexovým číslem.\n\n<br>\n\n"}' >> \
	$(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN{print "Pokud jsou v grafu volání nějaké cykly (kruhy), existuje záznam pro \
	celý cyklus. Tento záznam ukazuje, kdo volal cyklus (jako rodiče) a členy cyklu (jako \
	potomky). Záznam `+` rekurzivních volání ukazuje počet volání funkcí, které byly \
	interní pro cyklus, a záznam volání pro každého člena ukazuje, kolikrát byl volán od \
	ostatních členů cyklu.\n\n## Indexy funkcí\n"}' >> $(PROFILE_OUT_DIR)/gprof-report.md
	
	@awk 'BEGIN {start=0;} /Index by function name/ {start=1; next;} start==1 && \
	/\[[0-9]+\] .+::.+/{gsub(/\[/, "**["); gsub(/\]/, "]** `"); gsub(/$$/, "`"); print \
	"- " $$0;}' $(PROFILE_OUT_DIR)/temp2.txt | sort -n -t ']' -k 2 >> \
	$(PROFILE_OUT_DIR)/gprof-report.md

	@rm -f $(PROFILE_OUT_DIR)/temp1.txt
	@rm -f $(PROFILE_OUT_DIR)/temp2.txt


################################################################################
#                                                                              #
#                  ZABALENÍ PROJEKTU PRO ODEVZDÁNÍ do '.ZIP'                   #
#                                                                              #
################################################################################

### pack-repo: ## Zkopíruje požadované složky repozitáře do složky pro odevzdání
pack-repo:
	if [ -d "../.git" ]; then \
		rsync -av --progress ../.git $(PACK_REPO_DIR)/; \
	else \
		echo "../.git does not exist"; \
	fi
	if [ -d "../.github" ]; then \
		rsync -av --progress ../.github $(PACK_REPO_DIR)/; \
	else \
		echo "../.github does not exist"; \
	fi
	if [ -d "../.vscode" ]; then \
		rsync -av --progress ../.vscode $(PACK_REPO_DIR)/; \
	else \
		echo "../.vscode does not exist"; \
	fi
	if [ -d "../doc" ]; then \
		rsync -av --progress ../doc $(PACK_REPO_DIR)/; \
	else \
		echo "../doc does not exist"; \
	fi
	if [ -d "../mockup" ]; then \
		rsync -av --progress ../mockup $(PACK_REPO_DIR)/; \
	else \
		echo "../mockup does not exist"; \
	fi
	if [ -d "../plan" ]; then \
		rsync -av --progress ../plan $(PACK_REPO_DIR)/; \
	else \
		echo "../plan does not exist"; \
	fi
	if [ -d "../profiling" ]; then \
		rsync -av --progress ../profiling $(PACK_REPO_DIR)/; \
	else \
		echo "../profiling does not exist"; \
	fi
	if [ -d "../src" ]; then \
		rsync -av --progress ../src $(PACK_REPO_DIR)/ --exclude build; \
	else \
		echo "../src does not exist"; \
	fi
	if [ -f "../.editorconfig" ]; then \
		rsync -av --progress ../.editorconfig $(PACK_REPO_DIR)/; \
	else \
		echo "../.editorconfig does not exist"; \
	fi
	if [ -f "../.gitignore" ]; then \
		rsync -av --progress ../.gitignore $(PACK_REPO_DIR)/; \
	else \
		echo "../.gitignore does not exist"; \
	fi
	if [ -f "../LICENSE" ]; then \
		rsync -av --progress ../LICENSE $(PACK_REPO_DIR)/; \
	else \
		echo "../LICENSE does not exist"; \
	fi
	if [ -f "../README.md" ]; then \
		rsync -av --progress ../README.md $(PACK_REPO_DIR)/; \
	else \
		echo "../README.md does not exist"; \
	fi

### pack-doc: ## Vygeneruje dokumentaci pro účely odevzdání do složky pro odevzdání
pack-doc:
	$(MAKE) $(SILENTOPT) doc
	cp -r $(DOC_OUT_DIR)/ $(PACK_DOC_DIR)/
	@$(MAKE) $(SILENTOPT) clean-doc

### pack-install: ## Zkopíruje instalátor do složky pro odevzdání
pack-install:
	@echo "NULL"
