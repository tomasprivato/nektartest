IF (NEKTAR_USE_MKL)
    # Deal with MKL due to issues with FindBLAS VENDOR variable.
    INCLUDE (FindMKL)
    SET(BLAS_LAPACK ${MKL})
ELSEIF(NEKTAR_USE_WIN32_LAPACK)
    INCLUDE (FindWin32Lapack)
    SET(BLAS_LAPACK ${WIN32_BLAS} ${WIN32_LAPACK})
ELSE()
    IF(NEKTAR_USE_SYSTEM_BLAS_LAPACK)
        SET(TEST_ENV $ENV{LAPACK_DIR})
        IF(NOT DEFINED LAPACK_DIR AND DEFINED TEST_ENV)
	    SET(LAPACK_DIR $ENV{LAPACK_DIR})
        ENDIF()

        SET(TEST_ENV $ENV{BLAS_DIR})
        IF(NOT DEFINED BLAS_DIR AND DEFINED TEST_ENV)
	    SET(BLAS_DIR $ENV{BLAS_DIR})
        ENDIF()

        SET(VENDOR Generic)
    ELSEIF(NEKTAR_USE_OPENBLAS)
        SET(TEST_ENV $ENV{OPENBLAS_HOME})
        IF(NOT DEFINED LAPACK_DIR AND DEFINED TEST_ENV)
	    SET(LAPACK_DIR $ENV{OPENBLAS_HOME})
        ENDIF()

        SET(VENDOR OpenBLAS)
    ELSEIF(NEKTAR_USE_ACCELERATE_FRAMEWORK)
        SET(VENDOR Apple)
    ELSEIF(NEKTAR_USE_ACML)
        SET(VENDOR ACML)
    ENDIF()

    SET(BLA_VENDOR ${VENDOR})

    IF (NEKTAR_USE_SYSTEM_BLAS_LAPACK)
        find_package(BLAS QUIET)
    ENDIF()

    find_package(LAPACK QUIET)
    SET(BLAS_LAPACK ${LAPACK_LIBRARIES})

    IF(NEKTAR_USE_SYSTEM_BLAS_LAPACK)
        SET(BLAS_LAPACK ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
    ENDIF()
ENDIF()

IF (BLAS_LAPACK)
    MESSAGE(STATUS "Found BLAS and LAPACK: ${BLAS_LAPACK}")
ENDIF ()
