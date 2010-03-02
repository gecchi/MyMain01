#ifndef GGAFDX9TEXTURE_H_
#define GGAFDX9TEXTURE_H_
namespace GgafDx9Core {

/**
 * エフェクト基底クラス.
 * キャラ(アクター)のエフェクトを保持するクラスです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9Texture : public GgafCore::GgafObject {
    friend class GgafDx9TextureManager;

protected:
public:

    /** モデル定義の識別名。(50文字まで) */
    char* _effect_name;
    ID3DXTexture* _pID3DXTexture;
    /**
     * コンストラクタ<BR>
     * @param prm_effect_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9Texture(char* prm_effect_name);

    char* getName() {
        return _effect_name;
    }


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9TextureManagerである<BR>
     */
    virtual ~GgafDx9Texture(); //デストラクタ
};

}
#endif /*GGAFDX9EFFECT_H_*/
