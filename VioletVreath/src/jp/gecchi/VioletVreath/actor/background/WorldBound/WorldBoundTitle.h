#ifndef WORLDBOUNDTITLE_H_
#define WORLDBOUNDTITLE_H_
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

/**
 * �^�C�g���̐��E��� .
 * @version 1.00
 * @since 2012/01/10
 * @author Masatoshi Tsuge
 */
class WorldBoundTitle : public GgafLib::WorldBoundActor {

public:
    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    WorldBoundTitle(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void fadein();

    virtual ~WorldBoundTitle();
};

}
#endif /*WORLDBOUNDTITLE_H_*/

