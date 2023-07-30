#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include <fstream>

using namespace std;

void read_data (
    const string & file_name,
    vector <double> & arr_time,
    vector <int> & arr_counts
    )
{
    cout.precision(6);
    ifstream in(file_name);

    if (!in.is_open()) {
        cout << "Error opening file: " << file_name;
        return;
    }

    // читаем заголовок
    string s1, s2;
    in >> s1 >> s2;

    double x;
    int y;

    // читаем данные массивов
    while (in.good()) {
        in >> x >> y;
        arr_time.push_back(x);
        arr_counts.push_back(y);
    }

    cout << "File " << file_name << " has been read" << "\n\n";
    cout << "Total lines: " << arr_time.size() << '\n';
    cout << "Start time: " << arr_time[0] << '\n';
    cout << "End time: " << arr_time[arr_time.size()-1] << "\n\n";

    in.close();
}

double get_bg_level(
    const double & Ti, // начало интервала определения фона
    const double & Tf, // конец интервала определения фона
    const vector <double> & arr_time,
    const vector <int> & arr_counts
    )
{
    // определяем уровень фона
    double sum = 0;
    int counter = 0;
    for (int i = 0; i <= arr_time.size(); ++i) {
        if (arr_time[i] < Ti) {continue;}
        if (arr_time[i] > Tf) {break;}

        sum += arr_counts[i];
		counter++;
    }

    return sum / counter;
}

void burst_search(
    const double & Ti,        // начало интервала поиска всплеска
    const double & Tf,        // конец интервала поиска всплеска
    const double & threshold, // порог детектирования
    const double & bg_level,  // уровень фона
    const vector <double> & arr_time,
    const vector <int> & arr_counts
    )
{
    double
        burst_begin_time, // время начала всплеска
        burst_end_time,   // время конца всплеска
        counts_tot,       // полное число отсчётов при поиске превышения
        counts_bg,        // число отсчётов фона при поиске превышения
        frac_detected,    // значимость обнаруженного всплеска
        dt_burst;         // длителность интервала всплеска

    bool excess_found = false;

    // ограничиваем конец интервала поиска
    // caution! учитываем, что данные подаются с интервалом в одну секунду
    int Tf_i = Tf - arr_time[0];
    int i_max = Tf_i;

    // общий случай (конец интервала поиска -- конец массива)
    // int i_max = arr_counts.size();

    for (int i = 0; i < arr_counts.size(); ++i) {
        if (arr_time[i] < Ti) {continue;}
        if (arr_time[i] == Tf) {break;}

        // нет смысла начинать суммировать с бина ниже фона
        if (arr_counts[i] < bg_level) {continue;}

        int length = 0;
        double C_tot = 0; // полное число отсчётов на выбранном интервале

        for (int j = i; j < i_max; ++j) {

            length++;
            C_tot += arr_counts[j];
            double C_bg = bg_level * length; // число отсчётов от фона на выбранном интервале
            double frac = (C_tot - C_bg) / sqrt(C_bg);

            if (frac > threshold) {
                burst_begin_time = arr_time[i];
                burst_end_time = arr_time[j];
                counts_tot = C_tot;
                counts_bg = C_bg;
                frac_detected = frac;
                dt_burst = burst_end_time - burst_begin_time;

                excess_found = true;
                i_max--;
            }
        }

    }

    cout.precision(4);
    cout << "Burst search results:" << '\n';
    cout << "Start time: " << burst_begin_time << '\n';
    cout << "End time: " << burst_end_time << '\n';
    cout << "Duration: " << dt_burst << '\n';
    cout << "Counts tot: " << counts_tot << '\n';
    cout << "Counts bg: " << counts_bg << '\n';
    cout << "Significance: " << frac_detected << '\n';
}

int main() {
    const string file_name = "burst.txt";

    // определяем границы интервала поиска всплеска
    const double data_begin_time = -125.0; // начало всплеска
    const double data_end_time = 125.0; // конец всплеска
    const double bg_end_time = -70.0; // конец фонового интервала

    const double threshold = 5; // порог (значимость) детектирования

    vector <double> arr_time;
    vector <int> arr_counts;

    // читаем данные
    read_data(file_name, arr_time, arr_counts);

    // определяем уровень фона
    double bg_level = get_bg_level(
        data_begin_time,
        bg_end_time,
        arr_time,
        arr_counts
    );
    cout << "Bg. level: " << bg_level << "\n\n";

    // ищем границы всплеска
    burst_search(
        bg_end_time,
        data_end_time,
        threshold,
        bg_level,
        arr_time,
        arr_counts
    );
    cout << '\n';

    return 0;
}
