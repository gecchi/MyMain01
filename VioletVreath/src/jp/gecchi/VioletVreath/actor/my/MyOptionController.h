#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * オプションの纏め役クラス .
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyOptionController : public GgafLib::DefaultMeshSetActor {
class MyOptionController : public GgafDxCore::GgafDxGeometricActor {

public:
    /** [r]最大オプション数 */
    static int max_option_num_;
    /** [r]トレース時のオプションとオプションの間隔 */
    static int o2o_;
    int no_;
    MyOption* pOption_;
//    MyOptionControllerGizmo* pGizmo_;
//    MyOptionControllerDirectionVector* pDirectionVector_;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_OptCtrlGeoHistory_;
    velo veloOptionsMv_;

    /** [r]現在のオプション数 */
    static int now_option_num_;
    /** [r]オプションフリーモードの場合 true */
    bool is_free_from_myship_mode_;
    /** [r]オプションフリーモード時の、オプション操作モードの場合 true */
    bool is_handle_move_mode_;
    /** [r]オプション位置初期化中は true */
    bool return_to_default_position_seq_;

    /** 方向転換角速度 */
    angvelo angVelo_Turn_;
    int renge_;

public:
    MyOptionController(const char* prm_name, int prm_no);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GgafDxGeometricActorの場合はコメントを外すこと
    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);

    static void setNumOption(int prm_num);

    static void adjustDefaltAngPosition(frame prm_spent_frame);

    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

