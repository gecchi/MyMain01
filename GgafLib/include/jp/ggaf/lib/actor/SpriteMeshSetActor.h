#ifndef SPRITEMESHSETACTOR_H_
#define SPRITEMESHSETACTOR_H_
namespace GgafLib {

/**
 * テクスチャアニメーション可能メッシュセットアクターの具象クラス.
 * GgafDxCore::GgafDxSpriteMeshSetActor を空実装した具象アクターです。
 * 本クラスを継承してキャラクターを作成しましょう。<BR>
 * 以下に使用可能な支援オブジェクトを記す。<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>参照変数</TH><TH>概要</TH><TH>使用方法</TH><TH>CLASS名</TH></TR>
 * <TR><TD>_pProg</TD><TD>進捗管理</TD><TD>useProgress(int) を実行</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKrokoA</TD><TD>黒子A。移動回転支援</TD><TD>behave() をコール</TD><TD>GgafDxCore::GgafDxKurokoA</TD></TR>
 * <TR><TD>_pKrokoB</TD><TD>黒子B。移動支援</TD><TD>behave() をコール</TD><TD>GgafDxCore::GgafDxKurokoB</TD></TR>
 * <TR><TD>_pFader</TD><TD>フィードイン・アウト支援</TD><TD>behave() をコール</TD><TD> GgafDxCore::GgafDxAlphaFader</TD></TR>
 * <TR><TD>_pUvFlipper</TD><TD>テクスチャローテーション支援</TD><TD>behave() をコール</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>_pSeTransmitter</TD><TD>効果音発生管理</TD><TD>useSe(int) 後 set(int prm_id, const char*)。<BR>
 * そしてplay系のメソッド実行</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pScaler</TD><TD>拡大縮小支援</TD><TD>behave() をコール</TD><TD>GgafDxCore::GgafDxScaler</TD></TR>
 * <TR><TD>_pCollisionChecker</TD><TD>衝突判定支援</TD><TD>makeCollision(int) 後 setColli*** で当たり判定定義。<BR>
 * 親シーンで CollisionChecker::_pLinearOctree->executeAllHitChk(A,B) </TD><TD>GgafLib::CollisionChecker</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetActor : public GgafDxCore::GgafDxSpriteMeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pCollisionChecker;

    /**
     * コンストラクタ
     * DefaultMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @return
     */
    SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~SpriteMeshSetActor();
};

}
#endif /*SPRITEMESHSETACTOR_H_*/
