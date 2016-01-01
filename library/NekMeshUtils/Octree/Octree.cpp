////////////////////////////////////////////////////////////////////////////////
//
//  File: octree.h
//
//  For more information, please see: http://www.nektar.info/
//
//  The MIT License
//
//  Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
//  Department of Aeronautics, Imperial College London (UK), and Scientific
//  Computing and Imaging Institute, University of Utah (USA).
//
//  License for the specific language governing rights and limitations under
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  Description: cad object methods.
//
////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <limits>

#include <LibUtilities/BasicUtils/Progressbar.hpp>

#include <NekMeshUtils/Octree/Octree.h>
#include <NekMeshUtils/CADSystem/CADSurf.h>

using namespace std;
namespace Nektar
{
namespace NekMeshUtils
{
/*
NekDouble Octree::Query(Array<OneD, NekDouble> loc)
{
    //starting at master octant 0 move through succsesive octants which contain
    //the point loc until a leaf is found
    OctantSharedPtr n = m_masteroct;
    int quad;

    bool found=false;

    while(!found)
    {
        Array<OneD, NekDouble> octloc = n->GetLoc();

        if(!(loc[0] < octloc[0]) &&
           !(loc[1] < octloc[1]) &&
           !(loc[2] < octloc[2]))
        {
            quad=0;
        }
        else if(!(loc[0] < octloc[0]) &&
                !(loc[1] > octloc[1]) &&
                !(loc[2] < octloc[2]))
        {
            quad=1;
        }
        else if(!(loc[0] > octloc[0]) &&
                !(loc[1] > octloc[1]) &&
                !(loc[2] < octloc[2]))
        {
            quad=2;
        }
        else if(!(loc[0] > octloc[0]) &&
                !(loc[1] < octloc[1]) &&
                !(loc[2] < octloc[2]))
        {
            quad=3;
        }
        else if(!(loc[0] < octloc[0]) &&
                !(loc[1] < octloc[1]) &&
                !(loc[2] > octloc[2]))
        {
            quad=4;
        }
        else if(!(loc[0] < octloc[0]) &&
                !(loc[1] > octloc[1]) &&
                !(loc[2] > octloc[2]))
        {
            quad=5;
        }
        else if(!(loc[0] > octloc[0]) &&
                !(loc[1] > octloc[1]) &&
                !(loc[2] > octloc[2]))
        {
            quad=6;
        }
        else if(!(loc[0] > octloc[0]) &&
                !(loc[1] < octloc[1]) &&
                !(loc[2] > octloc[2]))
        {
            quad=7;
        }
        else
        {
            ASSERTL0(false,"Cannot locate quadrant");
        }

        n = n->GetChild(quad);

        if(n->IsLeaf())
        {
            found=true;
        }
    }
    return n->GetDelta();
}
*/
Array<OneD, Array<OneD, Array<OneD, NekDouble> > > Octree::GetOctantVerts()
{
    Array<OneD, Array<OneD, Array<OneD, NekDouble> > > out(Octants.size());
    for(int i = 0; i < Octants.size(); i++)
    {
        Array<OneD, Array<OneD, NekDouble> > oct(8);
        Array<OneD, NekDouble> p1(3);
        p1[0] = Octants[i]->FX(eBack);
        p1[1] = Octants[i]->FX(eRight);
        p1[2] = Octants[i]->FX(eDown);
        oct[0] = p1;

        Array<OneD, NekDouble> p2(3);
        p2[0] = Octants[i]->FX(eForward);
        p2[1] = Octants[i]->FX(eRight);
        p2[2] = Octants[i]->FX(eDown);
        oct[1] = p2;

        Array<OneD, NekDouble> p3(3);
        p3[0] = Octants[i]->FX(eForward);
        p3[1] = Octants[i]->FX(eLeft);
        p3[2] = Octants[i]->FX(eDown);
        oct[2] = p3;

        Array<OneD, NekDouble> p4(3);
        p4[0] = Octants[i]->FX(eBack);
        p4[1] = Octants[i]->FX(eLeft);
        p4[2] = Octants[i]->FX(eDown);
        oct[3] = p4;

        Array<OneD, NekDouble> p5(3);
        p5[0] = Octants[i]->FX(eBack);
        p5[1] = Octants[i]->FX(eRight);
        p5[2] = Octants[i]->FX(eUp);
        oct[4] = p5;

        Array<OneD, NekDouble> p6(3);
        p6[0] = Octants[i]->FX(eForward);
        p6[1] = Octants[i]->FX(eRight);
        p6[2] = Octants[i]->FX(eUp);
        oct[5] = p6;

        Array<OneD, NekDouble> p7(3);
        p7[0] = Octants[i]->FX(eForward);
        p7[1] = Octants[i]->FX(eLeft);
        p7[2] = Octants[i]->FX(eUp);
        oct[6] = p7;

        Array<OneD, NekDouble> p8(3);
        p8[0] = Octants[i]->FX(eBack);
        p8[1] = Octants[i]->FX(eLeft);
        p8[2] = Octants[i]->FX(eUp);
        oct[7] = p8;

        out[i] = oct;
    }
    return out;
}

void Octree::Build()
{
    BoundingBox = m_cad->GetBoundingBox();

    if(m_verbose)
        cout << endl << "Octree system" << endl;

    //build curvature samples
    CompileCuravturePointList();

    if(m_verbose)
        cout << "\tCurvature samples: " << m_cpList.size() << endl;

    NekDouble maxdim = (BoundingBox[1]-BoundingBox[0])/2 >
                           (BoundingBox[3]-BoundingBox[2])/2 ?
                           (BoundingBox[1]-BoundingBox[0])/2 :
                           (BoundingBox[3]-BoundingBox[2])/2;
    maxdim = maxdim > (BoundingBox[5]-BoundingBox[4])/2 ?
                        maxdim : (BoundingBox[5]-BoundingBox[4])/2;

    //make master octant based on the bounding box of the domain
    m_masteroct = MemoryManager<Octant>::AllocateSharedPtr(0,
                        (BoundingBox[1]+BoundingBox[0])/2.0,
                        (BoundingBox[3]+BoundingBox[2])/2.0,
                        (BoundingBox[5]+BoundingBox[4])/2.0, maxdim, m_cpList);

    numoct = 1;
    m_masteroct->Subdivide(m_masteroct, numoct);

    InitialSubDivide();

    Octants.clear();
    m_masteroct->CompileLeaves(Octants);

    cout << Octants.size() << endl;

    /*

    SmoothSurfaceOctants();

    if(m_verbose)
        cout << "\tPropagating spacing out to domain boundary" << endl;

    PropagateDomain();

    if(m_verbose)
        cout << "\tRecersively ensuring smoothness between all nodes" << endl;

    SmoothAllOctants();

    if(m_relax)
    {
        Relax();
    }

    for(int i = 0; i < Octants.size(); i++)
    {
        OctantSharedPtr oct = Octants[i];
        if(oct->IsLeaf())
        {
            ASSERTL0(!(oct->GetDelta() < 0.0),
                     "Error in initial octree construction");
        }
    }

    if(m_verbose)
    {
        int elem = CountElemt();
        printf("\tPredicted mesh: %.2d elements\n", elem);
    }*/
}

void Octree::SubDivide()
{
    bool repeat;
    vector<OctantSharedPtr> Octants;

    do
    {
        repeat = false;
        Octants.clear();
        //grab a list of the leaves curently in the octree
        m_masteroct->CompileLeaves(Octants);

        //needs to complile a list of leaf octants which require subdivision to make sure
        //the levels will not exceed one
        //Then create a list of octants which want to subdivide and then execute them
        vector<OctantSharedPtr> dividelist;
        for(int i = 0; i < Octants.size(); i++)
        {
            bool divide = false;
            map<OctantFace, vector<OctantSharedPtr> > ne = Octants[i]->GetNeigbours();
            map<OctantFace, vector<OctantSharedPtr> >::iterator it;
            for(it = ne.begin(); it != ne.end(); it++)
            {
                for(int j = 0; j < it->second.size(); j++)
                {
                    if(it->second[j]->NeedDivide())
                    {
                        if(it->second[j]->DX() < Octants[i]->DX())
                        {
                            dividelist.push_back(Octants[i]);
                            divide = true;
                            break;
                        }
                    }
                }
                if(divide) break;
            }
        }
        for(int i = 0; i < dividelist.size(); i++)
        {
            dividelist[i]->Subdivide(dividelist[i], numoct);
        }

        Octants.clear();
        m_masteroct->CompileLeaves(Octants);

        //loop over all the octants and subdivide if they want to
        for(int i = 0; i < Octants.size(); i++)
        {
            if(Octants[i]->NeedDivide() && Octants[i]->DX() / 4.0 > m_minDelta)
            {
                Octants[i]->Subdivide(Octants[i], numoct);
                repeat = true;
            }
        }
    }
    while(repeat);
}

/*

void Octree::SmoothSurfaceOctants()
{
    //for all the octants which are surface containing and know their delta
    //specification, look over all neighbours and ensure the specification
    //between them is smooth
    int ct = 0;
    OctantSet::iterator it;

    do
    {
        ct=0;
        for(int i = 0; i < Octants.size(); i++)
        {
            OctantSharedPtr oct = Octants[i];

            if(oct->IsLeaf() && oct->IsDeltaKnown())
            {
                vector<OctantSharedPtr> check;
                vector<OctantSharedPtr> nList = oct->GetNeighbourList();

                for(int j = 0; j < nList.size(); j++)
                {
                    if(nList[j]->IsDeltaKnown() && nList[j]->GetDelta()
                                                    < oct->GetDelta()
                       && ddx(oct, nList[j]) > 0.2)
                    {
                        check.push_back(nList[j]);
                    }
                }

                //for each neighbour listed in check_id, figure out the smoothed
                // delta, and asign the miminum of these to nodes[i].GetDelta()
                if(check.size() > 0)
                {
                    NekDouble deltaSM = numeric_limits<double>::max();
                    for(int j = 0; j < check.size(); j++)
                    {
                        NekDouble r = oct->Distance(check[j]);

                        if(0.199 * r + check[j]->GetDelta() < deltaSM)
                        {
                            deltaSM = 0.199 * r + check[j]->GetDelta();
                        }
                    }
                    oct->SetDelta(deltaSM);
                    ASSERTL0(!(deltaSM<m_minDelta),
                                    "Delta assignment less than min delta");
                    ct+=1;
                }
            }
        }

    }while(ct>0);
}

void Octree::PropagateDomain()
{
    //until all octants know their delta specifcation and orientaion
    //look over all octants and if their neighours know either their orientation
    //or specifcation calculate one for this octant
    int ct=0;
    OctantSet::iterator it;

    do
    {
        ct=0;
        for(int i = 0; i < Octants.size(); i++)
        {
            OctantSharedPtr oct = Octants[i];

            if(oct->IsLeaf() && !oct->IsDeltaKnown())
            { //if it is leaf and delta has not been asigned
                ct+=1;
                vector<OctantSharedPtr> known;
                vector<OctantSharedPtr> nList = oct->GetNeighbourList();

                for(int j = 0; j < nList.size(); j++)
                {
                    if(nList[j]->IsDeltaKnown())
                    {
                        known.push_back(nList[j]);
                    }
                }//create list of neighbours where delta is known.

                if(known.size() > 0)
                {
                    vector<NekDouble> deltaPrime;
                    for(int j = 0; j < known.size(); j++)
                    {
                        NekDouble r = oct->Distance(known[j]);

                        if(0.24*r + known[j]->GetDelta() < m_maxDelta)
                        {
                            deltaPrime.push_back(0.24 * r + known[j]->GetDelta());
                        }
                        else
                        {
                            deltaPrime.push_back(m_maxDelta);
                        }
                    }
                    NekDouble min=numeric_limits<double>::max();
                    for(int j = 0; j < deltaPrime.size(); j++)
                    {
                        if(deltaPrime[j] < min)
                        {
                            min=deltaPrime[j];
                        }
                    }
                    oct->SetDelta(min);
                    ASSERTL0(!(min<m_minDelta),
                            "Delta assignment less than min delta");
                    deltaPrime.clear();
                }
                known.clear();
            }

            if(oct->IsLeaf() && oct->GetLocation() == eUnknown)
            { //if the node does not know its location
                ct+=1;
                vector<OctantSharedPtr> known;
                vector<OctantSharedPtr> nList = oct->GetNeighbourList();

                for(int j = 0; j < nList.size(); j++)
                {
                    if(nList[j]->GetLocation() != eUnknown)
                    {
                        known.push_back(nList[j]);
                    }
                }
                if(known.size() > 0)
                {
                    vector<OctantSharedPtr> isOrient2;
                    for(int j = 0; j < known.size(); j++)
                    {
                        if(known[j]->GetLocation() == eOnBoundary)
                        {
                            isOrient2.push_back(known[j]);
                        }
                    }

                    if(isOrient2.size() == 0)
                    {
                        NekDouble dist=numeric_limits<double>::max();
                        OctantSharedPtr closest;
                        for(int j = 0; j < known.size(); j++)
                        {
                            if(oct->Distance(known[j]) < dist)
                            {
                                closest= known[j];
                                dist = oct->Distance(known[j]);
                            }
                        }

                        oct->SetLocation(closest->GetLocation());

                    }
                    else
                    {
                        NekDouble dist = numeric_limits<double>::max();

                        OctantSharedPtr closest;

                        for(int j = 0; j < isOrient2.size(); j++)
                        {
                            if(oct->Distance(isOrient2[j]) < dist)
                            {
                                closest = isOrient2[j];
                                dist = oct->Distance(isOrient2[j]);
                            }
                        }

                        CurvaturePointSharedPtr closestPoint;
                        dist = numeric_limits<double>::max();
                        vector<CurvaturePointSharedPtr> cp = closest->GetCPList();
                        for(int j = 0; j < cp.size(); j++)
                        {
                            if(oct->CPDistance(cp[j]) < dist)
                            {
                                closestPoint = cp[j];
                                dist = oct->CPDistance(cp[j]);
                            }
                        }

                        Array<OneD, NekDouble> octloc, cploc, vec(3), uv, N;
                        int surf;
                        closestPoint->GetCAD(surf, uv);
                        N = m_cad->GetSurf(surf)->N(uv);

                        octloc = oct->GetLoc();
                        cploc = closestPoint->GetLoc();

                        vec[0] = octloc[0] - cploc[0];
                        vec[1] = octloc[1] - cploc[1];
                        vec[2] = octloc[2] - cploc[2];

                        NekDouble dot = vec[0]*N[0] + vec[1]*N[1] + vec[2]*N[2];

                        if(dot <= 0.0)
                        {
                            oct->SetLocation(eOutside);
                        }
                        else
                        {
                            oct->SetLocation(eInside);
                        }
                    }
                }
                known.clear();
            }
        }

    }while(ct>0);

    for(int i = 0; i < Octants.size(); i++)
    {
        OctantSharedPtr oct = Octants[i];
        if(oct->IsLeaf())
        {
            ASSERTL0(oct->GetDelta() > 0.0, "leaf delta less than zero");
        }
    }
}

void Octree::SmoothAllOctants()
{
    //until no more changes occur smooth the mesh specification between all
    //octants not particualrly strictly
    int ct = 0;

    do
    {
        ct=0;
        for(int i = 0; i < Octants.size(); i++)
        {
            OctantSharedPtr oct = Octants[i];

            if(oct->IsLeaf())
            {
                vector<OctantSharedPtr> check;
                vector<OctantSharedPtr> nList = oct->GetNeighbourList();

                for(int j = 0; j < nList.size(); j++)
                {
                    if(!nList[j]->IsLeaf()) //this should not happen but does, this is a bit hacky but fixes it
                    {
                        continue;
                    }
                    if(nList[j]->GetDelta() < oct->GetDelta() && ddx(oct, nList[j]) > 0.3)
                    {
                        check.push_back(nList[j]);
                    }
                }

                //for each neighbour listed in check, figure out the smoothed delta, and asign the miminum of these to nodes[i].GetDelta()
                if(check.size() > 0)
                {
                    NekDouble deltaSM = numeric_limits<double>::max();
                    for(int j = 0; j < check.size(); j++)
                    {
                        NekDouble r = oct->Distance(check[j]);

                        if(0.29 * r + check[j]->GetDelta() < deltaSM)
                        {
                            deltaSM = 0.29 * r + check[j]->GetDelta();
                        }
                    }
                    oct->SetDelta(deltaSM);
                    ct+=1;
                }
            }
        }

    }while(ct>0);
}

int Octree::CountElemt()
{
    //by considering the volume of a tet evaluate the number of elements in the
    //mesh

    NekDouble total = 0.0;

    for(int i = 0; i < Octants.size(); i++)
    {
        OctantSharedPtr oct = Octants[i];
        if(oct->IsLeaf())
        {
            if(oct->GetLocation() == 1)
            {
                total += 8.0*oct->DX()*oct->DX()*oct->DX() /
                 (oct->GetDelta()*oct->GetDelta()*oct->GetDelta()/6.0/sqrt(2));
            }
            else if(oct->GetLocation() == 2)
            {
            }
        }
    }

    return int(total);
}*/

void Octree::CompileCuravturePointList()
{
    for(int i = 1; i <= m_cad->GetNumSurf(); i++)
    {
        CADSurfSharedPtr surf = m_cad->GetSurf(i);
        Array<OneD, NekDouble> bounds = surf->GetBounds();

        //to figure out the amount of curvature sampling to be conducted on
        //each parameter plane the surface is first sampled with a 40x40 grid
        //the real space lengths of this grid are analysed to find the largest
        //strecthing in the u and v directions
        //this stretching this then cosnidered with the mindelta user input
        //to find a number of sampling points in each direction which
        //enures that in the final octree each surface octant will have at least
        //one sample point within its volume.
        //the 40x40 grid is used to ensure each surface has a minimum of 40x40
        //samples.
        NekDouble du = (bounds[1]-bounds[0])/(40-1);
        NekDouble dv = (bounds[3]-bounds[2])/(40-1);

        NekDouble DeltaU = 0.0;
        NekDouble DeltaV = 0.0;

        Array<TwoD, Array<OneD, NekDouble> > samplepoints(40,40);

        for(int j = 0; j < 40; j++)
        {
            for(int k = 0; k < 40; k++)
            {
                Array<OneD, NekDouble> uv(2);
                uv[0] = k*du + bounds[0];
                uv[1] = j*dv + bounds[2];
                if(j==40-1) uv[1]=bounds[3];
                if(k==40-1) uv[0]=bounds[1];
                samplepoints[k][j] = surf->P(uv);
            }
        }

        for(int j = 0; j < 40-1; j++)
        {
            for(int k = 0; k < 40-1; k++)
            {
                NekDouble deltau = sqrt((samplepoints[k][j][0]-
                                         samplepoints[k+1][j][0])*
                                        (samplepoints[k][j][0]-
                                         samplepoints[k+1][j][0])+
                                        (samplepoints[k][j][1]-
                                         samplepoints[k+1][j][1])*
                                        (samplepoints[k][j][1]-
                                         samplepoints[k+1][j][1])+
                                        (samplepoints[k][j][2]-
                                         samplepoints[k+1][j][2])*
                                        (samplepoints[k][j][2]-
                                         samplepoints[k+1][j][2]));
                NekDouble deltav = sqrt((samplepoints[k][j][0]-
                                         samplepoints[k][j+1][0])*
                                        (samplepoints[k][j][0]-
                                         samplepoints[k][j+1][0])+
                                        (samplepoints[k][j][1]-
                                         samplepoints[k][j+1][1])*
                                        (samplepoints[k][j][1]-
                                         samplepoints[k][j+1][1])+
                                        (samplepoints[k][j][2]-
                                         samplepoints[k][j+1][2])*
                                        (samplepoints[k][j][2]-
                                         samplepoints[k][j+1][2]));

                if(deltau > DeltaU)
                    DeltaU = deltau;
                if(deltav > DeltaV)
                    DeltaV = deltav;
            }
        }

        //these are the acutal number of sample points in each parametric
        //direction
        int nu = ceil(DeltaU/m_minDelta)*40;
        int nv = ceil(DeltaV/m_minDelta)*40;

        for(int j = 0; j < nu; j++)
        {
            for(int k = 0; k < nv; k++)
            {
                Array<OneD, NekDouble> uv(2);
                uv[0] = (bounds[1]-bounds[0])/(nu-1)*j + bounds[0];
                uv[1] = (bounds[3]-bounds[2])/(nv-1)*k + bounds[2];

                //this prevents round off error at the end of the surface
                //may not be neseercary but works
                if(j==nu-1) uv[0]=bounds[1];
                if(k==nv-1) uv[1]=bounds[3];

                NekDouble C = surf->Curvature(uv);

                //create new point based on smallest R, flat surfaces have k=0
                //but still need a point for element estimation
                if(C != 0.0)
                {
                    bool minlimited = false;
                    NekDouble ideal;

                    NekDouble del = 2.0*(1.0/C)*sqrt(m_eps*(2.0-m_eps));

                    if(del>m_maxDelta)
                    {
                        del = m_maxDelta;
                    }
                    if(del<m_minDelta)
                    {
                        ideal = del;
                        del = m_minDelta;
                        minlimited = true;
                    }

                    if(minlimited)
                    {
                        CurvaturePointSharedPtr newCPoint =
                            MemoryManager<CurvaturePoint>::AllocateSharedPtr
                            (surf->GetId(), uv, surf->P(uv), del, ideal);

                        m_cpList.push_back(newCPoint);
                    }
                    else
                    {
                        CurvaturePointSharedPtr newCPoint =
                            MemoryManager<CurvaturePoint>::AllocateSharedPtr
                            (surf->GetId(), uv, surf->P(uv), del);

                        m_cpList.push_back(newCPoint);
                    }

                }else
                {
                    CurvaturePointSharedPtr newCPoint =
                        MemoryManager<CurvaturePoint>::AllocateSharedPtr
                        (surf->GetId(), uv, surf->P(uv));

                    m_cpList.push_back(newCPoint);
                }
            }
        }
    }
}

/*NekDouble Octree::ddx(OctantSharedPtr i, OctantSharedPtr j)
{
    return fabs(i->GetDelta() - j->GetDelta()) / i->Distance(j);
}

void Octree::AssignNeigbours(OctantSharedPtr const &o)
{
    //clear old list
    o->ClearNeigbourList();

    OctantSet::iterator it;
    vector<OctantSharedPtr> nlist;

    int eqhit = 0;

    //look over all octants and consider if they are neigbours
    for(int i = 0; i < Octants.size(); i++)
    {
        OctantSharedPtr oct = Octants[i];

        if(oct->IsLeaf())
        {
            if(oct == o)
            {
                eqhit++;
                continue;
            }

            //work out the max distance between the two octants if they were
            //joined corner to corner
            NekDouble rmax = o->DiagonalDim() + oct->DiagonalDim();

            NekDouble ractual = o->Distance(oct);

            //if the actucal distance between them is greater that this
            //this octant should not be considered, massive speed up
            if(ractual > 1.1*rmax)
            {
                continue;
            }

            //check overlapping in 2-D for all three dimensions
            if(fabs(o->FX(-1) - oct->FX(+1)) < 1E-6 ||
               fabs(o->FX(+1) - oct->FX(-1)) < 1E-6 )
            {
                //check yz rects
                bool Cond1 = false;
                bool Cond2 = false;
                bool Cond3 = false;
                bool Cond4 = false;
                if(o->FY(+1) < oct->FY(-1))
                    Cond1 = true;
                if(o->FY(-1) > oct->FY(+1))
                    Cond1 = true;
                if(o->FZ(+1) < oct->FZ(-1))
                    Cond1 = true;
                if(o->FZ(-1) > oct->FZ(+1))
                    Cond1 = true;
                if(!Cond1 && !Cond2 && !Cond3 && !Cond4)
                {
                    nlist.push_back(oct);
                }
            }
            else if(fabs(o->FY(-1) - oct->FY(+1)) <1E-6 ||
                    fabs(o->FY(+1) - oct->FY(-1)) <1E-6)
            {
                //check xz rects
                bool Cond1 = false;
                bool Cond2 = false;
                bool Cond3 = false;
                bool Cond4 = false;
                if(o->FX(+1) < oct->FX(-1))
                    Cond1 = true;
                if(o->FX(-1) > oct->FX(+1))
                    Cond1 = true;
                if(o->FZ(+1) < oct->FZ(-1))
                    Cond1 = true;
                if(o->FZ(-1) > oct->FZ(+1))
                    Cond1 = true;
                if(!Cond1 && !Cond2 && !Cond3 && !Cond4)
                {
                    nlist.push_back(oct);
                }
            }
            else if(fabs(o->FZ(-1) - oct->FZ(+1)) <1E-6 ||
                    fabs(o->FZ(+1) - oct->FZ(-1)) <1E-6)
            {
                //check xy rects
                bool Cond1 = false;
                bool Cond2 = false;
                bool Cond3 = false;
                bool Cond4 = false;
                if(o->FX(+1) < oct->FX(-1))
                    Cond1 = true;
                if(o->FX(-1) > oct->FX(+1))
                    Cond1 = true;
                if(o->FY(+1) < oct->FY(-1))
                    Cond1 = true;
                if(o->FY(-1) > oct->FY(+1))
                    Cond1 = true;
                if(!Cond1 && !Cond2 && !Cond3 && !Cond4)
                {
                    nlist.push_back(oct);
                }
            }
        }
    }
    o->SetNeigbourList(nlist);
    ASSERTL0(eqhit == 1,"found itself more than once");
}*/

}
}
