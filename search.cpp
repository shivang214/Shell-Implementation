#include "header.cpp"

bool searchFileOrFolderRecursively(const std::string& currentDir, const std::string& targetName) {
    DIR* dir = opendir(currentDir.c_str());
    if (!dir) {
        return false; // Failed to open directory
    }

    bool found = false;
    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (std::strcmp(entry->d_name, ".") == 0 || std::strcmp(entry->d_name, "..") == 0) {
            continue; // Skip "." and ".." entries
        }

        std::string entryPath = currentDir + "/" + entry->d_name;

        if (std::strcmp(entry->d_name, targetName.c_str()) == 0) {
            found = true;
            break; // Found the target
        }

        // Check if it's a directory
        struct stat st;
        if (stat(entryPath.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {

            found = searchFileOrFolderRecursively(entryPath, targetName);
            if (found) {
                break; // Found in a subdirectory
            }
        }
    }

    closedir(dir);
    return found;
}
