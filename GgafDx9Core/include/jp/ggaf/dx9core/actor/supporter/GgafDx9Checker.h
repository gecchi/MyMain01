#ifndef GGAFDX9CHECKER_H_
#define GGAFDX9CHECKER_H_
namespace GgafDx9Core {

/**
 * �`�F�b�N�Ɋւ���F�X�ȋ@�\���������N���X .
 * �i��GgafDx9GeometryChecker�j
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9Checker : public GgafCore::GgafObject {

protected:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;

public:

    /** �����蔻��̈� */
    GgafDx9Core::GgafDx9CollisionArea* _pCollisionArea;
    /** �������X���� */
    int _blown_sgn_vX;
    /** �������Y���� */
    int _blown_sgn_vY;
    /** �������Z���� */
    int _blown_sgn_vZ;
    /** ������ьv�Z���s���� */
//    int _is_blown;
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    GgafDx9Checker(GgafDx9GeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    //virtual void draw();

    GgafDx9GeometricActor* getTargetActor() {
        if (_pActor == NULL) {
            _TRACE_("GgafDx9Checker::getTargetActor NULL�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    virtual bool isHit(GgafDx9Checker* prm_pOtherChecker) = 0;

    virtual ~GgafDx9Checker();
};

}
#endif /*GGAFDX9CHECKER_H_*/

