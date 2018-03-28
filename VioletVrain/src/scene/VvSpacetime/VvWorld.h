#ifndef VVWORLD_H_
#define VVWORLD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/VvSpacetime.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/ggaf/lib/util/Quantity.hpp"
#include "jp/ggaf/lib/util/VirtualButton.h"

namespace VioletVrain {

/**
 * ���E�V�[���̐��` .
 * GgafLib::DefaultScene ���p�����ăV�[���N���X���쐬���ĉ������B<BR>
 * �{�T���v���ł́u���E�v�V�[���Ɩ��Â��܂����B<BR>
 * processBehavior() ���I�[�o�[���C�h���A���t���[���̏������L�q���܂��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvWorld : public GgafLib::DefaultScene {

public:
    /** ���͎�t */
    GgafLib::VirtualButton vb_;

    TrialAndErrScene* pTrialAndErrScene_;

    GgafLib::QuadtreeRounder* pHitCheckRounder_;
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    VvWorld(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~VvWorld();
};

}

#endif /*VVWORLD_H_*/
