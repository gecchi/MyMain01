#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * 壁ブロックシーン .
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::ScrolledScene {

public:

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;
    WalledScene(const char* prm_name);

    /**
     *
     * @param prm_wall_dep
     * @param prm_wall_width
     * @param prm_wall_height
     * @param prm_papSection
     * @param prm_section_num
     * @param prm_pDispatcher_Wall
     * @param prm_pFuncWallMove
     */
    void build(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Wall, void (*prm_pFuncWallMove)(GgafObject*, void*, void*)
         );

    /**
     * 初期処理
     */
    void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
