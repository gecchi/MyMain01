#ifndef SPLINESOURCE_H_
#define SPLINESOURCE_H_
namespace GgafLib {

/**
 * Spline�I�u�W�F�N�g�\�[�X .
 * SplineLine�̃��b�p�[�ł���A�t�@�C������̓ǂݍ��݋@�\��ǉ������N���X�B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSource : public GgafCore::GgafObject {

public:

    SplineLine* _pSp;
    double _accuracy;
    std::string _idstr;
    bool _is_create_SplineLine;
    SplineSource(char* prm_idstr);

    SplineSource(SplineLine* prm_pSp);

    virtual ~SplineSource();
};

}
#endif /*SPLINESOURCE_H_*/
