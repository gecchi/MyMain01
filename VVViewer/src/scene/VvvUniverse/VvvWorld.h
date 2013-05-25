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
        GgafDxCore::GgafDxDrawableActor* pActor_;
        std::string modelfile_;
        ActorInfo(GgafDxCore::GgafDxDrawableActor* pActor, std::string modelfile) {
            pActor_ = pActor;
            modelfile_ = modelfile;
        }
    };


    GgafCore::GgafLinkedListRing<ActorInfo> _listActorInfo;
    /** 入力受付 */
    GgafLib::VirtualButton* vb_;
    /** カーソル */
    VvvCursor* pCursor_;
    /** グリッド */
    VvvGrid* pGrid_;
    /** カメラマン */
    VvvCamWorker* pCamWorker_;

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

    virtual ~VvvWorld();
};

}
#endif /*VVVWORLD_H_*/
