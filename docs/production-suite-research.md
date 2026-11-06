# Základní sestava FilmStation a výzkum produkčních aplikací

Datum: 6. listopadu 2026. Výstup: rozhodnutí o hranicích modulů a doporučený rozsah, nikoli implementované funkce. Zkoumány veřejné oficiální stránky a manuály; neproběhlo praktické testování konkurenčních aplikací ani ověření jejich proprietárních formátů. Funkce se mohou lišit podle edice. Současná aplikace zůstává architektonickým prototypem s osmi registrovanými oblastmi.

## Rozhodnutí o jádru a základní instalaci

„Součást jádra“ zde rozlišujeme na technické jádro a moduly dodávané v základní instalaci. Doménové editory zůstávají moduly, i když je uživatel nemusí doinstalovávat. Základní sestava nebude závislá na stahování externích pluginů. Nejde o rozhodnutí o placených edicích.

Technické jádro poskytne projektový dokument a verzované úložiště, UUID a typované reference, transakční příkazy a undo/redo, registr schémat a validací, společný výběr, vyhledávání, média/přílohy, registr sestav a importních/exportních providerů. Pracovní shell vlastní MDI, strom a property grid. Sdílené služby budou evidence osob a organizací, čas/rezervace zdrojů, jednotky a peněžní hodnoty. Python Automation bude společná služba s vlastním pracovním oddílem.

Odborné významy zůstávají modulům: jádro nezná například dramaturgický popis postavy ani členění rozpočtových účtů. Sdílené kontrakty nesmějí vyžadovat přímé C++ odkazy mezi editory.

## Moduly základní instalace

| Oddíl v projektu | Odpovědnost a doporučené pohledy | Rozhraní vůči ostatním |
| --- | --- | --- |
| Production / Produkce | Film/seriál, epizody, fáze, produkční jednotky, výchozí měna a časová zóna | Kořen produkčního kontextu; nastavení, nikoli kopie projektu |
| Actors / Herci | Evidence herců, kontakty/agentury, casting, dostupnost, zkoušky | Herecký profil odkazuje na společnou osobu |
| Characters / Postavy | Postavy, popisy, výskyty ve scénách, obsazení, alternace | Samostatná fiktivní identita; herec není postava |
| Crew / Štáb | Osoby, profese, oddělení, angažmá, vedoucí a dostupnost | Stejná osoba může být herec i člen štábu; anglický název Crew |
| Calendars / Kalendáře | Denní/týdenní/měsíční pohled, dostupnost, zkoušky, fittingy, cesty a svátky | Sdílené události a rezervace; kalendář je pohled, ne další kopie plánu |
| Scripts / Scénáře | Literární scénáře a revize; technické scénáře, záběry a vazby na scény | Jeden registr scén a stabilních identit napříč revizemi |
| Breakdown / Rozpis scénáře | Požadavky scény: postavy, komparz, lokace, rekvizity, kostýmy, technika, vozidla, zvířata, kaskadéři, SFX/VFX | Množství, jednotky a odkazy do katalogů; žádné duplikované katalogové položky |
| Scheduling / Natáčecí plán | Stripboard, natáčecí dny, přesuny, přestávky, délky, varianty plánu, jednotky a epizody | Čerpá požadavky scén a vytváří rezervace; konflikty přes společnou službu |
| Locations & Sets / Lokace a dekorace | Reálné adresy/prostory, obhlídky, mapové body, dostupnost, podmínky a dokumenty | Dějové místo ve scénáři se mapuje na reálnou lokaci/dekoraci |
| Production Resources / Prostředky | Technika, rekvizity, kostýmy, masky, vozidla, zvířata, služby, dodavatelé | Kategorie a vlastní atributy; oddělit požadavek, fyzickou položku a rezervaci |
| Budgeting / Rozpočet | Struktura účtů, detailní kalkulace, sazby, měny, varianty a souhrny | Výslovné vazby na množství a dny; publikovaná verze se nesmí tiše přepsat změnou plánu |
| Call Sheets / Denní dispozice | Denní plán, individuální nástupy, kontakty, lokace, doprava, poznámky a verze k vydání | Vlastní editovatelný dokument odvozený z vybraného plánu; publikovaný snapshot |
| Reports / Sestavy | One-line, shooting schedule, breakdown sheets, DOOD, seznamy oddělení a finanční přehledy | Výstupní engine je společný; obsah poskytují moduly |
| Documents & Media / Dokumenty a média | Přílohy, fotografie, odkazy, verze a projektové dokumenty | Sdílené úložiště s explicitním životním cyklem souborů |
| Tasks / Úkoly | Odpovědnost, termíny, checklisty a vazby na scénu/den/lokaci | Úkol není rezervace osoby a není automaticky natáčecí den |
| Automation / Automatizace | Python skripty, parametry, spuštění, log, výsledek a historie | Volá verzované aplikační API, ne databázi ani widgety |

Oddíl nemusí odpovídat samostatné binární knihovně. Actors a Characters mohou zpočátku sdílet implementační balíček Cast, ale budou samostatnými navigačními oblastmi. Scénáře mají dva pododdíly požadované uživatelem; záběry/storyboard patří do technického scénáře, případný bohatší storyboard editor může přijít jako rozšíření. Lokace a prostředky jsou samostatné moduly. Požadavky pro bezpečnost, nezletilé, kaskadéry a efekty lze evidovat už v rozpise; plné specializované agendy přijdou později.

## Co ukázaly zavedené aplikace

| Produkt / primární zdroj | Doložené schopnosti | Dopad na návrh FilmStation |
| --- | --- | --- |
| [Movie Magic Scheduling](https://www.ep.com/movie-magic-scheduling/) | Více epizod/jednotek, konflikty mezi plány, kalendář dalších produkčních událostí, DOOD a přenos elementů do Budgeting | Jednotky a epizody patří do modelu od začátku; dostupnost se musí vyhodnocovat napříč jednotkami |
| [MMS Board manual](https://mms-docs.ep.com/Board/Board.html) | Stripy jsou rozpisy scén; více boards/sub-boards a prostor pro nezařazené scény | Uchovávat scénu odděleně od jejího zařazení do varianty plánu; návrhy nesmějí navzájem rezervovat stejné zdroje jako schválené závazky |
| [MMS FAQ](https://www.ep.com/support/movie-magic-scheduling/) | Import FDX a scheduling exportu SEX; rozdíl mezi nedostupností a dvojí rezervací | Rozlišovat příčiny konfliktů a jejich závažnost; formáty před implementací ověřit vlastními testovacími soubory |
| [Movie Magic Budgeting manual](https://mmb-docs.ep.com/ApplyTools/Apply_Tools_Overview.html), [Globals](https://mmb-docs.ep.com/Setup/globals.html) | Fringes, měny, jednotky, skupiny, poplatky a globální výpočtové parametry | Budgeting potřebuje parametrickou kalkulaci, nejen tabulku částek |
| [StudioBinder](https://www.studiobinder.com/) | Scénáře/revize, tagging, stripboard, script sides, storyboard/shot list, úkoly, kontakty/média a distribuce dispozic s potvrzeními | Pamatovat na úkoly, vizuální plánování a životní cyklus vydané dispozice |
| [Celtx Breakdown](https://support.celtx.com/hc/en-us/articles/216581678-Breakdown), [Budget](https://www.celtx.com/product/production/budget/) | Rozpis tvoří katalogové položky a propojuje je s další přípravou včetně nákladů | Breakdown je samostatný klíčový pracovní oddíl a datový most |
| [Fuzzlecheck](https://www.fuzzlecheck.com/) | Dostupnost, komparz, délky natáčení, odpočinek, slunce, více jednotek, exporty a online práva | Vedle obsazenosti evidovat pracovní čas a čas pro přesuny/přípravu; pravidla nastavovat podle produkce |
| [Jungle Software / Gorilla](https://junglesoftware.com/) | Propojené psaní, breakdown, plán, rozpočty, sazby a vizuální plánování | Celá cesta od scény po kalkulaci má využívat stejné identity |

Poslední sloupec jsou naše návrhové závěry, nikoli tvrzení o vnitřní architektuře konkurence. AI nástroje některých produktů nejsou důvodem podmiňovat základní funkce AI nebo internetem.

## Nezbytné průřezové schopnosti

- Revize: stabilní ID scény nezávislé na jejím čísle, uzamčené číslování, vložené/vynechané scény, historie a porovnání revizí; přenos breakdown tagů musí hlásit nejednoznačná místa.
- Plán: scény přes více dnů, rozdělené části, více jednotek, epizody i jednorázový film; nezařazené scény, návrhy a schválená varianta. Pracovní čas není čas příběhu a délka textu není automaticky doba natáčení. Podporovat zlomky stran (např. osminy) a odhady minut jako různé veličiny.
- Konflikty: nedostupnost, dvojí rezervace, nedostatečný přesun, příprava a odpočinek. Každé varování má příčinu a dotčené objekty; ruční výjimka je odůvodněná a dohledatelná. Zákonné/smluvní podmínky se dodávají jako explicitně zvolené a verzované sady pravidel, ne univerzální konstanty.
- Kalendáře: časová zóna lokace/události, letní čas, přesah přes půlnoc, celodenní události, opakování, dostupnost versus potvrzená rezervace. Celo-denní datum se nesmí při převodu zóny posunout.
- DOOD (Day Out of Days): matice dnů a využití osoby/prostředku, práce, hold, cestování, zkoušky a fittingy; legenda stavů a pravidla musí být výslovná.
- Dokumenty: tisk/PDF, přenositelné šablony, vícestránkové tabulky, verzované vydání, script sides (výběr scén pro daný den/osobu). Zobrazení a vydaný dokument musí používat tutéž vybranou revizi.
- Přenosy: prioritně FDX/Fountain pro scénáře, CSV pro strukturovaná data, PDF a XLSX pro sestavy, ICS pro kalendáře. Jde o cíle k implementaci a ověření; žádný formát není nyní podporován. Import PDF vyžaduje kontrolu rozpoznané struktury, sken potřebuje další OCR krok. ICS export neznamená obousměrnou synchronizaci. Nepřislíbit čtení MMS/MMB bez formálního a technického posouzení.
- Offline projekt, atomické ukládání, zálohy, obnova, přenositelné přílohy, vyhledávání, vlastní pole, lokalizace a regionální formáty. Oprávnění a sdílení kontaktních či finančních údajů navrhnout před týmovou synchronizací.

## Rozpočet: doporučené pododdíly

1. **Top Sheet**: přehled kategorií, mezisoučty, celkem, rezerva a zvolená varianta.
2. **Accounts & Details**: hierarchie účtů/podúčtů, řádky množství × sazba × doba/jednotka, poznámky a zdroj odhadu.
3. **Rates & Globals**: sazebníky a pojmenované parametry (např. počet natáčecích dnů), jejich platnost, vzorce a detekce cyklů.
4. **Fringes, Charges & Taxes**: oddělené modely souvisejících odvodů, příplatků/poplatků a daní, základy a limity; konkrétní pravidla se musí ověřit pro danou zemi a smlouvu.
5. **Currencies**: původní a základní měna, verzovaný kurz, datum a způsob zaokrouhlení. Historický rozpočet se nesmí měnit podle dnešního kurzu.
6. **Versions & Comparisons**: pracovní varianty, schválený základ, porovnání rozdílů a přenos položek s dohledatelným původem.
7. **Schedule Links**: zdroj množství z plánu, náhled změny nákladů, ruční override a výslovné převzetí nové hodnoty.
8. **Cost Tracking** (navazující etapa): objednané/zavázané částky, skutečnost, zbývající odhad, výhled a odchylka. Součty nesmějí započítat fakturu zároveň jako závazek i skutečnost.
9. **Cash Flow & Financing** (později): časové rozložení plateb, zdroje financování a výhled cash flow; oddělené od samotné kalkulace nákladů.

Výchozí šablona kategorií: vývoj a práva; producenti/režie/scénář; herci a komparz; štáb podle oddělení; lokace/studia/dekorace; rekvizity/kostýmy/masky; kamera/světla/grip/zvuk; doprava/ubytování/catering; kaskadéři/SFX/VFX; postprodukce/hudba/zvuk; pojištění/povolení/právní služby; dodávky a rezerva. Členění má být upravitelné podle země a produkce, nikoli vydávané za univerzální účetní standard.

Peníze musí používat přesnou reprezentaci a deklarované zaokrouhlení; ne běžný binární float. Budgeting není automaticky mzdový ani účetní systém. Tyto integrace jsou samostatná rozšíření.

## Python: architektonické rozhodnutí

Python je první skriptovací jazyk, nikoli alternativní datový model. Přidá se verzované API `filmstation` pro čtení projektového snapshotu a předkládání validovaných příkazů. Stejné příkazy musí používat UI i skripty.

Pro první implementaci doporučujeme **samostatný Python worker proces řízený z Qt přes QProcess**, nikoli zpřístupnění libovolných QObjectů a embedded interpreter v GUI vlákně. Jde o naše rozhodnutí; [QProcess](https://doc.qt.io/qt-6/qprocess.html) poskytuje spouštění a komunikaci s procesem. Skriptovací pracovní prostor nabídne editor, parametry, stdout/stderr, průběh, zrušení a výsledek. První verze může začít souborem a konzolí bez debuggeru.

- Komunikace přes verzovaný JSON-RPC protokol včetně ID požadavku, verze projektu/snapshotu, limitu velikosti zpráv a strukturovaných chyb. Vyhrazený protokolový kanál se nesmí míchat s uživatelským print.
- Čtení přes snapshot a dotazy; zápis přes příkazovou dávku ověřenou jádrem. Aplikace odmítne zastaralou revizi, neplatné reference i nepovolené operace. Úspěšná dávka tvoří jednu undo operaci; při chybě se nepublikuje její část.
- Skripty nemají přímý zápis do SQLite ani živých widgetů. API nepřijímá serializované spustitelné objekty/pickle. Dlouhý výpočet nesmí blokovat UI.
- Timeout, cancel, konec workeru a omezený objem logu; při pádu workeru zůstává projekt platný. Procesová izolace chrání stabilitu, **není bezpečnostní sandbox**. Běžný Python má práva svého OS uživatele; skutečné omezení souborů/sítě vyžaduje platformní sandbox nebo jiný mechanismus.
- Skripty vložené do otevřeného projektu se samy nespouštějí. Důvěra, požadované schopnosti a spouštěcí hooky jsou explicitní. Instalace Python balíčků není automatický vedlejší efekt otevření projektu.
- Nejprve výslovně nakonfigurovaný podporovaný interpreter a izolované závislosti; pro distribuci rozhodnout o dodávaném runtime, licencích a aktualizacích na všech platformách. Zatím neurčujeme minimální Python verzi bez ověření balení.
- Peněžní API přenáší desetinné řetězce s měnou a pravidlem zaokrouhlení; Python může využít [decimal](https://docs.python.org/3/library/decimal.html). Vlastní výpočet skriptu nenahrazuje autoritativní validaci jádra.

Příklady první automatizace: kontrola chybějících lokací/obsazení, export seznamu rekvizit pro vybrané dny, vlastní sestava, import firemního CSV, výpočet návrhu varianty plánu nebo hromadné úpravy s náhledem. Automatický optimalizátor plánu má nejprve vytvářet návrh, ne tiše přepisovat schválené rezervace.

## Další pluginy a etapy

**Základ první funkční verze:** projekt/identity/persistence/příkazy, Actors, Characters, Crew, literární a technické scénáře, breakdown, lokace, prostředky, kalendáře, ruční stripboard, základní rozpočet, PDF dispozice a sestavy. Python API navrhovat současně s příkazy; první read-only worker a pak vratné zápisy. Základní instalace může obsahovat všechny výše uvedené oddíly, jejich úplná funkcionalita vznikne postupně.

**Profesní rozšíření:** pokročilé revize, komparz a skupinové počty, multi-unit/multi-episode workflow, DOOD, pravidla času/odpočinku, srovnání rozpočtů a nákladová kontrola; bohatší storyboard/continuity editor.

**Volitelné pluginy:** cestování/ubytování/catering, smlouvy a povolení, bezpečnost/risk register, evidence záběrů a script supervision při natáčení, postprodukční plán a dodávky, účetnictví/mzdy, mapy/počasí/sluneční údaje, distribuční e-mail/SMS a potvrzení dispozic, cloudová spolupráce se schvalováním a auditní stopou, specializované národní sazebníky a optimalizace/AI. Základní data a otevření lokálního projektu nesmějí vyžadovat tyto služby.

Každý budoucí plugin má deklarovat ID, verzi API, závislosti, schémata, migrace, providery pohledů/příkazů/sestav a požadované schopnosti. Chybějící plugin nesmí způsobit ztrátu jeho dat při otevření a opětovném uložení. Při neznámém schématu je nutné zachovat neprůhledný payload a případně omezit editaci. Závislosti kontrolovat před aktivací; hot-unload není pro první verzi požadován.

## Dopad na existující prototyp

Současný Cast poskytuje pohledy Actors/Characters, Calendar je pod Scheduling a rozpis ani Automation zatím nejsou registrovány. Tento dokument stanoví cílové členění; není důvod nyní vydávat další prázdné editory za implementaci. Před další funkční prací doplnit schémata identit, referencí, kalendářů a příkazů; potom upravit navigaci a registraci podle tohoto návrhu. Žádné cizí produkční formáty ani služby nebyly změněny.
