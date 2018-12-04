Instructions for installation:
 ```
 cmsrel CMSSW_10_2_6
 cd CMSSW_10_2_6/src
 cmsenv
 mkdir GEN
 cd GEN
 git clone git@github.com:gourangakole:DemoGEN.git 
 
 ```

# To Run 
```
cmsRun test.py inputFiles="file:/eos/user/g//gkole/PostDoc/temp/HIG-RunIIFall18wmLHEGS-00561.root" maxEvents=-1 outputFile=HIG-RunIIFall18wmLHEGS-00561.root
```