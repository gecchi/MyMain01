#ifndef STAGE01MAIN_H_
#define STAGE01MAIN_H_
namespace MyStg2nd {

/**
 * ƒXƒe[ƒW‚P|‚Q .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01_02 : public GgafLib::DefaultScene {


public:

    Stage01_02(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~Stage01_02();
};

}
#endif /*STAGE01MAIN_H_*/
