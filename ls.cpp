#include "header.cpp"
using namespace std;





  auto print_permissions = [](mode_t mode) {
             char permissions[10] = "---------";
            if (S_ISDIR(mode)) permissions[0] = 'd';
            if (mode & S_IRUSR) permissions[1] = 'r';
            if (mode & S_IWUSR) permissions[2] = 'w';
            if (mode & S_IXUSR) permissions[3] = 'x';
            if (mode & S_IRGRP) permissions[4] = 'r';
            if (mode & S_IWGRP) permissions[5] = 'w';
            if (mode & S_IXGRP) permissions[6] = 'x';
            if (mode & S_IROTH) permissions[7] = 'r';
            if (mode & S_IWOTH) permissions[8] = 'w';
            if (mode & S_IXOTH) permissions[9] = 'x';
            cout << permissions;
        };


void new_list(vector<string> argv) {
    const char* directory = ".";
    bool show_hidden = false;
    bool show_long_format = false;

    for (int i = 1; i < argv.size(); i++) {
     
        if (strcmp(argv[i].c_str(), "-a") == 0) {
            show_hidden = true;
        } else if (strcmp(argv[i].c_str(), "-l") == 0) {
            
            show_long_format = true;
        }
        else if(strcmp(argv[i].c_str(), ".") == 0) {
            continue;  
        }
        else if(strcmp(argv[i].c_str(), "..") == 0) {
            directory="..";
        }
        else if(strcmp(argv[i].c_str(), "~")==0){
             const char* home_dir = getenv("HOME");
                if (home_dir != nullptr) {
                    directory = home_dir;
                }
        }

    }

    DIR* dir;
    struct dirent* entry;

    dir = opendir(directory);

    if (dir == nullptr) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (!show_hidden && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) {
            continue;  // Skip current directory and parent directory entries
        }

        if (show_long_format) {
            // Use stat to get detailed file information
            struct stat fileStat;
            if (stat(entry->d_name, &fileStat) == -1) {
                perror("Error getting file stats");
                continue;
            }

            print_permissions(fileStat.st_mode);

            struct passwd* pw = getpwuid(fileStat.st_uid);
            struct group* gr = getgrgid(fileStat.st_gid);

            cout << " " << setw(10) << left << pw->pw_name;
            cout << " " << setw(10) << left << gr->gr_name;
            cout << " " << setw(8) << right << fileStat.st_size;

            char timeBuffer[80];
            strftime(timeBuffer, sizeof(timeBuffer), "%b %d %H:%M", localtime(&fileStat.st_mtime));

            cout << " " << timeBuffer << " ";
        }

        cout << entry->d_name;
        
        if (show_long_format) {
            cout << endl;
        } else {
            cout <<endl;
        }
    }
       closedir(dir);
}







