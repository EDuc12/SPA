#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
}Vrh;

typedef struct {
    float n;
    unsigned short color;
}Triangle;

typedef struct {
    Vrh** V;
    Triangle** T;
    unsigned int num;
}Object_3D;

Object_3D read_binary(char* Header)
{
    FILE* fp = fopen("primjerbin.stl", "rb");
    Object_3D O;
    fread(Header, 80, 1, fp);
    fread(&O.num, 4, 1, fp);
    O.T = (Triangle**)malloc(sizeof(Triangle) * O.num);
    O.V = (Vrh**)malloc(sizeof(Vrh) * O.num);
    for (int i = 0; i < O.num; i++)
    {
        O.T[i] = (Triangle*)malloc(sizeof(float) * 3 + 2);
        O.V[i] = (Vrh*)malloc(sizeof(Vrh) * 9);
        for (int j = 0; j < 3; j++)
            fread(&O.T[i][j].n, 4, 1, fp);
        for (int j = 0; j < 9; j++)
            fread(&O.V[i][j].x, 4, 1, fp);
        fread(&O.T[i]->color, 2, 1, fp);
    }
    fclose(fp);
    return O;
}

void write_binary(char* Header, Object_3D O)
{
    FILE* fp = fopen("bin.stl", "wb");
    fwrite(Header, 80, 1, fp);
    fwrite(&O.num, 4, 1, fp);
    for (int i = 0; i < O.num; i++)
    {
        for (int j = 0; j < 3; j++)
            fwrite(&O.T[i][j].n, 4, 1, fp);
        for (int j = 0; j < 9; j++)
            fwrite(&O.V[i][j].x, 4, 1, fp);
        fwrite(&O.T[i]->color, 2, 1, fp);
    }
    fclose(fp);
}
void write_txt(Object_3D O)
{
    FILE* fp = fopen("txt.stl", "w");
    fprintf(fp, "solid %s\n", "Naslov Trokut");
    for (int i = 0; i < O.num; i++)
    {
        fprintf(fp, "  facet normal %.1f %.1f %.1f\n", O.T[i][0].n, O.T[i][1].n, O.T[i][2].n);
        fprintf(fp, "    outer loop\n");
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.V[i][0].x, O.V[i][1].x, O.V[i][2].x);
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.V[i][3].x, O.V[i][4].x, O.V[i][5].x);
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.V[i][6].x, O.V[i][7].x, O.V[i][8].x);
        fprintf(fp, "    endloop\n");
        fprintf(fp, "  endfacet\n");
    }
    fprintf(fp, "endsolid %s", "Naslov Trokut");
    fclose(fp);
}
void delete_3D(Object_3D O)
{
    free(O.T);
    free(O.V);
}
void main()
{
    char* Header = (char*)malloc(sizeof(char) * 80);
    Object_3D O = read_binary(Header);
    write_binary(Header, O);
    write_txt(O);
    delete_3D(O);
   
}