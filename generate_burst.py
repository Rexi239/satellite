"""
В скрипте реализована генерация модельной кривой блеска гамма-всплеска 
(отсчёты детектора в зависимости от времени).

В результаты сохраняются в виде рисунка 'burst.png' и 
выводятся в тестовый файл 'burst.txt'

Задача:
Придумать алгоритм поиска начала всплеска в сгенерированных данных.
Можно считать что на интервале [-200, -75] c всплеска нет и 
можно использовать этот интервал для определения уровня фона.

Считать, что на заданном временном интервале есть значимое превышение над фоном
если  (C_tot - C_bg) / sqrt(C_bg) > N, где 
C_tot - полное число отсчётов на выбранном интервале,
C_bg -  число отсчётов от фона на выбранном интервале,
N - значимость детектирования (взять N=5, в дальнейшем обсудим физический смысл этого значения).

"""

import numpy as np
from scipy.stats import poisson, norm

import matplotlib as mpl

mpl.use('Agg')

import matplotlib.pyplot as plt
plt.style.use('classic')

def generate_burst(t_i, t_f, dt, rate_bg, A, t_c, sigma):
    """
    Функция генерирует модельную кривую блеска гамма-всплеска в форме функции Гаусса, 
    наблюдаемого в присутствии постоянного фона детектора
    """

    # создаём массив временных интервалов (бинов)
    arr_time = np.arange(t_i, t_f, dt)

    # создаём массив отсчётов, связанных с фоном
    arr_counts = np.ones_like(arr_time) * rate_bg * dt

    # добавляем отсчёты связанные со всплеском 
    # см. https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.norm.html

    arr_counts += A * norm.pdf(arr_time, loc=t_c, scale=sigma)

    # накладываем на модельную кривую блеска пуассоновский шум, связанный со статистикой отсчётов детектора
    arr_counts = poisson.rvs(arr_counts, size=(1,len(arr_counts)))

    return arr_time, arr_counts[0]

def plot_burst(arr_time, arr_counts, rate_bg):

    dt = arr_time[1] - arr_time[0]
    plt.step(arr_time, arr_counts, c='r')
    plt.axhline(rate_bg*dt, c='k', ls='--')

    plt.xlim(-200, 200)
    #plt.ylim(0, 20)

    plt.xlabel('время, с')
    plt.ylabel('отсчёты')
    
    plt.savefig('burst.png')

def write(arr_time, arr_counts, file_name):

    with open(file_name, 'w') as f:
        f.write('    Time  Counst\n')
        for i in range(len(arr_time)):
            f.write('{:8.3f}  {:6.0f}\n'.format(arr_time[i], arr_counts[i]))
  
# def write_png(arr_time, arr_counts, file_name):

   # with open(file_name,'w') as ???:
       # for i in range(len(arr_time)):
           # ???.write()

def main():

    # временной инnервал
    t_i, t_f, = -200.0, +200.0 # секунды, с
 
    # шаг по времени
    dt = 1.0 # с  
 
    # скорость счёта фона
    rate_bg = 5 # отчёты/с

    # параметры функции Гаусса, которая будет моделью всплеска

    # амплитуда
    A = 500 # отчёты/с

    # положение центра 
    t_c = 0.0 # c

    # ширина
    sigma = 15.0 # c

    arr_time, arr_counts = generate_burst(t_i, t_f, dt, rate_bg, A, t_c, sigma)
    plot_burst(arr_time, arr_counts, rate_bg)

    file_name_txt = 'burst.txt'
    write(arr_time, arr_counts, file_name_txt)

    file_name_png = 'burst.png'
    # write_png(arr_time, arr_counts, file_name_png)

    # как считывать с файла?
    # f = open('burst.txt', 'r')
    # считаем с файла xlabel, ylabel

    # если пишем здась, читать не нужно, можно сразу arr_time, arr_counts
    # можно cpp с чтением файла



    xlabel = []
    ylabel = []
    s1, s2 = input().split()
    x, y = 0, 0

    while True:
        try:
            x, y = map(float, input().split())
            xlabel.append(x)
            ylabel.append(y)
        except:
            break

    sum = np.sum(ylabel[:126])
    phase_zero = sum / (200 - 75 + 1)

    max_amplitude = phase_zero
    for i in range(125):
        if ylabel[i] > max_amplitude:
            max_amplitude = ylabel[i]

    burst_begin_time = 0
    for i in range(401):
        if ylabel[i] > max_amplitude:
            burst_begin_time = xlabel[i]

    N = 5
    burst_end_time = 0
    for i in range(400, int(burst_begin_time), -1):
        if ylabel[i] > phase_zero:
            N -= 1
            if N == 0:
                burst_end_time = xlabel[i]
                break


main()
