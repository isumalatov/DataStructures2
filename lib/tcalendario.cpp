#include "tcalendario.h"
#include <string.h>

int
TCalendario::daysInMonth(int m, int a) {
    int days;
    switch (m) {
        case 2:
            if (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0)) {
                days = 29;
            } else {
                days = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        default:
            days = 31;
            break;
    }
    return days;
}

void TCalendario::copia(const TCalendario &c) {
    dia = c.dia;
    mes = c.mes;
    anyo = c.anyo;
    delete[] mensaje; // Liberar la memoria antigua
    if (c.mensaje != NULL) {
        mensaje = new char[strlen(c.mensaje) + 1];
        strcpy(mensaje, c.mensaje);
    } else {
        mensaje = NULL;
    }
}

TCalendario::TCalendario() {
    dia = 1;
    mes = 1;
    anyo = 1900;
    mensaje = NULL;
}

TCalendario::TCalendario(int d, int m, int a, char * mens) {
    if (a < 1900 || m < 1 || m > 12 || d < 1 || d > daysInMonth(m, a)) {
        dia = 1;
        mes = 1;
        anyo = 1900;
        mensaje = NULL;
    } else {
        dia = d;
        mes = m;
        anyo = a;
        if (mens != NULL) {
            mensaje = new char[strlen(mens) + 1];
            strcpy(mensaje, mens);
        } else {
            mensaje = NULL;
        }
    }
}

TCalendario::TCalendario(const TCalendario &c) {
    copia(c);
}

TCalendario::~TCalendario() {
    dia = 1;
    mes = 1;
    anyo = 1900;
    if (mensaje != NULL) {
        delete[] mensaje;
        mensaje = NULL;
    }
}

TCalendario & TCalendario::operator=(const TCalendario &c) {
    if (this != &c) { // Protección contra autoasignación
        (*this).~TCalendario();
        copia(c);
    }
    return *this; // Devolver una referencia a este objeto
}

TCalendario TCalendario::operator+(int n) {
    TCalendario c(*this);
    for (int i = 0; i < n; i++) {
        c.dia++;
        if (c.dia > daysInMonth(c.mes, c.anyo)) {
            c.dia = 1;
            c.mes++;
            if (c.mes > 12) {
                c.mes = 1;
                c.anyo++;
            }
        }
    }
    
    return c;
}

TCalendario TCalendario::operator-(int n) {
    TCalendario c(*this);
    for (int i = 0; i < n; i++) {
        c.dia--;
        if (c.dia < 1) {
            c.mes--;
            if (c.mes < 1) {
                c.mes = 12;
                c.anyo--;
            }
            c.dia = daysInMonth(c.mes, c.anyo);
        }
    }

    if(c.anyo < 1900) {
        c.dia = 1;
        c.mes = 1;
        c.anyo = 1900;
        if(c.mensaje != NULL) {
            delete[] c.mensaje;
            c.mensaje = NULL;
        }
    }
    
    return c;
}

TCalendario TCalendario::operator++(int) {
    TCalendario c(*this);
    dia++;
    if (dia > daysInMonth(mes, anyo)) {
        dia = 1;
        mes++;
        if (mes > 12) {
            mes = 1;
            anyo++;
        }
    }
    return c;
}

TCalendario & TCalendario::operator++() {
    dia++;
    if (dia > daysInMonth(mes, anyo)) {
        dia = 1;
        mes++;
        if (mes > 12) {
            mes = 1;
            anyo++;
        }
    }
    return *this;
}

TCalendario TCalendario::operator--(int) {
    TCalendario c(*this);
    dia--;
    if (dia < 1) {
        mes--;
        if (mes < 1) {
            mes = 12;
            anyo--;
        }
        dia = daysInMonth(mes, anyo);
    }
    if(anyo < 1900) {
        dia = 1;
        mes = 1;
        anyo = 1900;
        if(mensaje != NULL) {
            delete[] mensaje;
            mensaje = NULL;
        }
    }
    return c;
}

TCalendario & TCalendario::operator--() {
    dia--;
    if (dia < 1) {
        mes--;
        if (mes < 1) {
            mes = 12;
            anyo--;
        }
        dia = daysInMonth(mes, anyo);
    }
    if(anyo < 1900) {
        dia = 1;
        mes = 1;
        anyo = 1900;
        if(mensaje != NULL) {
            delete[] mensaje;
            mensaje = NULL;
        }
    }
    return *this;
}

bool TCalendario::ModFecha(int d, int m, int a) {
    if (a < 1900 || m < 1 || m > 12 || d < 1 || d > daysInMonth(m, a)) {
        return false;
    }
    dia = d;
    mes = m;
    anyo = a;
    return true;
}

bool TCalendario::ModMensaje(char * mens) {
    delete[] mensaje;
    if (mens != NULL) {
        mensaje = new char[strlen(mens) + 1];
        strcpy(mensaje, mens);
    } else {
        mensaje = NULL;
    }
    return true;
}

bool TCalendario::operator==(const TCalendario &c) {
    bool iguales;

    iguales = dia == c.dia && mes == c.mes && anyo == c.anyo;

    if (iguales) {
        if (mensaje == NULL && c.mensaje == NULL) {
            iguales = true;
        } else if (mensaje == NULL || c.mensaje == NULL) {
            iguales = false;
        } else {
            iguales = strcmp(mensaje, c.mensaje) == 0;
        }
    }

    return iguales;
}

bool TCalendario::operator!=(const TCalendario &c) {
    return !(*this == c);
}

bool TCalendario::operator>(const TCalendario &c) {
    if (anyo > c.anyo) {
        return true;
    } else if (anyo < c.anyo) {
        return false;
    } else if (mes > c.mes) {
        return true;
    } else if (mes < c.mes) {
        return false;
    } else if (dia > c.dia) {
        return true;
    } else if (dia < c.dia) {
        return false;
    } else if (mensaje == NULL && c.mensaje == NULL) {
        return false;
    } else if (mensaje == NULL)
        return false;
    else if (c.mensaje == NULL)
        return true;
    else
        return strcmp(mensaje, c.mensaje) > 0;
}

bool TCalendario::operator<(const TCalendario &c) {
    return !(*this > c || *this == c);
}

bool TCalendario::EsVacio() {
    return dia == 1 && mes == 1 && anyo == 1900 && mensaje == NULL;
}

int TCalendario::Dia() const{
    return dia;
}

int TCalendario::Mes() const{
    return mes;
}

int TCalendario::Anyo() const{
    return anyo;
}

char * TCalendario::Mensaje() const{
    return mensaje;
}

ostream & operator<<(ostream &os, const TCalendario &c) {
    if(c.Dia() < 10) {
        os << "0" << c.Dia() << "/";
    }
    else {
        os << c.Dia() << "/";
    }
    if(c.Mes() < 10) {
        os << "0" << c.Mes() << "/";
    }
    else {
        os << c.Mes() << "/";
    }
    os << c.Anyo() << " ";
    if(c.Mensaje() == NULL) {
        os << "\"\"";
    }
    else {
        os << "\"" << c.Mensaje() << "\"";
    }
    return os;
}