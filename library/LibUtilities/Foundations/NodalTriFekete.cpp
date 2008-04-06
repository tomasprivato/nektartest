///////////////////////////////////////////////////////////////////////////////
//
// File NodalTriFekete.cpp
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
// Department of Aeronautics, Imperial College London (UK), and Scientific
// Computing and Imaging Institute, University of Utah (USA).
//
// License for the specific language governing rights and limitations under
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
// 
// Description: 2D Nodal Triangle Fekete Point Definitions
//
///////////////////////////////////////////////////////////////////////////////
#include <LibUtilities/LibUtilities.h>
#include <iostream>
#include <algorithm>
#include <limits>
#include <math.h>
#include <LibUtilities/Foundations/Points.h>
#include <LibUtilities/Foundations/Foundations.hpp>
#include <LibUtilities/BasicUtils/ErrorUtil.hpp>
#include <LibUtilities/Polylib/Polylib.h>
#include <LibUtilities/Foundations/NodalTriFeketeData.h>

#include <LibUtilities/LinearAlgebra/NekMatrixFwd.hpp>
#include <LibUtilities/LinearAlgebra/Lapack.hpp>
#include <LibUtilities/LinearAlgebra/NekLinSys.hpp>
#include <LibUtilities/BasicUtils/SharedArray.hpp>

#include <LibUtilities/Foundations/NodalTriFekete.h>
#include <LibUtilities/Foundations/NodalUtil.h>


namespace Nektar
{
    namespace LibUtilities
    {


        void NodalTriFekete::CalculatePoints()
        {
            // Allocate the storage for points
            PointsBaseType::CalculatePoints();

            int index=0,isum=0;
            const int offset = 3; //offset to match Datafile
            NekDouble a,b,c;
            unsigned int numPoints = GetNumPoints();

            // initialize values
            for(unsigned int i=0; i < numPoints-2; ++i)
            {
                index += NodalTriFeketeNPTS[i];
            }

            for(unsigned int i=0; i < NodalTriFeketeNPTS[numPoints-2]; ++i, ++index)
            {
                if(int(NodalTriFeketeData[index][0]))
                {
                    a = NodalTriFeketeData[index][3]; 
                    b = NodalTriFeketeData[index][4]; 
                    c = NodalTriFeketeData[index][5]; 

                    m_points[0][isum] = 2.0*b - 1.0;
                    m_points[1][isum] = 2.0*c - 1.0;
                    isum++;
                    continue;
                }//end symmetry1


                if(int(NodalTriFeketeData[index][1]) == 1)
                {
                    for(unsigned int j=0; j < 3; ++j)
                    {
                        a = NodalTriFeketeData[index][offset+perm3A_2d[j][0]];
                        b = NodalTriFeketeData[index][offset+perm3A_2d[j][1]];
                        c = NodalTriFeketeData[index][offset+perm3A_2d[j][2]];
                        m_points[0][isum] = 2.0*b - 1.0;
                        m_points[1][isum] = 2.0*c - 1.0;
                        isum++;
                    }//end j
                    continue;
                }//end symmetry3a

                if(int(NodalTriFeketeData[index][1]) == 2)
                {
                    for(unsigned int j=0; j < 3; ++j)
                    {
                        a = NodalTriFeketeData[index][offset+perm3B_2d[j][0]];
                        b = NodalTriFeketeData[index][offset+perm3B_2d[j][1]];
                        c = NodalTriFeketeData[index][offset+perm3B_2d[j][2]];
                        m_points[0][isum] = 2.0*b - 1.0;
                        m_points[1][isum] = 2.0*c - 1.0;
                        isum++;
                    }//end j
                    continue;   
                }//end symmetry3b


                if(int(NodalTriFeketeData[index][2]))
                {
                    for(unsigned int j=0; j < 6; ++j)
                    {
                        a = NodalTriFeketeData[index][offset+perm6_2d[j][0]];
                        b = NodalTriFeketeData[index][offset+perm6_2d[j][1]];
                        c = NodalTriFeketeData[index][offset+perm6_2d[j][2]];
                        m_points[0][isum] = 2.0*b - 1.0;
                        m_points[1][isum] = 2.0*c - 1.0;
                        isum++;
                    }//end j
                    continue;   
                }//end symmetry6
            }//end npts

            NodalPointReorder2d();

            ASSERTL1((isum==m_pointsKey.GetTotNumPoints()),"sum not equal to npts");
        }
        
        void NodalTriFekete::CalculateWeights()
        {
            // Allocate the storage for points
            PointsBaseType::CalculateWeights();

            typedef DataType T;
            
            // Solve the Vandermonde system of integrals for the weight vector
            NekVector<T> w = MakeQuadratureWeights(NekVector<T>(m_points[0]), NekVector<T>(m_points[1]));
            
            m_weights = Array<OneD,T>( w.GetRows(), w.GetPtr() );

        }
           
        // ////////////////////////////////////////
        //        CalculateInterpMatrix()
        void NodalTriFekete::CalculateInterpMatrix(const Array<OneD, const NekDouble>& xia, const Array<OneD, const NekDouble>& yia,
                                                   Array<OneD, NekDouble>& interp)
        {
             NekVector<NekDouble>  x( m_points[0] );
             NekVector<NekDouble>  y( m_points[1] );
             NekVector<NekDouble> xi( xia );
             NekVector<NekDouble> yi( yia );
             NekMatrix<NekDouble> interMat = GetInterpolationMatrix(x, y, xi, yi);

             int rows = xi.GetRows(), cols = GetTotNumPoints();
             for( int i = 0; i < rows; ++i ) {
                for( int j = 0; j < cols; ++j ) {
                    interp[j + i*cols] = interMat(i,j);
                }
             }
         }

         // ////////////////////////////////////////
        //        CalculateDerivMatrix()
        void NodalTriFekete::CalculateDerivMatrix()
        {            
            // Allocate the derivative matrix.
            PointsBaseType::CalculateDerivMatrix();

            NekVector<NekDouble> x( m_points[0] );
            NekVector<NekDouble> y( m_points[1] );
            NekVector<NekDouble> xi = x;
            NekVector<NekDouble> yi = y;

            m_derivmatrix[0] = GetXDerivativeMatrix(x,y,xi,yi);
            m_derivmatrix[1] = GetYDerivativeMatrix(x,y,xi,yi);

        }

        boost::shared_ptr<NodalTriFekete::PointsBaseType> NodalTriFekete::Create(const PointsKey &key)
        {
            boost::shared_ptr<PointsBaseType> returnval(MemoryManager<NodalTriFekete>::AllocateSharedPtr(key));
            returnval->Initialize();
            return returnval;
        }

        void NodalTriFekete::NodalPointReorder2d()
        {
            int i,j;
            int cnt;
            int istart,iend;

            NekDouble evaluateTol  = 1e-12;

            const int nVerts = 3;
            const int nEdgeInteriorPoints = GetNumPoints()-2;
            const int nBoundaryPoints = 3*nEdgeInteriorPoints + 3; 

            if(nEdgeInteriorPoints==0)
            {
                return;
            }

            // group the points of edge 1 together;
            istart = nVerts;
            for(i = cnt = istart; i < nBoundaryPoints; i++)
            {
                if( fabs(m_points[1][i] + 1.0) < evaluateTol)
                {
                    std::swap(m_points[0][cnt], m_points[0][i]);
                    std::swap(m_points[1][cnt], m_points[1][i]);
                    cnt++;
                }
            }

            // bubble sort edge 1 (counterclockwise numbering)
            iend = istart + nEdgeInteriorPoints;
            for(i = istart; i < iend; i++)
            {
                for(j = istart+1; j < iend; j++)
                {
                    if(m_points[0][j] < m_points[0][j-1])
                    {
                        std::swap(m_points[0][j], m_points[0][j-1]);
                        std::swap(m_points[1][j], m_points[1][j-1]);
                    }
                }
            }

            // group the points of edge 2 together;
            istart = iend;
            for(i = cnt = istart; i < nBoundaryPoints; i++)
            {
                if( fabs(m_points[1][i]+m_points[0][i]) < evaluateTol)
                {
                    std::swap(m_points[0][cnt], m_points[0][i]);
                    std::swap(m_points[1][cnt], m_points[1][i]);
                    cnt++;
                }
            }

            // bubble sort edge 2 (counterclockwise numbering)
            iend = istart + nEdgeInteriorPoints;
            for(i = istart; i < iend; i++)
            {
                for(j = istart+1; j < iend; j++)
                {
                    if(m_points[1][j] < m_points[1][j-1])
                    {
                        std::swap(m_points[0][j], m_points[0][j-1]);
                        std::swap(m_points[1][j], m_points[1][j-1]);
                    }
                }
            }

            // group the points of edge 3 together;
            istart = iend;
            for(i = cnt = istart; i < nBoundaryPoints; i++)
            {
                if( fabs(m_points[0][i]+1.0) < evaluateTol)
                {
                    std::swap(m_points[0][cnt], m_points[0][i]);
                    std::swap(m_points[1][cnt], m_points[1][i]);
                    cnt++;
                }
            }
            // bubble sort edge 3 (counterclockwise numbering)
            iend = istart + nEdgeInteriorPoints;
            for(i = istart; i < iend; i++)
            {
                for(j = istart+1; j < iend; j++)
                {
                    if(m_points[1][j] > m_points[1][j-1])
                    {
                        std::swap(m_points[0][j], m_points[0][j-1]);
                        std::swap(m_points[1][j], m_points[1][j-1]);
                    }
                }
            }
            return;
        }     


    } // end of namespace stdregion
} // end of namespace stdregion

/**
* $Log: NodalTriFekete.cpp,v $
* Revision 1.24  2008/04/02 21:12:35  pvos
* Update of the 2D local to global map
*
* Revision 1.23  2008/03/18 14:11:50  pvos
* Update for nodal triangular helmholtz solver
*
* Revision 1.22  2007/10/03 03:00:13  bnelson
* Added precompiled headers.
*
* Revision 1.21  2007/08/06 05:41:25  ehan
* Fixed derivative matrix
*
* Revision 1.20  2007/07/31 18:19:11  ehan
* Conform to Coding Style Standard
*
* Revision 1.19  2007/07/26 22:24:24  ehan
* conform to Coding Style Standard
*
* Revision 1.18  2007/07/22 23:03:27  bnelson
* Backed out Nektar::ptr.
*
* Revision 1.17  2007/07/21 05:01:50  ehan
* Completed version of NodalTriFekete with integration, derivation, and interpolation implemented and tested.
*
* Revision 1.12  2007/05/15 03:37:24  bnelson
* Updated to use the new Array object.
*
* Revision 1.11  2007/04/30 23:29:10  jfrazier
* More conversion to multi_array.
*
* Revision 1.10  2007/04/29 00:31:57  jfrazier
* Updated to use multi_arrays.
*
*/

