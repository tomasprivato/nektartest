SET(THIRDPARTY_BUILD_NIST_SPBLASTK OFF CACHE BOOL
    "Build NIST Sparse BLAS")

IF (THIRDPARTY_BUILD_NIST_SPBLASTK)
    INCLUDE(ExternalProject)
    EXTERNALPROJECT_ADD(
        spblastk0.9b
        PREFIX ${TPSRC}
        URL ${TPURL}/spblastk0.9b.tar.bz2
        URL_MD5 "93469940f03554939a4600f431eb4d99"
        DOWNLOAD_DIR ${TPSRC}
        CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX:PATH=${TPSRC}/dist ${TPSRC}/src/spblastk0.9b
    )
    SET(NIST_SPARSE_BLAS sbtk CACHE FILEPATH
        "Path to NIST Sparse BLAS." FORCE)
    LINK_DIRECTORIES(${TPSRC}/dist/lib)
ELSE (THIRDPARTY_BUILD_NIST_SPBLASTK)
    INCLUDE(FindNistSparseBlas)
ENDIF (THIRDPARTY_BUILD_NIST_SPBLASTK)

