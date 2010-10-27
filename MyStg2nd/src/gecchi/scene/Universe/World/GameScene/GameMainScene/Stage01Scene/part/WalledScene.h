#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace MyStg2nd {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::DefaultScene {
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

    WalledScene(const char* prm_name);
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
