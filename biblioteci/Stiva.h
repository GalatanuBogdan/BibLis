#include "Preferences.h"
#include "GlobalFunctions.h"

struct nodS
{
    int info;
    nodS *succ;
};

struct stiva
{
    nodS *prim;
};

stiva stivaVida()
{
    stiva s;
    s.prim=NULL;

    return s;
}

bool esteVida(stiva s)  //verifica daca stiva e vida
{
    if(s.prim==NULL)
        return true;
    else
        return false;
}

void push(stiva &st,int elem)   //insereaza un element in varful listei
{
    nodS *p=new nodS;
    p->info=elem;
    p->succ=st.prim;
    st.prim=p;
}

void pop(stiva &st)     //sterge elementul din varful listei
{
    if(st.prim==NULL)
        return;

    nodS *p=st.prim;
    st.prim=st.prim->succ;
    delete p;
}

int top(stiva st)       //returneaza elementul din varful listei
{
    if(st.prim!=NULL)
        return st.prim->info;
    else
        return NULL;
}
//############################################################################################################



void drawStack(float x,float y,int lung,int lat)    //deseneaza casetele pt stiva
{
    float a=lung/2,b=lat/2;

    line(x-a,y+b,x+a,y+b);
    line(x-a,y-b,x-a,y+b);
    line(x+a,y-b,x+a,y+b);
}

void drawStiva(stiva s,float x,float y)     //deseneaza stiva
{
    nodS *p=s.prim;
    char c[MAX];

    drawStack(x,y,lung_stiva,lat_stiva);

    outtextxy(WIDTH/2+340,HEIGHT/2.4+30,"-stiva este un caz particular de lista simplu inlantuita in care");
    outtextxy(WIDTH/2+340,HEIGHT/2.4+50,"inserarea si eliminarea se fac doar pe pozitia 0 (varful stivei)");

    line(x+lung_stiva/2+30,y-lat_stiva/2-20,x+lung_stiva/2+30,y+lat_stiva/2+20);    //traseaza o sageata in sus si scrie eticheta OUT
    line(x+lung_stiva/2+30,y-lat_stiva/2-20,x+lung_stiva/2+20,y-lat_stiva/2-10);
    line(x+lung_stiva/2+30,y-lat_stiva/2-20,x+lung_stiva/2+40,y-lat_stiva/2-10);
    outtextxy(x+lung_stiva/2+60,y,"OUT");


    line(x-lung_stiva/2-30,y-lat_stiva/2-20,x-lung_stiva/2-30,y+lat_stiva/2+20);    //traseaza o sageata in jos si scrie eticheta IN
    line(x-lung_stiva/2-30,y+lat_stiva/2+20,x-lung_stiva/2-40,y+lat_stiva/2+10);
    line(x-lung_stiva/2-30,y+lat_stiva/2+20,x-lung_stiva/2-20,y+lat_stiva/2+10);
    outtextxy(x-lung_stiva/2-60,y,"IN");

    y+=lat_stiva;

    while(p!=NULL)
    {
        sprintf(c,"%d",p->info);
        outtextxy(x,y,c);

        drawStack(x,y,lung_stiva,lat_stiva);

        y+=lat_stiva;
        p=p->succ;
    }
}

bool upDown(stiva s,float x,float &y)     //muta desenul st/dr
{
    if(s.prim!=NULL)
    {
        char c=' ';

        c=getch();

        if(c==KEY_DOWN)
        {
            y+=70;
            resetEcran();
            drawStiva(s,x,y);
        }else if(c==KEY_UP)
        {
            y-=70;
            resetEcran();
            drawStiva(s,x,y);
        }else if(c==27)     //caracterul ESC
            return 0;
        else
            if(c == ' ')
                return 0;
        return 1;
    }
    return 0;
}

void saveStiva(stiva s)
{
    FILE *fisier;
    fisier=fopen("salvari/saveStiva.bin","wb");

    nodS *p;
    p=s.prim;

    while(p!=NULL)
    {
        fwrite(&p->info,sizeof(int),1,fisier);
        p=p->succ;
    }

    fclose(fisier);
}

void loadStiva(stiva &s)
{
    FILE *fisier;
    fisier=fopen("salvari/saveStiva.bin","rb");

    while(s.prim!=NULL)
        pop(s);

    int aux;

    while(fread(&aux,sizeof(int),1,fisier)!=NULL)
    {
        nodS *p=new nodS;
        p->info=aux;
        p->succ=NULL;
        if(s.prim==NULL)
        {
            s.prim=p;

        }else
        {
            p->succ=s.prim;
            s.prim=p;
        }
    }

    fclose(fisier);
}


int mouseStiva()
{
    int x,y;

    while(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN,x,y);

        if(x>=45 && x<=255 && y>=95 && y<=215)    return 1;
        else if(x>=45 && x<=255 && y>=260 && y<=310)    return 2;
        else if(x>=45 && x<=255 && y>=355 && y<=400)    return 0;
        else if(x>=320 && x<=370 && y>=580 && y<=625)    return 3;
        else if(x>=320 && x<=370 && y>=640 && y<=685)    return 4;
    }

    return -1;
}


void meniuStiva(stiva &s,float x,float y)
{
    int n=-1;
    int value;
    float aux;
    while(1)
    {

        aux=y;
        while(1)
        {
            if(!upDown(s,x,aux))
                break;
        }

        readimagefile("poze_meniuri/MeniuStiva.jpg",0,0,300,720);
        readimagefile("poze_meniuri/Load.jpg",320,640,370, 690);
        readimagefile("poze_meniuri/Save.jpg",320,580,370, 630);

        semn:
        while(n==-1)
            n=mouseStiva();

        switch(n)
        {
            case 0:return;
            case 1:value=inputForm(180,173);  push(s,value);    resetEcran();    drawStiva(s,x,y);  n=-1;   break;
            case 2:pop(s);  resetEcran();  drawStiva(s,x,y);    n=-1;   break;
            case 3:saveStiva(s); n = -1; goto semn;
            case 4:loadStiva(s); resetEcran();   drawStiva(s,x,y); n = -1; break;
            //default:cout<<"\nalegeti alta optiune...\n";    break;
        }
    }
}

