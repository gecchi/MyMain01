#ifndef VVVWORLD_H_
#define VVVWORLD_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "VvvCaretaker.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/dx/actor/FigureActor.h"

namespace VVViewer {

/**
 * VVViewerの世界シーン .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvWorld : public GgafLib::DefaultScene {

public:
    /** 表示中モデルのリスト */
    class ActorInfo {
    public:
        GgafDx::FigureActor* pActor_;
        GgafLib::WorldCollisionChecker* pCollisionChecker_;
        std::string modelfile_;
        ActorInfo(GgafDx::FigureActor* pActor, GgafLib::WorldCollisionChecker* pCollisionChecker, std::string modelfile) {
            pActor_ = pActor;
            pCollisionChecker_ = pCollisionChecker;
            modelfile_ = modelfile;
        }
        ~ActorInfo() {
            pActor_->end();
        }
    };

    GgafCore::RingLinkedList<ActorInfo> listActorInfo_;
    /** 入力受付 */
    GgafLib::VirtualButton* vb_;
    /** カーソル */
    VvvCursor* pCursor_;
    /** グリッド */
    VvvGrid* pGrid_;
    /** カメラマン */
    VvvCamWorker* pCamWorker_;
    /****/
    Font01* pFont01_help_;
    Font01* pFont01_info_;
    bool view_info_;
    bool view_help_;
    VvvMousePointer* pVvvMousePointer_;

    double _w_r;
    double _h_r;
    pixcoord _buffer_left1;
    pixcoord _buffer_top1;
    pixcoord _buffer_width1;
    pixcoord _buffer_height1;
    std::map<int, int> mapNumDik_;
    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    VvvWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
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
