#include <stdio.h>
#include <string.h>
#include <locale.h>

// Função para o Menu Principal
void menuinicial()
{
    setlocale(LC_ALL, "");
    printf("----------Sistema de Gerenciamento----------\n");
    printf("| 1. Cadastrar Tarefa\n");
    printf("| 2. Listar Tarefas\n");
    printf("| 3. Editar Tarefa\n");
    printf("| 4. Excluir Tarefa\n");
    printf("| 5. Salvar Tarefas em Arquivo\n");
    printf("| 6. Sair\n");
    printf("Escolha uma opção: ");
}

// Função de cadastro
void TarefaCadastrada(char Tarefa[250][4][50], int *quantidade)
{
    setlocale(LC_ALL, "");

    if (*quantidade >= 250)
    {
        printf("Limite de tarefas alcançado.\n");
        return;
    }

    printf("Título: ");
    getchar(); // limpa buffer
    fgets(Tarefa[*quantidade][0], 50, stdin);
    Tarefa[*quantidade][0][strcspn(Tarefa[*quantidade][0], "\n")] = '\0';

    printf("Descrição: ");
    fgets(Tarefa[*quantidade][1], 50, stdin);
    Tarefa[*quantidade][1][strcspn(Tarefa[*quantidade][1], "\n")] = '\0';

    printf("Importância (Pouca, Média, Muita): ");
    fgets(Tarefa[*quantidade][2], 50, stdin);
    Tarefa[*quantidade][2][strcspn(Tarefa[*quantidade][2], "\n")] = '\0';

    printf("Situação (Inacabado, Finalizado): ");
    fgets(Tarefa[*quantidade][3], 50, stdin);
    Tarefa[*quantidade][3][strcspn(Tarefa[*quantidade][3], "\n")] = '\0';

    (*quantidade)++;

    printf("\nTarefa cadastrada com sucesso!\n");
}

// Função de listagem
void ListagemDaTarefa(char Tarefa[250][4][50], int quantidade)
{
    setlocale(LC_ALL, "");

    if (quantidade == 0)
    {
        printf("\nNenhuma Tarefa cadastrada.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        printf("Tarefa %d:\n", i + 1);
        printf("Título: %s\n", Tarefa[i][0]);
        printf("Descrição: %s\n", Tarefa[i][1]);
        printf("Importância: %s\n", Tarefa[i][2]);
        printf("Situação: %s\n\n", Tarefa[i][3]);
    }
}

// Função de edição
void EdicaoDaTarefa(char Tarefa[250][4][50], int indice)
{
    setlocale(LC_ALL, "");

    if (indice < 0 || indice >= 250 || strlen(Tarefa[indice][0]) == 0)
    {
        printf("\nÍndice inválido ou tarefa inexistente.\n");
        return;
    }

    printf("Editando tarefa %d\n", indice + 1);

    printf("Novo título: ");
    getchar();
    fgets(Tarefa[indice][0], 50, stdin);
    Tarefa[indice][0][strcspn(Tarefa[indice][0], "\n")] = '\0';

    printf("Nova descrição: ");
    fgets(Tarefa[indice][1], 50, stdin);
    Tarefa[indice][1][strcspn(Tarefa[indice][1], "\n")] = '\0';

    printf("Nova Importância: ");
    fgets(Tarefa[indice][2], 50, stdin);
    Tarefa[indice][2][strcspn(Tarefa[indice][2], "\n")] = '\0';

    printf("Nova Situação: ");
    fgets(Tarefa[indice][3], 50, stdin);
    Tarefa[indice][3][strcspn(Tarefa[indice][3], "\n")] = '\0';

    printf("Tarefa editada com sucesso!\n\n");
}

// Função para excluir uma tarefa
void ExclusaoDaTarefa(char Tarefa[250][4][50], int *quantidade, int indice)
{
    setlocale(LC_ALL, "");

    if (indice < 0 || indice >= *quantidade)
    {
        printf("\nÍndice inválido.\n");
        return;
    }

    for (int i = indice; i < *quantidade - 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            strcpy(Tarefa[i][j], Tarefa[i + 1][j]);
        }
    }

    (*quantidade)--;

    printf("\nTarefa excluída com sucesso.\n");
}

// Função para salvar as tarefas em arquivo
void SalvamentoDeTarefasArquivo(char Tarefa[250][4][50], int quantidade)
{
    setlocale(LC_ALL, "");

    FILE *arquivo = fopen("tarefas.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        fprintf(arquivo, "Tarefa %d: %s - Descrição: %s - Importância: %s - Situação: %s\n",
                i + 1, Tarefa[i][0], Tarefa[i][1], Tarefa[i][2], Tarefa[i][3]);
    }

    fclose(arquivo);
    printf("\nTarefas salvas em 'tarefas.txt' com sucesso.\n");
}

// Função principal
int main()
{
    setlocale(LC_ALL, "");

    char Tarefa[250][4][50];
    int quantidade = 0;
    int ver = 0;

    while (ver != 6)
    {
        menuinicial();
        scanf("%d", &ver);

        switch (ver)
        {
        case 1:
            TarefaCadastrada(Tarefa, &quantidade);
            break;

        case 2:
            ListagemDaTarefa(Tarefa, quantidade);
            break;

        case 3:
            if (quantidade == 0)
            {
                printf("\nNenhuma tarefa para editar.\n");
                break;
            }
            printf("Digite o número da tarefa a editar (1 a %d): ", quantidade);
            int indEditar;
            scanf("%d", &indEditar);
            EdicaoDaTarefa(Tarefa, indEditar - 1);
            break;

        case 4:
            if (quantidade == 0)
            {
                printf("\nNenhuma tarefa para excluir.\n");
                break;
            }
            printf("Digite o número da tarefa a excluir (1 a %d): ", quantidade);
            int indExcluir;
            scanf("%d", &indExcluir);
            ExclusaoDaTarefa(Tarefa, &quantidade, indExcluir - 1);
            break;

        case 5:
            SalvamentoDeTarefasArquivo(Tarefa, quantidade);
            break;

        case 6:
            printf("Saindo do programa... Até a próxima! ;)\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
        }
    }

    return 0;
}