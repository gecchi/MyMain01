#ifndef PLANET001_H_
#define PLANET001_H_
namespace VioletVreath {

/**
 * �f��001 .
 * @version 1.00
 * @since 2011/11/14
 * @author Masatoshi Tsuge
 */
class Planet001 : public GgafLib::DefaultMeshActor {

public:

    Planet001Atmosphere* _pAtmosphere;

    Planet001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual int isOutOfView() override {
        return 0;
    }

    virtual bool isOutOfUniverse() override {
        return false;
    }

    virtual ~Planet001();

};

}
#endif /*PLANET001_H_*/

