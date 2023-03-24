#ifndef FORMATIONALLAS001_H_
#define FORMATIONALLAS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * �G�@�A���X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationAllas001 : public GgafLib::TreeFormation {

public:
    /** �A���X�̔��˒e�̎؂���ꌳDepository�����ւ̐ڑ� */
    DepositoryConnection* pConn_depo_;
    /** �Ȑ��ړ��̏�񎑌��ւ̐ڑ� */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    /** �ґ���(RANK�ϓ�) */
    int num_Allas_;
    /** �ґ��Ԋu�t���[��(RANK�ϓ�) */
    frame interval_frames_;
    /** �ړ����x(RANK�ϓ�) */
    velo velo_mv_;

public:
    FormationAllas001(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void onCalledUpAllas(EnemyAllas* prm_pAllas) = 0;

    virtual ~FormationAllas001();
};

}
#endif /*FORMATIONALLAS001_H_*/
