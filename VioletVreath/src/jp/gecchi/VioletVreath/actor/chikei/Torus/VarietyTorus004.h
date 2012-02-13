#ifndef VARIETYTORUS004_H_
#define VARIETYTORUS004_H_
namespace VioletVreath {

/**
 * 地形トーラスのバリエーション004 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyTorus004 : public Torus {

public:

    VarietyTorus004(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyTorus004();
};

}
#endif /*VARIETYTORUS004_H_*/

