#ifndef ENEMYOZARTIASHOT01_H_
#define ENEMYOZARTIASHOT01_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎩�@���߂����Ē����ړ��B�ĉ������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyOzartiaShot01 : public GgafLib::DefaultMeshSetActor {
public:
    enum {
        PROG_INIT   ,
        PROG_ENTRY  ,
        PROG_MOVE01 ,
        PROG_LEAVE  ,
    };
public:
    EnemyOzartiaShot01(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyOzartiaShot01();
};

}
#endif /*ENEMYOZARTIASHOT01_H_*/

