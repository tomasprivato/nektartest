///////////////////////////////////////////////////////////////////////////////
//
// File DisContField3D.h
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
// Description: Field definition in three-dimensions for a discontinuous
// LDG-H expansion
//
///////////////////////////////////////////////////////////////////////////////

#ifndef NEKTAR_LIBS_MULTIREGIONS_DISCONTFIELD3D_H
#define NEKTAR_LIBS_MULTIREGIONS_DISCONTFIELD3D_H
#include <MultiRegions/MultiRegionsDeclspec.h>
#include <LibUtilities/Communication/Comm.h>
#include <MultiRegions/MultiRegions.hpp>
#include <MultiRegions/ExpList3D.h>
#include <MultiRegions/ExpList1D.h>
#include <MultiRegions/GlobalLinSys.h>
#include <MultiRegions/AssemblyMap/AssemblyMapDG.h>
#include <LocalRegions/SegExp.h>
#include <SpatialDomains/MeshGraph3D.h>
#include <SpatialDomains/Conditions.h>
#include <SpatialDomains/SegGeom.h>

namespace Nektar
{
    namespace MultiRegions
    {        
        /**
         * Abstraction of a global discontinuous three-dimensional spectral/hp
         * element expansion which approximates the solution of a set of
         * partial differential equations.
         */
        class DisContField3D : public ExpList3D
        {
        public:
            /**
             * Default constructor
             */
            MULTI_REGIONS_EXPORT DisContField3D();

            /**
             * Constructs a global discontinuous field based on an input mesh
             * with boundary conditions.
             */
            MULTI_REGIONS_EXPORT DisContField3D(
                const LibUtilities::SessionReaderSharedPtr &pSession,
                const SpatialDomains::MeshGraphSharedPtr &graph3D,
                const std::string &variable,
                const bool SetUpJustDG = true);

            MULTI_REGIONS_EXPORT DisContField3D(
                const DisContField3D &In,
                const SpatialDomains::MeshGraphSharedPtr &graph3D,
                const std::string &variable,
                const bool SetUpJustDG = false);
            
            /// Constructs a global discontinuous field based on another
            /// discontinuous field.
            MULTI_REGIONS_EXPORT DisContField3D(const DisContField3D &In);

            /// Destructor.
            MULTI_REGIONS_EXPORT virtual ~DisContField3D();

            MULTI_REGIONS_EXPORT GlobalLinSysSharedPtr GetGlobalBndLinSys(const GlobalLinSysKey &mkey);
        protected:
            /**
             * An array of size equal to the number of boundary regions and
             * consists of entries of the type MultiRegions#ExpList1D. Every
             * entry corresponds to the one-dimensional spectral/hp expansion
             * on a single boundary region.  The values of the boundary
             * conditions are stored as the coefficients of the
             * one-dimensional expansion.
             */
            Array<OneD,MultiRegions::ExpListSharedPtr>        m_bndCondExpansions;

            /// An array which contains the information about the boundary
            /// condition on the different boundary regions.
            Array<OneD,SpatialDomains::BoundaryConditionShPtr> m_bndConditions;

            GlobalLinSysMapShPtr        m_globalBndMat;
            ExpListSharedPtr            m_trace;
            AssemblyMapDGSharedPtr      m_traceMap;

            /**
             * @brief A map which identifies pairs of periodic faces.
             */
            map<int, PeriodicFace> m_periodicFaces;
	    
            /**
             * @brief Auxiliary map for periodic boundary conditions.
             * 
             * Takes geometry IDs of periodic edges to a pair (n,e), where n
             * is the expansion containing the edge and e the local edge number.
             */
            boost::unordered_map<int,pair<int,int> > m_perFaceToExpMap;

            /// This function discretises the boundary conditions by setting up
            /// a list of one-dimensional boundary expansions.
            void GenerateBoundaryConditionExpansion(
                    const SpatialDomains::MeshGraphSharedPtr &graph3D,
                    const SpatialDomains::BoundaryConditions &bcs,
                    const std::string &variable);

            void SetUpDG();

            bool SameTypeOfBoundaryConditions(const DisContField3D &In);

            /// Generates a map of periodic faces in the mesh.
            void GetPeriodicFaces(
                const SpatialDomains::MeshGraphSharedPtr &graph3D,
                const SpatialDomains::BoundaryConditions &bcs,
                const std::string                        &variable,
                map<int,int>                             &periodicVertices,
                map<int,int>                             &periodicEdges,
                map<int,PeriodicFace>                    &periodicFaces);

            virtual void v_HelmSolve(
                    const Array<OneD, const NekDouble> &inarray,
                          Array<OneD,       NekDouble> &outarray,
                    const FlagList &flags,
                    const StdRegions::ConstFactorMap &factors,
                    const StdRegions::VarCoeffMap &varcoeff,
                    const Array<OneD, const NekDouble> &dirForcing);
			
            virtual void v_GeneralMatrixOp(
                   const GlobalMatrixKey             &gkey,
                   const Array<OneD,const NekDouble> &inarray,
                   Array<OneD,      NekDouble> &outarray,
                   CoeffState coeffstate = eLocal);

            virtual void v_EvaluateBoundaryConditions(
                const NekDouble time = 0.0,
                const NekDouble x2_in = NekConstants::kNekUnsetDouble,
                const NekDouble x3_in = NekConstants::kNekUnsetDouble);

            bool IsLeftAdjacentFace(const int n, const int e);
            
            virtual void v_GetFwdBwdTracePhys(
                Array<OneD,NekDouble> &Fwd,
                Array<OneD,NekDouble> &Bwd);
            virtual void v_GetFwdBwdTracePhys(
                const Array<OneD,const NekDouble> &field,
                      Array<OneD,      NekDouble> &Fwd,
                      Array<OneD,      NekDouble> &Bwd);
            virtual void v_ExtractTracePhys(
                      Array<OneD,       NekDouble> &outarray);
            virtual void v_ExtractTracePhys(
                const Array<OneD, const NekDouble> &inarray,
                      Array<OneD,       NekDouble> &outarray);
            virtual void v_AddTraceIntegral(
                const Array<OneD, const NekDouble> &Fn,
                      Array<OneD,       NekDouble> &outarray);
            virtual void v_AddFwdBwdTraceIntegral(
                const Array<OneD, const NekDouble> &Fwd, 
                const Array<OneD, const NekDouble> &Bwd, 
                Array<OneD,       NekDouble> &outarray);

            virtual const Array<OneD, const MultiRegions::ExpListSharedPtr> 
                &v_GetBndCondExpansions();
            virtual const Array<OneD,const SpatialDomains::BoundaryConditionShPtr> 
                &v_GetBndConditions();

            /// \brief Set up a list of element ids and edge ids the link to the
            /// boundary conditions
            virtual void v_GetBoundaryToElmtMap(Array<OneD,int> &ElmtID,
                                                Array<OneD,int> &FaceID);

            virtual ExpListSharedPtr &v_GetTrace(void)
            {
                if(m_trace == NullExpListSharedPtr)
                {
                    SetUpDG();
                }
                return m_trace;
            }
            
            virtual AssemblyMapDGSharedPtr &v_GetTraceMap()
            {
                return m_traceMap;
            }

            virtual map<int, RobinBCInfoSharedPtr> v_GetRobinBCInfo();
        };

        typedef boost::shared_ptr<DisContField3D> DisContField3DSharedPtr;
    } //end of namespace
} //end of namespace

#endif // MULTIERGIONS_DISCONTFIELD3D_H
