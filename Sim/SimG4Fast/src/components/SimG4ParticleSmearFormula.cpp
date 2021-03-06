#include "SimG4ParticleSmearFormula.h"

// Gaudi
#include "GaudiKernel/DeclareFactoryEntries.h"
#include "GaudiKernel/IRndmGenSvc.h"
#include "GaudiKernel/IRndmGen.h"

//ROOT
#include "TFormula.h"

//CLHEP
#include "CLHEP/Vector/ThreeVector.h"

DECLARE_TOOL_FACTORY(SimG4ParticleSmearFormula)

SimG4ParticleSmearFormula::SimG4ParticleSmearFormula(const std::string& type, const std::string& name, const IInterface* parent):
    GaudiTool(type, name, parent),
    m_resolutionMomentum() {
  declareInterface<ISimG4ParticleSmearTool>(this);
  declareProperty("detectorNames", m_volumeNames);
  declareProperty("resolutionMomentum", m_resolutionMomentumStr = "");
  declareProperty("minP", m_minP = 0);
  declareProperty("maxP", m_maxP = 0);
  declareProperty("maxEta", m_maxEta = 0);
}

SimG4ParticleSmearFormula::~SimG4ParticleSmearFormula() {}

StatusCode SimG4ParticleSmearFormula::initialize() {
  if(GaudiTool::initialize().isFailure()) {
    return StatusCode::FAILURE;
  }
  if(m_volumeNames.size() == 0) {
    error() << "No detector name is specified for the parametrisation" << endmsg;
    return StatusCode::FAILURE;
  }
  m_randSvc = service("RndmGenSvc");
  if(!m_randSvc) {
    error() << "Couldn't get RndmGenSvc" << endmsg;
    return StatusCode::FAILURE;
  }
  if (!m_resolutionMomentumStr.empty()) {
    m_resolutionMomentum = TFormula("pdep",m_resolutionMomentumStr.c_str());
    info() << "Momentum-dependent resolutions: "<< m_resolutionMomentum.GetExpFormula() << endmsg;
  } else {
    info() << "No momentum-dependent resolutions defined."<< endmsg;
  }
  return StatusCode::SUCCESS;
}

StatusCode SimG4ParticleSmearFormula::finalize() {
  return GaudiTool::finalize();
}

StatusCode SimG4ParticleSmearFormula::smearMomentum( CLHEP::Hep3Vector& aMom, int /*aPdg*/) {
  if(!m_resolutionMomentum.IsValid()) {
    error()<<"Unable to smear particle's momentum - no resolution given!"<<endmsg;
    return StatusCode::FAILURE;
  }
  m_randSvc->generator(Rndm::Gauss(1,m_resolutionMomentum.Eval(aMom.mag())), m_gauss);
  double tmp = m_gauss->shoot();
  aMom *= tmp;
  return StatusCode::SUCCESS;
}
