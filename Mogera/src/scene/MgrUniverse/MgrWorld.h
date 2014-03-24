#ifndef MGRWORLD_H_
#define MGRWORLD_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "scene/MgrUniverse.h"
#include "jp/ggaf/lib/util/PxQuantity.h"


namespace Mogera {

#ifdef P_UNIVERSE
    #define P_WORLD ((Mogera::MgrWorld*)(P_UNIVERSE->pWorld_))
#else
    #error P_UNIVERSE isnt define
#endif

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
    TestActor* pBack_;
    MgrActor* pMgrActor1_;
    Teki001* pTeki_;
    Teki002* pTeki002_;
    Mikata001* pMikata_;
    TestBar* pTestBar_;
    TestCappedBar* pBar_;
    int mp_;
//    GgafLib::PxQuantity* pBarVal_;

    static std::string key_;
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