#ifndef PROCESOS_H
#define PROCESOS_H

void proc_padre(  );
void proc_hijo_producto( int np, int *pipefd );
void proc_hijo_autocorrelacion( int np, int *pipefd );

#endif
