#include "FileDialog.h"
#include <nfd.hpp>
#include <iostream>

namespace FileDialog {
    std::string OpenFile() {

        NFD::UniquePath outPath;
        nfdfilteritem_t filterItem[1] = {{"Audio file", "wav,mp3,ogg,flac"}};
        nfdresult_t result = NFD::OpenDialog(outPath, filterItem, 1);
        
        if (result == NFD_OKAY) {
            std::string path = outPath.get();
            std::cout << "Selected file: " << path << std::endl;
            return path;
        } else if (result == NFD_CANCEL) {
            std::cout << "User cancelled selection." << std::endl;
        } else {
            std::cerr << "Error: " << NFD_GetError() << std::endl;
        }

        return std::string();
    }
}