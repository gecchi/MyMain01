#ifndef ENEMYOZARTIAPILLAR01_H_
#define ENEMYOZARTIAPILLAR01_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �I�[�c�@���e�B�A�̕X���i�n�`�����j .
 * @version 1.00
 * @since 2013/10/16
 * @author Masatoshi Tsuge
 */
class EnemyOzartiaPillar01 : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_LEAVE  ,
        PROG_BANPEI,
    };
public:
    EnemyOzartiaPillar01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyOzartiaPillar01();
};

}
#endif /*ENEMYOZARTIAPILLAR01_H_*/

