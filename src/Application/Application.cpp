#include "Application.h"

namespace PhiVideo {

    Application::Application(int argc, char** argv, std::string WorkDir, std::string ResDir)
        : argc(argc), argv(argv) {
        m_Info.WorkDir = WorkDir;
        m_Info.ResDir = ResDir;
        Init();
    }

    Application::~Application() {
        if (m_Inited) Terminate();
    }

    void Application::Init() {
        m_Inited = true;
        m_Framebuffer = new Framebuffer(m_Width, m_Height);
    }

    void Application::Terminate() {
        m_Inited = false;
        delete m_Framebuffer;
    }

    void Application::Run() {
    }

}
