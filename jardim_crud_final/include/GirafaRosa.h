#pragma once
#include "Planta.h"
#include "PlantaOrnamental.h"
#include "PlantaFrutifera.h"
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// ============================================================
//  GirafaRosa — Gerenciadora CRUD  (Req 8)
//  Usa std::queue com polimorfismo  (Req 5)
// ============================================================
class GirafaRosa {
private:
    // std::queue com polimorfismo via unique_ptr  (Req 5)
    std::queue<std::unique_ptr<Planta>> plantas;
    const std::string arquivoDados = "jardim_dados.txt";

    // ── Acesso indexado à queue ────────────────────────────────
    // std::queue não permite acesso por índice. Este método reconstrói
    // a queue preservando todos os elementos e retorna ponteiros brutos
    // (sem transferir ownership) para operações indexadas.
    std::vector<Planta*> getVectorView() const {
        std::vector<Planta*> v;
        auto& q = const_cast<std::queue<std::unique_ptr<Planta>>&>(plantas);
        std::queue<std::unique_ptr<Planta>> tmp;
        while (!q.empty()) {
            v.push_back(q.front().get());
            tmp.push(std::move(q.front()));
            q.pop();
        }
        q = std::move(tmp);
        return v;
    }

    void enfileirar(std::unique_ptr<Planta> p) {
        plantas.push(std::move(p));
    }

    // Remove o elemento de índice idx reconstruindo a queue
    void removerDaQueue(int idx) {
        std::queue<std::unique_ptr<Planta>> nova;
        int i = 0;
        while (!plantas.empty()) {
            if (i != idx)
                nova.push(std::move(plantas.front()));
            else
                plantas.front().reset(); // libera memória
            plantas.pop();
            i++;
        }
        plantas = std::move(nova);
    }

    int size() const { return (int)plantas.size(); }

    // ── Helpers de UI ──────────────────────────────────────────
    void limparTela() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pausar() const {
        std::cout << "\n  \033[90mPressione ENTER para continuar...\033[0m";
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

    void cabecalho(const std::string& titulo) const {
        std::cout << "\033[1;34m";
        std::cout << "  \xe2\x95\x94\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x97\n";
        std::cout << "  \xe2\x95\x91   \033[1;32m\xf0\x9f\x8c\xbf JARDIM INTELIGENTE \xe2\x80\x94 SISTEMA CRUD\033[1;34m          \xe2\x95\x91\n";
        std::cout << "  \xe2\x95\xa0\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\xa3\n";
        std::cout << "  \xe2\x95\x91  \033[1;36m" << std::left << std::setw(48) << titulo << "\033[1;34m\xe2\x95\x91\n";
        std::cout << "  \xe2\x95\x9a\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x90\xe2\x95\x9d\033[0m\n\n";
    }

    void linha() const {
        std::cout << "\033[90m  \xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\xe2\x94\x80\033[0m\n";
    }

    std::string inputStr(const std::string& prompt) const {
        std::cout << "  \033[33m" << prompt << "\033[0m";
        std::string s;
        std::getline(std::cin, s);
        return s;
    }

    double inputDouble(const std::string& prompt) const {
        double v = 0;
        std::cout << "  \033[33m" << prompt << "\033[0m";
        std::cin >> v;
        std::cin.ignore(10000, '\n');
        return v;
    }

    int inputInt(const std::string& prompt) const {
        int v = 0;
        std::cout << "  \033[33m" << prompt << "\033[0m";
        std::cin >> v;
        std::cin.ignore(10000, '\n');
        return v;
    }

    Data inputData(const std::string& prompt) const {
        std::cout << "  \033[33m" << prompt << "\033[0m";
        int d = 1, m = 1, a = 2024; char sep;
        std::cin >> d >> sep >> m >> sep >> a;
        std::cin.ignore(10000, '\n');
        return Data(d, m, a);
    }

public:
    // ── Pesquisar por nome — Req 1c / 1d / 1e ─────────────────
    int Pesquisar(std::string nome) {
        std::string nomeLow = nome;
        std::transform(nomeLow.begin(), nomeLow.end(), nomeLow.begin(), ::tolower);

        auto v = getVectorView();
        std::vector<int> encontrados;
        for (int i = 0; i < (int)v.size(); i++) {
            std::string n = v[i]->getNome();
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            if (n.find(nomeLow) != std::string::npos)
                encontrados.push_back(i);
        }

        if (encontrados.empty()) {
            std::cout << "\033[31m  X Nenhuma planta encontrada com o nome \"" << nome << "\".\033[0m\n";
            return -1;
        }

        if (encontrados.size() == 1) return encontrados[0];

        std::cout << "\033[33m  Multiplas plantas encontradas:\033[0m\n";
        for (int idx : encontrados) {
            std::cout << "  [" << idx << "] " << v[idx]->getNome()
                      << " (" << v[idx]->getTipo() << ")\n";
        }
        int sel = inputInt("  Selecione o indice: ");
        for (int idx : encontrados)
            if (idx == sel) return sel;

        std::cout << "\033[31m  X Indice invalido.\033[0m\n";
        return -1;
    }

    // ── 1. INSERIR ─────────────────────────────────────────────
    void inserir() {
        limparTela();
        cabecalho("INSERIR NOVA PLANTA");

        std::cout << "  Tipo de planta:\n"
                  << "  \033[32m[1]\033[0m Ornamental\n"
                  << "  \033[33m[2]\033[0m Frutifera\n\n";
        int tipo = inputInt("  Escolha: ");

        std::string nome  = inputStr("  Nome da planta      : ");
        std::string local = inputStr("  Localizacao         : ");
        double preco      = inputDouble("  Preco (R$)          : ");
        Data data         = inputData("  Data plantio (D/M/A): ");
        double umidade    = inputDouble("  Umidade ideal (%)   : ");
        int diasRega      = inputInt("  Dias entre regas    : ");
        int fios          = inputInt("  Qtd fios de cabelo  : ");

        if (tipo == 1) {
            std::string corFlor = inputStr("  Cor da flor         : ");
            std::string flBool  = inputStr("  Floresce? (s/n)     : ");
            bool fl = (flBool == "s" || flBool == "S");
            enfileirar(std::make_unique<PlantaOrnamental>(
                nome, local, preco, data, umidade, diasRega, fios, corFlor, fl));
        } else {
            std::string fruto = inputStr("  Tipo de fruto       : ");
            int meses         = inputInt("  Meses ate colheita  : ");
            double prod       = inputDouble("  Producao anual (kg) : ");
            enfileirar(std::make_unique<PlantaFrutifera>(
                nome, local, preco, data, umidade, diasRega, fios, fruto, meses, prod));
        }

        std::cout << "\033[32m\n  Planta inserida na fila (std::queue) com sucesso!\033[0m\n";
        pausar();
    }

    // ── 2. LISTAR TODOS ────────────────────────────────────────
    void listarTodos() const {
        limparTela();
        cabecalho("LISTAR TODAS AS PLANTAS");

        if (plantas.empty()) {
            std::cout << "\033[31m  Nenhuma planta cadastrada.\033[0m\n";
            pausar(); return;
        }

        auto v = getVectorView();

        double totalInvestido = 0;
        int nOrnamental = 0, nFrutifera = 0;
        for (auto* p : v) {
            totalInvestido += p->getPreco();
            if (p->getTipo() == "Ornamental") nOrnamental++;
            else nFrutifera++;
        }
        std::cout << "  \033[1;34mDASHBOARD\033[0m\n";
        std::cout << "  Total plantas   : \033[1;36m" << v.size() << "\033[0m\n";
        std::cout << "  Total investido : \033[1;33mR$ " << std::fixed
                  << std::setprecision(2) << totalInvestido << "\033[0m\n";
        std::cout << "  Ornamentais     : \033[32m" << nOrnamental << "\033[0m\n";
        std::cout << "  Frutifera       : \033[33m" << nFrutifera << "\033[0m\n";
        linha();

        for (int i = 0; i < (int)v.size(); i++) {
            std::cout << "\033[90m  [" << i << "]\033[0m ";
            v[i]->exibeVaca();
        }
        pausar();
    }

    // ── 3. EXIBIR UM ───────────────────────────────────────────
    void exibirUm() {
        limparTela();
        cabecalho("PESQUISAR PLANTA POR NOME");
        std::string nome = inputStr("  Nome a pesquisar: ");
        int idx = Pesquisar(nome);
        if (idx < 0) { pausar(); return; }
        linha();
        getVectorView()[idx]->exibir();
        pausar();
    }

    // ── 4. ALTERAR ─────────────────────────────────────────────
    void alterar() {
        limparTela();
        cabecalho("ALTERAR PLANTA");
        std::string nome = inputStr("  Nome a pesquisar: ");
        int idx = Pesquisar(nome);
        if (idx < 0) { pausar(); return; }

        auto v = getVectorView();
        linha();
        std::cout << "\033[90m  Planta atual:\033[0m\n";
        v[idx]->exibir();
        linha();
        std::cout << "  \033[33mDeixe em branco para manter o valor atual.\033[0m\n\n";

        std::string nNome  = inputStr("  Novo nome         [" + v[idx]->getNome() + "]: ");
        std::string nLocal = inputStr("  Nova localizacao  [" + v[idx]->getLocalizacao() + "]: ");
        std::string nPreco = inputStr("  Novo preco        [" + std::to_string(v[idx]->getPreco()) + "]: ");
        std::string nUmid  = inputStr("  Nova umidade %    [" + std::to_string(v[idx]->getUmidadeIdeal()) + "]: ");
        std::string nDias  = inputStr("  Novos dias/rega   [" + std::to_string(v[idx]->getDiasEntreRega()) + "]: ");
        std::string nFios  = inputStr("  Novos fios cabelo [" + std::to_string(v[idx]->getQtdFiosDeCabelo()) + "]: ");

        if (!nNome.empty())  v[idx]->setNome(nNome);
        if (!nLocal.empty()) v[idx]->setLocalizacao(nLocal);
        if (!nPreco.empty()) v[idx]->setPreco(std::stod(nPreco));
        if (!nUmid.empty())  v[idx]->setUmidadeIdeal(std::stod(nUmid));
        if (!nDias.empty())  v[idx]->setDiasEntreRega(std::stoi(nDias));
        if (!nFios.empty())  v[idx]->setQtdFiosDeCabelo(std::stoi(nFios));

        if (auto* o = dynamic_cast<PlantaOrnamental*>(v[idx])) {
            std::string nCor = inputStr("  Nova cor flor     [" + o->getCorFlor() + "]: ");
            std::string nFl  = inputStr("  Floresce? s/n     [" + std::string(o->getFloresce() ? "s" : "n") + "]: ");
            if (!nCor.empty()) o->setCorFlor(nCor);
            if (!nFl.empty())  o->setFloresce(nFl == "s" || nFl == "S");
        } else if (auto* f = dynamic_cast<PlantaFrutifera*>(v[idx])) {
            std::string nFruto = inputStr("  Novo tipo fruto   [" + f->getTipoDeFruto() + "]: ");
            std::string nMeses = inputStr("  Meses colheita    [" + std::to_string(f->getMesesAteColheita()) + "]: ");
            std::string nProd  = inputStr("  Producao kg/ano   [" + std::to_string(f->getProducaoKg()) + "]: ");
            if (!nFruto.empty())  f->setTipoDeFruto(nFruto);
            if (!nMeses.empty())  f->setMesesAteColheita(std::stoi(nMeses));
            if (!nProd.empty())   f->setProducaoKg(std::stod(nProd));
        }

        std::cout << "\033[32m\n  Planta atualizada!\033[0m\n";
        pausar();
    }

    // ── 5. REMOVER ─────────────────────────────────────────────
    void remover() {
        limparTela();
        cabecalho("REMOVER PLANTA");
        std::string nome = inputStr("  Nome a remover: ");
        int idx = Pesquisar(nome);
        if (idx < 0) { pausar(); return; }

        auto v = getVectorView();
        std::cout << "\n  Planta selecionada: \033[1;31m" << v[idx]->getNome() << "\033[0m\n";
        std::string conf = inputStr("  Confirmar remocao? (s/n): ");
        if (conf == "s" || conf == "S") {
            removerDaQueue(idx);
            std::cout << "\033[32m\n  Planta removida da fila!\033[0m\n";
        } else {
            std::cout << "\033[33m  Operacao cancelada.\033[0m\n";
        }
        pausar();
    }

    // ── 6. RELATORIO ───────────────────────────────────────────
    void exibirRelatorio() const {
        limparTela();
        cabecalho("RELATORIO DO JARDIM");

        auto v = getVectorView();
        int    total       = v.size();
        int    nOrnamental = 0, nFrutifera = 0;
        double totalPreco  = 0, precoOrnamental = 0, precoFrutifera = 0;
        double totalProd   = 0;
        long   totalFios   = 0;
        int    maxMeses    = 0;

        for (auto* p : v) {
            totalPreco += p->getPreco();
            totalFios  += p->getQtdFiosDeCabelo();
            if (dynamic_cast<const PlantaOrnamental*>(p)) {
                nOrnamental++; precoOrnamental += p->getPreco();
            } else if (auto* f = dynamic_cast<const PlantaFrutifera*>(p)) {
                nFrutifera++;
                precoFrutifera += p->getPreco();
                totalProd      += f->getProducaoKg();
                if (f->getMesesAteColheita() > maxMeses)
                    maxMeses = f->getMesesAteColheita();
            }
        }

        std::cout << "  Quantidade total de plantas : \033[1;36m" << total << "\033[0m\n";
        std::cout << "  Valor total investido       : \033[1;33mR$ "
                  << std::fixed << std::setprecision(2) << totalPreco << "\033[0m\n";
        std::cout << "  Total fios de cabelo        : \033[35m" << totalFios << "\033[0m\n\n";

        linha();
        std::cout << "  \033[32mPlantas Ornamentais\033[0m\n";
        std::cout << "     Quantidade  : " << nOrnamental << "\n";
        std::cout << "     Valor total : R$ " << std::fixed << std::setprecision(2) << precoOrnamental << "\n";
        if (nOrnamental > 0)
            std::cout << "     Valor medio : R$ " << (precoOrnamental / nOrnamental) << "\n";

        linha();
        std::cout << "  \033[33mPlantas Frutifera\033[0m\n";
        std::cout << "     Quantidade       : " << nFrutifera << "\n";
        std::cout << "     Valor total      : R$ " << std::fixed << std::setprecision(2) << precoFrutifera << "\n";
        std::cout << "     Producao total/a : " << std::setprecision(1) << totalProd << " kg\n";
        if (nFrutifera > 0)
            std::cout << "     Maior espera     : " << maxMeses << " meses\n";

        linha();
        // Req 9: quantidade de Girafas armazenadas na queue
        std::cout << "  \033[1;35mGirafas armazenadas na fila (std::queue) : " << total << "\033[0m\n\n";

        pausar();
    }

    // ── 8. VIAJAR PARA A LUA ───────────────────────────────────
    void viajarParaALua() const {
        limparTela();
        cabecalho("VIAGEM PARA A LUA");
        std::cout << "\n"
                  << "         *     .        .       .       *\n"
                  << "    .  .    *    .  * .    .  .\n"
                  << "  .   *   .   *    .   *  .   *   .\n"
                  << "         ___\n"
                  << "        /   \\\n"
                  << "       | o o |    Levando todas as plantas!\n"
                  << "        \\___/\n"
                  << "       /|   |\\\n"
                  << "      / |   | \\\n"
                  << "        |   |\n"
                  << "       / \\ / \\\n\n";
        std::cout << "  Destino   : Mare Tranquillitatis (Lua)\n";
        std::cout << "  Distancia : ~384.400 km\n";
        std::cout << "  Carga     : " << size() << " plantas na fila + muitos fios de cabelo\n";
        pausar();
    }

    // ── PERSISTENCIA ───────────────────────────────────────────
    void salvarEmArquivo() const {
        std::ofstream arq(arquivoDados);
        if (!arq.is_open()) { std::cerr << "  Erro ao salvar arquivo.\n"; return; }
        auto v = getVectorView();
        for (auto* p : v)
            arq << p->serialize() << "\n";
        arq.close();
    }

    void carregarDeArquivo() {
        std::ifstream arq(arquivoDados);
        if (!arq.is_open()) return;

        std::string linha;
        while (std::getline(arq, linha)) {
            if (linha.empty()) continue;
            std::istringstream iss(linha);
            std::string token;
            std::vector<std::string> partes;
            while (std::getline(iss, token, '|'))
                partes.push_back(token);

            if (partes.size() < 10) continue;
            if (partes[0] != "Vaca") continue;
            if (partes.back() != "Girafa") continue;

            std::string tipo    = partes[1];
            std::string nome    = partes[2];
            std::string local   = partes[3];
            double      preco   = std::stod(partes[4]);
            Data        data    = Data::deserialize(partes[5]);
            double      umidade = std::stod(partes[6]);
            int         diasR   = std::stoi(partes[7]);
            int         fios    = std::stoi(partes[8]);

            if (tipo == "Ornamental" && partes.size() >= 12) {
                std::string corFlor = partes[9];
                bool fl = (partes[10] == "1");
                enfileirar(std::make_unique<PlantaOrnamental>(
                    nome, local, preco, data, umidade, diasR, fios, corFlor, fl));
            } else if (partes.size() >= 13) {
                std::string fruto = partes[9];
                int    meses = std::stoi(partes[10]);
                double prod  = std::stod(partes[11]);
                enfileirar(std::make_unique<PlantaFrutifera>(
                    nome, local, preco, data, umidade, diasR, fios, fruto, meses, prod));
            }
        }
        arq.close();
    }

    // ── MENU PRINCIPAL ─────────────────────────────────────────
    void executar() {
        carregarDeArquivo();

        while (true) {
            limparTela();
            std::cout << "\033[1;32m"
                      << "  +--------------------------------------------------+\n"
                      << "  |     JARDIM INTELIGENTE  -- CRUD SYSTEM            |\n"
                      << "  +--------------------------------------------------+\n"
                      << "  |  \033[1;36m[1]\033[1;32m Inserir nova planta                           |\n"
                      << "  |  \033[1;36m[2]\033[1;32m Listar todas                                  |\n"
                      << "  |  \033[1;36m[3]\033[1;32m Exibir uma (pesquisar por nome)               |\n"
                      << "  |  \033[1;36m[4]\033[1;32m Alterar (pesquisar por nome)                  |\n"
                      << "  |  \033[1;36m[5]\033[1;32m Remover (pesquisar por nome)                  |\n"
                      << "  |  \033[1;36m[6]\033[1;32m Exibir relatorio                              |\n"
                      << "  |  \033[1;36m[7]\033[1;32m Sair                                          |\n"
                      << "  |  \033[1;36m[8]\033[1;32m Viajar para a Lua                             |\n"
                      << "  |  \033[1;31m[Z]\033[1;32m Sair (salvar e fechar)                        |\n"
                      << "  +--------------------------------------------------+\033[0m\n\n";
            std::cout << "  \033[33mPlantas na fila (std::queue): \033[1;36m" << size() << "\033[0m\n\n";

            std::cout << "  \033[33mOpcao: \033[0m";
            std::string op;
            std::getline(std::cin, op);
            if (op.empty()) continue;

            char c = op[0];

            if (c == 'Z' || c == 'z' || c == '7') {
                salvarEmArquivo();
                limparTela();
                std::cout << "\033[1;32m\n  Dados salvos em \"" << arquivoDados << "\"\n";
                std::cout << "  Ate logo! O seu jardim esta em boas maos.\033[0m\n\n";
                break;
            }

            switch (c) {
                case '1': inserir();         break;
                case '2': listarTodos();     break;
                case '3': exibirUm();        break;
                case '4': alterar();         break;
                case '5': remover();         break;
                case '6': exibirRelatorio(); break;
                case '8': viajarParaALua();  break;
                default:
                    std::cout << "\033[31m  Opcao invalida!\033[0m\n";
                    pausar();
            }
        }
    }
};
