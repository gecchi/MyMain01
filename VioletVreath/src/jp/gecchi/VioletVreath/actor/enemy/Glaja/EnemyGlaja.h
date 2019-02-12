#ifndef ENEMYGLAJA_H_
#define ENEMYGLAJA_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�O���� .
 * ���^�@�ɂ��悤���B
 * �|�C���ƊʁX���Ȃ��āA�r�V���Ƒ��e�ɕω����Ĕ��ł����B
 * @version 1.00
 * @since 2013/08/19
 * @author Masatoshi Tsuge
 */
class EnemyGlaja : public GgafLib::DefaultMorphMeshActor {

public:
    DepositoryConnection* pConn_pShot_;
    GgafDx::GeoElem next_pos_;
    int num_fire_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyGlaja(const char* prm_name);

    void onCreateModel() override;

    /**
     * �O�����̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �O�������A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �O�����̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �O�����̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �O�����̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    static void onDispatchedShot(GgafDx::FigureActor* prm_pActor, int prm_dispatch_num, int prm_set_index, int prm_way_index);

    virtual ~EnemyGlaja();
};

}
#endif /*ENEMYGLAJA_H_*/

