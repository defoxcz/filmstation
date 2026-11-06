# FilmStation

- Komunikuj česky; zdrojové UI texty anglicky přes Qt překladové funkce.
- Před změnami čti README.md a docs/architecture.md.
- Samostatný C++17/Qt Widgets projekt; zachovej přenositelnost macOS, Windows a Linux. Ověření uváděj pro skutečně testované platformy.
- Doménové moduly registruj přes IModule a ModuleRegistry, ne podmínkami v MainWindow. Zachovej vlevo projekt, vpravo vlastnosti a uprostřed MDI.
- Nepracuj s uživatelskými daty Vestigie; žádné přebírání tokenů, klíčů ani produkčních databází.
- Testy používej s izolovanými daty; ověření: cmake --build --preset debug a ctest --preset debug.
- Buildy, lokální SDK cesty a tajné údaje nepatří do Gitu. Commit/push jen na výslovný pokyn pro tento projekt; nepoužívej remote jiného projektu.
