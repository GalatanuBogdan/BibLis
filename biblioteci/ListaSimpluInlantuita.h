#include <iostream>
#include "Preferences.h"
#include "GlobalFunctions.h"
using namespace std;


struct nod
{
    int info;
    nod *succ;
};

struct lista
{
    nod *prim;
    nod *ultim;
};

lista listaVida()
{
    lista L;
    L.prim=NULL;
    L.ultim=NULL;

    return L;
}

void insereaza(lista &L,int k,int e)    //insereaza un element e pe o pozitia k
{
    if(k<0)
    {
        cout<<"eroare \n";
        return;
    }
    nod *q=new nod;
    nod *p;
    q->info=e;
    if(k==0 || L.prim==NULL)
    {
        q->succ=L.prim;
        L.prim=q;

        if(L.ultim==NULL)
            L.ultim=q;

    }else
    {
        p=L.prim;
        int j=0;
        while(j<k-1 && p!=L.ultim)
        {
            p=p->succ;
            j++;
        }
        if(j<k-1)
        {
            cout<<"eroare \n";
            return;
        }
        q->succ=p->succ;
        p->succ=q;
        if(p==L.ultim)
            L.ultim=q;
    }
}

lista elimina(lista L,int k)    //elimina elementul de pe pozitia k
{
    if(k<0 || L.prim==NULL)
    {
        cout<<"eroare \n";
        return L;
    }

    nod *q;
    nod *p;

    q=L.prim;

    if(k==0)
    {
        L.prim=q->succ;
        delete q;
        return L;
    }

    int j=0;
    while(j<k-1 && q!=L.ultim)
    {
        q=q->succ;
        j++;
    }
    if(j<k-1)
    {
        cout<<"eroare \n";
        return L;
    }

    p=q;
    q=q->succ;
    p->succ=q->succ;

    if(p->succ==NULL)
        L.ultim=p;

    delete q;

    return L;
}

int alKlea(lista L, int k)  //returneaza valoarea elementului de pe pozitia k
{
    if(k<0 || L.prim==NULL)
    {
        cout<<"eroare \n";
        return NULL;
    }

    if(k==0)
    {
        return L.prim->info;
    }

    nod *q;

    q=L.prim;
    int j=0;
    while(j<k && q!=L.ultim)
    {
        q=q->succ;
        j++;
    }
    if(j<k)
    {
        cout<<"eroare \n";
        return NULL;
    }

    return q->info;
}


lista parcurge(lista L,void(*f)(int))   //parcurge lista si aplica o functie asupra fiecarui element
{
    nod *p;
    p=L.prim;

    while(p!=NULL)
    {
        f(p->info);
        p=p->succ;
    }

    return L;
}

int poz(lista L,int e)  //returneaza pozitia elementului e
{
    nod *p;
    p=L.prim;
    int k=0;

    while(p!=NULL)
    {
        if(p->info==e)
        {
            return k;
        }

        p=p->succ;
        k++;
    }

    return -1;
}

int lung(lista L)   //returneaza lungimea listei
{
    int n=0;
    nod *p;
    p=L.prim;

    while(p!=NULL)
    {
        p=p->succ;
        n++;
    }

    return n;
}


//#######################################################################################################



void etichetaPrim(float x,float y,int lung,int lat) //scrie "PRIM" deasupra primului nod
{
    float a=lung/2,b=lat/2;

    line(x-3*a/4,y-b,x-3*a/4,y-20);
    line(x-3*a/4,y-20,x-a,y-20);

    outtextxy(x-a-20,y-25,"PRIM");
}

void etichetaUltim(float x,float y,int lung,int lat) //scrie "ULTIM" deasupra ultimului nod
{
    float a=lung/2,b=lat/2;

    line(x+a/4,y-b,x+a/4,y-20);
    line(x+a/4,y-20,x+a/2,y-20);

    outtextxy(x+a/2+30,y-25,"ULTIM");
}

void drawRect(float x,float y,int lung,int lat)     //deseneaza un dreptunghi   pt lista simplu inlantuita
{
    float a=lung/2,b=lat/2;

    line(x-a,y-b,x+a,y-b);
    line(x-a,y+b,x+a,y+b);
    line(x-a,y-b,x-a,y+b);
    line(x+a,y-b,x+a,y+b);

    line(x+a/2,y-b,x+a/2,y+b);  //linie pt caseta pointerului

    line(x+3*a/4,y,x+2*a+45,y);   //linie care uneste casetele

}

void drawLista(lista l,float x,float y)        //deseneaza nr, apoi un dreptunghi in jurul lui
{
    nod *p=l.prim;
    char c[MAX];
    int lung,lat;

    while(p!=NULL)
    {
        sprintf(c,"%d",p->info);
        outtextxy(x-10,y+5,c);

        lung=lung_lsi;
        lat=lat_stiva/2;

        drawRect(x,y,lung,lat);

        if(p==l.prim)
            etichetaPrim(x,y,lung,lat);

        if(p==l.ultim)
            etichetaUltim(x,y,lung,lat),outtextxy(x+2*lung/2+80,y+5,"NULL");

        x+=lung+lung/2+45;
        p=p->succ;
    }

}


void drawPrimUlt(float x,float y,int lung,int lat)     //deseneaza nodurile prim/ultim legate la null
{
    etichetaPrim(x,y,lung,lat);
    etichetaUltim(x,y,lung,lat);

    outtextxy(x-10,y+10,"NULL");
}

void drawNodGol(float x,float y,int lung,int lat)     //deseneaza un nod nou
{
    float a=lung/2,b=lat/2;

    y+=50;

    line(x-a,y-b,x+a,y-b);
    line(x-a,y+b,x+a,y+b);
    line(x-a,y-b,x-a,y+b);
    line(x+a,y-b,x+a,y+b);

    line(x+a/2,y-b,x+a/2,y+b);
}

void drawNodInfo(float x,float y,int lung,int lat,int n)   //pune in nodul nou informatia si il leaga la null
{
    char c[MAX];
    float a=lung/2;
    y+=50;

    sprintf(c,"%d",n);
    outtextxy(x-10,y+5,c);

    line(x+3*a/4,y,x+2*a+30,y);
    outtextxy(x+2*a+80,y+5,"NULL");
}

void legNod(float x,float y,int lung,int lat,int n)   //leaga prim/ultim la nod
{
    cleardevice();
    resetEcran();

    etichetaPrim(x,y,lung,lat);
    etichetaUltim(x,y,lung,lat);

    y-=50;
    drawNodGol(x,y,lung,lat);
    drawNodInfo(x,y,lung,lat,n);

}

void drawListaVida(float x,float y,int n)   //trateaza cazul pt inserarea unui element intr-o lista vida
{
    char c='a';
    int lung,lat;

    lung=lung_lsi;
    lat=lat_stiva/2;

    drawPrimUlt(x,y,lung,lat);

    while(c!=BUTON)    c=getch();
    drawNodGol(x,y,lung,lat);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se creeaza un nod gol");

    c='a';

    while(c!=BUTON)    c=getch();
    drawNodInfo(x,y,lung,lat,n);
    outtextxy(WIDTH/2+357,HEIGHT/2.4+60,"-se introduce in nod valoarea selectata si se leaga la NULL");

    c='a';

    while(c!=BUTON)    c=getch();
    legNod(x,y,lung,lat,n);
    outtextxy(WIDTH/2+290,HEIGHT/2.4+30,"-pointerii PRIM si ULTIM se leaga la nod");

    c='a';
}

void legUrm(float x,float y,int lung,int lat,int n) //traseaza linie de la noul nod la urm
{
    char c[MAX];
    float a=lung/2,b=lat/2;
    y+=50;

    sprintf(c,"%d",n);
    outtextxy(x+(3*a+45)/2,y+5,c);

    line(x+(9*a+90)/4,y,x+3*a+45,y-50+b);
}

void legPred(float x,float y,int lung,int lat)   //traseaza linie de la noul nod la predecesor si taie legatura veche
{
    float a=lung/2,b=lat/2;
    y+=50;

    line(x+(a+45)/2,y,x+3*a/4,y-50);

    line(x+5*a/4+30,y-65,x+5*a/4+60,y-35);  //deseneaza un X peste
    line(x+5*a/4+30,y-35,x+5*a/4+60,y-65);  //legatura veche
}

void reDraw(float x,float y,lista &l,int n,int poz) //deseneaza lista cu nodul nou adaugat
{
    resetEcran();
    insereaza(l,poz,n);
    drawLista(l,x,y);
}

void drawCazGeneral(float x,float y,lista &l,int n,int poz)  //trateaza cazul pt inserarea unui element pe o poz!=0 intr-o lista nevida
{
    char c='a';
    int lung,lat,aux=x;

    lung=lung_lsi;
    lat=lat_stiva/2;

    int a=lung/2;

    x+=(poz-1)*(3*a+45);

    float mijloc=x+(3*a+45)/2;

    while(c!=BUTON)    c=getch();
    drawNodGol(mijloc,y,lung,lat);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se creeaza un nod gol");

    c='a';
    while(c!=BUTON)    c=getch();
    legUrm(x,y,lung,lat,n);
    outtextxy(WIDTH/2+295,HEIGHT/2.4+60,"-se introduce valoarea selectata in nod");
    outtextxy(WIDTH/2+350,HEIGHT/2.4+90,"-se leaga de nodul de pe pozitia urmatoare ori de NULL");
    outtextxy(WIDTH/2+240,HEIGHT/2.4+110,"daca e inserat la final");

    c='a';
    while(c!=BUTON)    c=getch();
    legPred(x,y,lung,lat);
    outtextxy(WIDTH/2+398,HEIGHT/2.4+130,"-nodul predecesor se leaga de nodul nou si se elimina vechea legatura");

    c='a';
    while(c!=BUTON)    c=getch();
    reDraw(aux,y,l,n,poz);
    outtextxy(WIDTH/2+360,HEIGHT/2.4+30,"-se muta pointerul ULTIM daca nodul a fost inserat la final");

    c='a';
}

void drawInceput(float &x,float y,lista l,int n) //insereaza nod la inceputul listei
{
    int lung,lat;
    char v[MAX],c='a';

    lung=lung_lsi;
    lat=lat_stiva/2;

    int a=lung/2;

    x=x-3*a-45;

    while(c!=BUTON)    c=getch();
    drawNodGol(x,y-50,lung,lat);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se creeaza un nod gol");

    c='a';

    while(c!=BUTON)    c=getch();
    sprintf(v,"%d",n);
    outtextxy(x,y+5,v);
    line(x+3*a/4,y,x+2*a+45,y);
    outtextxy(WIDTH/2+385,HEIGHT/2.4+60,"-se introduce in nod valoarea selectata si se leaga la nodul urmator");

    c='a';

    while(c!=BUTON)    c=getch();
    c='a';
}

void adaugareLis(float x,float y,lista &l,int n,int poz)     //afiseaza modificarile efectuate asupra unei liste la inserare
{
    if(poz>=0 && poz<=lung(l))
    {
        if(l.prim==NULL)
        {
            insereaza(l,0,n);
            drawListaVida(x,y,n);
        }else
        {
            drawLista(l,x,y);

            if(poz!=0 && poz<=lung(l))
                drawCazGeneral(x,y,l,n,poz);
            else if(poz==0)
            {
                drawInceput(x,y,l,n);
                reDraw(x,y,l,n,poz);
                outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se muta pointerul PRIM");
            }
        }
    }else
    {
        //cout<<"\neroare: pozitie incorecta...\n";
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-eroare: pozitie incorecta");
        drawLista(l,x,y);
    }

}

void eliminareLisZero(float x,float y,lista &l)     //elimina nodul de pe poz 0
{
    int lung,lat;
    char c='a';

    lung=lung_lsi;
    lat=lat_stiva/2;

    resetEcran();   drawLista(l,x,y);
    int a=lung/2,b=lat/2;


    while(c!=BUTON)    c=getch();
    line(x+5*a/4+30,y-15,x+5*a/4+60,y+15);  //deseneaza un X peste
    line(x+5*a/4+30,y+15,x+5*a/4+60,y-15);  //legatura veche

    line(x-a-15,y-b-15,x+a+15,y+b+15);  //deseneaza X
    line(x-a-15,y+b+15,x+a+15,y-b-15);  //peste nod
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se elimina nodul si legatura");

    c='a';

    while(c!=BUTON)    c=getch();
    l=elimina(l,0);     resetEcran();    drawLista(l,x,y);
    outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se muta pointerul PRIM");

    c='a';
}

void eliminareLis(float x,float y,lista &l,int poz)  //sterge grafic un nod din lista
{
    if(poz==0 && poz<lung(l))
    {
        eliminareLisZero(x,y,l);

    }else if(poz>0 && poz<lung(l))
    {
        float aux=x;
        int lung,lat;
        char c='a';

        lung=lung_lsi;
        lat=lat_stiva/2;

        resetEcran();   drawLista(l,x,y);
        int a=lung/2,b=lat/2;

        x=x+(3*a+45)*(poz);

        while(c!=BUTON)    c=getch();

        line(aux+(3*a+45)*(poz-1)+3*a/4,y+5,aux+(3*a+45)*(poz-1)+3*a/4,y+30);       //deseneaza o noua legatura peste nodul sters
        line(aux+(3*a+45)*(poz-1)+3*a/4,y+30,aux+(3*a+45)*(poz+1),y+30);
        line(aux+(3*a+45)*(poz+1),y+30,aux+(3*a+45)*(poz+1),y+b);
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-se elimina legatura veche");


        line(aux+(3*a+45)*(poz-1)+5*a/4+30,y-15,aux+(3*a+45)*(poz-1)+5*a/4+60,y+15);  //deseneaza un X peste
        line(aux+(3*a+45)*(poz-1)+5*a/4+30,y+15,aux+(3*a+45)*(poz-1)+5*a/4+60,y-15);  //legatura veche
        outtextxy(WIDTH/2+240,HEIGHT/2.4+60,"-se creaza o legatura noua");

        c='a';


        while(c!=BUTON)    c=getch();
        line(x-a-15,y-b-15,x+a+15,y+b+15);  //deseneaza X
        line(x-a-15,y+b+15,x+a+15,y-b-15);  //peste nod
        outtextxy(WIDTH/2+240,HEIGHT/2.4+90,"-se elimina nodul selectat");

        c='a';
        while(c!=BUTON)    c=getch();
        l=elimina(l,poz);     resetEcran();    drawLista(l,aux,y);
        outtextxy(WIDTH/2+340,HEIGHT/2.4+30,"-se muta pointerul ULTIM daca s-a eliminat ultimul nod");

        c='a';
    }else if(poz>=lung(l))
        outtextxy(WIDTH/2+240,HEIGHT/2.4+30,"-eroare: pozitie invalida");
}

bool leftRight(lista l,float &x,float y)     //muta desenul st/dr
{
    if(l.prim!=NULL)
    {
        char c=' ';

        c=getch();

        if(c==KEY_RIGHT)
        {
            x+=70;
            resetEcran();
            drawLista(l,x,y);
        }else if(c==KEY_LEFT)
        {
            x-=70;
            resetEcran();
            drawLista(l,x,y);
        }else if(c==27)     //caracterul ESC
            return 0;
        else
            if(c == ' ')
                return 0;

        return 1;
    }
    return 0;
}

void saveLista(lista l)
{
    FILE *fisier;
    fisier=fopen("salvari/saveLista.bin","wb");

    nod *p;
    p=l.prim;

    while(p!=NULL)
    {
        fwrite(&p->info,sizeof(int),1,fisier);
        p=p->succ;
    }

    fclose(fisier);
}

void loadLista(lista &l)
{
    FILE *fisier;
    fisier=fopen("salvari/saveLista.bin","rb");

    while(l.prim!=NULL)
        l=elimina(l,0);

    int aux;

    while(fread(&aux,sizeof(int),1,fisier)!=NULL)
    {
        nod *p=new nod;
        p->info=aux;
        p->succ=NULL;
        if(l.prim==NULL)
        {
            l.prim=p;

            if(l.ultim==NULL)
                l.ultim=p;
        }else
        {
            l.ultim->succ=p;
            l.ultim=p;
        }
    }

    fclose(fisier);
}


int mouseListaSimpla()
{
    int x,y;

    while(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);

        if(x>=45 && x<=255 && y>=90 && y<=230)    return 1;
        else if(x>=45 && x<=255 && y>=275 && y<=395)    return 2;
        else if(x>=45 && x<=255 && y>=435 && y<=485)    return 0;
        else if(x>=320 && x<=370 && y>=580 && y<=625)    return 3;
        else if(x>=320 && x<=370 && y>=640 && y<=685)    return 4;
    }

    return -1;
}


void meniuLista(lista &l,float x,float y)
{
    int n=-1;
    int poz,value;
    float aux;    //fara aux, x nu se mai reseteaza dupa mutari
    while(1)
    {
        aux=x;

        while(1)
        {
            if(!leftRight(l,aux,y))
                break;
        }

        readimagefile("poze_meniuri/MeniuLSI.jpg",0,0,300,720);
        readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
        readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);

        semn:
        while(n == -1)
            n = mouseListaSimpla();

        switch(n)
        {
            case 0:return;
            case 1:value=inputForm(180,145);  poz=inputForm(180,190);  resetEcran();  adaugareLis(x,y,l,value,poz);  n=-1;   break;
            case 2:poz=inputForm(180,350);  eliminareLis(x,y,l,poz);   n=-1;   break;
            case 3:saveLista(l);    n=-1;     goto semn;
            case 4:loadLista(l); resetEcran();   drawLista(l,x,y);  n=-1;  break;
            /*default:cout<<"\nalegeti alta optiune...\n";    break;*/
        }
    }
}

