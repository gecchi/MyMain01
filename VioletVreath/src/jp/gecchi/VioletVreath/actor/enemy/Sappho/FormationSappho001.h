#ifndef FORMATIONSAPPHO001_H_
#define FORMATIONSAPPHO001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�T�b�t�H�[�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationSappho001 : public GgafLib::TreeFormation {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Sappho_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;

    int cnt_call_up_;

public:
    FormationSappho001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onCallUpSappho(EnemySappho* prm_pSappho, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationSappho001();
};

}
#endif /*FORMATIONSAPPHO001_H_*/
