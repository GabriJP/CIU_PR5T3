#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Espacio para las variables globales de la ventana
float gl_ancho = 2.0, gl_alto = 2.0, gl_cerca = 2.0, gl_lejos = 10.0; //cambiar seg�n el proyecto
int w_ancho = 700, w_alto = 700;


// Espacio para otras variables globales
int hombro = 0, codo = 0;

// Espacio para la declaración de funciones
void InitGlew();

void InitGL();

void Display();

void ReshapeSize(int ancho, int alto);

void Teclas(int key, int x, int y);

//main
int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w_ancho, w_alto);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("OpenGL Practica 5, tarea 3");
    InitGlew(); // despues de crear la primera ventana
    InitGL();
    glutDisplayFunc(Display); // registra la funcion de rendering
    glutReshapeFunc(ReshapeSize);
    glutSpecialFunc(Teclas);

    glutMainLoop(); // bucle principal

    return 0;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void Teclas(int key, int x, int y) {
#pragma clang diagnostic pop
    switch (key) {
        case GLUT_KEY_LEFT:
            (codo += 5) %= 360;
            break;
        case GLUT_KEY_RIGHT:
            (codo -= 5) %= 360;
            break;
        case GLUT_KEY_UP:
            (hombro += 5) %= 360;
            break;
        case GLUT_KEY_DOWN:
            (hombro -= 5) %= 360;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void wireBox(GLfloat width, GLfloat height, GLfloat depth) {
    glPushMatrix();
    glScalef(width, height, depth);
    glutWireCube(1.0);
    glPopMatrix();
}

void InitGlew() {

    // para poder utilizar trasnparentemente todas las extensiones de OpenGL

    GLenum glew_init = glewInit();
    if (glew_init != GLEW_OK) {
        // Problem: glewInit failed, something is seriously wrong.
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_init));
    } else
        fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void InitGL() {

    if (gl_ancho / w_ancho != gl_alto / w_alto) {
        fprintf(stderr, "La relaci�n de aspecto no es correcta\n");
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    // para cambiar el criterio de lo que se ve. LESS es el de defecto: se ve lo que tiene menor profundidad
    //glDepthFunc(GL_LESS);
    // TO DO

    //glViewport(0, 0, w_ancho, w_alto); // pordefecto ya se establece as� en la inicialización
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-gl_ancho / 2.0, gl_ancho / 2.0, -gl_alto / 2.0, gl_alto / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glMatrixMode(GL_MODELVIEW); // las futuras operaciones se refieren a las coordenadas de los modelos
}


// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
void ReshapeSize(int ancho, int alto) {

    float dx = gl_ancho;
    float dy = gl_alto;

    dx *= (float) ancho / (float) w_ancho;
    dy *= (float) alto / (float) w_alto;

    glViewport(0, 0, ancho, alto); // utiliza la totalidad de la ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-dx / 2.0, dx / 2.0, -dy / 2.0, dy / 2.0, gl_cerca, gl_lejos); // espacio de trabajo
    glMatrixMode(GL_MODELVIEW); // futuras operaciones se refieren a modelos
    glutPostRedisplay();
}

// función de gestion de ventana
void Display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
    glLoadIdentity(); // a partie de aqui empieza poner modelos y transformarlos.
    // TO DO

    glTranslatef(0.0f, 0.0f, -4.0f);
    glScalef(0.4f, 0.4f, 0.4f);

    glRotatef((GLfloat) hombro, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 0.5);

    //repetimos
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) codo, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.4, 0.5);

    glFlush(); // actualiza el framebuffer
    glutSwapBuffers(); // en caso de animacion
}