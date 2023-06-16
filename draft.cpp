#include <iostream>
using namespace std;

int main() {

    // вводим данные для генерации, генерируем
    // считываем xlabel, ylabel (из burst.txt)

    vector <double> xlabel;
    vector <double> ylabel;

    string s1, s2;
    cin >> s1 >> s2;

    double x, y;

    while (cin >> x) {
        cin >> x;
        cin >> y;
        xlabel.pushback(x)
        ylabel.pushback(y)
    }

    // определяем уровень фона
    double sum = 0;
    for (int i = -200; i <= -75; ++i) {
        sum += ylabel[i];

    }
    double phase_zero = sum / (200 - 75 + 1);

    double max_amplitude = phase_zero;
    for (int i = -200; i < 75; ++i) {
        if (ylabel[i] > max_amplitude) {
            max_amplitude = ylabel[i];
        }
    }

    // начало всплеска

    double burst_begin_time;
    for (int i = -200; i <= 200; ++i) {
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
    
    for (int i = -200; i <= 200; ++i) {
        if () {

        }
    }

    cout << burst_begin_time << endl;

    return 0;
}
