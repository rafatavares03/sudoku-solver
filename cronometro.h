#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

struct timeval iniciaCronometro();
double finalizaCronometro(struct timeval inicio, char *processo, double tempoDecorrido);