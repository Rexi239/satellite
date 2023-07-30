# ReadMe

**Задача**. Придумать алгоритм поиска начала всплеска в сгенерированных данных.
Можно считать что на интервале [-200, -75] c всплеска нет и 
можно использовать этот интервал для определения уровня фона.

### ![generate_burst.py](https://github.com/Rexi239/satellite/blob/main/generate_burst.py) 
В скрипте реализована генерация модельной кривой блеска гамма-всплеска 
(отсчёты детектора в зависимости от времени).
В результаты сохраняются в виде рисунка 'burst.png' и 
выводятся в тестовый файл !['burst.txt'](https://github.com/Rexi239/satellite/blob/main/burst.txt).

Пример графика 'burst.png':

![burst.png](https://github.com/Rexi239/satellite/blob/main/burst.png)

### ![analyze_burst.cpp](https://github.com/Rexi239/satellite/blob/main/analyze_burst.cpp) 
Реализована обработка сгенерированных данных, в частности, поиск границ всплеска.
