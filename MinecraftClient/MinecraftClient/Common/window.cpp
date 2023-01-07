#include "window.h"


namespace GNF::Common
{
    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_nativeWindow);
    }
    void Window::HandleEventsIfAny()
    {
        glfwSwapBuffers(m_nativeWindow);
        glfwPollEvents();
    }
	Window* Window::CreateWindow()
	{
		g_instance.reset(new Window());

        return g_instance.get();
	}

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
    void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        MouseMoveEventArgs e(xpos, ypos, isMouseRaw);

        OnMouseMove(e);
    }
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        MousePressedEventArgs e(button,action);
        MousePressed(e);
    }
    void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        KeyPressedEventArgs e(key, action);
        switch (action)
        {
            case GLFW_PRESS:
                switch (key)
                {
                    case GLFW_KEY_F:
                        if (isMouseRaw)
                        {
                            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                            isMouseRaw = false;
                        }
                        else
                        {
                            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                            isMouseRaw = true;
                        }
                        break;
                }
                break;
        }
        KeyPressed(e);
    }
	Window::Window()
	{
        // glfw: initialize and configure
   // ------------------------------

        if (!glfwInit())
            exit(EXIT_FAILURE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);


        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(640, 480, "Indie MC", NULL, NULL);
        if (window == NULL)
        {
            glfwTerminate();
            exit(-1);
        }

        glfwSetWindowUserPointer(window, this);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        auto func = [](GLFWwindow* w, int key, int scancode, int action, int mods)
        {
            ((Window*)glfwGetWindowUserPointer(w))->key_callback(w, key, scancode, action, mods);
        };
        
        auto mousePosFunc = [](GLFWwindow* window, double xpos, double ypos)
        {
            ((Window*)glfwGetWindowUserPointer(window))->cursor_position_callback(window, xpos, ypos);

        };

        auto mouseButtonFunc = [](GLFWwindow* window, int button, int action, int mods)
        {
            ((Window*)glfwGetWindowUserPointer(window))->mouse_button_callback(window, button, action, mods);
        };

        glfwSetKeyCallback(window, func);
        glfwSetCursorPosCallback(window, mousePosFunc);
        glfwSetMouseButtonCallback(window, mouseButtonFunc);
        // glad: load all OpenGL function pointers
  // ---------------------------------------
        /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            exit(-1);
        }*/
        gladLoadGL();

        glfwSwapInterval(1);

        m_nativeWindow = window;
	}

  
}