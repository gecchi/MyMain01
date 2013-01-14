#ifndef LASERCHIP_H_
#define LASERCHIP_H_
namespace GgafLib {

/**
 * ポリラインレーザーのチップの基底クラス .
 * ＜注意＞
 * processSettlementBehavior()内の処理により、
 * setHitAble(false); は意味をなしません。
 * 当たり判定を行いたくない場合、
 * registHitAreaCube_AutoGenMidColli() 等の当たり判定自体を作成しないで下さい。
 * @version 1.00
 * @since 2008/11/24
 * @author Masatoshi Tsuge
 */
class LaserChip : public GgafDxCore::GgafDxMeshSetActor {
    friend class WateringLaserChip;
    friend class HomingLaserChip;
    friend class RefractionLaserChip;
    friend class StraightLaserChip;
    friend class LaserChipDepository;
    friend class LaserChipDepositoryStore;

private:
    D3DXHANDLE _ah_kind[11];
    D3DXHANDLE _ah_force_alpha[11];
    D3DXHANDLE _ah_matWorld_front[11];
    //D3DXHANDLE _h_cnt_vertec;


    /** onAcive() でリセットされる振る舞い時フレーム数 */
    frame _frame_of_behaving_from_onActive;

    /** 自身を管理してるアクター発送者 */
    LaserChipDepository* _pDepo;
    /** registHitAreaCube_AutoGenMidColli() メソッドにより登録時の当たり判定立方体の１辺の長さ */
    int _hitarea_edge_length;
    int _hitarea_edge_length_3;
    /** registHitAreaCube_AutoGenMidColli() メソッドにより登録時の当たり判定立方体の１辺の長さの半分 */
    int _harf_hitarea_edge_length;

public:


    CollisionChecker* _pColliChecker;

    /** 一つ前方のレーザーチップ */
    LaserChip* _pChip_front;
    /** 一つ後方のレーザーチップ */
    LaserChip* _pChip_behind;
    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭から２番目で先頭のテクスチャ （末尾かつ先頭は末尾が優先） 4:本当の先頭(但し描画できない) */
    int _chip_kind;
    /** [r]地形ヒットありチップ(10回に1回) */
    bool _can_chikei_hit;
    /** [r]自身が所属する先端チップ */
    LaserChip* _pLeader;
    /** [r]強制上書きアルファ値。（出現時は遠方であっても表示させるため) */
    float _force_alpha;
    /** [r]rueならば、前方チップと離れすぎた場合に中間当たり判定自動生成 */
    float _middle_colli_able;

    LaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void executeHitChk_MeAnd(GgafActor* prm_pOtherActor) override;

    virtual void onActive() override;
    /**
     * 様々な事前処理 .
     * ＜注意＞
     * setHitAble(true);
     * を内部で実行していますので、
     * setHitAble(false);
     * は無意味です。
     */
    virtual void processSettlementBehavior() override;

    virtual void processPreDraw() override;

    virtual void processDraw() override;

    virtual void onInactive() override;

    virtual void drawHitArea() override;

    /**
     * レーザーチップ用当たり判定立方体をセット .
     * レーザーチップ間の距離が離れ、当たり判定のすり抜けを防止するため、<BR>
     * 通常の当たり判定に加え、接続された前方チップとの距離が離れた場合にのみ、<BR>
     * 自動的に中間に当たり判定を自動生成する機能も付与される。<BR>
     * 当たり判定要素数は２つになる。
     * 【注意】<BR>
     * 予めレーザーチップ間の距離が開かず、すり抜けが起こらないとわかっている場合は、<BR>
     * 本メソッドで設定せず、通常 _pColliChecker->makeCollision(1);<BR>
     * を行ったほうがパフォーマンスが良い。<BR>
     * @param prm_edge_length
     */
    virtual void registHitAreaCube_AutoGenMidColli(int prm_edge_length);


    /**
     * α設定.
     * @param prm_alpha
     */
    virtual void setAlpha(float prm_alpha) override;

    /**
     * α加算 .
     * @param prm_alpha
     */
    virtual void addAlpha(float prm_alpha) override;


    virtual ~LaserChip();

};

}
#endif /*LASERCHIP_H_*/

