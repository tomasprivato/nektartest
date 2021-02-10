///////////////////////////////////////////////////////////////////////////////
//
// File LinearisedAdvection.cpp
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
// Description: Evaluation of the linearised advective term
//
///////////////////////////////////////////////////////////////////////////////

#include <IncNavierStokesSolver/AdvectionTerms/LinearisedAdvection.h>
#include <StdRegions/StdSegExp.h>

using namespace std;

namespace Nektar
{
string LinearisedAdvection::className
        = SolverUtils::GetAdvectionFactory().RegisterCreatorFunction(
                "Linearised",
                LinearisedAdvection::create);

/**
 * Constructor. Creates ...
 *
 * \param
 * \param
 */

LinearisedAdvection::LinearisedAdvection():
    Advection()
{
}


void LinearisedAdvection::v_InitObject(
        LibUtilities::SessionReaderSharedPtr        pSession,
        Array<OneD, MultiRegions::ExpListSharedPtr> pFields)
{
    Advection::v_InitObject(pSession, pFields);

    m_session            = pSession;
    m_boundaryConditions = MemoryManager<SpatialDomains::BoundaryConditions>
        ::AllocateSharedPtr(m_session, pFields[0]->GetGraph());
    m_spacedim           = pFields[0]->GetGraph()->GetSpaceDimension();
    m_expdim             = pFields[0]->GetGraph()->GetMeshDimension();

    //Setting parameters for homogeneous problems
    m_HomoDirec          = 0;
    m_HomogeneousType    = eNotHomogeneous;
    m_singleMode         = false;
    m_halfMode           = false;
    m_multipleModes      = false;

    if(m_session->DefinesSolverInfo("HOMOGENEOUS"))
    {
        std::string HomoStr = m_session->GetSolverInfo("HOMOGENEOUS");
        m_spacedim          = 3;

        if((HomoStr == "HOMOGENEOUS1D")||(HomoStr == "Homogeneous1D")||
           (HomoStr == "1D")||(HomoStr == "Homo1D"))
        {
            m_HomogeneousType = eHomogeneous1D;
            m_LhomZ           = m_session->GetParameter("LZ");
            m_HomoDirec       = 1;

            ASSERTL0(m_session->DefinesSolverInfo("ModeType"),
                     "Need to specify ModeType as HalfMode,SingleMode or "
                     "MultipleModes");

            m_session->MatchSolverInfo("ModeType",      "SingleMode",
                                       m_singleMode,    false);
            m_session->MatchSolverInfo("ModeType",      "HalfMode",
                                       m_halfMode,      false);
            m_session->MatchSolverInfo("ModeType",      "MultipleModes",
                                       m_multipleModes, false);

            if(m_singleMode)
            {
                m_npointsZ = 2;
            }
            else if(m_halfMode)
            {
                m_npointsZ = 1;
            }
            else if(m_multipleModes)
            {
                m_npointsZ = m_session->GetParameter("HomModesZ");
            }
        }

        if((HomoStr == "HOMOGENEOUS2D")||(HomoStr == "Homogeneous2D")||
           (HomoStr == "2D")||(HomoStr == "Homo2D"))
        {
            m_HomogeneousType = eHomogeneous2D;
            m_session->LoadParameter("HomModesY", m_npointsY);
            m_session->LoadParameter("LY",        m_LhomY);
            m_session->LoadParameter("HomModesZ", m_npointsZ);
            m_session->LoadParameter("LZ",        m_LhomZ);
            m_HomoDirec       = 2;
        }

        if((HomoStr == "HOMOGENEOUS3D")||(HomoStr == "Homogeneous3D")||
           (HomoStr == "3D")||(HomoStr == "Homo3D"))
        {
            m_HomogeneousType = eHomogeneous3D;
            m_session->LoadParameter("HomModesX",m_npointsX);
            m_session->LoadParameter("LX",       m_LhomX   );
            m_session->LoadParameter("HomModesY",m_npointsY);
            m_session->LoadParameter("LY",       m_LhomY   );
            m_session->LoadParameter("HomModesZ",m_npointsZ);
            m_session->LoadParameter("LZ",       m_LhomZ   );
            m_HomoDirec       = 3;
        }


    }
    else
    {
        m_npointsZ = 1; // set to default value so can use to identify 2d or 3D (homogeneous) expansions
    }
    


    bf.GetFldBase(m_session,pFields,false,0.0);
    bf.GetBaseGrad(m_session,pFields);

}

void LinearisedAdvection::v_SetBaseFlow(
        const Array<OneD, Array<OneD, NekDouble> >        &inarray,
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields)
{
    if (m_session->GetSolverInfo("EqType") == "UnsteadyNavierStokes")
    {
        // The SFD method is only applied to the velocity variables in
        // incompressible
        ASSERTL1(inarray.size() == (bf.m_baseflow.size() - 1),
                 "Number of base flow variables does not match what is "
                 "expected.");
    }
    else
    {
        ASSERTL1(inarray.size() == (bf.m_baseflow.size()),
             "Number of base flow variables does not match what is expected.");
    }

    int npts = inarray[0].size();

    for (int i = 0; i < inarray.size(); ++i)
    {
        ASSERTL1(npts == bf.m_baseflow[i].size(),
             "Size of base flow array does not match expected.");
        Vmath::Vcopy(npts, inarray[i], 1, bf.m_baseflow[i], 1);
    }

    bf.UpdateGradBase(fields);
}


LinearisedAdvection::~LinearisedAdvection()
{
}


//Advection function

void LinearisedAdvection::v_Advect(
        const int nConvectiveFields,
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
        const Array<OneD, Array<OneD, NekDouble> >        &advVel,
        const Array<OneD, Array<OneD, NekDouble> >        &inarray,
        Array<OneD, Array<OneD, NekDouble> >              &outarray,
        const NekDouble                                   &time,
        const Array<OneD, Array<OneD, NekDouble> >        &pFwd,
        const Array<OneD, Array<OneD, NekDouble> >        &pBwd)
{
    ASSERTL1(nConvectiveFields == inarray.size(),
             "Number of convective fields and Inarray are not compatible");

    int nPointsTot  = fields[0]->GetNpoints();
    int ndim        = advVel.size();
    int nBaseDerivs = (m_halfMode || m_singleMode) ? 2 : m_spacedim;
    int nDerivs     = (m_halfMode) ? 2 : m_spacedim;

    Array<OneD, Array<OneD, NekDouble> > velocity(ndim);
    for(int i = 0; i < ndim; ++i)
    {
        if(fields[i]->GetWaveSpace() && !m_singleMode && !m_halfMode)
        {
            velocity[i] = Array<OneD, NekDouble>(nPointsTot,0.0);
            fields[i]->HomogeneousBwdTrans(advVel[i],velocity[i]);
        }
        else
        {
            velocity[i] = advVel[i];
        }
    }

    Array<OneD, Array<OneD, NekDouble> > grad (nDerivs);
    for( int i = 0; i < nDerivs; ++i)
    {
        grad[i] = Array<OneD, NekDouble> (nPointsTot);
    }

    // Evaluation of the base flow for periodic cases
    //bf.UpdateBase(time);

    string file = bf.m_session->GetFunctionFilename("BaseFlow", 0);

    if (bf.m_slices > 1)
    {
        ASSERTL0(bf.m_session->GetFunctionType("BaseFlow", 0) ==
                     LibUtilities::eFunctionTypeFile,
                 "Base flow should be a sequence of files.");

        int step =
            fmod(time, bf.m_period) / bf.m_session->GetParameter("TimeStep");

        size_t found = file.find("%d");
        ASSERTL0(
            found != string::npos && file.find("%d", found + 1) == string::npos,
            "Since N_slices is specified, the filename provided for function "
            "'BaseFlow' must include exactly one instance of the format "
            "specifier '%d', to index the time-slices.");
        char *buffer = new char[file.length() + 8];

        sprintf(buffer, file.c_str(), step);


        cout << buffer << " linearisedadvection\n";

        bf.ImportFldBase(buffer, fields, 1);

        delete[] buffer;
        // DFT(file,pFields,m_slices);
    }

    bf.UpdateGradBase(fields);
    
    //Evaluate the linearised advection term
    for( int i = 0; i < nConvectiveFields; ++i)
    {
        // Calculate gradient
        switch(nDerivs)
        {
            case 1:
            {
                fields[i]->PhysDeriv(inarray[i], grad[0]);
            }
            break;
            case 2:
            {
                fields[i]->PhysDeriv(inarray[i], grad[0], grad[1]);
            }
            break;
            case 3:
            {
                fields[i]->PhysDeriv(inarray[i], grad[0], grad[1], grad[2]);
                if(m_multipleModes)
                {
                    // transform gradients into physical Fourier space
                    fields[i]->HomogeneousBwdTrans(grad[0], grad[0]);
                    fields[i]->HomogeneousBwdTrans(grad[1], grad[1]);
                    fields[i]->HomogeneousBwdTrans(grad[2], grad[2]);
                }
            }
            break;
        }

        // Calculate U_j du'_i/dx_j
        Vmath::Vmul(nPointsTot,grad[0], 1, bf.m_baseflow[0], 1, outarray[i], 1);
        for( int j = 1; j < nDerivs; ++j)
        {
            Vmath::Vvtvp(nPointsTot,grad[j], 1,
                                    bf.m_baseflow[j], 1,
                                    outarray[i], 1,
                                    outarray[i], 1);
        }

        // Add u'_j dU_i/dx_j
        int lim = (m_halfMode || m_singleMode) ? 2 : ndim;
        if (m_halfMode && i==2)
        {
            lim = 0;
        }
        for( int j = 0; j < lim; ++j)
        {
            Vmath::Vvtvp(nPointsTot,bf.m_gradBase[i*nBaseDerivs + j], 1,
                                    velocity[j], 1,
                                    outarray[i], 1,
                                    outarray[i], 1);
        }

        if(m_multipleModes)
        {
            fields[i]->HomogeneousFwdTrans(outarray[i],outarray[i]);
        }
        Vmath::Neg(nPointsTot,outarray[i],1);
    }
}


} //end of namespace

