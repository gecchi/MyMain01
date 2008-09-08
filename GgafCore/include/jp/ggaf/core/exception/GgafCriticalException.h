#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_

/**
 * GgafCore���C�u������p�A���C�u�����Ɩ���O .
 * GgafCore���C�u�����̗��p�ҁi�������j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
#define throw_GgafCriticalException(X) {std::stringstream ss; ss << X; throw GgafCriticalException(ss.str()); }


class GgafCriticalException : public GgafException {
public:
	GgafCriticalException(string prm_message);
	virtual ~GgafCriticalException();
};


#endif /*GGAFCRITICALEXCEPTION_H_*/
