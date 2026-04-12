# Order Book System

![C++](https://img.shields.io/badge/language-C++-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Status](https://img.shields.io/badge/status-academic--project-lightgrey)

Sistema de simulação de um **Order Book** financeiro desenvolvido em C++ sem uso da STL, utilizando **heaps implementados manualmente** e **controle explícito de memória**.

---

## Descrição

O sistema gerencia ordens de compra e venda e executa automaticamente transações quando há compatibilidade entre preços.

Cada ordem possui:

- identificador (`id`)
- tipo (`B` para compra, `S` para venda)
- preço
- timestamp (prioridade temporal)

Quando uma nova ordem é submetida, o sistema verifica a melhor ordem oposta. Caso haja compatibilidade, a transação é executada imediatamente; caso contrário, a ordem é inserida na estrutura apropriada.

---

## Organização Interna dos Dados

Os dados são organizados em três estruturas principais:

- heap de compras (`buy_orders`) — **max-heap**
- heap de vendas (`sell_orders`) — **min-heap**
- array dinâmico de transações (`transactions`)

### Estrutura geral
```
OrderBook
│
├── Buy Heap (max-heap)
│ ├── Order*
│ └── ...
│
├── Sell Heap (min-heap)
│ ├── Order*
│ └── ...
│
└── Transactions
├── Transaction*
└── ...
```

- O heap de compras prioriza **maior preço**
- O heap de vendas prioriza **menor preço**
- Empates são resolvidos pelo **menor timestamp**
- As estruturas são **arrays dinâmicos redimensionados automaticamente**

---

## Funcionamento

### Inserção de ordens (`submit`)

Ordem de compra (`B`):

- Se não há vendas → entra no heap de compras
- Se `preço_compra ≥ menor_preço_venda` → executa transação
- Caso contrário → inserida no heap de compras

Ordem de venda (`S`):

- Se não há compras → entra no heap de vendas
- Se `preço_venda ≤ maior_preço_compra` → executa transação
- Caso contrário → inserida no heap de vendas

O preço da transação é sempre o da ordem **que já estava no sistema**, respeitando a prioridade temporal.

---

## Execução de Transações

Quando há compatibilidade entre as ordens:

1. Cria-se uma `Transaction`
2. Remove-se a raiz do heap oposto
3. O heap é reorganizado com `siftDown`
4. A transação é armazenada no array dinâmico

---

## Estruturas Utilizadas

### Heap de Compras (Max-Heap)

Prioridade:
```
maior preço > menor preço
empate → menor timestamp
```

---

### Heap de Vendas (Min-Heap)

Prioridade:
```
menor preço < maior preço
empate → menor timestamp
```

---

## Operações

- Inserção (`insertBuy`, `insertSell`)
- Reorganização ascendente (`siftUp`)
- Reorganização descendente (`siftDown`)
- Cancelamento de ordem (`cancel`)
- Consulta (`getBuyOrders`, `getSellOrders`, `getTransactions`)
- Registro de transações (`insertTransaction`)

---

## Cancelamento de Ordens

O cancelamento é realizado em três etapas:

1. Busca linear pelo `id`
2. Substituição pelo último elemento da heap
3. Reorganização com `siftDown` e `siftUp`

Essa abordagem mantém a propriedade da heap sem necessidade de reconstrução completa.

---

## Complexidade

| Operação | Complexidade |
|---------|-------------|
| `submit()` | O(log n) |
| inserção na heap | O(log n) |
| remoção da raiz | O(log n) |
| `cancel()` | O(n) + O(log n) |
| `get*()` | O(n) |
| stress test (n operações) | O(n log n) |

---

## Detalhes de Implementação

- Heaps implementados manualmente
- Arrays dinâmicos com **capacity doubling**
- Uso de **ponteiro de ponteiro (`Order**`)**
- Trocas feitas apenas com ponteiros
- Controle explícito de memória (`new` / `delete`)
- Sem uso de STL (`vector`, `priority_queue`, etc.)
- Timestamp usado como critério de desempate
- Transações armazenadas dinamicamente

---

## Alternativas Consideradas

- Lista encadeada ordenada  
  - implementação mais simples  
  - inserção O(n)

- Heap com índice auxiliar (map id → posição)  
  - cancelamento O(log n)  
  - maior complexidade e uso de memória

- Array ordenado  
  - busca eficiente  
  - inserção O(n)

---

## Trade-offs

- Heap favorece `submit()` em detrimento de `cancel()`
- Busca linear no cancel simplifica implementação
- Arrays dinâmicos permitem acesso indexado eficiente
- Uso de ponteiros evita cópias de objetos
- `submit()` recebe ordem por valor → cópia extra
- Gerenciamento manual aumenta controle, mas exige cuidado

---

## Testes

O arquivo `main.cpp` contém cenários de teste para:

- construção dos heaps
- inserção de ordens
- execução automática de transações
- cancelamento de ordens
- reorganização após remoção
- stress test com grande volume de operações
- validação das prioridades preço/tempo

---

## Compilação

```bash
g++ -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -std=c++17 \
main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o orderbook