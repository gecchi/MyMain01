#ifndef VVVWORLD_H_
#define VVVWORLD_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "VvvGod.h"
#include "jp/ggaf/core/util/LinkedListRing.hpp"

namespace VVViewer {

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
        GgafDx::FigureActor* pActor_;
        std::string modelfile_;
        ActorInfo(GgafDx::FigureActor* pActor, std::string modelfile) {
            pActor_ = pActor;
            modelfile_ = modelfile;
        }
    };

    GgafCore::LinkedListRing<ActorInfo> listActorInfo_;
    /** ���͎�t */
    GgafLib::VirtualButton* vb_;
    /** �J�[�\�� */
    VvvCursor* pCursor_;
    /** �O���b�h */
    VvvGrid* pGrid_;
    /** �J�����}�� */
    VvvCamWorker* pCamWorker_;
    /****/
    Font01* pFont01_help_;
    Font01* pFont01_info_;
    bool view_info_;
    bool view_help_;


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
