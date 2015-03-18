#ifndef ENEMYANTIOPE_H_
#define ENEMYANTIOPE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�A���e�B�I�y .
 * �����Ɣ������̏u���̂悤�ȃC���[�W�̓���
 * @version 1.00
 * @since 2013/04/08
 * @author Masatoshi Tsuge
 */
class EnemyAntiope :
    public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION,
    };

    enum {
        PROG_INIT  ,
        PROG_ENTRY ,
        PROG_MOVE01,
        PROG_LEAVE ,
        PROG_RUSH,
        PROG_BANPEI,
    };

    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

    GgafDxCore::GgafDxGeoElem mv_velo_twd_;

    /** ���� */
    EnemyAntiope* pP_;
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyAntiope(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    void onCreateModel() override;

    /**
     * �A���e�B�I�y�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A���e�B�I�y�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A���e�B�I�y�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A���e�B�I�y�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A���e�B�I�y�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyAntiope();
};

}
#endif /*ENEMYANTIOPE_H_*/

