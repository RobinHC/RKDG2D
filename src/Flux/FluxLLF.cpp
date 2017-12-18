#include "FluxLLF.h"
#include <iostream>

using namespace std;

// ------------------ Constructors & Destructors ----------------


// ------------------ Private class methods --------------------

// ------------------ Public class methods ---------------------

numvector<double,5> FluxLLF::evaluate( const numvector<double, 5>& solInner, const numvector<double, 5>& solOuter, const Point& n) const
{

    numvector<double,5> fluxOutward = n.x() * problem->fluxF(solInner) + n.y() * problem->fluxG(solInner);
    numvector<double,5> fluxInward = n.x() * problem->fluxF(solOuter) + n.y() * problem->fluxG(solOuter);

    double lambda = problem->lambdaG(solInner,solOuter)[4];

    return 0.5 * (fluxInward + fluxOutward) + 0.5 * lambda * (solInner - solOuter);
}


numvector<double,5> FluxLLF::evaluateHor( const numvector<double, 5>& solInner, const numvector<double, 5>& solOuter) const
{

    numvector<double,5> fluxOutward = problem->fluxG(solInner);
    numvector<double,5> fluxInward = problem->fluxG(solOuter);

    double lambda = problem->lambdaG(solInner,solOuter)[4];

    return 0.5 * (fluxInward + fluxOutward) + 0.5 * lambda * (solInner - solOuter);
}

numvector<double,5> FluxLLF::evaluateVer( const numvector<double, 5>& solInner, const numvector<double, 5>& solOuter) const
{
    numvector<double,5> fluxOutward = problem->fluxF(solInner);
    numvector<double,5> fluxInward = problem->fluxF(solOuter);

    double lambda = problem->lambdaF(solInner,solOuter)[4];

    return 0.5 * (fluxOutward + fluxInward) + 0.5 * lambda * (solInner - solOuter);
}


//numvector<double,5> FluxLLF::evaluateVer(numvector<double,2> point, const vector<numvector<double,5*nShapes>>& alpha, int iCellLeft, int iCellRight)
//{
//    numvector<double,5> solLeft = problem->reconstructSolution(alpha[iCellLeft],point,iCellLeft);
//    numvector<double,5> solRight = problem->reconstructSolution(alpha[iCellRight],point,iCellRight);

//    numvector<double,5> fluxLeftRight = problem->fluxF(solLeft);
//    numvector<double,5> fluxRightLeft = problem->fluxF(solRight);

//    double lambda = problem->lambdaF(solLeft,solRight)[4];

//    return 0.5 * (fluxLeftRight + fluxRightLeft) + 0.5 * lambda * (solLeft - solRight);
//}

//vector<numvector<double,5*nShapes>> FluxLLF::getRHS(const vector<numvector<double,5*nShapes>>& alpha)
//{
//    //cout << "welcome to hell" << endl;




//    int nEdgesHor = mesh->edgesHor.size();
//    int nEdgesVer = mesh->edgesVer.size();
//    int nCells = mesh->nInternalCells;
//    vector<numvector<double,5*nShapes>> RHS(nCells);


//    numvector<double,5> buffer;

//    vector<function<numvector<double, 5>(numvector<double, 2>)>> integrateFluxesHor(nEdgesHor);
//    vector<function<numvector<double, 5>(numvector<double, 2>)>> integrateFluxesVer(nEdgesVer);

//    GaussIntegrator GP;



///*    for (int i = 0; i < nEdgesHor; ++i)
//    {
//        double a = mesh->nodes[mesh->edgesHor[i][0]][0];
//        double b = mesh->nodes[mesh->edgesHor[i][1]][0];
//        double y = mesh->nodes[mesh->edgesHor[i][0]][1];

//        int iCellUp = mesh->neighbCellsHorEdges[i][1];
//        int iCellDown = mesh->neighbCellsHorEdges[i][0];

//        function<numvector<double,5>(numvector<double,2>)> f = [=](numvector<double,2> point)
//        {
//            return evaluateHor(point,alpha,iCellUp,iCellDown);
//        };

//        integrateFluxesHor[i] = f;
//    }
//*/

///*
//    for (int i = 0; i < nCells; ++i)
//    {
//        // for hor edges
//        double a = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][0]][0];
//        double b = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][1]][0];
//        double y = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][0]][1];

//        // for down edge
//        int iCellUp = i; //mesh->neighbCellsHorEdges[mesh->cells[i][0]][1];
//        int iCellDownCell = mesh->neighbCellsHorEdges[mesh->cells[i][0]][0];

//        for (int q = 0; q < nShapes; ++q)
//        {
//            function<numvector<double,5>(double)> f = [=](double x)
//            {
//                numvector<double, 2> point = {x, y};
//                return ;
//            };
//        }
//    }
//*/


//    double a,b,z;
//    numvector<numvector<double, 2>,4> cellNodes;
//    int iCellOne,iCellTwo;


//    for(int i=0;i<nCells;++i)
//    {
//        for(int j=0;j<nShapes;++j)
//        {


//            // Get fluxes through cell
//            cellNodes = mesh->getCellCoordinates(i);
//            function<numvector<double, 5>(numvector<double, 2>)> f5 = [&](numvector<double,2> point)
//            {
//                return problem->fluxF( problem->reconstructSolution(alpha[i],point,i) )  * problem->gradPhi[j](point,i)[0] + \
//                       problem->fluxG( problem->reconstructSolution(alpha[i],point,i) )  * problem->gradPhi[j](point,i)[1] ;
//            };

//            buffer = GP.integrate(f5,cellNodes);

//            for(int p=0;p<5;++p)
//            {
//                RHS[i][p*nShapes+j] = buffer[p];
//                //cout << buffer[p] << ' ' ;

//            }// for p



//            // Get fluxes through edges
//            // for the down edge
//            a = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][0]][0];
//            b = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][1]][0];
//            z = mesh->nodes[mesh->edgesHor[mesh->cells[i][0]][0]][1];

//            iCellOne = i;
//            iCellTwo = mesh->neighbCellsHorEdges[mesh->cells[i][0]][0];

//            function<numvector<double,5>(double)> f1 = [&](double x)
//            {
//                numvector<double, 2> point = {x, z};
//                //problem->write(cout,alpha[0]);
//                return evaluateHor(point,alpha,iCellOne,iCellTwo) * problem->phi[j](point,i);
//            };

//            buffer = GP.integrate(f1,a,b);

//            for(int p=0; p < 5; ++p)
//            {
//                RHS[i][p*nShapes+j] += buffer[p];
//                //cout << buffer[p] << ' ' ;
//            }// for p

//            //cout << endl;



//            // for the up edge
//            a = mesh->nodes[mesh->edgesHor[mesh->cells[i][1]][0]][0];
//            b = mesh->nodes[mesh->edgesHor[mesh->cells[i][1]][1]][0];
//            z = mesh->nodes[mesh->edgesHor[mesh->cells[i][1]][0]][1];

//            iCellOne = mesh->neighbCellsHorEdges[mesh->cells[i][1]][0];
//            iCellTwo = i;

//            function<numvector<double,5>(double)> f2 = [&](double x)
//            {
//                numvector<double, 2> point = {x, z};
//                return evaluateHor(point,alpha,iCellOne,iCellTwo) * problem->phi[j](point,i);
//            };

//            buffer = GP.integrate(f2,a,b);

//            for(int p=0;p<5;++p)
//            {
//                RHS[i][p*nShapes+j]-=buffer[p];

//                //cout << buffer[p] << ' ' ;
//            }// for p

//            //cout << endl;


//            // for the left edge
//            a = mesh->nodes[mesh->edgesVer[mesh->cells[i][2]][0]][1];
//            b = mesh->nodes[mesh->edgesVer[mesh->cells[i][2]][1]][1];
//            z = mesh->nodes[mesh->edgesVer[mesh->cells[i][2]][0]][0];

//            iCellOne = mesh->neighbCellsVerEdges[mesh->cells[i][2]][0];
//            iCellTwo = i;

//            function<numvector<double,5>(double)> f3 = [&](double y)
//            {
//                numvector<double, 2> point = {z, y};
//                return evaluateVer(point,alpha,iCellOne,iCellTwo) * problem->phi[j](point,i);
//            };

//            buffer = GP.integrate(f3,a,b);

//            for(int p=0;p<5;++p)
//            {
//                RHS[i][p*nShapes+j]+=buffer[p];
//                //cout << buffer[p] << ' ' ;
//            }// for p

//            //cout << endl;

//            // for the right edge
//            a = mesh->nodes[mesh->edgesVer[mesh->cells[i][3]][0]][1];
//            b = mesh->nodes[mesh->edgesVer[mesh->cells[i][3]][1]][1];
//            z = mesh->nodes[mesh->edgesVer[mesh->cells[i][3]][0]][0];

//            iCellOne = i;
//            iCellTwo = mesh->neighbCellsVerEdges[mesh->cells[i][3]][1];

//            function<numvector<double,5>(double)> f4 = [&](double y)
//            {
//                numvector<double, 2> point = {z, y};
//                return evaluateVer(point,alpha,iCellOne,iCellTwo) * problem->phi[j](point,i);
//            };

//            buffer = GP.integrate(f4,a,b);

//            for(int p=0;p<5;++p)
//            {
//                RHS[i][p*nShapes+j]-=buffer[p];
//                //cout << buffer[p] << ' ' ;

//            }// for p

//            //cout << endl;




//        } // for j
//    }// for i


//    return RHS;

//}
