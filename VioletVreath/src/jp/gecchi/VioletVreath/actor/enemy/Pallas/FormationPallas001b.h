#ifndef FORMATIONPALLAS001B_H_
#define FORMATIONPALLAS001B_H_
namespace VioletVreath {

/**
 * �G�@�p���X�p�t�H�[���[�V��������001-b .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001b : public FormationPallas001 {
public:

    FormationPallas001b(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void onActive() override;

    virtual ~FormationPallas001b();
};

}
#endif /*FORMATIONPALLAS001B_H_*/
