///////////////////////////////////////////////////////////////////////////////
//
//  File: OutputNekpp.cpp
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
//  Description: Nektar++ file format output.
//
///////////////////////////////////////////////////////////////////////////////

#include <set>
#include <string>
using namespace std;

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/filesystem.hpp>
namespace io = boost::iostreams;

#include <tinyxml.h>
#include <SpatialDomains/MeshGraph.h>
#include <SpatialDomains/PointGeom.h>

#include <NekMeshUtils/MeshElements/Element.h>
#include "OutputNekpp.h"

using namespace Nektar::NekMeshUtils;
using namespace Nektar::SpatialDomains;

namespace Nektar
{
namespace Utilities
{
ModuleKey OutputNekpp::className1 =
    GetModuleFactory().RegisterCreatorFunction(ModuleKey(eOutputModule, "xml"),
                                               OutputNekpp::create,
                                               "Writes a Nektar++ xml file.");

ModuleKey OutputNekpp::className2 =
    GetModuleFactory().RegisterCreatorFunction(ModuleKey(eOutputModule, "nekg"),
                                               OutputNekpp::create,
                                               "Writes a Nektar++ file with hdf5.");

OutputNekpp::OutputNekpp(MeshSharedPtr m) : OutputModule(m)
{
    m_config["test"] = ConfigOption(
        true, "0", "Attempt to load resulting mesh and create meshgraph.");
    m_config["uncompress"] = ConfigOption(true, "0", "Uncompress xml sections");
    m_config["order"] = ConfigOption(false, "-1", "Enforce a polynomial order");
}

OutputNekpp::~OutputNekpp()
{
}

/*
template <typename T> void TestElmts(SpatialDomains::MeshGraphSharedPtr &graph)
{
    const std::map<int, std::shared_ptr<T> > &tmp =
        graph->GetAllElementsOfType<T>();

    SpatialDomains::CurveMap &curvedEdges = graph->GetCurvedEdges();
    SpatialDomains::CurveMap &curvedFaces = graph->GetCurvedFaces();

    for (auto it1 = tmp.begin(), it2 = tmp.end(); it1 != it2; ++it1)
    {
        SpatialDomains::GeometrySharedPtr geom = it1->second;
        geom->FillGeom();
        geom->Reset(curvedEdges, curvedFaces);
    }
}
*/

void OutputNekpp::Process()
{
    if (m_mesh->m_verbose)
    {
        cout << "OutputNekpp: Writing file..." << endl;
    }

    int order = m_config["order"].as<int>();

    if (order != -1)
    {
        m_mesh->MakeOrder(order, LibUtilities::ePolyEvenlySpaced);
    }

    string file = m_config["outfile"].as<string>();
    string ext = boost::filesystem::extension(file);

    // Default to compressed XML output.
    std::string type = "XmlCompressed";


    // Extract the output filename and extension
    string filename = m_config["outfile"].as<string>();

    // Compress output and append .gz extension
    if(boost::iequals(ext, ".xml") && m_config["uncompress"].beenSet)
    {
        type = "Xml";
    }
    else if(boost::iequals(ext, ".nekg"))
    {
        type = "HDF5";
    }

    SpatialDomains::MeshGraphSharedPtr graph =
        SpatialDomains::GetMeshGraphFactory().CreateInstance(type);
    graph->Empty(m_mesh->m_expDim, m_mesh->m_spaceDim);

    TransferVertices(graph);
    TransferEdges(graph);
    TransferFaces(graph);
    TransferElements(graph);
    TransferCurves(graph);
    TransferComposites(graph);
    TransferDomain(graph);

    string out = m_config["outfile"].as<string>();
    graph->WriteGeometry(out, true);

    /*
    // Test the resulting XML file (with a basic test) by loading it
    // with the session reader, generating the MeshGraph and testing if
    // each element is valid.
    if (m_config["test"].beenSet)
    {
        vector<string> filenames(1);
        filenames[0] = filename;

        LibUtilities::SessionReaderSharedPtr vSession =
            LibUtilities::SessionReader::CreateInstance(0, NULL, filenames);
        SpatialDomains::MeshGraphSharedPtr graphShPt =
            SpatialDomains::MeshGraph::Read(vSession);

        TestElmts<SpatialDomains::SegGeom>(graphShPt);
        TestElmts<SpatialDomains::TriGeom>(graphShPt);
        TestElmts<SpatialDomains::QuadGeom>(graphShPt);
        TestElmts<SpatialDomains::TetGeom>(graphShPt);
        TestElmts<SpatialDomains::PrismGeom>(graphShPt);
        TestElmts<SpatialDomains::PyrGeom>(graphShPt);
        TestElmts<SpatialDomains::HexGeom>(graphShPt);
    }
    */
}

void OutputNekpp::TransferVertices(MeshGraphSharedPtr graph)
{
    PointGeomMap &pointMap = graph->GetAllPointGeoms();
    for(auto &it : m_mesh->m_vertexSet)
    {
        PointGeomSharedPtr vert = MemoryManager<PointGeom>::AllocateSharedPtr(
                        m_mesh->m_spaceDim, it->m_id, it->m_x, it->m_y, it->m_z);
        vert->SetGlobalID(it->m_id);
        pointMap[it->m_id] = vert;
    }
}

void OutputNekpp::TransferEdges(MeshGraphSharedPtr graph)
{
    if (m_mesh->m_expDim >= 2)
    {
        SegGeomMap &segMap = graph->GetAllSegGeoms();
        for(auto &it : m_mesh->m_edgeSet)
        {
            PointGeomSharedPtr verts[2] = {graph->GetVertex(it->m_n1->m_id),
                                           graph->GetVertex(it->m_n2->m_id)};
            SegGeomSharedPtr edge = MemoryManager<SegGeom>::AllocateSharedPtr(
                                it->m_id, m_mesh->m_spaceDim, verts);
            segMap[it->m_id] = edge;
        }
    }
}

void OutputNekpp::TransferFaces(MeshGraphSharedPtr graph)
{
    if(m_mesh->m_expDim == 3)
    {
        TriGeomMap &triMap = graph->GetAllTriGeoms();
        QuadGeomMap &quadMap = graph->GetAllQuadGeoms();
        for(auto &it : m_mesh->m_faceSet)
        {
            if(it->m_edgeList.size() == 3)
            {
                SegGeomSharedPtr edges[TriGeom::kNedges] =
                {
                    graph->GetSegGeom(it->m_edgeList[0]->m_id),
                    graph->GetSegGeom(it->m_edgeList[1]->m_id),
                    graph->GetSegGeom(it->m_edgeList[2]->m_id)
                };

                TriGeomSharedPtr tri = MemoryManager<TriGeom>::AllocateSharedPtr(it->m_id, edges);
                triMap[it->m_id] = tri;
            }
            else
            {
                SegGeomSharedPtr edges[QuadGeom::kNedges] =
                {
                    graph->GetSegGeom(it->m_edgeList[0]->m_id),
                    graph->GetSegGeom(it->m_edgeList[1]->m_id),
                    graph->GetSegGeom(it->m_edgeList[2]->m_id),
                    graph->GetSegGeom(it->m_edgeList[3]->m_id)
                };

                QuadGeomSharedPtr quad = MemoryManager<QuadGeom>::AllocateSharedPtr(it->m_id, edges);
                quadMap[it->m_id] = quad;
            }
        }
    }
}

void OutputNekpp::TransferElements(MeshGraphSharedPtr graph)
{
    vector<ElementSharedPtr> &elmt = m_mesh->m_element[m_mesh->m_expDim];

    SegGeomMap &segMap = graph->GetAllSegGeoms();
    TriGeomMap &triMap = graph->GetAllTriGeoms();
    QuadGeomMap &quadMap = graph->GetAllQuadGeoms();
    TetGeomMap &tetMap = graph->GetAllTetGeoms();
    PyrGeomMap &pyrMap = graph->GetAllPyrGeoms();
    PrismGeomMap &prismMap = graph->GetAllPrismGeoms();
    HexGeomMap &hexMap = graph->GetAllHexGeoms();

    for (int i = 0; i < elmt.size(); ++i)
    {
        switch (elmt[i]->GetTag()[0])
        {
            case 'S':
            {
                int id = elmt[i]->GetId();
                PointGeomSharedPtr vertices[2] = {
                    graph->GetVertex(elmt[i]->GetVertex(0)->m_id),
                    graph->GetVertex(elmt[i]->GetVertex(1)->m_id)};
                segMap[id] = MemoryManager<SegGeom>::AllocateSharedPtr(id, m_mesh->m_spaceDim, vertices);
            }
            break;
            case 'T':
            {
                int id = elmt[i]->GetId();
                SegGeomSharedPtr edges[TriGeom::kNedges] = {
                        graph->GetSegGeom(elmt[i]->GetEdge(0)->m_id),
                        graph->GetSegGeom(elmt[i]->GetEdge(1)->m_id),
                        graph->GetSegGeom(elmt[i]->GetEdge(2)->m_id)};

                triMap[id] = MemoryManager<TriGeom>::AllocateSharedPtr(id, edges);
            }
            break;
            case 'Q':
            {
                int id = elmt[i]->GetId();
                SegGeomSharedPtr edges[QuadGeom::kNedges] = {
                        graph->GetSegGeom(elmt[i]->GetEdge(0)->m_id),
                        graph->GetSegGeom(elmt[i]->GetEdge(1)->m_id),
                        graph->GetSegGeom(elmt[i]->GetEdge(2)->m_id),
                        graph->GetSegGeom(elmt[i]->GetEdge(3)->m_id)};

                quadMap[id] = MemoryManager<QuadGeom>::AllocateSharedPtr(id, edges);
            }
            break;
            case 'A':
            {
                int id = elmt[i]->GetId();
                TriGeomSharedPtr tfaces[4];
                for(int j = 0; j < 4; ++j)
                {
                    Geometry2DSharedPtr face =
                        graph->GetGeometry2D(elmt[i]->GetFace(j)->m_id);
                    tfaces[j] = static_pointer_cast<TriGeom>(face);
                }

                tetMap[id] = MemoryManager<TetGeom>::AllocateSharedPtr(id, tfaces);
            }
            break;
            case 'P':
            {
                Geometry2DSharedPtr faces[5];

                int id = elmt[i]->GetId();
                for(int j = 0; j < 5; ++j)
                {
                    Geometry2DSharedPtr face =
                        graph->GetGeometry2D(elmt[i]->GetFace(j)->m_id);

                    if (face->GetShapeType() ==
                                LibUtilities::eTriangle)
                    {
                        faces[j] = static_pointer_cast<TriGeom>(face);
                    }
                    else if (face->GetShapeType() ==
                                LibUtilities::eQuadrilateral)
                    {
                        faces[j] = static_pointer_cast<QuadGeom>(face);
                    }
                }
                pyrMap[id] = MemoryManager<PyrGeom>::AllocateSharedPtr(id, faces);
            }
            break;
            case 'R':
            {
                Geometry2DSharedPtr faces[5];

                int id = elmt[i]->GetId();
                for(int j = 0; j < 5; ++j)
                {
                    Geometry2DSharedPtr face =
                        graph->GetGeometry2D(elmt[i]->GetFace(j)->m_id);

                    if (face->GetShapeType() ==
                                LibUtilities::eTriangle)
                    {
                        faces[j] = static_pointer_cast<TriGeom>(face);
                    }
                    else if (face->GetShapeType() ==
                                LibUtilities::eQuadrilateral)
                    {
                        faces[j] = static_pointer_cast<QuadGeom>(face);
                    }
                }
                prismMap[id] = MemoryManager<PrismGeom>::AllocateSharedPtr(id, faces);
            }
            break;
            case 'H':
            {
                QuadGeomSharedPtr faces[6];

                int id = elmt[i]->GetId();
                for(int j = 0; j < 6; ++j)
                {
                    Geometry2DSharedPtr face =
                        graph->GetGeometry2D(elmt[i]->GetFace(j)->m_id);
                    faces[j] = static_pointer_cast<QuadGeom>(face);
                }

                hexMap[id] = MemoryManager<HexGeom>::AllocateSharedPtr(id, faces);
            }
            break;
            default:
                ASSERTL0(false, "Unknown element type");
        }
    }
}

void OutputNekpp::TransferCurves(MeshGraphSharedPtr graph)
{
    CurveMap &edges = graph->GetCurvedEdges();

    int edgecnt = 0;

    for(auto &it : m_mesh->m_edgeSet)
    {
        if(it->m_edgeNodes.size() > 0)
        {
            CurveSharedPtr curve = MemoryManager<Curve>::AllocateSharedPtr(it->m_id,
                                            it->m_curveType);
            vector<NodeSharedPtr> ns;
            it->GetCurvedNodes(ns);
            for(int i = 0; i < ns.size(); i++)
            {
                PointGeomSharedPtr vert = MemoryManager<PointGeom>::AllocateSharedPtr(
                    m_mesh->m_expDim, edgecnt, ns[i]->m_x, ns[i]->m_y, ns[i]->m_z);
                curve->m_points.push_back(vert);
            }

            edges[it->m_id] = curve;
            edgecnt++;
        }
    }

    CurveMap &faces = graph->GetCurvedFaces();

    int facecnt = 0;

    for(auto &it : m_mesh->m_faceSet)
    {
        if(it->m_faceNodes.size() > 0)
        {
            CurveSharedPtr curve = MemoryManager<Curve>::AllocateSharedPtr(it->m_id,
                                            it->m_curveType);
            vector<NodeSharedPtr> ns;
            it->GetCurvedNodes(ns);
            for(int i = 0; i < ns.size(); i++)
            {
                PointGeomSharedPtr vert = MemoryManager<PointGeom>::AllocateSharedPtr(
                    m_mesh->m_expDim, facecnt, ns[i]->m_x, ns[i]->m_y, ns[i]->m_z);
                curve->m_points.push_back(vert);
            }

            faces[it->m_id] = curve;
            facecnt++;
        }
    }
}

void OutputNekpp::TransferComposites(MeshGraphSharedPtr graph)
{
    SpatialDomains::CompositeMap &comps = graph->GetComposites();
    map<int, string> &compLabels = graph->GetCompositesLabels();

    int j = 0;

    for(auto &it : m_mesh->m_composite)
    {
        if(it.second->m_items.size() > 0)
        {
            int indx = it.second->m_id;
            SpatialDomains::CompositeSharedPtr curVector =
                            MemoryManager<SpatialDomains::Composite>::AllocateSharedPtr();

            if(it.second->m_label.size())
            {
                compLabels[indx] = it.second->m_label;
            }

            switch (it.second->m_tag[0])
            {
                case 'V':
                {
                    PointGeomMap &pointMap = graph->GetAllPointGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(pointMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'S':
                case 'E':
                {
                    SegGeomMap &segMap = graph->GetAllSegGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(segMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'Q':
                {
                    QuadGeomMap &quadMap = graph->GetAllQuadGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(quadMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'T':
                {
                    TriGeomMap &triMap = graph->GetAllTriGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(triMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'F':
                {
                    QuadGeomMap &quadMap = graph->GetAllQuadGeoms();
                    TriGeomMap &triMap = graph->GetAllTriGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        auto f = quadMap.find(it.second->m_items[i]->GetId());
                        if(f != quadMap.end())
                        {
                            curVector->m_geomVec.push_back(f->second);
                        }
                        else
                        {
                            auto f2 = triMap.find(it.second->m_items[i]->GetId());
                            curVector->m_geomVec.push_back(f2->second);
                        }
                    }
                }
                break;
                case 'A':
                {
                    TetGeomMap &tetMap = graph->GetAllTetGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(tetMap[it.second->m_items[i]->GetId()]);
                    };
                }
                break;
                case 'P':
                {
                    PyrGeomMap &pyrMap = graph->GetAllPyrGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(pyrMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'R':
                {
                    PrismGeomMap &prismMap = graph->GetAllPrismGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(prismMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                case 'H':
                {
                    HexGeomMap &hexMap = graph->GetAllHexGeoms();
                    for(int i = 0; i < it.second->m_items.size(); i++)
                    {
                        curVector->m_geomVec.push_back(hexMap[it.second->m_items[i]->GetId()]);
                    }
                }
                break;
                default:
                    ASSERTL0(false, "Unknown element type");
            }

            comps[indx] = curVector;
        }
        j++;
    }
}

void OutputNekpp::TransferDomain(MeshGraphSharedPtr graph)
{
    vector<SpatialDomains::CompositeMap> &domain = graph->GetDomain();

    string list;

    for(auto &it : m_mesh->m_composite)
    {
        if(it.second->m_items[0]->GetDim() == m_mesh->m_expDim)
        {
            if(list.length() > 0)
            {
                list += ",";
            }
            list += boost::lexical_cast<string>(it.second->m_id);
        }
    }

    SpatialDomains::CompositeMap fullDomain;
    graph->GetCompositeList(list, fullDomain);
    domain.push_back(fullDomain);
}

}
}
