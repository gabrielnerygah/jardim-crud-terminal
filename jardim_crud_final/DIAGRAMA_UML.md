# Diagrama UML de Classes — Jardim Inteligente CRUD

```
┌─────────────────────────────────────────────────────────────────────────────────────────┐
│                          DIAGRAMA DE CLASSES — JARDIM CRUD                               │
└─────────────────────────────────────────────────────────────────────────────────────────┘

                        ┌───────────────────────────────┐
                        │            <<Classe>>          │
                        │              Vaca              │
                        ├───────────────────────────────┤
                        │ # qtdFiosDeCabelo : int        │
                        ├───────────────────────────────┤
                        │ + Vaca(fios: int)              │
                        │ + getQtdFiosDeCabelo(): int    │
                        │ + setQtdFiosDeCabelo(int)      │
                        │ + exibeVaca(): void <<virtual>>│
                        │ + getTipo(): string <<virtual>>│
                        └───────────────┬───────────────┘
                                        │ herança
                                        │
                        ┌───────────────▼───────────────────────────────┐
                        │              <<Classe>>                        │
                        │               Planta                           │
                        ├───────────────────────────────────────────────┤
                        │ # nome         : string                        │
                        │ # localizacao  : string                        │
                        │ # preco        : double                        │
                        │ # dataPlantio  : Data      ◆──── composição    │
                        │ # umidadeIdeal : double                        │
                        │ # diasEntreRega: int                           │
                        ├───────────────────────────────────────────────┤
                        │ + Planta(nome, loc, preco, data, umid, dias,  │
                        │          fios)                                 │
                        │ + getNome(): string                            │
                        │ + getLocalizacao(): string                     │
                        │ + getPreco(): double                           │
                        │ + getDataPlantio(): Data&                      │
                        │ + getUmidadeIdeal(): double                    │
                        │ + getDiasEntreRega(): int                      │
                        │ + setNome(string)                              │
                        │ + setLocalizacao(string)                       │
                        │ + setPreco(double)                             │
                        │ + getTipo(): string <<override>>               │
                        │ + getCor(): string <<virtual>>                 │
                        │ + exibeVaca(): void <<override>>               │ ← sobrescreve Req 7
                        │ + exibir(): void <<virtual>>                   │
                        │ + serialize(): string <<virtual>>              │
                        └────────────┬─────────────┬─────────────────────┘
                                     │              │
                      herança        │              │    herança
              ┌──────────────────────┘              └──────────────────────┐
              │                                                             │
┌─────────────▼───────────────────────┐       ┌──────────────────────────▼──────────────┐
│          PlantaOrnamental            │       │            PlantaFrutifera               │
├──────────────────────────────────────┤       ├─────────────────────────────────────────┤
│ - corFlor   : string                 │       │ - tipoDeFruto       : string             │
│ - floresce  : bool                   │       │ - mesesAteColheita  : int                │
├──────────────────────────────────────┤       │ - producaoKgPorAno  : double             │
│ + PlantaOrnamental(nome, loc, preco, │       ├─────────────────────────────────────────┤
│   data, umid, dias, fios,            │       │ + PlantaFrutifera(nome, loc, preco,      │
│   corFlor, floresce)                 │       │   data, umid, dias, fios,                │
│ + getCorFlor(): string               │       │   fruto, meses, producao)                │
│ + getFloresce(): bool                │       │ + getTipoDeFruto(): string               │
│ + setCorFlor(string)                 │       │ + getMesesAteColheita(): int              │
│ + setFloresce(bool)                  │       │ + getProducaoKg(): double                │
│ + getTipo(): string <<override>>     │       │ + setTipoDeFruto(string)                 │
│ + getCor(): string <<override>>      │       │ + setMesesAteColheita(int)               │
│   → retorna Verde Sálvia             │       │ + setProducaoKg(double)                  │
│ + exibeVaca(): void <<override>>     │       │ + getTipo(): string <<override>>         │
│ + exibir(): void <<override>>        │       │ + getCor(): string <<override>>           │
│ + serialize(): string <<override>>   │       │   → retorna Terracota                    │
└──────────────────────────────────────┘       │ + exibeVaca(): void <<override>>         │
                                               │ + exibir(): void <<override>>            │
                                               │ + serialize(): string <<override>>       │
                                               └─────────────────────────────────────────┘

  ┌───────────────────────────────────────┐
  │            <<Classe>>                  │
  │               Data        (composição) │
  ├───────────────────────────────────────┤
  │ - dia : int                            │
  │ - mes : int                            │
  │ - ano : int                            │
  ├───────────────────────────────────────┤
  │ + Data(dia, mes, ano)                  │
  │ + getDia(): int                        │
  │ + getMes(): int                        │
  │ + getAno(): int                        │
  │ + toString(): string                   │
  │ + serialize(): string                  │
  │ + deserialize(string): Data <<static>> │
  └───────────────────────────────────────┘

  ┌────────────────────────────────────────────────────────────────────────────┐
  │                         <<Classe Gerenciadora>>                             │
  │                              GirafaRosa    (Req 8)                          │
  ├────────────────────────────────────────────────────────────────────────────┤
  │ - plantas      : vector<unique_ptr<Planta>>   ← polimorfismo / Req 5/6     │
  │ - arquivoDados : string                                                     │
  ├────────────────────────────────────────────────────────────────────────────┤
  │ + Pesquisar(nome: string): int          ← reutilizado em 3, 4 e 5          │
  │ + inserir(): void            (Create)                                       │
  │ + listarTodos(): void        (Read)                                         │
  │ + exibirUm(): void           (Read)                                         │
  │ + alterar(): void            (Update)                                       │
  │ + remover(): void            (Delete)                                       │
  │ + exibirRelatorio(): void                                                   │
  │ + viajarParaALua(): void                                                    │
  │ + salvarEmArquivo(): void               ← chamado ao sair (Req 11)          │
  │ + carregarDeArquivo(): void             ← chamado ao iniciar (Req 11)       │
  │ + executar(): void                      ← loop principal até 'Z' (Req 10)  │
  └────────────────────────────────────────────────────────────────────────────┘

─────────────────────────────────────────────────────────────────────────────────
 RELAÇÕES:
 ◆  Composição : Planta ◆──── Data        (Planta tem uma Data como atributo)
 ▲  Herança    : Planta ──▲── Vaca
 ▲  Herança    : PlantaOrnamental ──▲── Planta
 ▲  Herança    : PlantaFrutifera  ──▲── Planta
 ○  Uso        : GirafaRosa ──○── Planta (via vector<unique_ptr<Planta>>)
─────────────────────────────────────────────────────────────────────────────────

 MAPEAMENTO DE REQUISITOS:
 Req  1  → GirafaRosa: inserir, listarTodos, exibirUm, alterar, remover, exibirRelatorio
 Req  3  → Planta tem ≥4 atributos; Data é composição; qtdFiosDeCabelo é obrigatório
 Req  4  → Herança: Vaca ← Planta ← PlantaOrnamental / PlantaFrutifera
 Req  5  → vector<unique_ptr<Planta>> com polimorfismo (std::queue semanticamente)
 Req  7  → exibeVaca() sobrescrito em Planta, Ornamental e Frutifera
 Req  8  → Classe GirafaRosa gerencia todo o CRUD
 Req  9  → GirafaRosa::exibirRelatorio() com contagem de Girafas armazenadas
 Req 10  → Loop while(true) no GirafaRosa::executar(), sai com 'Z'
 Req 11  → carregarDeArquivo() ao iniciar; salvarEmArquivo() ao sair
           Cada linha começa com "Vaca" e termina com "Girafa"
```
