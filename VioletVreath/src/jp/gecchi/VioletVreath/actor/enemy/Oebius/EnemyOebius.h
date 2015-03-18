#ifndef ENEMYOEBIUS_H_
#define ENEMYOEBIUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�r�E�X .
 * ���r�E�X�̑т̕ґ��v��
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class EnemyOebius : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE_BEGIN ,
        PROG_SPLINE ,
        PROG_SCATTER ,
        PROG_LEAVE ,
        PROG_BANPEI,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** �ړ��X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pKurokoLeader_;

    bool scatter_flg_;

    frame delay_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyOebius(const char* prm_name);

    void onCreateModel() override;

    /**
     * �G�r�E�X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �G�r�E�X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �G�r�E�X�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �G�r�E�X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �G�r�E�X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * �U��U��ɂȂ� .
     */
    void scatter();


    virtual ~EnemyOebius();
};

}
#endif /*ENEMYOEBIUS_H_*/

