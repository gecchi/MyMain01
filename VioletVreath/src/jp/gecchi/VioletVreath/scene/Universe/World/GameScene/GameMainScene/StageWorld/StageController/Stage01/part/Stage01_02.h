#ifndef STAGE01_02_H_
#define STAGE01_02_H_
namespace VioletVreath {

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

    virtual ~Stage01_02();
};

}
#endif /*STAGE01_02_H_*/
