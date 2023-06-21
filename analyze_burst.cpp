#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {

    freopen("burst.txt", 'r', stdin);

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

    return 0;
}