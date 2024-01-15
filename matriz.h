#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED
typedef struct
{
    float tx, ty;
    float d1, d2;
    float sen;
    float matriz[3][3];
    matriz[0][0] = d1; matriz[1][1] = d2; matriz[2][2] = 1 ;
    matriz[0][1] = sen*(-1); matriz[0][2] = tx; matriz[1][2] = ty;
    matriz[1][0] = sen; matriz[2][0] = 0.0; matriz[2][1] = 0.0;
}matrixP;

#endif // MATRIZ_H_INCLUDED
