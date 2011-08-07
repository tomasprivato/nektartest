///////////////////////////////////////////////////////////////////////////////
//
// File SessionReader.h
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
// Description:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef NEKTAR_LIB_UTILITIES_SESSIONREADER_H
#define NEKTAR_LIB_UTILITIES_SESSIONREADER_H

#include <iostream>
#include <map>
#include <string>

#include <LibUtilities/Communication/Comm.h>
#include <LibUtilities/BasicUtils/Equation.h>
#include <LibUtilities/BasicConst/NektarUnivTypeDefs.hpp>
#include <LibUtilities/LibUtilitiesDeclspec.h>

#include <boost/algorithm/string.hpp>
#include <boost/enable_shared_from_this.hpp>

class TiXmlElement;
class TiXmlDocument;

namespace Nektar
{
    namespace LibUtilities
    {
        typedef std::map<std::string, std::string>  SolverInfoMap;
        typedef std::map<std::string, NekDouble>    ParameterMap;
        typedef std::map<std::string, std::string>  GeometricInfoMap;
        typedef std::map<std::string, std::string>  ExpressionMap;
        typedef std::vector<std::string>            VariableList;
        typedef std::map<std::string, EquationSharedPtr>  EquationMap;
        typedef std::map<std::string, std::string>  TagMap;

        typedef std::map<std::string, int>          EnumMap;
        typedef std::map<std::string, EnumMap>      EnumMapList;

        enum FunctionType
        {
            eFunctionTypeNone,
            eFunctionTypeExpression,
            eFunctionTypeFile,
            eSIZE_FunctionType
        };
        const char* const FunctionTypeMap[] =
        {
            "No Function type",
            "Expression",
            "File"
        };
        struct FunctionDefinition
        {
            enum FunctionType m_type;
            std::string       m_filename;
            EquationMap       m_expressions;
        };
        typedef std::map<std::string, FunctionDefinition > FunctionMap;

        class SessionReader;
        typedef boost::shared_ptr<SessionReader> SessionReaderSharedPtr;

        /// Reads and parses information from a Nektar++ XML session file.
        class SessionReader: public boost::enable_shared_from_this<SessionReader>
        {
        public:
            /// Support creation through MemoryManager only.
            friend class MemoryManager<SessionReader>;

            /**
             * @brief Creates an instance of the SessionReader class.
             *
             * This function should be used by an application to instantiate the
             * session reader. It should be called at the very beginning of the
             * application before any other processing of command-line
             * arguments. After instantiating the class and setting up any
             * parallel communication, it also calls the main initialisation
             * of the object.
             */
            static SessionReaderSharedPtr CreateInstance(int argc, char *argv[])
            {
                SessionReaderSharedPtr p = MemoryManager<LibUtilities::SessionReader>::AllocateSharedPtr(argc, argv);
                p->InitSession();
                return p;
            }

            /// Destructor
            LIB_UTILITIES_EXPORT ~SessionReader();

            /// Provides direct access to the TiXmlDocument object.
            LIB_UTILITIES_EXPORT TiXmlDocument &GetDocument();
            /// Provides direct access to the TiXmlElement specified.
            LIB_UTILITIES_EXPORT TiXmlElement *GetElement(const std::string& pPath);
            /// Tests if a specified element is defined in the XML document.
            LIB_UTILITIES_EXPORT bool DefinesElement(const std::string& pPath) const;
            /// Returns the filename of the loaded XML document.
            LIB_UTILITIES_EXPORT const std::string &GetFilename() const;
            /// Returns the session name of the loaded XML document.
            LIB_UTILITIES_EXPORT const std::string &GetSessionName() const;
            /// Returns the communication object.
            LIB_UTILITIES_EXPORT CommSharedPtr &GetComm();
            /// Finalises the session.
            LIB_UTILITIES_EXPORT void Finalise();

            /* ------ PARAMETERS --------*/
            /// Checks if a parameter is specified in the XML document.
            LIB_UTILITIES_EXPORT bool DefinesParameter(const std::string &name) const;
            /// Returns the value of the specified parameter.
            LIB_UTILITIES_EXPORT const NekDouble &GetParameter(const std::string &pName) const;
            /// Load an integer parameter
            LIB_UTILITIES_EXPORT void LoadParameter(const std::string &name, int &var) const;
            /// Check for and load an integer parameter.
            LIB_UTILITIES_EXPORT void LoadParameter(const std::string &name, int &var, const int &def) const;
            /// Load a double precision parameter
            LIB_UTILITIES_EXPORT void LoadParameter(const std::string &name, NekDouble &var) const;
            /// Check for and load a double-precision parameter.
            LIB_UTILITIES_EXPORT void LoadParameter(const std::string &name, NekDouble &var, const NekDouble &def) const;

            /* ------ SOLVER INFO ------ */
            /// Checks if a solver info property is specified.
            LIB_UTILITIES_EXPORT bool DefinesSolverInfo(const std::string &name) const;
            /// Returns the value of the specified solver info property.
            LIB_UTILITIES_EXPORT const std::string& GetSolverInfo(const std::string &pProperty) const;
            /// Returns the value of the specified solver info property.
            LIB_UTILITIES_EXPORT template<typename T>
                                 inline const T GetSolverInfoAsEnum(const std::string &pName) const;
            /// Check for and load a solver info property.
            LIB_UTILITIES_EXPORT void LoadSolverInfo(const std::string &name, std::string& var, const std::string &def = "") const;
            /// Check if the value of a solver info property matches.
            LIB_UTILITIES_EXPORT void MatchSolverInfo(const std::string &name, const std::string &trueval, bool &var, const bool &def = false) const;
            /// Check if the value of a solver info property matches.
            LIB_UTILITIES_EXPORT bool MatchSolverInfo(const std::string &name, const std::string &trueval) const;
            /// Check if the value of a solver info property matches.
            LIB_UTILITIES_EXPORT template<typename T>
                                 inline const bool MatchSolverInfoAsEnum(const std::string& name, const T &trueval) const;
            /// Registers an enumeration value.
            LIB_UTILITIES_EXPORT inline static std::string RegisterEnumValue(std::string pEnum, std::string pString, int pEnumValue);
            /// Registers the default string value of a solver info property.
            LIB_UTILITIES_EXPORT inline static std::string RegisterDefaultSolverInfo(const std::string &pName, const std::string &pValue);

            /* ------ GEOMETRIC INFO ------ */
            /// Checks if a geometric info property is defined.
            LIB_UTILITIES_EXPORT bool DefinesGeometricInfo(const std::string &name) const;
            /// Checks for and load a geometric info string property.
            LIB_UTILITIES_EXPORT void LoadGeometricInfo(const std::string &name, std::string &var, const std::string &def = "") const;
            /// Checks for and loads a geometric info boolean property.
            LIB_UTILITIES_EXPORT void LoadGeometricInfo(const std::string &name, bool &var, const bool &def = false) const;
            /// Check if the value of a geometric info string property matches.
            LIB_UTILITIES_EXPORT void MatchGeometricInfo(const std::string &name, const std::string &trueval, bool &var, const bool &def = false) const;

            /* ------ VARIABLES ------ */
            /// Returns the name of the variable specified by the given index.
            LIB_UTILITIES_EXPORT const std::string& GetVariable(const unsigned int &idx) const;
            /// Returns the names of all variables.
            LIB_UTILITIES_EXPORT std::vector<std::string> GetVariables() const;

            /* ------ FUNCTIONS ------*/
            /// Checks if a specified function is defined in the XML document.
            LIB_UTILITIES_EXPORT bool DefinesFunction(const std::string &name) const;
            /// Checks if a specified function has a given variable defined.
            LIB_UTILITIES_EXPORT bool DefinesFunction(const std::string &name, const std::string &variable) const;
            /// Returns an EquationSharedPtr to a given function variable.
            LIB_UTILITIES_EXPORT EquationSharedPtr GetFunction(const std::string &name, const std::string &variable) const;
            /// Returns an EquationSharedPtr to a given function variable index.
            LIB_UTILITIES_EXPORT EquationSharedPtr GetFunction(const std::string &name, const unsigned int &var) const;
            /// Returns the type of a given function.
            LIB_UTILITIES_EXPORT enum FunctionType GetFunctionType(const std::string& name) const;
            /// Returns the filename to be loaded for a given function.
            LIB_UTILITIES_EXPORT std::string GetFunctionFilename(const std::string& name) const;

            /* ------ TAGS ------ */
            /// Checks if a specified tag is defined.
            LIB_UTILITIES_EXPORT bool DefinesTag(const std::string& pName) const;
            /// Sets a specified tag.
            LIB_UTILITIES_EXPORT void SetTag(const std::string& pName, const std::string& pValue);
            /// Returns the value of a specified tag.
            LIB_UTILITIES_EXPORT const std::string &GetTag(const std::string& pName) const;

            /// Substitutes expressions defined in the XML document.
            LIB_UTILITIES_EXPORT void SubstituteExpressions(std::string &expr);

        private:
            CommSharedPtr               m_comm;
            std::string                 m_filename;
            std::string                 m_sessionName;
            TiXmlDocument*              m_xmlDoc;

            SolverInfoMap               m_solverInfo;
            ParameterMap                m_parameters;
            GeometricInfoMap            m_geometricInfo;
            ExpressionMap               m_expressions;
            FunctionMap                 m_functions;
            VariableList                m_variables;
            TagMap                      m_tags;

            /// String to enumeration map for Solver Info parameters.
            static EnumMapList          m_enums;
            static SolverInfoMap        m_solverInfoDefaults;

            /// Main constructor
            SessionReader(int argc, char *argv[]);
            void InitSession();

            /// Returns a shared pointer to the current object.
            inline boost::shared_ptr<SessionReader> GetSharedThisPtr();

            /// Loads and parses the specified file.
            void LoadFile(const std::string &pFilename);
            /// Loads the given XML document and instantiates an appropriate
            /// communication object.
            void CreateComm(int &argc, char* argv[], const std::string &pFilename);
            /// Partitions the mesh when running in parallel.
            void PartitionMesh();

            /// Reads the PARAMETERS section of the XML document.
            void ReadParameters(TiXmlElement *conditions);
            /// Reads the SOLVERINFO section of the XML document.
            void ReadSolverInfo(TiXmlElement *conditions);
            /// Reads the GEOMETRICINFO section of the XML document.
            void ReadGeometricInfo(TiXmlElement *geometry);
            /// Reads the EXPRESSIONS section of the XML document.
            void ReadExpressions(TiXmlElement *conditions);
            /// Reads the VARIABLES section of the XML document.
            void ReadVariables(TiXmlElement *conditions);
            /// Reads the FUNCTIONS section of the XML document.
            void ReadFunctions(TiXmlElement *conditions);

            /// Perform a case-insensitive string comparison.
            int NoCaseStringCompare(const std::string &s1, const std::string &s2) const;
        };


        /**
         *
         */
        template<typename T>
        inline const bool SessionReader::MatchSolverInfoAsEnum(const std::string &name, const T &trueval) const
        {
            return (GetSolverInfoAsEnum<T>(name) == trueval);
        }


        /**
         *
         */
        template<typename T>
        inline const T SessionReader::GetSolverInfoAsEnum(const std::string &pName) const
        {
            ASSERTL0(DefinesSolverInfo(pName), "Solver info '" + pName + "' not defined.");

            std::string vValue = GetSolverInfo(pName);
            EnumMapList::iterator x;
            ASSERTL0((x = m_enums.find(pName)) != m_enums.end(),
                    "Enum for SolverInfo property '" + pName + "' not found.");
            EnumMap::iterator y;
            ASSERTL0((y = x->second.find(vValue)) != x->second.end(),
                    "Value of SolverInfo property '" + pName + "' is invalid.");
            return T(y->second);
        }


        /**
         *
         */
        inline std::string SessionReader::RegisterEnumValue(std::string pEnum, std::string pString, int pEnumValue)
        {
            EnumMapList::iterator x;
            if ((x = m_enums.find(pEnum)) == m_enums.end())
            {
                m_enums[pEnum] = EnumMap();
                x = m_enums.find(pEnum);
            }
            x->second[pString] = pEnumValue;
            return pString;
        }


        /**
         *
         */
        inline std::string SessionReader::RegisterDefaultSolverInfo(const std::string &pName, const std::string &pValue)
        {
            std::string vName = boost::to_upper_copy(pName);
            m_solverInfoDefaults[vName] = pValue;
            return pValue;
        }


        /**
         *
         */
        inline boost::shared_ptr<SessionReader> SessionReader::GetSharedThisPtr()
        {
            return shared_from_this();
        }
    }
}

#endif

