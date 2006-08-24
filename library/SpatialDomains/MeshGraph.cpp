////////////////////////////////////////////////////////////////////////////////
//
//  File:  $Source: /usr/sci/projects/Nektar/cvs/Nektar++/libs/SpatialDomains/MeshGraph.cpp,v $
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
#include "pchSpatialDomains.h"

#include <SpatialDomains/MeshGraph.h>

// Use the stl version, primarily for string.
#define TIXML_USE_STL
#include <tinyxml/tinyxml.h>
#include <string>
#include <strstream>

namespace Nektar
{
    namespace SpatialDomains
    {

        MeshGraph::MeshGraph():
            m_MeshDimension(3),
            m_SpaceDimension(3)
        {
        }

        // \brief Read will read the meshgraph vertices given a filename.
        void MeshGraph::Read(std::string &infilename)
        {
            SetFileName(infilename);
            TiXmlDocument doc(infilename);
            bool loadOkay = doc.LoadFile();

            std::string errstr = "Unable to load file: ";
            errstr += infilename;
            ASSERTL0(loadOkay, errstr.c_str());

            Read(doc);
        }

        // \brief Read will read the meshgraph vertices given a TiXmlDocument.
        void MeshGraph::Read(TiXmlDocument &doc)
        {
            TiXmlNode* node = NULL;
            TiXmlElement* mesh = NULL;
            int err;    /// Error value returned by TinyXML.

            // Find the Mesh tag and same the dim and space attributes
            mesh = doc.FirstChildElement("MESH");

            ASSERTL0(mesh, "Unable to find MESH tag in file.");
            TiXmlAttribute *attr = mesh->FirstAttribute();

            // Initialize the mesh and space dimensions to 3 dimensions.
            // We want to do this each time we read a file, so it should
            // be done here and not just during class initialization.
            m_MeshDimension = 3;
            m_SpaceDimension = 3;

            while (attr)
            {
                std::string attrName(attr->Name());
                if (attrName == "DIM")
                {
                    err = attr->QueryIntValue(&m_MeshDimension);
                    ASSERTL1(err==TIXML_SUCCESS, "Unable to read mesh dimension.");
                }
                else if (attrName == "SPACE")
                {
                    err = attr->QueryIntValue(&m_SpaceDimension);
                    ASSERTL1(err==TIXML_SUCCESS, "Unable to read mesh dimension.");
                }
                else
                {
                    std::string errstr("Unknown attribute: ");
                    errstr += attrName;
                    ASSERTL1(false, errstr.c_str());
                }

                // Get the next attribute.
                attr = attr->Next();
            }

            ASSERTL1(m_MeshDimension<=m_SpaceDimension, "Mesh dimension greater than space dimension");

            // Now read the vertices
            TiXmlElement* element = mesh->FirstChildElement("VERTEX");
            ASSERTL0(element, "Unable to find mesh VERTEX tag in file.");

            attr = element->FirstAttribute();
            ASSERTL0(attr, "VERTEX tag must include NUMBER"
                "attribute specifying the number of vertices");

            int numVertices;
            err = attr->QueryIntValue(&numVertices);
            ASSERTL0(err==TIXML_SUCCESS, "Unable to read VERTEX NUMBER attribute value.");

            //// Get the entire data block then go through it one line at a time.
            std::string vertexData;

            // Look through all immediate children and accumulate all text (type TEXT).
            // This is just in case it is broken up by other tagged elements.
            // Using element->GetText() will not work if text contains XML comments,
            // for example.
            TiXmlNode *child = element->FirstChild();
            while(child)
            {
                if (child->Type() == TiXmlNode::TEXT)
                {
                    vertexData += child->ToText()->Value();
                    vertexData += " "; // Don't jam together.
                }
                child = child->NextSibling();
            }

            // Get vertex data from the data string.
            int indx;
            double xval, yval, zval;
            std::istrstream vertexDataStrm(vertexData.c_str());

            try
            {
                for (int i=0; i<numVertices; ++i)
                {
                    vertexDataStrm >> indx;
                    vertexDataStrm >> xval >> yval >> zval;

                    VertexComponentSharedPtr vert(new VertexComponent(m_MeshDimension, indx, xval, yval, zval));
                    m_vertset.push_back(vert);
                }
            }
            catch(...)
            {
                ASSERTL0(false, "Unable to read VERTEX data.");
            }
        }

        void MeshGraph::Write(std::string &outfilename)
        {
        }

        MeshGraph::~MeshGraph()
        {
        }
    }; //end of namespace
}; //end of namespace

//
// $Log: MeshGraph.cpp,v $
// Revision 1.2  2006/05/09 13:37:01  jfrazier
// Removed duplicate definition of shared vertex pointer.
//
// Revision 1.1  2006/05/04 18:59:02  kirby
// *** empty log message ***
//
// Revision 1.14  2006/04/09 02:08:35  jfrazier
// Added precompiled header.
//
// Revision 1.13  2006/04/04 23:12:37  jfrazier
// More updates to readers.  Still work to do on MeshGraph2D to store tris and quads.
//
// Revision 1.12  2006/03/25 00:58:29  jfrazier
// Many changes dealing with fundamental structure and reading/writing.
//
// Revision 1.11  2006/03/12 14:20:43  sherwin
//
// First compiling version of SpatialDomains and associated modifications
//
// Revision 1.10  2006/02/26 21:19:43  bnelson
// Fixed a variety of compiler errors caused by updates to the coding standard.
//
// Revision 1.9  2006/02/19 01:37:33  jfrazier
// Initial attempt at bringing into conformance with the coding standard.  Still more work to be done.  Has not been compiled.
//
//
