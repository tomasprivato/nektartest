///////////////////////////////////////////////////////////////////////////////
//
// File: CompressibleSolver.h
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
// Description: Compressible Riemann solver.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_COMPRESSIBLEFLOWSOLVER_RIEMANNSOLVER_COMPRESSIBLESOLVER
#define NEKTAR_SOLVERS_COMPRESSIBLEFLOWSOLVER_RIEMANNSOLVER_COMPRESSIBLESOLVER

#include <SolverUtils/RiemannSolvers/RiemannSolver.h>
#include <CompressibleFlowSolver/Misc/EquationOfState.h>

using namespace Nektar::SolverUtils;

namespace Nektar
{
    class CompressibleSolver : public RiemannSolver
    {
    protected:
        bool m_pointSolve;
        EquationOfStateSharedPtr m_eos;
        bool m_idealGas;
        
        CompressibleSolver(
                const LibUtilities::SessionReaderSharedPtr& pSession);

        virtual void v_Solve(
            const int                                         nDim,
            const Array<OneD, const Array<OneD, NekDouble> > &Fwd,
            const Array<OneD, const Array<OneD, NekDouble> > &Bwd,
                  Array<OneD,       Array<OneD, NekDouble> > &flux);

        virtual void v_ArraySolve(
            const Array<OneD, const Array<OneD, NekDouble> > &Fwd,
            const Array<OneD, const Array<OneD, NekDouble> > &Bwd,
                  Array<OneD,       Array<OneD, NekDouble> > &flux)
        {
            ASSERTL0(false, "This function should be defined by subclasses.");
        }
        
        virtual void v_PointSolve(
            NekDouble  rhoL, NekDouble  rhouL, NekDouble  rhovL, NekDouble  rhowL, NekDouble  EL,
            NekDouble  rhoR, NekDouble  rhouR, NekDouble  rhovR, NekDouble  rhowR, NekDouble  ER,
            NekDouble &rhof, NekDouble &rhouf, NekDouble &rhovf, NekDouble &rhowf, NekDouble &Ef)
        {
            ASSERTL0(false, "This function should be defined by subclasses.");
        }
        
        virtual void v_PointSolveVisc(
            NekDouble  rhoL, NekDouble  rhouL, NekDouble  rhovL, NekDouble  rhowL, NekDouble  EL, NekDouble EpsL,
            NekDouble  rhoR, NekDouble  rhouR, NekDouble  rhovR, NekDouble  rhowR, NekDouble  ER, NekDouble EpsR,
            NekDouble &rhof, NekDouble &rhouf, NekDouble &rhovf, NekDouble &rhowf, NekDouble &Ef, NekDouble &Epsf)
        {
            ASSERTL0(false, "This function should be defined by subclasses.");
        }

        NekDouble GetRoeSoundSpeed(
            NekDouble rhoL, NekDouble pL, NekDouble eL, NekDouble HL, NekDouble srL,
            NekDouble rhoR, NekDouble pR, NekDouble eR, NekDouble HR, NekDouble srR,
            NekDouble HRoe, NekDouble URoe2, NekDouble srLR);

        virtual void v_CalcFluxJacobian(
            const int                                         nDim,
            const Array<OneD, const Array<OneD, NekDouble> > &Fwd,
            const Array<OneD, const Array<OneD, NekDouble> > &Bwd,
            const Array<OneD, const Array<OneD, NekDouble> > &normals,
                  DNekBlkMatSharedPtr                         FJac,
                  DNekBlkMatSharedPtr                         BJac);
        
        virtual void v_PointFluxJacobian(
            const Array<OneD, NekDouble> &Fwd,
            const Array<OneD, NekDouble> &Bwd,
            const Array<OneD, NekDouble> &normals,
                  DNekMatSharedPtr        FJac,
                  DNekMatSharedPtr        BJac)
        {
            ASSERTL0(false, "v_PointFluxJacobian This function should be defined by subclasses.");
        }
    };
}

#endif
