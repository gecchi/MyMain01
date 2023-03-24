#ifndef MYLOCKONCONTROLLER_H_
#define MYLOCKONCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/core/actor/ex/DestructActor.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace VioletVreath {

/**
 * ���b�N�I���R���g���[���[ .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::DestructActor {

public:
    /** [r]�P�I�v�V����������̌��݉\���b�N�I���� */
    static int lockon_num_;

    /** ���C�����b�N�I���G�t�F�N�g */
    LockonCursor001_Main* pMainLockonCursor_;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    GgafCore::RingLinkedList<GgafDx::GeometricActor> listTarget_;

public:
    MyLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseAllLockon();

    void lockon(GgafDx::GeometricActor* prm_pTarget);

    virtual ~MyLockonController();
    /**
     * pRingTarget_���e�\��(�f�o�b�O�p) .
     * @param pMain
     */
    void dumpTarget(GgafDx::GeometricActor* pMain);

};

}
#endif /*MYLOCKONCONTROLLER_H_*/

