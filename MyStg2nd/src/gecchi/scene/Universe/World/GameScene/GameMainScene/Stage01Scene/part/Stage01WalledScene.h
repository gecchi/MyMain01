#ifndef STAGE01WALLEDSCENE_H_
#define STAGE01WALLEDSCENE_H_
namespace MyStg2nd {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01WalledScene : public GgafDx9LibStg::ScrolledScene {
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

    Stage01WalledScene(const char* prm_name);
    static void moveX(GgafObject* pThat, void* p1, void* p2);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01WalledScene();
};

}
#endif /*STAGE01WALLEDSCENE_H_*/
