#ifndef MGRWORLD_H_
#define MGRWORLD_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/MgrSpacetime.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace Mogera {



/**
 * ���E�V�[���̐��` .
 * GgafLib::DefaultScene ���p�����ăV�[���N���X���쐬���ĉ������B<BR>
 * �{�T���v���ł́u���E�v�V�[���Ɩ��Â��܂����B<BR>
 * processBehavior() ���I�[�o�[���C�h���A���t���[���̏������L�q���܂��B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrWorld : public GgafLib::DefaultScene {

public:
    /** ���͎�t */
    GgafLib::VirtualButton* vb_;

    TrialAndErrScene* pTrialAndErrScene_;
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    MgrWorld(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    void processJudgement() override;

    virtual ~MgrWorld();
};

}

#endif /*MGRWORLD_H_*/