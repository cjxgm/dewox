
#ifndef __STACKING__
#define __STACKING__

typedef struct oprinfo
{
  float tick;
  float step;
  short rendered[128];
  struct oprinfo * inputs[4];
}
oprinfo;

typedef struct
{
  char enabled;
  char x;
  char y;
  char w;
  char hovered;
  char selected;
  char type;
  oprinfo oi;
}
opr;

#endif
