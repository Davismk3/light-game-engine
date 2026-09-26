#include "window.hpp"

/*
C++ Refresher
int* ptr_to_var = &var          a pointer to var's address
var = *ptr_to_var               var from the pointer to its address
int& ref_to_var = var           reference to var, shorthand for (*ptr_to_var)
*/

namespace {
    static void glfwErrorCallback(int error, const char* description) {
        std::cerr << "[GLFW Error " << error << "] " << description << '\n';
    }

    void initializeGLFW() {
        glfwSetErrorCallback(glfwErrorCallback);

        #ifdef __APPLE__
        // GLFW's Cocoa backend chdir()s into Contents/Resources during
        // glfwInit() if that folder exists (a legacy convention for
        // resolving assets relative to it) - overriding this executable's
        // own chdir-to-its-own-directory logic from main(), which every
        // relative asset path in this codebase (engine/engine_assets/...,
        // app/app_assets/...) actually depends on. Disable it.
        glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
        #endif

        if (!glfwInit()) throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    void initializeGLAD() {
        gladLoadGL(glfwGetProcAddress);
    }

    void configureOpenGL() {
        glEnable(GL_DEPTH_TEST);
    }

    void frameBufferSizeCallback(GLFWwindow* m_window, int width, int height) {
        //glViewport(0, 0, width, height);
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(m_window));
        if (!window) return;
        window->m_framebuffer_extent = {width, height};
        window->m_framebuffer_resized = true;
    }

    void setIcon(GLFWwindow* native_handle) {
        GLFWimage images[1];
        images[0].pixels = stbi_load(ICON_PATH, &images[0].width, &images[0].height, 0, 4);

        if (images[0].pixels) {
            glfwSetWindowIcon(native_handle, 1, images);
            stbi_image_free(images[0].pixels);
        } else printf("app icon failed to load\n");
    }

    void scrollCallback(GLFWwindow* m_window, double xoffset, double yoffset) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(m_window));
        window->scrollX += xoffset;
        window->scrollY += yoffset;
    }
}

void Window::windowInitialize() {
    initializeGLFW();

    m_native_handle = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);

    if (!m_native_handle) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    glfwMakeContextCurrent(m_native_handle);

    // Must happen before any gl* call
    initializeGLAD();

    glfwSwapInterval(1);  // max frame rate is monitor refresh rate
    // ^ setting this to zero will cause the FPS to be unbounded, which may blow up your computer, so don't do it

    int framebuffer_width = 0;
    int framebuffer_height = 0;
    glfwGetFramebufferSize(m_native_handle, &framebuffer_width, &framebuffer_height);
    m_framebuffer_extent = {framebuffer_width, framebuffer_height};
    m_framebuffer_resized = true;
    glViewport(0, 0, framebuffer_width, framebuffer_height);

    glfwSetWindowUserPointer(m_native_handle, this);
    glfwSetFramebufferSizeCallback(m_native_handle, frameBufferSizeCallback);

    glfwSetScrollCallback(m_native_handle, scrollCallback);

    configureOpenGL();

    setIcon(m_native_handle);
}

void Window::windowClose() {
    glfwSetWindowShouldClose(m_native_handle, true);
}

void Window::windowShutdown() {
    glfwDestroyWindow(m_native_handle);
    glfwTerminate();
}

void Window::windowPollEvents() {
    scrollX = 0.0;
    scrollY = 0.0;
    
    glfwPollEvents();
}

void Window::windowSwapBuffers() {
    glfwSwapBuffers(m_native_handle);
}

bool Window::windowShouldClose() const {
    return glfwWindowShouldClose(m_native_handle);
}

GLFWwindow* Window::windowNativeHandle() const {
    return m_native_handle;
}

bool Window::windowConsumeFramebufferResize(FramebufferExtent& extent) {
    if (!m_framebuffer_resized) return false;

    extent = m_framebuffer_extent;
    m_framebuffer_resized = false;

    return true;
}