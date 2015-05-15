#ifndef MYLOCKONCONTROLLER_H_
#define MYLOCKONCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/ex/GgafDestructActor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace VioletVreath {


/**
 * ���b�N�I���R���g���[���[ .
 * @version 1.00
 * @since 2010/09/08
 * @author Masatoshi Tsuge
 */
class MyLockonController : public GgafCore::GgafDestructActor {

public:
    /** [r]�P�I�v�V����������̍ő�\���b�N�I���� */
    static int max_lockon_num_;
    /** [r]�P�I�v�V����������̌��݉\���b�N�I���� */
    static int lockon_num_;

    /** ���C�����b�N�I���G�t�F�N�g */
    EffectLockon001_Main* pMainLockonEffect_;
    /** ���b�N�I���^�[�Q�b�g���X�g�����O */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeometricActor>* pRingTarget_;

public:
    MyLockonController(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseAllLockon();

    void lockon(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~MyLockonController();
    /**
     * pRingTarget_���e�\��(�f�o�b�O�p) .
     * @param pMain
     */
    void dumpTarget(GgafDxCore::GgafDxGeometricActor* pMain);

};

}
#endif /*MYLOCKONCONTROLLER_H_*/

