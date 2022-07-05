#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math.h"

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINE_STRIP, 0, 1);
    auto error = glGetError();

    printf("%d", error);
    
    glutSwapBuffers();
}


static void create_vertex_buffer(){
    vec3 ver = vec3(0);
    vec3 vs[3];
    vs[0] = vec3(0);
    vs[1] = vec3(0.5, 0.5, 0);
    vs[2] = vec3(0.5, -0.5, 0);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vs), vs, GL_STATIC_DRAW);

}

int main(int argc, char** argv)
{
    

    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    int width = 800;
    int height = 800;
    glutInitWindowSize(width, height);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);


    int win = glutCreateWindow("Tutorial 01");
    printf("window id: %d\n", win);

    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }




    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);


    create_vertex_buffer();


    glutDisplayFunc(RenderSceneCB);

    glutMainLoop();

    return 0;
}