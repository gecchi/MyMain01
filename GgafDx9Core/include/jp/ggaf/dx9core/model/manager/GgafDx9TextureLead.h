#ifndef GGAFDX9TEXTURELEAD_H_
#define GGAFDX9TEXTURELEAD_H_
namespace GgafDx9Core {

/**
 * テクスチャのコネクション.
 */
class GgafDx9TextureLead : public GgafCore::GgafResourceLead<IDirect3DTexture9> {

public:

    /**
     * コンストラクタ<BR>
     * @param prm_texture_file_name テクスチャ識別名(＝ファイル名)
     * @param prm_pIDirect3DTexture9 テクスチャ
     */
    GgafDx9TextureLead(char* prm_idstr, LPDIRECT3DTEXTURE9 prm_pIDirect3DTexture9);

    void processReleaseResource(IDirect3DTexture9* prm_pResource);

    virtual ~GgafDx9TextureLead() {
    }
};

}
#endif /*GGAFDX9TEXTURELEAD_H_*/
