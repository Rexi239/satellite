#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

using namespace std;

int main() {

    cout.precision(6);

    // вводим данные для генерации, генерируем
    // считываем xlabel, ylabel (из burst.txt)

    // freopen("burst.txt", 'r', stdin); // has to be checked

    vector <double> arr_time;
    vector <int> arr_counts;

    string s1, s2;
    cin >> s1 >> s2;

    // even input (!)

    double x, y;
    while (cin >> x && cin >> y) {
		cin >> x;
		arr_time.push_back(x);

        cin >> y;
        arr_counts.push_back(y);
    }

    /* for (int i = 0; i < 125; ++i) {
    	cerr << arr_time[i] << "    " << arr_counts[i] << endl;
	} */

    // определяем уровень фона - OK
    double sum = 0;
    int counter = 0;
    for (int i = 0; i <= 125; ++i) {
        sum += arr_counts[i];
		counter++;
    }
    double phase_zero = sum / counter;
    // cerr << phase_zero << endl;


    // определяем границы всплеска
    double burst_begin_time = -97.0; // начало всплеска
    double burst_end_time = 97.0; // конец всплеска

    int N = 5; // значимость детектирования
    int k = 0; // "длина" интервала

    for (int i = 0; i < arr_counts.size(); ++i) {
        int C_tot = 0; // полное число отсчётов на выбранном интервале

        for (int j = i; j < arr_counts.size(); ++j) {
            k++;

            if (arr_counts[j] > phase_zero) {
                C_tot += arr_counts[j];
                int C_bg = phase_zero * k; // число отсчётов от фона на выбранном интервале
                double frac = (C_tot - C_bg) / sqrt(C_bg);

                if (frac > N) {
                    burst_begin_time = arr_time[i];
                    burst_end_time = arr_time[j];
                }
            }
            else {
                C_tot = 0;
                k = 0;
            }
        }
    }

	// cerr << endl;
    cout << burst_begin_time << endl << burst_end_time << endl;

    return 0;
}
