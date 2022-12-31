#ifndef __ADT_H
#define __ADT_H

typedef struct _adt_ Adt;

Adt *adtCreate(int maxItens);
int adtInsert(Adt *cofo, int item);
int adtRemove(Adt *cofo, int key);
int adtRemoveNth(Adt *adt, int nth);
int adtQuery (Adt *cofo, int key);
int adtDestroy(Adt *cofo);
void printAdt(Adt *cofo);
#endif