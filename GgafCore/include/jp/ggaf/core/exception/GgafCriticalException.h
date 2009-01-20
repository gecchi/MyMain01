#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_
namespace GgafCore {


/**
 * GgafCore���C�u������p�A���C�u�����Ɩ���O .
 * GgafCore���C�u�����̗��p�ҁi�������j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
#define throw_GgafCriticalException(X) {std::stringstream ss; ss << X; throw GgafCore::GgafCriticalException(ss.str()); }


class GgafCriticalException : public GgafCore::GgafException {
public:
	GgafCriticalException(std::string prm_message);
	virtual ~GgafCriticalException();
};


}
#endif /*GGAFCRITICALEXCEPTION_H_*/
