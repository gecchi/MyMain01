#ifndef SCENETRANSITIONER_H_
#define SCENETRANSITIONER_H_
namespace GgafDx9LibStg {


class SceneTransitioner : public GgafCore::GgafObject {

    DefaultScene* _pScene;

    SceneTransitioner(DefaultScene* prm_pScene);

    virtual ~SceneTransitioner();
};

}
#endif /*SCENETRANSITIONER_H_*/
