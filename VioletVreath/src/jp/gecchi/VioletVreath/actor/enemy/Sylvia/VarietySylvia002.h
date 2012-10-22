#ifndef VARIETYSYLVIA002_H_
#define VARIETYSYLVIA002_H_
namespace VioletVreath {

/**
 * 地形トーラスのバリエーション002 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietySylvia002 : public EnemySylvia {

public:

    VarietySylvia002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietySylvia002();
};

}
#endif /*VARIETYSYLVIA002_H_*/

