
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];


void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  //get the unit length by dividing the range by 80
  double xUnit = (double)((maxX-minX)/MAXCOLS);
  double yRatio = 1;
  double yValues[MAXCOLS];
  double x = 0;
  double maxY = 0;
  double minY = 0;
  int axisX = 0;
  int axisY = 0;

  clearPlot();
  //loop 80 times
  for(int i = 0;i<MAXCOLS;i++){
    //get the number we're on, multiply by the unit, offset it by the minimum x value
    x = rpn_eval(funcFile,i*xUnit+minX);
    if(i==0){
        maxY = x;
        minY = x;
    }
    //Store in yy vector
    yValues[i]=x;
    //Find the largest and smallest values while storing them
    if(x>maxY){
        maxY = x;
    }
    if(x<minY){
        minY = x;
    }
  }

  yRatio = (MAXROWS-1)/(maxY-minY);
  for(int i=0; i<MAXCOLS; i++){
    yValues[i] = (int)round((yValues[i]-minY)*yRatio);
  }
  //Plot X axis if it's on the graph
  if(minX<=0&&maxX>=0){
    axisX = (int)round(maxY*(MAXROWS-1)/(maxY-minY));
    for(int i=0; i<MAXCOLS;i++){
        plotXY(i,axisX,'_');
    }
  }
  //Plot Y axis if it's on the graph
  if(minY<=0&&maxY>=0){
    axisY = (int)round(maxX*(MAXCOLS-1)/(maxX-minX));
    for(int i=0; i<MAXROWS;i++){
        plotXY(axisY,i,'|');
    }
  }
  //Check it out snake, go plot that shit
  for(int c=0; c<MAXCOLS;c++){
    plotXY(c,(MAXROWS-(int)round(yValues[c])-1),'*');
  }
  printPlot();
}

int main(int argc, char ** argv){
  printf("RPN Plotter.\n");

  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  // Get arguments
  char * fileName = argv[1];
  double min = strtod(argv[2],NULL);
  double max = strtod(argv[3],NULL);
  createPlot(fileName, min, max);
}
