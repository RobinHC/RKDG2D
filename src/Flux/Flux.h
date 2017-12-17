#ifndef FLUX_H
#define FLUX_H

#include "Problem.h"

class Flux
{

public:
    Problem *problem;

public:

    //- Default constructor
    Flux() {}

    //- Construct with problem
    Flux(Problem &prb);

    //- Destructor
    virtual ~Flux() {}
    
    //- Overloaded "=" operator
    Flux& operator=(const Flux& flx) { problem = flx.problem; return *this;}

    //- Evaluate numerical flux through one point
    virtual numvector<double, 5> evaluateHor(const numvector<double, 5>& solInner, const numvector<double, 5>& solOuter) const = 0;
    virtual numvector<double, 5> evaluateVer(const numvector<double, 5>& solInner, const numvector<double, 5>& solOuter) const = 0;

};// end Flux

#endif // FLUX_H

