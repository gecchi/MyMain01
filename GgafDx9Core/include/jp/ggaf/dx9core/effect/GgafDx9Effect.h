#ifndef GGAFDX9EFFECT_H_
#define GGAFDX9EFFECT_H_
namespace GgafDx9Core {

/**
 * モデル基底クラス.
 * キャラ(アクター)の形状や色などを保持するクラスです。<BR>
 */
class GgafDx9Effect : public GgafCore::GgafObject {
    friend class GgafDx9EffectManager;

protected:
public:

    /** モデル定義の識別名。(50文字まで) */
    char* _effect_name;
    ID3DXEffect* _pID3DXEffect;
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9Effect(char* prm_effect_name);
    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9EffectManagerである<BR>
     */
    virtual ~GgafDx9Effect(); //デストラクタ
};

}
#endif /*GGAFDX9EFFECT_H_*/
