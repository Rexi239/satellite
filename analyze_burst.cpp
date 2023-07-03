#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

using namespace std;

int main() {
    cout.precision(6);

    // считываем arr_time, arr_counts (из burst.txt)
    // freopen("burst.txt", 'r', stdin); // has to be checked

    vector <double> arr_time;
    vector <int> arr_counts;

    string s1, s2;
    cin >> s1 >> s2;

    // input
    int cin_cnt = 400;

    while (cin_cnt >= 0) {
        double x;
        int y;

		cin >> x;
		arr_time.push_back(x);

        cin >> y;
        arr_counts.push_back(y);

        cin_cnt--;
    }

    /* for (int i = 0; i < 125; ++i) {
    	cerr << arr_time[i] << "    " << arr_counts[i] << endl;
	}
	cerr << endl; */

    // определяем уровень фона
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

    for (int i = 0; i < arr_counts.size(); ++i) {

        int k = 0; // "длина" интервала
        int C_tot = 0; // полное число отсчётов на выбранном интервале
        bool big_enough = true;

        for (int j = i; j < arr_counts.size(); ++j) {
            if (arr_counts[j] > phase_zero && big_enough) {
                k++;
                C_tot += arr_counts[j];
                int C_bg = phase_zero * k; // число отсчётов от фона на выбранном интервале
                double frac = (C_tot - C_bg) / sqrt(C_bg);

                if (frac > N) {
                    burst_begin_time = arr_time[i];
                    burst_end_time = arr_time[j];
                }
            }
            else {
                break;
            }
        }
    }

	// cerr << endl;
    cout << burst_begin_time << endl << burst_end_time << endl;

    return 0;
}
