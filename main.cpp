//    glewInit();
//    cout << "硬件信息为:" << endl;
//    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
//    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
//    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
//    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
//    cout << "------------------------------------------------------" << endl;

#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "Light.h"
#include <cmath>
#include <map>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Model.h"
#include "Camera.h"
#include "FirstPersonGun.h"
#include "SceneController.h"
#include <ft2build.h>
#include FT_FREETYPE_H
using namespace std;

struct Character{
    GLuint     TextureID;  // 字形纹理的ID
    glm::ivec2 Size;       // 字形大小
    glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
    GLuint     Advance;
};

std::map<GLchar, Character> Characters;

unsigned int loadCubemap(std::vector<std::string> faces);
unsigned int loadTextureToGPU(const char * path, int slot);
void reset();
void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

GLuint fontVAO, fontVBO;
Camera camera(glm::vec3(0, 15.0f, 25.0f), glm::vec3(0, 1.0f, 0), 0.0f, 0.0f);
DirectionalLight directionalLight(glm::vec3(0.4, 0.4, 0.4), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.4, 0.4, 0.4),
        glm::vec3(glm::radians(45.0), 0, glm::radians(45.0)));
PointLight pointLight(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(5.0f,10.0f,0.0f),
        1.0f, 0.09f, 0.032f);
SpotLight spotLight(glm::vec3(2.0, 2.0, 2.0), glm::vec3(2.0, 2.0, 2.0), glm::vec3(2.0, 2.0, 2.0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
        1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)),  glm::cos(glm::radians(15.0f)));
void processInput(GLFWwindow *window);
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;
float deltaTime = 0.1f;

float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow * window;
    if(!glfwInit()){
        cout<<"create window failed!"<<endl;
        exit(1);
    }
    window = glfwCreateWindow(800,600,"hello window",nullptr, nullptr);
    if(window== nullptr){
        cout<<"window is null!"<<endl;
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//    stbi_set_flip_vertically_on_load(true);
    //init fonts
    FT_Library ft;
    if(FT_Init_FreeType(&ft)){
        cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
    }
    FT_Face face;
    if (FT_New_Face(ft, "/Users/liuxiaobei/CLionProjects/openGL_Test/Font/Arial.ttf", 0, &face)){
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
    for (GLubyte c = 0; c < 128; c++)
    {
        // 加载字符的字形
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // 生成纹理
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // 设置纹理选项
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // 储存字符供之后使用
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    //game state
    int score = 0;
    bool end = false;

//    unsigned int texture = loadTextureToGPU("/Users/liuxiaobei/CLionProjects/openGL_Test/Texture/container.jpg",0);
    vector<string> faces{
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/right.jpg",
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/left.jpg",
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/top.jpg",
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/bottom.jpg",
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/front.jpg",
        "/Users/liuxiaobei/CLionProjects/openGL_Test/skybox-1/back.jpg"
    };

    unsigned int skybox = loadCubemap(faces);

    Shader skyShader("/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/SkyBox.vert",
            "/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/SkyBox.frag");

    Shader shader("/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/ModelVert.vert",
            "/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/ModelFrag.frag");
    Shader fontShader("/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/FontVert.vert",
            "/Users/liuxiaobei/CLionProjects/openGL_Test/ShaderDir/FontFrag.frag");
    SceneController sceneController;
    sceneController.InitScene();
    //skybox
    unsigned int skyVAO,skyVBO;
    glGenVertexArrays(1,&skyVAO);
    glGenBuffers(1,&skyVBO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER,skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    //font
    glGenVertexArrays(1, &fontVAO);
    glGenBuffers(1, &fontVBO);
    glBindVertexArray(fontVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    FirstPersonGun firstPersonGun(camera);
    Enemy enemy;
    irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
    time_t endtime = time(nullptr) + 30;
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);
        reset();
        //Draw SkyBox
        glUseProgram(skyShader.ID);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view(1.0f);
        view = camera.getViewMat();
        view[3][0] = view[3][1] = view[3][2] = 0;
        glDisable(GL_DEPTH_TEST);
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(120.0f, 120.0f, 120.0f));
        glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(skyShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniform1i(glGetUniformLocation(skyShader.ID,"skybox"),0);
        glBindVertexArray(skyVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glEnable(GL_DEPTH_TEST);
        //Draw text
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
        RenderText(fontShader, "Score:" + to_string(score), 630.0f, 540.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        time_t rtime = endtime - time(nullptr) > 0 ? endtime - time(nullptr) : 0;
        RenderText(fontShader, "Time:" + to_string(rtime), 40.0f, 540.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        RenderText(fontShader, "in 30s get at least 70 score", 200.0f, 40.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
        RenderText(fontShader, "- o -", 395.0f, 300.0f, 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(fontShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // render the loaded model
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glUseProgram(shader.ID);
        directionalLight.setDiffuse(shader.ID);
        directionalLight.setSpecular(shader.ID);
        directionalLight.setAmbinet(shader.ID);
        directionalLight.setDirection(shader.ID);

        pointLight.setAmbinet(shader.ID);
        pointLight.setSpecular(shader.ID);
        pointLight.setDiffuse(shader.ID);
        pointLight.setPosition(shader.ID);
        pointLight.setConstant(shader.ID);
        pointLight.setLinear(shader.ID);
        pointLight.setQuadratic(shader.ID);

        spotLight.position = camera.Position;
        spotLight.direction = camera.Forward;
        spotLight.setAmbinet(shader.ID);
        spotLight.setSpecular(shader.ID);
        spotLight.setDiffuse(shader.ID);
        spotLight.setPosition(shader.ID);
        spotLight.setConstant(shader.ID);
        spotLight.setLinear(shader.ID);
        spotLight.setQuadratic(shader.ID);
        spotLight.setCutff(shader.ID);
        spotLight.setOuterCutoff(shader.ID);
        spotLight.setDirection(shader.ID);
//        glUniform3f(glGetUniformLocation(shader.ID, "lightPos"), 10.0f,10.0f,10.0f);
//        glUniform3f(glGetUniformLocation(shader.ID, "lightColor"), 0.0f,0.5f,.0f);
        glUniform3f(glGetUniformLocation(shader.ID, "viewPos"), camera.Position.x,camera.Position.y,camera.Position.z);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
        view = camera.getViewMat();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, &view[0][0]);
        enemy.Draw(shader);
        sceneController.Draw(shader);
        firstPersonGun.Draw(shader);
        sceneController.checkCollision(firstPersonGun.player,firstPersonGun.camera);
        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !end) {
            enemy.checkShoot(&camera, firstPersonGun.player, engine,score);
            if (engine != nullptr) {
                engine->play2D("/Users/liuxiaobei/CLionProjects/openGL_Test/Sound/xjls_shoot1.wav");
            }
        }
        enemy.checkAmount();
        camera.rigidbody.onLand();
        camera.updatePosition();
        if(endtime - time(nullptr) < 0){
            end = true;
            string info;
            if(score >= 70){
                info = "You Win The Game Press Esc To Exit";
            }
            else{
                info = "You Lose The Game Press Esc To Exit";
            }
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
            RenderText(fontShader, info, 200.0f, 300.0f, 0.5f, glm::vec3(1.0f,1.0f,1.0f));
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &skyVAO);
    glDeleteBuffers(1, &skyVBO);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyBoard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyBoard(BACK, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyBoard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyBoard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera.processKeyBoard(UP, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    int width,height;
    glfwGetWindowSize(window, &width, &height);
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    if(xpos > width * 5/ 6){
        xpos = width * 3/ 6;
        glfwSetCursorPos(window,xpos,ypos);
    }

    if(xpos < width / 6){
        xpos = width * 3/ 6;
        glfwSetCursorPos(window,xpos,ypos);
    }
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

unsigned int loadTextureToGPU(const char * path, int slot){
    unsigned int texture;
    glGenTextures(1, &texture);
    glewInit();
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width,height,nlchannle;
    unsigned char * data = stbi_load(path,&width,&height,&nlchannle,0);
    if(data){
        GLenum format;
        if (nlchannle == 1)
            format = GL_RED;
        else if (nlchannle == 3)
            format = GL_RGB;
        else if (nlchannle == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glewInit();
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

unsigned int loadCubemap(std::vector<std::string> faces){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void reset(){
    camera.rigidbody.collide = false;
    camera.rigidbody.collideBack = false;
    camera.rigidbody.collideRight = false;
    camera.rigidbody.collideLeft = false;
    camera.rigidbody.collideForward = false;
}

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    glUseProgram(shader.ID);
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(fontVAO);

    // Iterate through all characters
    for (int i = 0 ; i< text.length(); ++i)
    {
        Character ch = Characters[text[i]];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}