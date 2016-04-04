////////////////////////////////////////////////////////////////////////////////
//
//  File: Curavturepoint.hpp
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
//  Description: class and methods of curvature sampling point
//
////////////////////////////////////////////////////////////////////////////////

#ifndef NEKMESHUTILS_OCTREE_CURAVTUREPOINT
#define NEKMESHUTILS_OCTREE_CURAVTUREPOINT

#include <LibUtilities/BasicUtils/SharedArray.hpp>
#include <LibUtilities/Memory/NekMemoryManager.hpp>

namespace Nektar
{
namespace NekMeshUtils
{

enum SPType
{
    eCBoundary; // on a curved boundary
    ePBoundary; // on a planar boundary (R=inf)
    eSrcPoint;  // source point
};

/**
 * @brief base class of sizing point for octree construction
 *        these carry information the octree needs and have various types
 */
class SPBase
{
public:
    friend class MemoryManager<SPBase>;

    SPBase(){};

    CPType GetType()
    {
        return m_type;
    }

    Array<OneD, NekDouble> GetLoc()
    {
        return m_loc;
    }

    virtual NekDouble GetDelta();

protected:
    /// type
    CPType m_type;
    /// x,y,z location
    Array<OneD, NekDouble> m_loc;
}

/**
 * @brief class for a curvature based samlping Point
 */
class CPoint : public SPBase
{
public:
    friend class MemoryManager<CPoint>;

    /**
     * @brief constructor for a valid point (has radius of curvature)
     */
    CPoint(int i, Array<OneD, NekDouble> uv, Array<OneD, NekDouble> l,
           NekDouble d)
        : sid(i), m_uv(uv), m_loc(l), m_delta(d)
    {
        m_type = eCBoundary;
    }

    /**
     * @brief get mesh spacing paramter
     */
    NekDouble GetDelta()
    {
        return m_delta;
    }

    /**
     * @brief gets the corresponding cad information for the point
     */
    void GetCAD(int &surf, Array<OneD, NekDouble> &uv)
    {
        surf = sid;
        uv   = m_uv;
    }

    void SetDelta(NekDouble i)
    {
        m_delta = i;
    }

private:
    /// surf id
    int sid;
    /// uv coord on surf
    Array<OneD, NekDouble> m_uv;
    /// delta parameter
    NekDouble m_delta;
};
typedef boost::shared_ptr<CPoint> CPoint;

/**
 * @brief class for a planar boundary based samlping Point
 */
class BPoint : public SPBase
{
public:
    friend class MemoryManager<BPoint>;

    /**
     * @brief constructor for a boundary point without delta
     */
    BPoint(int i, Array<OneD, NekDouble> uv, Array<OneD, NekDouble> l)
        : sid(i), m_uv(uv), m_loc(l)
    {
        m_type = ePBoundary;
    }

    NekDouble GetDelta()
    {
        ASSERTL0(false,"Cannot retrieve delta from this type")
    }
private:
    /// surf id
    int sid;
    /// uv coord on surf
    Array<OneD, NekDouble> m_uv;
};
typedef boost::shared_ptr<BPoint> BPoint;

/**
 * @brief class for a planar boundary based samlping Point
 */
class SrcPoint : public SPBase
{
public:
    friend class MemoryManager<SrcPoint>;

    /**
     * @brief constructor for a boundary point without delta
     */
    SrcPoint(Array<OneD, NekDouble> l, NekDouble d)
            : m_loc(l), m_delta(d)
    {
        m_type = eSrcPoint;
    }

    /**
     * @brief get mesh spacing paramter
     */
    NekDouble GetDelta()
    {
        return m_delta;
    }

    void SetDelta(NekDouble i)
    {
        m_delta = i;
    }

private:
    NekDouble m_delta;
};
typedef boost::shared_ptr<SrcPoint> SrcPoint;

}
}

#endif
