#include "tabbcalendario.h"
#include <queue>

TNodoABB::TNodoABB()
{
    item = TCalendario();
    iz = TABBCalendario();
    de = TABBCalendario();
}

TNodoABB::TNodoABB(const TNodoABB &nodo)
{
    item = nodo.item;
    iz = nodo.iz;
    de = nodo.de;
}

TNodoABB::~TNodoABB()
{
    item.~TCalendario();
    iz.~TABBCalendario();
    de.~TABBCalendario();
}

TNodoABB &TNodoABB::operator=(const TNodoABB &nodo)
{
    if (this != &nodo)
    {
        item = nodo.item;
        iz = nodo.iz;
        de = nodo.de;
    }
    return *this;
}

// =================================================================
// =================================================================

TABBCalendario::TABBCalendario()
{
    raiz = NULL;
}

TABBCalendario::TABBCalendario(const TABBCalendario &arbol)
{
    if (arbol.raiz != NULL)
    {
        TNodoABB *aux = new TNodoABB();
        aux->item = arbol.raiz->item;
        this->raiz = aux;
        this->raiz->iz = TABBCalendario(arbol.raiz->iz);
        this->raiz->de = TABBCalendario(arbol.raiz->de);
    }
    else
        raiz = NULL;
}

TABBCalendario::~TABBCalendario()
{
    if (raiz != NULL)
    {
        delete raiz;
        raiz = NULL;
    }
}

TABBCalendario &TABBCalendario::operator=(const TABBCalendario &arbol)
{
    if (this != &arbol)
    {
        this->~TABBCalendario();
        if (arbol.raiz != NULL)
        {
            TNodoABB *aux = new TNodoABB();
            aux->item = arbol.raiz->item;
            this->raiz = aux;
            this->raiz->iz = TABBCalendario(arbol.raiz->iz);
            this->raiz->de = TABBCalendario(arbol.raiz->de);
        }
    }
    return *this;
}

bool TABBCalendario::operator==(const TABBCalendario &arbol) const
{
    if (raiz == NULL && arbol.raiz == NULL)
        return true;
    if (raiz != NULL && arbol.raiz != NULL)
    {
        if (raiz->item == arbol.raiz->item)
        {
            return raiz->iz == arbol.raiz->iz && raiz->de == arbol.raiz->de;
        }
    }
    return false;
}

bool TABBCalendario::EsVacio() const
{
    return raiz == NULL;
}

bool TABBCalendario::Buscar(const TCalendario &cal) const
{
    if (raiz != NULL)
    {
        if (raiz->item == cal)
            return true;
        if (raiz->item > cal)
            return raiz->iz.Buscar(cal);
        if (raiz->item < cal)
            return raiz->de.Buscar(cal);
    }
    return false;
}

bool TABBCalendario::Insertar(const TCalendario &cal)
{
    if (Buscar(cal))
        return false;
    if (raiz == NULL)
    {
        raiz = new TNodoABB();
        raiz->item = cal;
        return true;
    }
    if (raiz->item > cal)
        return raiz->iz.Insertar(cal);
    if (raiz->item < cal)
        return raiz->de.Insertar(cal);
    return false;
}

bool TABBCalendario::Borrar(const TCalendario &cal)
{
    if (Buscar(cal))
    {
        if (raiz->item > cal)
            return raiz->iz.Borrar(cal);
        else if (raiz->item < cal)
            return raiz->de.Borrar(cal);
        else if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
        {
            delete raiz;
            raiz = NULL;
            return true;
        }
        else if (raiz->iz.raiz == NULL)
        {
            raiz = raiz->de.raiz;
            return true;
        }
        else if (raiz->de.raiz == NULL)
        {
            raiz = raiz->iz.raiz;
            return true;
        }
        else
        {
            TNodoABB *aux = raiz->iz.raiz;
            TCalendario sustituto = raiz->iz.raiz->item;
            while (!aux->de.EsVacio())
            {
                sustituto = raiz->de.raiz->item;
                aux = aux->de.raiz;
            }
            raiz->item = sustituto;
            return raiz->iz.Borrar(sustituto);
        }
    }
    else
    {
        return false;
    }
}

TCalendario TABBCalendario::Raiz() const
{
    if (raiz != NULL)
        return raiz->item;
    return TCalendario();
}

int TABBCalendario::Altura() const
{
    if (raiz != NULL)
    {
        int iz = raiz->iz.Altura();
        int de = raiz->de.Altura();
        return 1 + (iz > de ? iz : de);
    }
    return 0;
}

int TABBCalendario::Nodos() const
{
    if (raiz != NULL)
        return 1 + raiz->iz.Nodos() + raiz->de.Nodos();
    return 0;
}

int TABBCalendario::NodosHoja() const
{
    if (raiz != NULL)
    {
        if (raiz->iz.raiz == NULL && raiz->de.raiz == NULL)
            return 1;
        return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
    }
    return 0;
}

void TABBCalendario::InordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.InordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
        raiz->de.InordenAux(vector, pos);
    }
}

TVectorCalendario TABBCalendario::Inorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    InordenAux(vector, pos);
    return vector;
}

void TABBCalendario::PreordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        vector[pos] = raiz->item;
        pos++;
        raiz->iz.PreordenAux(vector, pos);
        raiz->de.PreordenAux(vector, pos);
    }
}

TVectorCalendario TABBCalendario::Preorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PreordenAux(vector, pos);
    return vector;
}

void TABBCalendario::PostordenAux(TVectorCalendario &vector, int &pos) const
{
    if (raiz != NULL)
    {
        raiz->iz.PostordenAux(vector, pos);
        raiz->de.PostordenAux(vector, pos);
        vector[pos] = raiz->item;
        pos++;
    }
}

TVectorCalendario TABBCalendario::Postorden() const
{
    int pos = 1;
    TVectorCalendario vector(Nodos());
    PostordenAux(vector, pos);
    return vector;
}

TVectorCalendario TABBCalendario::Niveles() const
{
    TVectorCalendario vector(Nodos());
    int pos = 1;
    if (raiz != NULL)
    {
        queue<TNodoABB *> cola;
        cola.push(raiz);
        while (!cola.empty())
        {
            TNodoABB *aux = cola.front();
            cola.pop();
            vector[pos] = aux->item;
            pos++;
            if (aux->iz.raiz != NULL)
                cola.push(aux->iz.raiz);
            if (aux->de.raiz != NULL)
                cola.push(aux->de.raiz);
        }
    }

    return vector;
}

TABBCalendario TABBCalendario::operator+(const TABBCalendario &arbol)
{
    TABBCalendario aux(*this);
    if (arbol.raiz != NULL)
    {
        TVectorCalendario v = arbol.Inorden();
        for (int i = 1; i <= v.Tamano(); i++)
            aux.Insertar(v[i]);
    }
    return aux;
}

TABBCalendario TABBCalendario::operator-(const TABBCalendario &arbol)
{
    TABBCalendario aux(*this);
    if (arbol.raiz != NULL)
    {
        TVectorCalendario v = arbol.Inorden();
        for (int i = 1; i <= v.Tamano(); i++)
            aux.Borrar(v[i]);
    }
    return aux;
}
