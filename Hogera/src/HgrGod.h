#ifndef HGRGOD_H_
#define HGRGOD_H_
#include "Hogera.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/HgrSpacetime.h"

#undef P_GOD
#define P_GOD ((Hogera::HgrGod*)GgafCore::God::_pGod)

namespace Hogera {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::Spacetime* createSpacetime() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrGod : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance �C���X�^���X�n���h��
     * @param prm_hWnd1 �P��ʖڃE�C���h�E�n���h��
     * @param prm_hWnd2 �Q��ʖڃE�C���h�E�n���h��
     */
    HgrGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::Spacetime* createSpacetime() override;

    virtual HgrSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (HgrSpacetime*)_pSpacetime;
    }

    virtual ~HgrGod();
};

}
#endif /*HGRGOD_H_*/
