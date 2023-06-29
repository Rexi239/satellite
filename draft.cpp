#include <iostream>
#include <vector>
using namespace std;

int main() {

    // вводим данные для генерации, генерируем
    // считываем xlabel, ylabel (из burst.txt)

    vector <double> arr_time;
    vector <double> arr_counts;

    string s1, s2;
    cin >> s1 >> s2;

    double x, y;

    while (cin >> x) {
        cin >> x;
        cin >> y;
        arr_time.push_back(x);
        arr_counts.push_back(y);
    }

    // определяем уровень фона
    double sum = 0;
    for (int i = 0; i <= 125; ++i) {
        sum += ylabel[i];

    }
    double phase_zero = sum / (200 - 75 + 1);


    /* Индексы:
        -200 = 0
        labelx (-200) = index (0)
        index = labelx + 200
    */


    double max_amplitude = phase_zero;
    for (int i = 0; i < 125; ++i) {
        if (ylabel[i] > max_amplitude) {
            max_amplitude = ylabel[i];
        }
    }

    // начало всплеска

    double burst_begin_time;
    for (int i = 0; i <= 400; ++i) {
        if (ylabel[i] > max_amplitude) {
            burst_begin_time = xlabel[i];
        }
    }

    // весь всплеск

    /* Считать, что на заданном временном интервале есть значимое превышение над фоном
если  (C_tot - C_bg) / sqrt(C_bg) > N, где 
C_tot - полное число отсчётов на выбранном интервале,
C_bg -  число отсчётов от фона на выбранном интервале,
N - значимость детектирования (взять N=5, в дальнейшем обсудим физический смысл этого значения). */

    int N = 5;
    double burst_end_time;
    
    for (int i = 400; i >= burst_begin_time; --i) {
        int C_tot = i - burst_begin_time + 1;

        for (int j = burst_begin_time; j <= i; ++j) {
            int C_bg = i - j + 1;

            if ((C_tot - C_bg) / sqrt(C_bg) > N) {
                burst_end_time = xlabel[j];
            }
        }
    }

    cout << burst_begin_time << endl << burst_end_time << endl;

    return 0;
}


/* converted to python

import numpy as np

xlabel = []
ylabel = []
s1, s2 = input().split()
x, y = 0, 0
while True:
    try:
        x, y = map(float, input().split())
        xlabel.append(x)
        ylabel.append(y)
    except:
        break

sum = np.sum(ylabel[:126])
phase_zero = sum / (200 - 75 + 1)

max_amplitude = phase_zero
for i in range(125):
    if ylabel[i] > max_amplitude:
        max_amplitude = ylabel[i]

burst_begin_time = 0
for i in range(401):
    if ylabel[i] > max_amplitude:
        burst_begin_time = xlabel[i]

N = 5
burst_end_time = 0
for i in range(400, int(burst_begin_time), -1):
    if ylabel[i] > phase_zero:
        N -= 1
        if N == 0:
            burst_end_time = xlabel[i]
            break

print(burst_begin_time, burst_end_time)

*/