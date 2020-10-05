///////////////////////////////////////////////////////////////////////////////
//
// File LinearisedAdvection.h
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
// Description: TBA
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_LINEARISEDADVECTION_H
#define NEKTAR_SOLVERS_LINEARISEDADVECTION_H

#include <SolverUtils/Advection/Advection.h>
#include <SolverUtils/BaseFlow.h>


namespace Nektar
{

class LinearisedAdvection: public SolverUtils::Advection
{
    
public:
    friend class MemoryManager<LinearisedAdvection>;

    /// Creates an instance of this class
    static SolverUtils::AdvectionSharedPtr create(std::string)
    {
        return MemoryManager<LinearisedAdvection>::AllocateSharedPtr();
    }
    /// Name of class
    static std::string className;

    BaseFlow bf;


protected:
    LibUtilities::SessionReaderSharedPtr m_session;


    int m_spacedim;
    int m_expdim;

    

    /// flag to determine if use single mode or not
    bool                                            m_singleMode;
    /// flag to determine if use half mode or not
    bool                                            m_halfMode;
    /// flag to determine if use multiple mode or not
    bool                                            m_multipleModes;


    LinearisedAdvection();

    virtual ~LinearisedAdvection();

    virtual void v_InitObject(
              LibUtilities::SessionReaderSharedPtr         pSession,
              Array<OneD, MultiRegions::ExpListSharedPtr>  pFields);

    virtual void v_Advect(
        const int nConvectiveFields,
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields,
        const Array<OneD, Array<OneD, NekDouble> >        &advVel,
        const Array<OneD, Array<OneD, NekDouble> >        &inarray,
              Array<OneD, Array<OneD, NekDouble> >        &outarray,
        const NekDouble                                   &time,
        const Array<OneD, Array<OneD, NekDouble> > &pFwd = NullNekDoubleArrayofArray,
        const Array<OneD, Array<OneD, NekDouble> > &pBwd = NullNekDoubleArrayofArray);


    virtual void v_SetBaseFlow(
        const Array<OneD, Array<OneD, NekDouble> >        &inarray,
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields);

    
private:
    ///Parameter for homogeneous expansions
    enum HomogeneousType
    {
        eHomogeneous1D,
        eHomogeneous2D,
        eHomogeneous3D,
        eNotHomogeneous
    };

    enum HomogeneousType m_HomogeneousType;

    NekDouble m_LhomX; ///< physical length in X direction (if homogeneous)
    NekDouble m_LhomY; ///< physical length in Y direction (if homogeneous)
    NekDouble m_LhomZ; ///< physical length in Z direction (if homogeneous)

    int m_npointsX;    ///< number of points in X direction (if homogeneous)
    int m_npointsY;    ///< number of points in Y direction (if homogeneous)
    int m_npointsZ;    ///< number of points in Z direction (if homogeneous)

    int m_HomoDirec;   ///< number of homogenous directions

    int m_NumMode;     ///< Mode to use in case of single mode analysis

    SpatialDomains::BoundaryConditionsSharedPtr m_boundaryConditions;
};

}

#endif //NEKTAR_SOLVERS_INCNAVIERSTOKES_H
