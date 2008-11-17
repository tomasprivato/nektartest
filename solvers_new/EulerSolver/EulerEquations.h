///////////////////////////////////////////////////////////////////////////////
//
// File EulerEquations.h
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
// Description: Euler Equations definition in two-dimensions
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_EULEREQUATIONS_EULEREQUATIONS_H
#define NEKTAR_SOLVERS_EULEREQUATIONS_EULEREQUATIONS_H

#include <MultiRegions/DisContField2D.h>
#include <Auxiliary/ADRBase.h>

namespace Nektar
{     
    /**
     * 
     * 
     **/
    
    class EulerEquations: public ADRBase
    {
    public:           

        /**
         * Default constructor. 
         * 
         **/ 
        EulerEquations();


        /**
         * Constructor.
         * /param 
         * 
         *
         **/
        EulerEquations(string &fileStringName);
	
	void GetFluxVector(const int i, Array<OneD, Array<OneD, NekDouble> >&physfield, 
			   Array<OneD, Array<OneD, NekDouble> >&flux);
	
	void NumericalFlux(Array<OneD, Array<OneD, NekDouble> > &physfield,
                           Array<OneD, Array<OneD, NekDouble> > &numfluxX,
			   Array<OneD, Array<OneD, NekDouble> > &numfluxY);
        
        void ODEforcing(const Array<OneD, const  Array<OneD, NekDouble> >&inarray, 
			Array<OneD, Array<OneD, NekDouble> >&outarray, NekDouble time);
	
        void ExplicitlyIntegrateAdvection(int nsteps);

        void Summary(std::ostream &out);

	enum UpwindType
        {           ///< flux not defined
	  eNotSet,  ///< averaged (or centred) flux
	  eAverage, ///< simple upwind flux
	  eUpwind,  ///< local Lax-Friedrich flux
	  eLLF,     ///< Harten-Lax-Leer Contact corrected flux
	  eHLLC,    ///< Roe flux
	  eRoe,    
        };
	
    protected:

    private: 
        int m_infosteps;  ///< dump info to stdout at steps time

	NekDouble m_gamma; 

	void GetPressure(Array<OneD, Array<OneD, NekDouble> > &physfield,
			 Array<OneD, NekDouble> &pressure);


	void SetBoundaryConditions(Array<OneD, Array<OneD, NekDouble> > &physarray, NekDouble time);
	
	void WallBoundary(int bcRegion, Array<OneD, Array<OneD, NekDouble> > &physarray);


	void RiemannSolver(NekDouble rhoL, NekDouble rhouL, NekDouble rhovL, NekDouble EL,
			   NekDouble rhoR, NekDouble rhouR, NekDouble rhovR, NekDouble ER,
			   NekDouble &rhoflux, NekDouble &rhouflux, NekDouble &rhovflux, NekDouble &Eflux);
	
	virtual void v_GetFluxVector(const int i, Array<OneD, Array<OneD, NekDouble> > &physfield, 
				     Array<OneD, Array<OneD, NekDouble> > &flux) 
	{ 
	  GetFluxVector(i,physfield,flux);
        }
        
	virtual void v_NumericalFlux(Array<OneD, Array<OneD, NekDouble> > &physfield, 
				     Array<OneD, Array<OneD, NekDouble> > &numfluxX, 
				     Array<OneD, Array<OneD, NekDouble> > &numfluxY )
        {
	  NumericalFlux(physfield, numfluxX, numfluxY); 
        }
	
    };
    
    typedef boost::shared_ptr<EulerEquations> EulerEquationsSharedPtr;
    
} //end of namespace

#endif //NEKTAR_SOLVERS_EULEREQUATIONS_EULEREQUATIONS_H

/**
* $Log: EulerEquations.cpp,v $
* Revision 1.1  2008/08/22 09:48:23  pvos
* Added Claes' AdvectionDiffusionReaction, ShallowWater and Euler solver
*
**/
