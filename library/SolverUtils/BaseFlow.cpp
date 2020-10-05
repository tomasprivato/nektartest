#include <SolverUtils/BaseFlow.h>
#include <StdRegions/StdSegExp.h>

using namespace std;

namespace Nektar
{

void BaseFlow::GetFldBase(LibUtilities::SessionReaderSharedPtr         pSession,
                                     Array<OneD, MultiRegions::ExpListSharedPtr>  pFields)
    
{

    m_session            = pSession;
    m_spacedim           = pFields[0]->GetGraph()->GetSpaceDimension();

    //Setting parameters for homogeneous problems
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
        {   m_session->LoadParameter("HomModesZ", m_npointsZ);
        }

        if((HomoStr == "HOMOGENEOUS3D")||(HomoStr == "Homogeneous3D")||
           (HomoStr == "3D")||(HomoStr == "Homo3D"))
        {
            m_session->LoadParameter("HomModesZ",m_npointsZ);
        }

        if(m_session->DefinesSolverInfo("USEFFT"))
        {
            m_useFFT = true;
        }
    }
    else
    {
        m_npointsZ = 1; // set to default value so can use to identify 2d or 3D (homogeneous) expansions
    }
    

    int nvar = pSession->GetVariables().size();
    m_baseflow = Array<OneD, Array<OneD, NekDouble> >(nvar);
    for (int i = 0; i < nvar; ++i)
    {
        m_baseflow[i] = Array<OneD, NekDouble>(pFields[i]->GetTotPoints(), 0.0);

    }

    ASSERTL0(pSession->DefinesFunction("BaseFlow"),
             "Base flow must be defined for linearised forms.");
    string file = pSession->GetFunctionFilename("BaseFlow", 0);


    //Periodic base flows
    if(pSession->DefinesParameter("N_slices"))
    {
        pSession->LoadParameter("N_slices",m_slices);
        if(m_slices>1)
        {
            ASSERTL0(pSession->GetFunctionType("BaseFlow", 0)
                == LibUtilities::eFunctionTypeFile,
                "Base flow should be a sequence of files.");
            DFT(file,pFields,m_slices);
        }
        else
        {
            ASSERTL0(false, "Number of slices must be a positive number "
                            "greater than 1");
        }
    }
    //Steady base-flow
    else
    {
        m_slices=1;

        //BaseFlow from file
        if (pSession->GetFunctionType("BaseFlow", pSession->GetVariable(0))
            == LibUtilities::eFunctionTypeFile)
        {
            ImportFldBase(file,pFields,1);

        }
        //analytic base flow
        else
        {
            int nq = pFields[0]->GetNpoints();
            Array<OneD,NekDouble> x0(nq);
            Array<OneD,NekDouble> x1(nq);
            Array<OneD,NekDouble> x2(nq);

            // get the coordinates (assuming all fields have the same
            // discretisation)
            pFields[0]->GetCoords(x0,x1,x2);

            for(unsigned int i = 0 ; i < pFields.size(); i++)
            {
                LibUtilities::EquationSharedPtr ifunc
                    = pSession->GetFunction("BaseFlow", i);

                ifunc->Evaluate(x0,x1,x2,m_baseflow[i]);
            }
        }
    }


    if(pSession->DefinesParameter("period"))
    {
        m_period=pSession->GetParameter("period");
    }
    else
    {
        m_period=(pSession->GetParameter("TimeStep")*m_slices)/(m_slices-1.);
    }


}

void BaseFlow::GetBaseGrad(LibUtilities::SessionReaderSharedPtr         pSession,
                                      Array<OneD, MultiRegions::ExpListSharedPtr>  pFields)
    
{

    int nvar = pSession->GetVariables().size();
    
    int nBaseDerivs = (m_halfMode || m_singleMode) ? 2 : m_spacedim;
    m_gradBase = Array<OneD, Array<OneD, NekDouble> >(nvar*nBaseDerivs);
    for (int i = 0; i < nvar; ++i)
    {
        for (int j = 0; j < nBaseDerivs; ++j)
        {
            m_gradBase[i*nBaseDerivs + j ] = Array<OneD, NekDouble>
                                            (pFields[i]->GetTotPoints(), 0.0);
        }
    }

    UpdateGradBase(pFields);


}





/**
 * Import field from infile and load into \a m_fields. This routine will
 * also perform a \a BwdTrans to ensure data is in both the physical and
 * coefficient storage.
 * @param   pInFile          Filename to read.
 * @param   pFields          Array of expansion lists
 */
void BaseFlow::ImportFldBase(
        std::string                                  pInfile,
        Array<OneD, MultiRegions::ExpListSharedPtr> &pFields,
        int                                          pSlice)
{
    std::vector<LibUtilities::FieldDefinitionsSharedPtr> FieldDef;
    std::vector<std::vector<NekDouble> >                 FieldData;

    int nqtot = m_baseflow[0].size();
    Array<OneD, NekDouble> tmp_coeff(pFields[0]->GetNcoeffs(), 0.0);

    cout << "nqtot " << nqtot << "\n";
    cout << "getNcoeffs " << pFields[0]->GetNcoeffs() << "\n";

    int numexp = pFields[0]->GetExpSize();
    cout << "numexp " << numexp << "\n";
    Array<OneD,int> ElementGIDs(numexp);

    // Define list of global element ids
    for(int i = 0; i < numexp; ++i)
    {
        ElementGIDs[i] = pFields[0]->GetExp(i)->GetGeom()->GetGlobalID();

        cout << "elementgid " << ElementGIDs[i] << "\n";
    }

    //Get Homogeneous
    LibUtilities::FieldIOSharedPtr fld = LibUtilities::FieldIO::CreateForFile(
        m_session, pInfile);
    fld->Import(pInfile, FieldDef, FieldData,
                LibUtilities::NullFieldMetaDataMap,
                ElementGIDs);


    int nSessionVar     = m_session->GetVariables().size();
    int nSessionConvVar = nSessionVar - 1;
    int nFileVar        = FieldDef[0]->m_fields.size();
    int nFileConvVar    = nFileVar - 1; // Ignore pressure


    if (m_halfMode)
    {
        ASSERTL0(nFileVar == 3, "For half mode, expect 2D2C base flow.");
        nFileConvVar = 2;
    }

    for(int j = 0; j < nFileConvVar; ++j)
    {
        for(int i = 0; i < FieldDef.size(); ++i)
        {
            bool flag = FieldDef[i]->m_fields[j] ==
                m_session->GetVariable(j);

            ASSERTL0(flag, (std::string("Order of ") + pInfile
                            + std::string(" data and that defined in "
                            "the session file differs")).c_str());

            pFields[j]->ExtractDataToCoeffs(
                                FieldDef[i],
                                FieldData[i],
                                FieldDef[i]->m_fields[j],
                                tmp_coeff);
        
        }
        
        

        if(m_singleMode || m_halfMode)
        {
            pFields[j]->GetPlane(0)->BwdTrans(tmp_coeff, m_baseflow[j]);

            if(m_singleMode)
            {
                //copy the bwd trans into the second plane for single
                //Mode Analysis
                int ncplane=(pFields[0]->GetNpoints())/m_npointsZ;
                Vmath::Vcopy(ncplane,&m_baseflow[j][0],1,&m_baseflow[j][ncplane],1);
            }
        }
        else // fully 3D base flow - put in physical space.
        {

            bool oldwavespace = pFields[j]->GetWaveSpace();
            pFields[j]->SetWaveSpace(false);
            pFields[j]->BwdTrans(tmp_coeff, m_baseflow[j]);
            pFields[j]->SetWaveSpace(oldwavespace);
        }
    }

    // Zero unused fields (e.g. w in a 2D2C base flow).
    for (int j = nFileConvVar; j < nSessionConvVar; ++j)
    {
        Vmath::Fill(nqtot, 0.0, m_baseflow[j], 1);
    }

    // If time-periodic, put loaded data into the slice storage.
    if(m_session->DefinesParameter("N_slices"))
    {
        for(int i = 0; i < nSessionConvVar; ++i)
        {
            Vmath::Vcopy(nqtot, &m_baseflow[i][0], 1, &m_interp[i][pSlice*nqtot], 1);
        }
    }
}

void BaseFlow::UpdateBase(const NekDouble m_time)
{
    int ndim    = m_baseflow.size();
    int npoints = m_baseflow[0].size();

    // Evaluation of the base flow for periodic cases
    if (m_slices > 1)
    {

        NekDouble BetaT = 2 * M_PI * fmod(m_time, m_period) / m_period;
        NekDouble phase;
        for (int j = 0; j < ndim; ++j)
        {
            
            Vmath::Vcopy(npoints, &m_interp[j][0], 1, &m_baseflow[j][0], 1);
            Vmath::Svtvp(npoints, cos(0.5 * m_slices * BetaT),
                         &m_interp[j][npoints], 1, &m_baseflow[j][0], 1, &m_baseflow[j][0],
                         1);

            for (int i = 2; i < m_slices; i += 2)
            {
                phase = (i >> 1) * BetaT;

                Vmath::Svtvp(npoints, cos(phase), &m_interp[j][i * npoints], 1,
                             &m_baseflow[j][0], 1, &m_baseflow[j][0], 1);
                Vmath::Svtvp(npoints, -sin(phase), &m_interp[j][(i + 1) * npoints],
                             1, &m_baseflow[j][0], 1, &m_baseflow[j][0], 1);
            }
        }
    }
}

void BaseFlow::UpdateGradBase(
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields)
{

    int ndim    = m_baseflow.size();

    for (int j = 0; j < ndim; ++j) 
    {

      int nBaseDerivs = (m_halfMode || m_singleMode) ? 2 : m_spacedim;
    switch(m_spacedim)
    {
        case 1:         // 1D
        {
            fields[j]->PhysDeriv(m_baseflow[j], m_gradBase[j*nBaseDerivs + 0]);
        }
        break;
        case 2:  //2D
        {
            fields[j]->PhysDeriv(m_baseflow[j], m_gradBase[j*nBaseDerivs + 0],
                                              m_gradBase[j*nBaseDerivs + 1]);
        }
        break;
        case 3:
        {
            if(m_halfMode) // can assume W = 0 and  d/dz == 0
            {
                if( j < 2)
                {
                    fields[j]->PhysDeriv(m_baseflow[j],
                                              m_gradBase[j*nBaseDerivs + 0],
                                              m_gradBase[j*nBaseDerivs + 1]);
                }
            }
            else if(m_singleMode) // single mode where d/dz = 0
            {
                fields[j]->PhysDeriv(m_baseflow[j], m_gradBase[j*nBaseDerivs + 0],
                                                  m_gradBase[j*nBaseDerivs + 1]);
            }
            else
            {
                // Differentiate base flow in physical space
                bool oldwavespace = fields[j]->GetWaveSpace();
                fields[j]->SetWaveSpace(false);
                fields[j]->PhysDeriv(m_baseflow[j], m_gradBase[j*nBaseDerivs + 0],
                                                  m_gradBase[j*nBaseDerivs + 1],
                                                  m_gradBase[j*nBaseDerivs + 2]);
                fields[j]->SetWaveSpace(oldwavespace);
            }
        }
        break;
    }


    }


    




}

DNekBlkMatSharedPtr BaseFlow::GetFloquetBlockMatrix() const
{
    DNekMatSharedPtr    loc_mat;
    DNekBlkMatSharedPtr BlkMatrix;
    int n_exp = 0;

    n_exp = m_baseflow[0].size(); // will operatore on m_phys

    Array<OneD,unsigned int> nrows(n_exp);
    Array<OneD,unsigned int> ncols(n_exp);

    nrows = Array<OneD, unsigned int>(n_exp,m_slices);
    ncols = Array<OneD, unsigned int>(n_exp,m_slices);

    MatrixStorage blkmatStorage = eDIAGONAL;
    BlkMatrix = MemoryManager<DNekBlkMat>
        ::AllocateSharedPtr(nrows,ncols,blkmatStorage);


    const LibUtilities::PointsKey Pkey(m_slices,LibUtilities::eFourierEvenlySpaced);
    const LibUtilities::BasisKey  BK(LibUtilities::eFourier,m_slices,Pkey);
    StdRegions::StdSegExp StdSeg(BK);

    StdRegions::StdMatrixKey matkey(StdRegions::eFwdTrans,
                                    StdSeg.DetShapeType(),
                                    StdSeg);

    loc_mat = StdSeg.GetStdMatrix(matkey);

    // set up array of block matrices.
    for(int i = 0; i < n_exp; ++i)
    {
        BlkMatrix->SetBlock(i,i,loc_mat);
    }

    return BlkMatrix;
}

//Discrete Fourier Transform for Floquet analysis
void BaseFlow::DFT(const string file,
        Array<OneD, MultiRegions::ExpListSharedPtr>& pFields,
        const NekDouble m_slices)
{
    int ConvectedFields = m_baseflow.size()-1;
    int npoints         = m_baseflow[0].size();
    m_interp            = Array<OneD, Array<OneD, NekDouble> > (ConvectedFields);

    for (int i = 0; i < ConvectedFields; ++i)
    {
        m_interp[i] = Array<OneD,NekDouble>(npoints*m_slices, 0.0);
    }

    // Import the slides into auxiliary vector
    // The base flow should be stored in the form "filename_%d.ext"
    // A subdirectory can also be included, such as "dir/filename_%d.ext"
    size_t found = file.find("%d");
    ASSERTL0(found != string::npos && file.find("%d", found+1) == string::npos,
             "Since N_slices is specified, the filename provided for function "
             "'BaseFlow' must include exactly one instance of the format "
             "specifier '%d', to index the time-slices.");
    char* buffer = new char[file.length() + 8];
    for (int i = 0; i < m_slices; ++i)
    {
        sprintf(buffer, file.c_str(), i);
        ImportFldBase(buffer,pFields,i);
    }
    delete[] buffer;


    // Discrete Fourier Transform of the fields
    for(int k=0; k< ConvectedFields;++k)
    {
#ifdef NEKTAR_USING_FFTW

        //Discrete Fourier Transform using FFTW
        Array<OneD, NekDouble> fft_in(npoints*m_slices);
        Array<OneD, NekDouble> fft_out(npoints*m_slices);

        Array<OneD, NekDouble> m_tmpIN(m_slices);
        Array<OneD, NekDouble> m_tmpOUT(m_slices);

        //Shuffle the data
        for(int j= 0; j < m_slices; ++j)
        {
            Vmath::Vcopy(npoints,&m_interp[k][j*npoints],1,&(fft_in[j]),m_slices);
        }

        m_FFT = LibUtilities::GetNektarFFTFactory().CreateInstance("NekFFTW", m_slices);

        //FFT Transform
        for(int i=0; i<npoints; i++)
        {
            m_FFT->FFTFwdTrans(m_tmpIN =fft_in + i*m_slices, m_tmpOUT =fft_out + i*m_slices);

        }

        //Reshuffle data
        for(int s = 0; s < m_slices; ++s)
        {
            Vmath::Vcopy(npoints,&fft_out[s],m_slices,&m_interp[k][s*npoints],1);

        }

        Vmath::Zero(fft_in.size(),&fft_in[0],1);
        Vmath::Zero(fft_out.size(),&fft_out[0],1);
#else
        //Discrete Fourier Transform using MVM
        DNekBlkMatSharedPtr blkmat;
        blkmat = GetFloquetBlockMatrix();

        int nrows = blkmat->GetRows();
        int ncols = blkmat->GetColumns();

        Array<OneD, NekDouble> sortedinarray(ncols);
        Array<OneD, NekDouble> sortedoutarray(nrows);

        //Shuffle the data
        for(int j= 0; j < m_slices; ++j)
        {
            Vmath::Vcopy(npoints,&m_interp[k][j*npoints],1,&(sortedinarray[j]),m_slices);
        }

        // Create NekVectors from the given data arrays
        NekVector<NekDouble> in (ncols,sortedinarray,eWrapper);
        NekVector<NekDouble> out(nrows,sortedoutarray,eWrapper);

        // Perform matrix-vector multiply.
        out = (*blkmat)*in;

        //Reshuffle data
        for(int s = 0; s < m_slices; ++s)
        {
            Vmath::Vcopy(npoints,&sortedoutarray[s],m_slices,&m_interp[k][s*npoints],1);
        }

        for(int r=0; r<sortedinarray.size();++r)
        {
            sortedinarray[0]=0;
            sortedoutarray[0]=0;
        }

#endif
    }

}



} //end of namespace

