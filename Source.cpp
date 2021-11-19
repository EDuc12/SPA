#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	float n1, n2, n3;
	float x, y, z;
    unsigned short color;
}Triangle;

typedef struct {
    
    Triangle* T;
    unsigned int num;
}Object_3D;

Object_3D read_binary(char* Header)
{
    FILE* fp = fopen("primjerbin.stl", "rb");
    Object_3D O;
    fread(Header, 80, 1, fp);
    fread(&O.num, 4, 1, fp);
    O.T = (Triangle*)malloc(sizeof(Triangle) * O.num);
	
    for (int i = 0; i < O.num; i++)
    {
		fread(&(O.T[i]), 50, 1, fp);
		/*
		fread(&O.T[i].n1, 4, 1, fp);
		fread(&O.T[i].n2, 4, 1, fp);
		fread(&O.T[i].n3, 4, 1, fp);
		for (int j = 0; j < 3; j++)
		{
			fread(&O.T[i].x, 4, 1, fp);
			fread(&O.T[i].y, 4, 1, fp);
			fread(&O.T[i].z, 4, 1, fp);
		}
        fread(&O.T[i].color, 2, 1, fp);*/
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
		fwrite(&(O.T[i]), 50, 1, fp);
		/*fwrite(&O.T[i].n1, 4, 1, fp);
		fwrite(&O.T[i].n2, 4, 1, fp);
		fwrite(&O.T[i].n3, 4, 1, fp);
		for (int j = 0; j < 3; j++)
		{
			fwrite(&O.T[i].x, 4, 1, fp);
			fwrite(&O.T[i].y, 4, 1, fp);
			fwrite(&O.T[i].z, 4, 1, fp);
		}
		fwrite(&O.T[i].color, 2, 1, fp);*/
    }
    fclose(fp);
}
void write_txt(Object_3D O)
{
    FILE* fp = fopen("txt.stl", "w");
    fprintf(fp, "solid %s\n", "Naslov Trokut");
    for (int i = 0; i < O.num; i++)
    {
        fprintf(fp, "  facet normal %.1f %.1f %.1f\n", O.T[i].n1, O.T[i].n2, O.T[i].n3);
        fprintf(fp, "    outer loop\n");
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.T[i].x, O.T[i].y, O.T[i].z);
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.T[i].x, O.T[i].y, O.T[i].z);
        fprintf(fp, "      vertex %.1f %.1f %.1f\n", O.T[i].x, O.T[i].y, O.T[i].z);
        fprintf(fp, "    endloop\n");
        fprintf(fp, "  endfacet\n");
    }
    fprintf(fp, "endsolid %s", "Naslov Trokut");
    fclose(fp);
}
void delete_3D(Object_3D O)
{
    free(O.T);
}
void main()
{
    char* Header = (char*)malloc(sizeof(char) * 80);
    Object_3D O = read_binary(Header);
    write_binary(Header, O);
    write_txt(O);
    delete_3D(O);
   
}