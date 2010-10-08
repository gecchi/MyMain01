#ifndef GROUNDBOXSCENE_H_
#define GROUNDBOXSCENE_H_
namespace MyStg2nd {

/**
 * GROUNDBOX .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class GroundBoxScene : public GgafDx9LibStg::DefaultScene {


public:

    GroundBoxScene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~GroundBoxScene();
};

}
#endif /*STAGE01_01_H_*/
