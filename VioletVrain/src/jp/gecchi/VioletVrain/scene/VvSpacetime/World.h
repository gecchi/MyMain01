#ifndef VVWORLD_H_
#define VVWORLD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVrain/scene/VvSpacetime.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace VioletVrain {

/**
 * ���E�V�[�� .
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class World : public GgafLib::DefaultScene {

public:
    /** ���͎�t */
    GgafLib::VirtualButton vb_;

    TrialAndErrScene* pTrialAndErrScene_;

    GgafLib::QuadtreeRounder* pHitCheckRounder_;
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    World(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~World();
};

}

#endif /*VVWORLD_H_*/
