// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "data.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <string>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <strings.h>
#include "varify.hpp"
#include "calculator.hpp"
#include <fstream>

std::string res;
    std::string errorInfo;
    bool errorOccurs = false;
    bool quit = false;
    float lastTime = -1;
    float thisTime = 0;
    bool StateBattle = false;
    bool Statechoose = true;
    bool StateJudge = false;
    int BattleTime = 0;
    const std::string input[10]=
    {
        "(",
        ")",
        "<-",
        "=",
        "+",
        "-",
        "*",
        "/",
        "answer"
    };

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


void problem()
{
    do 
    { GenerateData(); }
    while (!exist());
}

void BattleWindow()
{
    ImGui::Begin("play");
    thisTime = ImGui::GetTime();
    for (int i = 0 ; i < 2 ; i++)
    {
        if (ImGui::Button(input[i].data(),ImVec2(100,100)))
        { res+= input[i]; }
        ImGui::SameLine();
    }
    if (ImGui::Button(input[2].data(),ImVec2(100,100)))
    {
        if (!res.empty())
        { res.pop_back(); }
    }
    ImGui::SameLine();
    if (ImGui::Button(input[3].data(),ImVec2(100,100)))
    {
        calculator cal;
        bool out = false;
        if (legal(res))
        { cal.read(res); }
        else  
        { 
            res.clear();
            errorOccurs = true;
            errorInfo = "bad input";
            lastTime = ImGui::GetTime();
            out = 1;
        }
        if (!out)
        {
            if (cal.result().getval() != 24)
            {
                res.clear();
                errorOccurs = true;
                errorInfo = "wrong result";
                lastTime = ImGui::GetTime();
            }
            else  
            {
                res.clear();
                errorOccurs = true;
                errorInfo = "win~~";
                lastTime = ImGui::GetTime();
            }
            problem();
        }
    }
    for (int i = 4 ; i < 8 ; i++)
    {
        if (ImGui::Button(input[i].data(),ImVec2(100,100)))
        { res+= input[i]; }
        if (i != 7)
            ImGui::SameLine();
    }
    for (int i = 0 ; i < 4 ; i++)
    {
        ImGui::PushID(i);
        if (ImGui::Button(std::to_string(data[i]).data(),ImVec2(100,100)))
        { res+= std::to_string(data[i]); }
        ImGui::PopID();
        if (i != 3)
            ImGui::SameLine();
    }
    if (ImGui::Button(input[8].data(),ImVec2(440,100)))
    {
        res.clear();
        errorOccurs = true;
        errorInfo = ans.str();
        lastTime = ImGui::GetTime();
        problem();
    }
    if (ImGui::Button("Back to Mode Select",ImVec2(440,100)))
    { 
        StateBattle = false;
        Statechoose = true;
    }
    if (errorOccurs && thisTime - lastTime <= 2.0f)
    { ImGui::Text(errorInfo.data()); }
    else 
    {
        errorOccurs = false;
        ImGui::Text(res.data());
    }
    
    ImGui::End();
}
bool FileMode = false;
bool ModeSelect = true;
int dataindex = 0;
string GUImodeshow="";
void JudgeWindow()
{
    ImGui::Begin("Solve");
    ImGui::Text("Give me an expression I try to solve it\n and save the answer as answer.txt in folder 'file'\n Please name your input file as input.txt in folder 'file'");
    if (ImGui::Button("Back to Mode Select",ImVec2(880,100)))
    { 
        StateJudge = false;
        Statechoose = true;
    }
    if (ModeSelect)
    {
        if (ImGui::Button("GUI Mode",ImVec2(440,100)))
        { 
            FileMode = false;
            ModeSelect = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("File Mode",ImVec2(440,100)))
        { 
            FileMode = true;
            ModeSelect = false;
        }
    }
    if (ModeSelect == false)
    {
        if (FileMode)
        {
            std::fstream file;
            file.open("../file/input.txt", std::ios::in);
            if (!file.is_open())
            { ImGui::Text("No such file"); }
            string input;
            int success = 0, total = 0;
            while (std::getline(file, input))
            {
                total++;
                try
                { 
                    string x;
                    for (auto it = input.begin(); it != input.end(); it++)
                    {
                        if (*it == '\t')
                        { 
                            data[dataindex] = stoi(x);
                            x.clear();
                            dataindex++;
                            continue;
                        }
                        if (*it >= 'A' && *it <= 'Z')
                        {
                            switch (*it) 
                            {
                                case 'J': x += "11";
                                break;
                                case 'Q': x += "12";
                                break;
                                case 'K': x += "13";
                            }
                        }
                        else if (*it >= '0' && *it <= '9')
                        {
                            x += *it;
                        }
                        else
                        {
                            data[dataindex] = stoi(x);
                            x.clear();
                            dataindex++;
                        }
                    }
                    data[dataindex] = stoi(x);
                    dataindex++;
                    if (dataindex == 4)
                    {
                        dataindex = 0;
                        std::fstream output;
                        output.open("../file/answer.txt", std::ios::out | std::ios::app);
                        if (exist())
                        { 
                            output<<"+"<<'\t';
                            success++;
                        }
                        else  
                        { output<<"-"<<'\t'; }
                        for (int i = 0 ; i < 4 ; i++)
                        { 
                            output<<data[i];
                            if (i != 3)
                                output<<'\t'; 
                        }
                        output<<'\n';
                        output.close();
                    }
                }
                catch(...)
                { 
                    std::fstream output;
                    output.open("../file/answer.txt", std::ios::out | std::ios::app);
                    output<<"wrong input"<<'\n';
                } 
            }
            std::fstream output;
            output.open("../file/answer.txt", std::ios::out | std::ios::app);
            output<<success << '/' <<total;
            output.close();
            StateJudge = false;
            Statechoose = true;
        }
        else  
        {
            for (int i = 1 ; i <= 13 ; i++)
            {
                if (ImGui::Button(std::to_string(i).c_str(),ImVec2(100,100)) && dataindex < 4)
                { 
                    data[dataindex] = i; 
                    GUImodeshow += std::to_string(i) + " ";
                    dataindex++;
                }
                if (i % 4 != 0)
                { ImGui::SameLine(); }
            }

            ImGui::Text(GUImodeshow.c_str());
            if (ImGui::Button("solve",ImVec2(460,100)))
            {
                std::fstream file;
                GUImodeshow = "";
                file.open("../file/answer.txt", std::ios::out | std::ios::trunc);
                if (dataindex != 4)
                { file << "bad input\n"; }
                else if (exist())
                {  file<<ans.str()<<'\n';  }
                else  
                {  file<<"no sovlution"<<'\n'; }
                file.close();
            }
        }
    }
    ImGui::End();
}
void chooseWindow()
{
    ImGui::Begin("Choose");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello welcome to 24 point game!");
    if (ImGui::Button("Play Mode",ImVec2(880,100)))
    { 
        StateBattle = true;
        Statechoose = false;
        problem();
    }
    if (ImGui::Button("Solution Mode",ImVec2(880,100)))
    { 
        StateJudge = true;
        Statechoose = false;
        FileMode = false;
        ModeSelect = true;
        int dataindex = 0;
        GUImodeshow = "";
    }
    if (ImGui::Button("Quit",ImVec2(880,100)))
    {  quit = true; }
    ImGui::End();
}
// Main code
int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "24", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

   
    io.Fonts->AddFontFromFileTTF("../font/Roboto-Medium.ttf", 30.0f);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // my code
        if (Statechoose)
        { chooseWindow(); }
        else if (StateBattle)
        { BattleWindow(); }
        else if (StateJudge)
        { JudgeWindow(); }






        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        if (quit)
        { break; }
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
