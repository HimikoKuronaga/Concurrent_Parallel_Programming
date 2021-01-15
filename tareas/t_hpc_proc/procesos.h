#ifndef PROC_H
#define PROC_H

void proc_padre( int pipesfd[NP][2] );
void proc_hijo( int np, int *pipefd );

#endif
