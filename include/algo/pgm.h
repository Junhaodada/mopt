#ifndef MOPT_PGM_H
#define MOPT_PGM_H

#include "l1min/l1min.h"
#include "lrmr/lrmr.h"

/**
 * proximal gradient method
 */
class pgm {
public:
    void execute(l1min *problem);
    void execute(lrmr *problem);

    pgm(float64 tau = 5e-4, float64 epsilon = 1e-4, int64 maxIter = 2000, int64 logInter = 10);

    float64 tau;
    float64 epsilon;
    int64 max_iter;
    int64 log_inter;
};

#endif //MOPT_PGM_H
