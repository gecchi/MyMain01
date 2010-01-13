#ifndef GGAFDX9CRITICALEXCEPTION_H_
#define GGAFDX9CRITICALEXCEPTION_H_
namespace GgafDx9Core {


/**
 * GgafDxCore���C�u������p�A���C�u�����Ɩ���O .
 * GgafDxCore���C�u�����̗��p�ҁi������?�j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2008/11/12
 * @author Masatoshi Tsuge
 */
#ifdef MY_DEBUG
#define mightDx9Exception(HR, OKVAL, X) {if (HR != OKVAL) {std::stringstream ss; ss <<__FILE__<<"("<<__LINE__<<") : " << X; throw GgafDx9CriticalException(ss.str(),HR); } }
#else
#define mightDx9Exception(HR, OKVAL, X)
#endif

class GgafDx9CriticalException  : public GgafCore::GgafCriticalException {
public:
    HRESULT _hr;
    GgafDx9CriticalException(std::string prm_message, HRESULT prm_hr);
    //�I�[�o�[���C�h
    virtual std::string getMsg();
    virtual ~GgafDx9CriticalException();
};


}
#endif /*GGAFDX9CRITICALEXCEPTION_H_*/
