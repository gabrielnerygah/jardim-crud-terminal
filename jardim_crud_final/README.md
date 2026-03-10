# 🌿 Jardim Inteligente — Sistema CRUD em C++17

Sistema CRUD de gerenciamento de plantas para jardim, com interface de terminal colorida (Dark Mode neon) e persistência automática em arquivo.

## 📁 Estrutura do Projeto

```
jardim_crud/
├── include/
│   ├── Data.h              ← Composição: representa data de plantio
│   ├── Vaca.h              ← Superclasse base obrigatória
│   ├── Planta.h            ← Superclasse principal (herda Vaca)
│   ├── PlantaOrnamental.h  ← Subclasse 1
│   ├── PlantaFrutifera.h   ← Subclasse 2
│   └── GirafaRosa.h        ← Gerenciadora CRUD (Req 8)
├── src/
│   └── main.cpp            ← Ponto de entrada
├── DIAGRAMA_UML.md         ← Diagrama de classes
└── README.md               ← Este arquivo
```

## 🔨 Como Compilar (sem CMake)

### Linux / macOS
```bash
g++ -std=c++17 -Wall -Iinclude src/main.cpp -o jardim
./jardim
```

### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Iinclude src/main.cpp -o jardim.exe
jardim.exe
```

### VS Code — tasks.json
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compilar Jardim",
            "type": "shell",
            "command": "g++",
            "args": ["-std=c++17", "-Wall", "-Iinclude", "src/main.cpp", "-o", "jardim"],
            "group": { "kind": "build", "isDefault": true }
        }
    ]
}
```

## 📋 Mapa de Requisitos

| Req | Descrição | Implementação |
|-----|-----------|---------------|
| 1   | Menu CRUD com 8 opções | `GirafaRosa::executar()` |
| 3   | ≥4 atributos + composição | `Planta` + `Data` |
| 4   | Herança 1 super / 2 sub | `Vaca → Planta → {Ornamental, Frutífera}` |
| 5   | Lista com polimorfismo | `vector<unique_ptr<Planta>>` |
| 7   | Sobrescreve `exibeVaca()` | Em todas as subclasses |
| 8   | Classe gerenciadora | `GirafaRosa` |
| 9   | Relatório c/ qtd Girafas | `GirafaRosa::exibirRelatorio()` |
| 10  | Loop até opção 'Z' | `while(true)` em `executar()` |
| 11  | Persistência em arquivo | `carregarDeArquivo()` / `salvarEmArquivo()` |

## 💾 Formato do Arquivo de Dados

Cada linha começa com `Vaca` e termina com `Girafa` (Req 11):

```
Vaca|Ornamental|nome|local|preco|dia,mes,ano|umidade|diasRega|fios|corFlor|floresce|Girafa
Vaca|Frutífera|nome|local|preco|dia,mes,ano|umidade|diasRega|fios|fruto|meses|producao|Girafa
```

## 🎮 Menu do Sistema

```
[1] Inserir nova planta
[2] Listar todas
[3] Exibir uma (pesquisar por nome)
[4] Alterar (pesquisar por nome)
[5] Remover (pesquisar por nome)
[6] Exibir relatório
[7] Sair
[8] Viajar para a Lua 🚀
[Z] Sair (salvar e fechar)
```

## 🌈 Comportamento Polimórfico

- **Ornamental** → exibe em Verde Sálvia `RGB(143,188,143)`
- **Frutífera** → exibe em Terracota `RGB(205,133,63)`
- `exibeVaca()` é chamado uniformemente no `listarTodos()` — cada subclasse imprime diferente
