#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

using namespace std;

int main() {

    // вводим данные для генерации, генерируем
    // считываем xlabel, ylabel (из burst.txt)

    // freopen("burst.txt", 'r', stdin); // has to be checked

    vector <double> arr_time;
    vector <double> arr_counts;

    string s1, s2;
    cin >> s1 >> s2;

    // arrays work correctly

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

    cerr << phase_zero << endl;

    /* индексы:
        -200 = 0
        labelx (-200) = index (0)
        index = labelx + 200
    */

    // определяем уровень фона - ok

    /* double max_amplitude = phase_zero;
    for (int i = 0; i < 125; ++i) {
        if (arr_counts[i] > max_amplitude) {
            max_amplitude = arr_counts[i];
        }
    }
    cerr << max_amplitude << endl;
    */

    // med_amplitude
    sum = 0;
    counter = 0;
    for (int i = 0; i <= 125; ++i) {
        if (arr_counts[i] > phase_zero) {
            sum += arr_counts[i];
            counter++;
        }
    }
    double med_amplitude = sum / counter;
    cerr << med_amplitude << endl;

    // начало всплеска

    double burst_begin_time = -9797.97;
    int burst_begin_time_i = -1;
    for (int i = 0; i < arr_counts.size() - 2; ++i) {
        if (arr_counts[i] > med_amplitude && arr_counts[i+1] > med_amplitude && arr_counts[i+2] > med_amplitude) {
            burst_begin_time = arr_time[i];
            burst_begin_time_i = i;
        }
    }

    //  конец всплеска
    int N = 5;
    double burst_end_time;
    int burst_end_time_i = -1;
    for (int i = burst_begin_time_i; i < arr_counts.size() - 2; ++i) {
        if (arr_counts[i] < med_amplitude && arr_counts[i+1] < med_amplitude && arr_counts[i+2] < med_amplitude) {
            burst_end_time = arr_time[i];
            burst_end_time_i = i;
        }
    }

    /* Считать, что на заданном временном интервале есть значимое превышение над фоном
    если  (C_tot - C_bg) / sqrt(C_bg) > N, где
    C_tot - полное число отсчётов на выбранном интервале,
    C_bg -  число отсчётов от фона на выбранном интервале,
    N - значимость детектирования (взять N=5, в дальнейшем обсудим физический смысл этого значения). */

    /* // to be fixed
    for (int i = 400; i >= burst_begin_time; --i) {
        int C_tot = i - burst_begin_time + 1;

        for (int j = burst_begin_time; j <= i; ++j) {
            int C_bg = i - j + 1;

            if ((C_tot - C_bg) / sqrt(C_bg) > N) {
                burst_end_time = arr_time[j];
            }
        }
    } */

	cerr << endl;
    cout << burst_begin_time << endl << burst_end_time << endl;

    return 0;
}
