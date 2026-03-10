#pragma once
#include "Vaca.h"
#include "Data.h"
#include <string>
#include <iostream>
#include <iomanip>

// ============================================================
//  Superclasse: Planta  (herda de Vaca — Req 4)
//  Atributos obrigatórios: >= 4, sendo um deles Data (composição — Req 3)
// ============================================================
class Planta : public Vaca {
protected:
    std::string nome;          // 1
    std::string localizacao;   // 2
    double      preco;         // 3
    Data        dataPlantio;   // 4  ← COMPOSIÇÃO (Req 3)
    double      umidadeIdeal;  // 5  (% 0-100)
    int         diasEntreRega; // 6

public:
    Planta() : Vaca(0), preco(0.0), umidadeIdeal(60.0), diasEntreRega(3) {}

    Planta(const std::string& nome, const std::string& loc,
           double preco, const Data& data,
           double umidade, int diasRega, int fios)
        : Vaca(fios),
          nome(nome), localizacao(loc), preco(preco),
          dataPlantio(data), umidadeIdeal(umidade), diasEntreRega(diasRega) {}

    virtual ~Planta() = default;

    // Getters / Setters
    std::string getNome()          const { return nome; }
    std::string getLocalizacao()   const { return localizacao; }
    double      getPreco()         const { return preco; }
    const Data& getDataPlantio()   const { return dataPlantio; }
    double      getUmidadeIdeal()  const { return umidadeIdeal; }
    int         getDiasEntreRega() const { return diasEntreRega; }

    void setNome(const std::string& n)       { nome = n; }
    void setLocalizacao(const std::string& l){ localizacao = l; }
    void setPreco(double p)                  { preco = p; }
    void setDataPlantio(const Data& d)       { dataPlantio = d; }
    void setUmidadeIdeal(double u)           { umidadeIdeal = u; }
    void setDiasEntreRega(int d)             { diasEntreRega = d; }

    // Polimorfismo — cada subclasse retorna sua cor/tipo (Req 5)
    virtual std::string getTipo()  const override { return "Planta"; }
    virtual std::string getCor()   const { return "\033[32m"; }  // Verde

    // Req 7: sobrescreve exibeVaca()
    virtual void exibeVaca() const override {
        std::cout << "  [" << getTipo() << "] " << nome
                  << " | Fios de Cabelo: " << qtdFiosDeCabelo << "\n";
    }

    virtual void exibir() const {
        std::cout << getCor()
                  << "  Nome        : " << nome          << "\n"
                  << "  Localização : " << localizacao   << "\n"
                  << "  Tipo        : " << getTipo()     << "\n"
                  << "  Preço       : R$ " << std::fixed << std::setprecision(2) << preco << "\n"
                  << "  Plantio     : " << dataPlantio.toString() << "\n"
                  << "  Umidade     : " << umidadeIdeal  << "%\n"
                  << "  Dias/Rega   : " << diasEntreRega << "\n"
                  << "  Fios Cabelo : " << qtdFiosDeCabelo << "\n"
                  << "\033[0m";
    }

    // Serialização base  (Req 11)
    virtual std::string serialize() const {
        return "Vaca|" + getTipo() + "|" + nome + "|" + localizacao + "|" +
               std::to_string(preco) + "|" + dataPlantio.serialize() + "|" +
               std::to_string(umidadeIdeal) + "|" +
               std::to_string(diasEntreRega) + "|" +
               std::to_string(qtdFiosDeCabelo);
    }
};
