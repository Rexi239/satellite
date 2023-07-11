#include <iostream>
#include <vector>
#include <math.h>

#include <fstream>
// #include <cstdio>

using namespace std;

int main() {
    cout.precision(6);

    // считываем arr_time, arr_counts (из burst.txt)
    // freopen("burst.txt", 'r', stdin); // has to be checked

    vector <double> arr_time;
    vector <int> arr_counts;

    ifstream in ("burst.txt"); // окрываем файл для чтения

    if (in.is_open()) {
        string s1, s2;
        in >> s1 >> s2;

        double x;
        int y;
        int cin_cnt = 400;

        while (cin_cnt >= 0) {
                in >> x >> y;
                arr_time.push_back(x);
                arr_counts.push_back(y);
                cin_cnt--;
        }
    }
    in.close();

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
    bool borders_found = false;

    for (int i = 0; i < arr_counts.size(); ++i) {

        if (borders_found) break;

        int length = 0;
        double C_tot = 0; // полное число отсчётов на выбранном интервале

        for (int j = i; j < arr_counts.size(); ++j) {
            if (arr_counts[j] > phase_zero) {
                length++;
                C_tot += arr_counts[j];
                double C_bg = phase_zero * length; // число отсчётов от фона на выбранном интервале
                double frac = (C_tot - C_bg) / sqrt(C_bg);

                if (frac > N) {
                    burst_begin_time = arr_time[i];
                    burst_end_time = arr_time[j];
                    borders_found = true;
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
