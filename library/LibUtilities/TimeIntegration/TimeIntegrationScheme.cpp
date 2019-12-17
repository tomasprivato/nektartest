///////////////////////////////////////////////////////////////////////////////
//
// File TimeIntegrationScheme.cpp
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
// Description: implementation of time integration key class
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include <LibUtilities/TimeIntegration/TimeIntegrationSolution.h>
#include <LibUtilities/TimeIntegration/TimeIntegrationSchemeOperators.h>
#include <LibUtilities/TimeIntegration/TimeIntegrationScheme.h>
#include <LibUtilities/TimeIntegration/TimeIntegrationSchemeData.h>
#include <LibUtilities/BasicConst/NektarUnivConsts.hpp>

namespace Nektar
{
namespace LibUtilities
{

TimeIntegrationSchemeFactory &GetTimeIntegrationSchemeFactory()
{
    static TimeIntegrationSchemeFactory instance;
    return instance;
}

std::ostream &operator<<(std::ostream &os,
                         const TimeIntegrationSchemeSharedPtr &rhs)
{
    os << *rhs.get();
    return os;
}

std::ostream &operator<<(std::ostream &os, const TimeIntegrationScheme &rhs)
{

    os << "Time Integration Scheme: " << rhs.GetName() << ".\n"
       << "        Has " << rhs.m_integration_phases.size() << " phases.\n";

    for (int i = 0; i < rhs.m_integration_phases.size(); i++)
    {
        os << "            - "
           << rhs.m_integration_phases[i]->m_parent->GetName()
           << "\n";
    }
    return os;
}

TimeIntegrationScheme::ConstDoubleArray &TimeIntegrationScheme::TimeIntegrate(
    const int timestep, const NekDouble delta_t,
    TimeIntegrationSolutionSharedPtr &solvector,
    const TimeIntegrationSchemeOperators &op)
{
    int phases = GetNumIntegrationPhases();
    TimeIntegrationSchemeDataSharedPtr &data =
        m_integration_phases[std::min(timestep, phases - 1)];
    return data->TimeIntegrate(delta_t, solvector, op);
}

TimeIntegrationScheme::TimeIntegrationSolutionSharedPtr TimeIntegrationScheme::
    InitializeScheme(const NekDouble deltaT,
                     TimeIntegrationScheme::ConstDoubleArray &y_0,
                     const NekDouble time,
                     const TimeIntegrationSchemeOperators &op)
{
    return m_integration_phases.back()->InitializeData(deltaT, y_0, time, op);
}

TimeIntegrationSchemeType TimeIntegrationScheme::GetIntegrationSchemeType()
    const
{
    ASSERTL0(!m_integration_phases.empty(), "No scheme")
    return m_integration_phases[m_integration_phases.size() - 1]->m_schemeType;
}

void TimeIntegrationScheme::SetExponentialCoefficients(Array<TwoD, NekDouble> &Lambda)
{
    ASSERTL0(!m_integration_phases.empty(), "No scheme")

    // Assumption: the two-dimensional Lambda matrix is a diagonal
    // matrix thus values are non zero if and only i=j. As such, the
    // diagonal Lambda values are stored as two vectors so to
    // accomodate complex numbers lambda[0] real, lambda[1] imaginary.

    // Assume that each phase is an exponential integrator.
    for (int i = 0; i < m_integration_phases.size(); i++)
    {
        m_integration_phases[i]->m_L = Lambda;

        // Anytime the coefficents are updated reset the nVars to be
        // assured that the exponential matrices are recalculated
        // (e.g. the number of variables may remain the same but the
        // coefficients have changed).
        m_integration_phases[i]->m_lastNVars = 0;
    }
}

void TimeIntegrationScheme::SetupSchemeExponentialData(TimeIntegrationSchemeData *phase, NekDouble deltaT) const
{
    boost::ignore_unused(phase);
    boost::ignore_unused(deltaT);

    ASSERTL0(false, "No SetupSchemeExponentialData method for scheme " +
             GetName());
};

NekDouble TimeIntegrationScheme::exp_function(NekDouble deltaT,
                                              NekDouble L_Real,
                                              NekDouble L_Imaginary) const
{
    boost::ignore_unused( L_Imaginary );

    return exp( deltaT * L_Real );
}

NekDouble TimeIntegrationScheme::psi_function(unsigned int i,
                                              NekDouble deltaT,
                                              NekDouble L_Real,
                                              NekDouble L_Imaginary) const
{
    NekDouble z = deltaT * L_Real;

    NekDouble expZ = exp_function(deltaT, L_Real, L_Imaginary);

    switch( i )
    {
    case 1:
        return  (expZ - 1.0) / (z);
        break;
    case 2:
        return (expZ - z - 1.0) / (z * z);
        break;
    case 3:
        return (expZ - (z*z)/2.0 - z - 1.0) / (z * z * z);
        break;
    default:
        ASSERTL0(false,
                 "No phi function defined for index " + std::to_string(i) );
        break;
    }

    return 0;
}

} // end namespace LibUtilities
} // end namespace NekTar
