#include <athread.h>
#include <math.h>

#include "userFunc_SAXPY.h"

void residualNormFactor_host(MVM_Arrays *MVM_ArraysPtr)
{
  MVM_ParametersPack pack;
  pack.A1Ptr = MVM_ArraysPtr->A1Ptr;
  pack.A2Ptr = MVM_ArraysPtr->A2Ptr;
  pack.A3Ptr = MVM_ArraysPtr->A3Ptr;
  pack.A4Ptr = MVM_ArraysPtr->A4Ptr;
  pack.k1Ptr = MVM_ArraysPtr->k1Ptr;
  pack.k2Ptr = MVM_ArraysPtr->k2Ptr;
  pack.n1 = MVM_ArraysPtr->n1;

  athread_spawn(residualNormFactor_slave, &pack);
  athread_join();
}
