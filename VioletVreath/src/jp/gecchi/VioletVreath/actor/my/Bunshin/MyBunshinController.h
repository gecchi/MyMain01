#ifndef MYBUNSHINCONTROLLER_H_
#define MYBUNSHINCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"
#include "jp/gecchi/VioletVreath/Caretaker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

namespace VioletVreath {


/**
 * 分身コントローラー .
 * MyBunshinBase から分離。MyBunshin から取り込み。
 * 階層構造、全て FK で追加
 * MyBunshinBase ＞ MyBunshinController ＞MyBunshin
 * @version 1.00
 * @since 2023/03/08
 * @author Masatoshi Tsuge
 */
class MyBunshinController : public GgafLib::DefaultGeometricActor {

public:
    MyBunshinBase* pBase_;
    MyBunshin* pBunshin_;
public:
    MyBunshinController(const char* prm_name, MyBunshinBase* prm_pBase);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    virtual ~MyBunshinController();

    /**
     * フリーモードへ移行時の点火エフェクト .
     */
    void effectFreeModeIgnited();
    /**
     * フリーモードへ一時停止時のエフェクト .
     */
    void effectFreeModePause();

    void setRadiusPosition(coord prm_radius_pos);
    void addRadiusPosition(coord prm_radius_pos);
    coord getRadiusPosition();

    void slideMvRadiusPosition(coord prm_target_radius_pos, frame prm_spent_frames);

    void addExpanse(angvelo prm_ang_expanse);
    angvelo getExpanse();
    void turnExpanse(coord prm_target_ang_expanse, frame prm_spent_frames);
};

}
#endif /*MYBUNSHINCONTROLLER_H_*/

