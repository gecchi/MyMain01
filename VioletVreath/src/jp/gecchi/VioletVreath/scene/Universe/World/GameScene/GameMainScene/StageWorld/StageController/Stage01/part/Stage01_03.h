#ifndef STAGE01_03_H_
#define STAGE01_03_H_
namespace VioletVreath {

/**
 * ƒXƒe[ƒW‚P|‚R .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01_03 : public GgafLib::DefaultScene {


public:
    Stage01_03(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01_03();
};

}
#endif /*STAGE01_03_H_*/
