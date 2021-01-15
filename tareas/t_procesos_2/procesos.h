#ifndef PROC_H
#define PROC_H

void proceso_padre( int pipesfd[NPROC][2], int *datos );
void proceso_hijo( int np, int *pipefd, int *datos );

#endif
