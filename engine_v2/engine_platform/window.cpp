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
}

void Window::windowInitialize() {
    initializeGLFW();

    m_native_handle = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);

    if (!m_native_handle) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    glfwMakeContextCurrent(m_native_handle);
    glfwSwapInterval(1);  // max frame rate is monitor refresh rate

    int framebuffer_width = 0;
    int framebuffer_height = 0;
    glfwGetFramebufferSize(m_native_handle, &framebuffer_width, &framebuffer_height);
    m_framebuffer_extent = {framebuffer_width, framebuffer_height};
    m_framebuffer_resized = true;
    glViewport(0, 0, framebuffer_width, framebuffer_height);

    glfwSetWindowUserPointer(m_native_handle, this);
    glfwSetFramebufferSizeCallback(m_native_handle, frameBufferSizeCallback);

    initializeGLAD();
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