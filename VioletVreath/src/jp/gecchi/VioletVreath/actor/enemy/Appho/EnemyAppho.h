#ifndef ENEMYAPPHO_H_
#define ENEMYAPPHO_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�A�b�|�[ .
 * ���A�˂U�WK�̎G���̂悤�ɁA
 * ����āA�ڂ̑O�ɃX�[���Ɨ��āA
 * ������ƃE���E�����āA�X�[���Ɠ�����B
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemyAppho : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_MOVE03 ,
        PROG_MOVE04 ,
        PROG_BANPEI ,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]�E���E��������W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem stagnating_pos_;
    /** [r]�ޏo���W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem leave_pos_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAppho(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�b�|�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A�b�|�[�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�b�|�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�b�|�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�b�|�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyAppho();
};

}
#endif /*ENEMYAPPHO_H_*/

