#ifndef SHOWERRECOALGMODULAR_CXX
#define SHOWERRECOALGMODULAR_CXX

#include "ShowerRecoAlgModular.h"

namespace showerreco {

    Shower_t ShowerRecoAlgModular::RecoOneShower(const ShowerClusterSet_t& clusters){
      // Run over the shower reco modules:
      Shower_t result;
      Shower_t localCopy = result;

      for (auto & module : _modules){
        module -> do_reconstruction(clusters, result);
        if (_debug){
          printChanges(localCopy, result,module->name());
          localCopy = result;
        }

      }

      return result;
    }
    
    void ShowerRecoAlgModular::AddShowerRecoModule( ShowerRecoModuleBase * module){
      _modules.push_back(module);
    }

    void ShowerRecoAlgModular::InsertShowerRecoModule(ShowerRecoModuleBase * module, unsigned int index){
      if (_modules.size() > index){
        _modules.insert(_modules.begin() + index, module);
      }
      else{
        std::cerr << "WARNING: Request to insert module at index " << index << " which is beyond the last index." << std::endl;
      }
    }

    void ShowerRecoAlgModular::InsertShowerRecoModule(ShowerRecoModuleBase * module, std::string name){
      for (unsigned int index = 0; index < _modules.size(); index ++){
        if (_modules.at(index)->name() == name){
          _modules.insert(_modules.begin() + index, module);
          return;
        }
      }
      std::cerr << "WARNING: Request to insert module after non existing module \"" << name << "\"" << std::endl;

    }
    

    void ShowerRecoAlgModular::ReplaceShowerRecoModule( ShowerRecoModuleBase * module, unsigned int index){
      if (_modules.size() > index){
        _modules.at(index) = module;
      }
      else{
        std::cerr << "WARNING: Request to remove non existing module at index " << index << std::endl;
      }
    }

    
    void ShowerRecoAlgModular::ReplaceShowerRecoModule( ShowerRecoModuleBase * module, std::string name){

      for (unsigned int index = 0; index < _modules.size(); index ++){
        if (_modules.at(index)->name() == name){
          _modules.at(index) = module;
          return;
        }
      }
      std::cerr << "WARNING: Request to remove non existing module \"" << name << "\"" << std::endl;

    }

    void ShowerRecoAlgModular::PrintModuleList(){

      std::cout << "Print the list of modules to run in Shower Reco Alg Modular:\n";
      int i = 0;
      for (auto & module : _modules){
        std::cout << "\t" << i << ") " << module -> name() << "\n";
        i++;
      }

    }

    void ShowerRecoAlgModular::printChanges(const Shower_t & localCopy, const Shower_t result, std::string moduleName){

          // Look at each value of Shower_t and if it has changed, print out that change
          std::cout << "Printing the list of changes made by module " << moduleName << std::endl;

          // Compare vectors by x/y/z/ values
          // Doing comparisons in the order of values in Shower_t
          // Cos Start:
          if (localCopy.fDCosStart.X() != result.fDCosStart.X() ||
              localCopy.fDCosStart.Y() != result.fDCosStart.Y() ||
              localCopy.fDCosStart.X() != result.fDCosStart.X() ) {
            std::cout << "\tfDCosStart has changed from (" 
                      << localCopy.fDCosStart.X() << ", "
                      << localCopy.fDCosStart.Y() << ", " 
                      << localCopy.fDCosStart.Z() << ") to (" 
                      << result.fDCosStart.X() << ", " 
                      << result.fDCosStart.Y() << ", " 
                      << result.fDCosStart.Z() << ") " 
                      << std::endl; 
          }

          // Sigma Cos Start:
          if (localCopy.fSigmaDCosStart.X() != result.fSigmaDCosStart.X() ||
              localCopy.fSigmaDCosStart.Y() != result.fSigmaDCosStart.Y() ||
              localCopy.fSigmaDCosStart.X() != result.fSigmaDCosStart.X() ) {
            std::cout << "\tfSigmaDCosStart has changed from (" 
                      << localCopy.fSigmaDCosStart.X() << ", "
                      << localCopy.fSigmaDCosStart.Y() << ", " 
                      << localCopy.fSigmaDCosStart.Z() << ") to (" 
                      << result.fSigmaDCosStart.X() << ", " 
                      << result.fSigmaDCosStart.Y() << ", " 
                      << result.fSigmaDCosStart.Z() << ") " 
                      << std::endl; 
          }
          
          // XYZ Start:
          if (localCopy.fXYZStart.X() != result.fXYZStart.X() ||
              localCopy.fXYZStart.Y() != result.fXYZStart.Y() ||
              localCopy.fXYZStart.X() != result.fXYZStart.X() ) {
            std::cout << "\tfXYZStart has changed from (" 
                      << localCopy.fXYZStart.X() << ", "
                      << localCopy.fXYZStart.Y() << ", " 
                      << localCopy.fXYZStart.Z() << ") to (" 
                      << result.fXYZStart.X() << ", " 
                      << result.fXYZStart.Y() << ", " 
                      << result.fXYZStart.Z() << ") " 
                      << std::endl; 
          }

          // Sigma XYZ Start
          if (localCopy.fSigmaXYZStart.X() != result.fSigmaXYZStart.X() ||
              localCopy.fSigmaXYZStart.Y() != result.fSigmaXYZStart.Y() ||
              localCopy.fSigmaXYZStart.X() != result.fSigmaXYZStart.X() ) {
            std::cout << "\tfSigmaXYZStart has changed from (" 
                      << localCopy.fSigmaXYZStart.X() << ", "
                      << localCopy.fSigmaXYZStart.Y() << ", " 
                      << localCopy.fSigmaXYZStart.Z() << ") to (" 
                      << result.fSigmaXYZStart.X() << ", " 
                      << result.fSigmaXYZStart.Y() << ", " 
                      << result.fSigmaXYZStart.Z() << ") " 
                      << std::endl; 
          }

          // Length
          if (localCopy.fLength != result.fLength) {
            std::cout << "\tfDCosStart has changed from " << localCopy.fLength 
                      << " to "  << result.fLength << std::endl; 
          }

          // Opening Angle
          if (localCopy.fOpeningAngle != result.fOpeningAngle) {
            std::cout << "\tfDCosStart has changed from " << localCopy.fOpeningAngle 
                      << " to "  << result.fOpeningAngle << std::endl; 
          }

          // Since these should be length = nplanes, checking each plane for change
          // If changed, print out
          // Total Energy
          bool changed = false;
          for (unsigned int i = 0; i < localCopy.fTotalEnergy.size(); i++){
            if (localCopy.fTotalEnergy[i] != result.fTotalEnergy[i]){
              changed = true;
              break;
            }
          }

          if (changed){
            std::cout << "\tfTotalEnergy has changed from (";
            for (auto & val : localCopy.fTotalEnergy ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fTotalEnergy ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }


          // Sigma Total Energy
          changed = false;
          for (unsigned int i = 0; i < localCopy.fSigmaTotalEnergy.size(); i++){
            if (localCopy.fSigmaTotalEnergy[i] != result.fSigmaTotalEnergy[i]){
              changed = true;
              break;
            }
          }
          if (changed){
            std::cout << "\tfSigmaTotalEnergy has changed from (";
            for (auto & val : localCopy.fSigmaTotalEnergy ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fSigmaTotalEnergy ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }

          // dEdx
          changed = false;
          for (unsigned int i = 0; i < localCopy.fdEdx.size(); i++){
            if (localCopy.fdEdx[i] != result.fdEdx[i]){
              changed = true;
              break;
            }
          }
          if (changed){
            std::cout << "\tfdEdx has changed from (";
            for (auto & val : localCopy.fdEdx ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fdEdx ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }


          // sigma dEdx
          changed = false;
          for (unsigned int i = 0; i < localCopy.fSigmadEdx.size(); i++){
            if (localCopy.fSigmadEdx[i] != result.fSigmadEdx[i]){
              changed = true;
              break;
            }
          }
          if (changed){
            std::cout << "\tfSigmadEdx has changed from (";
            for (auto & val : localCopy.fSigmadEdx ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fSigmadEdx ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }

          // Total MIP Energy
          changed = false;
          for (unsigned int i = 0; i < localCopy.fTotalMIPEnergy.size(); i++){
            if (localCopy.fTotalMIPEnergy[i] != result.fTotalMIPEnergy[i]){
              changed = true;
              break;
            }
          }
          if (changed){
            std::cout << "\tfTotalMIPEnergy has changed from (";
            for (auto & val : localCopy.fTotalMIPEnergy ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fTotalMIPEnergy ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }

          // Sigma Total MIP Energy
          changed = false;
          for (unsigned int i = 0; i < localCopy.fSigmaTotalMIPEnergy.size(); i++){
            if (localCopy.fSigmaTotalMIPEnergy[i] != result.fSigmaTotalMIPEnergy[i]){
              changed = true;
              break;
            }
          }
          if (changed){
            std::cout << "\tfSigmaTotalMIPEnergy has changed from (";
            for (auto & val : localCopy.fSigmaTotalMIPEnergy ) std::cout << val << " ";
            std::cout << ") to (";
            for (auto & val : result.fSigmaTotalMIPEnergy ) std::cout << val << " ";
            std::cout << ")" << std::endl;
          }

          if (localCopy.fBestPlane != result.fBestPlane) {
            std::cout << "\tfBestPlane has changed from " << localCopy.fBestPlane.Plane
                      << " to "  << result.fBestPlane.Plane << std::endl; 
          }

    }

} // showerreco

#endif