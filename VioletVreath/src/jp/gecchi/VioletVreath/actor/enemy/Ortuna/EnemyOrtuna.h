#ifndef ENEMYORTUNA_H_
#define ENEMYORTUNA_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�I���g�D�i .
 * �r���[�|�C���g�Q�ʐ��ʂ��烏�������o�鋛�G���݂����Ȃ��
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class EnemyOrtuna : public GgafLib::DefaultMorphMeshActor {

public:

    enum {
        MPH_OPEN = 1,
    };

    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_MOVE02 ,
        PROG_MOVE03 ,
        PROG_BANPEI,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;
    /** [r]�܂�Ԃ����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem hanging_pos_;

    frame hanging_pos_frames_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOrtuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * �I���g�D�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �I���g�D�i�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �I���g�D�i�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �I���g�D�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �I���g�D�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;


    virtual ~EnemyOrtuna();
};

}
#endif /*ENEMYAPPHO_H_*/
