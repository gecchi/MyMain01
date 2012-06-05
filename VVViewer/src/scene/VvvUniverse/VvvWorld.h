#ifndef SMPWORLD_H_
#define SMPWORLD_H_
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
    /** 入力受付 */
    GgafLib::VirtualButton* vb_;
    /** テストキャラ */
    VvvActor* pActor_;
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
#endif /*SMPWORLD_H_*/
