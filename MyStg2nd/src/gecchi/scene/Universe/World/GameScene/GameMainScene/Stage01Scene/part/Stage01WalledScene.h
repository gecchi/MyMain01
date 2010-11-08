#ifndef STAGE01WALLEDSCENE_H_
#define STAGE01WALLEDSCENE_H_
namespace MyStg2nd {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01WalledScene : public GgafDx9LibStg::WalledScene {

public:

    Stage01WalledScene(const char* prm_name);

//    static void scroll_X(GgafObject* pThat, void* p1, void* p2);
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
