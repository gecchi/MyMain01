#ifndef FORMATIONHALIA_H_
#define FORMATIONHALIA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�n���A�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationHalia : public GgafLib::TreeFormation {
public:
    /** �ґ���(RANK�ϓ�) */
    int num_Halia_;
    /** �n���A�̔z��(RANK�ϓ�) */
    EnemyHalia** papHalia_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;


public:
    FormationHalia(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationHalia();
};

}
#endif /*FORMATIONHALIA_H_*/
