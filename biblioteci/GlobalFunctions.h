#pragma once

struct punct {
    int x;
    int y;
};

void creareX(punct centru, int marimeX, int inaltimeY)
{
    line(centru.x - marimeX / 2, centru.y + inaltimeY / 2, centru.x + marimeX / 2, centru.y - inaltimeY / 2);
    line(centru.x - marimeX / 2, centru.y - inaltimeY / 2, centru.x + marimeX / 2, centru.y + inaltimeY / 2);
}

void sageataArc(punct start, punct sfarsit, int inaltime, bool varfStanga, bool varfDreapta, int marimeVarf)
{
    arc(start.x + inaltime, start.y,90, 180, inaltime);
    line(start.x + inaltime, start.y - inaltime, sfarsit.x - inaltime, sfarsit.y - inaltime);
    arc(sfarsit.x - inaltime, sfarsit.y, 0, 90, inaltime);

    if(varfDreapta)
    {
        line(sfarsit.x - marimeVarf , sfarsit.y - marimeVarf, sfarsit.x, sfarsit.y);
        line(sfarsit.x + marimeVarf, sfarsit.y - marimeVarf, sfarsit.x, sfarsit.y);
    }
    if(varfStanga){
        line(start.x - marimeVarf, start.y - marimeVarf, start.x, start.y);
        line(start.x + marimeVarf, start.y - marimeVarf, start.x, start.y);
    }
}


void deseneazaInstanta(int inaltime, int latime, punct centru) {
    int left = centru.x - latime / 2;
    int top = centru.y - inaltime / 2;
    int right = centru.x + latime / 2;
    int bottom = centru.y + inaltime / 2;
    rectangle(left, top, right, bottom);
}

void drawArrow(punct startPos, punct endPos, int marimeVarf)
{
    line(startPos.x, startPos.y, endPos.x, endPos.y);
    line(endPos.x - marimeVarf, endPos.y - marimeVarf, endPos.x, endPos.y);
    line(endPos.x - marimeVarf, endPos.y + marimeVarf, endPos.x, endPos.y);
}

void convertToChar(char * p, int info) {
    int i = 0, left, right;
    if (info == 0) {
        p[0] = '0';
        p[1] = '\0';
        return;
    }

    while (info) {
        p[i++] = (info % 10) + '0';
        info /= 10;
    }
    p[i] = '\0';
    left = 0;
    right = i - 1;
    while (left < right)
        std::swap(p[left++], p[right--]);

}


void resetEcran()   //sterge ecranul si deseneaza caseta pt text
{
    cleardevice();
    line(WIDTH/2+110,HEIGHT/2.4,WIDTH-1,HEIGHT/2.4);
    line(WIDTH/2+110,HEIGHT/2.4,WIDTH/2+110,HEIGHT-1);
}

void resetEcranLista()
{
    resetEcran();
    readimagefile("MeniuLSI.jpg",0,0,300,720);
}

void resetEcranStiva()
{
    resetEcran();
    readimagefile("MeniuStiva.jpg",0,0,300,720);
}


int charToInt(char c[])
{
    int n=strlen(c);
    int rez=0,i=0;
    bool negativ=0;

    if(c[0]=='-')
        i++,negativ=1;

    for(;i<n;i++)
        rez=rez*10+c[i]-48;

    if(negativ)
        return -rez;
    return rez;
}

int inputForm(int x,int y)
{
    //std::cout<<"A INTRAT";
    char inputbuf[MAX_INPUT_LEN] = "_\0";
    int input_pos = 0;
    char c;
    int the_end = 0;
    int rez = 0;
    do
    {

       inputbuf[input_pos] = '_';
       outtextxy (x,y, inputbuf);
       inputbuf[input_pos] = '\0';
       c = getch();
       switch (c)
       {
            case 8: // backspace
              if (input_pos)
              {
                    setcolor(0);
                    inputbuf[input_pos] = '_';
                    outtextxy (x,y, inputbuf);
                    inputbuf[input_pos] = '\0';
                    setcolor(15);
                    input_pos--;
                    inputbuf[input_pos] = '\0';
              }
              break;
            case 13: // return

                setcolor(0);
                inputbuf[input_pos] = '_';
                outtextxy (x,y, inputbuf);
                inputbuf[input_pos] = '\0';
                setcolor(15);
                outtextxy(x,y, inputbuf);
                rez = charToInt(inputbuf);
                if(strlen(inputbuf)){
                    return rez;
                }
            default:
              if (input_pos < MAX_INPUT_LEN - 2 && ((c >= '0' && c <= '9') || (c=='-' && input_pos==0)))
              {
                 inputbuf[input_pos] = c;
                 input_pos++;
                 inputbuf[input_pos] = 0;
              }
       }

    } while (!the_end);
    return 0;
}

char infNull[]="null";
char infP[] = "P";
char infU[] = "U";
char infNullStanga[] ="-reprezentam nodul null stanga";
char infNullDreapta[] = "-reprezentam nodul null dreapta";
char infCreareNod[] = "-se creaza nodul nou";
char infLegaturaStangaCatreNull [] = "-legam la stanga null in noul nod";
char infLegaturaDreaptaCatreNull[] = "-legam la dreapta null in noul nod";
char infMarcareAdresaInceput[] ="-marcam adresa de inceput";
char infMarcareAdresaSfarsit[] ="-marcam adresa de sfarsit";
char infStergereLegaturaNull[] = "-stergem legatura dintre primul element si null";
char infSchimbareAdresaDreapta[] = "-marcam adresa din dreapta ca fiind primul element";
char infRepozitionare[] = "-repozitionare";
char infLegareDeUltimulElement[] = "-se leaga ultimul nod de noul nod";
char infLegareNodDeUltimulElement[] = "-se leaga noul nod de ultimul element";
char infListaVidaStergere[] = "-lista este vida. Nu avem ce sterge";
char infStergereLegaturaDreapta[] = "-stergem legatura din dreapta";
char infStergereLegaturaStanga[] = "-stergem legatura din stanga";
char infLegareNodUrmDeAnterior[] = "-legam nodul urmator de cel anterior";
char infLegareNodAnteriorDeUrmator[] = "-legam nodul anterior de cel urmator";
char infStergereNod[] ="-stergem nodul";
char infPozitieIncorectaInserare[] = "-pozitie incorecta. Nu putem insera";
char infEliminareLegaturi[] = "-se elimina legaturile";
char infLegareDeNodStang[] = "-se leaga noul element de nodul stang";
char infLegareDeNodDrept[] = "-se leaga noul element de nodul drept";
char infSalvareLista[] = "-lista s-a salvat";
char infSalvareCoada[] = "-coada s-a salvat";
char infFisierInexistent[] = "-fisier Inexistent. Intai Salvati";
char infListaIncarcata[] = "-lista s-a incarcat";
char infCoadaIncarcata[] = "-coada s-a incarcat";
char infLegareNull[] = "-il legam la null";
char infModificareUltimaLegatura[] = "-se modifica legatura ultimului nod";
char infLegareElementLaCoada[] = "-legam elementul la sfarsitul cozii";




