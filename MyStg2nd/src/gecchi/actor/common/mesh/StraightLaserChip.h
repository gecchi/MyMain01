#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace MyStg2nd {

class StraightLaserChip : public LaserChip {
    friend class LaserChipDispatcher;

public:
    /** レーザーの位置を同期するための、X座標変数場所 */
    int* _pSource_X;
    /** レーザーの位置を同期するための、Y座標変数場所 */
    int* _pSource_Y;
    /** レーザーの位置を同期するための、Z座標変数場所 */
    int* _pSource_Z;
    /** レーザーの向き方向のを同期するための、X軸回転アングル値変数場所 */
    GgafDx9Core::angle* _pSource_RX;
    /** レーザーの向き方向のを同期するための、Y軸回転アングル値変数場所 */
    GgafDx9Core::angle* _pSource_RY;
    /** レーザーの向き方向のを同期するための、Z軸回転アングル値変数場所 */
    GgafDx9Core::angle* _pSource_RZ;
    /** レーザーの移動方向を同期するための、単位方向ベクトルX成分変数場所 */
    float* _pSource_vX;
    /** レーザーの移動方向を同期するための、単位方向ベクトルY成分変数場所 */
    float* _pSource_vY;
    /** レーザーの移動方向を同期するための、単位方向ベクトルZ成分変数場所 */
    float* _pSource_vZ;
    /** 移動速度 */
    int _veloMove;


    StraightLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void onActive();

    virtual void onInactive();

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

    virtual ~StraightLaserChip();

};

}
#endif /*STRAIGHTLASERCHIP_H_*/

