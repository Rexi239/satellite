#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <fstream>

using namespace std;

vector <int> copy(vector <int> & v) {
    vector <int> result;
    for (int i = 0; i < v.size(); ++i)
        result.push_back(v[i]);
    return result;
}

void read_data (
        const string & file_name,
        vector<double> & time1,
        vector<double> & time2,
        vector<vector<int> > & c
)
{
    ifstream in(file_name);

    if (!in.is_open()) {
        cout << "Error opening file: " << file_name;
        cout << '\n';
        return;
    }

    double t1, t2;

    // читаем данные массивов
    while (in.good()) {
        in >> t1 >> t2;
        time1.push_back(t1);
        time2.push_back(t2);

        for (int i = 0; i < 12; ++i) {
            int ci;
            in >> ci;
            c[i].push_back(ci);
        }
    }

    cout << "File " << file_name << " has been read" << "\n\n";
    cout << "Total lines: " << time1.size() << '\n';
    cout << "Start time: " << time1[0] << '\n';
    cout << "End time: " << time1[time1.size()-1] << "\n\n";

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

// ищет первый всплеск на заданном диапазоне
void burst_search(
        bool & all_bursts_found,
        double & last_burst_end_time,
        const double & Ti,        // начало интервала поиска всплеска
        const double & threshold, // порог детектирования
        const double & bg_level,  // уровень фона
        const vector <double> & arr_time,
        const vector <int> & arr_counts
)
{
    double
            burst_begin_time, // время начала всплеска
    burst_end_time;   // время конца всплеска

    bool excess_found = false;

    //конец интервала поиска -- конец массива!
    int i_max = arr_counts.size();

    for (int i = 0; i < arr_counts.size(); ++i) {
        if (arr_time[i] <= Ti) {continue;}

        // нет смысла начинать суммировать с бина ниже фона
        if (arr_counts[i] < bg_level) {continue;}

        int length = 0;
        double C_tot = 0; // полное число отсчётов на выбранном интервале

        for (int j = i; j < i_max; ++j) {
            length++;
            C_tot += arr_counts[j];
            double C_bg = bg_level * length; // число отсчётов от фона на выбранном интервале
            double frac = (C_tot - C_bg) / sqrt(C_bg);

            if (frac > threshold && arr_time[i] != arr_time[j]) {
                burst_begin_time = arr_time[i];
                burst_end_time = arr_time[j];
                excess_found = true;
                i_max--;
            }
        }
    }

    if(!excess_found) {
        all_bursts_found = true;
        cout << "No (more) bursts found.\n";
        return;
    }

    cout.precision(6);
    cout << "Burst: from " << burst_begin_time << " to " << burst_end_time << ". Bg. level: " << bg_level << ".\n";

    last_burst_end_time = burst_end_time;
}

void where_are_the_bursts(
        const double & data_begin_time,
        const double & data_end_time,
        const double & threshold, // порог детектирования
        const vector <double> & time,
        const vector <int> & counts
)
{
    bool all_bursts_found = false;
    double last_burst_end_time = data_begin_time;

    const double static_bg_level = get_bg_level(30.056, 50.024, time, counts);
    cout << "Static bg. level: " << static_bg_level << ".\n\n";

    while (!all_bursts_found) {
        burst_search(
                all_bursts_found,
                last_burst_end_time,
                last_burst_end_time,
                threshold,
                static_bg_level,
                time,
                counts
        );
    }
}

vector<int> energy_interval(vector <vector <int> > & c, int counts_number){
    return copy(c[counts_number-1]);
}



int main() {

    // задаем массивы для записи данных
    vector <double> time1;
    vector <double> time2;
    vector <vector <int> > c (12); // counts[i]

    const double threshold = 10; // порог (значимость) детектирования

    // читаем файл
    read_data("krf20090406_62535_1_S1_64ms.thr",time1, time2,c);

    // анализируем набор данных на наличие всплесков
    // циклом проходя по всем энергетическим диапазонам
    for (int i = 1; i <= 12; i++) {
        where_are_the_bursts(
                time1[0],
                time1[time1.size() - 1],
                threshold,
                time1,
                energy_interval(c, i) // выбираем энергетический диапазон
        );
    }
    return 0;
}