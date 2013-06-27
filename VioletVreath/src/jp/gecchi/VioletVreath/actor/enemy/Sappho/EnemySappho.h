#ifndef ENEMYSAPPHO_H_
#define ENEMYSAPPHO_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�T�b�t�H�[ .
 * ���A�˂U�WK�̎G���̂悤�ɁA
 * ����āA�ڂ̑O�ɃX�[���Ɨ��āA
 * ������ƃE���E�����āA�X�[���Ɠ�����B
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class EnemySappho : public GgafLib::DefaultMeshSetActor {

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
    /** [r]����G�t�F�N�g */
    GgafDxCore::GgafDxDrawableActor* pEntryEffect_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemySappho(const char* prm_name);

    void onCreateModel() override;

    /**
     * �T�b�t�H�[�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �T�b�t�H�[�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �T�b�t�H�[�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �T�b�t�H�[�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �T�b�t�H�[�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemySappho();
};

}
#endif /*ENEMYSAPPHO_H_*/

