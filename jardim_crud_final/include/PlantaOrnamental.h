#pragma once
#include "Planta.h"
#include <string>
#include <iostream>

// ============================================================
//  Subclasse 1: PlantaOrnamental  (herda de Planta → Vaca)
// ============================================================
class PlantaOrnamental : public Planta {
private:
    std::string corFlor;
    bool        floresce;

public:
    PlantaOrnamental() : Planta(), corFlor("Branca"), floresce(false) {}

    PlantaOrnamental(const std::string& nome, const std::string& loc,
                     double preco, const Data& data,
                     double umidade, int diasRega, int fios,
                     const std::string& corFlor, bool floresce)
        : Planta(nome, loc, preco, data, umidade, diasRega, fios),
          corFlor(corFlor), floresce(floresce) {}

    std::string getCorFlor()  const { return corFlor; }
    bool        getFloresce() const { return floresce; }
    void setCorFlor(const std::string& c) { corFlor = c; }
    void setFloresce(bool f)              { floresce = f; }

    std::string getTipo() const override { return "Ornamental"; }
    std::string getCor()  const override { return "\033[38;2;143;188;143m"; } // Verde Sálvia

    void exibeVaca() const override {
        std::cout << "  \033[38;2;143;188;143m[Ornamental]\033[0m " << nome
                  << " | Flor: " << corFlor
                  << " | Fios: " << qtdFiosDeCabelo << "\n";
    }

    void exibir() const override {
        Planta::exibir();
        std::cout << getCor()
                  << "  Cor da Flor : " << corFlor << "\n"
                  << "  Floresce    : " << (floresce ? "Sim" : "Não") << "\n"
                  << "\033[0m";
    }

    std::string serialize() const override {
        return Planta::serialize() + "|" + corFlor + "|" +
               (floresce ? "1" : "0") + "|Girafa";
    }
};
