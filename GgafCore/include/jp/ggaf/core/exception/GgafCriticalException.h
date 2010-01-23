#ifndef GGAFCRITICALEXCEPTION_H_
#define GGAFCRITICALEXCEPTION_H_
namespace GgafCore {

#define throwGgafCriticalException(X) { \
    std::stringstream ss; \
    ss <<__FILE__<<"("<<__LINE__<<") : "<< X; \
    throw GgafCore::GgafCriticalException(ss.str()); \
}


/**
 * GgafCore���C�u������p�A���C�u�����Ɩ���O .
 * GgafCore���C�u�����̗��p�ҁi������?�j�͖{�N���X���L���b�`���ăv���O�������X�g�b�v���ĉ������B
 * @version 1.00
 * @since 2007/12/03
 * @author Masatoshi Tsuge
 */
class GgafCriticalException : public GgafCore::GgafException {
public:
    GgafCriticalException(std::string prm_message);
    virtual ~GgafCriticalException();
};

}
#endif /*GGAFCRITICALEXCEPTION_H_*/
