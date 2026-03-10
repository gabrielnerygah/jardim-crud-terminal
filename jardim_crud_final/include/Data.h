#pragma once
#include <string>
#include <sstream>
#include <iomanip>

class Data {
private:
    int dia, mes, ano;
public:
    Data(int d = 1, int m = 1, int a = 2024) : dia(d), mes(m), ano(a) {}

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }
    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAno(int a) { ano = a; }

    std::string toString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << dia << "/"
            << std::setw(2) << std::setfill('0') << mes << "/"
            << ano;
        return oss.str();
    }

    // Serialização simples
    std::string serialize() const {
        return std::to_string(dia) + "," + std::to_string(mes) + "," + std::to_string(ano);
    }

    static Data deserialize(const std::string& s) {
        std::istringstream iss(s);
        int d, m, a; char sep;
        iss >> d >> sep >> m >> sep >> a;
        return Data(d, m, a);
    }
};
