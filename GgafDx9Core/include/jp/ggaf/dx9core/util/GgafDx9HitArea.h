#ifndef GGAFDX9HITAREA_H_
#define GGAFDX9HITAREA_H_
namespace GgafDx9Core {

/**
 * �����蔻��̈�N���X
 */
class GgafDx9HitArea : public GgafCore::GgafObject {

public:

    int _iAreaNum;

    GgafDx9HitArea(int prm_iAreaNum);

    virtual ~GgafDx9HitArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
