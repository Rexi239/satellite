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
) {
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
    //const vector <double> & arr_time,
    const vector <int> & arr_counts
) {
    double sum = 0;
    int counter = 0;
    for (int i = 0; i <= 125; ++i) {
        sum += arr_counts[i];
		counter++;
    }
    return sum / counter;
}

void burst_search_draft(
    const double & bg_level,
    const vector <double> & arr_time,
    const vector <int> & arr_counts
) {

    // предопределяем границы всплеска
    double burst_begin_time = -97.0; // начало всплеска
    double burst_end_time = 97.0; // конец всплеска

    int N = 5; // значимость детектирования
    bool borders_found = false;

    for (int i = 0; i < arr_counts.size(); ++i) {

        if (borders_found) break;

        int length = 0;
        double C_tot = 0; // полное число отсчётов на выбранном интервале

        for (int j = i; j < arr_counts.size(); ++j) {
            if (arr_counts[j] > bg_level) {
                length++;
                C_tot += arr_counts[j];
                double C_bg = bg_level * length; // число отсчётов от фона на выбранном интервале
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

    cout << "Burst search results:\n";
    cout << "Start time: " << burst_begin_time << '\n';
    cout << "End time: " << burst_end_time << '\n';

}

int main() {
    cout.precision(6);

    const string file_name = "burst.txt";

    vector <double> arr_time;
    vector <int> arr_counts;

    // читаем данные
    read_data(file_name, arr_time, arr_counts);

    // определяем уровень фона
    double bg_level = get_bg_level(arr_counts); // уровень фона
    cout << "Bg. level: " << bg_level << endl << endl;

    // ищем границы всплеска
    burst_search_draft(bg_level, arr_time, arr_counts);

    return 0;
}
