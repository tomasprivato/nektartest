///////////////////////////////////////////////////////////////////////////////
//
// File: DiffusionLDG.h
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2006 Division of Applied Mathematics, Brown University (USA),
// Department of Aeronautics, Imperial College London (UK), and Scientific
// Computing and Imaging Institute, University of Utah (USA).
//
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
// Description: LDG diffusion class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERUTILS_DIFFUSIONWEAKDG
#define NEKTAR_SOLVERUTILS_DIFFUSIONWEAKDG

#include <boost/core/ignore_unused.hpp>

#include <SolverUtils/Diffusion/Diffusion.h>

namespace Nektar
{
    namespace SolverUtils
    {
        class DiffusionLDG : public Diffusion
        {
        public:
            static DiffusionSharedPtr create(std::string diffType)
            {
                boost::ignore_unused(diffType);
                return DiffusionSharedPtr(new DiffusionLDG());
            }
            
            static std::string type;
            
        protected:
            DiffusionLDG();
   		
	    std::string                          m_shockCaptureType;
	         
            Array<OneD, Array<OneD, NekDouble> >              m_traceNormals;
            LibUtilities::SessionReaderSharedPtr              m_session;

            virtual void v_InitObject(
                LibUtilities::SessionReaderSharedPtr               pSession,
                Array<OneD, MultiRegions::ExpListSharedPtr>        pFields);
            
            virtual void v_Diffuse(
                const int                                          nConvective,
                const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
                const Array<OneD, Array<OneD, NekDouble> >        &inarray,
                      Array<OneD, Array<OneD, NekDouble> >        &outarray,
                const Array<OneD, Array<OneD, NekDouble> > &pFwd = NullNekDoubleArrayofArray,
                const Array<OneD, Array<OneD, NekDouble> > &pBwd = NullNekDoubleArrayofArray);
            
            virtual void v_NumFluxforScalar(
                const Array<OneD, MultiRegions::ExpListSharedPtr>       &fields,
                const Array<OneD, Array<OneD, NekDouble> >              &ufield,
                      Array<OneD, Array<OneD, Array<OneD, NekDouble> > >&uflux,
                const Array<OneD, Array<OneD, NekDouble> > &pFwd = NullNekDoubleArrayofArray,
                const Array<OneD, Array<OneD, NekDouble> > &pBwd = NullNekDoubleArrayofArray);
            
            virtual void v_WeakPenaltyforScalar(
                const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
                const int                                          var,
                const Array<OneD, const NekDouble>                &ufield,
                const Array<OneD, const NekDouble>                &uplus,
                      Array<OneD,       NekDouble>                &penaltyflux);
            
            virtual void v_NumFluxforVector(
                const Array<OneD, MultiRegions::ExpListSharedPtr>       &fields,
                const Array<OneD, Array<OneD, NekDouble> >              &ufield,
                      Array<OneD, Array<OneD, Array<OneD, NekDouble> > >&qfield,
                      Array<OneD, Array<OneD, NekDouble> >              &qflux);
            
            virtual void v_WeakPenaltyforVector(
                const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
                const int                                          var,
                const int                                          dir,
                const Array<OneD, const NekDouble>                &qfield,
                const Array<OneD, const NekDouble>                &qtemp,
                      Array<OneD,       NekDouble>                &penaltyflux,
                NekDouble                                          C11);
        }; 
    }
}
    
#endif
