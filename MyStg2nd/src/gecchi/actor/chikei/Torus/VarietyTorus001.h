#ifndef VARIETYTORUS001_H_
#define VARIETYTORUS001_H_
namespace MyStg2nd {

/**
 * ínå`ÉgÅ[ÉâÉXÇOÇOÇP .
 * @version 1.00
 * @since 2010/05/23
 * @author Masatoshi Tsuge
 */
class VarietyTorus001 : public Torus {

public:

    VarietyTorus001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~VarietyTorus001();
};

}
#endif /*VARIETYTORUS001_H_*/

