#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

namespace VioletVreath {

/**
 * �e�X�g�p .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafLib::SpriteMeshSetActor {

public:
    /** �s���p�^�[���ԍ� */
    int iMovePatternNo_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineLeader* pProgram_Tamago01Move_;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_shot_;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* pDepo_effect_;

    DepositoryConnection* pConn_depo_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

    /**
     * ���܂����f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * ���܂��̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���܂����A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���܂��̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * ���܂��̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * ���܂��̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒e�ݒ� .
     * @param prm_pDepo (GgafDxFigureActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_shot_ = prm_pDepo;
    }

    /**
     * ���ʃG�t�F�N�g�ݒ� .
     * @param prm_pDepo (GgafDxFigureActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_ShotEffect(GgafCore::GgafActorDepository* prm_pDepo) {
        pDepo_effect_ = prm_pDepo;
    }

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/

