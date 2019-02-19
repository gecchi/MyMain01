#ifndef VVENEMYACTOR_H_
#define VVENEMYACTOR_H_

#include "VvActor.h"

template<class T>
class VvEnemyActor : public VvActor<T> {

public:
    VvEnemyActor(const char* prm_name, const char* prm_model_id, void* prm_pPrm1 = nullptr);

    virtual ~VvEnemyActor();
};

#endif /* VVTEKIACTOR_H_ */
