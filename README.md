Instructions for local installation:

 ```
 cmsrel CMSSW_10_2_6 (or higher CMSSW version)
 cd CMSSW_10_2_6/src
 cmsenv
 mkdir GEN
 cd GEN
 git clone -b 11Oct2019_LHEheader git@github.com:gourangakole/DemoGEN.git 
 scram b
 ```

# To Run the example code
```
cd DemoGEN/test
cmsRun test.py inputFiles="file:/afs/cern.ch/user/g/gkole/public/HIG-RunIIFall17wmLHEGS-01124_2_slc7_withoutMS.root" maxEvents=-1 outputFile=HIG-RunIIFall18wmLHEGS-00561.root &>without_MS.txt
cmsRun test.py inputFiles="file:/afs/cern.ch/user/g/gkole/public/HIG-RunIIFall17wmLHEGS-01124_2_slc6.root" maxEvents=-1 outputFile=HIG-RunIIFall18wmLHEGS-00561.root >& with_MS.txt &

vimdiff with_MS.txt without_MS.txt 

```