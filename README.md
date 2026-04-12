# Order Book System

![C++](https://img.shields.io/badge/language-C++-blue)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Status](https://img.shields.io/badge/status-academic--project-lightgrey)

Sistema de simulação de um **Order Book** financeiro desenvolvido em C++.

---

## Descrição

O sistema gerencia ordens de compra e venda e executa automaticamente transações quando há compatibilidade entre preços.

Cada ordem possui:

- identificador (`id`)
- tipo (`B` para compra, `S` para venda)
- preço
- timestamp (prioridade temporal)

O projeto foi desenvolvido sem uso da STL, com foco em eficiência e controle manual de memória.

---

## Organização Interna dos Dados

Os dados são organizados em três estruturas principais:

- heap de compras (`buy_orders`)
- heap de vendas (`sell_orders`)
- lista de transações (`transactions`)

### Estrutura geral:

```
OrderBook
│
├── Buy Heap (max-heap)
│   ├── Order*
│   └── ...
│
├── Sell Heap (min-heap)
│   ├── Order*
│   └── ...
│
└── Transactions
    ├── Transaction*
    └── ...
```

- O heap de compras prioriza **maior preço**
- O heap de vendas prioriza **menor preço**
- Em caso de empate, usa-se o **menor timestamp**

---

## Funcionamento

### Inserção de ordens (`submit`)

- Ordem de compra (`B`):
  - Se não há vendas → entra no heap de compras
  - Se `preço_compra ≥ menor_preço_venda` → executa transação
  - Caso contrário → entra no heap

- Ordem de venda (`S`):
  - Se não há compras → entra no heap de vendas
  - Se `preço_venda ≤ maior_preço_compra` → executa transação
  - Caso contrário → entra no heap

---

## Execução de Transações

Quando há compatibilidade:

- Cria uma `Transaction`
- Remove a melhor ordem oposta (raiz do heap)
- Reorganiza o heap com `siftDown`

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
- Remoção do topo (`siftDown`)
- Reorganização (`siftUp`)
- Cancelamento (`cancel`)
- Consulta (`getBuyOrders`, `getSellOrders`, `getTransactions`)

---

## Complexidade

| Operação        | Complexidade |
|----------------|------------|
| `submit()`     | O(log n)   |
| inserção heap  | O(log n)   |
| remoção topo   | O(log n)   |
| `cancel()`     | O(n)       |
| `get()`        | O(n)       |

---

## Detalhes de Implementação

- Heaps implementados manualmente com arrays dinâmicos
- Redimensionamento dobrando a capacidade
- Uso de ponteiros (`Order*`, `Transaction*`)
- Controle explícito de memória (`new` / `delete`)
- Não utiliza STL (`vector`, `priority_queue`, etc.)

---

## Testes

O arquivo `main.cpp` contém diversos cenários:

- construção e validação dos heaps
- execução de transações
- cancelamento de ordens
- reorganização após remoção
- stress test com milhares de operações

---

## Compilação

```bash
g++ -Wall -Wextra -Werror -Wshadow -Wpedantic -Wconversion -std=c++17 main.cpp OrderBook.cpp Order.cpp -o orderbook
```

---
