#include "lduAgglomeration.hpp"

// bool UNAP::lduAgglomeration::forward_(true);

UNAP::lduAgglomeration::lduAgglomeration(const lduMatrix &A)
    : maxLevels_(50),
      nCellsInCoarsestLevel_(50),
      forward_(true),
      nCells_(maxLevels_, A.getCommunicator()),
      nCreatedLevels_(0),
      mergeLevels_(1),
      finestMatrix_(A),
      coarseMatrixLevels_(maxLevels_),
      restrictAddressing_(maxLevels_),
      faceRestrictAddressing_(maxLevels_),
      patchFaceRestrictAddressing_(maxLevels_),
      matrix::agglomeration(A.getCommunicator())
{
}

UNAP::lduAgglomeration::~lduAgglomeration() {}

bool UNAP::lduAgglomeration::continueAgglomerating(
    const label nCoarseCells) const
{
  //- check the need for further agglomeration on all processors
  bool contAgg = false;

  if (nCoarseCells >= nCellsInCoarsestLevel_)
  {
    contAgg = true;
  }

  bool contAggLocal = contAgg;
  commcator_->allReduce(
      "LOR", &contAggLocal, &contAgg, 1, COMM_CXX_BOOL, COMM_LOR);
  commcator_->finishTask("LOR");

  return contAgg;
}

void UNAP::lduAgglomeration::compactLevels(const label nCreatedLevels)
{
  nCreatedLevels_ = nCreatedLevels;
  nCells_.SET_size(nCreatedLevels);
  coarseMatrixLevels_.SET_size(nCreatedLevels);
  restrictAddressing_.SET_size(nCreatedLevels);
  faceRestrictAddressing_.SET_size(nCreatedLevels);
  patchFaceRestrictAddressing_.SET_size(nCreatedLevels);
}

const UNAP::lduMatrix &UNAP::lduAgglomeration::matrixLevel(const label i) const
{
  if (i == 0)
  {
    return finestMatrix_;
  }
  else
  {
    return coarseMatrixLevels_[i - 1];
  }
}

void UNAP::lduAgglomeration::SET_maxLevels(const label i) { maxLevels_ = i; }

void UNAP::lduAgglomeration::SET_nCellsInCoarsestLevel(const label i)
{
  nCellsInCoarsestLevel_ = i;
}
