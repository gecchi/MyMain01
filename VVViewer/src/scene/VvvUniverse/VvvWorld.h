#ifndef VVVWORLD_H_
#define VVVWORLD_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"

namespace VVViewer {

#ifdef P_UNIVERSE
    #define P_WORLD ((VVViewer::VvvWorld*)(P_UNIVERSE->pWorld_))
#else
    #error P_UNIVERSE isnt define
#endif

/**
 * VVViewer�̐��E�V�[�� .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvWorld : public GgafLib::DefaultScene {

public:
    /** �\�������f���̃��X�g */
    class ActorInfo {
    public:
        GgafDxCore::GgafDxDrawableActor* pActor_;
        std::string modelfile_;
        ActorInfo(GgafDxCore::GgafDxDrawableActor* pActor, std::string modelfile) {
            pActor_ = pActor;
            modelfile_ = modelfile;
        }
    };


    GgafCore::GgafLinkedListRing<ActorInfo> _listActorInfo;
    /** ���͎�t */
    GgafLib::VirtualButton* vb_;
    /** �J�[�\�� */
    VvvCursor* pCursor_;
    /** �O���b�h */
    VvvGrid* pGrid_;
    /** �J�����}�� */
    VvvCamWorker* pCamWorker_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     */
    VvvWorld(const char* prm_name);

    /**
     * ���E�V�[���̏������� .
     */
    void initialize() override;

    /**
     * ���E�V�[���̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~VvvWorld();
};

}
#endif /*VVVWORLD_H_*/
