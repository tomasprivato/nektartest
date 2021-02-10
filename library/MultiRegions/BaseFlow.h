#include <LibUtilities/FFT/NektarFFT.h>
#include <MultiRegions/ExpList.h>


namespace Nektar
{
namespace MultiRegions
{
class BaseFlow
{
    
public:
    
    int m_spacedim;


    LibUtilities::SessionReaderSharedPtr m_session;

    /// Storage for base flow
    Array<OneD, Array<OneD, NekDouble> >            m_baseflow;
    Array<OneD, Array<OneD, NekDouble> >            m_gradBase;



    /// flag to determine if use single mode or not
    bool                                            m_singleMode;
    /// flag to determine if use half mode or not
    bool                                            m_halfMode;
    /// flag to determine if use multiple mode or not
    bool                                            m_multipleModes;


    /// number of slices
    int                                             m_slices;
    /// period length
    NekDouble                                       m_period;
    /// interpolation vector
    Array<OneD, Array<OneD, NekDouble> >            m_interp;
    /// auxiliary variables
    LibUtilities::NektarFFTSharedPtr                m_FFT;
    Array<OneD,NekDouble>                           m_tmpIN;
    Array<OneD,NekDouble>                           m_tmpOUT;
    bool                                            m_useFFTW;
    
    DNekBlkMatSharedPtr GetFloquetBlockMatrix() const;
    DNekBlkMatSharedPtr GenFloquetBlockMatrix() const;



    void UpdateBase(
        const NekDouble                                    m_time);

    void UpdateGradBase(
        const Array<OneD, MultiRegions::ExpListSharedPtr> &fields);

    void DFT(
        const std::string                                  file,
              Array<OneD, MultiRegions::ExpListSharedPtr> &pFields,
        const NekDouble                                    m_slices);

    /// Import Base flow
    void ImportFldBase(
              std::string                                  pInfile,
              Array<OneD, MultiRegions::ExpListSharedPtr> pFields,
              int                                          slice);

    void GetFldBase(LibUtilities::SessionReaderSharedPtr         pSession,
                    Array<OneD, MultiRegions::ExpListSharedPtr>  pFields,
                    bool adj,
                    const NekDouble time);

    void GetBaseGrad(LibUtilities::SessionReaderSharedPtr         pSession,
                    Array<OneD, MultiRegions::ExpListSharedPtr>  pFields);

private:
    /// flag to determine if use or not the FFT for transformations
    bool m_useFFT = false;

    ///Parameter for homogeneous expansions
    enum HomogeneousType
    {
        eHomogeneous1D,
        eHomogeneous2D,
        eHomogeneous3D,
        eNotHomogeneous
    };

    enum HomogeneousType m_HomogeneousType;

    NekDouble m_LhomX; ///< physical length in X direction (if homogeneous)
    NekDouble m_LhomY; ///< physical length in Y direction (if homogeneous)
    NekDouble m_LhomZ; ///< physical length in Z direction (if homogeneous)

    int m_npointsX;    ///< number of points in X direction (if homogeneous)
    int m_npointsY;    ///< number of points in Y direction (if homogeneous)
    int m_npointsZ;    ///< number of points in Z direction (if homogeneous)

    int m_HomoDirec;   ///< number of homogenous directions

    int m_NumMode;     ///< Mode to use in case of single mode analysis
};

}
}