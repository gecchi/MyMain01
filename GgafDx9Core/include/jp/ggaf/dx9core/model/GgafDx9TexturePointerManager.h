#ifndef GGAFDX9TEXTUREPOINTERMANAGER_H_
#define GGAFDX9TEXTUREPOINTERMANAGER_H_
namespace GgafDx9Core {


/**
 * GgafDx9TexturePointer 管理クラス .
 * 生成済み GgafDx9TexturePointer オブジェクトを登録しておき、使いまわします。
 */
class GgafDx9TexturePointerManager : public GgafCore::GgafResourcePointerManager<IDirect3DTexture9> {

public:

	GgafDx9TexturePointerManager(std::string prm_name);
	/**
	 * オーバーライド
	 */
	IDirect3DTexture9* processCreateResource(std::string prm_resource_idstr);

	/**
	 * オーバーライド
	 */
	GgafCore::GgafResourcePointer<IDirect3DTexture9>* processCreateResourcePointer(std::string prm_resource_idstr, IDirect3DTexture9* prm_pResource);


	virtual ~GgafDx9TexturePointerManager();
};


}
#endif /*GGAFDX9TEXTUREPOINTERMANAGER_H_*/
