////////////////////////////////////////////////////////////////////////////////
//
//  File:  $Source: /usr/sci/projects/Nektar/cvs/Nektar++/libs/SpatialDomains/TriGeom.h,v $
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
#ifndef NEKTAR_SPATIALDOMAINS_TRIGEOM_H
#define NEKTAR_SPATIALDOMAINS_TRIGEOM_H

#include <StdRegions/StdRegions.hpp>
#include <SpatialDomains/SpatialDomains.hpp>

#include <SpatialDomains/GeoFac.h>
#include <SpatialDomains/Geometry2D.h>
#include <SpatialDomains/MeshComponents.h>
#include <SpatialDomains/EdgeComponent.h>
#include <SpatialDomains/TriFaceComponent.h>

namespace Nektar
{
    namespace SpatialDomains
    {
        class TriGeom: public TriFaceComponent
        {
        public:
            TriGeom();
            TriGeom(const VertexComponentSharedPtr verts[], const EdgeComponentSharedPtr edges[], StdRegions::EdgeOrientation * eorient);
            TriGeom(const EdgeComponentSharedPtr edges[], StdRegions::EdgeOrientation * eorient);
            ~TriGeom();

            inline void SetOwnData()
            {
                m_owndata = true; 
            }

            void FillGeom();
            GeoFacSharedPtr GenXGeoFac();

            void GetLocCoords(double *Lcoords, const double *coords);

        static const int kNedges = 3;
        static const int kNverts = 3;

        protected:
            VertexComponentVector           m_verts;
            EdgeComponentVector             m_edges;
            StdRegions::EdgeOrientation     m_eorient [kNedges];

        private:
            bool m_owndata;
        };

        typedef boost::shared_ptr<TriGeom>      TriGeomSharedPtr;
        typedef std::vector< TriGeomSharedPtr > TriGeomVector;
        typedef std::vector< TriGeomSharedPtr >::iterator TriGeomVectorIter;

    }; //end of namespace SpatialDomains
}; //end of namespace Nektar

#endif //NEKTAR_SPATIALDOMAINS_TRIGEOM_H

//
// $Log: TriGeom.h,v $
// Revision 1.4  2006/05/30 14:00:04  sherwin
// Updates to make MultiRegions and its Demos work
//
// Revision 1.3  2006/05/29 17:05:17  sherwin
// Updated to use shared_ptr around Geom types - added typedef
//
// Revision 1.2  2006/05/07 11:26:38  sherwin
// Modifications to get the demo LocalRegions::Project2D to compile
//
// Revision 1.1  2006/05/04 18:59:05  kirby
// *** empty log message ***
//
// Revision 1.23  2006/04/11 23:18:11  jfrazier
// Completed MeshGraph2D for tri's and quads.  Not thoroughly tested.
//
// Revision 1.22  2006/04/09 02:08:36  jfrazier
// Added precompiled header.
//
// Revision 1.21  2006/03/25 00:58:29  jfrazier
// Many changes dealing with fundamental structure and reading/writing.
//
// Revision 1.20  2006/03/12 14:20:44  sherwin
//
// First compiling version of SpatialDomains and associated modifications
//
// Revision 1.19  2006/03/12 11:06:41  sherwin
//
// First complete copy of code standard code but still not compile tested
//
// Revision 1.18  2006/03/04 20:26:05  bnelson
// Added comments after #endif.
//
// Revision 1.17  2006/02/19 01:37:35  jfrazier
// Initial attempt at bringing into conformance with the coding standard.  Still more work to be done.  Has not been compiled.
//
//
