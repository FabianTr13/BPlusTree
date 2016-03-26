#include <iostream>
#include <array>
using namespace std;

class Nodo{
    public:
    string indice;
    string dato;

    Nodo(string inx = "", string dat = ""){
        indice = inx;
        dato = dat;
    }
};

class NodoLista{
    public:
    Nodo claves [5];
    NodoLista *hijos [5];
    NodoLista *shojas;
    int ingresados;

    NodoLista(){
        this->ingresados = 0;
    }
};


class Arbol{
    public:
    NodoLista *raiz, *rHijo, *P, *raizHojas;
    int k, MAX, MIN, nivel;
    Nodo cajaT;
    bool esta, ea ;
    array<string,4> sugerencias;

    Arbol(){
        k = 0;
        esta    = ea = false;
        MAX     = 4;
        MIN     = 2;
        nivel   = 0;
        raizHojas = raiz = P = rHijo = NULL;
    }

bool arbolVacio(NodoLista *nodo){
    return ((nodo == NULL) || (nodo->ingresados == 0));
}

void refrescarRaizHojas(){
    nivel = altura ();
    NodoLista *aux = raiz;

    while (!arbolVacio(aux->hijos[0]))
        aux = aux->hijos[0];

    raizHojas = aux;
}

void insertar(string valor){
Nodo temp;
        temp.indice = valor;
        temp.dato = valor;
        insertarF(temp);
}

void insertarF (Nodo clave){
    ea = false;
    empujar(clave, raiz);
    if(ea){
        NodoLista *nuevo = new NodoLista();
        nuevo->ingresados = 1;
        nuevo->claves[1] = cajaT;
        nuevo->hijos [0] = raiz;
        nuevo->hijos [1] = rHijo;
        raiz = nuevo;
    }
    refrescarRaizHojas();
}


void empujar (Nodo clave, NodoLista *nodo){
    if(nodo == NULL){
        ea = true;
        cajaT = clave;
        rHijo = NULL;
    }
    else{
        esta = buscarNodo (clave, nodo);
        if(esta)
            cout<<"\nCodigo Repetido: "<< clave.indice << endl;
        else{
            empujar(clave, nodo->hijos[k]);
            buscarNodo(clave, nodo);

            if(ea){
                if(nodo->ingresados < MAX){
                    //cout << "Voy a meterhoja!" <<endl;
                    ea = false;
                    P = nodo;
                    meterHoja();
                }
                else{
                    //cout << "Voy a dividir!" << endl;
                    ea = true;
                    P = nodo;
                    dividir();
                }
            }
        }
    }
}


void meterHoja(){
    for(int i = P->ingresados; i >= k+1; i--){
            P->claves[i + 1] = P->claves[i];
            P->hijos [i + 1] = P->hijos [i];
    }
    P->claves[k+1] = cajaT;
    P->hijos [k+1] = rHijo;
    P->ingresados++;
}

void dividir(){
    NodoLista *temp = new NodoLista();
    int pos;

    if (k <= MIN)
        pos = MIN;
    else
        pos = MIN+1;

    for(int i = pos+1; i <= MAX; i++){
        temp->claves[i-pos] = P->claves[i];
        temp->hijos [i-pos] = P->hijos[i];
    }

    temp->ingresados = MAX-pos;
    P->ingresados = pos;

    if (k <= MIN)
        meterHoja();
    else{
        k = k-pos;
        NodoLista *aux = P;
        P = temp;
        meterHoja();
        P = aux;
    }
    cajaT = P->claves[P->ingresados];

    if(arbolVacio(P->hijos[0]))
        duplicar(temp);

    temp->hijos[0] = P->hijos[P->ingresados];
    temp->shojas = P->shojas;
    P->shojas = temp;

    P->ingresados--;
    rHijo = temp;
}

void duplicar (NodoLista *temp){
    for(int i = temp->ingresados; i >= 1; i--){
        temp->claves[i + 1] = temp->claves[i];
        temp->hijos [i + 1] = temp->hijos [i];
    }
    temp->claves[1] = cajaT;
    temp->ingresados++;
}

 void imprimirArbol(){
    if(!arbolVacio(raiz)){
        imprimirArbol(raiz);
        cout<<endl;
    }
    else
        cout<<"\nEl Arbol B+ esta Vacio!" << endl;
}

void imprimirArbol(NodoLista *nodo){
    if(!arbolVacio(nodo)){
        imprimirArbol(nodo->hijos[0]);
        for(int i = 1; i <= nodo->ingresados; i++){
            cout<<nodo->claves[i].indice<<" ";
            imprimirArbol(nodo->hijos[i]);
        }
    }
}

bool buscarNodo(Nodo clave, NodoLista *nodo){
        if(nodo == NULL)
            return false;
        else{
            if(clave.indice < nodo->claves[1].indice){
                    k = 0;
                    return esta = false;
            }
            else{
                k = nodo->ingresados;
                while((k > 1) && (clave.indice <nodo->claves[k].indice))
                    k--;

                esta = (clave.indice == nodo->claves[k].indice);
            }
            return esta;
        }
}

int altura(){
    int res = 0;
    NodoLista *aux = raiz;
    if (arbolVacio(aux)){
        cout<<"\nEl Arbol B+ esta Vacio!"<<endl;
        return 0;
    }else{
        while (!arbolVacio(aux)){
            res++;
            aux = aux->hijos[0];
        }
        return res;
    }
}

void imprimirHojas(){
    NodoLista *aux = raizHojas;
    if (arbolVacio(aux))
        cout << "\nEl Arbol B+ esta Vacio!" << endl;
    else{
        cout<<"Impresion del arbol B+:"<<endl;
        while (!arbolVacio(aux)){
            for (int i= 1; i <= aux->ingresados; i++)
                cout<<aux->claves[i].indice<<" ";
            aux = aux->shojas;
        }
    }
}

void BuscarSugerencias(string valor){
    Nodo clave;
    clave.dato = valor;
    clave.indice = valor;
    empujarPorSugerencias(clave,raiz);
}

void empujarPorSugerencias(Nodo clave, NodoLista *nodo){
    if(nodo == NULL){
        ea = true;
    }
    else{
        esta = buscarNodo (clave, nodo);
        if(esta)
            cout<<"\nCodigo Repetido: "<< clave.indice << endl;
        else{
            empujarPorSugerencias(clave, nodo->hijos[k]);
            buscarNodo(clave, nodo);

            if(ea){
                if(nodo->ingresados < MAX){
                    ea = false;
                    P = nodo;
                    for(int i = 0; i<4;i++)
                    sugerencias[i]=P->claves[i+1].dato;
                }
                else{
                    ea = true;
                    P = nodo;
                }
            }
        }
    }
}
};

int main(){
    Arbol H;

        H.insertar("acordo");
        H.insertar("acido");
        H.insertar("actor");
        H.insertar("bonito");
        H.insertar("ballena");
        H.insertar("bolla");
        H.insertar("caso");
        H.insertar("ceda");
        H.insertar("cosa");
        H.insertar("dedir");
        H.insertar("decir");
        H.insertar("dundo");
        H.insertar("eco");
        H.insertar("economia");
        H.insertar("eficaz");
        H.insertar("fabian");
        H.insertar("foca");
        H.insertar("fierro");
        H.insertar("gato");
        H.insertar("gano");
        H.insertar("gineo");
        H.insertar("hola");
        H.insertar("hoy");
        H.insertar("huy");
        H.insertar("zampo");
    cout<<"Hojas:\n";
    H.imprimirHojas();
    cout<<endl;
    cout<<"Arbol b+\n";
    H.imprimirArbol();
    cout << "\nLa altura del arbol b+ es: "<<H.altura()<< endl;
    H.BuscarSugerencias("fabsdsjh");
    cout<<"\n\n";
    for(int i = 1; i < 4; i++)
        cout<<H.sugerencias[i]<<" ";
    return 0;
}


