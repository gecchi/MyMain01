#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace GgafDx9LibStg {

/**
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::ScrolledScene {
//    class Section {
//    public :
//        GgafDx9LibStg::WalledSectionScene* _pScene;
//        int _repeat;
//        Section(GgafDx9LibStg::WalledSectionScene* prm_pScene, int prm_repeat) {
//            _pScene = prm_pScene;
//            _repeat = prm_repeat;
//        }
//    };

public:

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;
    WalledScene(const char* prm_name);

    void build(
            int prm_wall_dep, int prm_wall_width, int prm_wall_height,
            WalledSectionScene** prm_papSection, int prm_section_num,
            GgafCore::GgafActorDispatcher* prm_pDispatcher_Wall, void (*prm_pFuncWallMove)(GgafObject*, void*, void*)
         );

    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
