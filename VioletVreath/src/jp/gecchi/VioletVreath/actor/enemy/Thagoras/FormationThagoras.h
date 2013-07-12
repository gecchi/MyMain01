#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    /** �ґ���(RANK�ϓ�) */
    int num_Thagoras_;
public:
    FormationThagoras(const char* prm_name, int prm_num_Thagoras);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
