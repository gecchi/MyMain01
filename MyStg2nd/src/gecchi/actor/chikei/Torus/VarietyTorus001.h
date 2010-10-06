#ifndef VARIETYTORUS001_H_
#define VARIETYTORUS001_H_
namespace MyStg2nd {

/**
 * 地形トーラスのバリエーション001 .
 * @version 1.00
 * @since 2010/05/23
 * @author Masatoshi Tsuge
 */
class VarietyTorus001 : public Torus {

public:

    VarietyTorus001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyTorus001();
};

}
#endif /*VARIETYTORUS001_H_*/

