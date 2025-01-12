#ifndef ANITEST3_H_
#define ANITEST3_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultSkinAniMeshActor.h"

#include <iostream>
#include <fstream>

namespace Mogera {

/**
 * �G�@�A�j�����q .
 * @version 1.00
 * @since 2015/02/13
 * @author Masatoshi Tsuge
 */
class AniTest3 : public GgafLib::DefaultSkinAniMeshActor {
public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    AniTest3(const char* prm_name);

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
     */
    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override;


    void onInactive() override;


    virtual ~AniTest3();
};

}
#endif /*ANITEST3_H_*/

