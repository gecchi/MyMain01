#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace MyStg2nd {

class StraightLaserChip : public LaserChip {
    friend class LaserChipDispatcher;
public:
    int* _pSource_X;
    int* _pSource_Y;
    int* _pSource_Z;

    GgafDx9Core::angle* _pSource_RX;
    GgafDx9Core::angle* _pSource_RY;
    GgafDx9Core::angle* _pSource_RZ;

    double* _pSource_vX;
    double* _pSource_vY;
    double* _pSource_vZ;

    int _veloMove;
    DWORD _dwActiveFrame;

//    GgafDx9Core::GgafDx9GeometricActor* _pPosSourceActor;
//    GgafDx9Core::GgafDx9GeometricActor* _pAngleSourceActor;

    StraightLaserChip(const char* prm_name, const char* prm_model);

//    void setSource(int* pSrcX, int* pSrcY, int* pSrcZ,
//                       GgafDx9Core::angle* pSrcRX, GgafDx9Core::angle* pSrcRY, GgafDx9Core::angle* pSrcRZ
//                   ) {
//        _pSource_X = pSrcX;
//        _pSource_Y = pSrcY;
//        _pSource_Z = pSrcZ;
//        _pSource_RX = pSrcRX;
//        _pSource_RY = pSrcRY;
//        _pSource_RZ = pSrcRZ;
//        _pSource_vX = pSrcvX;
//        _pSource_vY = pSrcvY;
//        _pSource_vZ = pSrcvZ;
//    }


    void setPositionSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
    }

    void setAngleSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pMover->_vX;
        _pSource_vY = &prm_pGeoActor->_pMover->_vY;
        _pSource_vZ = &prm_pGeoActor->_pMover->_vZ;
    }

    void setSource(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pMover->_vX;
        _pSource_vY = &prm_pGeoActor->_pMover->_vY;
        _pSource_vZ = &prm_pGeoActor->_pMover->_vZ;
    }

    virtual void initialize();

    virtual void onActive();

    virtual void processBehavior();

    virtual void processJudgement();

    //virtual void processDraw();

    virtual ~StraightLaserChip();

};

}
#endif /*STRAIGHTLASERCHIP_H_*/

