#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
#include "VioletVreath.h"
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
    /** [r]現在装備中のオプション数 */
    static int now_option_num_;

    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;
    /** 自身のオプションインデックス 0 ～ now_option_num_-1 */
    int no_;
    MyOption* pOption_;
//    MyOptionControllerGizmo* pGizmo_;
//    MyOptionControllerDirectionVector* pDirectionVector_;

    /** オプションコントローラーの毎フレームの絶対座標履歴 */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_OptCtrlGeoHistory_;
    velo veloOptionsMv_;


    /** [r]オプションフリーモードの場合 true */
    bool is_free_from_myship_mode_;
    /** [r]オプションフリーモード時の、オプション操作モードの場合 true */
    bool is_handle_move_mode_;
    /** [r]オプション位置初期化中は true */
    bool return_to_default_position_seq_;

    /** 方向転換角速度 */
    angvelo angVelo_Turn_;
    int renge_;

    /** オプションフリーモードへの準備の点火カウンター */
    int ignite_option_cnt_;
    /** オプションフリーモードへ移行するための、必要な点火のカウント時間 */
    frame frame_of_ignite_option_;
    /** オプションフリーモードへの準備の点火カウントモードの場合 true */
    bool ignited_option_cnt_mode_;
    /** 点火され、オプションフリーモードへの移行可能な状態の場合 true */
    bool was_ignited_option_;

    enum {
        SE_RESTORE  ,
        SE_FREE  ,
    };

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

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_ang_rz_target, angle prm_ang_ry_target);

    static void setNumOption(int prm_num);

    static void adjustDefaltAngPosition(frame prm_spent_frame);
    static void adjustDefaltAngPosition(frame prm_spent_frame, int prm_start_opt_no, int prm_end_opt_no);
    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

