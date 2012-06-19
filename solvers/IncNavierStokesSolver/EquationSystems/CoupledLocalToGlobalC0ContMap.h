///////////////////////////////////////////////////////////////////////////////
//
// File CoupledLcoalToGlobalC0ContMap.h
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
// Description: Wrapper class around the library
// LocalToGlobalC0ContMap class for use in the Couplied Linearised NS
// solver.
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_COUPLEDLOCALTOGLOBALC0CONTMAP_H
#define NEKTAR_SOLVERS_COUPLEDLOCALTOGLOBALC0CONTMAP_H

#include <IncNavierStokesSolver/EquationSystems/IncNavierStokes.h>
#include <MultiRegions/AssemblyMap/AssemblyMapCG2D.h>
#include <MultiRegions/GlobalLinSysDirectStaticCond.h>
#include <SpatialDomains/MeshGraph.h>

namespace Nektar
{
    class CoupledLocalToGlobalC0ContMap: public MultiRegions::AssemblyMapCG2D
    {
    public:
        CoupledLocalToGlobalC0ContMap(const LibUtilities::SessionReaderSharedPtr &pSession,
                                      const SpatialDomains::MeshGraphSharedPtr &graph,
                                      const SpatialDomains::BoundaryConditionsSharedPtr &boundaryConditions,
                                      const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
                                      const MultiRegions::ExpListSharedPtr &pressure,
                                      const int nz_loc,
                                      const bool CheeckForSingularSys=true);
    };

    typedef boost::shared_ptr<CoupledLocalToGlobalC0ContMap> CoupledLocalToGlobalC0ContMapSharedPtr;
        
}

#endif
