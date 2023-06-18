Program napisany w ramach projektu końcowego na zajęcia z Algorytmów i Struktur Danych.

Projekt polega na znalezieniu najtańszego systemu nie przekraczając ograniczeń czasowych, czyli w praktyce znalezienie drzewa rozpinającego o najniższym koszcie, którego czas nie przekracza górnego limitu czasowego wczytywanego przez użytkownika z klawiatury.

Instrukcja użytkowania:

  1. Podaj wielkość pokolenia poczatkowego
  2. Podaj nazwę grafu (np graf10.txt)
  3. Podaj warunek stopu (liczba pokoleń, w których sprawdzany jest najlepszy wygenerowny osobnik)
  4. Podaj ilość klonowań (współczynnik z przedziału [0,1])
  5. Podaj ilość krzyżowań (współczynnik z przedziału [0,1])
  6. Podaj ilośc mutacji (współczynnik z przedziału [0,1])
  7. Podaj czas nie do przekroczenia
  8. Odczytaj rezultat

Schemat działania programu i opis poszczególnych klas.

resourceManager:
    Klasa odpowiedzialna za losowy przydział zasobu do poszczególnych wierzchołków drzewa rozpinającego.
    Zajmuje się tym statyczna funkcja selectRes zwracająca obiekt typu std::pair<resource,int>, gdzie resource jest klasą odpowiedzialną za zasób, a w polu int     
    znajduje się indeks danego zasobu z vectora resources.

resource:

    Klasa odpowiadająca za konkretny zasób.
    Z klasy odczytujemy jego koszt, czas oraz informacje o tym ile razy został wybrany.

task:

    Klasa zajmująca się prztrzymywaniem wszystkich możliwych do wybrania zasobów dla danego węzła odczytanych z grafu zadań oraz przechowuje wybrany po mapowaniu   
    genotypu w fenotyp zasób.

task_graph:

    Klasa, która pobiera wszystkie istotne informacje z grafu zadań znajdującego się w pliku tekstowym, tzn( węzły, krawędzie, czasy, koszta)
    Tworzy kontenery przechowujące te dane oraz tworzy instancje klas task i odpwiednio je ustawia.

spanning_tree:

    Jest to klasa, która reprezentuje osobnika. Zawiera krawędzie i wierzchołki pobrane z grafu zadań. Implementuje operatory genetyczne(krzyżowanie, mutacja,   
    klonowanie). Posiada funkcje obliczającą koszt i czas ze wszystkich wierzchołków oraz zajmuje się mapowaniem genotypu w fenotyp, czyli już w konkretnego 
    osbnika z wybranymi kosztami i czasami dla każdego wierzchołka.

  Plik main.cpp zajmuje się zebraniem wszystkich składowych projektu i implementuje algorytm zajmujący się szukaniem najlepszego osobnika.

  Opis algorytmu:
  Po wczytaniu wszystkich danych z klawiatury następuje utowrzenie pierwszego pokolenia, którego ilość genotypów tworzona jest według wzoru π = α *n *z, gdzie alfa   to wczytwana z klawiatury ilość następnych pokoleń, w których sprawdzany będzie osobnik, n to liczba wierzchołków grafu zadań, a z to liczba zasobów.
  Następnie zostaje utworzona pętla while, która wykonuje się do momentu aż gdy zmienna currentLoops bedzie większa niż alfa.
  Najpierw dokonywana jest selekcja czyli posortowanie wszsytkich osobników w danej generacji. Następnie obliczana jest faktyczna ilośc użycia operatorów   
  genetycznych. To ile razy wykona się dany operator jest obliczane mnożąc podany przez użytkownika współczynnik razy ilść osobników w danej generacji.
  
  Krzyżowanie polega na wybraniu losowego punktu przecięcia i zamienieniu ze sobą nawzajem dwóch poddrzew z dwóch osobników zaczynających się od wylosowanego 
  punktu przecięcia.
  Zwracane są dwa nowe osobniki.
  
  Mutacja polega na wybraniu losowego wierzchołka genotypu i zamianie go na inny, losowo stworzony.
  
  Klonowanie to po prostu powielenie aktualnego osobnika.
  
  Ilość osobników w nowej generacji jest sumą wszystkich osobników otrzymanych po użyciu tych trzech operatorów genetycznych.
  Następnie na wygenerowanym w ten sposob pokoleniu wywoływana jest operacja mapowania genotypu w fenotyp, gdzie dla każdego wierzchołka zostaje przydzielony już 
  konkretny zasób.
  Po każdym przejścu pętli następuje sprawdzenie czy nie został znaleziony osobnik z niższym kosztem niz ten z poprzedniej generacji.(na samym początku     
  porówynywany jest z kosztem losowego osobnika z pierwszej generacji)
  Jeśli tak to jest on zapisywany i następuje sprawdzenie drugiego warunku jakim jest kontrola czy czas osobnika jest niższy niż ten podany z klawaitury, jeśli 
  tak, to currentLoops jest zerowane i osobnik zostanie  porównywnany z następnymi generacjami co najmniej alfa razy. Jeśli jendnak czas jest większy niż ten 
  użytkownika, to currentLoops zostanie inkrementowane. Zmienna tak samo zostanie inkeremntowana w przypadku gdy osobnik nowego pokolenia nie będzie mial niższego 
  kosztu niż ten z poprzedniego.

      Program napisany w języku C++ 17 za pomocą Visual Studio 2022
      Debuger Release x64
  

    


