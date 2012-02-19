#ifndef GOD_H_
#define GOD_H_
namespace SimpleSample {

/**
 * �_�̐��` .
 * GgafLib::DefaultGod ���p�����A�_�N���X���쐬���ĉ������B<BR>
 * ���̍ہAGgafCore::GgafUniverse* createUniverse() ���I�[�o�[���C�h���A�������ĉ������B<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class God : public GgafLib::DefaultGod {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_hInstance HINSTANCE
     * @param prm_pHWndPrimary �P��ʖ�HWND
     * @param prm_pHWndSecondary �Q��ʖ�HWND
     */
    God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * ���̐��������@ .
     * �_�N���X���쐬����ɂ́A�u���̐��v�̐������@����������K�v������܂��B
     * @return ���������u���̐��v
     */
    GgafCore::GgafUniverse* createUniverse() override;

    virtual ~God();
};

}
#endif /*GOD_H_*/
