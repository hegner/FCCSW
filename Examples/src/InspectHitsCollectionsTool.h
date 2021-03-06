#ifndef TESTDD4HEP_INSPECTHITSCOLLECTIONSTOOL_H
#define TESTDD4HEP_INSPECTHITSCOLLECTIONSTOOL_H

// Gaudi
#include "GaudiAlg/GaudiTool.h"

//FCCSW
#include "SimG4Interface/ISimG4SaveOutputTool.h"

/** @class InspectHitsCollectionsTool TestDD4hep/TestDD4hep/InspectHitsCollectionsTool.h InspectHitsCollectionsTool.h
 *
 *  Tool used to inspect the hits collection.
 *  No output in EDM is produced.
 *
 *  @author Anna Zaborowska
 */

class InspectHitsCollectionsTool: public GaudiTool, virtual public ISimG4SaveOutputTool {
public:
  /// Constructor.
  explicit InspectHitsCollectionsTool(const std::string& type, const std::string& name, const IInterface* parent);
  virtual ~InspectHitsCollectionsTool();
  /// Initialize.
  virtual StatusCode initialize() final;
  /// Finalize.
  virtual StatusCode finalize() final;
  /// inspect output
  virtual StatusCode saveOutput(const G4Event& aEvent) final;
};

#endif /* TESTDD4HEP_INSPECTHITSCOLLECTIONSTOOL_H */
