#ifndef ENEMYALISANA_H_
#define ENEMYALISANA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * �G�@�A���T�i .
 * Delheid�̃n�b�`�B
 * @version 1.00
 * @since 2014/04/16
 * @author Masatoshi Tsuge
 */
class EnemyAlisana : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_HATCH_OPEN,
        PROG_HATCH_OPEN_DONE,
        PROG_HATCH_CLOSE,
        PROG_LEAVE,
        PROG_BANPEI,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    enum {
        MPH_HATCH_CLOSE,
        MPH_HATCH_OPEN,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r/w]�n�b�`�J���� �y�сA���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAlisana(const char* prm_name);

    /**
     * �A���T�i���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;

    /**
     * �A���T�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A���T�i�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A���T�i�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * �A���T�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A���T�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    void acitve_open(frame prm_delay = 1);

    bool isOpenDone();

    void close_sayonara();

    virtual ~EnemyAlisana();
};

}
#endif /*ENEMYALISANA_H_*/
