#ifndef MGRGOD_H_
#define MGRGOD_H_
#include "jp/ggaf/lib/DefaultGod.h"

namespace Mogera {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::GgafUniverse* createUniverse() ���I�[�o�[���C�h���������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrGod : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance �C���X�^���X�n���h��
     * @param prm_hWnd1 �P��ʖڃE�C���h�E�n���h��
     * @param prm_hWnd2 �Q��ʖڃE�C���h�E�n���h��
     */
    MgrGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2);

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~MgrGod();
};

}
#endif /*MGRGOD_H_*/
