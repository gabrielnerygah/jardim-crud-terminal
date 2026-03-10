#pragma once
#include "Planta.h"
#include <string>
#include <iostream>

// ============================================================
//  Subclasse 2: PlantaFrutifera  (herda de Planta → Vaca)
// ============================================================
class PlantaFrutifera : public Planta {
private:
    std::string tipoDeFruto;
    int         mesesAteColheita;
    double      producaoKgPorAno;

public:
    PlantaFrutifera() : Planta(), tipoDeFruto("Desconhecido"),
                        mesesAteColheita(12), producaoKgPorAno(0.0) {}

    PlantaFrutifera(const std::string& nome, const std::string& loc,
                    double preco, const Data& data,
                    double umidade, int diasRega, int fios,
                    const std::string& fruto, int meses, double producao)
        : Planta(nome, loc, preco, data, umidade, diasRega, fios),
          tipoDeFruto(fruto), mesesAteColheita(meses), producaoKgPorAno(producao) {}

    std::string getTipoDeFruto()      const { return tipoDeFruto; }
    int         getMesesAteColheita() const { return mesesAteColheita; }
    double      getProducaoKg()       const { return producaoKgPorAno; }
    void setTipoDeFruto(const std::string& t)  { tipoDeFruto = t; }
    void setMesesAteColheita(int m)            { mesesAteColheita = m; }
    void setProducaoKg(double p)               { producaoKgPorAno = p; }

    std::string getTipo() const override { return "Frutífera"; }
    std::string getCor()  const override { return "\033[38;2;205;133;63m"; } // Terracota

    void exibeVaca() const override {
        std::cout << "  \033[38;2;205;133;63m[Frutífera]\033[0m " << nome
                  << " | Fruto: " << tipoDeFruto
                  << " | Fios: " << qtdFiosDeCabelo << "\n";
    }

    void exibir() const override {
        Planta::exibir();
        std::cout << getCor()
                  << "  Tipo Fruto  : " << tipoDeFruto       << "\n"
                  << "  Meses/Colh  : " << mesesAteColheita  << "\n"
                  << "  Produção/Ano: " << std::fixed << std::setprecision(1)
                                        << producaoKgPorAno  << " kg\n"
                  << "\033[0m";
    }

    std::string serialize() const override {
        return Planta::serialize() + "|" + tipoDeFruto + "|" +
               std::to_string(mesesAteColheita) + "|" +
               std::to_string(producaoKgPorAno) + "|Girafa";
    }
};
