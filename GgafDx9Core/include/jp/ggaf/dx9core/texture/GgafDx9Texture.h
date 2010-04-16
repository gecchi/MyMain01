#ifndef GGAFDX9TEXTURE_H_
#define GGAFDX9TEXTURE_H_
namespace GgafDx9Core {

/**
 * テクスチャ基底クラス.
 * キャラ(アクター)のテクスチャをラップするクラスです。<BR>
 * @version 1.00
 * @since 2009/03/09
 * @author Masatoshi Tsuge
 */
class GgafDx9Texture : public GgafCore::GgafObject {
    friend class GgafDx9TextureManager;

protected:
public:

    /** モデル定義の識別名。(50文字まで) */
    char* _texture_name;
    D3DXIMAGE_INFO* _pD3DXIMAGE_INFO;
    LPDIRECT3DTEXTURE9 _pIDirect3DTexture9;
    /**
     * コンストラクタ<BR>
     * @param prm_texture_name モデル定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9Texture(char* prm_texture_name);

    char* getName() {
        return _texture_name;
    }


    /**
     * デストラクタ<BR>
     * deleteするのはGgafDx9TextureManagerである<BR>
     */
    virtual ~GgafDx9Texture(); //デストラクタ
};

}
#endif /*GGAFDX9EFFECT_H_*/
