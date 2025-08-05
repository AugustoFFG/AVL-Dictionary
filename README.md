# AVL-Dictionary
<img src="https://www.cefet-rj.br/attachments/article/431/vert_azul.png" alt="Logo do Projeto" width="200" style="display: block; margin: auto;"/>

- [Augusto Freitas](https://github.com/AugustoFFG) 
- [Felipe Katsumoto](https://github.com/FeKatsu)

Curso de Engenharia de Computação - CEFET/RJ Uned Petrópolis.

Disciplina AEDs II - Professora Laura Assis

[Relatório completo](./Relatorio_AugustoF_FelipeH_AEDSII_Trab1_2024-2.pdf)
## 📖 Resumo
Este projeto foi desenvolvido como parte fundamental da disciplina de Algoritmos e Estrutura de Dados II, disciplina obrigatória do curso de **Engenharia de Computação** no **Centro Federal de Educação Tecnológica Celso Suckow da Fonseca (CEFET-RJ)**.

Este trabalho apresenta um programa que implementa um dicionário utilizando uma árvore AVL. O dicionário permite operações comuns, como criação de uma árvore vazia, remoção de palavras, inserção de palavras e seus significados, busca por palavras e impressão da estrutura atual da árvore. 

O programa foi desenvolvido considerando uma interface interativa que permite ao usuário inserir palavras e seus significados, pesquisar termos cadastrados, remover entradas e visualizar a árvore resultante. A cada operação de inserção e remoção, o programa ajusta automaticamente a árvore para manter seu balanceamento

## 🌳 O que é uma árvore AVL? 
Uma árvore AVL é uma estrutura de dados do tipo árvore binária de busca (BST) autobalanceada, onde a diferença de altura (fator de balanceamento) entre as subárvores esquerda e direita de qualquer nó é, no máximo, 1.
Esse balanceamento garante que as operações de inserção, remoção e busca tenham complexidade O(log n) no pior caso.

O nome AVL vem dos seus criadores Adelson-Velsky e Landis.

por meio de operações de troca de ponteiros, conhecidas como rotações (RR, RL, LL, LR), a fim de alcançar um custo de algoritmo com o tempo de pesquisa tendendo a O(log n).

## ⚙️ Funcionalidades
- Inserção de palavras e significados
- Busca por palavras
- Remoção de palavras
- Impressão da árvore em ordem
- Balanceamento automático (com rotações)
- Menu interativo
- Execução via terminal ou por arquivos de entrada
