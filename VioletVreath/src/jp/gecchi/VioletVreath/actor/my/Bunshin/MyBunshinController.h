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
 * ���g�R���g���[���[ .
 * MyBunshinBase ���番���BMyBunshin �����荞�݁B
 * �K�w�\���A�S�� FK �Œǉ�
 * MyBunshinBase �� MyBunshinController ��MyBunshin
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
     * �t���[���[�h�ֈڍs���̓_�΃G�t�F�N�g .
     */
    void effectFreeModeIgnited();
    /**
     * �t���[���[�h�ֈꎞ��~���̃G�t�F�N�g .
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

