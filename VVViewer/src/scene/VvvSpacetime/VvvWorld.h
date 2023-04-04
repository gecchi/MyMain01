#ifndef VVVWORLD_H_
#define VVVWORLD_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "VvvCaretaker.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"

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
        GgafLib::WorldCollisionChecker* pCollisionChecker_;
        std::string dropfile_;
        bool is_model_x_;
        ActorInfo(GgafDx::FigureActor* pActor, GgafLib::WorldCollisionChecker* pCollisionChecker, std::string dropfile, bool is_model_x) {
            pActor_ = pActor;
            pCollisionChecker_ = pCollisionChecker;
            dropfile_ = dropfile;
            is_model_x_=is_model_x;
        }
        ~ActorInfo() {
            pActor_->end();
        }
    };

    GgafCore::RingLinkedList<ActorInfo> listActorInfo_;
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
    VvvMousePointer* pVvvMousePointer_;

    double _w_r;
    double _h_r;
    pixcoord _primary_buffer_source_left;
    pixcoord _primary_buffer_source_top;
    pixcoord _primary_buffer_source_width;
    pixcoord _primary_buffer_source_height;
    std::map<int, int> mapNumDik_;
    char aBufDebug_[256];
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

    void manipulateWorld();

    void manipulateActiveActor(GgafDx::FigureActor* prm_pActiveActor);

    void behaveActor(GgafDx::FigureActor* prm_pActor);

    void processDragAndDrop();

    virtual ~VvvWorld();
};

}
#endif /*VVVWORLD_H_*/
