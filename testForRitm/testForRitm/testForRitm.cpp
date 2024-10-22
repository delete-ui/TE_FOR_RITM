#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double m = 1.0;                       // масса
const double L = 5.0;                       // длина стержня
const double g0 = 9.81;                     // ускорение свободного падения
const double t0 = 0.0;                      // начальный момент времени
const double dt = 0.01;                     // шаг по времени
const double T = 1.0;                       // период внешней силы (пример)
const double t_end = 10.0;                  // конечное время
const double M_PI = 3.14159265358979323846; //число П

// Функция, описывающая систему уравнений
void f(double t, double x, double y, double& dx, double& dy) {
    double g = g0 + 0.05 * sin(2 * M_PI * T * t);
    dx = -x / L * T;
    dy = -L / T * m * g;
}

int main() {
    // Начальные условия
    double x = 3.0;
    double y = -4.0;
    double dx, dy;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "t\t x\t y\n";
    for (double t = t0; t <= t_end; t += dt) {
        f(t, x, y, dx, dy);

        // Обновление значений с методом Рунге-Кутты
        double k1x = dx;
        double k1y = dy;

        double k2x, k2y;
        f(t + dt / 2, x + k1x * dt / 2, y + k1y * dt / 2, k2x, k2y);

        double k3x, k3y;
        f(t + dt / 2, x + k2x * dt / 2, y + k2y * dt / 2, k3x, k3y);

        double k4x, k4y;
        f(t + dt, x + k3x * dt, y + k3y * dt, k4x, k4y);

        x += dt / 6 * (k1x + 2 * k2x + 2 * k3x + k4x);
        y += dt / 6 * (k1y + 2 * k2y + 2 * k3y + k4y);

        // Вывод значения времени и координат
        std::cout << t << "\t" << x << "\t" << y << "\n";
    }

    return 0;
}