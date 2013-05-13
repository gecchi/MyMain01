#ifndef ENEMYPALISANA_H_
#define ENEMYPALISANA_H_
namespace VioletVreath {

/**
 * �G�@�p���T�i .
 * Adelheid�̃n�b�`�B
 * @version 1.00
 * @since 2014/04/16
 * @author Masatoshi Tsuge
 */
class EnemyPalisana : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        PROG_INIT ,
        PROG_ENTRY,
        PROG_HATCH_OPEN,
        PROG_HATCH_OPEN_DONE,
        PROG_HATCH_CLOSE,
        PROG_LEAVE,
    };
    enum {
        SE_DAMAGED  ,
        SE_EXPLOSION,
    };

    enum {
        MPH_HATCH_CLOSE,
        MPH_HATCH_OPEN,
    };

    /** [r/w]�n�b�`�J���� �y�сA���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyPalisana(const char* prm_name);

    /**
     * �p���T�i���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;

    /**
     * �p���T�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �p���T�i�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �p���T�i�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * �p���T�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �p���T�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    void acitve_open(frame prm_delay = 1);

    bool isOpenDone();

    void close_sayonara();

    virtual ~EnemyPalisana();
};

}
#endif /*ENEMYPALISANA_H_*/

