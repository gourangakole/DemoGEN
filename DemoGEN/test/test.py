import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process("Demo")

#runOnMC = True
#process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_condDBv2_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#if runOnMC:
#   process.GlobalTag.globaltag = '94X_mc2017_realistic_v14' 
#elif not(runOnMC):
#   process.GlobalTag.globaltag = '94X_mc2017_realistic_v14'


process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.load("FWCore.MessageService.MessageLogger_cfi")
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

print 'open file'
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    #   fileNames = cms.untracked.vstring(
         fileNames = cms.untracked.vstring(options.inputFiles
       #'/store/mc/RunIIFall17MiniAOD/DYJetsToEE_M-50_LTbinned_0To75_5f_LO_13TeV-madgraph_pythia8/MINIAODSIM/94X_mc2017_realistic_v11-v1/20000/003B2BBC-DE0F-E811-A321-FA163ED1BCED.root'
       # '/store/mc/RunIIFall17MiniAOD/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/94X_mc2017_realistic_v10-v2/10000/0A308ACD-50F7-E711-905C-0CC47A78A4A6.root'
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00542.root' #500 GeV
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00551.root' #1000 GeV
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00553.root' #1250 GeV
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00555.root' #1500 GeV
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00559.root' #2000 GeV
       #'file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00561.root' #3000 GeV

                                           )
                            )


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.demo = cms.EDAnalyzer('DemoGEN',
    gentag = cms.InputTag('generator'),
    lhetag = cms.InputTag('externalLHEProducer'),
                              #genSrc = cms.InputTag('prunedGenParticles'), # genParticles'),
    PtNBins = cms.int32(20),
    PtMin = cms.double(-10.),
    PtMax = cms.double(10.),
)


process.p = cms.Path(process.demo)
process.TFileService = cms.Service('TFileService',
    #fileName = cms.string("eff_M3000.root")
     fileName = cms.string( options.outputFile )
)
