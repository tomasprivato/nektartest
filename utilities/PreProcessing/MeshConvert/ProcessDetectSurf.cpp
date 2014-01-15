////////////////////////////////////////////////////////////////////////////////
//
//  File: ProcessDetectSurf.cpp
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
//  Description: Extract one or more surfaces from mesh.
//
////////////////////////////////////////////////////////////////////////////////

#include "MeshElements.h"
#include "ProcessDetectSurf.h"

#include <SpatialDomains/MeshGraph.h>
#include <LibUtilities/Foundations/ManagerAccess.h>

#include <vector>
using namespace std;

namespace Nektar
{
    namespace Utilities
    {
        ModuleKey ProcessDetectSurf::className = 
            GetModuleFactory().RegisterCreatorFunction(
                ModuleKey(eProcessModule, "detect"), ProcessDetectSurf::create,
                "Process elements based on values of Jacobian.");

        ProcessDetectSurf::ProcessDetectSurf(MeshSharedPtr m) : ProcessModule(m)
        {
            config["vol"] = ConfigOption(false, "-1",
                "Tag identifying surface to process.");
        }

        ProcessDetectSurf::~ProcessDetectSurf()
        {
        }
        
        struct EdgeInfo {
            EdgeInfo() : count(0) {}
            int           count;
            EdgeSharedPtr edge;
            unsigned int  group;
        };

        void ProcessDetectSurf::Process()
        {
            if (m->expDim > 2)
            {
                cerr << "Surface detection only implemented for 2D meshes" << endl;
                return;
            }

            int i, j;
            string surf = config["vol"].as<string>();

            // Obtain vector of surface IDs from string.
            vector<unsigned int> surfs;
            if (surf != "-1")
            {
                ParseUtils::GenerateSeqVector(surf.c_str(), surfs);
                sort(surfs.begin(), surfs.end());
            }

            // If we're running in verbose mode print out a list of surfaces.
            if (m->verbose)
            {
                cout << "ProcessDetectSurf: detecting surfaces";
                if (surfs.size() > 0)
                {
                    cout << " for surface" << (surfs.size() == 1 ? "" : "s")
                         << " " << surf << endl;
                }
            }

            vector<ElementSharedPtr> &el = m->element[m->expDim];
            map<int, EdgeInfo> edgeCount;
            set<int> doneIds;
            map<int, int> idMap;

            // Iterate over list of surface elements.
            for (i = 0; i < el.size(); ++i)
            {
                // Work out whether this lies on our surface of interest.
                if (surfs.size() > 0)
                {
                    vector<int> inter, tags = el[i]->GetTagList();

                    sort(tags.begin(), tags.end());
                    set_intersection(surfs.begin(), surfs.end(),
                                     tags .begin(), tags .end(),
                                     back_inserter(inter));
                
                    // It doesn't continue to next element.
                    if (inter.size() != 1)
                    {
                        continue;
                    }
                }
                
                // List all edges.
                ElementSharedPtr elmt = el[i];
                for (j = 0; j < elmt->GetEdgeCount(); ++j)
                {
                    EdgeSharedPtr e = elmt->GetEdge(j);
                    int eId = e->id;
                    edgeCount[eId].count++;
                    edgeCount[eId].edge = e;
                }

                doneIds.insert(elmt->GetId());
                ASSERTL0(idMap.count(elmt->GetId()) == 0, "Shouldn't happen");
                idMap[elmt->GetId()] = i;
            }

            CompositeMap::iterator cIt;
            unsigned int maxId = 0;

            for (cIt = m->composite.begin(); cIt != m->composite.end(); ++cIt)
            {
                maxId = std::max(cIt->first, maxId);
            }

            ++maxId;

            map<int, EdgeInfo>::iterator eIt;

            while (doneIds.size() > 0)
            {
                ElementSharedPtr start
                    = m->element[m->expDim][idMap[*(doneIds.begin())]];

                vector<ElementSharedPtr> block;
                FindContiguousSurface(start, doneIds, block);
                ASSERTL0(block.size() > 0, "Contiguous block not found");

                // Loop over all edges in block.
                for (i = 0; i < block.size(); ++i)
                {
                    // Find edge info.
                    ElementSharedPtr elmt = block[i];

                    for (j = 0; j < elmt->GetEdgeCount(); ++j)
                    {
                        eIt = edgeCount.find(elmt->GetEdge(j)->id);
                        ASSERTL0(eIt != edgeCount.end(), "Couldn't find edge");
                        eIt->second.group = maxId;
                    }
                }

                ++maxId;
            }

            for (eIt = edgeCount.begin(); eIt != edgeCount.end(); ++eIt)
            {
                if (eIt->second.count > 1)
                {
                    continue;
                }

                unsigned int compId = eIt->second.group;
                CompositeMap::iterator cIt = m->composite.find(compId);

                if (cIt == m->composite.end())
                {
                    CompositeSharedPtr comp(new Composite());
                    comp->id  = compId;
                    comp->tag = "E";
                    cIt = m->composite.insert(std::make_pair(compId, comp)).first;
                }

                vector<int> tags(1);
                tags[0] = compId;
                vector<NodeSharedPtr> nodeList(2);
                nodeList[0] = eIt->second.edge->n1;
                nodeList[1] = eIt->second.edge->n2;

                ElmtConfig conf(eLine, 1, false, false);
                ElementSharedPtr elmt = GetElementFactory().
                    CreateInstance(eLine,conf,nodeList,tags);
                elmt->SetEdgeLink(eIt->second.edge);

                cIt->second->items.push_back(elmt);
            }
        }

        void ProcessDetectSurf::FindContiguousSurface(
            ElementSharedPtr          start,
            set<int>                 &doneIds,
            vector<ElementSharedPtr> &block)
        {
            block.push_back(start);
            doneIds.erase(start->GetId());

            vector<EdgeSharedPtr> edges = start->GetEdgeList();

            for (int i = 0; i < edges.size(); ++i)
            {
                for (int j = 0; j < edges[i]->elLink.size(); ++j)
                {
                    ElementSharedPtr elmt = edges[i]->elLink[j].first;
                    if (elmt == start)
                    {
                        continue;
                    }

                    if (doneIds.count(elmt->GetId()) == 0)
                    {
                        continue;
                    }

                    FindContiguousSurface(elmt, doneIds, block);
                }
            }
        }
    }
}
