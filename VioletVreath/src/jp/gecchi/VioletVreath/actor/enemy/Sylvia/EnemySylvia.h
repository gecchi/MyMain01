#ifndef ENEMYSYLVIA_H_
#define ENEMYSYLVIA_H_
namespace VioletVreath {


HASHVAL(SYLVIA_EXPLOSION);

/**
 * シルヴィア .
 * 最初に作った地形シルヴィア
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
//class EnemySylvia : public GroundMeshActor {
class EnemySylvia : public GgafLib::CubeMapMeshActor {

public:
    enum {
        PROG_INIT = 1  ,
        PROG_FLOAT_MOVE   ,
        PROG_EXPLOSION    ,
        PROG_NOTHING    ,
    };

    /** トーラスの半径1(輪の半径) */
    coord r1_;
    /** トーラスの半径2(太さの半径) */
    coord r2_;
    int colli_part_num_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_model
     * @param prm_r1 トーラスの半径1(輪の半径)
     * @param prm_r2 トーラスの半径2(太さの半径)
     * @return
     */
    EnemySylvia(const char* prm_name, const char* prm_model, coord prm_r1, coord prm_r2);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() override {
        if (GgafDxCore::GgafDxUniverse::_X_gone_left < _X) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~EnemySylvia();

protected:
    /**
     * シルヴィアの当たり判定領域を作成し設定する .
     * @param prm_nSphere 当たり判定球の数
     */
    void makeCollisionArea(int prm_nSphere);

    /**
     * シルヴィアの表面にサブボーンを追加
     * @param prm_pGeoActor 追加するアクター
     * @param prm_angPos1 輪の角度位置
     * @param prm_angPos2 輪周りの角度位置
     */
    void addSubGroupAsFkOnSurface(GgafDxCore::GgafDxGeometricActor* prm_pGeoActor, angle prm_angPos1, angle prm_angPos2);

};

}
#endif /*ENEMYSYLVIA_H_*/

