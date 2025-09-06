#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // Usado pro atoi() e exit()

// Estrutura que guarda os dados de uma carta de cidade
typedef struct {
    char estado[50];
    char codigo[10];
    char nome[100];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} Carta;

// Estrutura que guarda o resultado da comparação de cartas
typedef struct {
    int vencedora;  // 1 para carta1, 2 para carta2, 0 para empate
    char atributo1[30];
    char atributo2[30];
    float valor1_attr1, valor1_attr2;
    float valor2_attr1, valor2_attr2;
    int pontos_carta1, pontos_carta2;
} ResultadoComparacao;

// Essa função limpa todos os dados de uma carta, deixando ela "zerada"
void limparCarta(Carta *carta) {
    strcpy(carta->estado, "");
    strcpy(carta->codigo, "");
    strcpy(carta->nome, "");
    carta->populacao = 0;
    carta->area = 0.0;
    carta->pib = 0.0;
    carta->pontos_turisticos = 0;
}

// Essa função serve só para limpar o que sobrou no teclado antes de pedir outro valor
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Essa função pede a população e confere se o usuário digitou certo
int lerPopulacao() {
    char input[50];
    int populacao;
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;
    
    while (tentativas < MAX_TENTATIVAS) {
        printf("População (apenas números inteiros): ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove a quebra de linha
            input[strcspn(input, "\n")] = 0;
            
            // Verifica se contém apenas dígitos
            int valido = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (input[i] < '0' || input[i] > '9') {
                    if (input[i] == '.' || input[i] == ',') {
                        printf("❌ ERRO: População deve ser um número INTEIRO (sem vírgula ou ponto)!\n");
                        printf("   Exemplo correto: 1500000\n\n");
                    } else {
                        printf("❌ ERRO: População deve conter apenas números!\n");
                        printf("   Exemplo correto: 1500000\n\n");
                    }
                    valido = 0;
                    break;
                }
            }
            
            if (valido && strlen(input) > 0) {
                populacao = atoi(input);
                if (populacao > 0) {
                    return populacao;
                } else {
                    printf("❌ ERRO: População deve ser maior que zero!\n\n");
                }
            }
        }
        
        tentativas++;
        if (tentativas < MAX_TENTATIVAS) {
            printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
        }
    }
    
    printf("❌ Muitas tentativas inválidas. Reiniciando cadastro desta carta...\n\n");
    return -1; // Indica erro para recomeçar
}

// Essa função pede a área e também valida se foi digitada corretamente
float lerArea() {
    char input[50];
    float area;
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;
    
    while (tentativas < MAX_TENTATIVAS) {
        printf("Área em km² (use PONTO para decimais): ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove a quebra de linha
            input[strcspn(input, "\n")] = 0;
            
            // Verifica se contém vírgula
            if (strchr(input, ',') != NULL) {
                printf("❌ ERRO: Use PONTO (.) ao invés de vírgula (,) para decimais!\n");
                printf("   Exemplo correto: 1234.56\n\n");
                tentativas++;
                if (tentativas < MAX_TENTATIVAS) {
                    printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
                }
                continue;
            }
            
            // Tenta converter usando sscanf
            if (sscanf(input, "%f", &area) == 1 && area > 0) {
                return area;
            } else {
                printf("❌ ERRO: Área deve ser um número válido maior que zero!\n");
                printf("   Exemplo correto: 1234.56\n\n");
            }
        }
        
        tentativas++;
        if (tentativas < MAX_TENTATIVAS) {
            printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
        }
    }
    
    printf("❌ Muitas tentativas inválidas. Reiniciando cadastro desta carta...\n\n");
    return -1; // Indica erro para recomeçar
}

// Essa função pede o PIB e valida se está no formato correto
float lerPIB() {
    char input[50];
    float pib;
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;
    
    while (tentativas < MAX_TENTATIVAS) {
        printf("PIB em milhões (use PONTO para decimais): ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove a quebra de linha
            input[strcspn(input, "\n")] = 0;
            
            // Verifica se contém vírgula
            if (strchr(input, ',') != NULL) {
                printf("❌ ERRO: Use PONTO (.) ao invés de vírgula (,) para decimais!\n");
                printf("   Exemplo correto: 5678.90\n\n");
                tentativas++;
                if (tentativas < MAX_TENTATIVAS) {
                    printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
                }
                continue;
            }
            
            // Tenta converter usando sscanf
            if (sscanf(input, "%f", &pib) == 1 && pib > 0) {
                return pib;
            } else {
                printf("❌ ERRO: PIB deve ser um número válido maior que zero!\n");
                printf("   Exemplo correto: 5678.90\n\n");
            }
        }
        
        tentativas++;
        if (tentativas < MAX_TENTATIVAS) {
            printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
        }
    }
    
    printf("❌ Muitas tentativas inválidas. Reiniciando cadastro desta carta...\n\n");
    return -1; // Indica erro para recomeçar
}

// Essa função pede o número de pontos turísticos e garante que é um número válido
int lerPontosTuristicos() {
    char input[50];
    int pontos;
    int tentativas = 0;
    const int MAX_TENTATIVAS = 3;
    
    while (tentativas < MAX_TENTATIVAS) {
        printf("Número de pontos turísticos (apenas números inteiros): ");
        
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Remove a quebra de linha
            input[strcspn(input, "\n")] = 0;
            
            // Verifica se contém apenas dígitos
            int valido = 1;
            for (int i = 0; input[i] != '\0'; i++) {
                if (input[i] < '0' || input[i] > '9') {
                    if (input[i] == '.' || input[i] == ',') {
                        printf("❌ ERRO: Pontos turísticos deve ser um número INTEIRO (sem vírgula ou ponto)!\n");
                        printf("   Exemplo correto: 25\n\n");
                    } else {
                        printf("❌ ERRO: Pontos turísticos deve conter apenas números!\n");
                        printf("   Exemplo correto: 25\n\n");
                    }
                    valido = 0;
                    break;
                }
            }
            
            if (valido && strlen(input) > 0) {
                pontos = atoi(input);
                if (pontos >= 0) {
                    return pontos;
                } else {
                    printf("❌ ERRO: Pontos turísticos deve ser zero ou maior!\n\n");
                }
            }
        }
        
        tentativas++;
        if (tentativas < MAX_TENTATIVAS) {
            printf("⚠️ Tentativa %d de %d. Tente novamente.\n", tentativas + 1, MAX_TENTATIVAS);
        }
    }
    
    printf("❌ Muitas tentativas inválidas. Reiniciando cadastro desta carta...\n\n");
    return -1; // Indica erro para recomeçar
}

// Essa função faz o cadastro de uma carta inteira, pedindo os dados um por um
void cadastrarCarta(Carta * carta, int numero, int totalCartas) {
    int tentativasGerais = 0;
    const int MAX_TENTATIVAS_GERAIS = 3;
    
    // Limpa o buffer antes de começar o cadastro
    limparBuffer();
    
    while (tentativasGerais < MAX_TENTATIVAS_GERAIS) {
        // Limpa a estrutura da carta antes de cadastrar
        limparCarta(carta);
        
        printf("\n=== CADASTRO DA CARTA %d ===\n", numero);
        
        // Entrada de dados de texto (sem validação especial)
        printf("Estado: ");
        fgets(carta->estado, sizeof(carta->estado), stdin);
        carta->estado[strcspn(carta->estado, "\n")] = 0;
        
        printf("Código da carta: ");
        fgets(carta->codigo, sizeof(carta->codigo), stdin);
        carta->codigo[strcspn(carta->codigo, "\n")] = 0;
        
        printf("Nome da cidade: ");
        fgets(carta->nome, sizeof(carta->nome), stdin);
        carta->nome[strcspn(carta->nome, "\n")] = 0;
        
        // Entrada de dados numéricos com validação
        printf("\n📊 DADOS NUMÉRICOS (siga as instruções cuidadosamente):\n");
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        // Ler população
        carta->populacao = lerPopulacao();
        if (carta->populacao == -1) {
            tentativasGerais++;
            if (tentativasGerais < MAX_TENTATIVAS_GERAIS) {
                printf("🔄 Recomeçando cadastro da carta %d...\n", numero);
                continue;
            } else {
                printf("❌ Muitas tentativas falharam. Encerrando programa...\n");
                exit(1);
            }
        }
        
        // Ler área
        carta->area = lerArea();
        if (carta->area == -1) {
            tentativasGerais++;
            if (tentativasGerais < MAX_TENTATIVAS_GERAIS) {
                printf("🔄 Recomeçando cadastro da carta %d...\n", numero);
                continue;
            } else {
                printf("❌ Muitas tentativas falharam. Encerrando programa...\n");
                exit(1);
            }
        }
        
        // Ler PIB
        carta->pib = lerPIB();
        if (carta->pib == -1) {
            tentativasGerais++;
            if (tentativasGerais < MAX_TENTATIVAS_GERAIS) {
                printf("🔄 Recomeçando cadastro da carta %d...\n", numero);
                continue;
            } else {
                printf("❌ Muitas tentativas falharam. Encerrando programa...\n");
                exit(1);
            }
        }
        
        // Ler pontos turísticos
        carta->pontos_turisticos = lerPontosTuristicos();
        if (carta->pontos_turisticos == -1) {
            tentativasGerais++;
            if (tentativasGerais < MAX_TENTATIVAS_GERAIS) {
                printf("🔄 Recomeçando cadastro da carta %d...\n", numero);
                continue;
            } else {
                printf("❌ Muitas tentativas falharam. Encerrando programa...\n");
                exit(1);
            }
        }
        
        // Se chegou até aqui, todos os dados foram inseridos corretamente
        printf("\n✅ Dados da carta %d cadastrados com sucesso!\n", numero);
        break;
    }
    
    // Mensagem condicional baseada no número da carta (APENAS para cadastro inicial)
    if (numero < totalCartas) {
        printf("\n🔄 Pressione Enter (Duas Vezes) para cadastrar a próxima carta...");
        while(getchar() != '\n');
    } else if (numero == totalCartas) {
        printf("\n✅ Cadastro da última carta concluído!");
        // NÃO adiciona pausa aqui - deixa para o main decidir
    }
}

// Função para exibir informações de uma carta
void exibirCarta(Carta carta) {
    printf("\n--- INFORMAÇÕES DA CARTA ---\n");
    printf("Estado: %s\n", carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("Cidade: %s\n", carta.nome);
    printf("População: %d habitantes\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: R$ %.2f milhões\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontos_turisticos);
    
    float densidade = carta.populacao / carta.area;
    printf("Densidade Populacional: %.2f hab/km²\n", densidade);
}

// Essa função mostra o menu de atributos para o jogador escolher na comparação
int exibirMenuAtributos(int numeroEscolha) {
    int opcao;
    
    printf("\n=== ESCOLHA DO %dº ATRIBUTO ===\n", numeroEscolha);
    printf("Escolha um atributo para comparação:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("Digite sua opção (1-5): ");
    scanf("%d", &opcao);
    
    return opcao;
}

// Parecida com a anterior, mas não deixa repetir o mesmo atributo
int exibirMenuAtributosComExclusao(int numeroEscolha, int atributoExcluido, char *nomeExcluido) {
    int opcao;
    
    printf("\n=== ESCOLHA DO %dº ATRIBUTO ===\n", numeroEscolha);
    printf("⚠️ ATENÇÃO: Você já escolheu '%s'\n", nomeExcluido);
    printf("Escolha um atributo DIFERENTE para comparação:\n");
    
    // Mostra apenas as opções não escolhidas
    if (atributoExcluido != 1) printf("1. População\n");
    if (atributoExcluido != 2) printf("2. Área\n");
    if (atributoExcluido != 3) printf("3. PIB\n");
    if (atributoExcluido != 4) printf("4. Pontos Turísticos\n");
    if (atributoExcluido != 5) printf("5. Densidade Populacional\n");
    
    printf("Digite sua opção (1-5): ");
    scanf("%d", &opcao);
    
    return opcao;
}

// Essa função retorna o nome de cada atributo
void obterNomeAtributo(int opcao, char *nome) {
    switch(opcao) {
        case 1: strcpy(nome, "População"); break;
        case 2: strcpy(nome, "Área"); break;
        case 3: strcpy(nome, "PIB"); break;
        case 4: strcpy(nome, "Pontos Turísticos"); break;
        case 5: strcpy(nome, "Densidade Populacional"); break;
        default: strcpy(nome, "Inválido"); break;
    }
}

// Essa função pega o valor numérico do atributo escolhido (por exemplo: população da carta)
float obterValorAtributo(Carta carta, int opcao) {
    switch(opcao) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontos_turisticos;
        case 5: return carta.populacao / carta.area;
        default: return 0.0;
    }
}

// Aqui a regra especial é que, para densidade populacional, o menor valor vence
int temRegraEspecial(int opcao) {
    return opcao == 5; // Densidade populacional
}

// Essa função compara os atributos e decide quem venceu em cada caso
int compararAtributo(float valor1, float valor2, int temRegraEspecial) {
    if (temRegraEspecial) {
        // Para densidade populacional, menor valor vence
        return (valor1 < valor2) ? 1 : (valor1 > valor2) ? 2 : 0;
    } else {
        // Para outros atributos, maior valor vence
        return (valor1 > valor2) ? 1 : (valor1 < valor2) ? 2 : 0;
    }
}

// Essa função compara duas cartas usando dois atributos escolhidos pelo jogador
ResultadoComparacao compararDoisAtributos(Carta carta1, Carta carta2, int attr1, int attr2) {
    ResultadoComparacao resultado;
    
    // Inicializa o resultado
    resultado.pontos_carta1 = 0;
    resultado.pontos_carta2 = 0;
    resultado.vencedora = 0;
    
    // Obter nomes dos atributos
    obterNomeAtributo(attr1, resultado.atributo1);
    obterNomeAtributo(attr2, resultado.atributo2);
    
    // Obter valores dos atributos
    resultado.valor1_attr1 = obterValorAtributo(carta1, attr1);
    resultado.valor1_attr2 = obterValorAtributo(carta1, attr2);
    resultado.valor2_attr1 = obterValorAtributo(carta2, attr1);
    resultado.valor2_attr2 = obterValorAtributo(carta2, attr2);
    
    // Comparação do primeiro atributo
    int resultado_attr1 = compararAtributo(resultado.valor1_attr1, resultado.valor2_attr1, temRegraEspecial(attr1));
    
    // Comparação do segundo atributo
    int resultado_attr2 = compararAtributo(resultado.valor1_attr2, resultado.valor2_attr2, temRegraEspecial(attr2));
    
    // Lógica de pontuação usando operadores ternários
    resultado.pontos_carta1 += (resultado_attr1 == 1) ? 1 : 0;
    resultado.pontos_carta2 += (resultado_attr1 == 2) ? 1 : 0;
    resultado.pontos_carta1 += (resultado_attr2 == 1) ? 1 : 0;
    resultado.pontos_carta2 += (resultado_attr2 == 2) ? 1 : 0;
    
    // Determinação da vencedora usando operadores ternários encadeados
    resultado.vencedora = (resultado.pontos_carta1 > resultado.pontos_carta2) ? 1 :
                         (resultado.pontos_carta2 > resultado.pontos_carta1) ? 2 : 0;
    
    return resultado;
}

// Essa função mostra o resultado da comparação de forma detalhada
void exibirResultadoDetalhado(Carta carta1, Carta carta2, ResultadoComparacao resultado) {
    printf("\n==========================================\n");
    printf("       🏆 RESULTADO DA COMPARAÇÃO\n");
    printf("==========================================\n");
    
    // Exibição dos atributos comparados
    printf("\n📊 ATRIBUTOS COMPARADOS:\n");
    printf("1º Atributo: %s\n", resultado.atributo1);
    printf("2º Atributo: %s\n", resultado.atributo2);
    
    // Exibição dos valores - usando lógica aninhada para formatação
    printf("\n📈 VALORES DAS CARTAS:\n");
    printf("┌─────────────────────────────────────────┐\n");
    printf("│ CARTA 1 - %-25s \n", carta1.nome);
    printf("├─────────────────────────────────────────┤\n");
    
    // Formatação condicional usando operadores ternários
    (strcmp(resultado.atributo1, "População") == 0) ? 
        printf("│ %s: %.0f habitantes%*s\n", resultado.atributo1, resultado.valor1_attr1, 
               (int)(25 - strlen(resultado.atributo1) - (int)resultado.valor1_attr1/1000000*6 - 11), " ") :
    (strcmp(resultado.atributo1, "Área") == 0) ?
        printf("│ %s: %.2f km²%*s\n", resultado.atributo1, resultado.valor1_attr1,
               (int)(30 - strlen(resultado.atributo1) - 8), " ") :
    (strcmp(resultado.atributo1, "PIB") == 0) ?
        printf("│ %s: R$ %.2f milhões%*s\n", resultado.atributo1, resultado.valor1_attr1,
               (int)(22 - strlen(resultado.atributo1) - 8), " ") :
    (strcmp(resultado.atributo1, "Pontos Turísticos") == 0) ?
        printf("│ %s: %.0f%*s\n", resultado.atributo1, resultado.valor1_attr1,
               (int)(38 - strlen(resultado.atributo1) - (int)resultado.valor1_attr1/10), " ") :
        printf("│ %s: %.2f hab/km²%*s\n", resultado.atributo1, resultado.valor1_attr1,
               (int)(26 - strlen(resultado.atributo1) - 8), " ");
    
    (strcmp(resultado.atributo2, "População") == 0) ? 
        printf("│ %s: %.0f habitantes%*s\n", resultado.atributo2, resultado.valor1_attr2, 
               (int)(25 - strlen(resultado.atributo2) - (int)resultado.valor1_attr2/1000000*6 - 11), " ") :
    (strcmp(resultado.atributo2, "Área") == 0) ?
        printf("│ %s: %.2f km²%*s\n", resultado.atributo2, resultado.valor1_attr2,
               (int)(30 - strlen(resultado.atributo2) - 8), " ") :
    (strcmp(resultado.atributo2, "PIB") == 0) ?
        printf("│ %s: R$ %.2f milhões%*s\n", resultado.atributo2, resultado.valor1_attr2,
               (int)(22 - strlen(resultado.atributo2) - 8), " ") :
    (strcmp(resultado.atributo2, "Pontos Turísticos") == 0) ?
        printf("│ %s: %.0f%*s\n", resultado.atributo2, resultado.valor1_attr2,
               (int)(38 - strlen(resultado.atributo2) - (int)resultado.valor1_attr2/10), " ") :
        printf("│ %s: %.2f hab/km²%*s\n", resultado.atributo2, resultado.valor1_attr2,
               (int)(26 - strlen(resultado.atributo2) - 8), " ");
    
    printf("└─────────────────────────────────────────┘\n");
    
    printf("┌─────────────────────────────────────────┐\n");
    printf("│ CARTA 2 - %-25s \n", carta2.nome);
    printf("├─────────────────────────────────────────┤\n");
    
    // Mesma lógica para carta 2
    (strcmp(resultado.atributo1, "População") == 0) ? 
        printf("│ %s: %.0f habitantes%*s\n", resultado.atributo1, resultado.valor2_attr1, 
               (int)(25 - strlen(resultado.atributo1) - (int)resultado.valor2_attr1/1000000*6 - 11), " ") :
    (strcmp(resultado.atributo1, "Área") == 0) ?
        printf("│ %s: %.2f km²%*s\n", resultado.atributo1, resultado.valor2_attr1,
               (int)(30 - strlen(resultado.atributo1) - 8), " ") :
    (strcmp(resultado.atributo1, "PIB") == 0) ?
        printf("│ %s: R$ %.2f milhões%*s\n", resultado.atributo1, resultado.valor2_attr1,
               (int)(22 - strlen(resultado.atributo1) - 8), " ") :
    (strcmp(resultado.atributo1, "Pontos Turísticos") == 0) ?
        printf("│ %s: %.0f%*s\n", resultado.atributo1, resultado.valor2_attr1,
               (int)(38 - strlen(resultado.atributo1) - (int)resultado.valor2_attr1/10), " ") :
        printf("│ %s: %.2f hab/km²%*s\n", resultado.atributo1, resultado.valor2_attr1,
               (int)(26 - strlen(resultado.atributo1) - 8), " ");
    
    (strcmp(resultado.atributo2, "População") == 0) ? 
        printf("│ %s: %.0f habitantes%*s\n", resultado.atributo2, resultado.valor2_attr2, 
               (int)(25 - strlen(resultado.atributo2) - (int)resultado.valor2_attr2/1000000*6 - 11), " ") :
    (strcmp(resultado.atributo2, "Área") == 0) ?
        printf("│ %s: %.2f km²%*s\n", resultado.atributo2, resultado.valor2_attr2,
               (int)(30 - strlen(resultado.atributo2) - 8), " ") :
    (strcmp(resultado.atributo2, "PIB") == 0) ?
        printf("│ %s: R$ %.2f milhões%*s\n", resultado.atributo2, resultado.valor2_attr2,
               (int)(22 - strlen(resultado.atributo2) - 8), " ") :
    (strcmp(resultado.atributo2, "Pontos Turísticos") == 0) ?
        printf("│ %s: %.0f%*s\n", resultado.atributo2, resultado.valor2_attr2,
               (int)(38 - strlen(resultado.atributo2) - (int)resultado.valor2_attr2/10), " ") :
        printf("│ %s: %.2f hab/km²%*s\n", resultado.atributo2, resultado.valor2_attr2,
               (int)(26 - strlen(resultado.atributo2) - 8), " ");
    
    printf("└─────────────────────────────────────────┘\n");
    
    // Sistema de pontuação
    printf("\n🎯 SISTEMA DE PONTUAÇÃO:\n");
    printf("• %s (%s): %d ponto(s)\n", carta1.nome, carta1.codigo, resultado.pontos_carta1);
    printf("• %s (%s): %d ponto(s)\n", carta2.nome, carta2.codigo, resultado.pontos_carta2);
    
    // Resultado final usando operadores ternários aninhados
    printf("\n🏆 RESULTADO FINAL:\n");
    (resultado.vencedora == 1) ?
        printf("🎉 VENCEDORA: %s (%s)\n   Vantagem: %d ponto(s)\n", 
               carta1.nome, carta1.codigo, resultado.pontos_carta1 - resultado.pontos_carta2) :
    (resultado.vencedora == 2) ?
        printf("🎉 VENCEDORA: %s (%s)\n   Vantagem: %d ponto(s)\n", 
               carta2.nome, carta2.codigo, resultado.pontos_carta2 - resultado.pontos_carta1) :
        printf("🤝 EMPATE PERFEITO!\n   Ambas as cartas empataram com %d ponto(s) cada.\n", resultado.pontos_carta1);
    
    // Regras especiais aplicadas
    printf("\n⚠️ REGRAS ESPECIAIS APLICADAS:\n");
    printf("• Densidade Populacional: MENOR valor vence\n");
    printf("• Demais atributos: MAIOR valor vence\n");
}

// O Menu principal do jogo!
int menuPrincipal() {
    int opcao;
    
    printf("\n==========================================\n");
    printf("         🎮 MENU PRINCIPAL 🎮\n");
    printf("==========================================\n");
    printf("1. ⚔️ Comparar cartas (2 atributos)\n");
    printf("2. 📊 Ver cartas cadastradas\n");
    printf("3. 🔄 Recadastrar cartas\n");
    printf("4. 🚪 Sair do jogo\n");
    printf("==========================================\n");
    printf("Digite sua opção (1-4): ");
    scanf("%d", &opcao);
    
    return opcao;
}

// Verifica se o atributo escolhido é válido
int validarOpcaoAtributo(int opcao) {
    return (opcao >= 1 && opcao <= 5);
}

int main() {
    Carta carta1, carta2;
    int opcaoMenu, atributo1, atributo2;
    int cartasCadastradas = 0;
    
    // Inicializa as cartas vazias
    limparCarta(&carta1);
    limparCarta(&carta2);
    
    // Aqui começa o jogo, mostrando o título e explicação
    printf("==========================================\n");
    printf("     🎮 SUPER TRUNFO - NÍVEL MESTRE 🎮\n");
    printf("==========================================\n");
    printf("Bem-vindo ao nível mais avançado do jogo!\n");
    printf("Aqui você pode comparar DOIS atributos\n");
    printf("simultaneamente entre as cartas.\n");
    printf("==========================================\n");
    
    // O jogo roda em loop até o jogador escolher sair!
    do {
        // Se ainda não tem cartas cadastradas, o programa obriga a cadastrar primeiro
        if (cartasCadastradas == 0) {
            printf("\nℹ️ IMPORTANTE: Não use acentos em nomes de (Estado) e (Cidade)\n");
            printf("ℹ️ IMPORTANTE: Use PONTO (.) para decimais, NÃO vírgula (,)\n");
            printf("ℹ️ População e Pontos Turísticos devem ser números inteiros\n");
            printf("\n📝 Primeiro, vamos cadastrar as cartas! (Pressione Enter (Duas Vezes) para Começar)");
            limparBuffer(); // Limpa o buffer antes de começar
            
            // CHAMADAS MODIFICADAS - agora passam o total de cartas (2)
            cadastrarCarta(&carta1, 1, 2);
            cadastrarCarta(&carta2, 2, 2);
            cartasCadastradas = 1;
            
            printf("\n✅ Cartas cadastradas com sucesso!\n");
        }
        
        opcaoMenu = menuPrincipal();
        
        switch(opcaoMenu) {
            case 1: {
                // Aqui é o modo de comparação, onde o jogador escolhe 2 atributos
                printf("\n🎯 MODO COMPARAÇÃO DUPLA ATIVADO!\n");
                printf("Você escolherá 2 atributos para comparação.\n");
                
                // A seleção do primeiro atributo
                do {
                    atributo1 = exibirMenuAtributos(1);
                    if (!validarOpcaoAtributo(atributo1)) {
                        printf("❌ Opção inválida! Tente novamente.\n");
                    }
                } while (!validarOpcaoAtributo(atributo1));
                
                // Mostra qual atributo foi escolhido
                char nomeAttr1[30];
                obterNomeAtributo(atributo1, nomeAttr1);
                printf("✅ Primeiro atributo selecionado: %s\n", nomeAttr1);
                
                // Seleção do segundo atributo (não deixa repetir o mesmo atributo)
                do {
                    atributo2 = exibirMenuAtributosComExclusao(2, atributo1, nomeAttr1);
                    if (!validarOpcaoAtributo(atributo2)) {
                        printf("❌ Opção inválida! Tente novamente.\n");
                    } else if (atributo2 == atributo1) {
                        printf("❌ ERRO: Você escolheu '%s' novamente!\n", nomeAttr1);
                        printf("   Você DEVE escolher um atributo diferente para a comparação.\n");
                    }
                } while (!validarOpcaoAtributo(atributo2) || atributo2 == atributo1);
                
                // Confirmação dos atributos escolhidos
                char nomeAttr2[30];
                obterNomeAtributo(atributo2, nomeAttr2);
                printf("✅ Segundo atributo selecionado: %s\n", nomeAttr2);
                printf("\n🎯 COMPARAÇÃO CONFIGURADA:\n");
                printf("   1º Atributo: %s\n", nomeAttr1);
                printf("   2º Atributo: %s\n", nomeAttr2);
                
                // Aqui executa a comparação
                ResultadoComparacao resultado = compararDoisAtributos(carta1, carta2, atributo1, atributo2);
                exibirResultadoDetalhado(carta1, carta2, resultado);
                
                break;
            }
            case 2: {
                // Aqui mostra as cartas cadastradas
                printf("\n==========================================\n");
                printf("         📋 CARTAS CADASTRADAS\n");
                printf("==========================================\n");
                
                printf("\n🏙️ CARTA 1:");
                exibirCarta(carta1);
                
                printf("\n🏙️ CARTA 2:");
                exibirCarta(carta2);
                
                break;
            }
            case 3: {
                // Aqui o jogador pode recadastrar as cartas
                printf("\n🔄 RECADASTRANDO CARTAS...\n");
                printf("ℹ️ IMPORTANTE: Não use acentos em nomes de (Estado) e (Cidade)\n");
                printf("ℹ️ IMPORTANTE: Use PONTO (.) para decimais, NÃO vírgula (,)\n");
                printf("ℹ️ População e Pontos Turísticos devem ser números inteiros\n");
                cadastrarCarta(&carta1, 1, 2);
                cadastrarCarta(&carta2, 2, 2);
                printf("\n✅ Cartas recadastradas com sucesso!\n");
                
                break;
            }
            case 4: {
                // Aqui finaliza o jogo
                printf("\n👋 Obrigado por jogar Super Trunfo Nível Mestre!\n");
                printf("Até a próxima aventura! 🎯✨\n");
                break;
            }
            default: {
                printf("❌ Opção inválida! Por favor, escolha uma opção de 1 a 4.\n");
                break;
            }
        }
        
        // Pausa para o usuário ler as informações
        if (opcaoMenu != 4) {
            printf("\n🔄 Pressione Enter para continuar...");
            // Limpa qualquer caractere pendente no buffer antes da pausa
            limparBuffer();
        }
        
    } while (opcaoMenu != 4);
    
    return 0;
}
/*
 - Esse código foi feito até o "Nível Mestre"!
 - O código acabou ficando grande porque acabei fazendo muita validação de entrada, e deixei comentários pra não ficar perdido.
 - Coloquei uns emojis pra ficar mais mais bonito visualmente.
 - Esse código foi o mais trabalhoso, mas foi um grande aprendizado.
*/