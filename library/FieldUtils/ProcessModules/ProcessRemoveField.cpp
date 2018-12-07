///////////////////////////////////////////////////////////////////////////////
//
//  File: ProcessFieldFromString.cpp
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
//  Description: Modify an existing or add a new field from a string based on
//  existing variable
//
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;

#include "ProcessRemoveField.h"

#include <LibUtilities/BasicUtils/ParseUtils.h>
#include <LibUtilities/BasicUtils/SharedArray.hpp>

namespace Nektar
{
namespace FieldUtils
{

ModuleKey ProcessRemoveField::className =
    GetModuleFactory().RegisterCreatorFunction(
        ModuleKey(eProcessModule, "removefield"), ProcessRemoveField::create,
        "Remove one of the existing fields");

ProcessRemoveField::ProcessRemoveField(FieldSharedPtr f) : ProcessModule(f)
{
    m_config["fieldname"] =
        ConfigOption(false, "NotSet", "Name for field to be removed, required");
}

ProcessRemoveField::~ProcessRemoveField(void)
{
}

void ProcessRemoveField::Process(po::variables_map &vm)
{

    // Obtain field names to be removed
    string fieldNames = m_config["fieldname"].as<string>();
    vector<string> fieldName;
    ASSERTL0(fieldNames != "NotSet", "A fieldname is required");

    ASSERTL0(ParseUtils::GenerateVector(fieldNames, fieldName),
             "Failed to interpret fields string");

    // Remove fields specified
    for (int i = 0; i < fieldName.size(); ++i)
    {
        // Get number of fields
        int nFields = m_f->m_variables.size();

        // check if field exists
        auto it = std::find(m_f->m_variables.begin(), m_f->m_variables.end(),
                            fieldName[i]);
        ASSERTL0(it != m_f->m_variables.end(), "Field does not exist");

        int fieldID;
        fieldID = std::distance(m_f->m_variables.begin(), it);

        m_f->m_variables.erase(m_f->m_variables.begin() + fieldID);

        // All fields after the removed one are shifted
        if (fieldID != nFields)
        {
            for (int ind = fieldID; ind < nFields - 1; ++ind)
            {
                m_f->m_exp[ind] = m_f->m_exp[ind + 1];
            }
        }

        cout << "Field " << fieldName[i] << " has been erased" << endl;
    }
}
} // namespace FieldUtils
} // namespace Nektar
