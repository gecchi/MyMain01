#ifndef GGAFLINEAROCTREEFORACTOR_H_
#define GGAFLINEAROCTREEFORACTOR_H_
namespace GgafCore {

class GgafLinearOctreeForActor : public GgafLinearOctree {

public:

    GgafLinearOctreeForActor(int prm_level);

    virtual void registElem(Elem* prm_pElem, GgafActor* prm_pActor) = 0;

    virtual ~GgafLinearOctreeForActor();
};

}
#endif /*GGAFLINEAROCTREEFORACTOR_H_*/

