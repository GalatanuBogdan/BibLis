#include "Preferences.h"
#include "GlobalFunctions.h"
#include <math.h>
struct nodCoada {
    tip info;
    int lungime_elm = 0;
    nodCoada * urm;
};



struct coada {
    nodCoada* prim;
    nodCoada* ultim;
    int nrElemente;
};

bool esteCoadaVida(coada C)
{
    return C.nrElemente==0;
}

void initializeazaCoada(coada& C)
{
        C.prim=NULL; C.ultim=NULL; C.nrElemente=0;
}

tip peek(coada C)
{
    // ia informatia din primul nod al cozii, fara a-l elimina
    if (!esteCoadaVida(C)) return C.prim->info;
        else
        {
            return -1;
            //cerr<<"Eroare"; return EROARE;
        }
}


tip dequeue(coada &C)
// scoate primul element din coada, din capul cozii
{
    if (!esteCoadaVida(C))
    {
        tip element=peek(C);
        nodCoada* primul;
        primul=C.prim;
        C.prim=C.prim->urm;
        delete primul;
        C.nrElemente--;
        return element;
    }
    else
    {
         //cerr<<"EROARE: coada goala. "; return EROARE;
         return -1;
    }
}

void golesteCoada(coada &C)
{
    while (!esteCoadaVida(C))
        dequeue(C);
}

void enqueue(coada &C, tip element)
{
    // adauga un element la coada, dupa ultimul element (FIFO)
    nodCoada * nod_nou = new nodCoada;

    if(element == 0)
        nod_nou->lungime_elm = 1;
    else
        nod_nou->lungime_elm = log10(element) + 1;

    if (esteCoadaVida(C))
    {
        C.nrElemente = 1;
        C.prim = nod_nou;
        C.prim -> info = element;
        C.prim->urm = NULL;
        C.ultim = C.prim;
    }
    else
    {
        C.nrElemente++;
        nod_nou->info=element;
        nod_nou->urm=NULL;
        C.ultim->urm=nod_nou;
        C.ultim=nod_nou;
    }
}

void afiseazaCoada(int start_poz_x, int start_poz_y, coada c, bool nullSfarsit, bool prim, bool ultim)
{
    resetEcran();
    char numtoText[100];
    punct pivot, startSageata, sfarsitSageata;
    pivot.x = start_poz_x;
    pivot.y = start_poz_y;
    if (c.nrElemente == 1)
    {
        convertToChar(numtoText, c.prim->info);
        if(c.prim->lungime_elm < 2)
            outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
        else
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
        deseneazaInstanta(inaltimeElm, latimeElm * c.prim->lungime_elm, pivot);

        startSageata.x = pivot.x + latimeElm * c.prim->lungime_elm / 2;
        startSageata.y = pivot.y;

        sfarsitSageata.x = pivot.x + latimeElm * c.prim->lungime_elm / 2 + distantaIntreElm;
        sfarsitSageata.y = pivot.y;

        ///Afisam textul Prim si Ultim;
        if(prim)
            outtextxy(pivot.x - c.prim->lungime_elm * latimeElm / 2, pivot.y - 35, infP);
        if(ultim)
            outtextxy(pivot.x + c.prim->lungime_elm * latimeElm / 2, pivot.y - 35, infU);

        pivot.x += latimeElm * c.prim->lungime_elm / 2 + distantaIntreElm + 4 * latimeElm / 2;

        ///desenam Null de la sfarsit
        if(nullSfarsit){
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
            drawArrow(startSageata, sfarsitSageata, 5);
        }
    }
    else
     if(c.nrElemente > 1){
        nodCoada * current = c.prim;
        if(prim && c.nrElemente > 0)
        {
            outtextxy(start_poz_x - c.prim->lungime_elm * latimeElm / 2, pivot.y - 35, infP);
        }
        while(current != NULL)
        {
            deseneazaInstanta(inaltimeElm, latimeElm * current->lungime_elm, pivot);
            convertToChar(numtoText, current->info);
            if(current->lungime_elm < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

            if(current->urm){
                ///legaturi sageti
                startSageata.x = pivot.x + current->lungime_elm * latimeElm / 2;
                startSageata.y = pivot.y;
                sfarsitSageata.x = pivot.x + current->lungime_elm * latimeElm / 2 + distantaIntreElm;
                sfarsitSageata.y = pivot.y;
                drawArrow(startSageata, sfarsitSageata, 5);
                pivot.x += current->lungime_elm * latimeElm / 2 + distantaIntreElm + current->urm->lungime_elm * latimeElm / 2;
            }
            current = current->urm;
        }



        if(ultim && c.nrElemente > 0)
        {
            outtextxy(pivot.x + c.ultim->lungime_elm * latimeElm / 2, pivot.y - 35, infU);
        }


        ///desenam NULL;
        if(nullSfarsit && c.nrElemente > 0)
        {
            startSageata.x = pivot.x + c.ultim->lungime_elm * latimeElm / 2;
            startSageata.y = pivot.y;
            sfarsitSageata.x = pivot.x + c.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm;
            sfarsitSageata.y = pivot.y;

            pivot.x += c.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + 4 * latimeElm / 2;
            deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);

            drawArrow(startSageata, sfarsitSageata, 5);
        }
    }


}

void AnimatieEnqueue(int poz_x, int poz_y, coada &c, tip element)
{
    chrWait = 'a';
    resetEcran();
    punct pivot, startSageata, sfarsitSageata, nullPoz;
    pivot.x = poz_x;
    pivot.y = poz_y;
    char numtoText[100];
    int lungimeElement;

    if(element == 0)
        lungimeElement = 1;
    else
        lungimeElement = log10(element) + 1;

    if (esteCoadaVida(c))
    {
        convertToChar(numtoText, element);
        if(lungimeElement < 2)
            outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
        else
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
        deseneazaInstanta(inaltimeElm, latimeElm * lungimeElement, pivot);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,infCreareNod);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        startSageata.x = pivot.x + latimeElm * lungimeElement / 2;
        startSageata.y = pivot.y;

        sfarsitSageata.x = pivot.x + latimeElm * lungimeElement / 2 + distantaIntreElm;
        sfarsitSageata.y = pivot.y;

        ///Afisam textul Prim si Ultim;
        outtextxy(pivot.x - lungimeElement * latimeElm / 2, pivot.y - 35, infP);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+60,infMarcareAdresaInceput);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        outtextxy(pivot.x + lungimeElement * latimeElm / 2, pivot.y - 35, infU);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+90,    infMarcareAdresaSfarsit);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';

        pivot.x += latimeElm * lungimeElement / 2 + distantaIntreElm + 4 * latimeElm / 2;

        ///desenam Null din dreapta
        deseneazaInstanta(inaltimeElm, latimeElm * 4, pivot);
        outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, infNull);
        drawArrow(startSageata, sfarsitSageata, 5);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+120,infLegareNull);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
    }
    else
    {
        afiseazaCoada(poz_x, poz_y, c, false, true, false);

        ///mutam pivotul in dreapta cozii
        nodCoada * current = c.prim;
        while(current != NULL)
        {
            if(current->urm)
                pivot.x += current->lungime_elm * latimeElm / 2 + distantaIntreElm + current->urm->lungime_elm * latimeElm / 2;
            current = current->urm;
        }


        ///desenam instanta NULL
        nullPoz.x = pivot.x + c.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + latimeElm * lungimeElement + distantaIntreElm + 4 * latimeElm / 2;
        nullPoz.y = pivot.y;
        deseneazaInstanta(inaltimeElm, latimeElm * 4, nullPoz);
        outtextxy(nullPoz.x - latimeElm / 2, nullPoz.y - inaltimeElm / 4, infNull);


        ///Tragem sageata catre NULL
        startSageata.x = pivot.x + c.ultim->lungime_elm * latimeElm / 2 + 1;
        startSageata.y = pivot.y;
        sfarsitSageata.x = pivot.x + c.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + lungimeElement * latimeElm + distantaIntreElm - 1;
        sfarsitSageata.y = pivot.y;
        drawArrow(startSageata, sfarsitSageata, 5);


        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        ///Punem elementul nou
        pivot.x += c.ultim->lungime_elm * latimeElm / 2 + distantaIntreElm + lungimeElement * latimeElm / 2;
        pivot.y += distantaIntreElm;
        convertToChar(numtoText, element);
        if(lungimeElement < 2)
            outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
        else
            outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);
        deseneazaInstanta(inaltimeElm, latimeElm * lungimeElement, pivot);

        outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infCreareNod);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        ///Stergem legatura ultimului element din coada cu null
        setcolor(0);
        drawArrow(startSageata, sfarsitSageata, 5);
        setcolor(15);

        outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infModificareUltimaLegatura);
        ///Facem legaturile cu NULL si cu restul cozii
        startSageata.x = pivot.x - lungimeElement * latimeElm / 2 - distantaIntreElm;
        startSageata.y = pivot.y - distantaIntreElm;

        sfarsitSageata.x = pivot.x - lungimeElement * latimeElm / 2;
        sfarsitSageata.y = pivot.y;

        drawArrow(startSageata, sfarsitSageata, 5);


        outtextxy(WIDTH/2+240,HEIGHT/2.4+90, infLegareElementLaCoada);

        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        startSageata.x = pivot.x + lungimeElement * latimeElm / 2;
        startSageata.y = pivot.y;
        sfarsitSageata.x = pivot.x + lungimeElement * latimeElm / 2 + distantaIntreElm;
        sfarsitSageata.y = pivot.y - distantaIntreElm;
        drawArrow(startSageata, sfarsitSageata, 5);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+120, infLegaturaDreaptaCatreNull);
        while(chrWait != BUTON)
            chrWait = getch();
        chrWait = 'a';
        ///Incepem repozitionarea elementului
        while(pivot.y > poz_y)
        {
            resetEcran();
            pivot.y -= 1;
            afiseazaCoada(poz_x, poz_y, c, false, true, false);

            ///mutam pivotul in dreapta cozii

            ///desenam instanta NULL
            nullPoz.x = pivot.x + latimeElm * lungimeElement / 2 + distantaIntreElm + 4 * latimeElm / 2;
            nullPoz.y = poz_y;
            deseneazaInstanta(inaltimeElm, latimeElm * 4, nullPoz);
            outtextxy(nullPoz.x - latimeElm / 2, nullPoz.y - inaltimeElm / 4, infNull);

            ///Punem elementul nou

            if(lungimeElement < 2)
                outtextxy(pivot.x - latimeElm / 8, pivot.y - inaltimeElm / 4, numtoText);
            else
                outtextxy(pivot.x - latimeElm / 2, pivot.y - inaltimeElm / 4, numtoText);

            deseneazaInstanta(inaltimeElm, latimeElm * lungimeElement, pivot);


            ///Facem legaturile cu coada
            startSageata.x = pivot.x - lungimeElement * latimeElm / 2 - distantaIntreElm;
            startSageata.y = poz_y;

            sfarsitSageata.x = pivot.x - lungimeElement * latimeElm / 2;
            sfarsitSageata.y = pivot.y;

            drawArrow(startSageata, sfarsitSageata, 5);

            startSageata.x = pivot.x + lungimeElement * latimeElm / 2;
            startSageata.y = pivot.y;

            sfarsitSageata.x = pivot.x + lungimeElement * latimeElm / 2 + distantaIntreElm;
            sfarsitSageata.y = START_POZ_Y;
            drawArrow(startSageata, sfarsitSageata, 5);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infRepozitionare);
            //usleep(300);
        }

            outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infCreareNod);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infModificareUltimaLegatura);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+90, infLegareElementLaCoada);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+120, infLegaturaDreaptaCatreNull);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+150, infMarcareAdresaSfarsit);

            outtextxy(pivot.x + lungimeElement * latimeElm / 2, pivot.y - 35, infU);
            while(chrWait != BUTON)
                chrWait = getch();
            chrWait = 'a';

    }
    enqueue(c, element);
    afiseazaCoada(poz_x, poz_y, c, true, true, true);
}

void AnimatieDequeue(int poz_x, int poz_y, coada &C)
// scoate primul element din coada, din capul cozii
{
    chrWait = 'a';
    resetEcran();
    afiseazaCoada(poz_x, poz_y, C, true, true, true);
    if (!esteCoadaVida(C))
    {
        punct pivot, auxiliar;
        pivot.x = poz_x;
        pivot.y = poz_y;
        if(C.nrElemente > 1){
            auxiliar = pivot;

            ///schimbam referinta Prim
            setcolor(0);
            outtextxy(pivot.x - C.prim->lungime_elm * latimeElm / 2, pivot.y - 35, infP);
            setcolor(15);

//            while(chrWait != BUTON)
//            chrWait = getch();
//            chrWait = 'a';
            pivot.x += C.prim->lungime_elm * latimeElm / 2 + distantaIntreElm;
            outtextxy(pivot.x , pivot.y - 35, infP);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infMarcareAdresaInceput);
            while(chrWait != BUTON)
            chrWait = getch();
            chrWait = 'a';
            creareX(auxiliar, latimeElm * C.prim->lungime_elm, inaltimeElm);
            outtextxy(WIDTH/2+240,HEIGHT/2.4+60, infStergereNod);

        }
        else ///coada are un singur element
        {
            outtextxy(WIDTH/2+240,HEIGHT/2.4+30, infStergereNod);
            creareX(pivot, C.prim->lungime_elm * latimeElm, inaltimeElm);
        }
    }
    dequeue(C);
    while(chrWait != BUTON)
        chrWait = getch();
    afiseazaCoada(poz_x, poz_y, C, true, true, true);

}


int mouseCoada()
{
    int x,y;

    getmouseclick(WM_LBUTTONDOWN, x, y);
    if(x>=45 && x<=255 && y>=100 && y<=216)///inserare
        return 1;
    if(x>=45 && x<=255 && y>=260 && y<=310)///eliminare
        return 2;
    if(x>=45 && x<=255 && y>=350 && y<=400) ///inapoi
        return 3;
    if(x>=320 && x<=370 && y>=580 && y<=630) ///Salveaza
        return 4;
    if(x>=320 && x<=370 && y>=640 && y<=690) ///Incarca lista
        return 5;
    return -1;
}

bool leftRightCoada(coada Coada,int &x,int y)     //muta desenul st/dr
{
    if(Coada.nrElemente > 0 && kbhit())
    {
        char c=' ';

        c=getch();
        if(c==KEY_RIGHT)
        {
            x+=70;
            resetEcran();
            afiseazaCoada(x, y, Coada, true, true,true);
            return 1;

        }else if(c==KEY_LEFT)
        {
            x-=70;
            resetEcran();
            afiseazaCoada(x, y, Coada, true, true,true);
            return 1;
        }
    }

    return 0;
}

int controllerCoada(coada &c, int &poz_x, int &poz_y) ///Asteapta pt un click, sau apasarea unei sageti
{
    bool ok = true;
    int n = -1;
    int timeFuture, nowTime;
    while(n == -1){
        nowTime = clock();
        if(leftRightCoada(c, poz_x, poz_y)){
            timeFuture = nowTime + 1000;
            ok = false;
        }
        if(nowTime >= timeFuture && !ok){
            readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
            readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
            readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
            ok = true;
        }
        n = mouseCoada();
    }
    return n;
}

void saveCoada(coada c)
{
    FILE *fisier;
    fisier=fopen("salvari/saveCoada.bin","wb");

    nodCoada *p;
    p = c.prim;
    while(p!=NULL)
    {
        fwrite(&p->info,sizeof(int),1,fisier);
        p=p->urm;
    }
    outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infSalvareCoada);
    fclose(fisier);
}

void loadCoada(coada &c)
{
    FILE *fisier;
    fisier=fopen("salvari/saveCoada.bin","rb");

    if(!fisier)
    {
        outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infFisierInexistent);
        cout<<"Fisier Inexistent\n";
        return ;
    }

    golesteCoada(c);
    initializeazaCoada(c);
    int aux;
    while(fread(&aux,sizeof(int),1,fisier))
        enqueue(c, aux);
    outtextxy(WIDTH/2+240,HEIGHT/2.4 + 30, infCoadaIncarcata);
    fclose(fisier);
}


void meniuCoada(coada &Coada)
{
   resetEcran();
   int toAdd, n;
   readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
   readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
   readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
   initializeazaCoada(Coada);
   int poz_x = START_POZ_X, poz_y = START_POZ_Y;
   while(1)
   {

       n = controllerCoada(Coada, poz_x, poz_y);

       switch(n){
           case 1:
                toAdd = inputForm(160, 160);
                AnimatieEnqueue(poz_x, poz_y, Coada, toAdd);
                readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 2:
                AnimatieDequeue(poz_x, poz_y, Coada);
                readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           case 3:
               return;
           case 4:
                ///save
                saveCoada(Coada);
                readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
                break;
           case 5:
               ///incarca
                resetEcran();
                poz_x = START_POZ_X;
                poz_y = START_POZ_Y;
                loadCoada(Coada);

                if(Coada.nrElemente > 0)
                    afiseazaCoada(poz_x, poz_y, Coada, true, true, true);
                readimagefile("poze_meniuri/MeniuCoada.jpg",0,0,300,720);
                readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
                readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);
               break;
           }
   }
}
