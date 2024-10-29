#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_

#include "VvGeometricActor.h"

template<class T>
class VvEnemyActor : public VvGeometricActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model, void* prm_pPrm1 = nullptr);

    virtual ~VvEnemyActor();
};

#endif /* VVTEKIACTOR_H_ */
