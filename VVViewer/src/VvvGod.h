#ifndef SMPGOD_H_
#define SMPGOD_H_
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

    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance �C���X�^���X�n���h��
     * @param prm_hWnd1 �P��ʖڃE�C���h�E�n���h��
     * @param prm_hWnd2 �Q��ʖڃE�C���h�E�n���h��
     */
    VvvGod(HINSTANCE prm_hInstance, HWND prm_hWnd1, HWND prm_hWnd2);

    /**
     * ���̐��������@�̎��� .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~VvvGod();
};

}
#endif /*SMPGOD_H_*/
