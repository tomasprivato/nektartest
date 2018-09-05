///////////////////////////////////////////////////////////////////////////////
//
// File LocTraceToTraceMap.h
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
// Description: Local Trace to general trace map information
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MULTIREGIONS_LOCTRACETOTRACEMAP_H
#define MULTIREGIONS_LOCTRACETOTRACEMAP_H

#include <tuple>

#include <LibUtilities/Foundations/Points.h>
#include <LibUtilities/LinearAlgebra/NekTypeDefs.hpp>
#include <LibUtilities/BasicUtils/SharedArray.hpp>
#include <MultiRegions/MultiRegionsDeclspec.h>

namespace Nektar
{
namespace LocalRegions
{
class Expansion;
typedef std::shared_ptr<Expansion> ExpansionSharedPtr;
}

namespace MultiRegions
{
class ExpList;
typedef std::shared_ptr<ExpList> ExpListSharedPtr;

enum InterpLocTraceToTrace
{
    eNoInterp,
    eInterpDir0,
    eInterpEndPtDir0,
    eInterpDir1,
    eInterpEndPtDir1,
    eInterpBothDirs,
    eInterpEndPtDir0InterpDir1
};

/**
 * @brief Map holding points distributions required for interpolation of local
 * traces onto global trace in two and three dimensions.
 *
 * The tuple contains four PointsKey entries. All four are used in 3D, but for
 * 2D only two are used. The first two denote the local elemental points
 * distributions, the latter the target trace distributions. In the 2D case,
 * unused trace directions are set to LibUtilities::eNoPointsType.
 */
typedef std::tuple<LibUtilities::PointsKey,
                   LibUtilities::PointsKey,
                   LibUtilities::PointsKey,
                   LibUtilities::PointsKey> TraceInterpPoints;

struct cmpop
{
    bool operator()(TraceInterpPoints const &a,
                    TraceInterpPoints const &b) const
    {
        if (std::get<0>(a) < std::get<0>(b))
        {
            return true;
        }

        if (std::get<0>(b) < std::get<0>(a))
        {
            return false;
        }

        if (std::get<1>(a) < std::get<1>(b))
        {
            return true;
        }
        if (std::get<1>(b) < std::get<1>(a))
        {
            return false;
        }

        if (std::get<2>(a) < std::get<2>(b))
        {
            return true;
        }

        if (std::get<2>(b) < std::get<2>(a))
        {
            return false;
        }

        if (std::get<3>(a) < std::get<3>(b))
        {
            return true;
        }

        return false;
    }
};

/**
 * @brief A helper class to deal with trace operations in the discontinuous
 * Galerkin code.
 *
 * This class sets up a number of mappings to deal with operations that take the
 * "local trace" of an expansion list -- i.e. the concatenation of all elemental
 * facets -- to the "global trace" -- where the duplicate facets between
 * connected elements have been removed.
 *
 * <pre>
 * Elements:      Local trace:              Global trace:
 * +----+----+    + +---+ +   + +---+ +     + +---+ + +---+ +
 * |    |    |    |       |   |       |     |       |       |
 * |    |    |    |       |   |       |     |       |       |
 * +----+----+    + +---+ +   + +---+ +     + +---+ + +---+ +
 * </pre>
 *
 * There are a number of mappings that are required that this class provides
 * maps for:
 *
 *   - Extracting the local trace from the elements in physical space
 *   - Dealing with cases that need interpolation (i.e. where the polynomial
 *     order varies between two elements)
 *   - Adding global trace contributions back into the elements.
 *
 * These are documented in the member variables and class functions.
 */
class LocTraceToTraceMap
{
public:
    // Constructor
    MULTI_REGIONS_EXPORT LocTraceToTraceMap(
        const ExpList &locExp,
        const ExpListSharedPtr &trace,
        const Array<OneD, Array<OneD, LocalRegions::ExpansionSharedPtr> >
            &elmtToTrace,
        const std::vector<bool> &LeftAdjacents);

    // Destructor
    MULTI_REGIONS_EXPORT virtual ~LocTraceToTraceMap();

    MULTI_REGIONS_EXPORT void Setup2D(
        const ExpList &locExp,
        const ExpListSharedPtr &trace,
        const Array<OneD, Array<OneD, LocalRegions::ExpansionSharedPtr> >
            &elmtToTrace,
        const std::vector<bool> &LeftAdjacents);

    MULTI_REGIONS_EXPORT void Setup3D(
        const ExpList &locExp,
        const ExpListSharedPtr &trace,
        const Array<OneD, Array<OneD, LocalRegions::ExpansionSharedPtr> >
            &elmtToTrace,
        const std::vector<bool> &LeftAdjacents);

    MULTI_REGIONS_EXPORT void LocTracesFromField(
        const Array<OneD, const NekDouble> &field,
        Array<OneD, NekDouble> faces);

    MULTI_REGIONS_EXPORT void FwdLocTracesFromField(
        const Array<OneD, const NekDouble> &field,
        Array<OneD, NekDouble> faces);

    MULTI_REGIONS_EXPORT void InterpLocEdgesToTrace(
        const int dir,
        const Array<OneD, const NekDouble> &locfaces,
        Array<OneD, NekDouble> edges);

    MULTI_REGIONS_EXPORT void InterpLocFacesToTrace(
        const int dir,
        const Array<OneD, const NekDouble> &locfaces,
        Array<OneD, NekDouble> faces);

    MULTI_REGIONS_EXPORT void AddTraceCoeffsToFieldCoeffs(
        const Array<OneD, const NekDouble> &trace,
        Array<OneD, NekDouble> &field);

    MULTI_REGIONS_EXPORT void AddTraceCoeffsToFieldCoeffs(
        const int dir,
        const Array<OneD, const NekDouble> &race,
        Array<OneD, NekDouble> &field);

    /**
     * @brief Return the number of `forward' local trace points.
     */
    MULTI_REGIONS_EXPORT inline int GetNFwdLocTracePts()
    {
        return m_nFwdLocTracePts;
    }

    /**
     * @brief Return the number of local trace points.
     */
    MULTI_REGIONS_EXPORT inline int GetNLocTracePts()
    {
        return m_nLocTracePts;
    }

    /**
     * @brief Return the number of `forward' local trace coeffs.
     */
    MULTI_REGIONS_EXPORT inline int GetNFwdCoeffs()
    {
        return m_nTraceCoeffs[0];
    }

    /**
     * @brief Return the number of `forward' local trace coeffs.
     */
    MULTI_REGIONS_EXPORT inline int GetNBwdCoeffs()
    {
        return m_nTraceCoeffs[1];
    }

    //const Array<OneD, const Array<OneD, const int> > with a const in front of int can not compile but const Array<OneD, const int> can 
    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, int> > &Get_traceCoeffsToElmtMap() const
    {
        return m_traceCoeffsToElmtMap;
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, int> > &Get_traceCoeffsToElmtSign() const
    {
        return m_traceCoeffsToElmtSign;
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, int> > &Get_traceCoeffsToElmtTrace() const
    {
        return m_traceCoeffsToElmtTrace;
    }


    MULTI_REGIONS_EXPORT inline const Array<OneD, const int> &Get_traceCoeffsToElmtMap(const int nindex) const
    {
        return m_traceCoeffsToElmtMap[nindex];
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const int> &Get_traceCoeffsToElmtSign(const int nindex) const 
    {
        return m_traceCoeffsToElmtSign[nindex];
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const int> &Get_traceCoeffsToElmtTrace(const int nindex) const
    {
        return m_traceCoeffsToElmtTrace[nindex];
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, bool>>  &GetLeftRightAdjacentExpFlag() const
    {
        return m_LeftRightAdjacentExpFlag;
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, int >>   &GetLeftRightAdjacentExpId() const 
    {
        return m_LeftRightAdjacentExpId;
    }

    // MULTI_REGIONS_EXPORT inline const Array<OneD, const int >>   &GetLeftRightAdjacentExpId(const int lr) const 
    // {
    //     return m_LeftRightAdjacentExpId[lr];
    // }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, Array<OneD, int > > >  &GetTraceceffToLeftRightExpcoeffMap() const
    {
        return m_TraceceffToLeftRightExpcoeffMap;
    }

    MULTI_REGIONS_EXPORT inline const Array<OneD, const Array<OneD, Array<OneD, int > > > &GetTraceceffToLeftRightExpcoeffSign() const
    {
        return m_TraceceffToLeftRightExpcoeffSign;
    }

private:
    /// The number of forward trace points. A local trace element is `forward'
    /// if it is the side selected for the global trace.
    int m_nFwdLocTracePts;
    /// The number of local trace points.
    int m_nLocTracePts;
    /// The number of global trace points.
    int m_nTracePts;
    /// A mapping from the local trace points, arranged as all forwards traces
    /// followed by backwards traces, to elemental storage.
    Array<OneD, int> m_fieldToLocTraceMap;
    /// A mapping from local trace points to the global trace. Dimension 0 holds
    /// forward traces, dimension 1 backward.
    Array<OneD, Array<OneD, int> > m_LocTraceToTraceMap;
    /// A mapping holding the type of interpolation needed for each local trace.
    /// Dimension 0 holds forward traces, dimension 1 backward.
    Array<OneD, Array<OneD, InterpLocTraceToTrace> > m_interpTrace;
    /// Interpolation matrices for either 2D edges or first coordinate of 3D
    /// face.
    Array<OneD, Array<OneD, DNekMatSharedPtr> > m_interpTraceI0;
    /// Interpolation matrices for the second coordinate of 3D face, not used in
    /// 2D.
    Array<OneD, Array<OneD, DNekMatSharedPtr> > m_interpTraceI1;
    /// Interpolation points key distributions for each of the local to global
    /// mappings.
    Array<OneD, Array<OneD, TraceInterpPoints> > m_interpPoints;
    /// Mapping to hold first coordinate direction endpoint interpolation, which
    /// can be more optimal if using Gauss-Radau distribution for triangles
    Array<OneD, Array<OneD, Array<OneD, NekDouble> > > m_interpEndPtI0;
    /// Mapping to hold second coordinate direction endpoint interpolation,
    /// which can be more optimal if using Gauss-Radau distribution for
    /// triangles
    Array<OneD, Array<OneD, Array<OneD, NekDouble> > > m_interpEndPtI1;
    /// Number of edges/faces on a 2D/3D element that require interpolation.
    Array<OneD, Array<OneD, int> > m_interpNfaces;
    /// Number of forwards/backwards trace coefficients.
    int m_nTraceCoeffs[2];
    /// Mapping from forwards/backwards trace coefficients to elemental
    /// coefficient storage.
    Array<OneD, Array<OneD, int> > m_traceCoeffsToElmtMap;
    /// Mapping from forwards/backwards trace coefficients to the position of
    /// the trace element in global storage.
    Array<OneD, Array<OneD, int> > m_traceCoeffsToElmtTrace;
    /// Sign array for mapping from forwards/backwards trace coefficients to
    /// local trace storage.
    Array<OneD, Array<OneD, int> > m_traceCoeffsToElmtSign;


    // flag indicates whether the Expasion that are the left&right adjacent to current trace exists 
    Array<OneD, Array<OneD, bool>> m_LeftRightAdjacentExpFlag;
    
    // the Expasion id that are the left&right adjacent to current trace 
    Array<OneD, Array<OneD, int >> m_LeftRightAdjacentExpId;
    

    // the map of every coeff from current trace to the left&right adjacent expasion coeffs 
    Array<OneD, Array<OneD, Array<OneD, int > > > m_TraceceffToLeftRightExpcoeffMap;
    // the sign of every coeff from current trace to the left&right adjacent expasion coeffs 
    Array<OneD, Array<OneD, Array<OneD,int  > > > m_TraceceffToLeftRightExpcoeffSign;

    void TracelocToElmtlocCoeffMap(
        const ExpList &locExp,
        const ExpListSharedPtr &trace);
};

typedef std::shared_ptr<LocTraceToTraceMap> LocTraceToTraceMapSharedPtr;

}
}

#endif
