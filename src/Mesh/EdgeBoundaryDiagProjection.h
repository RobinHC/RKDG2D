#ifndef EDGEBOUNDARYDIAGPROJECTION_H
#define EDGEBOUNDARYDIAGPROJECTION_H

#include "Point.h"
#include "EdgeBoundary.h"
#include "Mesh2D.h"

class Mesh2D;

class EdgeBoundaryDiagProjection : public EdgeBoundary
{
    //- Get projection of the defined point onto diagonal (only for uniform meshes!!!)
    Point getDiagProjection(const Point &p) const;

    //- Pointer to mesh
    const Mesh2D* mesh;

    //- Get number of cell in diagonal where given point placed
    int getNumDiagCell(const Point& p);

public:

    //- Default constructor
    EdgeBoundaryDiagProjection() : EdgeBoundary()  {}

    //- Construct using two nodes
    EdgeBoundaryDiagProjection(const Point& p1, const Point& p2) : EdgeBoundary(p1, p2) {}

    //- Destructor
    virtual ~EdgeBoundaryDiagProjection() = default;

    //// RKDG methods

    //- Set BC function
    virtual void setBoundaryFunction(const numvector<double, 5>& bc) override { }

    //- Set mesh pointer
    void setMeshPointer(const Mesh2D& msh) { mesh = &msh; }

    //- Apply boundary condition
    //numvector<double, 5> applyBoundary(const numvector<double, 5>& solLeft = {0.0, 0.0, 0.0, 0.0, 0.0}) const override
    //{ return { 0, 0, 0, 0, 0 }; }

    //- Calculate local fluxes in gauss points
    virtual void getLocalFluxes(const Flux& flux) override;

};

#endif // EDGEBOUNDARYDIAGPROJECTION_H
