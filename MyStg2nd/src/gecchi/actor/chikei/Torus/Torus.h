#ifndef TORUS_H_
#define TORUS_H_
namespace MyStg2nd {

/**
 * 地形トーラス .
 * 最初に作った地形
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
class Torus : public GroundMeshActor {

public:
    /** トーラス半径1(輪) */
    int _r1;
    /** トーラス半径2(太さ) */
    int _r2;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_model
     * @param prm_r1 トーラス半径1(輪)
     * @param prm_r2 トーラス半径2(輪の太さ)
     * @return
     */
    Torus(const char* prm_name, const char* prm_model, int prm_r1, int prm_r2);

    virtual void onCreateModel() override;

    virtual void onActive() override;

    virtual void processJudgement() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() override {
        if (GgafDx9Core::GgafDx9Universe::_X_goneLeft < _X) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~Torus();

protected:
    /**
     * トーラスの当たり判定領域を作成し設定する .
     * @param prm_nSphere 当たり判定球の数
     */
    void makeCollisionArea(int prm_nSphere);

    /**
     * トーラスの表面にサブボーンを追加
     * @param prm_pGeoActor 追加するアクター
     * @param prm_angPos1 輪の角度位置
     * @param prm_angPos2 輪周りの角度位置
     */
    void addSubBoneOnSurface(GgafDx9Core::GgafDx9GeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2);

};

}
#endif /*TORUS_H_*/

