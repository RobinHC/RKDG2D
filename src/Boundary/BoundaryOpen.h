#ifndef BOUNDARYOPEN_H
#define BOUNDARYOPEN_H

#include "Boundary.h"

class BoundaryOpen : public Boundary
{
public:

    //- Default constructor
    BoundaryOpen() {};

    //- Apply boundary condition
    numvector<double, 5> applyBoundary(const numvector<double, 5>& solLeft = {0.0, 0.0, 0.0, 0.0, 0.0}) const override;

};

#endif // BOUNDARYOPEN_H