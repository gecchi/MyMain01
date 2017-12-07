#ifndef SMPWORLDMEDIATOR_H_
#define SMPWORLDMEDIATOR_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"

namespace SimpleSample {

/**
 * ����� .
 * @version 1.00
 * @since 2017/12/07
 * @author Masatoshi Tsuge
 */
class SmpWorldMediator : public GgafLib::DefaultSceneMediator {

public:
    /** �e�X�g�L���� */
    SmpActor* pActor_;

    /**
     * �R���X�g���N�^
     * @param prm_pSmpWorld
     * @return
     */
    SmpWorldMediator(GgafLib::DefaultScene* prm_pSmpWorld);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~SmpWorldMediator();
};

}
#endif /*SMPWORLDMEDIATOR_H_*/

