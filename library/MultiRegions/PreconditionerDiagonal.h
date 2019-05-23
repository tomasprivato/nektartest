///////////////////////////////////////////////////////////////////////////////
//
// File Preconditioner.h
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
// Description: Preconditioner header
//
///////////////////////////////////////////////////////////////////////////////
#ifndef NEKTAR_LIB_MULTIREGIONS_PRECONDITIONERDIAGONAL_H
#define NEKTAR_LIB_MULTIREGIONS_PRECONDITIONERDIAGONAL_H
#include <MultiRegions/GlobalLinSys.h>
#include <MultiRegions/Preconditioner.h>
#include <MultiRegions/MultiRegionsDeclspec.h>
#include <MultiRegions/AssemblyMap/AssemblyMapCG.h>


namespace Nektar
{
    namespace MultiRegions
    {
        class PreconditionerDiagonal;
        typedef std::shared_ptr<PreconditionerDiagonal>  PreconditionerDiagonalSharedPtr;

        class PreconditionerDiagonal: public Preconditioner
	{
        public:
            /// Creates an instance of this class
            static PreconditionerSharedPtr create(
                        const std::shared_ptr<GlobalLinSys> &plinsys,
                        const std::shared_ptr<AssemblyMap> &pLocToGloMap)
            {
	        PreconditionerSharedPtr p = MemoryManager<PreconditionerDiagonal>::AllocateSharedPtr(plinsys,pLocToGloMap);
	        p->InitObject();
	        return p;
            }

            /// Name of class
            static std::string className;
            //static std::string className1;

            MULTI_REGIONS_EXPORT PreconditionerDiagonal(
                         const std::shared_ptr<GlobalLinSys> &plinsys,
	                 const AssemblyMapSharedPtr &pLocToGloMap);

            MULTI_REGIONS_EXPORT
            virtual ~PreconditionerDiagonal() {}

	protected:

            Array<OneD, NekDouble>                      m_diagonals;

	private:

            void DiagonalPreconditionerSum(void);

	    void StaticCondDiagonalPreconditionerSum(void);

            virtual void v_InitObject();

            virtual void v_DoPreconditioner(                
                      const Array<OneD, NekDouble>& pInput,
		      Array<OneD, NekDouble>& pOutput);

            virtual void v_BuildPreconditioner();

            static std::string lookupIds[];
            static std::string def;
	};

        class PreconditionerNull;
        typedef std::shared_ptr<PreconditionerNull>  PreconditionerNullSharedPtr;

        class PreconditionerNull: public Preconditioner
	{
        public:
            /// Creates an instance of this class
            static PreconditionerSharedPtr create(
                const std::shared_ptr<GlobalLinSys> &plinsys,
                const std::shared_ptr<AssemblyMap>
                &pLocToGloMap)
            {
	        PreconditionerSharedPtr p = MemoryManager<PreconditionerNull>::AllocateSharedPtr(plinsys,pLocToGloMap);
	        p->InitObject();
	        return p;
            }

            /// Name of class
            static std::string className;

            MULTI_REGIONS_EXPORT PreconditionerNull(
                const std::shared_ptr<GlobalLinSys> &plinsys,
                const AssemblyMapSharedPtr &pLocToGloMap);
            
            MULTI_REGIONS_EXPORT
            virtual ~PreconditionerNull() {}

	private:

            virtual void v_InitObject();

            virtual void v_DoPreconditioner(                
                      const Array<OneD, NekDouble>& pInput,
		      Array<OneD, NekDouble>& pOutput);

            virtual void v_BuildPreconditioner();

            static std::string lookupIds[];
            static std::string def;
	};

    }
}

#endif
