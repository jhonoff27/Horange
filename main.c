#include <stdio.h>
#include <string.h>
#include <locale.h>
#define MAX_PRODUTOS 100

// Estrutura para representar um produto
typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} produto;

produto produtos[MAX_PRODUTOS];
int numprodutos = 0;

// Fun��o para cadastrar um produto
void cadastrarproduto() {
    if (numprodutos >= MAX_PRODUTOS) {
        printf("Limite de produtos alcan�ado!\n");
        return;
    }

    produto novoproduto;

    printf("Digite o nome do produto: ");
    getchar(); // Limpa o buffer para evitar problemas com o scanf
    scanf("%[^\n]", novoproduto.nome);

    printf("Digite o pre�o do produto: ");
    scanf("%f", &novoproduto.preco);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novoproduto.quantidade);

    produtos[numprodutos] = novoproduto;
    numprodutos++;

    printf("Produto cadastrado com sucesso!\n");
}

// Fun��o para listar produtos
void listarprodutos() {
    if (numprodutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nLista de produtos:\n");
    for (int i = 0; i < numprodutos; i++) {
        printf("%d. %s - R$ %.2f (Quantidade: %d)\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Fun��o para excluir um produto
void excluirProduto() {
    int indice;
    listarprodutos();

    if (numprodutos == 0) {
        printf("Nenhum produto cadastrado para excluir.\n");
        return;
    }

    printf("\nDigite o n�mero do produto que deseja excluir: ");
    scanf("%d", &indice);
    indice--; // Ajusta para �ndice baseado em 0

    if (indice < 0 || indice >= numprodutos) {
        printf("Produto inv�lido!\n");
        return;
    }

    // Confirma��o antes de excluir o produto
    char confirmacao;
    printf("Tem certeza que deseja excluir o produto '%s'? (S/N): ", produtos[indice].nome);
    getchar(); // Limpa o buffer para evitar problemas com o scanf
    scanf("%c", &confirmacao);

    if (confirmacao == 'S' || confirmacao == 's') {
        // Remove o produto e reorganiza o array
        for (int i = indice; i < numprodutos - 1; i++) {
            produtos[i] = produtos[i + 1];
        }
        numprodutos--; // Reduz o contador de produtos

        printf("Produto exclu�do com sucesso!\n");
    } else {
        printf("Exclus�o cancelada.\n");
    }
}

// Fun��o para realizar uma venda
void realizarvenda() {
    if (numprodutos == 0) {
        printf("Nenhum produto cadastrado. Imposs�vel realizar vendas.\n");
        return;
    }

    listarprodutos();

    int indice, quantidade;

    printf("Selecione o n�mero do produto que deseja comprar: ");
    scanf("%d", &indice);
    indice--; // Ajusta para �ndice baseado em 0

    if (indice < 0 || indice >= numprodutos) {
        printf("Produto inv�lido!\n");
        return;
    }

    printf("Digite a quantidade que deseja vender: ");
    scanf("%d", &quantidade);

    if (quantidade > produtos[indice].quantidade) {
        printf("Quantidade insuficiente em estoque!\n");
        return;
    }

    produtos[indice].quantidade -= quantidade;
    float total = quantidade * produtos[indice].preco;

    printf("Venda realizada com sucesso! Total: R$ %.2f\n", total);
}

// Fun��o principal (menu)
int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 3F");
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("3. Realizar venda\n");
        printf("4. Excluir produto\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarproduto();
                break;
            case 2:
                listarprodutos();
                break;
            case 3:
                realizarvenda();
                break;
            case 4:
                excluirProduto();
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
