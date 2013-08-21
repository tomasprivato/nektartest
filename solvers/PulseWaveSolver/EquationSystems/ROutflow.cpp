///////////////////////////////////////////////////////////////////////////////
//
// File CommMpi.cpp
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
// Description: MPI communication implementation
//
///////////////////////////////////////////////////////////////////////////////

#include <PulseWaveSolver/EquationSystems/ROutflow.h>

namespace Nektar
{

    std::string Routflow::className
    = GetFlowFactory().RegisterCreatorFunction(
        "Routflow",
        Routflow::create,
        "Resistive outflow boundary condition");

    /**
     *
     */
    Routflow::Routflow(Array<OneD, MultiRegions::ExpListSharedPtr> pVessel, const LibUtilities::SessionReaderSharedPtr pSession)
      : PulseWaveFlow(pVessel,pSession)
    {
    }

    /**
     *
     */
    Routflow::~Routflow()
    {

    }

    void Routflow::v_DoBoundary(int omega)
    { 
	NekDouble Q, A_r, u_r;
	NekDouble A_u, u_u;
        NekDouble R_t, A_l, u_l, u_0, c_0, c_l;

        Array<OneD, MultiRegions::ExpListSharedPtr>     vessel(2);

        vessel[0] = m_vessels[2*omega];
        vessel[1] = m_vessels[2*omega+1];
    }
}
