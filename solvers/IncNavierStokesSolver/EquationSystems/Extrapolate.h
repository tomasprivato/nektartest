///////////////////////////////////////////////////////////////////////////////
//
// File: Extrapolate.h
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
// Description: Abstract base class for Extrapolate.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_SOLVERS_EXTRAPOLATE_H
#define NEKTAR_SOLVERS_EXTRAPOLATE_H

#include <LibUtilities/BasicUtils/NekFactory.hpp>
#include <LibUtilities/Memory/NekMemoryManager.hpp>
#include <LibUtilities/BasicUtils/SessionReader.h>
#include <MultiRegions/ExpList.h>
#include <LibUtilities/BasicUtils/SharedArray.hpp>
#include <LibUtilities/TimeIntegration/TimeIntegrationWrapper.h>
#include <SolverUtils/AdvectionSystem.h>

namespace Nektar
{
    // Forward declaration
    class Extrapolate;
    typedef boost::shared_ptr<Extrapolate> ExtrapolateSharedPtr;
    typedef LibUtilities::NekFactory< std::string, Extrapolate,
        const LibUtilities::SessionReaderSharedPtr& ,
        Array<OneD, MultiRegions::ExpListSharedPtr>& ,
        MultiRegions::ExpListSharedPtr& ,
        const Array<OneD, int>& ,
        const SolverUtils::AdvectionSharedPtr& > ExtrapolateFactory;

    ExtrapolateFactory& GetExtrapolateFactory();

    class Extrapolate
    {
    public:
        Extrapolate(        
            const LibUtilities::SessionReaderSharedPtr  pSession,
            Array<OneD, MultiRegions::ExpListSharedPtr> pFields,
            MultiRegions::ExpListSharedPtr              pPressure,
            const Array<OneD, int>                      pVel,
            const SolverUtils::AdvectionSharedPtr                advObject);
        
        virtual ~Extrapolate();

        void GenerateHOPBCMap();

        inline void SubSteppingTimeIntegration(
            const int intMethod,
            const LibUtilities::TimeIntegrationWrapperSharedPtr &IntegrationScheme);

        inline void SubStepSaveFields(
            const int nstep);
        
        inline void SubStepSetPressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &inarray, 
            const NekDouble Aii_DT,
            NekDouble kinvis);

        inline void SubStepAdvance(
            const LibUtilities::TimeIntegrationSolutionSharedPtr &integrationSoln, 
            const int nstep, 
            NekDouble time);

        inline void MountHOPBCs(
            int HBCdata, 
            NekDouble kinvis, 
            Array<OneD, NekDouble> &Q, 
            Array<OneD, const NekDouble> &Advection);

        inline void  EvaluatePressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &fields,
            const Array<OneD, const Array<OneD, NekDouble> >  &N,
            NekDouble kinvis);

        void CalcExplicitDuDt(const Array<OneD, const Array<OneD, NekDouble> > &fields);
        void ExtrapolatePressureHBCs(void);
        void CopyPressureHBCsToPbndExp(void);

        Array<OneD,NekDouble> GetMaxStdVelocity(
            const Array<OneD, Array<OneD,NekDouble> > inarray);
        

        void CorrectPressureBCs( const Array<OneD, NekDouble>  &pressure);
        
        void IProductNormVelocityOnHBC(const Array<OneD, const Array<OneD, NekDouble> >  &Vel, 
                                       Array<OneD, NekDouble> &IprodVn);
        
        void IProductNormVelocityBCOnHBC(Array<OneD, NekDouble> &IprodVn);
        
        LibUtilities::TimeIntegrationMethod GetSubStepIntegrationMethod(void); 

        void ExtrapolateArray( Array<OneD, Array<OneD, NekDouble> > &array);

        void AccelerationBDF( Array<OneD, Array<OneD, NekDouble> > &array);

        void ExtrapolateArray(
            Array<OneD, Array<OneD, NekDouble> > &oldarrays,
            Array<OneD, NekDouble>  &newarray,
            Array<OneD, NekDouble>  &outarray);
        
    protected: 
        virtual void v_EvaluatePressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &inarray, 
            const Array<OneD, const Array<OneD, NekDouble> >  &N,
            NekDouble kinvis)=0;

       virtual void v_SubSteppingTimeIntegration(
            int intMethod,        
            const LibUtilities::TimeIntegrationWrapperSharedPtr &IntegrationScheme)=0;

        virtual void v_SubStepSaveFields(
            int nstep)=0;

        virtual void v_SubStepSetPressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &inarray, 
            NekDouble Aii_DT,
            NekDouble kinvis)=0;

        virtual void v_SubStepAdvance(
            const LibUtilities::TimeIntegrationSolutionSharedPtr &integrationSoln, 
            int nstep, 
            NekDouble time)=0;

        virtual void v_MountHOPBCs(
            int HBCdata, 
            NekDouble kinvis, 
            Array<OneD, NekDouble> &Q, 
            Array<OneD, const NekDouble> &Advection)=0;
        
        virtual LibUtilities::TimeIntegrationMethod 
            v_GetSubStepIntegrationMethod(void);

        void CalcNeumannPressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &fields,
            const Array<OneD, const Array<OneD, NekDouble> >  &N,
            NekDouble kinvis)
        {
            v_CalcNeumannPressureBCs( fields, N, kinvis);
        }
                
        virtual void v_CalcNeumannPressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &fields,
            const Array<OneD, const Array<OneD, NekDouble> >  &N,
            NekDouble kinvis);
            
        virtual void v_CorrectPressureBCs( const Array<OneD, NekDouble>  &pressure);
        
        void CalcOutflowBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &fields,
            NekDouble kinvis);

        void RollOver(
            Array<OneD, Array<OneD, NekDouble> > &input);

        LibUtilities::SessionReaderSharedPtr m_session;

        LibUtilities::CommSharedPtr m_comm;

        Array<OneD, MultiRegions::ExpListSharedPtr> m_fields;

        /// Pointer to field holding pressure field
        MultiRegions::ExpListSharedPtr m_pressure;

        /// int which identifies which components of m_fields contains the
        /// velocity (u,v,w);
        Array<OneD, int> m_velocity;

        SolverUtils::AdvectionSharedPtr m_advObject;

        Array<OneD, Array<OneD, NekDouble> > m_previousVelFields;

        /// Curl-curl dimensionality
        int m_curl_dim;
        
        /// bounday dimensionality
        int m_bnd_dim;

        /// pressure boundary conditions container
        Array<OneD, const SpatialDomains::BoundaryConditionShPtr> m_PBndConds;

        /// pressure boundary conditions expansion container
        Array<OneD, MultiRegions::ExpListSharedPtr>  m_PBndExp;
        
        /// number of times the high-order pressure BCs have been called
        int m_pressureCalls;
        
        /// Maximum points used in pressure BC evaluation
        int m_pressureBCsMaxPts;

        /// Maximum points used in Element adjacent to pressure BC evaluation
        int m_pressureBCsElmtMaxPts;

        // Number of degrees of freedom (coefficients) for HOPbc
        int m_numHBCDof;

        // Number of HOPbcs
        int m_HBCnumber;

        // Number of quadrature points for Outflow HOBC
        int m_numOutHBCPts;
        int m_numOutElmtPts;

        // Number of Outflow HOBcs
        int m_outHBCnumber;

        /// Maximum points used in pressure BC evaluation
        int m_intSteps;

        NekDouble m_timestep;

        /// Id of element to which pressure  boundary condition belongs
        Array<OneD, int> m_pressureBCtoElmtID;
        
        /// Id of edge (2D) or face (3D) to which pressure boundary condition belongs
        Array<OneD, int> m_pressureBCtoTraceID;
        
        /// Storage for current and previous levels of high order pressure boundary conditions.
        Array<OneD, Array<OneD, NekDouble> >  m_pressureHBCs;

        /// Storage for current and previous levels of the acceleration term.
        Array<OneD, Array<OneD, NekDouble> >  m_acceleration;

        /// Storage for current and previous velocity fields at the otuflow for high order outflow BCs
        Array<OneD, Array<OneD, Array<OneD, Array<OneD, NekDouble > > > > m_outflowVel;

        Array<OneD, Array<OneD, NekDouble> > m_traceNormals;

        // Velocity correction scheme coefficient required for extrapolation.
        static NekDouble StifflyStable_Betaq_Coeffs[3][3];
        static NekDouble StifflyStable_Alpha_Coeffs[3][3];
        static NekDouble StifflyStable_Gamma0_Coeffs[3];

    private:
        static std::string def;

    };

    /**
     * Evaluate Pressure Boundary Conditions for Standard Extrapolation
     */
    inline void Extrapolate::EvaluatePressureBCs(
            const Array<OneD, const Array<OneD, NekDouble> > &inarray, 
            const Array<OneD, const Array<OneD, NekDouble> >  &N,
            NekDouble kinvis)
    {
        v_EvaluatePressureBCs(inarray,N,kinvis);
    }

    /**
     *
     */
    inline void Extrapolate::SubSteppingTimeIntegration(
        int intMethod,
        const LibUtilities::TimeIntegrationWrapperSharedPtr &IntegrationScheme)
    {
        v_SubSteppingTimeIntegration(intMethod, IntegrationScheme);
    }
    
    /**
     *
     */
    inline void Extrapolate::SubStepSaveFields(
        int nstep)
    {
        v_SubStepSaveFields(nstep);
    }

    /**
     *
     */
    inline void Extrapolate::SubStepSetPressureBCs(
        const Array<OneD, const Array<OneD, NekDouble> > &inarray, 
        NekDouble Aii_DT,
        NekDouble kinvis)
    {
        v_SubStepSetPressureBCs(inarray,Aii_DT,kinvis);
    }
    
    /**
     *
     */
    inline void Extrapolate::SubStepAdvance(
        const LibUtilities::TimeIntegrationSolutionSharedPtr &integrationSoln, 
        int nstep, 
        NekDouble time)
    {
        v_SubStepAdvance(integrationSoln,nstep, time);
    }

    /**
     *
     */
    inline void Extrapolate::MountHOPBCs(
        int HBCdata, 
        NekDouble kinvis, 
        Array<OneD, NekDouble> &Q, 
        Array<OneD, const NekDouble> &Advection)
    {
        v_MountHOPBCs(HBCdata,kinvis,Q,Advection);
    }

    /**
     *
     */
    inline LibUtilities::TimeIntegrationMethod 
        Extrapolate::GetSubStepIntegrationMethod(void)
    {
        return v_GetSubStepIntegrationMethod();
    }

    /**
     *
     */
    inline void Extrapolate::CorrectPressureBCs(
        const Array<OneD, NekDouble>  &pressure)
    {
        v_CorrectPressureBCs(pressure);
    }
}

#endif

