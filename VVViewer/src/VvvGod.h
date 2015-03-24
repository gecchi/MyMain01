#ifndef VVVGOD_H_
#define VVVGOD_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/DefaultGod.h"

#include "scene/VvvSpacetime.h"

#undef P_GOD
#define P_GOD ((VVViewer::VvvGod*)VVViewer::VvvGod::_pGod)

namespace VVViewer {

/**
 * VVViewer�_ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvGod : public GgafLib::DefaultGod {

public:
    static bool is_wm_dropfiles_;
    static char dropfiles_[2048];

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance �C���X�^���X�n���h��
     * @param prm_hWnd1 �P��ʖڃE�C���h�E�n���h��
     * @param prm_hWnd2 �Q��ʖڃE�C���h�E�n���h��
     */
    VvvGod();

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafSpacetime* createSpacetime() override;

    virtual VvvSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (VvvSpacetime*)_pSpacetime;
    }

    virtual ~VvvGod();
};

}
#endif /*VVVGOD_H_*/
