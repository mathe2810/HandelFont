#include <stdio.h>
#include "allegro.h"
#include "string.h"

///site to convert ttf to fnt and bmp: https://ttf2fnt.com/

typedef struct
{
    BITMAP *charbmp;
    int xOffset,yOffset;
    int xAdvance;
}t_font;


BITMAP * importeImage(char *nomDeFichier)
{
    BITMAP *imageARendre= load_bitmap(nomDeFichier,NULL);
    if(!imageARendre)
    {
        allegro_message("ne peut pas ouvrir %s",nomDeFichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return imageARendre;
}

t_font * createFont(const char * filenameFNT,char * filenameBMP, int* tailleChar) {
    BITMAP *bitmapAllImages= importeImage(filenameBMP);
    FILE *pfFont= fopen(filenameFNT,"r");
    char *tmp= malloc(sizeof (char)*CHAR_MAX);
    fscanf(pfFont,"%s",tmp);
    fscanf(pfFont,"%s",tmp);
    char name[100];
    fscanf(pfFont,"%s",name);
    printf("name : %s\n",name);
    while(strcmp(tmp,"count")!=0){
        fscanf(pfFont,"%s",tmp);
    }
    int nbrChar;
    int charid=0;
    fscanf(pfFont,"%d",&nbrChar);
    printf("taille : %d\n",nbrChar);
    t_font *fontToReturn= malloc(sizeof (t_font)*nbrChar);
    for(int i=0;i<nbrChar;i++)
    {
        int id;
        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&id);
        printf("id :%d ",id);
        int x;
        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&x);
        printf("x : %d ",x);
        int y;
        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&y);
        printf("y : %d ",y);
        int width;
        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&width);
        printf("width : %d ",width);
        int height;
        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&height);
        printf("height : %d ",height);

        ///to save:

        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&fontToReturn[charid].xOffset);
        printf("xOffset : %d ",fontToReturn[charid].xOffset);

        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&fontToReturn[charid].yOffset);
        printf("yOffset : %d ",fontToReturn[charid].yOffset);

        fscanf(pfFont,"%s",tmp);
        fscanf(pfFont,"%d",&fontToReturn[charid].xAdvance);
        printf("xAdvance : %d ",fontToReturn[charid].xAdvance);

        while(strcmp(tmp,"15")!=0){
            fscanf(pfFont,"%s",tmp);
        }
        printf("\n");
        if(height==0||width==0)
        {

        }
        else{
            fontToReturn[charid].charbmp= create_sub_bitmap(bitmapAllImages, x, y, width, height);
            charid++;
        }
        *tailleChar=charid-1;

    }
    return fontToReturn;
}
void init()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,800,0,0)!=0)
    {
        allegro_message("prblm gfx");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
}


int main() {
    init();
    int tailletab;
    t_font *fontCustom=createFont("../OldLondon.fnt","../OldLondon.bmp",&tailletab);
    int charwanted=0;
    BITMAP *buffer= create_bitmap(SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC])
    {
        clear_bitmap(buffer);
        if(key[KEY_LEFT]&&charwanted!=0){charwanted--;}
        if(key[KEY_RIGHT]&&charwanted!=tailletab){charwanted++;}
        rectfill(buffer,0,0,SCREEN_W,SCREEN_H, makecol(255,255,255));
        draw_sprite(buffer,fontCustom[charwanted].charbmp,SCREEN_W/2+fontCustom[charwanted].xOffset,SCREEN_H/2+fontCustom[charwanted].yOffset);
        draw_sprite(buffer,fontCustom[charwanted+1].charbmp,fontCustom[charwanted].xAdvance+SCREEN_W/2+fontCustom[charwanted+1].xOffset,SCREEN_H/2+fontCustom[charwanted+1].yOffset);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(60);
    }
    allegro_exit();

    return 0;
}
END_OF_MAIN()
