# 2. projekt IVS - Týmový projekt: Kalkulačka: PLÁN PROJEKTU

## Členové týmu

| **Jméno** | **xlogin** | **Přezdívka** | **Speciální role** |
| --- | --- | --- | --- |
| **Farkašovský Lukáš** | xfarkal00 | norm | \----- |
| **Hýža Pavel** | xhyzapa00 |     | Zapisovatel |
| **Kalina Jan** | xkalinj00 | Honziksick | Vedoucí |
| **Krejčí David** | xkrejcd00 | DJmDavidus | \----- |

## Smluvené prostředky

### Vývoj (obecně)

| **Prostředek** | **Domluveno v týmu** |
| --- | --- |
| **Programovací jazyk** | C/C++<br><br>_(+ zatím nerozhodnutý jazyk pro tvorbu GUI)_ |
| **Platforma** | Ubuntu 22.04 – 64bit |
| **Hosting Gitu** | GitHub |
| **Licence** | GNU GPL v.3 |
| **IDE týmu** | Visual Studio Code _(Linux / WSL version)_ |
| **Nástroj pro dokumentaci** | Doxygen |
| **Formát a jazyk README** | README.md v jazyce Markdown |

### Týmový jazykový pakt

| **Prostředek** | **Jazyk** | **Detaily** |
| --- | --- | --- |
| **Komentář** | čeština s diakritikou | Doxygen struktura &<br>Velké množství pro navýšení porozumění |
| **Commit** | čeština s diakritikou | Struktura:  <br>&nbsp;&nbsp;&nbsp;&nbsp;STRUČNÝ NADPIS  <br>&nbsp;&nbsp;&nbsp;&nbsp;_volný řádek_  <br>&nbsp;&nbsp;&nbsp;&nbsp;DETAILNÍ POPIS |
| **Zdrojový kód** | angličtina | \----- |
| **Dokumentace _(veškerá)_** | čeština s diakritikou | nástroj Doxygen |
| **README.md** | čeština s diakritikou | jazyk Markdown |

## Další týmové domluvy

- V našem repozitáři budeme používat **.gitignore**, abychom předešli zanášení repozitářem nepotřebným a objemným smetím _(k nahlédnutí ve vzdáleném repozitáři)_
- Domluvili jsme se na využívání **.editorconfig**, abychom předešli případným problémům při tvorbě kódu _(k nahlédnutí ve vzdáleném repozitáři)_
- Rozhodli jsme se, že si v párech budeme **vzájemně ve dvojicích kontrolovat naše commity** pro minimalizaci počtu chyb v kódu či špatného pochopení specifikace
  - **Jan Kalina & Lukač Farkašovský**
  - **Pavel Hýža & David Krejčí**
- Pro potřeby domlouvání termínů _(v případě shledání Discordu nepraktickým)_ byly **zřízeny Outlook kalendáře** – **osobní** a **souhrnný týmový** –, které lze jednoduše **propojit s Doodlem**
- Pokud nám to čas dovolí, rádi bychom se **seznámili s možností CI GitHubu** a automatizovaného testování a sestavování při provedení změn

## Rozdělení úkolů

| **Úkol** | **Vykonavatel** | **Termín** |
| --- | --- | --- |
| **Předběžný plán** | Jan Kalina | nejpozději  <br>Čt 14. března, 7:00 ráno |
| **Makefile** |     |     |
| **Matematická knihovna formou TDD** |     |     |
| **GUI nad matematickou knihovnou** |     |     |
| **Debugging _(povinný)_** |     |     |
| **Profilling a protokol z profilleru** |     |     |
| **Od/Instalátor** |     |     |
| **Mockup** | všichni |     |
| **Programová dokumentace** | všichni + následné sjednocení TBD |     |
| **Uživatelská dokumentace** |     |     |
| **Návod pro manuální od/instalaci** |     |     |
| **Odevzdání projektu** | Jan Kalina | Nejpozději  <br>St 24. dubna, 7:00 ráno |
| **Nasazení u zákazníka** | všichni | 29\. dubna – 3. května |
| **Soubory hodnoceni.txt a skutečnost.txt** | všichni | nejpozději  <br>Čt 9. května, 7:00 ráno |
| **Prezentace k obhajobám** | TBD | nejpozději  <br>1 den před obhajobou |
| **Obhajoby** | všichni | 6\. – 10. května |

## Komunikace – Discord

### Kanály

- team-rules
- general
- info
- session-planning
- forum
- voting

### Pravidla komunikace

#### Pravidla pro jednotlivé kanály

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

#### Obecná pravidla komunikace

- **Kontrolujeme Discord pravidelně**
  - Každý člen týmu by měl pravidelně (alespoň dvakrát denně) kontrolovat Discord. Každý z nás máme jiný denní režim, proto je v případě problému či dotazu reagovat, co nejdřív, ideálně ještě v daný den, aby vývoj nestagnoval a mohli jsme všichni pokračovat v přidělených úkolech v době, kdy se nám to hodí a pasuje do denního režimu.
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