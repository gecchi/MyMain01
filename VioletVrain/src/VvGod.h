#ifndef VVGOD_H_
#define VVGOD_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvSpacetime.h"

#undef P_GOD
#define P_GOD ((VioletVrain::VvGod*)GgafCore::GgafGod::_pGod)

namespace VioletVrain {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::GgafSpacetime* createSpacetime() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvGod : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance �C���X�^���X�n���h��
     * @param prm_hWnd1 �P��ʖڃE�C���h�E�n���h��
     * @param prm_hWnd2 �Q��ʖڃE�C���h�E�n���h��
     */
    VvGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafSpacetime* createSpacetime() override;

    virtual VvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvSpacetime*)_pSpacetime;
    }

    virtual ~VvGod();
};

}
#endif /*VVGOD_H_*/
