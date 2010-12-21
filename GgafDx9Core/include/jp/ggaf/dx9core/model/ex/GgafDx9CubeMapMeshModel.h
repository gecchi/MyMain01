#ifndef GGAFDX9CUBEMAPMESHMODEL_H_
#define GGAFDX9CUBEMAPMESHMODEL_H_
namespace GgafDx9Core {

class GgafDx9CubeMapMeshModel : public GgafDx9MeshModel {
    friend class GgafDx9ModelManager;

public:

    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9CubeMapMeshModel(char* prm_model_name);

    virtual ~GgafDx9CubeMapMeshModel(); //デストラクタ
};

}
#endif /*GGAFDX9CUBEMAPMESHMODEL_H_*/

