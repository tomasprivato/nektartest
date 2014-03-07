////////////////////////////////////////////////////////////////////////////////
//
//  File: Field.hpp
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
//  Description: Field converter module base classes.
//
////////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>

#include <LibUtilities/BasicUtils/NekFactory.hpp>
#include <LibUtilities/BasicUtils/SharedArray.hpp>
#include <LibUtilities/BasicUtils/SessionReader.h>
#include <SpatialDomains/MeshGraph.h>

#include <MultiRegions/ExpList.h>
#include <MultiRegions/ContField1D.h>
#include <MultiRegions/ExpList2DHomogeneous1D.h>
#include <MultiRegions/ContField3DHomogeneous1D.h>
#include <MultiRegions/ContField3DHomogeneous2D.h>
#include <MultiRegions/ContField2D.h>
#include <MultiRegions/ContField3D.h>

#include <MultiRegions/DisContField1D.h>
#include <MultiRegions/DisContField3DHomogeneous1D.h>
#include <MultiRegions/DisContField3DHomogeneous2D.h>
#include <MultiRegions/DisContField2D.h>
#include <MultiRegions/DisContField3D.h>


using namespace std;

namespace Nektar
{
    namespace Utilities
    {
        struct Field {
            Field() : m_verbose(false),m_declareExpansionAsContField(false),
                      m_declareExpansionAsDisContField(false),
                      m_writeBndFld(false){}
            
            bool m_verbose;
            vector<LibUtilities::FieldDefinitionsSharedPtr> m_fielddef;
            vector<vector<double> > m_data;
            vector<MultiRegions::ExpListSharedPtr> m_exp;

            bool m_declareExpansionAsContField;
            bool m_declareExpansionAsDisContField;
            
            LibUtilities::CommSharedPtr          m_comm;
            LibUtilities::SessionReaderSharedPtr m_session;
            SpatialDomains::MeshGraphSharedPtr   m_graph;
            LibUtilities::FieldIOSharedPtr       m_fld;
            map<string, vector<string> >         m_inputfiles;

            bool                 m_writeBndFld; 
            vector<unsigned int> m_bndRegionsToWrite;
            bool                 m_fldToBnd; 

            
            MultiRegions::ExpListSharedPtr SetUpFirstExpList(int NumHomogeneousDir,
                                                             bool fldfilegiven = false)
            {
                
                MultiRegions::ExpListSharedPtr exp;

                // Set up expansion list
                int expdim  = m_graph->GetMeshDimension();
                
                bool useFFT     = false;
                bool dealiasing = false;
                
                switch (expdim)
                {
                case 1:
                    {
                        ASSERTL0(NumHomogeneousDir <= 2,
                                 "Quasi-3D approach is only set up for 1 or 2 "
                                 "homogeneous directions");
                        
                        if (NumHomogeneousDir == 1)
                        {
                            MultiRegions::ExpList2DHomogeneous1DSharedPtr Exp2DH1;
                            
                            // Define Homogeneous expansion
                            int nplanes;
                            NekDouble ly;
                            LibUtilities::BasisType btype;
                            
                            if(fldfilegiven)
                            {
                                nplanes = m_fielddef[0]->m_numModes[1];
                                ly      = m_fielddef[0]->m_homogeneousLengths[0];
                                btype   = m_fielddef[0]->m_basis[1];
                            }
                            else
                            {
                                m_session->LoadParameter("HomModesZ", nplanes);
                                m_session->LoadParameter("LY",ly);
                                btype = LibUtilities::eFourier;
                            }
                            
                            // Choose points to be at evenly spaced points at
                            // nplanes points
                            const LibUtilities::PointsKey 
                                Pkey(nplanes, LibUtilities::ePolyEvenlySpaced);
                            
                            const LibUtilities::BasisKey Bkey(btype, nplanes, Pkey);
                            
                            
                            
                            if(m_declareExpansionAsContField||
                               m_declareExpansionAsDisContField)
                            {
                                ASSERTL0(false,"ContField2DHomogeneous1D or "
                                         "DisContField2DHomogenenous1D has "
                                         "not been implemented");
                            }
                            
                            Exp2DH1 = MemoryManager<MultiRegions::
                                ExpList2DHomogeneous1D>::
                                AllocateSharedPtr(m_session, Bkey, ly, 
                                                  useFFT,  dealiasing, 
                                                  m_graph);
                            exp = Exp2DH1;
                        }
                        else if (NumHomogeneousDir == 2)
                        {
                            MultiRegions::ExpList3DHomogeneous2DSharedPtr Exp3DH2;
                            
                            int nylines,nzlines;
                            NekDouble ly,lz;
                            LibUtilities::BasisType btype1,btype2;
                            
                            if(fldfilegiven)
                            {
                                nylines = m_fielddef[0]->m_numModes[1];
                                nzlines = m_fielddef[0]->m_numModes[2];
                                ly      = m_fielddef[0]->m_homogeneousLengths[0];
                                lz      = m_fielddef[0]->m_homogeneousLengths[1];
                                btype1  = m_fielddef[0]->m_basis[1];
                                btype2  = m_fielddef[0]->m_basis[2];
                            }
                            else
                            {
                                m_session->LoadParameter("HomModesY", nylines);
                                m_session->LoadParameter("HomModesZ", nzlines);
                                m_session->LoadParameter("LY",ly);
                                m_session->LoadParameter("LZ",lz);
                                btype1 = LibUtilities::eFourier;
                                btype2 = LibUtilities::eFourier;
                            }
                            
                            // Choose points to be at evenly spaced points at
                            // nplanes points
                            const LibUtilities::PointsKey 
                                PkeyY(nylines, LibUtilities::ePolyEvenlySpaced);
                            const LibUtilities::BasisKey BkeyY(btype1, nylines, PkeyY);
                            
                            const LibUtilities::PointsKey 
                                PkeyZ(nzlines, LibUtilities::ePolyEvenlySpaced);
                            const LibUtilities::BasisKey BkeyZ(btype2, nzlines, PkeyZ);
                            
                            if(m_declareExpansionAsContField)
                            {
                                Exp3DH2 = MemoryManager<MultiRegions::
                                    ContField3DHomogeneous2D>::
                                    AllocateSharedPtr(m_session, BkeyY, BkeyZ, 
                                                      ly, lz, useFFT, dealiasing, 
                                                      m_graph,
                                                      m_session->GetVariable(0));
                            }
                            else if(m_declareExpansionAsContField)
                            {
                                Exp3DH2 = MemoryManager<MultiRegions::
                                    DisContField3DHomogeneous2D>::
                                    AllocateSharedPtr(m_session, BkeyY, BkeyZ, 
                                                      ly, lz, useFFT, dealiasing, 
                                                      m_graph,
                                                      m_session->GetVariable(0));
                            }
                            else
                            {
                                Exp3DH2 = MemoryManager<MultiRegions::
                                    ExpList3DHomogeneous2D>::
                                    AllocateSharedPtr(m_session, BkeyY, BkeyZ, 
                                                      ly, lz, useFFT, dealiasing, 
                                                      m_graph);
                            }
                            
                            exp = Exp3DH2;
                        }
                        else
                        {
                            MultiRegions::ExpList1DSharedPtr Exp1D;
                            
                            if(m_declareExpansionAsContField)
                            {
                                Exp1D = MemoryManager<MultiRegions::ContField1D>
                                    ::AllocateSharedPtr(m_session, m_graph,
                                                        m_session->GetVariable(0));
                            }
                            else if(m_declareExpansionAsContField)
                            {
                                Exp1D = MemoryManager<MultiRegions::DisContField1D>
                                    ::AllocateSharedPtr(m_session, m_graph,
                                                        m_session->GetVariable(0));
                            }
                            else 
                            {
                                Exp1D = MemoryManager<MultiRegions::ExpList1D>
                                    ::AllocateSharedPtr(m_session, m_graph);
                            }
                            
                            exp = Exp1D;
                        }
                    }
                    break;
                case 2:
                    {
                        ASSERTL0(NumHomogeneousDir <= 1, 
                                 "NumHomogeneousDir is only set up for 1");
                        
                        if (NumHomogeneousDir == 1)
                        {
                            MultiRegions::ExpList3DHomogeneous1DSharedPtr Exp3DH1;
                            
                            // Define Homogeneous expansion
                            int nplanes;
                            NekDouble lz;
                            LibUtilities::BasisType btype;
                            
                            if(fldfilegiven)
                            {
                                nplanes =  m_fielddef[0]->m_numModes[2];
                                lz      = m_fielddef[0]->m_homogeneousLengths[0];
                                btype   = m_fielddef[0]->m_basis[1];
                            }
                            else
                            {
                                m_session->LoadParameter("HomModesZ", nplanes);
                                m_session->LoadParameter("LZ",lz);
                                btype = LibUtilities::eFourier;
                            }
                            
                            // Choose points to be at evenly spaced points at
                            // nplanes points
                            const LibUtilities::PointsKey 
                                Pkey(nplanes, LibUtilities::ePolyEvenlySpaced);
                            
                            const LibUtilities::BasisKey  Bkey(btype, nplanes, Pkey);
                            
                            if(m_declareExpansionAsContField)
                            {
                                Exp3DH1 = MemoryManager<MultiRegions::
                                    ContField3DHomogeneous1D>::
                                    AllocateSharedPtr(m_session, Bkey, lz, useFFT, 
                                                      dealiasing, m_graph,
                                                      m_session->GetVariable(0));
                            }
                            else if (m_declareExpansionAsContField)
                            {
                                Exp3DH1 = MemoryManager<MultiRegions::
                                    DisContField3DHomogeneous1D>::
                                    AllocateSharedPtr(m_session,
                                                      Bkey, lz, useFFT, 
                                                      dealiasing, m_graph,
                                                      m_session->GetVariable(0));
                            }
                            else
                            {
                                Exp3DH1 = MemoryManager<MultiRegions::
                                    ExpList3DHomogeneous1D>::
                                    AllocateSharedPtr(m_session, Bkey, lz, useFFT, 
                                                      dealiasing, m_graph);
                            }
                            exp = Exp3DH1;
                        }
                        else
                        {
                            MultiRegions::ExpList2DSharedPtr Exp2D;
                            
                            if(m_declareExpansionAsContField)
                            {
                                Exp2D = MemoryManager<MultiRegions::ContField2D>
                                    ::AllocateSharedPtr(m_session,m_graph,
                                                        m_session->GetVariable(0));
                            }
                            else if(m_declareExpansionAsDisContField)
                            {
                                Exp2D = MemoryManager<MultiRegions::DisContField2D>
                                    ::AllocateSharedPtr(m_session,m_graph,
                                                        m_session->GetVariable(0));
                            }
                            else
                            {
                                Exp2D = MemoryManager<MultiRegions::ExpList2D>
                                    ::AllocateSharedPtr(m_session,m_graph);
                            }

                            exp = Exp2D;
                        }
                    }
                    break;
                case 3:
                    {
                        MultiRegions::ExpList3DSharedPtr Exp3D;
                        
                        if(m_declareExpansionAsContField)
                        {
                            Exp3D = MemoryManager<MultiRegions::ContField3D>
                                ::AllocateSharedPtr(m_session,m_graph,
                                                    m_session->GetVariable(0));
                        }
                        else if(m_declareExpansionAsDisContField)
                        {
                            Exp3D = MemoryManager<MultiRegions::DisContField3D>
                            ::AllocateSharedPtr(m_session,m_graph,
                                                m_session->GetVariable(0));
                        }
                        else
                        {
                            Exp3D = MemoryManager<MultiRegions::ExpList3D>
                                ::AllocateSharedPtr(m_session, m_graph);
                        }
                        
                        exp = Exp3D;
                    }
                    break;
                default:
                    ASSERTL0(false, "Expansion dimension not recognised");
                    break;
                }
                
                return exp;
            };
            
            MultiRegions::ExpListSharedPtr AppendExpList(string var = "DefaultVar", 
                                                         bool NewField = false)
            {
                MultiRegions::ExpListSharedPtr tmp;
                switch (m_graph->GetMeshDimension())
                {
                case 1:
                    {
                        if (m_fielddef[0]->m_numHomogeneousDir == 1)
                        {
                            if(m_declareExpansionAsContField||
                               m_declareExpansionAsDisContField)
                            {
                                ASSERTL0(false,"ContField2DHomogeneous1D or DisContField2DHomogenenous1D has not been implemented");
                            }
                            
                            MultiRegions::ExpList2DHomogeneous1DSharedPtr tmp2 =
                                boost::dynamic_pointer_cast<MultiRegions::
                                ExpList2DHomogeneous1D>(m_exp[0]);
                            
                            tmp = MemoryManager<MultiRegions::
                                ExpList2DHomogeneous1D>::
                                AllocateSharedPtr(*tmp2);
                            
                        }
                        else if (m_fielddef[0]->m_numHomogeneousDir == 2)
                        {
                            if(m_declareExpansionAsContField)
                            {
                                MultiRegions::ContField3DHomogeneous2DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ContField3DHomogeneous2D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    ContField3DHomogeneous2D>::
                                    AllocateSharedPtr(*tmp2);
                            }
                            else  if(m_declareExpansionAsContField)
                            {
                                MultiRegions::DisContField3DHomogeneous2DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    DisContField3DHomogeneous2D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    DisContField3DHomogeneous2D>::
                                    AllocateSharedPtr(*tmp2);
                            }
                            else 
                            {
                                MultiRegions::ExpList3DHomogeneous2DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ExpList3DHomogeneous2D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    ExpList3DHomogeneous2D>::
                                    AllocateSharedPtr(*tmp2);
                            }

                            
                        }
                        else
                        {
                            if(m_declareExpansionAsContField)
                            {
                                MultiRegions::ContField1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ContField1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::ContField1D>::
                                    AllocateSharedPtr(m_session,m_graph,var);
                            }
                            else if(m_declareExpansionAsDisContField)
                            {
                                MultiRegions::DisContField1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    DisContField1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::DisContField1D>::
                                    AllocateSharedPtr(m_session,m_graph,var);
                            }
                            else
                            {
                                MultiRegions::ExpList1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ExpList1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::ExpList1D>::
                                    AllocateSharedPtr(*tmp2);
                            }

                        }
                    }
                    break;
                case 2:
                    {   
                        if (m_fielddef[0]->m_numHomogeneousDir == 1)
                        {                            
                            if(m_declareExpansionAsContField)
                            {
                                MultiRegions::ContField3DHomogeneous1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ContField3DHomogeneous1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    ContField3DHomogeneous1D>::
                                    AllocateSharedPtr(*tmp2);

                                //WARNINGL0(false,"ContField is not copying BCs");
                            }
                            else  if(m_declareExpansionAsDisContField)
                            {
                                MultiRegions::DisContField3DHomogeneous1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    DisContField3DHomogeneous1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    DisContField3DHomogeneous1D>::
                                    AllocateSharedPtr(*tmp2);
                                //  WARNINGL0(false,"DisContField is not copying BCs");
                            }
                            else  
                            {
                                MultiRegions::ExpList3DHomogeneous1DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ExpList3DHomogeneous1D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::
                                    ExpList3DHomogeneous1D>::
                                    AllocateSharedPtr(*tmp2);
                            }

                        }
                        else
                        {
                            if(m_declareExpansionAsContField)
                            {
                                if(NewField)
                                {
                                    tmp = MemoryManager<MultiRegions::ContField2D>::
                                        AllocateSharedPtr(m_session,m_graph,var);
                                }
                                else // call copy constructor
                                {
                                    
                                    MultiRegions::ContField2DSharedPtr tmp2 =
                                        boost::dynamic_pointer_cast<MultiRegions::
                                        ContField2D>(m_exp[0]);
                                    
                                    tmp = MemoryManager<MultiRegions::ContField2D>::
                                        AllocateSharedPtr(*tmp2,m_graph,var);
                                }
                            }
                            else if(m_declareExpansionAsDisContField)
                            {
                                if(NewField)
                                {
                                    tmp = MemoryManager<MultiRegions::DisContField2D>::
                                        AllocateSharedPtr(m_session,m_graph,var);
                                }
                                else // call copy constructor
                                {
                                    MultiRegions::DisContField2DSharedPtr tmp2 =
                                        boost::dynamic_pointer_cast<MultiRegions::
                                        DisContField2D>(m_exp[0]);
                                    
                                    tmp = MemoryManager<MultiRegions::DisContField2D>::
                                        AllocateSharedPtr(*tmp2,m_graph,var);
                                }
                            }
                            else
                            {
                                MultiRegions::ExpList2DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ExpList2D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::ExpList2D>::
                                    AllocateSharedPtr(*tmp2);
                            }       
                        }
                    }
                    break;
                case 3:
                    {
                        if(m_declareExpansionAsContField)
                        {
                            if(NewField)
                            {
                                tmp = MemoryManager<MultiRegions::ContField3D>::
                                    AllocateSharedPtr(m_session,m_graph,var);
                            }
                            else
                            {
                                MultiRegions::ContField3DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    ContField3D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::ContField3D>::
                                    AllocateSharedPtr(*tmp2,m_graph,var);
                            }
                        }
                        else if(m_declareExpansionAsDisContField)
                        {
                            if(NewField)
                            {
                                tmp = MemoryManager<MultiRegions::DisContField3D>::
                                    AllocateSharedPtr(m_session,m_graph,var);
                            }
                            else
                            {
                                MultiRegions::DisContField3DSharedPtr tmp2 =
                                    boost::dynamic_pointer_cast<MultiRegions::
                                    DisContField3D>(m_exp[0]);
                                
                                tmp = MemoryManager<MultiRegions::DisContField3D>::
                                    AllocateSharedPtr(*tmp2,m_graph,var);
                            }
                        }
                        else
                        {
                            MultiRegions::ExpList3DSharedPtr tmp2 =
                                boost::dynamic_pointer_cast<MultiRegions::
                                ExpList3D>(m_exp[0]);
                            
                            tmp = MemoryManager<MultiRegions::ExpList3D>::
                                AllocateSharedPtr(*tmp2);
                        }
                    }
                    break;
                default:
                    ASSERTL0(false, "Expansion dimension not recognised");
                    break;
                }
                
                return tmp;
            }
            
        };

        typedef boost::shared_ptr<Field> FieldSharedPtr;
    }
}

