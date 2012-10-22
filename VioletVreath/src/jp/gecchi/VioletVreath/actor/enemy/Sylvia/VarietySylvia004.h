#ifndef VARIETYSYLVIA004_H_
#define VARIETYSYLVIA004_H_
namespace VioletVreath {

/**
 * 地形トーラスのバリエーション004 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietySylvia004 : public EnemySylvia {

public:

    VarietySylvia004(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietySylvia004();
};

}
#endif /*VARIETYSYLVIA004_H_*/

