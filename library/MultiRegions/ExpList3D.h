///////////////////////////////////////////////////////////////////////////////
//
// File ExpList3D.h
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
// Description: Expansion list 3D header definition
//
///////////////////////////////////////////////////////////////////////////////

#ifndef EXPLIST3D_H
#define EXPLIST3D_H

#include <vector>
#include <MultiRegions/MultiRegions.hpp>
#include <MultiRegions/ExpList2D.h>

#include <LocalRegions/HexExp.h>
#include <LocalRegions/PrismExp.h>
#include <LocalRegions/PyrExp.h>
#include <LocalRegions/TetExp.h>
#include <SpatialDomains/MeshGraph3D.h>
#include <SpatialDomains/BoundaryConditions.h>

namespace Nektar
{
    namespace MultiRegions
    {
        /// Abstraction of a three-dimensional multi-elemental expansion which
        /// is merely a collection of local expansions.
        class ExpList3D:  public ExpList
        {
        public:
            /// Default constructor.
            ExpList3D();

            /// Copy constructor.
            ExpList3D(const ExpList3D &In);

/*          ExpList3D(const LibUtilities::BasisKey &Ba,
                  const LibUtilities::BasisKey &Bb,
                  const LibUtilities::BasisKey &Bc,
                  const SpatialDomains::MeshGraph3D &graph3D,
                  const LibUtilities::PointsType
                  TetNb = LibUtilities::SIZE_PointsType);
*/
            /// Sets up a list of local expansions based on an input mesh.
            ExpList3D(SpatialDomains::MeshGraph3D &graph3D);

            /// Destructor.
            ~ExpList3D();

        protected:
            /// Populates the list of boundary condition expansions.
            void SetBoundaryConditionExpansion(
                        SpatialDomains::MeshGraph3D &graph3D,
                        SpatialDomains::BoundaryConditions &bcs,
                        const std::string variable,
                        Array<OneD, ExpList2DSharedPtr> &bndCondExpansions,
                        Array<OneD, SpatialDomains::BoundaryConditionShPtr>
                                                                &bndConditions);

            /// Evaluates boundary conditions.
            void EvaluateBoundaryConditions(
                        const NekDouble time,
                        Array<OneD, ExpList2DSharedPtr> &bndCondExpansions,
                        Array<OneD, SpatialDomains::BoundaryConditionShPtr>
                                                                &bndConditions);

            /// Generates a map of periodic faces in the mesh.
            void GetPeriodicFaces(SpatialDomains::MeshGraph3D &graph3D,
                        SpatialDomains::BoundaryConditions &bcs,
                        const std::string variable,
                        map<int,int>& periodicVertices,
                        map<int,int>& periodicEdges,
                        map<int,int>& periodicFaces);

        private:
/*            LocalRegions::HexExpVector    m_hex;
            LocalRegions::PrismExpVector  m_prism;
            LocalRegions::PyrExpVector    m_pyr;
            LocalRegions::TetExpVector    m_tet;
*/
        };

        /// Shared pointer to an ExpList3D object.
        typedef boost::shared_ptr<ExpList3D>      ExpList3DSharedPtr;
        /// Vector of pointers to ExpList3D objects.
        typedef std::vector<ExpList3DSharedPtr>   ExpList3DVector;
        /// Iterator over an ExpList3DVector.
        typedef std::vector<ExpList3DSharedPtr>::iterator ExpList3DVectorIter;

    } //end of namespace
} //end of namespace

#endif
