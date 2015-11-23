////////////////////////////////////////////////////////////////////////////////
//
// File: Interpolator.cpp
//
// For more information, please see: http://www.nektar.info/
//
// The MIT License
//
// Copyright (c) 2015 Kilian Lackhove
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
// Description: Interpolator
//
////////////////////////////////////////////////////////////////////////////////

#include <SolverUtils/Interpolator.h>

namespace Nektar
{
namespace SolverUtils
{

/**
 * @brief Compute the weights for an interpolation of the field values to physical points
 *
 * @param physCoords    coordinates of the physical points
 * @param coord_id      id of the coordinate to use for interpolation.
 *
 * Set coord_id to -1 to use n-D interpolation for an n-dimensional field.
 * The most suitable algorithm is chosen automatically.
 */
void Interpolator::CalcWeights(
            const LibUtilities::PtsFieldSharedPtr ptsInField, LibUtilities::PtsFieldSharedPtr &ptsOutField)
{
    ASSERTL0(ptsInField->GetNFields() == ptsOutField->GetNFields(), "number of fields does not match");
    ASSERTL0(ptsInField->GetDim() <= m_dim, "too many dimesions in inField");
    ASSERTL0(ptsOutField->GetDim() <= m_dim, "too many dimesions in outField");

    m_ptsInField = ptsInField;
    m_ptsOutField = ptsOutField;

    int nOutPts = m_ptsOutField->GetNpoints();
    int lastProg = 0;

    m_weights = Array<OneD, Array<OneD, float> >(nOutPts);
    m_neighInds = Array<OneD, Array<OneD, unsigned int> >(nOutPts);

    std::vector<PtsPointPair> inPoints;
    for (int i = 0; i < m_ptsInField->GetNpoints(); ++i)
    {
        Array<OneD, NekDouble> coords(3, 0.0);
        for (int j = 0; j < m_ptsInField->GetDim(); ++j)
        {
            coords[j] = m_ptsInField->GetPointVal(j,i);
        }
        inPoints.push_back(PtsPointPair(BPoint(coords[0], coords[1], coords[2]), i));
    }
    m_rtree = MemoryManager<PtsRtree>::AllocateSharedPtr();
    m_rtree->insert(inPoints.begin(), inPoints.end());

    // set a default method
    if(m_method == eNoMethod)
    {
        if (m_ptsInField->GetDim() == 1 || m_coordId >= 0)
        {
            m_method = eQuadratic;
        }
        else
        {
            m_method = eShepard;
        }
    }

    switch (m_method)
    {
        case eNearestNeighbour:
        {
            for (int i = 0; i < nOutPts; ++i)
            {
                Array<OneD, NekDouble> tmp(m_dim, 0.0);
                for (int j = 0; j < m_ptsOutField->GetDim(); ++j)
                {
                    tmp[j] = m_ptsOutField->GetPointVal(j,i);
                }
                PtsPoint searchPt(i, tmp, 1E30);

                CalcW_NNeighbour(searchPt);

                int progress = int(100 * i / nOutPts);
                if (m_progressCallback && progress > lastProg)
                {
                    m_progressCallback(i, nOutPts);
                    lastProg = progress;
                }
            }

            break;
        }

        case eQuadratic:
        {
            ASSERTL0(m_ptsInField->GetDim() == 1 || m_coordId >= 0, "not implemented");

            if (m_ptsInField->GetDim() == 1)
            {
                m_coordId = 0;
            }

            for (int i = 0; i < nOutPts; ++i)
            {
                Array<OneD, NekDouble> tmp(m_dim, 0.0);
                for (int j = 0; j < m_ptsOutField->GetDim(); ++j)
                {
                    tmp[j] = m_ptsOutField->GetPointVal(j,i);
                }
                PtsPoint searchPt(i, tmp, 1E30);


                if (m_ptsInField->GetNpoints() <= 2)
                {
                    CalcW_Linear(searchPt, m_coordId);
                }
                else
                {
                    CalcW_Quadratic(searchPt, m_coordId);
                }

                int progress = int(100 * i / nOutPts);
                if (m_progressCallback && progress > lastProg)
                {
                    m_progressCallback(i, nOutPts);
                    lastProg = progress;
                }
            }

            break;
        }

        case eShepard:
        {
            for (int i = 0; i < nOutPts; ++i)
            {
                Array<OneD, NekDouble> tmp(m_dim, 0.0);
                for (int j = 0; j < m_ptsOutField->GetDim(); ++j)
                {
                    tmp[j] = m_ptsOutField->GetPointVal(j,i);
                }
                PtsPoint searchPt(i, tmp, 1E30);

                CalcW_Shepard(searchPt);

                int progress = int(100 * i / nOutPts);
                if (m_progressCallback && progress > lastProg)
                {
                    m_progressCallback(i, nOutPts);
                    lastProg = progress;
                }
            }

            break;
        }

        case eGauss:
        {
            ASSERTL0(m_filtWidth > NekConstants::kNekZeroTol, "No filter width set");
            NekDouble sigma = m_filtWidth * 0.4246609001;

            for (int i = 0; i < nOutPts; ++i)
            {
                Array<OneD, NekDouble> tmp(m_dim, 0.0);
                for (int j = 0; j < m_ptsOutField->GetDim(); ++j)
                {
                    tmp[j] = m_ptsOutField->GetPointVal(j,i);
                }
                PtsPoint searchPt(i, tmp, 1E30);

                CalcW_Gauss(searchPt, sigma);

                int progress = int(100 * i / nOutPts);
                if (m_progressCallback && progress > lastProg)
                {
                    m_progressCallback(i, nOutPts);
                    lastProg = progress;
                }
            }

            break;
        }

        default:
            ASSERTL0(false, "Invalid interpolation m_method");
            break;
    }
}


/**
 * @brief Perform the interpolate of field values to physical points
 *
 * @param intFields     interpolated field at the physical points
 *
 * The weights must have already been computed by @CalcWeights or set by
 * @SetWeights.
 */
void Interpolator::Interpolate(
            const LibUtilities::PtsFieldSharedPtr ptsInField, LibUtilities::PtsFieldSharedPtr &ptsOutField)
{
    ASSERTL0(ptsInField->GetNFields() == ptsOutField->GetNFields(), "number of fields does not match");
    ASSERTL0(ptsInField->GetDim() <= m_dim, "too many dimesions in inField");
    ASSERTL0(ptsOutField->GetDim() <= m_dim, "too many dimesions in outField");

    m_ptsInField = ptsInField;
    m_ptsOutField = ptsOutField;

    if ( m_weights.num_elements() == 0)
    {
        CalcWeights(m_ptsInField, m_ptsOutField);
    }

    ASSERTL0(m_weights.num_elements() == m_ptsOutField->GetNpoints(), "weights dimension mismatch");

    int nFields = m_ptsOutField->GetNFields();
    int nOutPts = m_ptsOutField->GetNpoints();
    int inDim = m_ptsInField->GetDim();

    // interpolate points and transform
    for (int i = 0; i < nFields; ++i)
    {
        for (int j = 0; j < nOutPts; ++j)
        {
            NekDouble val = 0.0;
            int nPts = m_weights[j].num_elements();
            for (int k = 0; k < nPts; ++k)
            {
                unsigned int nIdx = m_neighInds[j][k];
                val += m_weights[j][k] * m_ptsInField->GetPointVal(inDim + i, nIdx);
            }
            m_ptsOutField->SetPointVal(i,j, val);
        }
    }
}

void Interpolator::Interpolate(const vector< MultiRegions::ExpListSharedPtr > expInField, vector< MultiRegions::ExpListSharedPtr > &expOutField)
{
    ASSERTL0(false, "not implemented yet");
}


void Interpolator::Interpolate(const vector< MultiRegions::ExpListSharedPtr > expInField, LibUtilities::PtsFieldSharedPtr &ptsOutField)
{
    ASSERTL0(expInField.size() == ptsOutField->GetNFields(), "number of fields does not match");
    ASSERTL0(expInField[0]->GetCoordim(0) <= m_dim, "too many dimesions in inField");
    ASSERTL0(ptsOutField->GetDim() <= m_dim, "too many dimesions in outField");

    m_expInField = expInField;
    m_ptsOutField = ptsOutField;

    int nInDim = expInField[0]->GetCoordim(0);
    int nOutPts = m_ptsOutField->GetNpoints();
    int lastProg = 0;

    m_weights = Array<OneD, Array<OneD, float> >(nOutPts);
    m_neighInds = Array<OneD, Array<OneD, unsigned int> >(nOutPts);

    for (int i = 0; i < nOutPts; ++i)
    {
        Array<OneD, NekDouble> Lcoords(nInDim, 0.0);
        Array<OneD, NekDouble> coords(nInDim, 0.0);
        for (int j = 0; j < m_ptsOutField->GetDim(); ++j)
        {
            coords[j] = m_ptsOutField->GetPointVal(j,i);
        }

        // Obtain Element and LocalCoordinate to interpolate
        int elmtid = m_expInField[0]->GetExpIndex(coords, Lcoords, 1e-3);

        if(elmtid >= 0)
        {
            int offset = m_expInField[0]->GetPhys_Offset(m_expInField[0]->
                                               GetOffset_Elmt_Id(elmtid));

            for (int f = 0; f < m_expInField.size(); ++f)
            {
                NekDouble value = m_expInField[f]->GetExp(elmtid)->
                    StdPhysEvaluate(Lcoords, m_expInField[f]->GetPhys() +offset);

                if ((boost::math::isnan)(value))
                {
                    ASSERTL0(false, "new value is not a number");
                }
                else
                {
                    m_ptsOutField->SetPointVal(f, i, value);
                }
            }
        }

        int progress = int(100 * i / nOutPts);
        if (m_progressCallback && progress > lastProg)
        {
            m_progressCallback(i, nOutPts);
            lastProg = progress;
        }
    }
}


void Interpolator::Interpolate(const LibUtilities::PtsFieldSharedPtr ptsInField, vector< MultiRegions::ExpListSharedPtr > &expOutField)
{
    ASSERTL0(expOutField.size() == ptsInField->GetNFields(), "number of fields does not match");
    ASSERTL0(ptsInField->GetDim() <= m_dim, "too many dimesions in inField");
    ASSERTL0(expOutField[0]->GetCoordim(0) <= m_dim, "too many dimesions in outField");

    m_ptsInField = ptsInField;
    m_expOutField = expOutField;

    int nFields = max( (int) ptsInField->GetNFields(), (int) m_expOutField.size());
    int nOutPts = m_expOutField[0]->GetTotPoints();
    int outDim = m_expOutField[0]->GetCoordim(0);

    // create intermediate Ptsfield that matches the expOutField
    Array<OneD, Array<OneD, NekDouble> > pts(outDim + nFields);
    for (int i = 0; i < outDim + nFields; ++i)
    {
        pts[i] = Array<OneD,  NekDouble>(nOutPts);
    }
    if (outDim == 1)
    {
        m_expOutField[0]->GetCoords(pts[0]);
    }
    else if (outDim == 2)
    {
        m_expOutField[0]->GetCoords(pts[0], pts[1]);
    }
    else if (outDim == 3)
    {
        m_expOutField[0]->GetCoords(pts[0], pts[1], pts[2]);
    }
    LibUtilities::PtsFieldSharedPtr tmpPts =
            MemoryManager<LibUtilities::PtsField>::AllocateSharedPtr(outDim, pts);
    //TODO: no interpolation needed here, we might as well just take the physical values of the expansion
    Interpolator interp1;
    interp1.Interpolate(m_expOutField, tmpPts);

    // interpolate m_ptsInField to this intermediate field
    Interpolator interp2;
    interp2.Interpolate(m_ptsInField, tmpPts);

    // write the intermediate fields data into our expOutField
    for (int i = 0; i < nFields; i++)
    {
        for (int j = 0; j < nOutPts; ++j)
        {
            m_expOutField[i]->UpdatePhys()[j] = tmpPts->GetPointVal(i, j);
        }
    }

    //TODO: figure out a way to show a reasonable progreesbar
}


int Interpolator::GetDim() const
{
    return m_dim;
}

int Interpolator::GetCoordId() const
{
    return m_coordId;
}


NekDouble Interpolator::GetFiltWidth() const
{
    return m_filtWidth;
}


InterpMethod Interpolator::GetInterpMethod() const
{
    return m_method;
}


LibUtilities::PtsFieldSharedPtr Interpolator::GetInField() const
{
    return m_ptsInField;
}


LibUtilities::PtsFieldSharedPtr Interpolator::GetOutField() const
{
    return m_ptsOutField;
}


/**
 * @brief Compute interpolation weights for a physical point using Gauss filtering
 *
 * @param physPtIdx         The index of the physical point in its storage array
 * @param physPt            The coordinates of the physical point
 *
 */
void Interpolator::CalcW_Gauss(const PtsPoint &searchPt, const NekDouble sigma)
{
    NekDouble ts2 = 2 * sigma * sigma;
    NekDouble fac = 1.0 / (sigma * sqrt(2 * M_PI));
    fac = pow(fac, m_ptsInField->GetDim());

    // find nearest neighbours
    int maxPts = 500;
    vector<PtsPoint > neighbourPts;
    FindNeighbours(searchPt, neighbourPts, 1.96 * sigma);
    int numPts = min( (int) neighbourPts.size(), maxPts);

    // handle the case that there was no point within 1.96 * sigma
    if (numPts == 0)
    {
        m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (0);
        m_weights[searchPt.idx] = Array<OneD, float> (0);

        return;
    }

    m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (numPts);
    for (int i = 0; i < numPts; i++)
    {
        m_neighInds[searchPt.idx][i] = neighbourPts.at(i).idx;
    }

    m_weights[searchPt.idx] = Array<OneD, float> (numPts, 0.0);

    NekDouble wSum = 0.0;
    for (int i = 0; i < numPts; ++i)
    {
        m_weights[searchPt.idx][i] = fac * exp(-1 * pow(neighbourPts[i].dist, 2.0f) / ts2);
        wSum += m_weights[searchPt.idx][i];
    }

    for (int i = 0; i < numPts; ++i)
    {
        m_weights[searchPt.idx][i] = m_weights[searchPt.idx][i] / wSum;
    }

    ASSERTL0(Vmath::Nnan(numPts, m_weights[searchPt.idx], 1) == 0, "NaN found in weights");
}


/**
 * @brief Compute interpolation weights for a 1D physical point using linear
 * interpolation.
 *
 * @param physPtIdx         The index of the physical point in its storage array
 * @param coord             The coordinate of the physical point
 */

void Interpolator::CalcW_Linear(const PtsPoint &searchPt, int m_coordId)
{
    int npts = m_ptsInField->GetNpoints();
    int i;

    NekDouble coord = searchPt.coords[m_coordId];

    int numPts = 2;
    m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (numPts);
    m_weights[searchPt.idx] = Array<OneD, float> (numPts, 0.0);

    for (i = 0; i < npts - 1; ++i)
    {
        if ((m_ptsInField->GetPointVal(0,i) <= coord) && (coord <= m_ptsInField->GetPointVal(0,i + 1)))
        {
            NekDouble pdiff = m_ptsInField->GetPointVal(0,i+1) - m_ptsInField->GetPointVal(0,i);

            m_neighInds[searchPt.idx][0] = i;
            m_neighInds[searchPt.idx][1] = i + 1;

            m_weights[searchPt.idx][0] = (m_ptsInField->GetPointVal(0,i+1) - coord) / pdiff;
            m_weights[searchPt.idx][1] = (coord - m_ptsInField->GetPointVal(0,i)) / pdiff;

            break;
        }
    }
    ASSERTL0(i != npts - 1, "Failed to find coordinate " +
             boost::lexical_cast<string>(coord) +
             " within provided input points");
};


void Interpolator::CalcW_NNeighbour(const PtsPoint &searchPt)
{
    // find nearest neighbours
    vector<PtsPoint > neighbourPts;
    FindNNeighbours(searchPt, neighbourPts, 1);

    m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (1, neighbourPts.at(0).idx);
    m_weights[searchPt.idx] = Array<OneD, float> (1, 1.0);
}


/**
 * @brief Compute interpolation weights for a physical point using a modified
 * Shepard algorithm.
 *
 * @param physPtIdx         The index of the physical point in its storage array
 * @param physPt            The coordinates of the physical point
 *
 * The algorithm is based on Shepard, D. (1968). A two-dimensional interpolation
 * function for irregularly-spaced data. Proceedings of the 1968 23rd ACM
 * National Conference. pp. 517–524.
 *
 * In order to save memory, for n dimesnions, only 2^n points are considered.
 * Contrary to Shepard, we use a fixed number of points with fixed weighting
 * factors 1/d^n.
 */

void Interpolator::CalcW_Shepard(const PtsPoint &searchPt)
{
    // find nearest neighbours
    vector<PtsPoint > neighbourPts;
    int numPts = pow(float(2), m_ptsInField->GetDim());
    numPts = min(numPts, int(m_ptsInField->GetNpoints() / 2));
    FindNNeighbours(searchPt, neighbourPts, numPts);

    m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (numPts);
    for (int i = 0; i < numPts; i++)
    {
        m_neighInds[searchPt.idx][i] = neighbourPts.at(i).idx;
    }

    m_weights[searchPt.idx] = Array<OneD, float> (numPts, 0.0);

    // In case d < kVertexTheSameDouble ( d^2 < kNekSqrtTol), use the exact
    // point and return
    for (int i = 0; i < numPts; ++i)
    {
        if (neighbourPts[i].dist <= NekConstants::kNekZeroTol)
        {
            m_weights[searchPt.idx][i] = 1.0;
            return;
        }
    }

    NekDouble wSum = 0.0;
    for (int i = 0; i < numPts; ++i)
    {
        m_weights[searchPt.idx][i] = 1 / pow(double(neighbourPts[i].dist),
                                          double(m_ptsInField->GetDim()));
        wSum += m_weights[searchPt.idx][i];
    }

    for (int i = 0; i < numPts; ++i)
    {
        m_weights[searchPt.idx][i] = m_weights[searchPt.idx][i] / wSum;
    }

    ASSERTL0(Vmath::Nnan(numPts, m_weights[searchPt.idx], 1) == 0, "NaN found in weights");

}

/**
* @brief Compute interpolation weights for a 1D physical point using quadratic
* interpolation.
*
* @param physPtIdx         The index of the physical point in its storage array
* @param coord             The coordinate of the physical point
*/

void Interpolator::CalcW_Quadratic(const PtsPoint &searchPt, int m_coordId)
{
    int npts = m_ptsInField->GetNpoints();
    int i;

    NekDouble coord = searchPt.coords[m_coordId];

    int numPts = 3;
    m_neighInds[searchPt.idx] = Array<OneD, unsigned int> (numPts);
    m_weights[searchPt.idx] = Array<OneD, float> (numPts, 0.0);

    for (i = 0; i < npts - 1; ++i)
    {
        if ((m_ptsInField->GetPointVal(0,i) <= coord) && (coord <= m_ptsInField->GetPointVal(0,i+1)))
        {
            NekDouble pdiff = m_ptsInField->GetPointVal(0,i+1) - m_ptsInField->GetPointVal(0,i);
            NekDouble h1, h2, h3;

            if (i < npts - 2)
            {
                // forwards stencil
                NekDouble pdiff2 = m_ptsInField->GetPointVal(0,i+2) - m_ptsInField->GetPointVal(0,i+1);

                h1 = (m_ptsInField->GetPointVal(0,i+1) - coord)
                     * (m_ptsInField->GetPointVal(0,i+2) - coord)
                     / (pdiff * (pdiff + pdiff2));
                h2 = (coord - m_ptsInField->GetPointVal(0,i))
                     * (m_ptsInField->GetPointVal(0,i+2) - coord)
                     / (pdiff * pdiff2);
                h3 = (coord - m_ptsInField->GetPointVal(0,i))
                     * (coord - m_ptsInField->GetPointVal(0,i+1))
                     / ((pdiff + pdiff2) * pdiff2);

                m_neighInds[searchPt.idx][0] = i;
                m_neighInds[searchPt.idx][1] = i + 1;
                m_neighInds[searchPt.idx][2] = i + 2;
            }
            else
            {
                // backwards stencil
                NekDouble pdiff2 = m_ptsInField->GetPointVal(0,i) - m_ptsInField->GetPointVal(0,i-1);

                h1 = (m_ptsInField->GetPointVal(0,i+1) - coord)
                     * (coord - m_ptsInField->GetPointVal(0,i-1))
                     / (pdiff * pdiff2);
                h2 = (coord - m_ptsInField->GetPointVal(0,i))
                     * (coord - m_ptsInField->GetPointVal(0,i-1))
                     / (pdiff * (pdiff + pdiff2));
                h3 = (m_ptsInField->GetPointVal(0,i) - coord)
                     * (m_ptsInField->GetPointVal(0,i+1) - coord)
                     / ((pdiff + pdiff2) * pdiff);

                m_neighInds[searchPt.idx][0] = i;
                m_neighInds[searchPt.idx][1] = i + 1;
                m_neighInds[searchPt.idx][2] = i - 1;
            }


            m_weights[searchPt.idx][0] = h1;
            m_weights[searchPt.idx][1] = h2;
            m_weights[searchPt.idx][2] = h3;

            break;
        }
    }
    ASSERTL0(i != npts - 1, "Failed to find coordinate " +
             boost::lexical_cast<string>(coord) +
             " within provided input points");
};


/**
 * @brief Find nearest neighbours using a brute-force "algorithm".
 *
 * @param physPt              Coordinates of the physical point its neighbours
 * we are looking for
 * @param neighbourPts        The points we found
 * @param numPts              The number of points to find
 *
 * This iterates over all points, computes the (squared) euclidean distance
 * and chooses the numPts closest points. Thus, its very expensive and
 * inefficient.
 */

void Interpolator::FindNNeighbours(const PtsPoint &searchPt,
                               vector< PtsPoint > &neighbourPts,
                               const unsigned int numPts)
{
    std::vector<PtsPointPair> result;
    BPoint searchBPoint(searchPt.coords[0], searchPt.coords[1], searchPt.coords[2]);
    m_rtree->query(bgi::nearest(searchBPoint, numPts), std::back_inserter(result));

    // massage into or own format
    for(typename vector<PtsPointPair>::iterator it = result.begin(); it != result.end(); ++it)
    {
        int idx = it->second;
        Array<OneD, NekDouble> coords(m_dim, 0.0);
        for (int j = 0; j < m_ptsInField->GetDim(); ++j)
        {
            coords[j] = m_ptsInField->GetPointVal(j, idx);
        }
        NekDouble d = bg::distance(searchBPoint, it->first);
        neighbourPts.push_back(PtsPoint(idx, coords, d));
    }

    sort(neighbourPts.begin(), neighbourPts.end());
}


/**
 * @brief Find nearest neighbours using a brute-force "algorithm".
 *
 * @param physPt              Coordinates of the physical point its neighbours
 * we are looking for
 * @param neighbourPts        The points we found
 * @param dist                The max distance of a neighbour point
 *
 * This iterates over all points, computes the (squared) euclidean distance
 * and chooses the points within the defined distance. Thus, its very expensive
 * and inefficient.
 */

void Interpolator::FindNeighbours(const PtsPoint &searchPt,
                              vector<PtsPoint > &neighbourPts,
                              const NekDouble dist)
{
    BPoint searchBPoint(searchPt.coords[0], searchPt.coords[1], searchPt.coords[2]);
    BPoint bbMin(searchPt.coords[0] - dist, searchPt.coords[1] - dist, searchPt.coords[2] - dist);
    BPoint bbMax(searchPt.coords[0] + dist, searchPt.coords[1] + dist, searchPt.coords[2] + dist);
    bg::model::box<BPoint> bbox(bbMin, bbMax);

    // find points within the distance box
    std::vector<PtsPointPair> result;
    m_rtree->query(bgi::within(bbox), std::back_inserter(result));

    // massage into or own format
    for(typename vector<PtsPointPair>::iterator it = result.begin(); it != result.end(); ++it)
    {
        int idx = it->second;
        Array<OneD, NekDouble> coords(m_dim, 0.0);
        for (int j = 0; j < m_ptsInField->GetDim(); ++j)
        {
            coords[j] = m_ptsInField->GetPointVal(j, idx);
        }
        NekDouble d = bg::distance(searchBPoint, it->first);

        // discard points beyonf dist
        if (d <= dist)
        {
            neighbourPts.push_back(PtsPoint(idx, coords, dist));
        }
    }

    sort(neighbourPts.begin(), neighbourPts.end());
}


}
}
