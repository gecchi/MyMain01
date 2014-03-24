#ifndef FORMATIONORTUNA001_H_
#define FORMATIONORTUNA001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �I���g�D�i�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001 : public GgafLib::TreeFormation {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Ortuna_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;

    int index_call_up_;

public:
    FormationOrtuna001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    /**
     * �I���g�D�iCallUp���ɃR�[���o�b�N����郁�\�b�h�B
     * @param prm_pOrtuna CallUp���ꂽ�I���g�D�i
     * @param prm_index �C���f�b�N�X (0�`�E�E�E)
     */
    virtual void onCallUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationOrtuna001();
};

}
#endif /*FORMATIONORTUNA001_H_*/