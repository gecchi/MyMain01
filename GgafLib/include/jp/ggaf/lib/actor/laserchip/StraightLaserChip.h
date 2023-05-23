#ifndef GGAF_LIB_STRAIGHTLASERCHIP_H_
#define GGAF_LIB_STRAIGHTLASERCHIP_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * ストレートレーザー用ポリラインのチップ .
 * ストレートレーザーなどと表現しているが、正確には<BR>
 * ・発射座標任意、発射元座標が移動すると、それにともなって平行移動する（ことも可能）<BR>
 * ・発射方向任意、発射元方向の角度が変化すると、それにともなって発射元を中心に回転移動する（ことも可能）<BR>
 * ・移動方法は基本等速で直進<BR>
 * ・但し全チップ発射元オブジェクト座標と向きの差分を加算。同期をとる。<BR>
 * と言うべきか、グラディウス方式ワインダー可能なレーザーと言うべきか、そんな感じ。<BR>
 * メンバーの _velo_mv で移動します。dispatch() したら、座標と方向及び _velo_mv を設定して下さい。<BR>
 * 発射元と連動して動かす場合は setSource() を設定して下さい。この場合、座標と方向は自動設定されます。
 * @version 1.00
 * @since 2009/08/25
 * @author Masatoshi Tsuge
 */
class StraightLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    int _tmp_source_x;
    int _tmp_source_y;
    int _tmp_source_z;
    angle _tmp_source_rx;
    angle _tmp_source_ry;
    angle _tmp_source_rz;
    /** [r/w]移動速度 */
    velo _velo_mv;

    dxcoord _view_bound;
public:
    /** レーザーの位置を同期するための、X座標変数場所 */
    int* _pSource_x;
    /** レーザーの位置を同期するための、Y座標変数場所 */
    int* _pSource_y;
    /** レーザーの位置を同期するための、Z座標変数場所 */
    int* _pSource_z;
    /** レーザーの向き方向のを同期するための、X軸回転アングル値変数場所 */
    angle* _pSource_rx;
    /** レーザーの向き方向のを同期するための、Y軸回転アングル値変数場所 */
    angle* _pSource_ry;
    /** レーザーの向き方向のを同期するための、Z軸回転アングル値変数場所 */
    angle* _pSource_rz;

    GgafDx::GeometricActor* _pSourceActor;

public:
    StraightLaserChip(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    /**
     * 発射元の移動と回転について、同期をとる発射アクターを設定 .
     * @param prm_pGeoActor 発射元アクター
     */
    void setSource(GgafDx::GeometricActor* prm_pGeoActor) {
        _pSource_x = &prm_pGeoActor->_x;
        _pSource_y = &prm_pGeoActor->_y;
        _pSource_z = &prm_pGeoActor->_z;
        _pSource_rx = &prm_pGeoActor->_rx;
        _pSource_ry = &prm_pGeoActor->_ry;
        _pSource_rz = &prm_pGeoActor->_rz;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * 発射元の移動のみについて、同期をとる発射アクターを設定 .
     * どっちを向いてても同じ方向に発射。
     * @param prm_pGeoActor 発射元アクター
     */
    void setPositionSource(GgafDx::GeometricActor* prm_pGeoActor) {
        _pSource_x = &prm_pGeoActor->_x;
        _pSource_y = &prm_pGeoActor->_y;
        _pSource_z = &prm_pGeoActor->_z;
        _pSourceActor = prm_pGeoActor;
    }

    /**
     * 発射元の回転のみについて、同期をとる発射アクターを設定 .
     * 複数本同時発射などに使用するかな・・・。
     * @param prm_pGeoActor 発射元アクター
     */
    void setAngleSource(GgafDx::GeometricActor* prm_pGeoActor) {
        _pSource_rx = &prm_pGeoActor->_rx;
        _pSource_ry = &prm_pGeoActor->_ry;
        _pSource_rz = &prm_pGeoActor->_rz;
        _pSourceActor = prm_pGeoActor;
    }
    virtual int isOutOfView() override;

    /**
     * レーザーチップの移動速度を指定する .
     * @param prm_velo 移動速度
     */
    void setMvVelo(coord prm_velo);

    /**
     * レーザーチップの移動速度を取得 .
     * @return
     */
    coord getMvVelo() {
        return _velo_mv;
    }
    virtual ~StraightLaserChip();
};

}
#endif /*GGAF_LIB_STRAIGHTLASERCHIP_H_*/

