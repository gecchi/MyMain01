#ifndef FORMATIONPALLAS001A_H_
#define FORMATIONPALLAS001A_H_
namespace MyStg2nd {

/**
 * �G�@�p���X�p�t�H�[���[�V��������001-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001a : public FormationPallas001 {
public:

    FormationPallas001a(const char* prm_name);

    /**
     * �ґ����쐬 .
     */
    virtual void onActive() override;

    virtual ~FormationPallas001a();
};

}
#endif /*FORMATIONPALLAS001A_H_*/
