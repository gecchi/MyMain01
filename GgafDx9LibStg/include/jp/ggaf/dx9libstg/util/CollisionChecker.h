#ifndef COLLISIONCHECKER_H_
#define COLLISIONCHECKER_H_
namespace GgafDx9LibStg {

/**
 * �`�F�b�N�N���X.
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafDx9Core::GgafDx9Checker {

protected:
    /** �����蔻��̈� */
    GgafDx9Core::GgafDx9CollisionArea* _pCollisionArea;

    bool _need_update_aabb;
public:
    static LinearOctreeForActor* _pLinearOctree;
    LOFA_Elem* _pElem;

    static int _num_check;

    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    CollisionChecker(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);

    /**
     * �����蔻��̈�BOX�̉�]���s�ړ��ƁA�W���ؓo�^���s���܂��B .
     * ���݂� GgafDx9GeometricActor::processPreJudgement ����R�[������Ă���B
     */
    virtual void updateHitArea();

    void makeCollision(int prm_nColliPart);

    void setColliBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);


    void setColliBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2) {
        setColliBox(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    void setColliBox(int prm_index, int x1, int y1, int x2, int y2) {
        setColliBox(prm_index, x1, y1, -1 * (LEN_UNIT * PX_UNIT) / 2, x2, y2, (LEN_UNIT * PX_UNIT) / 2, false, false,
                      false);
    }


    void setColliBox_WHD(int prm_index, int prm_width, int prm_height, int prm_depth) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;

        setColliBox(prm_index, -hw, -hh, -hd, hw, hh, hd);
    }
    void setColliBox_Cube(int prm_index, int prm_edge) {
        int h = prm_edge / 2;
        setColliBox(prm_index, -h, -h, -h, h, h, h);
    }

    void enable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = true;
    }

    void disable(int prm_index) {
        _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg = false;
    }

    bool isEnable(int prm_index) {
        return _pCollisionArea->_papColliPart[prm_index]->_is_valid_flg;
    }
    //virtual void draw();

    /**
     * �I�[�o�[���C�h
     * @param prm_pOtherChecker
     * @return
     */
 //   bool isBump(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker);
    inline bool isBump(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker);

    virtual ~CollisionChecker();
};

}
#endif /*COLLISIONCHECKER_H_*/

