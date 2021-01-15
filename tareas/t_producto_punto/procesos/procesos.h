#ifndef PROCESOS_H
#define PROCESOS_H

void proc_padre( int pipesfd[NP][2] );
void proc_hijo( int np, int *pipefd );

#endif
