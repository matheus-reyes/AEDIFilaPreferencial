#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->idade = -1;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->idade);
		atual = atual->ant;
	}
	printf("\n\n");
}


int consultarIdade(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->idade;
		atual = atual->prox;
	}
	return -1;
}



bool inserirPessoaNaFila(PFILA f, int id, int idade){
    if(id < 0 || idade < 0 || buscarID(f, id) != NULL){
        return false;
    }
    PONT novo = (PONT)malloc(sizeof(ELEMENTO));
    novo->id = id;
    novo->idade = idade;
    if(idade >= IDADEPREFERENCIAL){
        if(f->cabeca->ant == f->cabeca && f->cabeca->prox == f->cabeca){
            f->cabeca->ant = novo;
            f->cabeca->prox = novo;
            novo->ant = f->cabeca;
            novo->prox = f->cabeca;
        }else if(f->inicioNaoPref == f->cabeca && f->cabeca->ant != f->cabeca){
            f->cabeca->ant->prox = novo;
            novo->prox = f->cabeca;
            novo->ant = f->cabeca->ant;
            f->cabeca->ant = novo;
        }else if(f->cabeca->prox == f->inicioNaoPref){
            novo->prox = f->inicioNaoPref;
            novo->ant = f->cabeca;
            f->cabeca->prox = novo;
            f->inicioNaoPref->ant = novo;
        }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca){
            novo->prox = f->inicioNaoPref;
            novo->ant = f->inicioNaoPref->ant;
            f->inicioNaoPref->ant->prox = novo;
            f->inicioNaoPref->ant = novo;
        }
    }else{
        if(f->cabeca->ant == f->cabeca && f->cabeca->prox == f->cabeca){
            f->cabeca->ant = novo;
            f->cabeca->prox = novo;
            novo->ant = f->cabeca;
            novo->prox = f->cabeca;
            f->inicioNaoPref = novo;
        }else if(f->inicioNaoPref == f->cabeca && f->cabeca->ant != f->cabeca){
            f->cabeca->ant->prox = novo;
            novo->prox = f->cabeca;
            novo->ant = f->cabeca->ant;
            f->cabeca->ant = novo;
            f->inicioNaoPref = novo;
        }else if(f->cabeca->prox == f->inicioNaoPref){
            f->cabeca->ant->prox = novo;
            novo->prox = f->cabeca;
            novo->ant = f->cabeca->ant;
            f->cabeca->ant = novo;
        }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca){
            f->cabeca->ant->prox = novo;
            novo->prox = f->cabeca;
            novo->ant = f->cabeca->ant;
            f->cabeca->ant = novo;
        }
    }
	return true;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
    if(f->cabeca->prox == f->cabeca && f->cabeca->ant == f->cabeca){
        return false;
    }
    *id = f->cabeca->prox->id;
    PONT apagar = f->cabeca->prox;

    if(tamanho(f) == 1){
        f->cabeca->prox = f->cabeca;
        f->cabeca->ant = f->cabeca;
        f->inicioNaoPref = f->cabeca;
    }else if(f->inicioNaoPref == f->cabeca && f->cabeca->ant != f->cabeca && tamanho(f) > 1){
        f->cabeca->prox = f->cabeca->prox->prox;
        f->cabeca->prox->ant = f->cabeca;
    }else if(f->cabeca->prox == f->inicioNaoPref && f->cabeca->ant != f->cabeca && tamanho(f) > 1){
        f->cabeca->prox = f->cabeca->prox->prox;
        f->cabeca->prox->ant = f->cabeca;
        f->inicioNaoPref = f->cabeca->prox;
    }else if(f->inicioNaoPref != f->cabeca && f->cabeca->prox != f->inicioNaoPref && tamanho(f) > 1){
        f->cabeca->prox = f->cabeca->prox->prox;
        f->cabeca->prox->ant = f->cabeca;
    }

    free(apagar);
	return true;
}


bool desistirDaFila(PFILA f, int id){
    if(buscarID(f,id) == NULL){
        return false;
    }

    PONT apagar = buscarID(f,id);

    if(f->cabeca->prox == apagar && f->cabeca->ant == apagar){
        f->cabeca->prox = f->cabeca;
        f->cabeca->ant = f->cabeca;
        f->inicioNaoPref = f->cabeca;
    }else if(f->cabeca->prox == f->inicioNaoPref && f->cabeca->prox == apagar && tamanho(f) > 1){
        f->cabeca->prox = apagar->prox;
        apagar->prox->ant = f->cabeca;
        f->inicioNaoPref = apagar->prox;
    }else if(f->cabeca->prox == f->inicioNaoPref && f->cabeca->ant == apagar && tamanho(f) > 1){
        f->cabeca->ant->ant->prox = f->cabeca;
        f->cabeca->ant = f->cabeca->ant->ant;
    }else if(f->inicioNaoPref == f->cabeca && f->cabeca->prox == apagar && tamanho(f) > 1){
        apagar->prox->ant = f->cabeca;
        f->cabeca->prox = apagar->prox;
    }else if(f->inicioNaoPref == f->cabeca && f->cabeca->ant == apagar && tamanho(f) > 1){
        f->cabeca->ant->ant->prox = f->cabeca;
        f->cabeca->ant = f->cabeca->ant->ant;
    }else if(f->cabeca->prox == apagar && f->cabeca->prox->prox == f->inicioNaoPref && tamanho(f) == 2){
        f->cabeca->prox = f->inicioNaoPref;
        f->inicioNaoPref->ant = f->cabeca;
    }else if(f->inicioNaoPref == apagar && f->cabeca->prox != f->inicioNaoPref && tamanho(f) == 2){
        f->cabeca->prox->prox = f->cabeca;
        f->cabeca->ant = f->cabeca->prox;
    }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca && f->inicioNaoPref->prox != f->cabeca && f->inicioNaoPref == apagar && tamanho(f) > 2){
        f->inicioNaoPref->ant->prox = f->inicioNaoPref->prox;
        f->inicioNaoPref->prox->ant = f->inicioNaoPref->ant;
        f->inicioNaoPref = f->inicioNaoPref->prox;
    }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca && f->inicioNaoPref->prox != f->cabeca && f->cabeca->ant == apagar && tamanho(f) > 2){
        f->cabeca->ant->ant->prox = f->cabeca;
        f->cabeca->ant = f->cabeca->ant->ant;
    }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca && f->inicioNaoPref->prox != f->cabeca && f->cabeca->prox == apagar && tamanho(f) > 2){
        f->cabeca->prox->prox->ant = f->cabeca;
        f->cabeca->prox = f->cabeca->prox->prox;
    }else if(f->cabeca->prox != f->inicioNaoPref && f->inicioNaoPref != f->cabeca && f->inicioNaoPref->prox != f->cabeca && f->inicioNaoPref->ant == apagar && tamanho(f) > 2){
        f->inicioNaoPref->ant->ant->prox = f->inicioNaoPref;
        f->inicioNaoPref->ant = f->inicioNaoPref->ant->ant;
    }

    free(apagar);
	return true;
}
