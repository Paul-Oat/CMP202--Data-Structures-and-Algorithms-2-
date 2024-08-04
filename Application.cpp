
// Include GLEW/GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iomanip>
//include headder files
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include "Renderer.h"
#include "Texture.h"
#include "Julia.h"

//Ccode from lab to report accelarator 
void report_accelerator(const Concurrency::accelerator a)
{
    const std::wstring bs[2] = { L"false", L"true" };
    std::wcout << ": " << a.description << " "
        << endl << "       device_path                       = " << a.device_path
        << endl << "       dedicated_memory                  = " << std::setprecision(4) << float(a.dedicated_memory) / (1024.0f * 1024.0f) << " Mb"
        << endl << "       has_display                       = " << bs[a.has_display]
        << endl << "       is_debug                          = " << bs[a.is_debug]
        << endl << "       is_emulated                       = " << bs[a.is_emulated]
        << endl << "       supports_double_precision         = " << bs[a.supports_double_precision]
        << endl << "       supports_limited_double_precision = " << bs[a.supports_limited_double_precision]
        << endl;
}
//code for lising all aaccelrator devices
void list_accelerators()
{
    //get all accelerators available to us and store in a vector so we can extract details
    std::vector<Concurrency::accelerator> accls = Concurrency::accelerator::get_all();

    // iterates over all accelerators and print characteristics
    for (int i = 0; i < accls.size(); i++)
    {
        Concurrency::accelerator a = accls[i];
        report_accelerator(a);

    }

    //Use default accelerator
    Concurrency::accelerator a = Concurrency::accelerator(Concurrency::accelerator::default_accelerator);
    std::wcout << " default acc = " << a.description << endl;
    cout << endl;
} // list_accelerators

//inialise OPENGL and GLFW
GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1024 * 2, 2048 * 2, "Julia Set Press esc to Escape", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return nullptr;
        
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

int main(void)
{
    //list GPU accelarator code from lab 
    list_accelerators();
    int iBench = 0, iEnd = 1;
    //allow the program to run multiple times 

    while(iEnd == 1) {
        //FInd
        std::cout << "////////////////////" << endl;
        std::cout << "//// Paul Oates ////" << endl;
        std::cout << "//// Julia Set  ////" << endl;
        std::cout << "//////////////////////" << endl;
        std::cout << "Benchmark(1)/OpenGL(0)" << endl;
        std::cout << "   Benchmark time   " << endl;
        std::cout <<  "       15 MINS     " << endl;
        std::cout << "////////////////////" << endl;
        std::cin >> iBench;
        if (iBench == 1) {
            //run benchmark
            Julia x;
            x.Benchmark();
            x.~Julia();
        }
        else {
            //no benchmark 
            Julia julia;
            julia.Ouput();


           //inialise GL window
            GLFWwindow* window = InitWindow();
            if (!window)
                return -1;

            //plot points
            float positions[] = {
                -1.0f, -1.0f, 0.0f, 0.0f, // 0
                 1.0f, -1.0f, 1.0f, 0.0f, // 1
                 1.0f,  1.0f, 1.0f, 1.0f, // 2
                -1.0f,  1.0f, 0.0f, 1.0f  // 3
            };


            //path to follow to make a square 
            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };
            //gl macro for debuging
            //enable GL
            GLCall(glEnable(GL_BLEND));
            GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

            //declare Vertex array instance 
            VertexArray va;
            //assign points to buffer 
            VertexBuffer vb(positions, 4 * 4 * sizeof(float));
            //assign positons to buffer
            IndexBuffer ib(indices, 6);

            //declare layout square 
            VertexBufferLayout layout;
            layout.AddFloat(2);
            layout.AddFloat(2);

            va.AddBuffer(vb, layout);


            //load shader
            Shader shader("res/shaders/Baisic.shader");
            shader.Bind();
            //load texture
            Texture texture("./julia.tga");
            texture.Bind();
            shader.SetUniform1i("x", 0);

            Renderer renderer;
            //draw 
            do {
                renderer.Clear();

                renderer.Draw(va, ib, shader);



                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();
            } //  if the ESC key was pressed or the window was closed
            while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0);


            // teminate GLFW instance
            glfwTerminate();

    
        }
        //ask user if they would like to run again 
        std::cout << "///////////////////////////" << endl;
        std::cout << "Would you like to run again" << endl;
        std::cout << "//   YES (1) / NO (0)   ///" << endl;
        std::cout << "///////////////////////////" << endl;
        std::cin >> iEnd;
        system("cls");
    }


    return 0;
}

