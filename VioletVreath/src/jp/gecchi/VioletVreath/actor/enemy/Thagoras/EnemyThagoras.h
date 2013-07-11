#ifndef ENEMYTHAGORAS_H_
#define ENEMYTHAGORAS_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X .
 * �g�����W�b�g���x���P
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class EnemyThagoras : public GgafLib::DefaultMeshSetActor {

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
    };
    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]�E���E��������W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem hanging_pos_;
    /** [r]�ޏo���W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem leave_pos_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThagoras(const char* prm_name);

    void onCreateModel() override;

    /**
     * �^�S���X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �^�S���X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �^�S���X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �^�S���X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �^�S���X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyThagoras();
};

}
#endif /*ENEMYTHAGORAS_H_*/

