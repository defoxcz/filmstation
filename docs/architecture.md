# Architektura FilmStation

## Inspirace Vestigií

Read-only prostudovány `core/modules/imodule.h`, `moduleregistry.h/.cpp`, hlavní okno a kapitola `docs/technical-manual/09-architecture.md` desktopové Vestigie. Převzat je princip rozdělení jádra, modulů a pracovního prostředí; žádné produkční databáze ani přihlašovací mechanismy se nekopírují.

## Současná implementace

- `core/IModule`: stabilní ID modulu, přeložitelný název, definice pohledů a jejich factory. Modul není datová entita.
- `ModuleRegistry`: vlastní moduly, odmítá chybějící/duplicitní identifikátory, před vložením kontroluje všechny pohledy. ID pohledu je jedinečné uvnitř modulu.
- `modules/builtinmodules.cpp`: vestavěné definice osmi oblastí. MainWindow neobsahuje seznam odborných modulů.
- `ui/MainWindow`: Qt docky Project a Properties a centrální QMdiArea. Identita pohledu je dvojice moduleId/viewId, nikoli zobrazovaný název. Registry žije déle než okna a jejich widgety.
- Property grid nyní ukazuje metadata vybraného modulu/pohledu pouze pro čtení. Společný výběr doménových objektů přibude s prvními editory.

Jde o základ rozšiřitelnosti, nikoli veřejné binární SDK. Externí plugin loader, verzování API, závislosti modulů a bezpečné uvolnění knihoven zatím nejsou implementované. Současné IModule spojuje definici s UI factory; před binárním SDK je třeba vymezit stabilní kontrakt a případně oddělit doménový provider od Qt Widgets adaptéru. Stejnou hranici mezi existujícím modulem a budoucím pluginem rozlišuje Vestigia.

## Další implementace

1. Společný ProjectDocument, identity a reference mezi scénami, postavami, herci, lokacemi a natáčecími dny.
2. Příkazová vrstva s validací, undo/redo, společný selection context a schémata atributů pro property grid.
3. Verzionované úložiště a izolované testovací projekty; explicitní migrace a atomické ukládání. Rozpočty musí definovat měny, přesnost, zaokrouhlení, sazby a daňová pravidla před implementací výpočtů.
4. Funkční scénáře a obsazení, návazně plánování a rozpočty; reporty nad společnými daty.
5. Plugin manifest, verze API a závislosti. Dynamický loader až s testovanou správou životnosti a definovanou politikou důvěry.

Formáty FilmStation jsou samostatné; žádná kompatibilita s `.vestigia` není deklarována. MVP nevyužívá uživatelská data ani služby Vestigie.

## Cílové členění základní instalace

Navazuje [výzkum a rozhodnutí o produkční sestavě](production-suite-research.md) z 6. listopadu 2026. Rozlišuje technické jádro, vestavěné odborné moduly a volitelná rozšíření. Actors a Characters mají vlastní navigační oddíly, sdílejí obsazení a evidenci osob s Crew. Kalendáře používají společný časový model. Nově plánované oddíly zahrnují Breakdown, Call Sheets, Documents & Media, Tasks a Automation. Python má běžet v samostatném workeru přes verzované příkazové API. Registr a runtime těmto cílům zatím plně neodpovídají; dokument neprohlašuje funkce za implementované.
