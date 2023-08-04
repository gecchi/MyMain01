#ifndef FORMATIONORTUNA001_H_
#define FORMATIONORTUNA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �I���g�D�i�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001 : public VvFormationActor<GgafLib::TreeFormation> {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Ortuna_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;

    int index_called_up_;

public:
    FormationOrtuna001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    /**
     * �I���g�D�iCalledUp���ɃR�[���o�b�N����郁�\�b�h�B
     * @param prm_pOrtuna CalledUp���ꂽ�I���g�D�i
     * @param prm_index �C���f�b�N�X (0�`�E�E�E)
     */
    virtual void onCalledUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) = 0;

    virtual void processBehavior() override;

    virtual ~FormationOrtuna001();
};

}
#endif /*FORMATIONORTUNA001_H_*/
