Problem N ciał - Karol Gajek 439438

Wersja 1.0.0

Program symuluje oddziaływanie grawitacyjne N ciał na płaszczyźnie, z uwzględnieniem kolizji niesprężystych.

1. Kompilacja

Program był pisany i kompilowany w środowisku Windows przy pomocy CMake oraz Visual Studio Code z zainstalowanym dodatkiem CMake Tools.
Konfiguracji CMake dokonano automatycznie przy pomocy Visual Studio.
Można dokonać jej manualnie, plik CMakeLists.txt znajduje się w folderze ImGui_ImPlot_for_students-master,
choć samemu nie jestem na tyle obeznany by wskazać jakie powinno być polecenie konfigurujące.
Sposób konfiguracji na moim urządzeniu, który udało mi się z sukcesem zreplikować w innych lokalizacjach, to:
1. otworzenie folderu w VScode
2. shift+ctrl+p -> CMake: Configure
3. Jak pojawi się błąd, to zamknąć VScode i otworzyć folder w Vscode ponownie
4. Nacisnąć przycisk build na pasku rozszerzeń VScode

By skompilować program, można użyć albo przycisku build z Visual Studio, albo z terminala w folderze build wykonać polecenie:
    cmake --build .
Program o nazwie 'Project' powinien zostać wygenerowany w folderze build.

2. Korzystanie z programu

Uruchomiony program będzie oczekiwał na podanie dwóch liczb naturalnych:
1. (n) liczba ciał, które mają zostać wygenerowane
2. (k) liczba ciał, którym będzie zapisywana i wyświetlana trajektoria (k <= n)
Po wprowadzeniu danych, program wyświetli wszystkie wygenerowane ciała oraz symulację na żywo w ImPlocie.

Program nie bada poprawności wprowadzenia danych.


3. Modyfikacja wartości stałych

W folderze ImGui_ImPlot_for_students-master znajduje się plik 'constants.h'.
W tym pliku znajdują się stałe wykorzystywane w programie, które można zmodyfikować.
Wielkości są nazwane w sposób intuicyjny i zostały dodatkowo opisane komentarzem.
Wpisane wielkości domyślne pozwalają zaobserwować poprawne działanie programu w rozsądnym czasie.

Program nie jest odporny na wprowadzenie niepoprawnych stałych
(np. minimalny promień większy od maksymalnego, ujemna masa, krok czasowy mniejszy od epsilon itp.)
Wszelkie niepoprawne działanie w takim wypadku będzie winą użytkownika.

4. Komentarze
Program był pisany w sposób, by komentarze nie były konieczne. To jest, nazwy klas, funkcji i zmiennych
powinny intuicyjnie wyjaśniać za co są one odpowiedzialne.
Są one jednak po angielsku - jeśli stanowiłoby to problem, dodam do kodu źródłowego odpowiednie polskie komentarze.


Do implementacji ImPlot wykorzystano następujące źródło: https://github.com/MichalMarciniak31415/PiMN2024/blob/main/ImGui_ImPlot_for_students-master.zip

Changelog:
1.0.0:
    - initial release