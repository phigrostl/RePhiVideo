#pragma once

#include "Base/Base.h"
#include "Framebuffer/Framebuffer.h"

#include <direct.h>
#include <shlwapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace PhiVideo {

    struct RenderInfo {
        std::string WorkDir;
        std::string ResDir;
    };

    class Application {
    public:
        Application(
            int argc, char** argv,
            std::string WorkDir, std::string ResDir
        );

        ~Application();

        void Run();

    public:
        std::string GetDir() const {
            char dir[MAX_PATH];
            if (!_getcwd(dir, MAX_PATH)) Exit("Failed to get Working Directory", 1);
            return dir;
        }

        void ToDir(std::string dir) const {
            char Dir[MAX_PATH];
            strcpy(Dir, dir.c_str());
            if (_chdir(Dir)) Exit("Failed to change directory to %s", 1, gbk2utf8(Dir).c_str());
        }

        std::string GetFileName(const std::string path) const {
            size_t pos = path.find_last_of("/\\");
            std::string tmp = path.substr(pos + 1);
            pos = tmp.find_last_of(".");
            return tmp.substr(0, pos);
        }

        std::string GetFilePath(const std::string& path) const {
            std::string result = path;
            size_t pos = result.find_last_of("/\\");
            if (pos != std::string::npos) result = result.substr(0, pos + 1);
            return result;
        }

    private:
        void Init();
        void Terminate();

    private:
        int argc;
        char** argv;

        int m_Width = 1920, m_Height = 1080;
        bool m_Inited = false;
        RenderInfo m_Info;
        Framebuffer* m_Framebuffer;
    };

}
