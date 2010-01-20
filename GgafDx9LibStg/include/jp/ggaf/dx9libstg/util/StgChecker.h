#ifndef STGCHECKER_H_
#define STGCHECKER_H_
namespace GgafDx9LibStg {

/**
 * チェッククラス.
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class StgChecker : public GgafDx9Core::GgafDx9Checker {

protected:
    /** 当たり判定領域 */
    HitAreaBoxs* _pHitAreaBoxs;

public:
    static LinearOctreeForActor* _pLinearOctree;


    LOFA_Elem* _pElem;

    static int _num_check;

    /** 現在の得点 */
    int _iScorePoint;
    /** 元来の得点 */
    int _iScorePointOriginally;
    /** 元来の耐久力 */
    int _iStaminaPointOriginally;
    /** 現在の耐久力 */
    int _iStaminaPoint;
    /** 攻撃力 */
    int _iAttackPoint;
    /** 防御力*/
    int _iDefensePoint;
	/** 当たり判定領域のいちばん外側のBOX */
    int _X1, _Y1, _Z1, _X2, _Y2, _Z2;


    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    StgChecker(GgafDx9Core::GgafDx9GeometricActor* prm_pActor);

    virtual void setStatus(int prm_iScorePoint, int prm_iStaminaPoint, int prm_iAttackPoint, int prm_iDefensePoint) {
        _iScorePointOriginally = _iScorePoint = prm_iScorePoint;
        _iStaminaPointOriginally = _iStaminaPoint = prm_iStaminaPoint;
        _iAttackPoint = prm_iAttackPoint;
        _iDefensePoint = prm_iDefensePoint;
    }

    /**
     * 当たり判定領域BOXの回転平行移動と、８分木登録を行います。 .
     * 現在は GgafDx9GeometricActor::processPreJudgement からコールされている。
     */
    virtual void updateHitArea();

    void useHitAreaBoxNum(int n);

    void setHitAreaBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    void setHitAreaBox(int prm_index, int x1, int y1, int z1, int x2, int y2, int z2) {
        setHitAreaBox(prm_index, x1, y1, z1, x2, y2, z2, false, false, false);
    }

    void setHitAreaBox(int prm_index, int x1, int y1, int x2, int y2) {
        setHitAreaBox(prm_index, x1, y1, -1 * (LEN_UNIT * PX_UNIT) / 2, x2, y2, (LEN_UNIT * PX_UNIT) / 2, false, false,
                      false);
    }


    void setHitAreaBox_WHD(int prm_index, int prm_width, int prm_height, int prm_depth) {
        int hw = prm_width  / 2;
        int hh = prm_height / 2;
        int hd = prm_depth  / 2;

        setHitAreaBox(prm_index, -hw, -hh, -hd, hw, hh, hd);
    }
    void setHitAreaBox_Cube(int prm_index, int prm_edge) {
        int h = prm_edge / 2;
        setHitAreaBox(prm_index, -h, -h, -h, h, h, h);
    }
    HitAreaBoxs* getHitAreaBoxs() {
        return _pHitAreaBoxs;
    }


    void enable(int prm_index) {
        _pHitAreaBoxs->_paBase[prm_index].is_valid_flg = true;
        _pHitAreaBoxs->_paHitArea[prm_index].is_valid_flg = true;
    }

    void disable(int prm_index) {
        _pHitAreaBoxs->_paBase[prm_index].is_valid_flg = false;
        _pHitAreaBoxs->_paHitArea[prm_index].is_valid_flg = false;
    }

    bool isEnable(int prm_index) {
        return _pHitAreaBoxs->_paHitArea[prm_index].is_valid_flg;
    }
    //virtual void draw();

    /**
     * オーバーライド
     * @param prm_pOtherChecker
     * @return
     */
 //   bool isBump(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker);
    inline bool isBump(GgafDx9Core::GgafDx9Checker* prm_pOtherChecker) {

        static GgafDx9Core::GgafDx9GeometricActor* pOtherActor;
        static HitAreaBoxs* pOtherHitAreaBoxs;

        pOtherActor = prm_pOtherChecker->getTargetActor();
        pOtherHitAreaBoxs = ((StgChecker*)prm_pOtherChecker)->getHitAreaBoxs();
        if (_pHitAreaBoxs == NULL || pOtherHitAreaBoxs == NULL ||
            _pActor->isOffscreen() > 0 || pOtherActor->isOffscreen() > 0 ) {
            return false;
        } else {

            //自分の箱と相手の箱

            for (int i = 0; i < _pHitAreaBoxs->_iAreaNum; i++) {
                if (_pHitAreaBoxs->_paHitArea[i].is_valid_flg) {
                    for (int j = 0; j < pOtherHitAreaBoxs->_iAreaNum; j++) {
                        if (pOtherHitAreaBoxs->_paHitArea[j].is_valid_flg) {
                            StgChecker::_num_check++;
                            if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z2 >= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z1) {
                                if (_pActor->_Z + _pHitAreaBoxs->_paHitArea[i].z1 <= pOtherActor->_Z + pOtherHitAreaBoxs->_paHitArea[j].z2) {
                                    if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x2 >= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x1) {
                                        if (_pActor->_X + _pHitAreaBoxs->_paHitArea[i].x1 <= pOtherActor->_X + pOtherHitAreaBoxs->_paHitArea[j].x2) {
                                            if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y2 >= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y1) {
                                                if (_pActor->_Y + _pHitAreaBoxs->_paHitArea[i].y1 <= pOtherActor->_Y + pOtherHitAreaBoxs->_paHitArea[j].y2) {
                                                    return true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    virtual ~StgChecker();
};

}
#endif /*STGCHECKER_H_*/

