#ifndef VARIETYSYLVIA003_H_
#define VARIETYSYLVIA003_H_
namespace VioletVreath {

/**
 * �n�`�g�[���X�̃o���G�[�V����003 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietySylvia003 : public EnemySylvia {

public:
    VarietySylvia003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietySylvia003();
};

}
#endif /*VARIETYSYLVIA003_H_*/

