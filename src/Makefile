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
GUI = cat_calc_gui

# Název a spouštění programu pro profilování
STDDEV = ./$(BUILD_DIR)/$(STDDEV_NAME)-profile
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


###                                               ###
#  Konfigurační parametry pro tvorbu debian balíku  #
###                                               ###

# Název a verze balíků
CATCALC = catcalc
CATCALC_NAME = calm-$(CATCALC)
CATCALC_VERSION = 1.0
PRODUCT_NAME_CATCALC = $(CATCALC_NAME)-$(CATCALC_VERSION)

STDDEV_NAME = stddev
STDDEV_VERSION = 1.0
PRODUCT_NAME_STDDEV = $(STDDEV_NAME)-$(STDDEV_VERSION)

# Adresář a zdrojové soubory pro zdrojové soubory k tvorbě debian balíku
INSTALL_MAIN_DIR = ../install
INSTALL_DIR_CATCALC = $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)/$(PRODUCT_NAME_CATCALC)
INSTALL_DIR_STDDEV = $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)/$(PRODUCT_NAME_STDDEV)

DEB_RESRC_DIR = deb-resources
ENV_SETUP_DIR = install
INSTALL_SRC = $(SRC_DIR) $(PROFILE_DIR) $(TEST_DIR) Makefile Doxyfile

# Cesta k adresáři, kam se má projekt nainstalovat
DESTDIR_CATCALC = debian/$(CATCALC_NAME)/
DESTDIR_STDDEV = debian/$(STDDEV_NAME)/
INSFLAGS = -m 0755


###                                                                       ###
#  Definice cest k různým složkám obsahující zdrojové soubory ke kompilaci  #
###                                                                       ###

# Cesta ke zdrojovým souborům Google Test a Google Mock knihoven
GTEST_DIR = ./tests/googletest-src/googletest
GMOCK_DIR = ./tests/googletest-src/googlemock

# Cesta ke zdrojovým souborům matematické knihovny "Calm CatCalc Core" a testů
SRC_DIR = CalmCatCalc
CORE_DIR = $(SRC_DIR)/core
GUI_DIR = $(SRC_DIR)/$(GUI)
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
STDDEV_BUILD_DIR = $(BUILD_DIR)/$(STDDEV_NAME)-build
GUI_BUILD_DIR = $(BUILD_DIR)/gui
PACK_DIR = ../xkalinj00_xfarkal00_xhyzapa00_xkrejcd00

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
.PHONY: all build-core build-coverage build-gui build-profile build-test-coverage \
        build-test-debug build-test-libs build-test build clean-build clean-core \
		clean-coverage clean-doc clean-pack clean-profile clean coverage deb-init \
		deb-make deb-make-catcalc deb-make-stddev deb-init-catcalc deb-init-stddev \
		deb-rewrite-control-catcalc deb-rewrite-control-stddev deb-rewrite-rules-catcalc \
		deb-rewrite-rules-stddev deb-rewrite-copyright build-stddev \
		dev-add-to-path dev-install-dep dev-install-doc-dep \
		dev-install-pack-dep dev-install-prof-dep dev-install \
		dev-set-env-var dev-update-dep doc filter-report help \
		install-catcalc install-stddev pack-doc pack-install pack-repo pack \
		prep-stddev-test process-coverage process-profile profile run-core-test \
		run-first-profile run-next-profile run-profile run-stddev-test \
		run-test-coverage test deb-rewrite-readme-catcalc deb-rewrite-scripts-catcalc \
		deb-rewrite-scripts-stddev deb-rewrite-readme-stddev uninstall-catcalc uninstall-stddev uninstall

### all: ## Nainstaluje dev-verze kalkulačky "Calm CatCalc" a programu "stddev"
all:
	$(MAKE) $(SILENTOPT) deb-clean
	$(MAKE) $(SILENTOPT) deb-init
	$(MAKE) $(SILENTOPT) deb-make
	cd ../install && sudo apt install ./$(CATCALC_NAME)_$(CATCALC_VERSION)_amd64.deb
	cd ../install && sudo apt install ./$(STDDEV_NAME)_$(STDDEV_VERSION)_amd64.deb

### install-catcalc: ## Nainstaluje kalkulačku "Calm CatCalc" s GUI
install-catcalc: build-gui
	mkdir -p $(DESTDIR_CATCALC)/usr/bin
	install $(INSFLAGS) $(BUILD_DIR)/$(GUI) $(DESTDIR_CATCALC)/usr/bin/$(CATCALC)

### install-stddev: ## Nainstaluje program na výpočet výběrové směrodatné odchylky "stddev"
install-stddev: build-stddev 
	mkdir -p $(DESTDIR_STDDEV)/usr/bin
	install $(INSFLAGS) $(BUILD_DIR)/stddev $(DESTDIR_STDDEV)/usr/bin/stddev

### build: ## Sestaví "Calm CatCalc" s GUI a program "stddev" pro profilování
build: build-gui build-stddev

### help: ## Vypíše nápovědu k použití Makefile
help:
	@dpkg -s less >/dev/null 2>&1 || (echo "Instaluji less" && sudo apt-get install less)
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
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)

### uninstall: ## Odinstaluje kalkulačku "Calm CatCalc" a program "stddev"
uninstall: uninstall-catcalc uninstall-stddev

### uninstall-catcalc: ## Odinstaluje kalkulačku "Calm CatCalc"
uninstall-catcalc:
	sudo apt remove $(CATCALC_NAME)

### uninstall-stddev: ## Odinstaluje kalkulačku "Stddev"
uninstall-stddev:
	sudo apt remove $(STDDEV_NAME)

### test: ## Sestaví knihovny GoogleTest a GoogleMock a spustí testy projektu
test: build-test-libs run-core-test 

### doc: ## Vygeneruje dokumentaci k projektu
doc:
	$(MAKE) $(SILENTOPT) dev-install-doc-dep
	$(MAKE) $(SILENTOPT) clean-doc
	doxygen Doxyfile
	cd $(DOC_OUT_DIR)/html && grep -v 'target="_self">resources\|target="_self">doc' files.html > temp.html && mv temp.html files.html
	
### coverage: ## Vytvoří a zpracuje data o pokrytí kódu testy
coverage:
	@dpkg -s lcov >/dev/null 2>&1 || (echo "Instaluji lcov" && sudo apt-get install lcov)
	$(MAKE) build-coverage
	$(MAKE) build-test-coverage
	$(MAKE) run-test-coverage
	$(MAKE) process-coverage

### profile: ## Sestaví a spustí profiling matematické knihovny
profile:
	$(MAKE) $(SILENTOPT) dev-install-prof-dep
	@if ! test -f build/stddev; then \
		echo "Soubor 'stddev-profile' neexistuje, provádím build-profile"; \
		$(MAKE) $(SILENTOPT) build-profile; \
	fi
	$(MAKE) $(SILENTOPT) run-profile
	
### build-gui: ## Sestaví grafické uživatelské rozhraní kalkulačky "Calm CatCalc"
build-gui:
	@dpkg -s cmake >/dev/null 2>&1 || (echo "Instaluji cmake" && sudo apt-get install cmake)
	@mkdir -p $(GUI_BUILD_DIR)
	@cp $(GUI_DIR)/CMakeLists.txt $(GUI_BUILD_DIR)/
	cd $(GUI_BUILD_DIR) && cmake . && make
	mv $(GUI_BUILD_DIR)/$(GUI) $(BUILD_DIR)/

### pack: ## Vytvoří ZIP archiv s projektem pro odevzdání
pack:
	$(MAKE) $(SILENTOPT) dev-install-pack-dep
	$(MAKE) $(SILENTOPT) clean-pack
	mkdir -p $(PACK_DIR)

	$(MAKE) pack-repo
	$(MAKE) pack-doc
	$(MAKE) pack-install

	cd $(PACK_DIR) && zip -r ../$(PACK_NAME) ./
	rm -rf $(PACK_DIR)

################################################################################
#                                                                              #
#                 CÍLE PRO TVORBU DEBIAN BALÍKŮ A INSTALÁTORŮ                  #
#                                                                              #
################################################################################

### deb-init: ## Vytvoří archiv se zdrojovými soubory a debian složku programu 'Calm CatCalc' i 'stddev'
deb-init: deb-init-catcalc deb-init-stddev

### deb-make: ## Vytvoří debian balík programu 'Calm CatCalc' i 'stddev'
deb-make: deb-make-catcalc deb-make-stddev

### deb-make-catcalc: ## Vytvoří debian balík programu 'Calm CatCalc'
deb-make-catcalc:
	cd $(INSTALL_DIR_CATCALC) && sudo dpkg-buildpackage -rfakeroot -uc -b
	mv $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)/$(CATCALC_NAME)_$(CATCALC_VERSION)_amd64.deb $(INSTALL_MAIN_DIR)/

### deb-make-stddev: ## Vytvoří debian balík programu 'stddev'
deb-make-stddev:
	cd $(INSTALL_DIR_STDDEV) && sudo dpkg-buildpackage -rfakeroot -uc -b
	mv $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)/$(STDDEV_NAME)_$(STDDEV_VERSION)_amd64.deb $(INSTALL_MAIN_DIR)/

### deb-init-catcalc: ## Vytvoří archiv se zdrojovými soubory a debian složku programu 'Calm CatCalc'
deb-init-catcalc: 
	mkdir -p $(INSTALL_DIR_CATCALC)
	cp -r $(INSTALL_SRC) $(INSTALL_DIR_CATCALC)
	cp -r $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/$(ENV_SETUP_DIR)_catcalc $(INSTALL_DIR_CATCALC)/$(ENV_SETUP_DIR)
	cd $(INSTALL_DIR_CATCALC) && tar -czvf ../$(PRODUCT_NAME_CATCALC).tar.gz $(INSTALL_SRC) $(ENV_SETUP_DIR)
	cd $(INSTALL_DIR_CATCALC) && dh_make -y -e xhyzapa00@stud.fit.vutbr.cz -n -s -c gpl3 -f ../$(PRODUCT_NAME_CATCALC).tar.gz
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/install-catcalc $(INSTALL_DIR_CATCALC)/debian/install
	$(MAKE) $(SILENTOPT) deb-rewrite-control-catcalc
	$(MAKE) $(SILENTOPT) deb-rewrite-rules-catcalc
	$(MAKE) $(SILENTOPT) deb-rewrite-readme-catcalc
	$(MAKE) $(SILENTOPT) deb-rewrite-scripts-catcalc
	$(MAKE) $(SILENTOPT) deb-rewrite-copyright
	
### deb-init-stddev: ## Vytvoří archiv se zdrojovými soubory a debian složku  programu 'stddev'
deb-init-stddev: 
	mkdir -p $(INSTALL_DIR_STDDEV)
	cp -r $(INSTALL_SRC) $(INSTALL_DIR_STDDEV)
	cp -r $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/$(ENV_SETUP_DIR)_stddev $(INSTALL_DIR_STDDEV)/$(ENV_SETUP_DIR)
	cd $(INSTALL_DIR_STDDEV) && tar -czvf ../$(PRODUCT_NAME_STDDEV).tar.gz $(INSTALL_SRC)
	cd $(INSTALL_DIR_STDDEV) && dh_make -y -e xhyzapa00@stud.fit.vutbr.cz -n -s -c gpl3 -f ../$(PRODUCT_NAME_STDDEV).tar.gz
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/install-stddev $(INSTALL_DIR_STDDEV)/debian/install
	$(MAKE) $(SILENTOPT) deb-rewrite-control-stddev
	$(MAKE) $(SILENTOPT) deb-rewrite-rules-stddev
	$(MAKE) $(SILENTOPT) deb-rewrite-readme-stddev
	$(MAKE) $(SILENTOPT) deb-rewrite-scripts-stddev
	$(MAKE) $(SILENTOPT) deb-rewrite-copyright

### deb-rewrite-control-catcalc: ## Přepíše soubor 'control' pro debian balík programu 'Calm CatCalc'
deb-rewrite-control-catcalc:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/control-catcalc $(INSTALL_DIR_CATCALC)/debian/control
	sed -i '/^Source:/c\Source: $(CATCALC_NAME)' $(INSTALL_DIR_CATCALC)/debian/control
	sed -i '/^Package:/c\Package: $(CATCALC_NAME)' $(INSTALL_DIR_CATCALC)/debian/control

### deb-rewrite-control-stddev: ## Přepíše soubor 'control' pro debian balík programu 'stddev'
deb-rewrite-control-stddev:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/control-stddev $(INSTALL_DIR_STDDEV)/debian/control
	sed -i '/^Source:/c\Source: $(STDDEV_NAME)' $(INSTALL_DIR_STDDEV)/debian/control
	sed -i '/^Package:/c\Package: $(STDDEV_NAME)' $(INSTALL_DIR_STDDEV)/debian/control

### deb-rewrite-rules-catcalc: ## Přepíše soubor 'rules' pro debian balík programu 'Calm CatCalc'
deb-rewrite-rules-catcalc:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/rules-catcalc $(INSTALL_DIR_CATCALC)/debian/rules

### deb-rewrite-rules-stddev: ## Přepíše soubor 'rules' pro debian balík programu 'stddev'
deb-rewrite-rules-stddev:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/rules-stddev $(INSTALL_DIR_STDDEV)/debian/rules

### deb-rewrite-scripts-catcalc: ## Přepíše soubor 'scripts' pro debian balík programu 'Calm CatCalc'
deb-rewrite-scripts-catcalc:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/preinst-catcalc.ex $(INSTALL_DIR_CATCALC)/debian/preinst.ex
	mv $(INSTALL_DIR_CATCALC)/debian/preinst.ex $(INSTALL_DIR_CATCALC)/debian/preinst
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/postrm-catcalc.ex $(INSTALL_DIR_CATCALC)/debian/postrm.ex
	mv $(INSTALL_DIR_CATCALC)/debian/postrm.ex $(INSTALL_DIR_CATCALC)/debian/postrm

### deb-rewrite-scripts-stddev: ## Přepíše soubor 'scripts' pro debian balík programu 'Stddev'
deb-rewrite-scripts-stddev:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/preinst-stddev.ex $(INSTALL_DIR_STDDEV)/debian/preinst.ex
	mv $(INSTALL_DIR_STDDEV)/debian/preinst.ex $(INSTALL_DIR_STDDEV)/debian/preinst

### deb-rewrite-readme-catcalc: ## Přepíše soubor 'readme' pro debian balík programu 'Calm CatCalc'
deb-rewrite-readme-catcalc:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/readme-catcalc $(INSTALL_DIR_CATCALC)/debian/README

### deb-rewrite-readme-stddev: ## Přepíše soubor 'readme' pro debian balík programu 'Stddev'
deb-rewrite-readme-stddev:
	cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/readme-stddev $(INSTALL_DIR_STDDEV)/debian/README

### deb-rewrite-copyright: ## Přepíše soubor 'copyright' pro debian balík aktuálními informacemi
deb-rewrite-copyright:
	if [ -d "$(INSTALL_DIR_CATCALC)/debian/" ]; then \
		cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/copyright $(INSTALL_DIR_CATCALC)/debian/; \
	fi

	if [ -d "$(INSTALL_DIR_STDDEV)/debian/" ]; then \
		cp $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)/copyright $(INSTALL_DIR_STDDEV)/debian/; \
	fi


################################################################################
#                                                                              #
#         CÍLE PRO INSTALACI VÝVOJÁŘSKÉ VERZE PŘÍMO ZE ZDROJOVÝCH KÓDŮ         #
#                                                                              #
################################################################################

### dev-install-dep: ## Nainstaluje závislosti potřebné pro kompilaci projektu
dev-install-dep: dev-update-dep dev-install-doc-dep dev-install-prof-dep dev-install-pack-dep
	@dpkg -s less >/dev/null 2>&1 || (echo "Instaluji less" && sudo apt-get install less)
	@dpkg -s lcov >/dev/null 2>&1 || (echo "Instaluji lcov" && sudo apt-get install lcov)

### dev-install-doc-dep: ## Nainstaluje závislosti potřebné pro generování dokumentace
dev-install-doc-dep:
	@dpkg -s doxygen >/dev/null 2>&1 || (echo "Instaluji doxygen" && sudo apt-get install doxygen)

### dev-install-prof-dep: ## Nainstaluje závislosti potřebné pro profilování
dev-install-prof-dep:
	@dpkg -s binutils >/dev/null 2>&1 || (echo "Instaluji binutils" && sudo apt-get install binutils)
	@dpkg -s libcairo2-dev >/dev/null 2>&1 || (echo "Instaluji libcairo2-dev" && sudo apt-get install libcairo2-dev)
	@dpkg -s python3-pip >/dev/null 2>&1 || (echo "Instaluji python3-pip" && sudo apt-get install python3-pip)
	@dpkg -s graphviz >/dev/null 2>&1 || (echo "Instaluji graphviz" && sudo apt-get install graphviz)
	@dpkg -s tar >/dev/null 2>&1 || (echo "Instaluji tar" && sudo apt-get install tar)
	@dpkg -s neofetch >/dev/null 2>&1 || (echo "Instaluji neofetch" && sudo apt-get install neofetch)
	@pip3 show gprof2dot >/dev/null 2>&1 || (echo "Instaluji gprof2dot" && sudo pip3 install gprof2dot)

### dev-install-pack-dep: ## Nainstaluje závislosti potřebné pro balení projektu
dev-install-pack-dep:
	@dpkg -s rsync >/dev/null 2>&1 || (echo "Instaluji rsync" && sudo apt-get install rsync)
	@dpkg -s zip >/dev/null 2>&1 || (echo "Instaluji zip" && sudo apt-get install zip)

### dev-update-dep: ## Aktualizuje seznam dostupných balíčků
dev-update-dep:
	sudo apt-get update -y

### dev-add-to-path: ## Přidá spustitelný soubor kalkulačky do systémové cesty
dev-add-to-path: $(BUILD_DIR)/$(GUI)
	sudo cp $< /usr/local/bin/catcalc

### dev-set-env-var: ## Nastaví proměnnou prostředí QT_QPA_PLATFORM=wayland, pokud ještě není nastavena
dev-set-env-var:
	sudo chmod 0700  /run/user/1000/
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
	find $(DOC_OUT_DIR) -mindepth 1 ! -path '$(DOC_OUT_DIR)/resources*' -delete || true

### clean-coverage: ## Odstraní všechny soubory vytvořené během pokrytí kódu
clean-coverage:
	rm -rf $(COVERAGE_BUILD_DIR)

### clean-profile: ## Odstraní všechny soubory vytvořené během profilování
clean-profile:
	rm -f $(PROFILE_OUT_DIR)/flat-profile.txt
	rm -f $(PROFILE_OUT_DIR)/gprof-report.md
	rm -f $(PROFILE_OUT_DIR)/gprof-report.png

### clean-pack: ## Odstraní ZIP archiv s projektem pro odevzdání
clean-pack:
	rm -f ../$(PACK_NAME)

### deb-clean: ## Odstraní adresáře a balíky vytvořené příkazem 'deb-init'
deb-clean:
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)_$(CATCALC_VERSION)_amd64.deb
	sudo rm -rf $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)_$(STDDEV_VERSION)_amd64.deb



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

### build-profile: ## Sestaví program pro výpočet směrodatné odchylky pro profilování
build-profile: $(BUILD_DIR)/$(STDDEV_NAME)-profile

### build-profile: ## Sestaví program pro výpočet směrodatné odchylky bez profilování
build-stddev: $(BUILD_DIR)/$(STDDEV_NAME)

### run-profile: ## Spustí profiling matematické knihovny
run-profile: $(BUILD_DIR)/$(STDDEV_NAME)-profile
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
run-stddev-test: build-stddev
	@mkdir -p $(PROFILE_BUILD_DIR)
	$(MAKE) $(SILENTOPT) prep-stddev-test
	$(TEST_BUILD_DIR)/$(STDDEV_TEST) $(ADV)

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
$(STDDEV_BUILD_DIR)/$(STDDEV_NAME).o: $(PROFILE_DIR)/$(STDDEV_NAME).cpp
	@mkdir -p $(STDDEV_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_STD) -c $< -o $@

# Stavba binárky programu "stddev" pro výpočet směrodatné odchylky
$(BUILD_DIR)/$(STDDEV_NAME): $(STDDEV_BUILD_DIR)/$(STDDEV_NAME).o \
                          $(STDDEV_BUILD_DIR)/$(EXECUTABLE)-$(STDDEV_NAME).o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_STD) $^ -o $@

# Stavba matematické knihovny s přepínači pro profilování pomocí gprof
$(STDDEV_BUILD_DIR)/$(EXECUTABLE)-$(STDDEV_NAME).o: $(CORE_DIR)/$(EXECUTABLE).cpp
	@mkdir -p $(STDDEV_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_STD) -c $< -o $@

# Stavba objektového souboru programu "stddev-profile" pro výpočet směrodatné odchylky
$(PROFILE_BUILD_DIR)/$(STDDEV_NAME)-profile.o: $(PROFILE_DIR)/$(STDDEV_NAME).cpp
	@mkdir -p $(PROFILE_BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) -c $< -o $@

# Stavba binárky programu "stddev-profile" pro výpočet směrodatné odchylky
$(BUILD_DIR)/$(STDDEV_NAME)-profile: $(PROFILE_BUILD_DIR)/$(STDDEV_NAME)-profile.o \
                          $(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(STDDEV_NAME)-profile.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PROF) $^ -o $@

# Stavba matematické knihovny s přepínači pro profilování pomocí gprof
$(PROFILE_BUILD_DIR)/$(EXECUTABLE)-$(STDDEV_NAME)-profile.o: $(CORE_DIR)/$(EXECUTABLE).cpp
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
	mkdir -p $(PACK_DIR)/$(PACK_REPO_DIR)
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
	if [ -f "../screenshot.png" ]; then \
		rsync -av --progress ../screenshot.png $(PACK_REPO_DIR)/; \
	else \
		echo "../screenshot.png does not exist"; \
	fi
	if [ -f "../dokumentace.pdf" ]; then \
		rsync -av --progress ../dokumentace.pdf $(PACK_REPO_DIR)/; \
	else \
		echo "../dokumentace.pdf does not exist"; \
	fi
	if [ -d "../mockup" ]; then \
		rsync -av --progress ../mockup $(PACK_REPO_DIR)/; \
	else \
		echo "../mockup does not exist"; \
	fi

### pack-doc: ## Vygeneruje dokumentaci pro účely odevzdání do složky pro odevzdání
pack-doc:
	mkdir -p $(PACK_DIR)/$(PACK_DOC_DIR)
	$(MAKE) $(SILENTOPT) doc
	cp -r $(DOC_OUT_DIR)/ $(PACK_DOC_DIR)/
	@$(MAKE) $(SILENTOPT) clean-doc

### pack-install: ## Zkopíruje instalátor do složky pro odevzdání
pack-install:
	mkdir -p $(PACK_DIR)/$(PACK_INSTALL_DIR)
	if [ -d "$(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR)" ]; then \
		rsync -av --progress $(INSTALL_MAIN_DIR)/$(DEB_RESRC_DIR) $(PACK_INSTALL_DIR)/; \
	else \
		echo "DEBIAN DEPENDENCIES DIR does not exist"; \
	fi
	if [ -f "$(INSTALL_MAIN_DIR)/$(CATCALC_NAME)_$(CATCALC_VERSION)_amd64.deb" ]; then \
		rsync -av --progress $(INSTALL_MAIN_DIR)/$(CATCALC_NAME)_$(CATCALC_VERSION)_amd64.deb $(PACK_INSTALL_DIR)/; \
	else \
		echo "Debian pack for CALM CATCALC does not exist"; \
	fi
	if [ -f "$(INSTALL_MAIN_DIR)/$(STDDEV_NAME)_$(STDDEV_VERSION)_amd64.deb" ]; then \
		rsync -av --progress $(INSTALL_MAIN_DIR)/$(STDDEV_NAME)_$(STDDEV_VERSION)_amd64.deb $(PACK_INSTALL_DIR)/; \
	else \
		echo "Debian pack for STDDEV does not exist"; \
	fi
