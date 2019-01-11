// -*- C++ -*-
//
// Package:    GEN/DemoGEN
// Class:      DemoGEN
// 
/**\class DemoGEN DemoGEN.cc GEN/DemoGEN/plugins/DemoGEN.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Gouranga Kole
//         Created:  Mon, 03 Dec 2018 05:56:57 GMT
//
//


// system include files
#include <iostream>
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1D.h"
#include "TTree.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class DemoGEN : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit DemoGEN(const edm::ParameterSet&);
      ~DemoGEN();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
  edm::Service<TFileService> fs;
  edm::EDGetTokenT<GenEventInfoProduct> GenToken_;
  edm::EDGetTokenT<LHEEventProduct> LheToken_;
  double theWeight;
  double pweight[1000];
  const int ptNBins;
  const double ptMin;
  const double ptMax;
  TH1D *h1_w;
  TTree* outTree_;
  double Htot, Hbb, Hgg, Hww, Hzz;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoGEN::DemoGEN(const edm::ParameterSet& iConfig):
  ptNBins(iConfig.getParameter<int>("PtNBins")),
  ptMin(iConfig.getParameter<double>("PtMin")),
  ptMax(iConfig.getParameter<double>("PtMax"))
{
  //now do what ever initialization is needed
  usesResource("TFileService");
  GenToken_=consumes<GenEventInfoProduct> (iConfig.getParameter<edm::InputTag>( "gentag") ) ;
  LheToken_=consumes<LHEEventProduct> (iConfig.getParameter<edm::InputTag>( "lhetag"));
  h1_w = fs->make<TH1D>("h1_w", "w", ptNBins, ptMin, ptMax);
  outTree_ = fs->make<TTree>("ntree","ntree");
  outTree_->Branch("pweight"        , pweight       ,"pweight[1000]/D");
  Htot=0.; Hbb=0.; Hgg=0.; Hww=0.; Hzz=0.;
}


DemoGEN::~DemoGEN()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoGEN::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace edm;
   edm::Handle<GenEventInfoProduct> genEvtInfo;
   iEvent.getByToken(GenToken_,genEvtInfo);
   theWeight = genEvtInfo->weight();
   //   std::cout<<theWeight<<std::endl;  
   h1_w->Fill(theWeight);

   
   edm::Handle<LHEEventProduct> wgtsource;
   iEvent.getByToken(LheToken_, wgtsource);
   for(size_t ki=0; ki<wgtsource->weights().size(); ki++) {
     pweight[ki]=wgtsource->weights()[ki].wgt/wgtsource->originalXWGTUP(); 
     std::cout<<ki<<" "<<pweight[ki]<<std::endl;
   }

   outTree_->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
DemoGEN::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoGEN::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoGEN::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoGEN);
