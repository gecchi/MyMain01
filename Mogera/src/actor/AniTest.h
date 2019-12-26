#ifndef ANITEST_H_
#define ANITEST_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"
#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * �G�@�A�j�����q .
 * @version 1.00
 * @since 2015/02/13
 * @author Masatoshi Tsuge
 */
class AniTest : public GgafLib::DefaultBoneAniMeshActor {
//    class AniTest : public GgafLib::DefaultSkinAniMeshActor {
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    AniTest(const char* prm_name);

    void onCreateModel() override;

    /**
     * �A�j�����q�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �A�j�����q���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �A�j�����q�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �A�j�����q�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �A�j�����q�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~AniTest();
};

}
#endif /*ANITEST_H_*/

