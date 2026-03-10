#include "GirafaRosa.h"

int main() {
    // Configurar terminal para UTF-8 no Windows, se necessário
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    GirafaRosa gerenciador;
    gerenciador.executar();
    return 0;
}
