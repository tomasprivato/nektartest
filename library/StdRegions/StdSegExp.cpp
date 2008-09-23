///////////////////////////////////////////////////////////////////////////////
//
// File StdSegExp.cpp
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
// Description: Routines within Standard Segment Expansions
//
///////////////////////////////////////////////////////////////////////////////

#include <StdRegions/StdSegExp.h>


namespace Nektar
{
    namespace StdRegions
    {

        StdSegExp::StdSegExp(const LibUtilities::BasisKey &Ba):
        StdExpansion1D(Ba.GetNumModes(),Ba)
        {    
        }
        
        StdSegExp::StdSegExp(const StdSegExp &T):
            StdExpansion1D(T)
        {
        }
        
        StdSegExp::~StdSegExp()
        {    
        }

        
        //----------------------------
        // Integration Methods
        //----------------------------
        
        NekDouble StdSegExp::Integral(const Array<OneD, const NekDouble>& inarray)
        {
            NekDouble Int = 0.0;
            int    nquad0 = m_base[0]->GetNumPoints();
            Array<OneD, NekDouble> tmp(nquad0);
            Array<OneD, const NekDouble> z  = m_base[0]->GetZ();
            Array<OneD, const NekDouble> w0 = m_base[0]->GetW();
            
            // multiply by integration constants 
            Vmath::Vmul(nquad0, inarray, 1, w0, 1, tmp, 1);
            
            Int = Vmath::Vsum(nquad0, tmp, 1);
            
            return Int;
        }

        void StdSegExp::IProductWRTBase(const Array<OneD, const NekDouble>& base, 
                                        const Array<OneD, const NekDouble>& inarray,
                                        Array<OneD, NekDouble> &outarray, 
                                        int coll_check)
        {
            int    nquad = m_base[0]->GetNumPoints();
            Array<OneD, NekDouble> tmp(nquad);
            Array<OneD, const NekDouble> z =  m_base[0]->GetZ();
            Array<OneD, const NekDouble> w =  m_base[0]->GetW();
            
            Vmath::Vmul(nquad, inarray, 1, w, 1, tmp, 1);
            
            if(coll_check&&m_base[0]->Collocation())
            {
                Vmath::Vcopy(nquad, tmp, 1, outarray, 1);
            }
            else
            {
                Blas::Dgemv('T',nquad,m_ncoeffs,1.0,base.get(),nquad,
                            &tmp[0],1,0.0,outarray.get(),1);
            }    
        }
        
        void StdSegExp::FillMode(const int mode, Array<OneD, NekDouble> &outarray)
        {
            int   nquad = m_base[0]->GetNumPoints();
            const NekDouble * base  = m_base[0]->GetBdata().get();
            
            ASSERTL2(mode <= m_ncoeffs , 
             "calling argument mode is larger than total expansion order");
            
            Vmath::Vcopy(nquad,(NekDouble *)base+mode*nquad,1, &outarray[0],1);
        }
    
        DNekMatSharedPtr StdSegExp::GenMatrix(const StdMatrixKey &mkey) 
        {
            DNekMatSharedPtr Mat;
            Mat = StdExpansion::CreateGeneralMatrix(mkey);
            
            switch(mkey.GetMatrixType())
            {
            case eMass:
                // For Fourier basis set the imaginary component of mean mode
                // to have a unit diagonal component in mass matrix 
                if(m_base[0]->GetBasisType() == LibUtilities::eFourier)
                {
                    (*Mat)(1,1) = 1.0;
                }
                break;
            }
            
            return Mat;
        }

        void StdSegExp::LaplacianMatrixOp(const Array<OneD, const NekDouble> &inarray,
                                          Array<OneD,NekDouble> &outarray)
        {
            int    i;
            int    nquad = m_base[0]->GetNumPoints();

            Array<OneD,NekDouble> physValues(nquad);
            Array<OneD,NekDouble> dPhysValuesdx(nquad);

            BwdTrans(inarray,physValues);

            // Laplacian matrix operation
            PhysDeriv(physValues,dPhysValuesdx);            
            IProductWRTBase(m_base[0]->GetDbdata(),dPhysValuesdx,outarray,1);        
        }

        void StdSegExp::HelmholtzMatrixOp(const Array<OneD, const NekDouble> &inarray,
                                          Array<OneD,NekDouble> &outarray,
                                          const double lambda)
        {
            int    i;
            int    nquad = m_base[0]->GetNumPoints();

            Array<OneD,NekDouble> physValues(nquad);
            Array<OneD,NekDouble> dPhysValuesdx(nquad);
            Array<OneD,NekDouble> wsp(m_ncoeffs);

            BwdTrans(inarray,physValues);

            // mass matrix operation
            IProductWRTBase((m_base[0]->GetBdata()),physValues,wsp,1);

            // Laplacian matrix operation
            PhysDeriv(physValues,dPhysValuesdx);            
            IProductWRTBase(m_base[0]->GetDbdata(),dPhysValuesdx,outarray,1);
            Blas::Daxpy(m_ncoeffs, lambda, wsp.get(), 1, outarray.get(), 1);            
        }
        
        //----------------------------
        // Differentiation Methods
        //-----------------------------
        
        void StdSegExp::PhysDeriv(const Array<OneD, const NekDouble>& inarray, 
                                  Array<OneD, NekDouble> &out_d0,
                                  Array<OneD, NekDouble> &out_d1,
                                  Array<OneD, NekDouble> &out_d2)
        {
            PhysTensorDeriv(inarray,out_d0);
        }
        
        //----------------------------
        // Evaluation Methods
        //----------------------------
        
        void StdSegExp::BwdTrans(const Array<OneD, const NekDouble>& inarray, 
                                 Array<OneD, NekDouble> &outarray)
        {
            int  nquad = m_base[0]->GetNumPoints();
            
            if(m_base[0]->Collocation())
            {
                Vmath::Vcopy(nquad, inarray, 1, outarray, 1);
            }
            else
            {

#ifdef NEKTAR_USING_DIRECT_BLAS_CALLS

                Blas::Dgemv('N',nquad,m_base[0]->GetNumModes(),1.0, (m_base[0]->GetBdata()).get(),
                            nquad,&inarray[0],1,0.0,&outarray[0],1);

#else //NEKTAR_USING_DIRECT_BLAS_CALLS

                NekVector<const NekDouble> in(m_ncoeffs,inarray,eWrapper);
                NekVector<NekDouble> out(nquad,outarray,eWrapper);
                NekMatrix<const double> B(nquad,m_ncoeffs,m_base[0]->GetBdata(),eWrapper);
                out = B * in;

#endif //NEKTAR_USING_DIRECT_BLAS_CALLS 

            }
        }
        
        void StdSegExp::FwdTrans(const Array<OneD, const NekDouble>& inarray, 
                                 Array<OneD, NekDouble> &outarray)
        {
            if(m_base[0]->Collocation())
            {
                Vmath::Vcopy(m_ncoeffs, inarray, 1, outarray, 1);
            }
            else
            {
                IProductWRTBase(inarray,outarray);
                
                // get Mass matrix inverse
                StdMatrixKey      masskey(eInvMass,DetExpansionType(),*this);
                DNekMatSharedPtr& matsys = GetStdMatrix(masskey);
                
                NekVector<const NekDouble> in(m_ncoeffs,outarray,eCopy);
                NekVector<NekDouble> out(m_ncoeffs,outarray,eWrapper);
                
                out = (*matsys)*in;
            }
        }

        void StdSegExp::FwdTrans_BndConstrained(const Array<OneD, const NekDouble>& inarray, 
                                                Array<OneD, NekDouble> &outarray)
        {
            if(m_base[0]->Collocation())
            {
                Vmath::Vcopy(m_ncoeffs, inarray, 1, outarray, 1);
            }
            else
            {
                int nInteriorDofs = m_ncoeffs-2;
                int offset;
                
                switch(m_base[0]->GetBasisType())
                {
                case LibUtilities::eGLL_Lagrange:
                    {
                        offset = 1;
                    }
                    break;
                case LibUtilities::eModified_A:
                case LibUtilities::eModified_B:
                    {
                        offset = 2;
                    }
                    break;
                default:
                    ASSERTL0(false,"This type of FwdTrans is not defined for this expansion type");
                }    

                fill(outarray.get(), outarray.get()+m_ncoeffs, 0.0 );

                outarray[GetVertexMap(0)] = inarray[0];
                outarray[GetVertexMap(1)] = inarray[m_base[0]->GetNumPoints()-1];

                if(m_ncoeffs>2)
                {
                    Array<OneD, NekDouble> tmp0(m_ncoeffs); //ideally, we would like to have tmp0 to be replaced by outarray (currently MassMatrixOp does not allow aliasing)
                    Array<OneD, NekDouble> tmp1(m_ncoeffs);
                    
                    MassMatrixOp(outarray,tmp0);
                    IProductWRTBase(inarray,tmp1);
                    
                    Vmath::Vsub(m_ncoeffs, tmp1, 1, tmp0, 1, tmp1, 1);
                    
                    // get Mass matrix inverse (only of interior DOF)
                    StdMatrixKey      masskey(eMass,DetExpansionType(),*this);
                    DNekMatSharedPtr  matsys = (m_stdStaticCondMatrixManager[masskey])->GetBlock(1,1);
                    
                    Blas::Dgemv('N',nInteriorDofs,nInteriorDofs,1.0, &(matsys->GetPtr())[0],
                                nInteriorDofs,tmp1.get()+offset,1,0.0,outarray.get()+offset,1);                
                }
            }
        }

        void StdSegExp::GetBoundaryMap(Array<OneD, unsigned int>& outarray)
        {
            if(outarray.num_elements()!=NumBndryCoeffs())
            {
                outarray = Array<OneD, unsigned int>(NumBndryCoeffs());
            }
            const LibUtilities::BasisType Btype = GetBasisType(0);
            int nummodes = m_base[0]->GetNumModes();

            outarray[0] = 0;

            switch(Btype)
            {
            case LibUtilities::eGLL_Lagrange:
                outarray[1]= nummodes-1;
                break;
            case LibUtilities::eModified_A:
            case LibUtilities::eModified_B:
                outarray[1] = 1;
                break;
            default:
                ASSERTL0(0,"Mapping array is not defined for this expansion");
                break;
            }
        }
        
        void StdSegExp::GetInteriorMap(Array<OneD, unsigned int>& outarray)
        {
            int i;
            if(outarray.num_elements()!=GetNcoeffs()-NumBndryCoeffs())
            {
                outarray = Array<OneD, unsigned int>(GetNcoeffs()-NumBndryCoeffs());
            }
            const LibUtilities::BasisType Btype = GetBasisType(0);

            switch(Btype)
            {
            case LibUtilities::eGLL_Lagrange:
                for(i = 0 ; i < GetNcoeffs()-2;i++)
                {
                    outarray[i] = i+1;
                }
                break;
            case LibUtilities::eModified_A:
            case LibUtilities::eModified_B:
                for(i = 0 ; i < GetNcoeffs()-2;i++)
                {
                    outarray[i] = i+2;
                }
                break;
            default:
                ASSERTL0(0,"Mapping array is not defined for this expansion");
                break;
            }
        }
        
        int StdSegExp::GetVertexMap(const int localVertexId)
        {
            ASSERTL0((localVertexId==0)||(localVertexId==1),"local vertex id"
                     "must be between 0 or 1");

            int localDOF = localVertexId;

            if( (m_base[0]->GetBasisType()==LibUtilities::eGLL_Lagrange) &&
                (localVertexId==1) )
            {
                localDOF = m_base[0]->GetNumModes()-1;
            }
            return localDOF;
        }

        
        void StdSegExp::GetCoords(Array<OneD, NekDouble> &coords)
        {
            Blas::Dcopy(GetNumPoints(0),(m_base[0]->GetZ()).get(),
                        1,&coords[0],1);
        }

        void StdSegExp::WriteToFile(std::ofstream &outfile, OutputFormat format, const bool dumpVar)
        {
            if(format==eTecplot)
            {
                int i,j;
                int     nquad = m_base[0]->GetNumPoints();
                Array<OneD, const NekDouble> z = m_base[0]->GetZ();
                
                if(dumpVar)
                {
                    outfile << "Variables = z, Coeffs \n" << std::endl;   
                }
                
                outfile << "Zone, I=" << nquad <<", F=Point" << std::endl;
                
                for(i = 0; i < nquad; ++i)
                {
                    outfile << z[i] << " " << m_phys[i] << std::endl;
                }
            }
            else if(format==eGmsh)
            {
                int i,j;
                int     nquad = m_base[0]->GetNumPoints();
                Array<OneD, const NekDouble> z = m_base[0]->GetZ();

                if(dumpVar)
                {
                    outfile<<"View.Type = 2;"<<endl;
                    outfile<<"View \" \" {"<<endl;
                }
 
                for(i = 0; i < nquad; ++i)
                {
                    outfile << "SP(" << z[i] <<",  0.0, 0.0){" << m_phys[i] << "};" << endl;
                }

                if(dumpVar)
                { 
                    outfile << "};" << endl;
                }
            }
            else
            {
                ASSERTL0(false, "Output routine not implemented for requested type of output");
            }
        }

    }//end namespace
}//end namespace

/** 
* $Log: StdSegExp.cpp,v $
* Revision 1.55  2008/07/19 21:12:54  sherwin
* Removed MapTo function and made orientation convention anticlockwise in UDG routines
*
* Revision 1.54  2008/07/04 10:18:40  pvos
* Some updates
*
* Revision 1.53  2008/07/02 14:08:56  pvos
* Implementation of HelmholtzMatOp and LapMatOp on shape level
*
* Revision 1.52  2008/06/06 14:57:51  pvos
* Minor Updates
*
* Revision 1.51  2008/05/30 00:33:49  delisi
* Renamed StdRegions::ShapeType to StdRegions::ExpansionType.
*
* Revision 1.50  2008/05/29 21:36:25  pvos
* Added WriteToFile routines for Gmsh output format + modification of BndCond implementation in MultiRegions
*
* Revision 1.49  2008/05/07 16:04:57  pvos
* Mapping + Manager updates
*
* Revision 1.48  2008/04/22 05:22:15  bnelson
* Speed enhancements.
*
* Revision 1.47  2008/04/06 06:04:15  bnelson
* Changed ConstArray to Array<const>
*
* Revision 1.46  2008/04/03 16:12:11  pvos
* updates for NEKTAR_USING_DIRECT_BLAS_CALLS
*
* Revision 1.45  2008/04/02 22:18:10  pvos
* Update for 2D local to global mapping
*
* Revision 1.44  2008/03/12 15:25:09  pvos
* Clean up of the code
*
* Revision 1.43  2007/12/17 13:03:51  sherwin
* Modified StdMatrixKey to contain a list of constants and GenMatrix to take a StdMatrixKey
*
* Revision 1.42  2007/12/06 22:44:47  pvos
* 2D Helmholtz solver updates
*
* Revision 1.41  2007/11/29 21:40:22  sherwin
* updates for MultiRegions and DG solver
*
* Revision 1.40  2007/10/03 11:37:51  sherwin
* Updates relating to static condensation implementation
*
* Revision 1.39  2007/07/20 02:16:55  bnelson
* Replaced boost::shared_ptr with Nektar::ptr
*
* Revision 1.38  2007/07/12 12:55:16  sherwin
* Simplified Matrix Generation
*
* Revision 1.37  2007/07/11 13:35:18  kirby
* *** empty log message ***
*
* Revision 1.36  2007/07/10 21:05:18  kirby
* even more fixes
*
* Revision 1.34  2007/07/10 19:27:58  kirby
* Update for new matrix structures
*
* Revision 1.33  2007/07/09 15:19:15  sherwin
* Introduced an InvMassMatrix and replaced the StdLinSysManager call with a StdMatrixManager call to the inverse matrix
*
* Revision 1.32  2007/06/07 15:54:19  pvos
* Modificications to make Demos/MultiRegions/ProjectCont2D work correctly.
* Also made corrections to various ASSERTL2 calls
*
* Revision 1.31  2007/05/31 19:13:12  pvos
* Updated NodalTriExp + LocalRegions/Project2D + some other modifications
*
* Revision 1.30  2007/05/17 17:59:28  sherwin
* Modification to make Demos work after introducion of Array<>
*
* Revision 1.29  2007/05/15 05:18:24  bnelson
* Updated to use the new Array object.
*
* Revision 1.28  2007/04/10 14:00:46  sherwin
* Update to include SharedArray in all 2D element (including Nodal tris). Have also remvoed all new and double from 2D shapes in StdRegions
*
* Revision 1.27  2007/04/08 03:36:58  jfrazier
* Updated to use SharedArray consistently and minor reformatting.
*
* Revision 1.26  2007/04/05 15:20:11  sherwin
* Updated 2D stuff to comply with SharedArray philosophy
*
* Revision 1.25  2007/04/04 20:48:17  sherwin
* Update to handle SharedArrays
*
* Revision 1.24  2007/03/29 19:35:09  bnelson
* Replaced boost::shared_array with SharedArray
*
* Revision 1.23  2007/03/25 15:48:22  sherwin
* UPdate LocalRegions to take new NekDouble and shared_array formats. Added new Demos
*
* Revision 1.22  2007/03/21 20:56:43  sherwin
* Update to change BasisSharedVector to boost::shared_array<BasisSharedPtr> and removed tthe Vector definitions in GetCoords and PhysDeriv
*
* Revision 1.21  2007/03/20 16:58:43  sherwin
* Update to use Array<OneD, NekDouble> storage and NekDouble usage, compiling and executing up to Demos/StdRegions/Project1D
*
* Revision 1.20  2007/03/14 21:24:09  sherwin
* Update for working version of MultiRegions up to ExpList1D
*
* Revision 1.19  2007/02/24 09:07:25  sherwin
* Working version of stdMatrixManager and stdLinSysMatrix
*
* Revision 1.18  2007/02/23 19:26:08  jfrazier
* General bug fix and formatting.
*
* Revision 1.17  2007/02/22 22:02:28  sherwin
* Update with executing StdMatManager
*
* Revision 1.16  2007/02/22 18:11:32  sherwin
* Version with some create functions introduced for StdMatManagers
*
* Revision 1.15  2007/02/21 22:55:16  sherwin
* First integration of StdMatrixManagers
*
* Revision 1.14  2007/02/17 03:40:21  jfrazier
* Couple changes to reflect additions and corrections to reflect linear algebra calls.
*
* Revision 1.13  2007/02/13 09:52:28  sherwin
* Updates to fix mass matrix inverse issues
*
* Revision 1.12  2007/02/12 17:00:20  sherwin
* Modifcations to make a working version of Project1D
*
* Revision 1.11  2007/02/07 12:51:53  sherwin
* Compiling version of Project1D
*
* Revision 1.10  2007/01/28 18:34:24  sherwin
* More modifications to make Demo Project1D compile
*
* Revision 1.9  2007/01/23 23:20:21  sherwin
* New version after Jan 07 update
*
* Revision 1.8  2007/01/20 22:35:21  sherwin
* Version with StdExpansion compiling
*
* Revision 1.7  2007/01/15 15:07:20  pvos
* updating doxygen documentation
*
* Revision 1.6  2006/12/10 19:00:54  sherwin
* Modifications to handle nodal expansions
*
* Revision 1.5  2006/08/16 23:34:42  jfrazier
* *** empty log message ***
*
* Revision 1.4  2006/08/05 19:03:48  sherwin
* Update to make the multiregions 2D expansion in connected regions work
*
* Revision 1.3  2006/06/06 15:25:21  jfrazier
* Removed unreferenced variables and replaced ASSERTL0(false, ....) with
* NEKERROR.
*
* Revision 1.2  2006/06/01 13:43:20  kirby
* *** empty log message ***
*
* Revision 1.1  2006/05/04 18:58:33  kirby
* *** empty log message ***
*
* Revision 1.52  2006/04/01 21:59:27  sherwin
* Sorted new definition of ASSERT
*
* Revision 1.51  2006/03/21 09:21:32  sherwin
* Introduced NekMemoryManager
*
* Revision 1.50  2006/03/05 22:11:03  sherwin
*
* Sorted out Project1D, Project2D and Project_Diff2D as well as some test scripts
*
* Revision 1.49  2006/03/01 08:25:04  sherwin
*
* First compiling version of StdRegions
*
* Revision 1.48  2006/02/26 23:37:30  sherwin
*
* Updates and compiling checks upto StdExpansions1D
*
**/ 




