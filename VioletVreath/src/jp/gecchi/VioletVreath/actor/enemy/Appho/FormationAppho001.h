#ifndef FORMATIONAPPHO001_H_
#define FORMATIONAPPHO001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�A�b�|�[�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationAppho001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Appho_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;

    int cnt_called_up_;

public:
    FormationAppho001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCalledUpAppho(EnemyAppho* prm_pAppho, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual ~FormationAppho001();
};

}
#endif /*FORMATIONAPPHO001_H_*/
