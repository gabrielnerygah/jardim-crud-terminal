#pragma once
#include <string>
#include <iostream>

// ============================================================
//  Classe base obrigatória: Vaca
// ============================================================
class Vaca {
protected:
    int qtdFiosDeCabelo;  // atributo obrigatório

public:
    Vaca(int fios = 0) : qtdFiosDeCabelo(fios) {}
    virtual ~Vaca() = default;

    int getQtdFiosDeCabelo() const { return qtdFiosDeCabelo; }
    void setQtdFiosDeCabelo(int f) { qtdFiosDeCabelo = f; }

    // Método que DEVE ser sobrescrito pelas subclasses (Req 7)
    virtual void exibeVaca() const {
        std::cout << "[VACA BASE] Fios de Cabelo: " << qtdFiosDeCabelo << "\n";
    }

    virtual std::string getTipo() const { return "Vaca"; }
};
