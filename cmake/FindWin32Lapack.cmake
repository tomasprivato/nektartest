FIND_LIBRARY(WIN32_BLAS NAMES libblas PATHS ${TPSRC})
FIND_LIBRARY(WIN32_LAPACK NAMES liblapack PATHS ${TPSRC})

IF (NOT WIN32_BLAS OR NOT WIN32_LAPACK)
    IF (CMAKE_CL_64 OR CMAKE_GENERATOR MATCHES Win64)
        SET(WIN_ZIP_FILE         "win64-blas-lapack.zip")
        SET(WIN_ZIP_MD5_VALUE    "b5ad4f7335ca964bbdafab129e44a046")
        SET(WIN_ZIP_SHA1_VALUE   "adb331fa195db264e95e46b902887f12971dbf48")
        SET(WIN_ZIP_SHA256_VALUE "0e6e3360cdf577718ee57a6fd27c47bac0391d3c7d373e29a0352505e1dc912b")
    ELSE()
        SET(WIN_ZIP_FILE         "win32-blas-lapack.zip")
        SET(WIN_ZIP_MD5_VALUE    "6dbf9cced1fb73cc093ccc6560cb46e2")
        SET(WIN_ZIP_SHA1_VALUE   "39c5deaf17211a5012ccfd9d0258da04a7ceb197")
        SET(WIN_ZIP_SHA256_VALUE "6bb347aa717530fa74b71539f331bb4027767d8b25b8a26c741b540c73398a03")
    ENDIF()

    SET(WIN_ZIP_PATH ${TPSRC}/${WIN_ZIP_FILE})

    IF (NOT EXISTS ${WIN_ZIP_PATH})
        FILE(DOWNLOAD ${TPURL}/${WIN_ZIP_FILE} ${WIN_ZIP_PATH})
    ENDIF()

    # Calculate expected MD5 and SHA128 hashes
    FILE  (MD5      ${WIN_ZIP_PATH}    WIN_ZIP_MD5)
    FILE  (SHA1     ${WIN_ZIP_PATH}    WIN_ZIP_SHA1)
    FILE  (SHA256   ${WIN_ZIP_PATH}    WIN_ZIP_SHA256)
    STRING(TOLOWER "${WIN_ZIP_MD5}"    WIN_ZIP_MD5)
    STRING(TOLOWER "${WIN_ZIP_SHA1}"   WIN_ZIP_SHA1)
    STRING(TOLOWER "${WIN_ZIP_SHA256}" WIN_ZIP_SHA256)

    IF ((NOT WIN_ZIP_MD5    STREQUAL WIN_ZIP_MD5_VALUE)  OR
        (NOT WIN_ZIP_SHA1   STREQUAL WIN_ZIP_SHA1_VALUE) OR
        (NOT WIN_ZIP_SHA256 STREQUAL WIN_ZIP_SHA256_VALUE))
        MESSAGE(FATAL_ERROR "Security error: Win32 BLAS/LAPACK file has "
                            "MD5, SHA1 or SHA256 hash")
    ENDIF()

    EXECUTE_PROCESS(
        COMMAND ${CMAKE_COMMAND} -E tar jxf ${WIN_ZIP_PATH}
        WORKING_DIRECTORY ${TPSRC}
    )

    # For some reason CMake refuses to run FIND_LIBRARY again so we
    # force this to the correct library.
    SET(WIN32_BLAS "${TPSRC}/libblas.lib" CACHE FILEPATH "Blas" FORCE)
    SET(WIN32_LAPACK "${TPSRC}/liblapack.lib" CACHE FILEPATH "LAPACK" FORCE)

    IF (NOT WIN32_BLAS)
        MESSAGE(FATAL_ERROR "Could not find BLAS library after unzipping!")
    ENDIF()

    IF (NOT WIN32_LAPACK)
        MESSAGE(FATAL_ERROR "Could not find LAPACK library after unzipping!")
    ENDIF()
ENDIF ()

GET_FILENAME_COMPONENT(LAPACK_DIR ${WIN32_LAPACK} PATH CACHE)
LINK_DIRECTORIES(${LAPACK_DIR})

MESSAGE(STATUS "Found Win32 BLAS: ${WIN32_BLAS}")
MESSAGE(STATUS "Found Win32 Lapack: ${WIN32_LAPACK}")