#ifndef FORMATIONAPPHO001_H_
#define FORMATIONAPPHO001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�A�b�|�[�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationAppho001 : public GgafLib::TreeFormation {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Appho_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;

    int cnt_call_up_;

public:
    FormationAppho001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpAppho(EnemyAppho* prm_pAppho, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationAppho001();
};

}
#endif /*FORMATIONAPPHO001_H_*/
