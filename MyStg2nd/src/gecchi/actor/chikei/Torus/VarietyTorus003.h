#ifndef VARIETYTORUS003_H_
#define VARIETYTORUS003_H_
namespace MyStg2nd {

/**
 * �n�`�g�[���X�̃o���G�[�V����003 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyTorus003 : public Torus {

public:

    VarietyTorus003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyTorus003();
};

}
#endif /*VARIETYTORUS003_H_*/

