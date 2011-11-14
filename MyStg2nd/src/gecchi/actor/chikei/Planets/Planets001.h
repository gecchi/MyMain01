#ifndef PLANETS001_H_
#define PLANETS001_H_
namespace MyStg2nd {

/**
 * òfêØ001 .
 * @version 1.00
 * @since 2011/11/14
 * @author Masatoshi Tsuge
 */
class Planets001 : public GgafLib::DefaultMeshActor {

public:

    Planets001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual int isOutOfView() override {
        return 0;
    }

    virtual bool isOutOfUniverse() override;

    virtual ~Planets001();

};

}
#endif /*PLANETS001_H_*/

