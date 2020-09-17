# Trabalho Prático 1

## Árvores binárias compartilhadas
Na primeira parte do curso discutimos abstrações e técnicas de construção de programas que usam threads e sincronização em memória compartilhada. Neste trabalho, vamos colocar esses conceitos em prática em um contexto realista.

O trabalho pode ser feito individualmente ou em dupla.

Objetivo
Implementar uma árvore binária que funcione em um ambiente de threads com eficiência.

Discussão
Em um ambiente de múltiplas threads, uma árvore binária se torna um recurso compartilhado que pode, potencialmente, ser usado paralelamente por todas as threads. Para isso, é importante entender como cada thread e cada operação sobre a árvore podem interagir umas com as outras. 

Um forma simplista de se tornar uma árvore binária segura para operação com múltiplas threads (em inglês, o termo usado é "thread-safe") seria colocar uma mutex ao redor de toda a árvore. Obviamente, essa solução leva a execuções corretas, mas limita excessivamente o grau de paralelismo que poderia ser obtido no sistema. Por exemplo, operações de busca não afetam a estrutura árvore e poderiam ser realizadas concorrentemente. Por outro lado, operações de inserção e remoção afetam a estrutura da árvore e exigem mais cuidado.

Uma outra solução seria aplicar o princípio dos leitores e escritores à árvore como um todo: qualquer operação que altere ou dependa da estrutura completa da árvore teria que ser executada com exclusão mútua, mas operações de consulta ou outras que não alterem a árvore poderiam ser executadas em paralelo.

Mesmo uma solução baseada no modelo de leitores e escritores, se aplicada à árvore como um todo, ainda pode ser refinada. Em estruturas como a árvore binária, alterações são localizadas: nós são sempre inseridos em uma folha e remoções só afetam a sub-árvore a partir do nó removido. Sendo assim, mesmo alterações podem ser vistas como exigindo exclusão mútua apenas na sub-árvore afetada. E essa sub-árvore afetada vai mudando à medida que o executor caminha pela árvore em busca do local exato da modificaçào.

Por exemplo, se uma thread que vai remover um nó detecta que esse nó se encontra na sub-árvore da esquerda da raiz, a sub-árvore da direita pode ser acessada por outras threads de leitura ou mesmo de escrita. Essa observação sugere uma solução onde cada nó pode ser travado e leitores e escritores podem trabalhar de forma diferente.

Detalhamento da implementação
O objetivo é criar uma implementação de árvore binária que permita o maior grau de paralelismo no acesso compartilhado à mesma. Para isso, vamos partir de uma implementação de árvore binária já existente: a implementação fornecida para o livro "Projeto de Algoritmos com implementações em Pascal e C" do Prof. Nívio Ziviani. O site do livro já fornece o código para uma implementação de árvore binária que pode ser usado como ponto de partida.

Testes
Para fins de testes, sua implementação deve conter também a implementação de uma barreira de sincronização, definida como:

TBarreira bar;

void initBarreira( TBarreira* b, int n );

void barreira( &bar );

Como sugestão, considere criar uma versão do programa de testes fornecido com múltiplas threads. Pela forma como o código da implementação foi criado, certifique-se de que duas threads diferentes não vão tentar inserir/retirar o mesmo valor, para evitar casos de uma operação falhar.

Para ter um programa com maior desempenho, remova a maior parte das chamadas da função Testa() para obter um código mais eficiente. Aumente também o tamanho máximo da árvore criada, pelo menos, para dezenas de milhares de nós.

Use barreiras para separar as três fases do programa original: inserção/remoção+busca+inserção/remoção final. Meça o número de operações por segundo para cada fase.

O que deve ser entregue
Você deve reorganizar o código fornecido em arquivos .h e .c da forma que julgar mais adequado para permitir que sua árvore seja linkada com outros programas, para fins de testes. Idealmente, a assinatura das funções não deve ser alterada, apenas os tipos utilizados, que podem ser expandidos.

Junto com esse código deve ser entregue um makefile e pelo menos um programa principal que possa ser compilado e executado usando make run. O código deve ser anotado com comentários que explicitem os pontos onde a sincronização atua e como isso ocorre.

Além dos arquivos de código deve ser entregue um relatório em PDF com o detalhamento da implementação. Em particular, o relatório deve explicar o raciocínio por trás da solução adotada de forma clara. O relatório e os comentários no código não devem ser simplesmente duas cópias do mesmo conteúdo: vocês devem considerar que o relatório dá a descrição geral do que foi feito e justifica as decisões tomadas, enquanto os comentários basicamente auxiliam na leitura do código, considerando que o leitor já leu o relatório.

Orientações gerais
O trabalho deve ser entregue como um arquivo .zip ou .tar.gz contendo todos os arquivos fonte utilizados e o PDF do relatório. Não inclua arquivos executáveis, nem arquivos objeto (.o). 

Farão parte dos critérios de avaliação a qualidade da documentação e do código apresentado, bem como o grau de paralelismo oferecido pela solução desenvolvida. Seu código deve funcionar sem alterações nas máquinas linux do laboratório de micros do DCC/UFMG. 

Dúvidas podem ser sanadas usando o fórum específico criado no moodle para esse trabalho. Não é permitido postar trechos de código ou detalhes de implementação no fórum. Se sua pergunta exige o fornecimento desses detalhes, envie-a por e-mail direto para o professor.