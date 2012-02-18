///////////////////////////////////////////////////////////////////////////////
//
// File: Expansion3D.h
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
// Description: Header file for Expansion3D routines
//
///////////////////////////////////////////////////////////////////////////////

#ifndef EXPANSION3D_H

#include <LocalRegions/Expansion.h>
#include <LocalRegions/Expansion2D.h>
#include <LocalRegions/LocalRegionsDeclspec.h>

namespace Nektar
{
    namespace LocalRegions 
    {
        class Expansion3D: virtual public Expansion, 
                           virtual public StdRegions::StdExpansion3D
        {
        public:
            LOCAL_REGIONS_EXPORT Expansion3D();
            LOCAL_REGIONS_EXPORT virtual ~Expansion3D() {}
            
            LOCAL_REGIONS_EXPORT void SetFaceExp(const int face, Expansion2DSharedPtr &f);                       
            
        protected:
            LOCAL_REGIONS_EXPORT virtual DNekMatSharedPtr v_GenMatrix(const StdRegions::StdMatrixKey &mkey);
            
            LOCAL_REGIONS_EXPORT void v_AddFaceNormBoundaryInt(
                const int                            face,
                StdRegions::StdExpansion2DSharedPtr &FaceExp,
                const Array<OneD, const NekDouble>  &Fx,
                const Array<OneD, const NekDouble>  &Fy,
                const Array<OneD, const NekDouble>  &Fz,
                      Array<OneD,       NekDouble>  &outarray);
            
            LOCAL_REGIONS_EXPORT void v_AddFaceNormBoundaryInt(
                const int                            face,
                StdRegions::StdExpansion2DSharedPtr &FaceExp,
                const Array<OneD, const NekDouble>  &Fn,
                      Array<OneD,       NekDouble>  &outarray);
            
        private:
            // Do not add members here since it may lead to conflicts.
            // Only use this class for member functions
            
            std::vector<Expansion2DWeakPtr> m_faceExp;
        };
        
        // type defines for use of PrismExp in a boost vector
        typedef boost::shared_ptr<Expansion3D> Expansion3DSharedPtr;
        typedef boost::weak_ptr<Expansion3D> Expansion3DWeakPtr;
        typedef std::vector< Expansion3DSharedPtr > Expansion3DVector;
        typedef std::vector< Expansion3DSharedPtr >::iterator Expansion3DVectorIter;
    } //end of namespace
} //end of namespace

#define EXPANSION3D_H
#endif
