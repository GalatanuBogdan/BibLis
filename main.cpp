#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "biblioteci/ListeDubluInlantuite.h"
#include "biblioteci/Coada.h"
#include "biblioteci/ListaSimpluInlantuita.h"
#include "biblioteci/Stiva.h"
using namespace std;

void instructiuniLista()
{
    cout<<"1 -> insereaza un element la inceput\n";
    cout<<"2 -> elimina elementul din lista\n";
    cout<<"3 -> insereaza un element la sfarsit\n";
    cout<<"4 -> introdu un element la o pozitie\n";
    cout<<"Introduceti cifra corespunzatoare operatiei ce urmeaza sa o executati\n";
}

void instructiuniCoada()
{
    cout<<"1 -> insereaza un element in coada\n";
    cout<<"2 -> elimina elementul din coada\n";
    cout<<"Introduceti cifra corespunzatoare operatiei ce urmeaza sa o executati\n";
}


int indicaCareButonDupaCoordonate(int x, int y)
{
    if(x >= 46 && x <= 254 && y >= 217 && y <= 263)
        return 1; ///indicele pentru liste dublu inlantuite

    if(x >= 46 && x <= 254 && y >= 454 && y <= 500)
        return 2; ///indicele pentru coada

    if(x >= 46 && x <= 254 && y >= 98 && y <= 145)
        return 3; ///indicele pentru liste simplu inlantuite

    if(x >= 46 && x <= 254 && y >= 338 && y <= 382)
        return 4; ///indicele pentru stiva

    if(x >= 46 && x <= 254 && y >= 574 && y <= 620)
        return 0; ///indicele pentru iesire
    return -1;
}

void meniu(listaDubla & ldi, coada &c, lista l, stiva s)
{
    readimagefile("poze_meniuri/meniu.jpg", 0, 0, 1280, 720);
    settextjustify(0,2);
    int tipStructura;
    int mouseX, mouseY;
    getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);


    tipStructura = indicaCareButonDupaCoordonate(mouseX, mouseY);

    switch(tipStructura){
    case -1:
        meniu(ldi, c,l, s);
        break;
        case 0:
            exit(1);
            break;
        case 1:
            meniuLDI(ldi);
            break;
        case 2:
            meniuCoada(c);
            break;
        case 3:

            settextjustify(1,1);  resetEcranLista();   drawLista(l,START_POZ_X,START_POZ_Y);   meniuLista(l,START_POZ_X,START_POZ_Y);  meniu(ldi, c, l, s);
            break;
        case 4:
            settextjustify(1,1);  resetEcranStiva();   drawStiva(s,START_POZ_X,START_POZ_Y);   meniuStiva(s,START_POZ_X,START_POZ_Y);  meniu(ldi, c, l, s);
            break;
        }
        meniu(ldi, c, l, s);
}

int main()
{
    initwindow(WIDTH, HEIGHT, "BibLis");

    listaDubla ldi;
    initializeazaLDI(ldi);

    coada c;
    initializeazaCoada(c);

    lista l = listaVida();
    stiva s = stivaVida();

    meniu(ldi, c, l, s);

    getch();
    closegraph();
}



