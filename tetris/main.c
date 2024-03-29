/* 
 * File:   main.c
 * Author: Hugo Carreira Costa e Wendell Ávila
 *
 * Created on 16 de Janeiro de 2018, 12:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct tela_ {
    int linha;
    int coluna;
    int sleep;
    char ** tela;
    int qtdPeca;
}tela;

typedef struct peca_ {
    int linha;
    int coluna;
    int qtMovimentos;
    char * movimentos;
    int movimentosIndice;
    char ** peca;
}peca;

void alocarMovimentos(peca * p){
    
    //alocando vetor com os movimentos
    p->movimentos = malloc( p->qtMovimentos * sizeof (char) );
    
}

void sleepTela(int segundos){
    sleep(segundos);
    system("clear");
}

void imprimirTela(tela * t, int sleepSeg){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            printf("%c", t->tela[i][j]);
        }
        printf("\n");
    }
    
    if(sleepSeg){
        sleepTela(t->sleep);
    }
    else {
        sleepTela(0);
    }
}

void lerPeca(tela * t, FILE * entrada, peca * p){
    
    int i;
    
    fscanf(entrada, "%d", &p->coluna);
    
    //condição para a peça não começar fora da tela
    if(p->coluna > t->coluna - 3){
        p->coluna = t->coluna - 3; 
    }
    else if(p->coluna < 0){
        p->coluna = 0;
    }

    fscanf(entrada, " %c %c %c\n", &p->peca[0][0], &p->peca[0][1], &p->peca[0][2]); //ler formato da peça
    fscanf(entrada, "%c %c %c\n", &p->peca[1][0], &p->peca[1][1], &p->peca[1][2]);
    fscanf(entrada, "%c %c %c", &p->peca[2][0], &p->peca[2][1], &p->peca[2][2]);
    fscanf(entrada, "%d", &p->qtMovimentos);

    alocarMovimentos(p); //alocar vetor de movimentos

    for(i = 0; i < p->qtMovimentos; i++){
        fscanf(entrada, " %c", &p->movimentos[i]); //ler movimentos
    }
    
    t->qtdPeca--; //decremento para dizer que uma peça ja foi lida
}

void lerTela(tela * t, FILE * entrada){
    
    int i;
    
    fscanf(entrada, "%d", &t->linha);
    fscanf(entrada, "%d", &t->coluna);
    fscanf(entrada, "%d", &t->sleep);
    fscanf(entrada, "%d", &t->qtdPeca);
}

void alocarTela(tela * t){
    
    int i;
    
    t->tela = malloc( t->linha * sizeof(char*) );
    for(i = 0; i < t->linha; i++){
        t->tela[i] = malloc( t->coluna * sizeof(char) );
    }
    
}

void desalocarTela(tela * t){
    
    int i;
    
    for(i = 0; i < t->linha; i++){
        free(t->tela[i]);
    }
    free(t->tela);

}

void preencherTela(tela * t){

    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            t->tela[i][j] = '.';
        }
    }

}

void alocarPeca(peca * p){

    int i, j;
    //alocando peça
    p->peca = malloc( 3 * sizeof (char*) );
    for(i = 0; i < 3; i++){
        p->peca[i] = malloc(3 * sizeof(char));
    }
    
}

void desalocarMovimentos(peca * p){

    int i;
    
    //desalocando vetor dos movimentos
    free(p->movimentos);
    
}

void desalocarPeca(peca * p){

    int i;
    
    //desalocando peça
    for(i = 0; i < 3; i++){
        free(p->peca[i]);
    }
    free(p->peca);
    
}

int inserirPeca(peca *p, tela *t){
    
    int i, j, inseriu;
    
    //inserindo peça na tela
    if(t->tela[p->linha + 2][p->coluna + 0] == '.' && t->tela[p->linha + 2][p->coluna + 1] == '.' && t->tela[p->linha + 2][p->coluna + 2] == '.' && t->tela[p->linha + 1][p->coluna + 0] == '.' && t->tela[p->linha + 1][p->coluna + 1] == '.' && t->tela[p->linha + 1][p->coluna + 2] == '.' && t->tela[p->linha][p->coluna + 0] == '.' && t->tela[p->linha][p->coluna + 1] == '.' && t->tela[p->linha][p->coluna + 2] == '.'){
        t->tela[p->linha + 2][p->coluna + 0] = p->peca[2][0];
        t->tela[p->linha + 2][p->coluna + 1] = p->peca[2][1];
        t->tela[p->linha + 2][p->coluna + 2] = p->peca[2][2];
        t->tela[p->linha + 1][p->coluna + 0] = p->peca[1][0];
        t->tela[p->linha + 1][p->coluna + 1] = p->peca[1][1];
        t->tela[p->linha + 1][p->coluna + 2] = p->peca[1][2];
        t->tela[p->linha][p->coluna + 0] = p->peca[0][0];
        t->tela[p->linha][p->coluna + 1] = p->peca[0][1];
        t->tela[p->linha][p->coluna + 2] = p->peca[0][2];
        
        inseriu = 1;
    }
    else if(t->tela[p->linha + 1][p->coluna + 0] == '.' && t->tela[p->linha + 1][p->coluna + 1] == '.' && t->tela[p->linha + 1][p->coluna + 2] == '.' && t->tela[p->linha][p->coluna + 0] == '.' && t->tela[p->linha][p->coluna + 1] == '.' && t->tela[p->linha][p->coluna + 2] == '.'){
        t->tela[p->linha + 1][p->coluna + 0] = p->peca[2][0];
        t->tela[p->linha + 1][p->coluna + 1] = p->peca[2][1];
        t->tela[p->linha + 1][p->coluna + 2] = p->peca[2][2];
        t->tela[p->linha][p->coluna + 0] = p->peca[1][0];
        t->tela[p->linha][p->coluna + 1] = p->peca[1][1];
        t->tela[p->linha][p->coluna + 2] = p->peca[1][2];
        
        inseriu = 1;
    }
    else if(t->tela[p->linha][p->coluna + 0] == '.' && t->tela[p->linha][p->coluna + 1] == '.' && t->tela[p->linha][p->coluna + 2] == '.'){
        t->tela[p->linha][p->coluna + 0] = p->peca[2][0];
        t->tela[p->linha][p->coluna + 1] = p->peca[2][1];
        t->tela[p->linha][p->coluna + 2] = p->peca[2][2];
        
        inseriu = 1;
    }
    else {
        inseriu = 0;
    }
    
    return(inseriu);
}

void descerPeca(peca * p, tela * t, int tipoDescida, int limiteBaixo[3]){
    
    int i, j;
    
    //descida para peças preenchidas até a 3a linha
    if(tipoDescida == 3){
        for(i = 3; i > 0; i--){
            for(j = 0; j < 3; j++){
                if((i-1) <= limiteBaixo[j]){
                    t->tela[p->linha + i][p->coluna + j] = t->tela[p->linha + (i - 1)][p->coluna + j];
                    t->tela[p->linha + (i - 1)][p->coluna + j] = '.';
                }
            }
        }
    }
    //descida para peças preenchidas até a 2a linha
    else if(tipoDescida == 2){
        for(i = 2; i > 0; i--){
            for(j = 0; j < 3; j++){
                if((i-1) <= limiteBaixo[j]){
                    t->tela[p->linha + i][p->coluna + j] = t->tela[p->linha + (i - 1)][p->coluna + j];
                    t->tela[p->linha + (i - 1)][p->coluna + j] = '.';
                }
            }
        }
    }
    //descida para peças preenchidas até a 1a linha
    else if(tipoDescida == 1){
        for(i = 1; i > 0; i--){
            for(j = 0; j < 3; j++){
                if((i-1) <= limiteBaixo[j]){
                    t->tela[p->linha + i][p->coluna + j] = t->tela[p->linha + (i - 1)][p->coluna + j];
                    t->tela[p->linha + (i - 1)][p->coluna + j] = '.';
                }
            }
        }
    }

    p->linha += 1;
}

void moverPeca(peca * p, tela * t, int tipoDescida, int limiteBaixo[3], int limiteEsq[3], int limiteDir[3]){
    
    int i, j, moveu = 0, desceu = 0;
    
    if(p->movimentosIndice < p->qtMovimentos){
        //movimentar
        
        if(((t->tela[p->linha + 2][p->coluna + limiteDir[0] + 1] == '.') || limiteDir[0] == -1 ) && // movimentar p/ DIREITA se as posições à direita da peça forem == '.'
                  ((t->tela[p->linha + 1][p->coluna + limiteDir[1] + 1] == '.') || limiteDir[1] == -1 ) &&
                  ((t->tela[p->linha][p->coluna + limiteDir[2] + 1] == '.') || limiteDir[2] == -1 ) &&
                    (p->movimentos[p->movimentosIndice] == 'd')){
            if(p->coluna + 1 < t->coluna - 2){ //if para a peça não sair pra fora pela direita
                
                for(j = 3; j > 0; j--){
                    for (i = 0; i < 3; i++) {
                        t->tela[p->linha + i][p->coluna+ j] = t->tela[p->linha + i][p->coluna+ (j-1)];
                        t->tela[p->linha + i][p->coluna+ (j-1)] = '.';
                    }
                    
                }
                p->coluna += 1;

            }
            moveu = 1;
        }
        else if(((t->tela[p->linha + 2][p->coluna + limiteEsq[0] - 1] == '.') || limiteEsq[0] == -1 ) && // movimentar p/ ESQUERDA se as posições à esquerda da peça forem == '.'
                  ((t->tela[p->linha + 1][p->coluna + limiteEsq[1] - 1] == '.') || limiteEsq[1] == -1 ) &&
                  ((t->tela[p->linha][p->coluna + limiteEsq[2] - 1] == '.') || limiteEsq[2] == -1 ) && 
                  (p->movimentos[p->movimentosIndice] == 'e')){ //movimento p/ ESQUERDA
            if(p->coluna - 1 > -1){ //if para a peça não sair pra fora pela esquerda

                for(j = -1; j < 2; j++){
                    for (i = 0; i < 3; i++) {
                        t->tela[p->linha + i][p->coluna+ j] = t->tela[p->linha + i][p->coluna+ (j+1)];
                        t->tela[p->linha + i][p->coluna+ (j+1)] = '.';
                    }
                    
                }
                p->coluna -= 1;
                
            }
            moveu = 1;
        }
        else if(p->movimentos[p->movimentosIndice] == 'b'){ //movimento p/ BAIXO

            // if para a peça não sair pra fora da tela por baixo 
            // e só descer se a posição abaixo do último caractere de cada coluna da peça estiver preenchida por ponto
            if((p->linha + 2 < t->linha) && (t->tela[p->linha + limiteBaixo[0] + 2][p->coluna] == '.') && (t->tela[p->linha + limiteBaixo[1] + 2][p->coluna + 1] == '.') && (t->tela[p->linha + limiteBaixo[2] + 2][p->coluna + 2] == '.')){
                descerPeca(p, t, tipoDescida, limiteBaixo);
            }
            moveu = 1;
            desceu = 1;
        }

        p->movimentosIndice += 1;

        if(moveu == 1 & desceu == 0){
            imprimirTela(t, 1);
        }
        else if(moveu == 1 & desceu == 1){
            imprimirTela(t, 0);
        }
    }
}

void gerarSaida(tela * t, FILE * saida, peca * p){
    int i, j;
    
    for(i = 0; i < t->linha; i++){
        for(j = 0; j < t->coluna; j++){
            fprintf(saida, "%c", t->tela[i][j]);
        }
        fprintf(saida, "\n");
    }
    fprintf(saida, "\n");
}

int limitesPecaDir(peca * p, int limiteDir[3]){
   
    //col 1
    if(p->peca[2][0] != '.'){
        limiteDir[2] = 2;
    }
    else if(p->peca[2][1] != '.'){
        limiteDir[2] = 1;
    }
    else if(p->peca[2][2] != '.'){
        limiteDir[2] = 0;
    }
    else {
        limiteDir[2] = -1;
    }
    
   
    //col 1
    if(p->peca[1][0] != '.'){
        limiteDir[1] = 2;
    }
    else if(p->peca[1][1] != '.'){
        limiteDir[1] = 1;
    }
    else if(p->peca[1][2] != '.'){
        limiteDir[1] = 0;
    }
    else {
        limiteDir[1] = -1;
    }
    
    
    //col 1
    if(p->peca[0][0] != '.'){
        limiteDir[0] = 2;
    }
    else if(p->peca[0][1] != '.'){
        limiteDir[0] = 1;
    }
    else if(p->peca[0][2] != '.'){
        limiteDir[0] = 0;
    }
    else {
        limiteDir[0] = -1;
    }
}

int limitesPecaEsq(peca * p, int limiteEsq[3]){
   
    //col 3
    if(p->peca[2][2] != '.'){
        limiteEsq[2] = 0;
    }
    else if(p->peca[1][2] != '.'){
        limiteEsq[2] = 1;
    }
    else if(p->peca[0][2] != '.'){
        limiteEsq[2] = 2;
    }
    else {
        limiteEsq[2] = -1;
    }
    
    //col 2
    if(p->peca[1][2] != '.'){
        limiteEsq[1] = 0;
    }
    else if(p->peca[1][1] != '.'){
        limiteEsq[1] = 1;
    }
    else if(p->peca[1][0] != '.'){
        limiteEsq[1] = 3;
    }
    else {
        limiteEsq[1] = -1;
    }
    
    //col 1
    if(p->peca[0][2] != '.'){
        limiteEsq[0] = 0;
    }
    else if(p->peca[0][1] != '.'){
        limiteEsq[0] = 1;
    }
    else if(p->peca[0][0] != '.'){
        limiteEsq[0] = 2;
    }
    else {
        limiteEsq[0] = -1;
    }
    
   
}   

int limitesPecaBaixo(peca * p, int limiteBaixo[3]){
    
    //encontrar última linha preenchida de cada coluna da peça
    
    //col 1
    if(p->peca[2][0] != '.'){
        limiteBaixo[0] = 2;
    }
    else if(p->peca[1][0] != '.'){
        limiteBaixo[0] = 1;
    }
    else if(p->peca[0][0] != '.'){
        limiteBaixo[0] = 0;
    }
    else {
        limiteBaixo[0] = -1;
    }
    
    //col 2
    if(p->peca[2][1] != '.'){
        limiteBaixo[1] = 2;
    }
    else if(p->peca[1][1] != '.'){
        limiteBaixo[1] = 1;
    }
    else if(p->peca[0][1] != '.'){
        limiteBaixo[1] = 0;
    }
    else {
        limiteBaixo[1] = -1;
    }
    
    //col 3
    if(p->peca[2][2] != '.'){
        limiteBaixo[2] = 2;
    }
    else if(p->peca[1][2] != '.'){
        limiteBaixo[2] = 1;
    }
    else if(p->peca[0][2] != '.'){
        limiteBaixo[2] = 0;
    }
    else {
        limiteBaixo[2] = -1;
    }
}

void rodarMovimentos(peca *p, tela *t){
    
    int descecont = 3, limiteBaixo[3], limiteEsq[3], limiteDir[3];
    
    if((p->peca[2][0] == '.') && (p->peca[2][1] == '.') && (p->peca[2][2] == '.')){
        descecont--; //2x3
        if((p->peca[1][0] == '.') && (p->peca[1][1] == '.') && (p->peca[1][2] == '.')){
            descecont--; //1x3
            if((p->peca[0][0] == '.') && (p->peca[0][1] == '.') && (p->peca[0][2] == '.')){
                descecont--; //0x0
            }
        }
    }
    
    limitesPecaBaixo(p, limiteBaixo);
    limitesPecaEsq(p, limiteEsq);
    limitesPecaDir(p, limiteDir);
    
    int linhaLimite = t->linha;

    
    while((p->linha + descecont < linhaLimite)){ //condição de parada para a peça não sair pra fora da tela por baixo
        
        //condição para a peça só descer se a posição abaixo do último caractere de cada coluna da peça estiver preenchida por ponto
        if(((t->tela[p->linha + limiteBaixo[0] + 1][p->coluna] == '.') || limiteBaixo[0] == -1 )&&
            ((t->tela[p->linha + limiteBaixo[1] + 1][p->coluna + 1] == '.') || limiteBaixo[1] == -1)&&
            ((t->tela[p->linha + limiteBaixo[2] + 1][p->coluna + 2] == '.') || limiteBaixo[2] == -1 )){

            moverPeca(p, t, descecont, limiteBaixo, limiteEsq, limiteDir);
            descerPeca(p, t, descecont, limiteBaixo);
            imprimirTela(t, 1);
        }
        
        //else para parar a descida da peça caso ela encontre caracteres diferentes de ponto abaixo
        else {
            linhaLimite = 0;
        } 
    }
       
}

//void limpaLinha(peca *p, tela *t){
//    
//    int i, i2, i3, j, contaLinha = 0, limpaCont = 0;
//    
//
//    for(i = 2; i > -1; i--){
//        for(j = 0; j < t->coluna; j++){
//            if(t->tela[p->linha + i][p->coluna + j] != '.'){
//                limpaCont++;
//            }
//        }
//        
//        if(limpaCont == t->coluna){
//            contaLinha++;
//            printf("%d", contaLinha);
//        }
//        else {
//            if(contaLinha > 0){
//                for(i2 = p->linha; i2 > -1; i2--){
//                    for(j = 0; j < t->coluna; j++){
//                      t->tela[p->linha + i2][j] = t->tela[p->linha + i2 - contaLinha][j];
//                    }
//                }
////                for(i3 = p->linha + i2; i3 > -1; i3--){
////                    for(j = 0; j < t->coluna; j++){
////                      t->tela[p->linha + i3][j] = t->tela[p->linha + i3 - contaLinha][j];
////                    }
////                }  
//            }
//        }
//        imprimirTela(t, 1);
//        limpaCont = 0;
//    }    
//}

int main(int argc, char** argv) {
    
    int i, inseriu, pararLoop = 0, linhaCheia;
    tela t;
    peca p;
    char condicao;
    
    //abrindo arquivo de entrada
    FILE *entrada; 
    entrada = fopen("entrada.txt", "r");
    
    //abrindo arquivo de saida
    FILE *saida;
    saida = fopen("saida.txt", "w");
    
    alocarPeca(&p);
    
    //ler arquivo enquanto tiver conteúdo a ser lido
    while(condicao != EOF){
        lerTela(&t, entrada);
        alocarTela(&t);
        preencherTela(&t);
        imprimirTela(&t, 1);

        while(t.qtdPeca > 0){
            p.linha = 0; //sempre começa com zero
            lerPeca(&t, entrada, &p);
            
            //checagem para ver se a peça atual foi inserida com sucesso
            inseriu = inserirPeca(&p, &t);
            
            if(inseriu){
                imprimirTela(&t, 1);
                p.movimentosIndice = 0;
                rodarMovimentos(&p, &t);
                //limpaLinha(&t);
            }
            else {
                pararLoop = 1;
            }
            
            //se a peça não foi inserida, é porque não há mais espaço na tela, encerrando assim o jogo
            if(pararLoop){
                break;
            }   
        }
        
        gerarSaida(&t, saida, &p);
        
        desalocarMovimentos(&p);
        desalocarTela(&t);
        
        //checagem para ver se existe conteúdo a ser lido no arquivo
        condicao = fgetc(entrada);
    }
    
    system("clear");
    printf("\n\tSaída gerada com sucesso!\n\n");
    
    desalocarPeca(&p);
    
    fclose(entrada);
    fclose(saida);
    
    return (EXIT_SUCCESS);
}