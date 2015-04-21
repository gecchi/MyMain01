#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 分身土台 .
 * @version 1.00
 * @since 2015/04/17
 * @author Masatoshi Tsuge
 */
class MyBunshinBase : public GgafLib::DefaultMeshActor {
//class MyBunshinBase : public GgafDxCore::GgafDxGeometricActor {

public:
    /** 最大分身数 */
    static int max_bunshin_num_;
    /** [r]分身と分身の間隔 */
    static frame bunshin_d_;

    /** [r]分身本体 */
    MyBunshin* pBunshin_;
    /** 自機トレースの座標からのオフセット(フリーでない場合は0) */
    GgafDxCore::GgafDxGeoElem trace_offset_;
    /** 分身番号(1～) */
    int no_;

    /** [r]自身を中心とした、分身の公転の半径 */
    coord bunshin_radius_position_;
    /** [r]自身を中心とした、分身の公転軌道上の位置 */
    angle bunshin_ang_position_;
    /** [r]分身の広がり角度 */
    angle bunshin_expanse_;
    /** [r]自身を中心とした、分身の公転の角速度 */
    angvelo bunshin_angvelo_mv_;

public:
    MyBunshinBase(const char* prm_name, int prm_no);

    void config(
            coord prm_radius_position,
            angle prm_ang_position,
            angle prm_expanse,
            angvelo prm_angvelo_mv);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GgafDxGeometricActorの場合はコメントを外すこと
    //virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    virtual ~MyBunshinBase();


};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

