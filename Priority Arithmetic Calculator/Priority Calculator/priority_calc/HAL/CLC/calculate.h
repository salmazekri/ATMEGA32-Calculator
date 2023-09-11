#ifndef CALCULATE_H
#define CALCULATE_H

void CalculateResult(u32 *expression);
u8 isValidOperation(u8 *expression);

#define MAXSIZE 20
 typedef union
 {
    float fData;
    char  cData;
 } Item;

 typedef struct
 {
    Item items[MAXSIZE];
    int top;
 } Stack;


#endif
