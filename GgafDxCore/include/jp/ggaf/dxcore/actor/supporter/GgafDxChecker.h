#ifndef GGAFDXCHECKER_H_
#define GGAFDXCHECKER_H_
namespace GgafDxCore {

/**
 * �`�F�b�N�Ɋւ���F�X�ȋ@�\���������N���X .
 * �i��GgafDxGeometryChecker�j
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxChecker : public GgafCore::GgafObject {

protected:
    /** �ΏۃA�N�^�[ */
    GgafDxGeometricActor* _pActor;

public:

    /** �����蔻��̈� */
    GgafDxCore::GgafDxCollisionArea* _pCollisionArea;
//    /** �������X���� */
//    int _blown_sgn_vX;
//    /** �������Y���� */
//    int _blown_sgn_vY;
//    /** �������Z���� */
//    int _blown_sgn_vZ;
    /** ������ьv�Z���s���� */
//    int _is_blown;
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDxChecker(GgafDxGeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    GgafDxGeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_("GgafDxChecker::getTargetActor nullptr�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    virtual bool isHit(GgafDxChecker* prm_pOtherChecker) = 0;

    virtual ~GgafDxChecker();
};

}
#endif /*GGAFDXCHECKER_H_*/

