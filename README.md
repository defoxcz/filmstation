# FilmStation

The Film Production Workstation. Samostatná desktopová aplikace C++17 / Qt 6 Widgets pro mezinárodní plánování filmové produkce.

## Stav

Verze 0.1.0 je spustitelný architektonický základ. Obsahuje strom modulů vlevo, MDI workspace uprostřed a property grid vpravo. Dvojklik otevře pohled; opakované otevření aktivuje existující okno. Nabídka Window nabízí dlaždice, kaskádu a zavření pohledu. Výběr ve stromu a aktivace MDI aktualizují vlastnosti.

Registrovány jsou Scripts (literární a technické scénáře), Cast & Characters, Crew, Locations, Scheduling (kalendář a plán), Budgeting, Production Resources a Reports. Obsahové editory jsou zatím výslovně označené jako připravované. Projekt zatím neukládá produkční data, nepočítá rozpočty a nenačítá externí pluginy.

UI používá anglické zdrojové texty a Qt překladové body; překladové katalogy zatím nejsou dodané.

## Sestavení

Vyžaduje CMake 3.24+, Ninja, C++17 a Qt 6.8+ (Widgets a pro testy Test). Qt nastavte přes CMAKE_PREFIX_PATH; lokální absolutní cesty nepatří do verzovaných presetů.

```sh
cmake --preset debug -DCMAKE_PREFIX_PATH=/path/to/Qt/platform
cmake --build --preset debug
ctest --preset debug
```

macOS aplikace: `build/debug/FilmStation.app`. Spuštění: `open build/debug/FilmStation.app`.

Viz [architektura](docs/architecture.md). Build a testy byly ověřeny na macOS Apple Silicon s Qt 6.11.2. Windows a Linux zatím neověřeny.

## Spuštění přes F5 ve VS Code (macOS)

Otevřete složku FilmStation a zvolte **FilmStation: macOS Debug** v Run and Debug. F5 nejdřív nakonfiguruje a sestaví Debug, potom spustí aplikaci přes CodeLLDB. Při chybě sestavení se ladění přeruší. Cmd+Shift+B spustí stejné sestavení. CodeLLDB a CMake Tools jsou na tomto počítači nainstalované.

Lokální Qt a Ninja jsou nastavené v ignorovaném `CMakeUserPresets.json` (preset `macos-debug-local`). Na jiném počítači vytvořte odpovídající lokální preset; macOS úlohy očekávají CMake z instalace `~/Qt/Tools/CMake/CMake.app`. Tato F5 konfigurace je pro macOS; Windows a Linux vyžadují vlastní cestu ke spustitelnému souboru a nástrojům.

## Rozsah základní sestavy

Cílové moduly, výzkum Movie Magic / StudioBinder / Celtx / Fuzzlecheck / Gorilla a návrh Python automatizace jsou v [návrhu produkční sestavy](docs/production-suite-research.md). Jde o plán rozvoje, nikoli již implementované editory.
