#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
//opa mano
string metodobinario (int num) {
    string bin="";
    if(num>0)
        if(num%2==0) {
            bin = (metodobinario(num / 2) + "0");
        } else {
            bin = (metodobinario(num / 2) + "1");
        }
    return bin;
}

int main() {
    fstream entrada;
    fstream saida1;
    fstream saida2;
    entrada.open("Entrada.in",ios::in);
    saida1.open("Tabela.out",ios::out);
    saida2.open("Resolucao.out",ios::out);
    string msg;
    int contador=0;
    while (getline(entrada, msg)) {
        contador = atoi(msg.c_str());
        if (contador > 0 ) {
            for (int i = 1; i <= contador; i++) {
                getline(entrada, msg);
                if (msg[0] == 'T' && msg[1] == 'T') {
                    int qdeoperando = 0;
                    int qdevariaveis = 0;
                    bool variaveis[4] = {false, false, false, false};
                    //pegar as variaveis
                    for (int j = 0; j < msg.length(); j++) {
                        if (msg[j] == 'P') {
                            variaveis[0] = true;
                        } else if (msg[j] == 'Q') {
                            variaveis[1] = true;
                        } else if (msg[j] == 'R') {
                            variaveis[2] = true;
                        } else if (msg[j] == 'S') {
                            variaveis[3] = true;
                        }
                    }
                    //saida2 << variaveis[0];
                    // cout << variaveis[1];
                    // cout << variaveis[2];
                    //  cout << variaveis[3];
                    // cout << "\n";


                    //pegar a quantidade de variaveis
                    for (int l = 0; l < 4; l++) {
                        if (variaveis[l] == true) {
                            qdevariaveis += 1;
                        };
                    }

                    //pegar a quantidade de operadores
                    for (int k = 0; k < msg.length(); k++) {
                        if (!(msg[k] >= 'A' && msg[k] <= 'Z') && !(msg[k] == '(' || msg[k] == ')' || msg[k] == ' ')) {
                            qdeoperando = qdeoperando + 1;
                        }
                    }

                    int colunas = qdeoperando + qdevariaveis;
                    int linhas = 0;
                    //preparando a tabela-verdade
                    string arrbase[colunas];
                    if (qdevariaveis == 1) {
                        linhas = 2;
                    } else if (qdevariaveis == 2) {
                        linhas = 4;
                    } else if (qdevariaveis == 3) {
                        linhas = 8;
                    } else if (qdevariaveis == 4) {
                        linhas = 16;
                    }
                    int arrvalores[linhas][colunas];

                    //preechendo a tabela base
                    //colocando as variaveis primeiro
                    int x = 0;
                    if (variaveis[0] == 1) {
                        arrbase[x] = "P";
                        x++;
                    }

                    if (variaveis[1] == 1) {
                        arrbase[x] = "Q";
                        x++;
                    }
                    if (variaveis[2] == 1) {
                        arrbase[x] = "R";
                        x++;
                    }
                    if (variaveis[3] == 1) {
                        arrbase[x] = "S";
                        x++;
                    }


                    msg[0] = ' ';
                    msg[1] = ' ';
                    int c, maxc;
                    bool achou;
                    string msgaux = msg;
                    //substituir por quantidade de operadores
                    for (int n = 0; n < qdeoperando; n++) {
                        c = 0, maxc = 999999;

                        for (int i = 0; i < msg.length(); i++) {
                            if (msg[i] == '(')c = 0;
                            else if (msg[i] == 'P' || msg[i] == 'Q' || msg[i] == 'R' || msg[i] == 'S')c++;
                            else if (msg[i] == ')') {
                                if (maxc > c) maxc = c;
                                if (!(maxc > 0)) {
                                    c = 0;
                                }
                            }
                        }

                        achou = true;
                        int contador_parenteses = 0, indx = 0, indy = 0;
                        int i = 0;
                        c = 0;

                        while (achou) {
                            if (msg[i] == '(') {
                                indx = i;
                                c = 0;
                            } else if (msg[i] == ')') {
                                indy = i;
                                if (c == maxc) {
                                    achou = false;
                                    string subexpressao;
                                    for (int j = indx + 1; j <= indy - 1; j++) {
                                        subexpressao += msgaux[j];
                                    }
                                    msg[indx] = ' ';
                                    msg[indy] = ' ';
                                    //  cout << subexpressao << endl;
                                    arrbase[x] = subexpressao;
                                    x++;
                                }
                            } else {
                                if (msg[i] == 'P' || msg[i] == 'Q' || msg[i] == 'R' || msg[i] == 'S') {
                                    c++;
                                }
                            }
                            i++;
                        }

                    }

                    //começar a mexer na tabela de valores
                    //trecho pra colocar as possibilidades das variaveis
                    linhas--;
                    int r = 0;
                    for (int i1 = 0; i1 <= linhas; i1++) {
                        string msgvalores = metodobinario(i1);
                        while (msgvalores.length() != qdevariaveis) {
                            msgvalores = '0' + msgvalores;
                        }
                        for (int i = 0; i < msgvalores.length(); i++) {
                            int z = msgvalores[i] - 48;
                            arrvalores[i1][i] = z;
                        }
                    }
                    // cout << "ÓTIMO!!!" << endl;



                    //trecho pra testar as subexpressões
                    int indvar;
                    //for para colunas
                    for (int k1 = 0; k1 < linhas + 1; k1++) {
                        //for para entrar em todas as subexpressoes
                        for (int j1 = qdevariaveis; j1 < colunas; j1++) {
                            string teste_subespressao = arrbase[j1];


                            //for para subexpressão pronta
                            int indf, inda, contador_fervoroso;
                            contador_fervoroso = 0;
                            bool entrada = true;
                            for (int l = 0; l < teste_subespressao.length(); l++) {
                                if (teste_subespressao[l] == '(') {
                                    if (entrada) {
                                        inda = l;
                                        entrada = false;
                                    }

                                    contador_fervoroso++;

                                } else if (teste_subespressao[l] == ')') {
                                    contador_fervoroso--;
                                    indf = l;
                                    if (contador_fervoroso == 0) {
                                        string procurar_subexpressao = "";
                                        for (int m = inda + 1; m < indf; m++) {
                                            procurar_subexpressao += teste_subespressao[m];
                                        }
                                        entrada = true;


                                        for (int j = 0; j < colunas; j++) {
                                            if (procurar_subexpressao == arrbase[j]) {
                                                indvar = j;
                                                if (arrvalores[k1][indvar] == 0) {
                                                    //apagar subexpressao e substituir
                                                    for (int k = 0; k < procurar_subexpressao.length() + 2; k++) {

                                                        if (k - 1 == procurar_subexpressao.length()) {
                                                            teste_subespressao[inda] = '0';
                                                            procurar_subexpressao = "";
                                                            l = l - (k - 2);
                                                            break;
                                                        } else {
                                                            teste_subespressao.erase(inda, 1);
                                                        }
                                                    }
                                                } else {
                                                    //apagar subexpressao e substituir
                                                    for (int k = 0; k < procurar_subexpressao.length() + 2; k++) {

                                                        if (k - 1 == procurar_subexpressao.length()) {
                                                            teste_subespressao[inda] = '1';
                                                            procurar_subexpressao = "0";
                                                            l = l - (k - 2);
                                                            break;
                                                        } else {
                                                            teste_subespressao.erase(inda, 1);
                                                        }
                                                    }
                                                }

                                            }


                                        }
                                    }
                                }
                            }

                            //for para subexpressão pronta sem parenteses
                            for (int i1 = 0; i1 < j1; i1++) {
                                if (teste_subespressao == arrbase[i1]) {
                                    if (arrvalores[k1][i1] == 0) {
                                        teste_subespressao = '0';
                                        break;
                                    } else {
                                        teste_subespressao = '1';
                                        break;
                                    }
                                }
                            }

                            //for para pecorrer toda a subexpressao
                            for (int i = 0; i < teste_subespressao.length(); i++) {
                                if (teste_subespressao[i] == 'P' || teste_subespressao[i] == 'Q' ||
                                    teste_subespressao[i] == 'R' || teste_subespressao[i] == 'S') {
                                    //for para achar qual dos arrbase ta o indvar da variavel
                                    for (int j = 0; j < 4; j++) {
                                        if (arrbase[j][0] == teste_subespressao[i]) {
                                            indvar = j;
                                            if (arrvalores[k1][indvar] == 0) {
                                                teste_subespressao[i] = '0';
                                                break;
                                            } else {
                                                teste_subespressao[i] = '1';
                                                break;
                                            }

                                        }
                                    }
                                }
                            }

                            //for para substituir negação
                            for (int m = 0; m < teste_subespressao.length(); m++) {
                                if (teste_subespressao[m] == '~' &&
                                    (teste_subespressao[m + 1] == '1' || teste_subespressao[m + 1] == '0')) {
                                    if (teste_subespressao[m + 1] == '1') {
                                        teste_subespressao[m + 1] = '0';
                                        teste_subespressao.erase(m, 1);

                                    } else if (teste_subespressao[m + 1] == '0') {
                                        teste_subespressao[m + 1] = '1';
                                        teste_subespressao.erase(m, 1);
                                    }
                                }
                            }

                            //for para casos testes complicados
                            for (int n = 0; n < teste_subespressao.length(); n++) {
                                if (teste_subespressao[n] == '(' || teste_subespressao[n] == ')') {
                                    teste_subespressao.erase(n, 1);
                                }
                            }


                            //0>(1 < 1)
                            //for pra checar operadores binarios
                            for (int k = 0; k < teste_subespressao.length(); k++) {
                                if (teste_subespressao[k] == 'v') {
                                    if (teste_subespressao[k - 2] == '1' || teste_subespressao[k + 2] == '1') {
                                        teste_subespressao = '1';
                                    } else {
                                        teste_subespressao = '0';
                                    }
                                } else if (teste_subespressao[k] == '&') {
                                    if (teste_subespressao[k - 2] == '1' && teste_subespressao[k + 2] == '1') {
                                        teste_subespressao = '1';
                                    } else {
                                        teste_subespressao = '0';
                                    }
                                } else if (teste_subespressao[k] == '>') {
                                    if (teste_subespressao[k - 2] == '1' && teste_subespressao[k + 2] == '0') {
                                        teste_subespressao = '0';
                                    } else {
                                        teste_subespressao = '1';
                                    }
                                } else if (teste_subespressao[k] == '<') {
                                    if (teste_subespressao[k - 2] == '1' && teste_subespressao[k + 2] == '0') {
                                        teste_subespressao = '0';
                                    } else if (teste_subespressao[k - 2] == '0' && teste_subespressao[k + 2] == '1') {
                                        teste_subespressao = '0';
                                    } else {
                                        teste_subespressao = '1';
                                    }
                                }
                            }




                            //aqui
                            if (teste_subespressao == "!0") {
                                arrvalores[k1][j1] = 1;
                            } else if (teste_subespressao == "!1") {
                                arrvalores[k1][j1] = 0;
                            } else if (teste_subespressao == "0") {
                                arrvalores[k1][j1] = 0;
                            } else if (teste_subespressao == "1") {
                                arrvalores[k1][j1] = 1;
                            }

                        }
                    }
                    linhas++;

                    saida1 << "Problema #" << i << endl;
                    //pra printar
                    for (int l1 = 0; l1 < colunas; l1++) {
                        saida1 << arrbase[l1] << " ";
                        if (l1 == qdevariaveis - 1) {
                            saida1 << "| ";
                        } else if (l1 == colunas) {
                            saida1 << arrbase[l1];
                        }
                    }
                    saida1 << endl;
                    for (int m1 = 0; m1 < linhas; m1++) {
                        for (int i = 0; i < colunas; i++) {
                            saida1 << arrvalores[m1][i] << " ";
                            if (i == qdevariaveis - 1) {
                                saida1 << "| ";
                                break;
                            }
                        }
                        for (int j = qdevariaveis; j < colunas; j++) {
                            int tamanho_espaco;
                            tamanho_espaco = arrbase[j].length();
                            for (int i = 0; i < tamanho_espaco - 1; i++) {
                                saida1 << " ";
                            }
                            saida1 << arrvalores[m1][j];
                        }
                        saida1 << endl;
                    }

                    bool satisfativel = false, refutavel = false, tautologia = false, insatifativel = false;
                    //print pra saber se é satisfatível
                    for (int n1 = 0; n1 < linhas; n1++) {
                        if (arrvalores[n1][colunas - 1] == 1) {
                            satisfativel = true;
                            break;
                        }
                    }

                    //print pra saber se é refutável
                    for (int i2 = 0; i2 < linhas; i2++) {
                        if (arrvalores[i2][colunas - 1] == 0) {
                            refutavel = true;
                            break;
                        }
                    }

                    if (satisfativel) {
                        saida1 << "Sim, é satisfatível" << endl;
                    } else if (satisfativel == false) {
                        saida1 << "Não, não é satisfatível" << endl;
                    }

                    if (refutavel) {
                        saida1 << "Sim, é refutável" << endl;
                    } else if (refutavel == false) {
                        saida1 << "Não, não é refutável" << endl;
                    }

                    if (refutavel == false) {
                        saida1 << "Sim, é tautologia" << endl;
                    }

                    if (satisfativel == false) {
                        saida1 << "Sim, é insatisfativel" << endl;
                    }

                    int contador_equivalencia = 0;
                    for (int j2 = 0; j2 < colunas - 1; j2++) {
                        for (int j = j2 + 1; j < colunas; j++) {
                            for (int i = 0; i < linhas; i++) {
                                if (arrvalores[i][j2] == arrvalores[i][j]) {
                                    contador_equivalencia++;
                                }
                            }
                            if (contador_equivalencia == pow(2, qdevariaveis)) {
                                saida1 << arrbase[j2] << " é equivalente a " << arrbase[j] << endl;
                            }
                            contador_equivalencia = 0;
                        }
                    }

                    bool consequencia = false;
                    for (int j2 = 0; j2 < colunas - 1; j2++) {
                        for (int j = j2 + 1; j < colunas; j++) {
                            for (int i = 0; i < linhas; i++) {
                                if (arrvalores[i][j] == 1 && arrvalores[i][j2] == 1) {
                                    consequencia = true;
                                } else if (arrvalores[i][j] == 1 && arrvalores[i][j2] == 0) {
                                    consequencia = false;
                                    break;
                                }
                            }
                            if (consequencia) {
                                saida1 << arrbase[j2] << " é consequência lógica de " << arrbase[j] << endl;
                            }
                            consequencia = false;
                        }
                    }


                } else if (msg[0] == 'R') {//AQUI COMEÇA A RESOLUÇÃO !!!!!!!!!!!!!!
                    saida2 << "Problema #" << i << endl;
                    bool continuar = true, abriu = false, hornSolver = true,taunt=false;
                    int x = 0;
                    string str;
                    msg[0] = msg[2] = '-';
                    str = msg;
                    if(str[1]== 'X'){
                        str[1]='-';
                        str.erase(remove(str.begin(), str.end(), '-'), str.end());
                        str.erase(remove(str.begin(), str.end(), ' '), str.end());
                        saida2<< "Se  @ é uma expressão e é uma tautologia ~@ é insat. ";
                        saida2<<"Seja @ = "<< str<<endl;
                        str.erase(remove(str.begin(), str.end(), '('), str.end());
                        str.erase(remove(str.begin(), str.end(), ')'), str.end());
                        taunt =true;
                        string provisoria= "(";
                        for(int nega=0;nega<str.length();nega++){
                            if(str[nega]=='~'){
                                if(str[nega+1]=='P')provisoria+="P";
                                else if(str[nega+1] == 'Q')provisoria+="Q";
                                else if(str[nega+1] == 'R')provisoria+="R";
                                else if(str[nega+1] == 'S')provisoria+="S";
                                nega++;
                            }else if(str[nega]=='&'){
                                provisoria+="v";
                            }else if(str[nega]=='v'){
                                provisoria+=")&(";
                            }else if(str[nega]=='-'){
                            }else{//variaveis
                                provisoria+="~";
                                if(str[nega]=='P')provisoria+="P";
                                else if(str[nega] == 'Q')provisoria+="Q";
                                else if(str[nega] == 'R')provisoria+="R";
                                else if(str[nega] == 'S')provisoria+="S";
                            }
                        }
                        provisoria+=")";
                        str=provisoria;
                        saida2<<"~@ = ";
                    }else str[1]='-';

                    str.erase(remove(str.begin(), str.end(), '-'), str.end());
                    saida2<< str<<endl;
                    str.erase(remove(str.begin(), str.end(), ' '), str.end());
                    int tamanho = str.length();
                    for (int a = 0; a < tamanho; a++) {// Teste de FNC
                        if (str[a] == 'P' || str[a] == 'Q' || str[a] == 'R' || str[a] == 'S' || str[a] == '~') {
                            //Procura se algo esta diferente dos caracteres padroes
                        } else if (str[a] == '&') {//garante que a clausula nao tem '&' no lugar errado
                            if (str[a - 1] != ')' || str[a + 1] != '(') {
                                continuar = false;
                                saida2 << "Não está na FNC." << endl;
                                break;
                            }
                        } else if (str[a] == 'v') {//garante que a clausula nao tem 'v' no lugar errado
                            if (str[a - 1] == ')' || str[a + 1] == '(') {
                                continuar = false;
                                saida2 << "Não está na FNC." << endl;
                                break;
                            }

                        } else if (str[a] == '(') {//garante que o programa sempre vai abrir depois fechar as parenteses
                            if (abriu) {
                                continuar = false;
                                saida2 << "Não está na FNC." << endl;
                                break;
                            } else {
                                abriu = true;
                            }
                        } else if (str[a] == ')') {
                            abriu = false;
                        } else {
                            continuar = false;
                            saida2 << "Não está na FNC." << endl;
                            break;

                        }
                    }
                    if (continuar && !taunt) {//Teste de Horn
                        int contador = 0;
                        for (int a = 0; a < tamanho; a++) {
                            if (str[a] == 'P' || str[a] == 'Q' || str[a] == 'R' || str[a] == 'S') {
                                //"If a Horn formula has no positive unit clauses, then it is satisfiable"
                                if (str[a - 1] == '(' && str[a + 1] == ')')hornSolver = false;
                                else if (str[a - 1] != '~')contador++;
                            } else if (str[a] == ')')contador = 0;
                            if (contador > 1) {
                                continuar = false;
                                saida2 << "Nem todas as cláusulas são de Horn." << endl;
                                break;
                            }
                        }
                    }

                    if (continuar) {// Teste de Sat
                        if (hornSolver) {// Se nenhuma clausula unica for positiva, já é sat
                            saida2<<"nenhuma clausula unitária é positiva, logo:"<<endl;
                            saida2 << "Sim, é satisfatível" << endl;

                        } else {
                            bool achou = true;
                            char uni = ' ';
                            int busca = 0, i = 0, f = 0, passo=1;
                            for (int a = 0; a < tamanho; a++) {

                                if (str[a] == 'P' || str[a] == 'Q' || str[a] == 'R' || str[a] == 'S') {
                                    if (str[a + 1] == ')' && str[a - 1] == '(') {//Unitaria positiva
                                        uni = str[a];
                                        str[a - 1] = '-';
                                        str[a] = '-';
                                        str[a + 1] = '-';
                                        if((a-2)>0)str[a-2]='-';
                                        else str[a+2]='-';
                                        for (int b = 0; b < tamanho; b++) {
                                            a = 0;
                                            if (str[b] == uni) {
                                                if (str[b - 1] == '~') {//Apagar a aparição
                                                    saida2<<"Passo: "<<passo<<" clausula: "<<str[b-1]<<str[b]<<str[b+1]<<endl;
                                                    str[b] = '-';
                                                    str[b-1]='-';
                                                    if(str[(b-2)]=='v')str[b-2]='-';
                                                    else if(str[(b+1)]=='v') str[b+1]='-';

                                                    str.erase(remove(str.begin(), str.end(), '-'), str.end());

                                                    saida2<<str<<endl;//Printando os passos
                                                    passo++;
                                                } else {//Apagar toda a claurula
                                                    while (achou) {//Procura '(' pra trás
                                                        if (str[b - busca] == '(')achou = false;
                                                        busca++;
                                                    }
                                                    i = b - busca - 1;
                                                    busca = 0;
                                                    achou = true;
                                                    while (achou) {//Procura ')' pra frente
                                                        if (str[b + busca] == ')')achou = false;
                                                        busca++;
                                                    }
                                                    f = b + busca - 1;
                                                    busca = 0;
                                                    achou = true;
                                                    for (int x = i; x < f + 1; x++) {
                                                        str[x] = '-';
                                                    }
                                                    saida2<<"Passo "<<passo<<endl;
                                                    str.erase(remove(str.begin(), str.end(), '-'), str.end());

                                                    saida2<<str<<endl;//Printando os passos
                                                    passo++;
                                                }

                                            }
                                        }
                                    } else if (str[a + 1] == ')' && str[a - 2] == '(') {//Unitaria negativa  q
                                        saida2<<"Passo: "<<passo<<" clausula: "<<str[a-2]<<str[a-1]<<str[a]<<str[a+1]<<endl;
                                        uni = str[a];
                                        str[a - 1] = '-';
                                        str[a - 2] = '-';
                                        str[a] = '-';
                                        str[a + 1] = '-';
                                        if((a-3)>0)str[a-3]='-';
                                        else str[a+2]='-';
                                        for (int b = 0; b < tamanho; b++) {
                                            a = 0;
                                            if (str[b] == uni) {
                                                if (str[b - 1] != '~') {//Apagar a aparição
                                                    str[b] = '-';

                                                    if(str[(b-1)]=='v'){
                                                        str[b-1]='-';
                                                    }else if(str[(b+1)]=='v'){
                                                        str[b+1]='-';
                                                    }

                                                    str.erase(remove(str.begin(), str.end(), '-'), str.end());

                                                    saida2<<str<<endl;//Printando os passos
                                                    passo++;
                                                } else {//Apagar toda a claurula
                                                    while (achou) {//Procura '(' pra trás
                                                        if (str[b - busca] == '(')achou = false;
                                                        busca++;
                                                    }
                                                    i = b - busca - 1;
                                                    busca = 0;
                                                    achou = true;
                                                    while (achou) {//Procura ')' pra frente
                                                        if (str[b + busca] == ')')achou = false;
                                                        busca++;
                                                    }
                                                    f = b + busca - 1;
                                                    busca = 0;
                                                    achou = true;
                                                    for (int x = i; x < f + 1; x++) {
                                                        str[x] = '-';
                                                    }
                                                    saida2<<"Passo "<<passo<<endl;
                                                    str.erase(remove(str.begin(), str.end(), '-'), str.end());

                                                    saida2<<str<<endl;//Printando os passos
                                                    passo++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            int conta = 0;
                            bool vazio = false;
                            for (int a = 0; a < tamanho; a++) {
                                if (str[a] == ')') {
                                    if (conta == 0)vazio = true;
                                    conta = 0;
                                } else if (str[a] == 'P' || str[a] == 'Q' || str[a] == 'R' || str[a] == 'S')conta++;
                            }
                            if (vazio){
                                if(taunt)saida2<<"É uma tautologia!"<<endl;
                                else
                                    saida2 << "Não, não é satisfatível." << endl;
                            } else saida2 << "Sim, é satisfatível." << endl;
                        }
                    }
                }
            }
        }
    }
    saida1.close();
    saida2.close();
    return 0;
}
