#ifndef STRAIGHTLASERCHIP_H_
#define STRAIGHTLASERCHIP_H_
namespace GgafLib {

/**
 * ストレートレーザー用ポリラインのチップ .
 * ストレートレーザーなどと表現しているが、正確には<BR>
 * ・発射座標任意、発射元座標が移動すると、それにともなって平行移動する（ことも可能）<BR>
 * ・発射方向任意、発射元方向の角度が変化すると、それにともなって発射元を中心に回転移動する（ことも可能）<BR>
 * ・移動方法は基本等速で直進<BR>
 * ・但し全チップ発射元オブジェクト座標と向きの差分を加算。同期をとる。<BR>
 * と言うべきか、グラディウス方式ワインダー可能なレーザーと言うべきか、そんな感じ。<BR>
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class StraightLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    /** レーザーの位置を同期するための、X座標変数場所 */
    int* _pSource_X;
    /** レーザーの位置を同期するための、Y座標変数場所 */
    int* _pSource_Y;
    /** レーザーの位置を同期するための、Z座標変数場所 */
    int* _pSource_Z;
    /** レーザーの向き方向のを同期するための、X軸回転アングル値変数場所 */
    angle* _pSource_RX;
    /** レーザーの向き方向のを同期するための、Y軸回転アングル値変数場所 */
    angle* _pSource_RY;
    /** レーザーの向き方向のを同期するための、Z軸回転アングル値変数場所 */
    angle* _pSource_RZ;
    /** レーザーの移動方向を同期するための、単位方向ベクトルX成分変数場所 */
    float* _pSource_vX;
    /** レーザーの移動方向を同期するための、単位方向ベクトルY成分変数場所 */
    float* _pSource_vY;
    /** レーザーの移動方向を同期するための、単位方向ベクトルZ成分変数場所 */
    float* _pSource_vZ;
    /** 移動速度 */
    int _veloMv;

    GgafDxGeometricActor* _pSourceActor;

    StraightLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * 平行移動と回転移動の同期をとる発射アクターを設定 .
     * @param prm_pGeoActor 発射元アクター
     */
    void setSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pKurokoA->_vX;
        _pSource_vY = &prm_pGeoActor->_pKurokoA->_vY;
        _pSource_vZ = &prm_pGeoActor->_pKurokoA->_vZ;
        _pSourceActor = prm_pGeoActor;
    }


    /**
     * 平行移動のみ同期をとる発射アクターを設定 .
     * @param prm_pGeoActor
     */
    void setPositionSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_X = &prm_pGeoActor->_X;
        _pSource_Y = &prm_pGeoActor->_Y;
        _pSource_Z = &prm_pGeoActor->_Z;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * 回転移動のみ同期をとる発射アクターを設定 .
     * @param prm_pGeoActor
     */
    void setAngleSource(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor) {
        _pSource_RX = &prm_pGeoActor->_RX;
        _pSource_RY = &prm_pGeoActor->_RY;
        _pSource_RZ = &prm_pGeoActor->_RZ;
        _pSource_vX = &prm_pGeoActor->_pKurokoA->_vX;
        _pSource_vY = &prm_pGeoActor->_pKurokoA->_vY;
        _pSource_vZ = &prm_pGeoActor->_pKurokoA->_vZ;
        _pSourceActor = prm_pGeoActor;
    }

    virtual ~StraightLaserChip();
};

}
#endif /*STRAIGHTLASERCHIP_H_*/

