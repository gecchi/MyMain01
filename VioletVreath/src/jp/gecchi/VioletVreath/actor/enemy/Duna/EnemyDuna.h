#ifndef ENEMYDUNA_H_
#define ENEMYDUNA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�h�D�[�i(�쐬���I) .
 * ���[���N���X�^�̃R�[���h�A�C�̂悤�ȓ����ɒ���b�I�I�B
 * @version 1.00
 * @since 2013/08/22
 * @author Masatoshi Tsuge
 */
class EnemyDuna : public GgafLib::DefaultMorphMeshActor {

public:
    enum {
        MPH_OPEN = 1,
    };

    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY_EFFECT,
        PROG_ENTRY_MOVE01,
        PROG_ENTRY_MOVE02,
        PROG_MOVE_ORDER_LARGE_SEMIARC_CW,
        PROG_MOVE_ORDER_LARGE_SEMIARC_CCW,
        PROG_MOVE_REV_LARGE_SEMIARC_CW,
        PROG_MOVE_REV_LARGE_SEMIARC_CCW,
        PROG_MOVE_ORDER_SMALL_SEMIARC_CW,
        PROG_MOVE_ORDER_SMALL_SEMIARC_CCW,
        PROG_MOVE_REV_SMALL_SEMIARC_CW,
        PROG_MOVE_REV_SMALL_SEMIARC_CCW,
        PROG_CLOSE ,
        PROG_BANPEI,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    GgafDxCore::GgafDxGeoElem next_pos_;
    int num_fire_;
    int nprog_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyDuna(const char* prm_name);

    void onCreateModel() override;

    /**
     * �h�D�[�i�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �h�D�[�i���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �h�D�[�i�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �h�D�[�i�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �h�D�[�i�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyDuna();
};

}
#endif /*ENEMYDUNA_H_*/

