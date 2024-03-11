# 2. projekt IVS - Týmový projekt: Kalkulačka: PLÁN PROJEKTU

## Členové týmu

| **Jméno**             | **xlogin** | **GitHub** | **Speciální role** |
| --------------------- | ---------- | ---------- | ------------------ |
| **Farkašovský Lukáš** | xfarkal00  | NormREE    | \-----             |
| **Hýža Pavel**        | xhyzapa00  | RyzaGrey   | Zapisovatel        |
| **Kalina Jan**        | xkalinj00  | Honziksick | Vedoucí            |
| **Krejčí David**      | xkrejcd00  | DJmDavidus | \-----             |

## Smluvené prostředky

### Vývoj (obecně)

| **Prostředek**                     | **Domluveno v týmu**                                                                     |
| ---------------------------------- | ---------------------------------------------------------------------------------------- |
| **Programovací jazyk**             | C/C++<br> *(+ zatím nerozhodnutý jazyk pro tvorbu GUI)*                                  |
| **Platforma**                      | Ubuntu 22.04 – 64bit                                                                     |
| **Hosting Gitu**                   | [GitHub](https://github.com/)                                                            |
| **Vlastník vzdáleného repozitáře** | [Jan Kalina](https://github.com/Honziksick/ivs-project-2-team-calculator) *(Honziksick)* |
| **Licence**                        | GNU GPL v.3                                                                              |
| **IDE týmu**                       | Visual Studio Code *(Linux / WSL version)*                                               |
| **Nástroj pro dokumentaci**        | Doxygen                                                                                  |
| **Formát a jazyk README**          | README.md v jazyce Markdown                                                              |

### Týmový jazykový pakt

| **Prostředek**              | **Jazyk**             | **Detaily**                                                   |
| --------------------------- | --------------------- | ------------------------------------------------------------- |
| **Komentář**                | čeština s diakritikou | Doxygen struktura &<br>Velké množství pro navýšení porozumění |
| **Commit**                  | čeština s diakritikou | Struktura:  <br>&nbsp;&nbsp;&nbsp;&nbsp;STRUČNÝ NADPIS  <br>&nbsp;&nbsp;&nbsp;&nbsp;_volný řádek_  <br>&nbsp;&nbsp;&nbsp;&nbsp;DETAILNÍ POPIS |
| **Zdrojový kód**            | angličtina            | \-----                                                        |
| **Dokumentace _(veškerá)_** | čeština s diakritikou | nástroj Doxygen                                               |
| **README.md**               | čeština s diakritikou | jazyk Markdown                                                |

### Další týmové domluvy & Informace

- Pomocí **GitHub Projects** byl vytvořen projekt, kde je možné sledovat úkoly jednotlivým členům týmu a také termíny na splnění těchto úkolů
- GitHub **repozitář byl zpřístupněn uživateli ivskontrola**, který by měl mít plný přístup k repozitáři a projektu v GitHub Projects
- V našem repozitáři budeme používat **.gitignore**, abychom předešli zanášení repozitáře „smetím“ *(k nahlédnutí v repozitáři)*
  - **.gitignore** bude **průběžně aktualizován**
- Domluvili jsme se na využívání **.editorconfig**, abychom předešli případným problémům při tvorbě kódu *(k nahlédnutí v repozitáři)*
  - **Odsazování řádků, šířka tabulátoru, znaková sada apod.** je možné prohlédnout si přímo v repozitáři
- Rozhodli jsme se, že si v párech budeme **vzájemně ve dvojicích kontrolovat naše commity** pro minimalizaci počtu chyb v kódu či špatného pochopení specifikace
  - **Jan Kalina & Lukaš Farkašovský**
  - **Pavel Hýža & David Krejčí**
- Pro potřeby domlouvání termínů *(v případě shledání Discordu nepraktickým)* byly **zřízeny** [**Outlook kalendáře**](https://outlook.office365.com/owa/calendar/fa4632066acb448eb80d979369909afc@vutbr.cz/8ab049304cc54a94b42b7fb7d0e380204962968217407228467/calendar.html) – **osobní** a **souhrnný týmový** –, které lze jednoduše **propojit s Doodlem**
  - **odkaz na týmový kalendář:** *<https://outlook.office365.com/owa/calendar/fa4632066acb448eb80d979369909afc@vutbr.cz/8ab049304cc54a94b42b7fb7d0e380204962968217407228467/calendar.html>*
- Pokud nám to čas dovolí, rádi bychom se **seznámili s možností CI GitHubu** a automatizovaného testování a sestavování při provedení změn

## Rozdělení úkolů

### Celkový souhrn

| **Úkol**                                             | **Vykonavatel**       | **Termín**                                        |
| ---------------------------------------------------- | --------------------- | ------------------------------------------------- |
| **Tvorba a příprava<br> repozitáře a README**        | **Jan Kalina**        | nejpozději  <br>Čt **14\. března**, **7:00 ráno** |
| **Předběžný plán<br> projektu**                      | **Jan Kalina**        | nejpozději  <br>Čt **14\. března**, **7:00 ráno** |
| **Tvorba a údržba<br> Makefile**                     | **Jan Kalina**        | **Průběžně** **a aktivně** podle žádostí týmu     |
| **Testy pro matematickou<br> knihovnu formou TDD**   | **David Krejčí**      | nejpozději  <br>Ne **17. března** 2024            |
| **Matematická knihovna**                             | **David Krejčí**      | nejpozději  <br>Ne **24. března** 2024            |
| **GUI nad matematickou<br> knihovnou**               | **Lukáš Farkašovský** | nejpozději  <br>Ne **7. dubna** 2024              |
| **Implementace<br> směrodatné odchylky**             | **Jan Kalina**        | nejpozději  <br>Ne **7. dubna** 2024              |
| **Protokol z profileru**                             | **Jan Kalina**        | nejpozději  <br>Ne **14. dubna** 2024             |
| **Od/Instalátor**                                    | **Pavel Hýža**        | nejpozději  <br>Ne **14. dubna** 2024             |
| **Mockup**                                           | **Lukáš Farkašovský** | nejpozději  <br>Pá **14. dubna** 2024             |
| **Debugging _(povinný)_**                            | **David Krejčí**      | nejpozději  <br>Pá **19. dubna** 2024             |
| **Návod pro manuální<br> od/instalaci**              | **Pavel Hýža**        | nejpozději  <br>Pá **19. dubna** 2024             |
| **Programová<br> dokumentace**                       | **Každý** dokumentuje svoji<br> práci + následná tvorba<br> výsledné dokumentace<br> **Jan Kalina** | nejpozději  <br>Pá **19\. dubna** 2024 |
| **Uživatelská<br> dokumentace**                      | **Pavel Hýža**        | nejpozději  <br>Pá **19\. dubna** 2024            |
| **Soubory _odevzdani.txt_<br> & odevzdání projektu** | **Jan Kalina**        | Nejpozději  <br>St **24\. dubna**, **7:00 ráno**  |
| **Nasazení u zákazníka**                             | **všichni**           | **29\. dubna – 3. května**                        |
| **Soubor _hodnoceni.txt_<br> a _skutecnost.txt_**    | **všichni**           | nejpozději  <br>Čt **9\. května**, **7:00 ráno**  |
| **Prezentace<br> k obhajobám**                       | **všichni**           | nejpozději  <br>**1 den před obhajobou**          |
| **Obhajoby**                                         | **všichni**           | **6\. – 10. května**                              |

### Individuální rozdělení úkolů

#### Jan Kalina *(xkalinj00)*

| **Úkol**                                             | **Vykonavatel** | **Termín**                                        |
| ---------------------------------------------------- | --------------- | ------------------------------------------------- |
| **Tvorba a příprava<br> repozitáře a README**        | **Jan Kalina**  | nejpozději  <br>Čt **14\. března**, **7:00 ráno** |
| **Předběžný plán<br> projektu**                      | **Jan Kalina**  | nejpozději  <br>Čt **14\. března**, **7:00 ráno** |
| **Tvorba a údržba<br> Makefile**                     | **Jan Kalina**  | **Průběžně** **a aktivně** podle žádostí týmu     |
| **Implementace<br> směrodatné odchylky**             | **Jan Kalina**  | nejpozději  <br>Ne **7. dubna** 2024              |
| **Protokol z profileru**                             | **Jan Kalina**  | nejpozději  <br>Ne **14. dubna** 2024             |
| **Výsledná programová<br> dokumentace**              | **Jan Kalina**  | nejpozději  <br>Pá **19\. dubna** 2024            |
| **Soubor _odevzdani.txt_<br> & odevzdání projektu**  | **Jan Kalina**  | Nejpozději  <br>St **24\. dubna**, **7:00 ráno**  |

#### Lukáš Farkašovský *(xfarkal00)*

| **Úkol**                               | **Vykonavatel**       | **Termín**                            |
| -------------------------------------- | --------------------- | ------------------------------------- |
| **GUI nad matematickou<br> knihovnou** | **Lukáš Farkašovský** | nejpozději  <br>Ne **7. dubna** 2024  |
| **Mockup**                             | **Lukáš Farkašovský** | nejpozději  <br>Pá **14. dubna** 2024 |

#### Pavel Hýža *(xhyzapa00)*

| **Úkol**                                | **Vykonavatel** | **Termín**                             |
| --------------------------------------- | --------------- | -------------------------------------- |
| **Od/Instalátor**                       | **Pavel Hýža**  | nejpozději  <br>Ne **14. dubna** 2024  |
| **Návod pro manuální<br> od/instalaci** | **Pavel Hýža**  | nejpozději  <br>Pá **19. dubna** 2024  |
| **Uživatelská<br> dokumentace**         | **Pavel Hýža**  | nejpozději  <br>Pá **19\. dubna** 2024 |

#### David Krejčí *(xkrejcd00)*

| **Úkol**                                           | **Vykonavatel**  | **Termín**                             |
| -------------------------------------------------- | ---------------- | -------------------------------------- |
| **Testy pro matematickou<br> knihovnu formou TDD** | **David Krejčí** | nejpozději  <br>Ne **17. března** 2024 |
| **Matematická knihovna**                           | **David Krejčí** | nejpozději  <br>Ne **24. března** 2024 |
| **Debugging _(povinný)_**                          | **David Krejčí** | nejpozději  <br>Pá **19. dubna** 2024  |

#### Společné úkoly

| **Úkol**                                           | **Vykonavatel**                       | **Termín**                                           |
| -------------------------------------------------- | ------------------------------------- | ---------------------------------------------------- |
| **Programová<br> dokumentace**                     | **Každý** dokumentuje<br> svoji práci | **Průběžně** **a aktivně  <br>**po celou dobu vývoje |
| **Nasazení u zákazníka**                           | **všichni**                           | **29\. dubna – 3. května**                           |
| **Soubory _hodnoceni.txt_<br> a _skutecnost.txt_** | **všichni**                           | nejpozději  <br>Čt **9\. května**, **7:00 ráno**     |
| **Prezentace<br> k obhajobám**                     | **všichni**                           | nejpozději  <br>**1 den před obhajobou**             |
| **Obhajoby**                                       | **všichni**                           | **6\. – 10. května**                                 |

## Komunikace

### Obecná pravidla komunikace

- **Kontrolujeme Discord pravidelně**
  - Každý člen týmu by měl pravidelně *(alespoň dvakrát denně)* kontrolovat Discord. Každý z nás máme jiný denní režim, proto je v případě problému či dotazu reagovat, co nejdřív, ideálně ještě v daný den, aby vývoj nestagnoval a mohli jsme všichni pokračovat v přidělených úkolech v době, kdy se nám to hodí a pasuje do denního režimu.
- **Telefonní komunikace používáme jen v případě nouze**
  - Komunikace formou mobilního telefonu *(telefonát / SMS)* je vyhrazena pouze pro akutní případy, kdy je nutné jednat ihned. Jedná se o týmovou Emergency Hotline
- **E-mail není preferovanou formou komunikace**
  - E-mailová komunikace slouží pro případ, kdyby došlo k výpadku Discordu a bylo potřeba něco vyřešit / naplánovat. E-maily rozesíláme vše členům týmu ­– tedy do kopie e-mailu vkládáme e-mailové adresy všech členů.
- **Doodle**
  - V případě shledání plánování schůzek a online meetingů na Discordu nepraktickým, budeme termíny plánovat pomocí skupinové nástroje Doodle. Všem členům týmu byl vytvořen osobní kalendář a také souhrnný týmový kalendář k usnadnění plánování termínů
- **Komunikujme aktivně, diskutujme, podílejme se**
  - Každý člen týmu by měl pravidelně přispívat k diskusi a sdílet své nápady a připomínky. Aktivní komunikace je klíčem k úspěchu projektu.
- **Respektujme čas a plány ostatních**
  - Dodržujte stanovené termíny a respektujte čas ostatních členů týmu. Pokud máte nějaké změny v plánu, dejte včas vědět.
- **Buďme k sobě slušní**
  - Přestože nemusíme souhlasit s názory a způsoby řešení ostatních, nebuďme k sobě vulgární či útoční. Tým musí držet při sobě.
- **Zpětná vazba je vítána**
  - Buďte otevření k zpětné vazbě a konstruktivní kritice. Pouze tak můžeme růst a zdokonalovat se jako tým. Nikdo z nás není neomylný a každý můžeme problém vidět trošku z jiného úhlu pohledu, proto je důležité, abychom v případě konfliktu předložil svůj úhel pohledu a své argumenty. Všechny názory mají stejnou váhu.
- **Respektujme pravidla jednotlivých kanálu**
  - Pokusme se dodržovat strukturu fóra a informačního kanálu a také určení jednotlivých kanálů. Ušetříme tak čas při hledání některých odpovědí a snížíme tak možnost opomenutí termínu či problému k vyřešení.
- **Dokumentace a sdílení informací**
  - Důležité informace a rozhodnutí týmu by měly být zdokumentovány a sdíleny v příslušných kanálech. To zajišťuje transparentnost a umožňuje snadnější přístup k potřebným informacím.

### Kontaktní informace na členy týmu

| **Jméno**             | **xlogin** | **Discord** | **Telefon** | **E-mail**                    |
| --------------------- | ---------- | ----------- | ----------- | ----------------------------- |
| **Farkašovský Lukáš** | xfarkal00  | normree     | 799 531 933 | <xfarkal00@stud.fit.vutbr.cz> |
| **Hýža Pavel**        | xhyzapa00  | ryzagrey    | 702 335 100 | <xhyzapa00@stud.fit.vutbr.cz> |
| **Kalina Jan**        | xkalinj00  | honziksick  | 776 736 555 | <xkalinj00@stud.fit.vutbr.cz> |
| **Krejčí David**      | xkrejcd00  | djmdavidus  | 702 484 271 | <xkrejcd00@stud.fit.vutbr.cz> |

### Podrobná pravidla pro týmový Discord

#### Kanály

- team-rules
- general
- info
- session-planning
- forum
- voting

#### Pravidla komunikace pro jednotlivé kanály

- **Team Rules**
  - V tomto kanálu jsou základní pravidla a očekávání týmu. Zahrnují například dodržování termínů, podílení se na projektu a pravidla komunikace.
- **General**
  - Tento kanál slouží pro každodenní komunikaci a sdílení neformálních informací. Tento kanál je určen zkrátka k čemukoliv, co projektu vůbec netýká, nebo si nezaslouží být v ostatních kanálech. Těším se na naše SegFaulty a Code Rage xD.
- **Leader’s Info**
  - V kanálu Leader‘s Info najdete důležité oznámení, aktualizace a informace týkající se projektu. Pokud by bylo potřeba reagovat na některé oznámení, reagujte prosím formou vlákna, ať v popředí kanálu skutečně zůstávají viditelná pouze oznámení.
- **Session Planning**
  - Kanál pro plánování setkání, diskusí a práce na projektu.
- **Forum**
  - V tomto kanálu probíhají hlubší diskuse, řešení problémů, brainstorming a sdílení dlouhodobých nápadů a plánů týkajících se projektu. Je to místo pro kreativitu a rozvoj myšlenek. Základním pravidle pro tento kanál, je udržovat ho ve formátu fóra: nejdříve odešlete zprávu, která obsahuje pouze nadpis fóra a následně do vlákna tohoto příspěvku zahajte diskuzi.
- **Voting**
  - Tento kanál slouží k pořádání veřejných hlasování. Jelikož jsme 4členný tým, tak může jednoduše dojít ke konfliktu. V případě nerozhodného hlasování vyhrává varianta, pro kterou hlasoval člověk, jehož úkolu se hlasovaný problém bezprostředně týká. V případě, že ani toto by konflikt v hlasování nevyřešilo, vyhrává varianta, pro kterou hlasoval vůdce týmu.

<br>

---

*Datum poslední úpravy: 11. 3. 2024, 23:42*