#include <iostream>
using namespace std;

int main() {

    // вводим данные для генерации
    // считываем xlabel, ylabel (при генерации?)

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

    double burst_begin_time;
    for (int i = -200; i <= 200; ++i) {
        if (ylabel[i] > max_amplitude) {
            burst_begin_time = xlabel[i];
        }
    }

    cout << burst_begin_time << endl;

    return 0;
}

