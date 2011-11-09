#ifndef GGAFDXCRITICALEXCEPTION_H_
#define GGAFDXCRITICALEXCEPTION_H_
namespace GgafDxCore {


/**
 * GgafDxCore���C�u������p�A���C�u�����Ɩ���O .
 * GgafDxCore���C�u�����̗��p�ҁi������?�j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2008/11/12
 * @author Masatoshi Tsuge
 */
class GgafDxCriticalException : public GgafCore::GgafCriticalException {
public:
    HRESULT _hr;
    GgafDxCriticalException(std::string prm_message, HRESULT prm_hr);
    //�I�[�o�[���C�h
    virtual std::string getMsg();

    static std::string getHresultMsg(HRESULT prm_hr);
    virtual ~GgafDxCriticalException();
};


}
#endif /*GGAFDXCRITICALEXCEPTION_H_*/