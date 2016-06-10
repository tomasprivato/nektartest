///////////////////////////////////////////////////////////////////////////////
//
// File Dummy.h
//
// For more information, please see: http://www.nektar.info
//
// The MIT License
//
// Copyright (c) 2016 Kilian Lackhove
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
// Description: Dummy Equation System that only sends/receives fields
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_DummySOLVER_EQUATIONSYSTEMS_DUMMY_H
#define NEKTAR_SOLVERS_DummySOLVER_EQUATIONSYSTEMS_DUMMY_H

#include <SolverUtils/UnsteadySystem.h>

#include <SolverUtils/Exchange.h>

using namespace Nektar::SolverUtils;

namespace Nektar
{

class Dummy : public UnsteadySystem
{
public:
    friend class MemoryManager<Dummy>;

    /// Creates an instance of this class
    static EquationSystemSharedPtr create(
        const LibUtilities::SessionReaderSharedPtr &pSession)
    {
        EquationSystemSharedPtr p =
            MemoryManager<Dummy>::AllocateSharedPtr(pSession);
        p->InitObject();
        return p;
    }
    /// Name of class
    static std::string className;

    /// Destructor
    virtual ~Dummy();

protected:
    SolverUtils::CouplingSharedPointer m_coupling;

    SolverUtils::ExchangeSharedPtr m_sendExchange;
    int m_nSendVars;
    int m_nRecvVars;
    int m_recvSteps;
    int m_sendSteps;

    /// Initialises UnsteadySystem class members.
    Dummy(const LibUtilities::SessionReaderSharedPtr &pSession);

    virtual void v_InitObject();

    void DoOdeRhs(const Array<OneD, const Array<OneD, NekDouble> > &inarray,
                  Array<OneD, Array<OneD, NekDouble> > &outarray,
                  const NekDouble time);

    void DoOdeProjection(
        const Array<OneD, const Array<OneD, NekDouble> > &inarray,
        Array<OneD, Array<OneD, NekDouble> > &outarray,
        const NekDouble time);

    virtual bool v_PostIntegrate(int step);

    virtual void v_Output(void);

private:
    Array<OneD, Array<OneD, NekDouble> > m_recFields;
    std::vector<std::string> m_recvFieldNames;

    void receiveFields();

    void DumpFields();
};
}

#endif
