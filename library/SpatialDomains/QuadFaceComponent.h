////////////////////////////////////////////////////////////////////////////////
//
//  File:  QuadFaceComponent.h
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
//  Description:
//
//
////////////////////////////////////////////////////////////////////////////////
#ifndef NEKTAR_SPATIALDOMAINS_QUADFACECOMPONENT_H
#define NEKTAR_SPATIALDOMAINS_QUADFACECOMPONENT_H

#include <SpatialDomains/SpatialDomains.hpp>
#include <SpatialDomains/MeshGraph.h>
#include <SpatialDomains/MeshComponents.h>
#include <SpatialDomains/Geometry2D.h>

#include <StdRegions/StdQuadExp.h>

namespace Nektar
{
    namespace SpatialDomains
    {
        class QuadFaceComponent: public Geometry2D
        {
        public:
            QuadFaceComponent();
            QuadFaceComponent(const int coordim);
            ~QuadFaceComponent();
            QuadFaceComponent(const QuadFaceComponent &T);

            void AddElmtConnected(int gvo_id, int locid);
            int  NumElmtConnected() const;
            bool IsElmtConnected(int gvo_id, int locid) const;

            inline int GetFid() const 
            {
                return m_fid;
            }

            inline int GetCoordDim() const 
            {
                return m_coordim;
            }

            inline const LibUtilities::BasisSharedPtr GetBasis(const int i, const int j)
            {
                return m_xmap[i]->GetBasis(j);
            }

            inline Array<OneD,NekDouble> &UpdatePhys(const int i)
            {
                return m_xmap[i]->UpdatePhys();
            }

            NekDouble GetCoord(const int i, const Array<OneD, const NekDouble> &Lcoord);

        protected:
            int m_fid;
            bool m_ownverts;
            std::list<CompToElmt> m_elmtmap;

            Array<OneD, StdRegions::StdExpansion2DSharedPtr> m_xmap;

        private:
            virtual void v_AddElmtConnected(int gvo_id, int locid)
            {
                AddElmtConnected(gvo_id,locid);
            }

            virtual int  v_NumElmtConnected() const
            {
                return NumElmtConnected();
            }

            virtual bool v_IsElmtConnected(int gvo_id, int locid) const
            {
                return IsElmtConnected(gvo_id,locid);
            }
            
            virtual int v_GetFid() const 
            {
                return GetFid();
            }

            virtual int v_GetCoordDim() const 
            {
                return GetCoordDim();
            }

            virtual const LibUtilities::BasisSharedPtr v_GetBasis(const int i, const int j)
            {
                return GetBasis(i,j);
            }

            virtual Array<OneD,NekDouble> &v_UpdatePhys(const int i)
            {
                return UpdatePhys(i);
            }

            virtual NekDouble v_GetCoord(const int i, const Array<OneD,const NekDouble> &Lcoord)
            {
                return GetCoord(i,Lcoord);
            }
        };

        typedef boost::shared_ptr<QuadFaceComponent> QuadFaceComponentSharedPtr;
        typedef std::vector<QuadFaceComponentSharedPtr> QuadFaceComponentVector; 
    }; //end of namespace
}; //end of namespace

#endif //NEKTAR_SPATIALDOMAINS_QUADFACECOMPONENT_H

//
// $Log: QuadFaceComponent.h,v $
// Revision 1.7  2008/04/02 22:19:04  pvos
// Update for 2D local to global mapping
//
// Revision 1.6  2008/01/21 19:58:14  sherwin
// Updated so that QuadGeom and TriGeom have SegGeoms instead of EdgeComponents
//
// Revision 1.5  2007/07/22 23:04:24  bnelson
// Backed out Nektar::ptr.
//
// Revision 1.4  2007/07/20 02:15:09  bnelson
// Replaced boost::shared_ptr with Nektar::ptr
//
// Revision 1.3  2007/06/06 15:15:21  pvos
// Some minor updates for 2D routines
//
// Revision 1.2  2007/05/28 21:48:42  sherwin
// Update for 2D functionality
//
// Revision 1.1  2006/05/04 18:59:03  kirby
// *** empty log message ***
//
// Revision 1.7  2006/03/12 14:20:43  sherwin
//
// First compiling version of SpatialDomains and associated modifications
//
// Revision 1.6  2006/03/12 11:06:40  sherwin
//
// First complete copy of code standard code but still not compile tested
//
// Revision 1.5  2006/03/04 20:26:05  bnelson
// Added comments after #endif.
//
// Revision 1.4  2006/02/19 01:37:34  jfrazier
// Initial attempt at bringing into conformance with the coding standard.  Still more work to be done.  Has not been compiled.
//
//
