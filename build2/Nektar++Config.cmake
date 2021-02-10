# - Nektar++ Config File
#
# Use this module by invoking find_package with the form:
#  FIND_PACKAGE(Nektar++
#    [version] [EXACT]      # Minimum or EXACT version e.g. 1.36.0
#    [REQUIRED]             # Fail with error if Nektar++ is not found
#    )                      #
#
# This sets the following variables:
#  Nektar++_FOUND             - True if headers and requested libraries were found
#  Nektar++_VERSION           - Nektar++_VERSION
#  Nektar++_INCLUDE_DIRS      - Nektar++ include directories
#  Nektar++_LIBRARY_DIRS      - Link directories for Nektar++ libraries
#  Nektar++_DEFINITIONS       - Nektar++ build flags
#  Nektar++_LIBRARIES         - Nektar++ component libraries to be linked
#
#  Nektar++_TP_INCLUDE_DIRS   - Nektar++ ThirdParty include directories
#  Nektar++_TP_LIBRARY_DIRS   - Link directories for Nektar++ ThirdParty libraries
#  Nektar++_TP_LIBRARIES      - Nektar++ ThirdParty libraries to be linked
#
# Example Use:
#  FIND_PACKAGE(Nektar++ REQUIRED)
#  ADD_DEFINITIONS(${NEKTAR++_DEFINITIONS})
#  INCLUDE_DIRECTORIES(${NEKTAR++_INCLUDE_DIRS} ${NEKTAR++_TP_INCLUDE_DIRS})
#  LINK_DIRECTORIES(${NEKTAR++_LIBRARY_DIRS} ${NEKTAR++_TP_LIBRARY_DIRS})
#  TARGET_LINK_LIBRARIES(${ProjectName} ${NEKTAR++_LIBRARIES} ${NEKTAR++_TP_LIBRARIES})
#

# set basic variables
SET(NEKTAR++_FOUND "ON")
SET(NEKTAR++_VERSION "5.0.0")
SET(NEKTAR++_ROOT_DIR "/home/tomas/Documents/gitproject/nektar++/build2/dist")
SET(NEKTAR++_INCLUDE_DIRS "${NEKTAR++_ROOT_DIR}/include/nektar++")
SET(NEKTAR++_LIBRARY_DIRS "${NEKTAR++_ROOT_DIR}/lib64")
SET(NEKTAR++_DEFINITIONS  -DNEKTAR_USE_SCOTCH -DTIXML_USE_STL -DNEKTAR_MEMORY_POOL_ENABLED)
SET(NEKTAR++_LIBRARIES LibUtilities;LocalRegions;SpatialDomains;StdRegions;Collections;MultiRegions;SolverUtils;NekMeshUtils;GlobalMapping;FieldUtils)

SET(NEKTAR++_TP_INCLUDE_DIRS
    "${NEKTAR++_ROOT_DIR}/include/nektar++/ThirdParty")
SET(NEKTAR++_TP_LIBRARIES "")
SET(NEKTAR++_TP_LIBRARY_DIRS "")

# Set up Boost and other ThirdParty include directories.
SET(Boost_INCLUDE_DIRS "/home/tomas/Documents/gitproject/nektar++/build2/dist/include/ThirdParty")
SET(NEKTAR++_TP_INCLUDE_DIRS
    ${NEKTAR++_TP_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

SET(Boost_LIBRARIES /home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_thread.so;-lpthread;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_iostreams.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_filesystem.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_system.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_program_options.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_regex.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_thread.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_iostreams.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_filesystem.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_system.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_program_options.so;/home/tomas/Documents/gitproject/nektar++/build2/ThirdParty/dist/lib/libboost_regex.so)
SET(Boost_LIBRARY_DIRS "/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/thirdparty")
SET(NEKTAR++_TP_LIBRARIES
    ${NEKTAR++_TP_LIBRARIES} ${Boost_LIBRARIES})

SET(TINYXML_INCLUDE_DIRS "/home/tomas/Documents/gitproject/nektar++/build2/dist/include/ThirdParty")
SET(NEKTAR++_TP_INCLUDE_DIRS
    ${NEKTAR++_TP_INCLUDE_DIRS} ${TINYXML_INCLUDE_DIRS})

SET(ZLIB_INCLUDE_DIRS "/usr/include")
SET(NEKTAR++_TP_INCLUDE_DIRS
    ${NEKTAR++_TP_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS})

SET(NEKTAR_USE_MPI "OFF")
IF( NEKTAR_USE_MPI )
    SET(MPI_C_LIBRARIES "")
    SET(MPI_C_INCLUDE_PATH "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${MPI_C_INCLUDE_PATH})
    SET(NEKTAR++_TP_LIBRARIES
        ${NEKTAR++_TP_LIBRARIES} ${MPI_C_LIBRARIES})
    SET(NEKTAR++_DEFINITIONS
        "${NEKTAR++_DEFINITIONS} -DNEKTAR_USE_MPI")
ENDIF( NEKTAR_USE_MPI )

SET(NEKTAR_USE_SCOTCH "ON")
IF( NEKTAR_USE_SCOTCH )
    SET(SCOTCH_INCLUDE_DIRS "/home/tomas/Documents/gitproject/nektar++/build2/dist/include/ThirdParty")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${SCOTCH_INCLUDE_DIRS})
ENDIF( NEKTAR_USE_SCOTCH )

SET(NEKTAR_USE_METIS "OFF")
IF( NEKTAR_USE_METIS )
    SET(METIS_INCLUDE_DIRS "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${METIS_INCLUDE_DIRS})
ENDIF( NEKTAR_USE_METIS )

SET(NEKTAR_USE_FFTW "OFF")
IF( NEKTAR_USE_FFTW )
    SET(FFTW_INCLUDE_DIR "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${FFTW_INCLUDE_DIR})
ENDIF( NEKTAR_USE_FFTW )

SET(NEKTAR_USE_ARPACK "ON")
IF( NEKTAR_USE_ARPACK )
    SET(ARPACK_INCLUDE_DIR "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${ARPACK_INCLUDE_DIR})
ENDIF( NEKTAR_USE_ARPACK )

SET(NEKTAR_USE_VTK "OFF")
IF( NEKTAR_USE_VTK )
    SET(VTK_INCLUDE_DIRS "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${VTK_INCLUDE_DIRS})
ENDIF( NEKTAR_USE_VTK )

SET(NEKTAR_USE_HDF5 "OFF")
IF( NEKTAR_USE_HDF5 )
    SET(HDF5_INCLUDE_DIRS "")
    SET(NEKTAR++_TP_INCLUDE_DIRS
        ${NEKTAR++_TP_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS})
ENDIF( NEKTAR_USE_HDF5 )

# find and add Nektar++ libraries
INCLUDE(/home/tomas/Documents/gitproject/nektar++/build2/dist/lib64/nektar++/cmake/Nektar++Libraries.cmake)

# platform dependent options
IF(${CMAKE_SYSTEM} MATCHES "Linux.*")
    set(NEKTAR++_TP_LIBRARIES ${NEKTAR++_TP_LIBRARIES} rt)
    SET(NEKTAR++_DEFINITIONS "${NEKTAR++_DEFINITIONS} -pthread")
ENDIF(${CMAKE_SYSTEM} MATCHES "Linux.*")
