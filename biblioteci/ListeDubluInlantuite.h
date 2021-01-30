#include <math.h>
#include <ctime>
#include "Preferences.h"
#include "GlobalFunctions.h"

using namespace std;
double pi = 3.14159265359;
typedef int tip;
tip EROARE = -1;
char chrWait = 'a';

struct nodLDI {
    tip info;
    nodLDI * prec;
    nodLDI * urm;
    int lungime_elm = 0;
};

struct listaDubla {
    //nodLDI * stanga;
    nodLDI * prim;
    //nodLDI * curent;
    nodLDI * ultim;
    //nodLDI * dreapta;
    int nrElemente = 0; // va fi 0 cand lista e vida, chiar daca are doar santinelele
};


bool esteLDIVida(listaDubla L) {
    return !L.nrElemente;
}

void initializeazaLDI(listaDubla & L) {
    L.prim = NULL;
    L.ultim = NULL;
    L.nrElemente = 0;
}

tip scoatePrimul(listaDubla & L) {
    if (!esteLDIVida(L)) {
        tip element;
        nodLDI * toDelete = L.prim;
        element = L.prim -> info;
        L.nrElemente--;
        L.prim = L.prim -> urm;
        delete(toDelete);
        return element;
    } else {
        //std::cerr << "EROARE. Lista e vida.";
        return EROARE;
    }
}

void golesteLDI(listaDubla & L) {
    while (!esteLDIVida(L))
        scoatePrimul(L);
}

void adaugaInFata(listaDubla &L, tip element)
{
    nodLDI * nodLDI_nou = new nodLDI;
    nodLDI_nou->info=element;
    if(element == 0){
        nodLDI_nou->lungime_elm = 1;
    }
    else
        nodLDI_nou->lungime_elm = log10(element) + 1;

    if (L.nrElemente>0)
    {
        nodLDI_nou->urm = L.prim;
        L.prim->prec = nodLDI_nou;
        nodLDI_nou->prec = NULL;
        L.prim = nodLDI_nou;
    }
    else
    {
        nodLDI_nou->urm = NULL;
        nodLDI_nou->prec = NULL;
        L.prim = nodLDI_nou;
        L.ultim = L.prim;
    }
    L.nrElemente++;
}

void afiseazaLDIInConsola(listaDubla L){
    nodLDI * current = L.prim;
    cout<<'\n';
    while(current != NULL)
    {
        cout<<current->info<<' ';
        current = current->urm;
    }
    cout<<'\n';
}

void afiseazaLDI(int startPoz_x, int startPoz_y, listaDubla L, bool nullStanga, bool nullDreapta) {

    bool adauga_inf_prim = true;
    bool adauga_inf_ultim = true;

    //resetEcran();
    punct pivot;
    pivot.x = startPoz_x;
    pivot.y = startPoz_y;
    punct startSageata;
    punct sfarsitSageata;
    nodLDI * nodLDI_curent = L.prim;
    if(nullStanga)          ///Adaugam null in stanga
    {
        deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
        outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        startSageata.x = pivot.x + 4 * latimeElm / 2;
        startSageata.y = pivot.y;
        sfarsitSageata.x = pivot.x + 4 * latimeElm / 2 + distantaIntreElm;
        sfarsitSageata.y = pivot.y;
        if(nodLDI_curent)
            drawArrow(sfarsitSageata, startSageata, -5);
        if(nodLDI_curent)
            pivot.x += distantaIntreElm + 4 * latimeElm / 2 + nodLDI_curent->lungime_elm * latimeElm / 2;
    }

    if (!esteLDIVida(L))
    {
        while (nodLDI_curent != NULL) {
            char numtoText[100];
            convertToChar(numtoText, nodLDI_curent->info);
            if(nodLDI_curent->lungime_elm < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
            deseneazaInstanta(inaltimeElm, latimeElm * nodLDI_curent->lungime_elm, pivot);


            if(nodLDI_curent == L.prim && adauga_inf_prim)
            {
                outtextxy(pivot.x - nodLDI_curent->lungime_elm * latimeElm / 2, pivot.y - 35, infP);
            }

            if(nodLDI_curent == L.ultim && adauga_inf_ultim)
            {
                outtextxy(pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2, pivot.y - 35, infU);
            }



            if(nodLDI_curent->urm != NULL)
            {

                startSageata.x = pivot.x + latimeElm * nodLDI_curent->lungime_elm / 2;
                startSageata.y = pivot.y;
                sfarsitSageata.x = pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2 + distantaIntreElm;
                sfarsitSageata.y = pivot.y;
                drawArrow(startSageata, sfarsitSageata, 5);
                drawArrow(sfarsitSageata, startSageata, -5);
                pivot.x += distantaIntreElm + latimeElm * nodLDI_curent->lungime_elm / 2 + latimeElm * nodLDI_curent->urm->lungime_elm / 2;
            }
            nodLDI_curent = nodLDI_curent -> urm;
        }
    }

    if(nullDreapta)
    {

        if(!esteLDIVida(L))
        {
            ///inseram casuta NULL
            //cout<<"Lungime ultim = "<<L.ultim->lungime_elm<<'\n';
            punct inceput_sageata, sfarsit_sageata;
            inceput_sageata.x = pivot.x + L.ultim->lungime_elm * latimeElm / 2;
            sfarsit_sageata.x = pivot.x + L.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm;
            inceput_sageata.y = sfarsit_sageata.y = startPoz_y;
            pivot.x += L.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;
            drawArrow(inceput_sageata, sfarsit_sageata, 5);
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
        else
        {
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
    }
}

void afiseazaLDIDeLanodLDI(nodLDI * nodLDI_curent, int start_poz_x, int start_poz_y, bool nullDreapta)
{
    punct pivot;
    pivot.x = start_poz_x;
    pivot.y = start_poz_y;
    nodLDI * copie = nodLDI_curent, *ultim;
    punct startSageata;
    punct sfarsitSageata;

    while(nodLDI_curent != NULL)
    {
        ultim = nodLDI_curent;
        nodLDI_curent = nodLDI_curent->urm;
    }

    nodLDI_curent = copie;
    while (nodLDI_curent != NULL) {
            char numtoText[100];
            convertToChar(numtoText, nodLDI_curent->info);
            if(nodLDI_curent->lungime_elm < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
            deseneazaInstanta(inaltimeElm, latimeElm * nodLDI_curent->lungime_elm, pivot);

            if(nodLDI_curent == ultim)
            {
                outtextxy(pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2, pivot.y - 35, infU);
            }

            if(nodLDI_curent->urm != NULL)
            {

                startSageata.x = pivot.x + latimeElm * nodLDI_curent->lungime_elm / 2;
                startSageata.y = pivot.y;
                sfarsitSageata.x = pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2 + distantaIntreElm;
                sfarsitSageata.y = pivot.y;
                drawArrow(startSageata, sfarsitSageata, 5);
                drawArrow(sfarsitSageata, startSageata, -5);
                pivot.x += distantaIntreElm + latimeElm * nodLDI_curent->lungime_elm / 2 + latimeElm * nodLDI_curent->urm->lungime_elm / 2;
            }
            nodLDI_curent = nodLDI_curent -> urm;
        }

    if(nullDreapta)
    {

        if(copie)
        {
            ///inseram casuta NULL
            //cout<<"Lungime ultim = "<<L.ultim->lungime_elm<<'\n';
            punct inceput_sageata, sfarsit_sageata;
            inceput_sageata.x = pivot.x + ultim->lungime_elm * latimeElm / 2;
            sfarsit_sageata.x = pivot.x + ultim->lungime_elm * latimeElm / 2 + distantaIntreElm;
            inceput_sageata.y = sfarsit_sageata.y = start_poz_y;
            pivot.x += ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;
            drawArrow(inceput_sageata, sfarsit_sageata, 5);
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
        else
        {
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
    }

}

void afiseazaLDIPanaLaIndex(int startPoz_x, int startPoz_y, listaDubla L, int index ,bool nullStanga, bool nullDreapta) {

    bool adauga_inf_prim = true;
    bool adauga_inf_ultim = true;

    //resetEcran();
    punct pivot;
    pivot.x = startPoz_x;
    pivot.y = startPoz_y;
    punct startSageata;
    punct sfarsitSageata;
    nodLDI * nodLDI_curent = L.prim;

    nodLDI_curent = L.prim;

    if(nullStanga)          ///Adaugam null in stanga
    {
        deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
        outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        startSageata.x = pivot.x + 4 * latimeElm / 2;
        startSageata.y = pivot.y;
        sfarsitSageata.x = pivot.x + 4 * latimeElm / 2 + distantaIntreElm;
        sfarsitSageata.y = pivot.y;
        if(nodLDI_curent)
            drawArrow(sfarsitSageata, startSageata, -5);
        if(nodLDI_curent)
            pivot.x += distantaIntreElm + 4 * latimeElm / 2 + nodLDI_curent->lungime_elm * latimeElm / 2;
    }

    if (!esteLDIVida(L))
    {
        int i = 0;
        while (i <= index && nodLDI_curent){
            char numtoText[100];
            convertToChar(numtoText, nodLDI_curent->info);
            if(nodLDI_curent->lungime_elm < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
            deseneazaInstanta(inaltimeElm, latimeElm * nodLDI_curent->lungime_elm, pivot);


            if(nodLDI_curent == L.prim && adauga_inf_prim)
            {
                outtextxy(pivot.x - nodLDI_curent->lungime_elm * latimeElm / 2, pivot.y - 35, infP);
            }

            if(nodLDI_curent == L.ultim && adauga_inf_ultim)
            {
                outtextxy(pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2, pivot.y - 35, infU);
            }



            if(nodLDI_curent->urm != NULL)
            {

                startSageata.x = pivot.x + latimeElm * nodLDI_curent->lungime_elm / 2;
                startSageata.y = pivot.y;
                sfarsitSageata.x = pivot.x + nodLDI_curent->lungime_elm * latimeElm / 2 + distantaIntreElm;
                sfarsitSageata.y = pivot.y;
                if(i < index){
                    drawArrow(startSageata, sfarsitSageata, 5);
                    drawArrow(sfarsitSageata, startSageata, -5);
                }
                pivot.x += distantaIntreElm + latimeElm * nodLDI_curent->lungime_elm / 2 + latimeElm * nodLDI_curent->urm->lungime_elm / 2;
            }
            nodLDI_curent = nodLDI_curent -> urm;
            i += 1;
        }
    }

    if(nullDreapta)
    {

        if(!esteLDIVida(L))
        {
            ///inseram casuta NULL
            //cout<<"Lungime ultim = "<<L.ultim->lungime_elm<<'\n';
            punct inceput_sageata, sfarsit_sageata;
            inceput_sageata.x = pivot.x + L.ultim->lungime_elm * latimeElm / 2;
            sfarsit_sageata.x = pivot.x + L.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm;
            inceput_sageata.y = sfarsit_sageata.y = startPoz_y;
            pivot.x += L.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;
            drawArrow(inceput_sageata, sfarsit_sageata, 5);
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
        else
        {
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        }
    }
}


void AnimatieAdaugareLaFata(int poz_x, int poz_y, listaDubla &L, tip element)
{
    resetEcran();
    char numtoText[100];
    int lungime_elm;
    punct elm_pos;
    convertToChar(numtoText, element);
    elm_pos.x = poz_x;
    elm_pos.y = poz_y;
    if(element == 0)
        lungime_elm = 1;
    else
        lungime_elm = log10(element) + 1;


    if(esteLDIVida(L)) ///Adaugare cand lista este vida
    {
        punct null_poz_stanga, null_poz_dreapta, elm_central, inceput_sageata, sfarsit_sageata, indicator_prim, indicator_ultim;

        ///null din stanga
        null_poz_stanga.x = poz_x;
        null_poz_stanga.y = poz_y;
        deseneazaInstanta(inaltimeElm, latimeElm * 4, null_poz_stanga);
        outtextxy(null_poz_stanga.x - latimeElm / 2, null_poz_stanga.y - inaltimeElm / 4, infNull);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,infNullStanga);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infNullDreapta);
        ///null din dreapta
        null_poz_dreapta.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm + 4 * latimeElm / 2 ;
        null_poz_dreapta.y = poz_y;
        deseneazaInstanta(inaltimeElm, latimeElm * 4, null_poz_dreapta);
        outtextxy(null_poz_dreapta.x - latimeElm / 2, null_poz_dreapta.y - inaltimeElm / 4, infNull);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        ///element central
        elm_central.x = poz_x + lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;
        elm_central.y = poz_y;
        deseneazaInstanta(inaltimeElm, latimeElm * lungime_elm, elm_central);
        if(lungime_elm < 2)
            outtextxy( elm_central.x - latimeElm / 8, elm_central.y - inaltimeElm / 4, numtoText);
        else
            outtextxy( elm_central.x - latimeElm / 2,  elm_central.y - inaltimeElm / 4, numtoText);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+90,infCreareNod);


        ///Sageata de la Element la NULL Stanga
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        outtextxy(WIDTH/2+240,HEIGHT/2.4+120,infLegaturaStangaCatreNull);
        sfarsit_sageata.x = poz_x + 4 * latimeElm / 2;
        sfarsit_sageata.y = poz_y;
        inceput_sageata.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm;
        inceput_sageata.y = poz_y;
        drawArrow(inceput_sageata, sfarsit_sageata, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        ///Sageata de la Element la NULL Dreapta
        outtextxy(WIDTH/2+240,HEIGHT/2.4+150, infLegaturaDreaptaCatreNull);
        sfarsit_sageata.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm;
        sfarsit_sageata.y = poz_y;
        inceput_sageata.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm;
        inceput_sageata.y = poz_y;
        drawArrow(inceput_sageata, sfarsit_sageata, 5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';


        ///Adaugam L.prim
        outtextxy(WIDTH/2+240,HEIGHT/2.4+180, infMarcareAdresaInceput);
        indicator_prim.x = elm_central.x - lungime_elm * latimeElm / 2;
        indicator_prim.y = elm_central.y - 35;
        outtextxy(indicator_prim.x, indicator_prim.y, infP);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';


        ///Adaugam L.ultim
        outtextxy(WIDTH/2+240,HEIGHT/2.4+210,infMarcareAdresaSfarsit);
        indicator_ultim.x = elm_central.x + lungime_elm * latimeElm / 2;
        indicator_ultim.y = elm_central.y - 35;
        outtextxy(indicator_ultim.x, indicator_ultim.y, infU);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

    }
    else
    {
        punct inceput_sageata, sfarsit_sageata, inceput_sageata1, sfarsit_sageata1, inceput_sageata2, sfarsit_sageata2, null_poz_stanga;
        ///inseram casuta NULL din stanga
        null_poz_stanga = elm_pos;
        deseneazaInstanta(inaltimeElm, latimeElm * 4, null_poz_stanga);
        outtextxy(null_poz_stanga.x - latimeElm / 2, elm_pos.y - inaltimeElm / 4, infNull);

        ///inseram restul listei cu spatiu pt primul element
        afiseazaLDI(poz_x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm + L.prim->lungime_elm * latimeElm / 2, poz_y, L, false, true);




        ///retinem coordonate legaturi pentru nullStanga
        sfarsit_sageata1.x = null_poz_stanga.x + 4 * latimeElm / 2;
        sfarsit_sageata1.y = poz_y;
        inceput_sageata1.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm;
        inceput_sageata1.y = poz_y + distantaIntreElm;



        ///retinem coordonate legaturi pentru elmSpreDreapta

        sfarsit_sageata2.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm;
        sfarsit_sageata2.y = poz_y;
        inceput_sageata2.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm;
        inceput_sageata2.y = poz_y + distantaIntreElm;

        drawArrow(sfarsit_sageata2, sfarsit_sageata1, -5);


        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        elm_pos.y += distantaIntreElm;
        elm_pos.x += 4 * latimeElm / 2 + distantaIntreElm + latimeElm * lungime_elm / 2;

        ///Afisam elementul nou
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infCreareNod);
        deseneazaInstanta(inaltimeElm, latimeElm * lungime_elm, elm_pos);
        if(lungime_elm < 2)
            outtextxy(elm_pos.x - latimeElm / 8, elm_pos.y - inaltimeElm / 4, numtoText);
        else
            outtextxy(elm_pos.x - latimeElm / 2, elm_pos.y - inaltimeElm / 4, numtoText);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';


        ///Adaugam sageata din stanga
        outtextxy(WIDTH/2+240,HEIGHT/2.4+60,infLegaturaStangaCatreNull);
        drawArrow(inceput_sageata1, sfarsit_sageata1, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        ///Stergem legatura dintre dreapta si NULL
        outtextxy(WIDTH/2+240,HEIGHT/2.4+90,infStergereLegaturaNull);
        setcolor(0);
        sfarsit_sageata2.x -= 1;
        sfarsit_sageata1.x += 1;
        drawArrow(sfarsit_sageata2, sfarsit_sageata1, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        setcolor(15);

        outtextxy(WIDTH/2+240,HEIGHT/2.4+120,infSchimbareAdresaDreapta);
        ///Adaugam sageata din dreapta
        drawArrow(inceput_sageata2, sfarsit_sageata2, 5);
        drawArrow(sfarsit_sageata2, inceput_sageata2, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';



        ///incepem pozitionarea elementului nou:
        while(elm_pos.y > poz_y)
        {
            resetEcran();
            ///inseram casuta NULL din stanga
            deseneazaInstanta(inaltimeElm, latimeElm * 4, null_poz_stanga);
            outtextxy(null_poz_stanga.x - latimeElm / 2, null_poz_stanga.y - inaltimeElm / 4, infNull);

            ///Repozitionam elementul nou
            elm_pos.y -= 1;
            deseneazaInstanta(inaltimeElm, latimeElm * lungime_elm, elm_pos);

            if(lungime_elm < 2)
                outtextxy(elm_pos.x - latimeElm / 8, elm_pos.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(elm_pos.x - latimeElm / 2, elm_pos.y - inaltimeElm / 4, numtoText);

            ///Legatura din stanga
            sfarsit_sageata.x = null_poz_stanga.x + 4 * latimeElm / 2;
            sfarsit_sageata.y = poz_y;
            inceput_sageata.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm;
            inceput_sageata.y = elm_pos.y;
            drawArrow(inceput_sageata, sfarsit_sageata, -5);


            ///Legatura din dreapta

            sfarsit_sageata.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm;
            sfarsit_sageata.y = poz_y;
            inceput_sageata.x = null_poz_stanga.x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm;
            inceput_sageata.y = elm_pos.y;
            drawArrow(inceput_sageata, sfarsit_sageata, 5);
            drawArrow(sfarsit_sageata, inceput_sageata, -5);

            ///punem partea din dreapta a listei
            afiseazaLDI(poz_x + 4 * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm + distantaIntreElm + L.prim->lungime_elm * latimeElm / 2, poz_y, L, false, true);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infRepozitionare);
            //usleep(300);
        }

        ///schimbam pozitia lui P;
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,infMarcareAdresaInceput);
        setcolor(0);
        outtextxy(elm_pos.x + latimeElm * lungime_elm / 2 + distantaIntreElm, elm_pos.y - 35, infP);
        setcolor(15);
        outtextxy(elm_pos.x - latimeElm * lungime_elm / 2, elm_pos.y - 35, infP);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    }

    adaugaInFata(L, element);
    resetEcran();
    afiseazaLDI(poz_x, poz_y, L, true, true);
}

void adaugaInSpate(listaDubla & L, tip toAdd){

    if(L.nrElemente == 0)
    {
        adaugaInFata(L, toAdd);
        return ;
    }
    nodLDI * current = L.ultim, *nodLDINou;
    nodLDINou = new nodLDI;
    nodLDINou->info = toAdd;
    nodLDINou->prec = current;
    nodLDINou->urm = NULL;
    current->urm = nodLDINou;
    L.ultim = nodLDINou;
    L.nrElemente += 1;
    if(toAdd == 0){
        nodLDINou->lungime_elm = 1;
    }
    else
        nodLDINou->lungime_elm = log10(toAdd) + 1;
}

void AnimatieAdaugareLaSpate(int poz_x, int poz_y, listaDubla & L, tip toAdd){
    resetEcran();

    if(L.nrElemente == 0)
    {
        AnimatieAdaugareLaFata(poz_x, poz_y, L, toAdd);
        return;
    }


    nodLDI * current = L.prim;
    int lungime_elm;

    char numtoText[100];
    convertToChar(numtoText, toAdd);

    afiseazaLDI(poz_x, poz_y, L, true, false);
    punct pivot, nullDreapta, startSageata, sfarsitSageata;
    pivot.x = poz_x;

    pivot.x += 4 * latimeElm / 2 + distantaIntreElm; ///elm null din stanga

    if(current)
        pivot.x += current->lungime_elm * latimeElm / 2;
    pivot.y = poz_y;

    while(current)
    {
        //line(pivot.x, pivot.y - 30, pivot.x, pivot.y + 30);
        if(current->urm)
            pivot.x +=  current->lungime_elm * latimeElm / 2 + distantaIntreElm + current->urm->lungime_elm * latimeElm / 2;
        current = current->urm;
    }

    if(toAdd == 0)
        lungime_elm = 1;
    else
        lungime_elm = log10(toAdd) + 1;

    pivot.x += L.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm / 2;

    nullDreapta = pivot;
    nullDreapta.x +=  lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;

    outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infCreareNod);
    pivot.y += distantaIntreElm;
    deseneazaInstanta(inaltimeElm, latimeElm * lungime_elm, pivot);

    if(lungime_elm < 2)
        outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
    else
        outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

    deseneazaInstanta(inaltimeElm, latimeElm * 4, nullDreapta);
    outtextxy(nullDreapta.x - latimeElm / 2, nullDreapta.y - inaltimeElm / 4, infNull);
    startSageata.x = pivot.x - lungime_elm * latimeElm / 2 - distantaIntreElm;
    startSageata.y = poz_y;
    sfarsitSageata.x = pivot.x + lungime_elm * latimeElm / 2 + distantaIntreElm;
    sfarsitSageata.y = poz_y;
    drawArrow(startSageata, sfarsitSageata, 5);

    while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    ///anulam sageata catre null
    outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infLegareDeUltimulElement);
    setcolor(0);
    startSageata.x += 1;
    drawArrow(startSageata, sfarsitSageata, 5);
    setcolor(15);


    startSageata.y = pivot.y - distantaIntreElm;
    sfarsitSageata.y = pivot.y;
    startSageata.x = pivot.x - lungime_elm * latimeElm / 2 - distantaIntreElm;
    sfarsitSageata.x = pivot.x - lungime_elm * latimeElm / 2;
    drawArrow(startSageata, sfarsitSageata, 5);
    while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    drawArrow(sfarsitSageata, startSageata, -5);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+90, infLegareNodDeUltimulElement);
    while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    outtextxy(WIDTH/2+240,HEIGHT/2.4+120, infLegaturaDreaptaCatreNull);
    startSageata.x = pivot.x + lungime_elm * latimeElm / 2;
    sfarsitSageata.x = pivot.x + lungime_elm * latimeElm / 2 + distantaIntreElm;
    startSageata.y = pivot.y;
    sfarsitSageata.y = pivot.y - distantaIntreElm;
    drawArrow(startSageata, sfarsitSageata, 5);
    while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';


    while(pivot.y > poz_y)
    {
        resetEcran();
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infRepozitionare);
        pivot.y -= 1;
        deseneazaInstanta(inaltimeElm, latimeElm * lungime_elm, pivot);
        if(lungime_elm < 2)
        	outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
    	else
        	outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

        outtextxy(nullDreapta.x - latimeElm / 2, nullDreapta.y - inaltimeElm / 4, infNull);
        afiseazaLDI(poz_x, poz_y, L, true, false);
        deseneazaInstanta(inaltimeElm, latimeElm * 4, nullDreapta);
        startSageata.y = poz_y;
        sfarsitSageata.y = pivot.y;
        startSageata.x = pivot.x - lungime_elm * latimeElm / 2 - distantaIntreElm;
        sfarsitSageata.x = pivot.x - lungime_elm * latimeElm / 2;
        drawArrow(startSageata, sfarsitSageata, 5);
        drawArrow(sfarsitSageata, startSageata, -5);
        startSageata.x = pivot.x + lungime_elm * latimeElm / 2;
        sfarsitSageata.x = pivot.x + lungime_elm * latimeElm / 2 + distantaIntreElm;
        startSageata.y = pivot.y;
        sfarsitSageata.y = poz_y;
        drawArrow(startSageata, sfarsitSageata, 5);
        //usleep(300);
    }
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infCreareNod);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infLegareDeUltimulElement);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+90, infLegareNodDeUltimulElement);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+120,infLegaturaDreaptaCatreNull);

    while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    outtextxy(WIDTH/2+240,HEIGHT/2.4+150, infMarcareAdresaSfarsit);
    ///schimbam adresa ultimului element al listei
    setcolor(0);
    outtextxy(pivot.x - latimeElm * lungime_elm / 2 - distantaIntreElm, pivot.y - 35, infU);
    setcolor(15);
     outtextxy(pivot.x + latimeElm * lungime_elm /2, pivot.y - 35, infU);
    while(chrWait != BUTON)
        chrWait = getch();
    chrWait = 'a';

    adaugaInSpate(L, toAdd);
    resetEcran();
    afiseazaLDI(poz_x, poz_y, L, true, true);
}


void eliminareLDI(listaDubla &L, tip target)
{
    nodLDI * current = L.prim;
    nodLDI * toDelete;
    while(current != NULL)
    {
        toDelete = current;
        if(current->info == target)
        {
            if(current == L.prim && current == L.ultim)
            {
                L.prim = NULL;
                L.ultim = NULL;
            }
            else
                if(current == L.prim)
                {
                    L.prim = current->urm;
                    current->urm->prec = current->prec;
                }
                else
                    if(current == L.ultim)
                    {
                        current->prec->urm = current->urm;
                        L.ultim = current->prec;
                    }
                    else
                    {
                        current->prec->urm = current->urm;
                        current->urm->prec = current->prec;
                    }
            current = current->urm;
            delete toDelete;
            L.nrElemente--;
            return;
        }
        else
            current = current->urm;
    }



}


void eliminareLDIAnimatie(int poz_x, int poz_y, listaDubla & L, tip target)
{
    if(esteLDIVida(L))
    {
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infListaVidaStergere);
        return;
    }
    ///Cautam elementul de eliminat
    nodLDI * current = L.prim;
    punct pivot;
    pivot.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm + L.prim->lungime_elm * latimeElm / 2;
    pivot.y = poz_y;
    punct sageataStanga, sageataDreapta, stergereLegatura;;
    while(current != NULL)
    {

        if(current->info == target)
        {

            sageataStanga.x = pivot.x - latimeElm * current->lungime_elm / 2 - distantaIntreElm;
            sageataStanga.y = pivot.y - inaltimeElm / 2;
            sageataDreapta.x = pivot.x + current->lungime_elm * latimeElm / 2 + distantaIntreElm;
            sageataDreapta.y = pivot.y - inaltimeElm / 2;


             int message_location = 30;
            if(current == L.ultim && current == L.prim)
            {

            }
            else{

                if(current->urm != NULL){
                    outtextxy(WIDTH/2+240,HEIGHT/2.4+message_location, infStergereLegaturaDreapta);
                    message_location+=30;
                    stergereLegatura.x = pivot.x + current->lungime_elm * latimeElm / 2 + distantaIntreElm / 2;
                    stergereLegatura.y = pivot.y;
                    creareX(stergereLegatura, distantaIntreElm / 2, inaltimeElm / 2);
                    while(chrWait != BUTON)
                        chrWait = getch();
                    chrWait = 'a';
                    outtextxy(WIDTH/2+240,HEIGHT/2.4+message_location, infLegareNodUrmDeAnterior);
                    message_location+=30;
                    sageataArc(sageataStanga, sageataDreapta, 20, true, false, 5);
                    while(chrWait != BUTON)
                        chrWait = getch();
                    chrWait = 'a';
                }
                if(current->prec != NULL){

                    stergereLegatura.x = pivot.x - current->lungime_elm * latimeElm / 2 - distantaIntreElm / 2;
                    stergereLegatura.y = pivot.y;
                    creareX(stergereLegatura, distantaIntreElm / 2, inaltimeElm / 2);
                    outtextxy(WIDTH/2+240,HEIGHT/2.4 + message_location, infStergereLegaturaStanga);
                    message_location+=30;
                    while(chrWait != BUTON)
                        chrWait = getch();
                    chrWait = 'a';
                    outtextxy(WIDTH/2+240,HEIGHT/2.4 + message_location,infLegareNodAnteriorDeUrmator);
                    message_location+=30;
                    sageataArc(sageataStanga, sageataDreapta, 20, false, true, 5);
                    while(chrWait != BUTON)
                        chrWait = getch();
                    chrWait = 'a';
                }
            }
            outtextxy(WIDTH/2+240,HEIGHT/2.4 + message_location, infStergereNod);
            creareX(pivot, 3 * current->lungime_elm * latimeElm / 2, inaltimeElm);
            while(chrWait != BUTON)
                chrWait = getch();
            chrWait = 'a';
            eliminareLDI(L, target);
            resetEcran();
            if(L.nrElemente > 0)
                afiseazaLDI(poz_x, poz_y, L, true, true);
            return ;
        }
        if(current->urm != NULL)
            pivot.x += latimeElm * current->lungime_elm / 2 + distantaIntreElm + current->urm->lungime_elm * latimeElm / 2;

        current = current->urm;
    }

    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-eroare: valoare invalida");
    //cout<<"Elementul "<<target <<" Nu a fost gasit in lista\n";
}


void adaugareLaindex(listaDubla & L, tip toAdd, int index)
{

    if(index >= L.nrElemente + 1 || index < 0)
    {
      //  cout<<"Pozitie incorecta. Nu putem insera in lista"<<'\n';
        return;
    }

    if(index == 0)
        adaugaInFata(L, toAdd);
    else
        if(index == L.nrElemente)
            adaugaInSpate(L, toAdd);
    else
    {
        int i = 0;
        nodLDI * current = L.prim, *nodLDINou;
        while(i < index){
            current = current->urm;
            i += 1;
        }
        nodLDINou = new nodLDI ;
        nodLDINou->info = toAdd;
        nodLDINou->urm = current;
        nodLDINou->prec = current->prec;
        current->prec->urm = nodLDINou;
        current->prec = nodLDINou;
        L.nrElemente += 1;
        if(toAdd == 0)
            nodLDINou->lungime_elm = 1;
        else
            nodLDINou->lungime_elm = log10(toAdd) + 1;
    }
}


void AnimatieAdaugareLaindex(int poz_x, int poz_y, listaDubla & L, tip toAdd, int index)
{

    if(index >= L.nrElemente + 1 || index < 0)
    {
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infPozitieIncorectaInserare);
        return;
    }
    resetEcran();
    if(index == 0)
        AnimatieAdaugareLaFata(poz_x, poz_y, L, toAdd);
    else
        if(index == L.nrElemente)
            AnimatieAdaugareLaSpate(poz_x, poz_y, L, toAdd);
    else
    {
        int lungime_elm, i = 0;
        ///Luam pivotul pt inserare
        punct pivot, dupa_index, sageata_stanga, sageata_dreapta;
        pivot.x = poz_x + 4 * latimeElm / 2 + distantaIntreElm + L.prim->lungime_elm * latimeElm / 2;
        pivot.y = poz_y;
        nodLDI * current = L.prim;

        char numtoText[100];
        convertToChar(numtoText, toAdd);

        afiseazaLDIPanaLaIndex(poz_x, poz_y, L, index - 1, true, false);

        while(i < index - 1)
        {
            pivot.x += current->lungime_elm * latimeElm / 2 + distantaIntreElm + current->urm->lungime_elm * latimeElm / 2;
            current = current->urm;
            i++;
        }

        if(toAdd == 0)
            lungime_elm = 1;
        else
            lungime_elm = log10(toAdd) + 1;

        pivot.x += current->lungime_elm * latimeElm / 2 + distantaIntreElm + lungime_elm * latimeElm / 2;

        dupa_index = pivot;
        dupa_index.x += distantaIntreElm + lungime_elm * latimeElm / 2 + current->urm->lungime_elm * latimeElm / 2;

        pivot.y += distantaIntreElm;
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infCreareNod);
        deseneazaInstanta(inaltimeElm, lungime_elm * latimeElm, pivot);
        if(lungime_elm < 2)
            outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
        else
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

        afiseazaLDIDeLanodLDI(current->urm, dupa_index.x, dupa_index.y, true);


        sageata_stanga.x = pivot.x - lungime_elm * latimeElm / 2 - distantaIntreElm;
        sageata_stanga.y = poz_y;
        sageata_dreapta.x = pivot.x + lungime_elm * latimeElm / 2 + distantaIntreElm;
        sageata_dreapta.y = poz_y;


        drawArrow(sageata_stanga, sageata_dreapta, 5);
        drawArrow(sageata_dreapta, sageata_stanga, -5);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        ///stergem legatura
        setcolor(0);
        drawArrow(sageata_stanga, sageata_dreapta, 5);
        drawArrow(sageata_dreapta, sageata_stanga, -5);
        setcolor(15);
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 60, infEliminareLegaturi);
        ///Facem legaturi cu noul element
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 90,infLegareDeNodStang);
        sageata_dreapta.x = pivot.x - lungime_elm * latimeElm / 2;
        sageata_dreapta.y = pivot.y;

        drawArrow(sageata_stanga, sageata_dreapta, 5);
        drawArrow(sageata_dreapta, sageata_stanga, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 120, infLegareDeNodDrept);
        sageata_stanga.x = pivot.x + lungime_elm * latimeElm / 2;
        sageata_stanga.y = pivot.y;
        sageata_dreapta.x = pivot.x + lungime_elm * latimeElm /2 + distantaIntreElm;
        sageata_dreapta.y = poz_y;
        drawArrow(sageata_stanga, sageata_dreapta, 5);
        drawArrow(sageata_dreapta, sageata_stanga, -5);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        while(pivot.y > poz_y)
        {
            resetEcran();
            outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infRepozitionare);
            pivot.y -= 1;
            deseneazaInstanta(inaltimeElm, lungime_elm * latimeElm, pivot);
            if(lungime_elm < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

            sageata_stanga.x = pivot.x - lungime_elm * latimeElm / 2 - distantaIntreElm;
            sageata_stanga.y = poz_y;
            sageata_dreapta.x = pivot.x - lungime_elm * latimeElm / 2;
            sageata_dreapta.y = pivot.y;

            drawArrow(sageata_stanga, sageata_dreapta, 5);
            drawArrow(sageata_dreapta, sageata_stanga, -5);

            sageata_stanga.x = pivot.x + lungime_elm * latimeElm / 2;
            sageata_stanga.y = pivot.y;
            sageata_dreapta.x = pivot.x + lungime_elm * latimeElm / 2 + distantaIntreElm;
            sageata_dreapta.y = poz_y;
            drawArrow(sageata_stanga, sageata_dreapta, 5);
            drawArrow(sageata_dreapta, sageata_stanga, -5);

            afiseazaLDIPanaLaIndex(START_POZ_X, START_POZ_Y, L, index - 1, true, false);
            afiseazaLDIDeLanodLDI(current->urm, dupa_index.x, dupa_index.y, true);


            //usleep(300);
        }


        adaugareLaindex(L, toAdd, index);
    }

    resetEcran();
    afiseazaLDI(poz_x, poz_y, L, true, true);
}

int mouseLDI()
{
    int x,y;
    getmouseclick(WM_LBUTTONDOWN, x, y);
    //cout<<x<<' '<<y<<'\n';
    if(x>=45 && x<=255 && y>=60 && y<=180)///inserare fata
        return 1;
    if(x>=45 && x<=255 && y>=190 && y<=310)///inserare sfarsit
        return 2;
    if(x>=45 && x<=255 && y>=320 && y<=460) ///Inserare index
        return 3;
    if(x>=45 && x<=255 && y>=470 && y<=590) ///Stergere Element
        return 4;
    if(x>=320 && x<=370 && y>=640 && y<=690) ///Incarca lista
        return 5;
    if(x>=320 && x<=370 && y>=580 && y<=630) ///Salveaza
        return 6;
    if(x>=45 && x<=255 && y>=605 && y<=650) ///inapoi
        return 7;
    return -1;
}

bool leftRightLDI(listaDubla l,int &x,int y)     //muta desenul st/dr
{

    if(l.prim!=NULL && kbhit())
    {
        char c=' ';
        c=getch();
        if(c==KEY_RIGHT)
        {
            x+=70;
            resetEcran();
            afiseazaLDI(x, y, l, true, true);
            return 1;

        }else if(c==KEY_LEFT)
        {
            x-=70;
            resetEcran();
            afiseazaLDI(x,y,l, true, true);
            return 1;
        }
    }

    return 0;
}


void saveLDI(listaDubla l)
{
    FILE *fisier;
    fisier=fopen("salvari/saveLDI.bin","wb");
    //cout<<"AICI1";
    nodLDI *p;
    p = l.prim;
    //cout<<"AICI2";
    while(p != NULL)
    {
        fwrite(&p->info,sizeof(int),1,fisier);
        cout<<p->info<<'\n';
        p=p->urm;
    }
    outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infSalvareLista);
    fclose(fisier);
}

void loadLDI(listaDubla &l)     //sa adaug un mod de a selecta fisierul de load
{
    FILE *fisier;
    fisier=fopen("salvari/saveLDI.bin","rb");

    if(!fisier)
    {
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infFisierInexistent);
        return ;
    }

    golesteLDI(l);
    initializeazaLDI(l);
    int aux;
    while(fread(&aux,sizeof(int),1,fisier))
        adaugaInSpate(l, aux);
    outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infListaIncarcata);
    fclose(fisier);
}

int controllerLDI(listaDubla &ldi, int &poz_x, int &poz_y) ///Asteapta pt un click, sau apasarea unei sageti
{
    bool ok = true;
    int n = -1;
    int timeFuture, nowTime;
    while(n == -1){
        nowTime = clock();
        if(leftRightLDI(ldi, poz_x, poz_y)){
            timeFuture = nowTime + 1000;
            ok = false;
        }
        if(nowTime >= timeFuture && !ok){
            readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
            readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
            readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
            ok = true;
        }
        n = mouseLDI();
    }
    return n;
}


void meniuLDI(listaDubla &ldi)
{
    resetEcran();
    readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
    readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
    readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
   int toAdd, index, toRemove, n;
   int poz_x = START_POZ_X, poz_y = START_POZ_Y;
   while(1)
   {

       n = -1;
       while(n == -1){
            n = controllerLDI(ldi, poz_x, poz_y);
       }

       switch(n){
           case 1:
                toAdd = inputForm(160, 120);
                AnimatieAdaugareLaFata(poz_x, poz_y, ldi, toAdd);
                readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 2:
               toAdd = inputForm(160, 243);
               AnimatieAdaugareLaSpate(poz_x, poz_y, ldi, toAdd);
               readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
               readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
               readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 3:

               toAdd = inputForm(160, 360);
               index = inputForm(160, 405);
               afiseazaLDI(poz_x, poz_y, ldi, true, true);
               AnimatieAdaugareLaindex(poz_x, poz_y, ldi, toAdd, index);
               readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
               readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
               readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 4:
               toRemove = inputForm(160, 532);
               eliminareLDIAnimatie(poz_x, poz_y, ldi, toRemove);
               readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
               readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
               readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 5:
                //cout<<"LOAD";
                resetEcran();
                poz_x = START_POZ_X;
                poz_y = START_POZ_Y;
                loadLDI(ldi);

                if(ldi.nrElemente > 0)
                    afiseazaLDI(poz_x, poz_y, ldi, true, true);
                readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
                break;
           case 6:
                //cout<<"SAVE";
                saveLDI(ldi);
                readimagefile("poze_meniuri/MeniuLDI.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
                break;
           case 7:
               return;
           }
   }
}

