#ifndef VARIETYTORUS002_H_
#define VARIETYTORUS002_H_
namespace MyStg2nd {

/**
 * �n�`�g�[���X�̃o���G�[�V����002 .
 * @version 1.00
 * @since 2010/05/26
 * @author Masatoshi Tsuge
 */
class VarietyTorus002 : public Torus {

public:

    VarietyTorus002(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    virtual ~VarietyTorus002();
};

}
#endif /*VARIETYTORUS002_H_*/

