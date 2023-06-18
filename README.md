Program napisany w ramach projektu końcowego na zajęcia z Algorytmów i Struktur Danych.

Projekt polega na znalezieniu najtańszego systemu nie przekraczając ograniczeń czasowych czyli w praktyce znalezienie drzewa rozpinającego o najniższym koszcie, którego czas nie przekracza górnego limitu czasowego wczytywanego przez użytkownika z klawiatury.

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
  Klasa, która pobiera wszystkie istotne informacje z grafu zadań znajdującego się w pliku tekstowym tzn( węzły, krawędzie, czasy, koszta)
  Tworzy kontenery przechowujące te dane oraz tworzy instancje klas task i odpwiednio je ustawia.

spanning_tree:
    Jest to klasa, która reprezentuje osobnika. Zawiera krawędzie i wierzchołki pobrane z grafu zadań. Implementuje operatory genetyczne(krzyżowanie, mutacja,   
    klonowanie). Posiada funkcje obliczającą koszt i czas ze wszystkich wierzchołków oraz zajmuje się mapowaniem genotypu w fenotyp, czyli już w konkretnego 
    osbnika z wybranymi kosztami i czasami dla każdego wierzchołka.

    Plik main.cpp zajmuje się zeebraniem wszystkich składowych projektu i implementuje algorytm zajmujący się szukaniem najlepszego osobnika.

    


