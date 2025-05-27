#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cmath>

int rollDice() {
    return (rand() % 6) + 1;
}

int jumlahlemparan = 1;
int jumlahlemparan2 = 1;

//Variabel untuk nilai dari player
float bidak_player1_X = 0.5;
float bidak_player1_Y = 0.7;

float bidak_player2_X = 0.5;
float bidak_player2_Y = 0.4;

//Variabel untuk pergantian pemain
bool giliran_player1 = true;

// Variabel untuk menggeser observer
float geser_oberver_X = 0.2;
float geser_oberver_Y = 0.5;

//Variabel untuk batas Observer
const float batas_observer_kiri = 0.1;
const float batas_observer_kanan = 5.9;
const float batas_observer_bawah = 0.1;
const float batas_observer_atas = 13.9;

const int rows = 14;
const int cols = 6;

int pemenang = 0;

// Variabel untuk rotasi papan permainan
float sudut_rotasi_X = 0.0f;
float sudut_rotasi_Y = 0.0f;
float sudut_rotasi_Z = 0.0f;

// Variabel untuk pusat rotasi
float pusat_rotasi_X = 3.5f;
float pusat_rotasi_Y = 6.0f;
float pusat_rotasi_Z = 0.0f;

// Variabel untuk menyimpan sudut rotasi terakhir
float sudut_rotasi_terakhir_x = 0.0f;
float sudut_rotasi_terakhir_Y = 0.0f;
float sudut_rotasi_terakhir_Z = 0.0f;


bool isRotated = false;
bool rotasi_awal_dilakukan = false;

// Variabel global untuk mode warna
bool warna_transparan = false;

int viewMode = 0;

float pos[3];
GLdouble viewdir[] = {-1.0, 0.0, 0.0};


void drawZero(float xAtas, float yBawah, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    glColor3f(1.0f, 0.5f, 0.0f);

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, backZ);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, backZ);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, backZ);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, backZ);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, backZ);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);

    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, backZ);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, backZ);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.65f, backZ);

    glEnd();
}


void drawFour(float xAtas, float yBawah, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    // Bagian depan
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, frontZ);
    glEnd();

    // Bagian belakang (menggunakan depth untuk memberikan kedalaman)
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, backZ);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glBegin(GL_QUADS);
    // Sisi 1
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, backZ);

    // Sisi 2
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.6 + yBawah, backZ);

    // Sisi 3
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);
    glVertex3f(0.85 + xAtas, 0.90 + yBawah, backZ);

    // Sisi 4
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.6 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);

    // Sisi 5
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.90 + yBawah, backZ);

    // Sisi 6
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, backZ);
    glVertex3f(0.75 + xAtas, 0.72 + yBawah, backZ);

    // Sisi 7
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.78 + xAtas, 0.72 + yBawah, backZ);

    // Sisi 8
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, backZ);
    glVertex3f(0.78 + xAtas, 0.76 + yBawah, backZ);

    // Sisi 9
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.76 + yBawah, backZ);

    // Sisi 10
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, frontZ);
    glVertex3f(0.75 + xAtas, 0.71 + yBawah, backZ);
    glVertex3f(0.9 + xAtas, 0.71 + yBawah, backZ);

    glEnd();
}



void drawSix(float x, float y, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    glColor3f(1.0f, 0.5f, 0.0f);

    // Bagian depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.8f, y + 0.65f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glEnd();

    // Bagian belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.8f, y + 0.65f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.6f, backZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);
    glEnd();

    // Menghubungkan depan dan belakang untuk membuat sisi 3D
    glBegin(GL_QUADS);
    // Top face
    glNormal3f(0, 1, 0);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);

    // Top right edge
    glNormal3f(1, 0, 0);
    glVertex3f(x + 0.9f, y + 0.9f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, frontZ);
    glVertex3f(x + 0.9f, y + 0.85f, backZ);
    glVertex3f(x + 0.9f, y + 0.9f, backZ);

    // Top left edge
    glNormal3f(-1, 0, 0);
    glVertex3f(x + 0.75f, y + 0.9f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);
    glVertex3f(x + 0.75f, y + 0.9f, backZ);

    // Left face (full length)
    glNormal3f(-1, 0, 0);
    glVertex3f(x + 0.75f, y + 0.85f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.85f, backZ);

    // Left inner face
    glNormal3f(1, 0, 0);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, frontZ);
    glVertex3f(x + 0.8f, y + 0.9f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(x + 0.75f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);
    glVertex3f(x + 0.75f, y + 0.6f, backZ);

    // Bottom right extension
    glNormal3f(0, -1, 0);
    glVertex3f(x + 0.8f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);
    glVertex3f(x + 0.8f, y + 0.6f, backZ);

    // Right bottom edge
    glNormal3f(1, 0, 0);
    glVertex3f(x + 0.9f, y + 0.6f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);
    glVertex3f(x + 0.9f, y + 0.6f, backZ);

    // Right middle vertical
    glNormal3f(1, 0, 0);
    glVertex3f(x + 0.9f, y + 0.65f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.65f, backZ);

    // Inner right vertical
    glNormal3f(-1, 0, 0);
    glVertex3f(x + 0.85f, y + 0.6f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, frontZ);
    glVertex3f(x + 0.85f, y + 0.75f, backZ);
    glVertex3f(x + 0.85f, y + 0.6f, backZ);

    // Middle horizontal top edge
    glNormal3f(0, 1, 0);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);

    // Middle horizontal bottom edge
    glNormal3f(0, -1, 0);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);

    // Middle vertical right edge
    glNormal3f(1, 0, 0);
    glVertex3f(x + 0.9f, y + 0.7f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, frontZ);
    glVertex3f(x + 0.9f, y + 0.75f, backZ);
    glVertex3f(x + 0.9f, y + 0.7f, backZ);

    // Middle vertical left edge
    glNormal3f(-1, 0, 0);
    glVertex3f(x + 0.8f, y + 0.7f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, frontZ);
    glVertex3f(x + 0.8f, y + 0.75f, backZ);
    glVertex3f(x + 0.8f, y + 0.7f, backZ);

    glEnd();
}


void drawNine(float xAtas, float yBawah, float z, float depth) {
    float frontZ = z;
    float backZ = z + depth;

    glColor3f(1.0f, 0.5f, 0.0f);

    // Front faces
    // Bottom horizontal bar
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, frontZ);
    glEnd();

    // Middle horizontal bar
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.72f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.72f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, frontZ);
    glEnd();

    // Top horizontal bar
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, frontZ);
    glEnd();

    // Right vertical bar
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, frontZ);
    glEnd();

    // Top left corner
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, frontZ);
    glEnd();

    // Back faces (same as front but with backZ)
    // Bottom horizontal bar (back)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);
    glEnd();

    // Middle horizontal bar (back)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.72f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.72f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.78f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, backZ);
    glEnd();

    // Top horizontal bar (back)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);
    glEnd();

    // Right vertical bar (back)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, backZ);
    glEnd();

    // Top left corner (back)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);
    glEnd();

    // Connecting sides (3D edges)
    glBegin(GL_QUADS);
    // Bottom face
    glNormal3f(0, -1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.6f, backZ);

    // Bottom edge of right bar
    glNormal3f(0, -1, 0);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, backZ);

    // Right face (full height)
    glNormal3f(1, 0, 0);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.9f, yBawah + 0.6f, backZ);

    // Inner right face
    glNormal3f(-1, 0, 0);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.6f, backZ);

    // Top face
    glNormal3f(0, 1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);

    // Top left corner vertical
    glNormal3f(-1, 0, 0);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.85f, backZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, backZ);

    // Top left corner horizontal
    glNormal3f(0, 1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.75f, yBawah + 0.78f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, backZ);

    // Middle bar bottom edge
    glNormal3f(0, -1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.72f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.72f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.72f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.72f, backZ);

    // Middle bar top edge
    glNormal3f(0, 1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.78f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.78f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.78f, backZ);

    // Bottom bar top edge
    glNormal3f(0, 1, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, frontZ);
    glVertex3f(xAtas + 0.85f, yBawah + 0.65f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.65f, backZ);

    // Left edge of top bar
    glNormal3f(-1, 0, 0);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, frontZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.9f, backZ);
    glVertex3f(xAtas + 0.7f, yBawah + 0.85f, backZ);

    glEnd();
}

void drawObserver(float x, float y) {
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(x, y, 0.6f);
    glutSolidCone(0.1, 0.2, 50, 50);
    glPopMatrix();
}


void drawPlayer1 (float x , float y){
    glColor3f(1,0.5,0);
    glTranslatef(x,y,0.6f);
    glutSolidSphere(0.1,50,50);
    glTranslatef(-x,-y,-0.6f);
    glPopMatrix();
}

void drawPlayer2(float x, float y){
    glColor3f(1,0.5,1);
    glTranslatef(x,y,0.6f);
    glutSolidCube(0.2);
    glTranslatef(-x,-y,-0.6f);
    glPopMatrix();
}

void drawSquare3D(float x, float y, float z, bool isDark) {
    float depth = 0.02f;

    if (warna_transparan) {

        if (isDark) {
            glColor4f(0.0, 0.0, 1.0, 0.4);
        } else {
            glColor4f(1.0, 1.0, 1.0, 0.4);
        }
    } else {
        if (isDark) {
            glColor4f(0.0, 0.0, 1.0, 1.0);
        } else {
            glColor4f(1.0, 1.0, 1.0, 1.0);
        }
    }

    // Sisi depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);  // Normal ke arah Z positif
    glVertex3f(x, y, z);
    glVertex3f(x + 1, y, z);
    glVertex3f(x + 1, y + 1, z);
    glVertex3f(x, y + 1, z);
    glEnd();

    // Sisi belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);  // Normal ke arah Z negatif
    glVertex3f(x, y, z - depth);
    glVertex3f(x, y + 1, z - depth);
    glVertex3f(x + 1, y + 1, z - depth);
    glVertex3f(x + 1, y, z - depth);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);  // Normal ke arah X positif
    glVertex3f(x + 1, y, z);
    glVertex3f(x + 1, y, z - depth);
    glVertex3f(x + 1, y + 1, z - depth);
    glVertex3f(x + 1, y + 1, z);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);  // Normal ke arah X negatif
    glVertex3f(x, y, z);
    glVertex3f(x, y + 1, z);
    glVertex3f(x, y + 1, z - depth);
    glVertex3f(x, y, z - depth);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);  // Normal ke arah Y positif
    glVertex3f(x, y + 1, z);
    glVertex3f(x, y + 1, z - depth);
    glVertex3f(x + 1, y + 1, z - depth);
    glVertex3f(x + 1, y + 1, z);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);  // Normal ke arah Y negatif
    glVertex3f(x, y, z);
    glVertex3f(x + 1, y, z);
    glVertex3f(x + 1, y, z - depth);
    glVertex3f(x, y, z - depth);
    glEnd();

    // MENGGAMBAR TANGGA 3D
    glPushMatrix();
    glColor3f(0.56f, 0.435f, 0.0f); // Warna seperti pada tangga 2D

    for (float i = 0.4 + 0.4; i < 3.6; i += 0.4) {
        // Depan
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(2.2, i, 0.5);
        glVertex3f(3.2 - 0.4, i, 0.5);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.5);
        glVertex3f(2.2, i + 0.1, 0.5);
        glEnd();

        // Belakang
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(2.2, i, 0.3);
        glVertex3f(3.2 - 0.4, i, 0.3);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.3);
        glVertex3f(2.2, i + 0.1, 0.3);
        glEnd();

        // Kiri
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(2.2, i, 0.5);
        glVertex3f(2.2, i, 0.3);
        glVertex3f(2.2, i + 0.1, 0.3);
        glVertex3f(2.2, i + 0.1, 0.5);
        glEnd();

        // Kanan
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(3.2 - 0.4, i, 0.5);
        glVertex3f(3.2 - 0.4, i, 0.3);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.3);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.5);
        glEnd();

        // Atas
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(2.2, i + 0.1, 0.5);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.5);
        glVertex3f(3.2 - 0.4, i + 0.1, 0.3);
        glVertex3f(2.2, i + 0.1, 0.3);
        glEnd();

        // Bawah
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(2.2, i, 0.5);
        glVertex3f(3.2 - 0.4, i, 0.5);
        glVertex3f(3.2 - 0.4, i, 0.3);
        glVertex3f(2.2, i, 0.3);
        glEnd();
    }

    // Gagang kiri
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(2.2, 0.4, 0.5);
    glVertex3f(2.2 + 0.1, 0.4, 0.5);
    glVertex3f(2.2 + 0.1, 3.6, 0.5);
    glVertex3f(2.2, 3.6, 0.5);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(2.2, 0.4, 0.3);
    glVertex3f(2.2 + 0.1, 0.4, 0.3);
    glVertex3f(2.2 + 0.1, 3.6, 0.3);
    glVertex3f(2.2, 3.6, 0.3);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(2.2, 0.4, 0.5);
    glVertex3f(2.2, 0.4, 0.3);
    glVertex3f(2.2, 3.6, 0.3);
    glVertex3f(2.2, 3.6, 0.5);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(2.2 + 0.1, 0.4, 0.5);
    glVertex3f(2.2 + 0.1, 0.4, 0.3);
    glVertex3f(2.2 + 0.1, 3.6, 0.3);
    glVertex3f(2.2 + 0.1, 3.6, 0.5);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(2.2, 3.6, 0.5);
    glVertex3f(2.2 + 0.1, 3.6, 0.5);
    glVertex3f(2.2 + 0.1, 3.6, 0.3);
    glVertex3f(2.2, 3.6, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(2.2, 0.4, 0.5);
    glVertex3f(2.2 + 0.1, 0.4, 0.5);
    glVertex3f(2.2 + 0.1, 0.4, 0.3);
    glVertex3f(2.2, 0.4, 0.3);
    glEnd();

    // Gagang kanan
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(2.7, 0.4, 0.5);
    glVertex3f(2.8, 0.4, 0.5);
    glVertex3f(2.8, 3.6, 0.5);
    glVertex3f(2.7, 3.6, 0.5);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(2.7, 0.4, 0.3);
    glVertex3f(2.8, 0.4, 0.3);
    glVertex3f(2.8, 3.6, 0.3);
    glVertex3f(2.7, 3.6, 0.3);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(2.7, 0.4, 0.5);
    glVertex3f(2.7, 0.4, 0.3);
    glVertex3f(2.7, 3.6, 0.3);
    glVertex3f(2.7, 3.6, 0.5);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(2.8, 0.4, 0.5);
    glVertex3f(2.8, 0.4, 0.3);
    glVertex3f(2.8, 3.6, 0.3);
    glVertex3f(2.8, 3.6, 0.5);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(2.7, 3.6, 0.5);
    glVertex3f(2.8, 3.6, 0.5);
    glVertex3f(2.8, 3.6, 0.3);
    glVertex3f(2.7, 3.6, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(2.7, 0.4, 0.5);
    glVertex3f(2.8, 0.4, 0.5);
    glVertex3f(2.8, 0.4, 0.3);
    glVertex3f(2.7, 0.4, 0.3);
    glEnd();

    glPopMatrix();

    // MENGGAMBAR TANGGA 3D HORIZONTAL/MIRING
    glPushMatrix();
    glColor3f(0.56f, 0.435f, 0.0f); // Warna seperti pada tangga 2D

    // Langkah-langkah tangga
    for (float i = 0.7; i < 5.4; i += 0.4) {
        // Depan (sisi atas)
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(i, 5.7, 0.5);
        glVertex3f(i, 5.7 - 0.4, 0.5);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.5);
        glVertex3f(i + 0.1, 5.7, 0.5);
        glEnd();

        // Belakang (sisi bawah)
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(i, 5.7, 0.3);
        glVertex3f(i, 5.7 - 0.4, 0.3);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.3);
        glVertex3f(i + 0.1, 5.7, 0.3);
        glEnd();

        // Sisi kiri
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(i, 5.7, 0.5);
        glVertex3f(i, 5.7, 0.3);
        glVertex3f(i, 5.7 - 0.4, 0.3);
        glVertex3f(i, 5.7 - 0.4, 0.5);
        glEnd();

        // Sisi kanan
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(i + 0.1, 5.7, 0.5);
        glVertex3f(i + 0.1, 5.7, 0.3);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.3);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.5);
        glEnd();

        // Atas (permukaan langkah)
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(i, 5.7, 0.5);
        glVertex3f(i + 0.1, 5.7, 0.5);
        glVertex3f(i + 0.1, 5.7, 0.3);
        glVertex3f(i, 5.7, 0.3);
        glEnd();

        // Bawah (sisi bawah langkah)
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(i, 5.7 - 0.4, 0.5);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.5);
        glVertex3f(i + 0.1, 5.7 - 0.4, 0.3);
        glVertex3f(i, 5.7 - 0.4, 0.3);
        glEnd();
    }

    // Papan atas (handrail atas)
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(0.4, 5.7, 0.5);
    glVertex3f(5.4, 5.7, 0.5);
    glVertex3f(5.4, 5.7 + 0.1, 0.5);
    glVertex3f(0.4, 5.7 + 0.1, 0.5);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(0.4, 5.7, 0.3);
    glVertex3f(5.4, 5.7, 0.3);
    glVertex3f(5.4, 5.7 + 0.1, 0.3);
    glVertex3f(0.4, 5.7 + 0.1, 0.3);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(0.4, 5.7 + 0.1, 0.5);
    glVertex3f(5.4, 5.7 + 0.1, 0.5);
    glVertex3f(5.4, 5.7 + 0.1, 0.3);
    glVertex3f(0.4, 5.7 + 0.1, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0.4, 5.7, 0.5);
    glVertex3f(5.4, 5.7, 0.5);
    glVertex3f(5.4, 5.7, 0.3);
    glVertex3f(0.4, 5.7, 0.3);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0.4, 5.7, 0.5);
    glVertex3f(0.4, 5.7, 0.3);
    glVertex3f(0.4, 5.7 + 0.1, 0.3);
    glVertex3f(0.4, 5.7 + 0.1, 0.5);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(5.4, 5.7, 0.5);
    glVertex3f(5.4, 5.7, 0.3);
    glVertex3f(5.4, 5.7 + 0.1, 0.3);
    glVertex3f(5.4, 5.7 + 0.1, 0.5);
    glEnd();

    // Papan bawah (handrail bawah)
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(0.4, 5.7 - 0.5, 0.5);
    glVertex3f(5.4, 5.7 - 0.5, 0.5);
    glVertex3f(5.4, 5.7 - 0.4, 0.5);
    glVertex3f(0.4, 5.7 - 0.4, 0.5);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(0.4, 5.7 - 0.5, 0.3);
    glVertex3f(5.4, 5.7 - 0.5, 0.3);
    glVertex3f(5.4, 5.7 - 0.4, 0.3);
    glVertex3f(0.4, 5.7 - 0.4, 0.3);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(0.4, 5.7 - 0.4, 0.5);
    glVertex3f(5.4, 5.7 - 0.4, 0.5);
    glVertex3f(5.4, 5.7 - 0.4, 0.3);
    glVertex3f(0.4, 5.7 - 0.4, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0.4, 5.7 - 0.5, 0.5);
    glVertex3f(5.4, 5.7 - 0.5, 0.5);
    glVertex3f(5.4, 5.7 - 0.5, 0.3);
    glVertex3f(0.4, 5.7 - 0.5, 0.3);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0.4, 5.7 - 0.5, 0.5);
    glVertex3f(0.4, 5.7 - 0.5, 0.3);
    glVertex3f(0.4, 5.7 - 0.4, 0.3);
    glVertex3f(0.4, 5.7 - 0.4, 0.5);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(5.4, 5.7 - 0.5, 0.5);
    glVertex3f(5.4, 5.7 - 0.5, 0.3);
    glVertex3f(5.4, 5.7 - 0.4, 0.3);
    glVertex3f(5.4, 5.7 - 0.4, 0.5);
    glEnd();

    glPopMatrix();


    // MENGGAMBAR TANGGA 3D DIAGONAL
    glPushMatrix();
    glColor3f(0.56f, 0.435f, 0.0f); // Warna tangga yang sama dengan sebelumnya

    // Koordinat anak tangga untuk perulangan (5 langkah)
    float stepCoords[5][4][2] = {
        {{2.5f, 9.7f}, {2.9f, 9.4f}, {3.0f, 9.5f}, {2.6f, 9.8f}},  // Anak Tangga 1
        {{2.9f, 10.5f}, {3.3f, 10.2f}, {3.4f, 10.3f}, {3.0f, 10.6f}}, // Anak Tangga 2
        {{3.3f, 11.3f}, {3.7f, 11.0f}, {3.8f, 11.1f}, {3.4f, 11.4f}}, // Anak Tangga 3
        {{3.7f, 12.1f}, {4.1f, 11.8f}, {4.2f, 11.9f}, {3.8f, 12.2f}}, // Anak Tangga 4
        {{4.1f, 12.9f}, {4.5f, 12.6f}, {4.6f, 12.7f}, {4.2f, 13.0f}}, // Anak Tangga 5
    };

    // Ketebalan tangga dalam 3D
    float thickness = 0.2f;
    float frontZ = 0.5f;
    float backZ = frontZ - thickness;

    // Loop untuk menggambar anak tangga 3D
    for (int i = 0; i < 5; i++) {
        // Atas (permukaan tangga)
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], frontZ);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], frontZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], frontZ);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], frontZ);
        glEnd();

        // Bawah
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], backZ);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], backZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], backZ);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], backZ);
        glEnd();

        // Sisi depan (vertical face)
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], frontZ);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], backZ);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], backZ);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], frontZ);
        glEnd();

        // Sisi belakang (vertical face)
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], frontZ);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], backZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], backZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], frontZ);
        glEnd();

        // Sisi kiri (vertical face)
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], frontZ);
        glVertex3f(stepCoords[i][0][0], stepCoords[i][0][1], backZ);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], backZ);
        glVertex3f(stepCoords[i][1][0], stepCoords[i][1][1], frontZ);
        glEnd();

        // Sisi kanan (vertical face)
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], frontZ);
        glVertex3f(stepCoords[i][3][0], stepCoords[i][3][1], backZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], backZ);
        glVertex3f(stepCoords[i][2][0], stepCoords[i][2][1], frontZ);
        glEnd();
    }

    // Pegangan Kiri (Sesuai sudut diagonal)
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(2.4f, 9.5f, frontZ);
    glVertex3f(2.5f, 9.4f, frontZ);
    glVertex3f(4.5f, 13.4f, frontZ);
    glVertex3f(4.4f, 13.5f, frontZ);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(2.4f, 9.5f, backZ);
    glVertex3f(2.5f, 9.4f, backZ);
    glVertex3f(4.5f, 13.4f, backZ);
    glVertex3f(4.4f, 13.5f, backZ);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(2.5f, 9.4f, frontZ);
    glVertex3f(4.5f, 13.4f, frontZ);
    glVertex3f(4.5f, 13.4f, backZ);
    glVertex3f(2.5f, 9.4f, backZ);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(2.4f, 9.5f, frontZ);
    glVertex3f(4.4f, 13.5f, frontZ);
    glVertex3f(4.4f, 13.5f, backZ);
    glVertex3f(2.4f, 9.5f, backZ);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(2.4f, 9.5f, frontZ);
    glVertex3f(2.4f, 9.5f, backZ);
    glVertex3f(2.5f, 9.4f, backZ);
    glVertex3f(2.5f, 9.4f, frontZ);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(4.4f, 13.5f, frontZ);
    glVertex3f(4.4f, 13.5f, backZ);
    glVertex3f(4.5f, 13.4f, backZ);
    glVertex3f(4.5f, 13.4f, frontZ);
    glEnd();

    // Pegangan Kanan (Sesuai sudut diagonal)
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(2.8f, 9.2f, frontZ);
    glVertex3f(2.9f, 9.1f, frontZ);
    glVertex3f(4.9f, 13.1f, frontZ);
    glVertex3f(4.8f, 13.2f, frontZ);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(2.8f, 9.2f, backZ);
    glVertex3f(2.9f, 9.1f, backZ);
    glVertex3f(4.9f, 13.1f, backZ);
    glVertex3f(4.8f, 13.2f, backZ);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(2.9f, 9.1f, frontZ);
    glVertex3f(4.9f, 13.1f, frontZ);
    glVertex3f(4.9f, 13.1f, backZ);
    glVertex3f(2.9f, 9.1f, backZ);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(2.8f, 9.2f, frontZ);
    glVertex3f(4.8f, 13.2f, frontZ);
    glVertex3f(4.8f, 13.2f, backZ);
    glVertex3f(2.8f, 9.2f, backZ);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(2.8f, 9.2f, frontZ);
    glVertex3f(2.8f, 9.2f, backZ);
    glVertex3f(2.9f, 9.1f, backZ);
    glVertex3f(2.9f, 9.1f, frontZ);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(4.8f, 13.2f, frontZ);
    glVertex3f(4.8f, 13.2f, backZ);
    glVertex3f(4.9f, 13.1f, backZ);
    glVertex3f(4.9f, 13.1f, frontZ);
    glEnd();

    glPopMatrix();

    // MENGGAMBAR ULAR 3D
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Warna merah

    // Parameter 3D
    float thickness2 = 0.2f; // Ketebalan ular
    float frontZ2 = 0.5f;    // Posisi depan
    float backZ2 = frontZ2 - thickness2; // Posisi belakang

    // Bagian pertama ular
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(4.63, 4.5, frontZ2);
    glVertex3f(4.5, 4.5, frontZ2);
    glVertex3f(3.2, 3.0, frontZ2);
    glVertex3f(3.3, 3.0, frontZ2);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(4.63, 4.5, backZ2);
    glVertex3f(4.5, 4.5, backZ2);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(4.63, 4.5, frontZ2);
    glVertex3f(4.5, 4.5, frontZ2);
    glVertex3f(4.5, 4.5, backZ2);
    glVertex3f(4.63, 4.5, backZ2);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(3.3, 3.0, frontZ2);
    glVertex3f(3.2, 3.0, frontZ2);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(4.63, 4.5, frontZ2);
    glVertex3f(4.63, 4.5, backZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glVertex3f(3.3, 3.0, frontZ2);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(4.5, 4.5, frontZ2);
    glVertex3f(4.5, 4.5, backZ2);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(3.2, 3.0, frontZ2);
    glEnd();

    // Bagian kedua ular
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(3.2, 3.0, frontZ2);
    glVertex3f(3.3, 3.0, frontZ2);
    glVertex3f(5.0, 2.0, frontZ2);
    glVertex3f(4.9, 2.0, frontZ2);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(4.9, 2.0, backZ2);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(3.3, 3.0, frontZ2);
    glVertex3f(3.2, 3.0, frontZ2);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(4.9, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(4.9, 2.0, backZ2);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(3.3, 3.0, frontZ2);
    glVertex3f(3.3, 3.0, backZ2);
    glVertex3f(4.9, 2.0, backZ2);
    glVertex3f(4.9, 2.0, frontZ2);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(3.2, 3.0, frontZ2);
    glVertex3f(3.2, 3.0, backZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(5.0, 2.0, frontZ2);
    glEnd();

    // Bagian ketiga ular
    // Depan
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(4.9, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, frontZ2);
    glVertex3f(3.52, 0.5, frontZ2);
    glVertex3f(3.5, 0.5, frontZ2);
    glEnd();

    // Belakang
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(4.9, 2.0, backZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(3.52, 0.5, backZ2);
    glVertex3f(3.5, 0.5, backZ2);
    glEnd();

    // Sisi atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(4.9, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(4.9, 2.0, backZ2);
    glEnd();

    // Sisi bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(3.5, 0.5, frontZ2);
    glVertex3f(3.52, 0.5, frontZ2);
    glVertex3f(3.52, 0.5, backZ2);
    glVertex3f(3.5, 0.5, backZ2);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(4.9, 2.0, frontZ2);
    glVertex3f(4.9, 2.0, backZ2);
    glVertex3f(3.5, 0.5, backZ2);
    glVertex3f(3.5, 0.5, frontZ2);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(5.0, 2.0, frontZ2);
    glVertex3f(5.0, 2.0, backZ2);
    glVertex3f(3.52, 0.5, backZ2);
    glVertex3f(3.52, 0.5, frontZ2);
    glEnd();

    glPopMatrix();

    // MENGGAMBAR ULAR 3D

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Warna merah

    // Parameter 3D
    float thickness3 = 0.2f; // Ketebalan ular
    float frontZ3 = 0.5f;    // Posisi depan
    float backZ3 = frontZ3 - thickness3; // Posisi belakang

    // Bagian pertama ular (segment pertama)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(1.45, 9.49, frontZ3);
    glVertex3f(1.6, 9.5, frontZ3);
    glVertex3f(3.4, 8.3, frontZ3);
    glVertex3f(3.3, 8.3, frontZ3);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(1.45, 9.49, backZ3);
    glVertex3f(1.6, 9.5, backZ3);
    glVertex3f(3.4, 8.3, backZ3);
    glVertex3f(3.3, 8.3, backZ3);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(1.45, 9.49, frontZ3);
    glVertex3f(1.45, 9.49, backZ3);
    glVertex3f(3.3, 8.3, backZ3);
    glVertex3f(3.3, 8.3, frontZ3);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(1.6, 9.5, frontZ3);
    glVertex3f(1.6, 9.5, backZ3);
    glVertex3f(3.4, 8.3, backZ3);
    glVertex3f(3.4, 8.3, frontZ3);
    glEnd();

    // Bagian kedua ular (segment kedua)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(3.3, 8.3, frontZ3);
    glVertex3f(3.4, 8.3, frontZ3);
    glVertex3f(1.7, 7.5, frontZ3);
    glVertex3f(1.6, 7.5, frontZ3);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(3.3, 8.3, backZ3);
    glVertex3f(3.4, 8.3, backZ3);
    glVertex3f(1.7, 7.5, backZ3);
    glVertex3f(1.6, 7.5, backZ3);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(3.3, 8.3, frontZ3);
    glVertex3f(3.3, 8.3, backZ3);
    glVertex3f(1.6, 7.5, backZ3);
    glVertex3f(1.6, 7.5, frontZ3);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(3.4, 8.3, frontZ3);
    glVertex3f(3.4, 8.3, backZ3);
    glVertex3f(1.7, 7.5, backZ3);
    glVertex3f(1.7, 7.5, frontZ3);
    glEnd();

    // Bagian ketiga ular (segment ketiga)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(1.6, 7.5, frontZ3);
    glVertex3f(1.7, 7.5, frontZ3);
    glVertex3f(3.5, 6.33, frontZ3);
    glVertex3f(3.5, 6.3, frontZ3);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(1.6, 7.5, backZ3);
    glVertex3f(1.7, 7.5, backZ3);
    glVertex3f(3.5, 6.33, backZ3);
    glVertex3f(3.5, 6.3, backZ3);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(1.6, 7.5, frontZ3);
    glVertex3f(1.6, 7.5, backZ3);
    glVertex3f(3.5, 6.3, backZ3);
    glVertex3f(3.5, 6.3, frontZ3);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(1.7, 7.5, frontZ3);
    glVertex3f(1.7, 7.5, backZ3);
    glVertex3f(3.5, 6.33, backZ3);
    glVertex3f(3.5, 6.33, frontZ3);
    glEnd();

    glPopMatrix();


    // MENGGAMBAR ULAR 3D
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Warna merah

    // Parameter 3D
    float thickness4 = 0.3f; // Ketebalan ular
    float frontZ4 = 0.5f;    // Posisi depan
    float backZ4 = frontZ4 - thickness4; // Posisi belakang

    // Bagian pertama ular (segment pertama)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(1.48, 13.48, frontZ4);
    glVertex3f(1.6, 13.5, frontZ4);
    glVertex3f(2.2, 10.85, frontZ4);
    glVertex3f(2.1, 10.7, frontZ4);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(1.48, 13.48, backZ4);
    glVertex3f(1.6, 13.5, backZ4);
    glVertex3f(2.2, 10.85, backZ4);
    glVertex3f(2.1, 10.7, backZ4);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(1.48, 13.48, frontZ4);
    glVertex3f(1.48, 13.48, backZ4);
    glVertex3f(2.1, 10.7, backZ4);
    glVertex3f(2.1, 10.7, frontZ4);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(1.6, 13.5, frontZ4);
    glVertex3f(1.6, 13.5, backZ4);
    glVertex3f(2.2, 10.85, backZ4);
    glVertex3f(2.2, 10.85, frontZ4);
    glEnd();

    // Bagian kedua ular (segment kedua)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(2.2, 10.85, frontZ4);
    glVertex3f(2.1, 10.7, frontZ4);
    glVertex3f(4.3, 11.7, frontZ4);
    glVertex3f(4.3, 11.8, frontZ4);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(2.2, 10.85, backZ4);
    glVertex3f(2.1, 10.7, backZ4);
    glVertex3f(4.3, 11.7, backZ4);
    glVertex3f(4.3, 11.8, backZ4);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(2.2, 10.85, frontZ4);
    glVertex3f(2.2, 10.85, backZ4);
    glVertex3f(4.3, 11.8, backZ4);
    glVertex3f(4.3, 11.8, frontZ4);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(2.1, 10.7, frontZ4);
    glVertex3f(2.1, 10.7, backZ4);
    glVertex3f(4.3, 11.7, backZ4);
    glVertex3f(4.3, 11.7, frontZ4);
    glEnd();

    // Bagian ketiga ular (segment ketiga)
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(4.3, 11.7, frontZ4);
    glVertex3f(4.3, 11.8, frontZ4);
    glVertex3f(5.52, 9.5, frontZ4);
    glVertex3f(5.5, 9.5, frontZ4);
    glEnd();

    glBegin(GL_POLYGON);
    glNormal3f(0, 0, -1);
    glVertex3f(4.3, 11.7, backZ4);
    glVertex3f(4.3, 11.8, backZ4);
    glVertex3f(5.52, 9.5, backZ4);
    glVertex3f(5.5, 9.5, backZ4);
    glEnd();

    // Sisi kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(4.3, 11.7, frontZ4);
    glVertex3f(4.3, 11.7, backZ4);
    glVertex3f(5.5, 9.5, backZ4);
    glVertex3f(5.5, 9.5, frontZ4);
    glEnd();

    // Sisi kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(4.3, 11.8, frontZ4);
    glVertex3f(4.3, 11.8, backZ4);
    glVertex3f(5.52, 9.5, backZ4);
    glVertex3f(5.52, 9.5, frontZ4);
    glEnd();

    glPopMatrix();


    //PAGAR

    // ATAS (Top fence)
    glColor3f(0.52, 0.7, 0);
    glBegin(GL_POLYGON);
    // Depan
    glNormal3f(0, 0, -1);
    glVertex3f(0, rows-0.1, 0.3);  // Adjusted Z to 0.3 (more backward)
    glVertex3f(cols, rows-0.1, 0.3);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(0, rows, 0.3);
    glEnd();

    glBegin(GL_POLYGON);
    // Belakang
    glNormal3f(0, 0, 1);
    glVertex3f(0, rows-0.1, 0.0);  // Adjusted Z to 0.0
    glVertex3f(cols, rows-0.1, 0.0);
    glVertex3f(cols, rows, 0.0);
    glVertex3f(0, rows, 0.0);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, rows-0.1, 0.0);
    glVertex3f(0, rows-0.1, 0.3);
    glVertex3f(0, rows, 0.3);
    glVertex3f(0, rows, 0.0);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(cols, rows-0.1, 0.0);
    glVertex3f(cols, rows-0.1, 0.3);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(cols, rows, 0.0);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(0, rows, 0.0);
    glVertex3f(cols, rows, 0.0);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(0, rows, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0, rows-0.1, 0.0);
    glVertex3f(cols, rows-0.1, 0.0);
    glVertex3f(cols, rows-0.1, 0.3);
    glVertex3f(0, rows-0.1, 0.3);
    glEnd();

    // BAWAH (Bottom fence)
    glBegin(GL_POLYGON);
    // Depan
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0.3);  // Adjusted Z to 0.3
    glVertex3f(cols, 0, 0.3);
    glVertex3f(cols, 0.1, 0.3);
    glVertex3f(0, 0.1, 0.3);
    glEnd();

    glBegin(GL_POLYGON);
    // Belakang
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, 0.0);  // Adjusted Z to 0.0
    glVertex3f(cols, 0, 0.0);
    glVertex3f(cols, 0.1, 0.0);
    glVertex3f(0, 0.1, 0.0);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 0.3);
    glVertex3f(0, rows, 0.3);
    glVertex3f(0, rows, 0.0);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(cols, 0, 0.0);
    glVertex3f(cols, 0, 0.3);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(cols, rows, 0.0);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(0, rows, 0.0);
    glVertex3f(cols, rows, 0.0);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(0, rows, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(cols, 0, 0.0);
    glVertex3f(cols, 0, 0.3);
    glVertex3f(0, 0, 0.3);
    glEnd();

    // KIRI (Left fence)
    glBegin(GL_POLYGON);
    // Depan
    glNormal3f(0, 0, -1);
    glVertex3f(0, 0, 0.3);  // Adjusted Z to 0.3
    glVertex3f(0.1, 0, 0.3);
    glVertex3f(0.1, rows, 0.3);
    glVertex3f(0, rows, 0.3);
    glEnd();

    glBegin(GL_POLYGON);
    // Belakang
    glNormal3f(0, 0, 1);
    glVertex3f(0, 0, 0.0);  // Adjusted Z to 0.0
    glVertex3f(0.1, 0, 0.0);
    glVertex3f(0.1, rows, 0.0);
    glVertex3f(0, rows, 0.0);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 0.3);
    glVertex3f(0, rows, 0.3);
    glVertex3f(0, rows, 0.0);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(0.1, 0, 0.0);
    glVertex3f(0.1, 0, 0.3);
    glVertex3f(0.1, rows, 0.3);
    glVertex3f(0.1, rows, 0.0);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(0, rows, 0.0);
    glVertex3f(0.1, rows, 0.0);
    glVertex3f(0.1, rows, 0.3);
    glVertex3f(0, rows, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0.1, 0, 0.0);
    glVertex3f(0.1, 0, 0.3);
    glVertex3f(0, 0, 0.3);
    glEnd();

    // KANAN (Right fence)
    glBegin(GL_POLYGON);
    // Depan
    glNormal3f(0, 0, -1);
    glVertex3f(cols, 0, 0.3);  // Adjusted Z to 0.3
    glVertex3f(cols-0.1, 0, 0.3);
    glVertex3f(cols-0.1, rows, 0.3);
    glVertex3f(cols, rows, 0.3);
    glEnd();

    glBegin(GL_POLYGON);
    // Belakang
    glNormal3f(0, 0, 1);
    glVertex3f(cols, 0, 0.0);  // Adjusted Z to 0.0
    glVertex3f(cols-0.1, 0, 0.0);
    glVertex3f(cols-0.1, rows, 0.0);
    glVertex3f(cols, rows, 0.0);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glNormal3f(-1, 0, 0);
    glVertex3f(cols, 0, 0.0);
    glVertex3f(cols, 0, 0.3);
    glVertex3f(cols, rows, 0.3);
    glVertex3f(cols, rows, 0.0);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glNormal3f(1, 0, 0);
    glVertex3f(cols-0.1, 0, 0.0);
    glVertex3f(cols-0.1, 0, 0.3);
    glVertex3f(cols-0.1, rows, 0.3);
    glVertex3f(cols-0.1, rows, 0.0);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    glVertex3f(cols, rows, 0.0);
    glVertex3f(cols-0.1, rows, 0.0);
    glVertex3f(cols-0.1, rows, 0.3);
    glVertex3f(cols, rows, 0.3);
    glEnd();

    // Bawah
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glVertex3f(cols, 0, 0.0);
    glVertex3f(cols-0.1, 0, 0.0);
    glVertex3f(cols-0.1, 0, 0.3);
    glVertex3f(cols, 0, 0.3);
    glEnd();


    glColor3f(0.52, 0.7, 0);

    // Parameter dasar
    float tinggi = 0.1f;       // Tinggi semua pagar
    float zDepan = 0.3f;       // Posisi Z depan
    float zBelakang = 0.01f;    // Posisi Z belakang

    for (int i = 1; i <= 13; i++) {
        float yBawah = 0.9f + (i - 1) * 1.0f;  // Setiap pagar naik 1.0f

        // Tentukan dimensi X berdasarkan ganjil/genap
        float xAwal, xAkhir;
        if (i % 2 == 1) { // Ganjil (pagar pertama)
            xAwal = 0.0f;
            xAkhir = 5.0f;
        } else { // Genap (pagar kedua)
            xAwal = 1.0f;
            xAkhir = 6.0f;
        }

        // Gambar semua sisi pagar
        // Depan
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, 1);
        glVertex3f(xAwal, yBawah, zDepan);
        glVertex3f(xAkhir, yBawah, zDepan);
        glVertex3f(xAkhir, yBawah + tinggi, zDepan);
        glVertex3f(xAwal, yBawah + tinggi, zDepan);
        glEnd();

        // Belakang
        glBegin(GL_POLYGON);
        glNormal3f(0, 0, -1);
        glVertex3f(xAwal, yBawah, zBelakang);
        glVertex3f(xAkhir, yBawah, zBelakang);
        glVertex3f(xAkhir, yBawah + tinggi, zBelakang);
        glVertex3f(xAwal, yBawah + tinggi, zBelakang);
        glEnd();

        // Kiri
        glBegin(GL_POLYGON);
        glNormal3f(-1, 0, 0);
        glVertex3f(xAwal, yBawah, zBelakang);
        glVertex3f(xAwal, yBawah, zDepan);
        glVertex3f(xAwal, yBawah + tinggi, zDepan);
        glVertex3f(xAwal, yBawah + tinggi, zBelakang);
        glEnd();

        // Kanan
        glBegin(GL_POLYGON);
        glNormal3f(1, 0, 0);
        glVertex3f(xAkhir, yBawah, zBelakang);
        glVertex3f(xAkhir, yBawah, zDepan);
        glVertex3f(xAkhir, yBawah + tinggi, zDepan);
        glVertex3f(xAkhir, yBawah + tinggi, zBelakang);
        glEnd();

        // Atas
        glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);
        glVertex3f(xAwal, yBawah + tinggi, zBelakang);
        glVertex3f(xAkhir, yBawah + tinggi, zBelakang);
        glVertex3f(xAkhir, yBawah + tinggi, zDepan);
        glVertex3f(xAwal, yBawah + tinggi, zDepan);
        glEnd();

        // Bawah
        glBegin(GL_POLYGON);
        glNormal3f(0, -1, 0);
        glVertex3f(xAwal, yBawah, zBelakang);
        glVertex3f(xAkhir, yBawah, zBelakang);
        glVertex3f(xAkhir, yBawah, zDepan);
        glVertex3f(xAwal, yBawah, zDepan);
        glEnd();
    }


    // 1-10
    drawFour(3, 0, 0.01, 0.2);
    drawSix(5 - 0.05, 0, 0.01, 0.2);
    drawNine(3, 0.99, 0.01, 0.2);
    drawZero(2, 1, 0.01, 0.2);

    // 11-20
    drawFour(1, 2, 0.01, 0.2);
    drawSix(3, 1.99, 0.01, 0.2);
    drawNine(5 - 0.05, 2.99, 0.01, 0.2);
    drawZero(4, 3, 0.01, 0.2);

    // 21-30
    drawFour(0, 3, 0.01, 0.2);
    drawSix(1, 3.99, 0.01, 0.2);
    drawNine(4, 3.99, 0.01, 0.2);
    drawZero(5 - 0.05, 4, 0.01, 0.2);

    // 31-40
    drawFour(2, 5, 0.01, 0.2);
    drawSix(0, 4.99, 0.01, 0.2);
    drawNine(2, 5.99, 0.01, 0.2);
    drawZero(3, 6, 0.01, 0.2);
    drawFour(2.75, 6, 0.01, 0.2);

    // 41-50
    drawFour(4, 6, 0.01, 0.2);
    drawFour(5 - 0.05, 6, 0.01, 0.2);
    drawFour(5 - 0.05, 7, 0.01, 0.2);
    drawFour(4, 7, 0.01, 0.2);
    drawFour(3.8, 7, 0.01, 0.2);
    drawFour(3, 7, 0.01, 0.2);
    drawSix(2, 6.99, 0.01, 0.2);
    drawFour(1.8, 7, 0.01, 0.2);
    drawFour(1, 7, 0.01, 0.2);
    drawFour(0, 7, 0.01, 0.2);
    drawNine(0, 7.99, 0.01, 0.2);
    drawFour(-0.25, 8, 0.01, 0.2);
    drawZero(1, 8, 0.01, 0.2);

    // 51-60
    drawFour(5 - 0.05, 8, 0.01, 0.2);
    drawSix(4, 8.99, 0.01, 0.2);
    drawNine(1, 8.99, 0.01, 0.2);
    drawZero(0, 9, 0.01, 0.2);
    drawSix(-0.25, 8.99, 0.01, 0.2);

    // 61-70
    drawSix(0, 9.99, 0.01, 0.2);
    drawSix(1, 9.99, 0.01, 0.2);
    drawSix(2, 9.99, 0.01, 0.2);


    drawFour(3, 10, 0.01, 0.2);

    drawSix(2.8, 9.99, 0.01, 0.2);


    drawSix(4, 9.99, 0.01, 0.2);
    drawSix(5 - 0.05, 9.99, 0.01, 0.2);
    drawSix(4.8 - 0.05, 9.99, 0.01, 0.2);
    drawSix(5 - 0.05, 10.99, 0.01, 0.2);
    drawSix(4, 10.99, 0.01, 0.2);
    drawNine(3, 10.99, 0.01, 0.2);
    drawSix(2.75, 10.99, 0.01, 0.2);
    drawZero(2, 11, 0.01, 0.2);

    // 71-84
    drawFour(1, 12, 0.01, 0.2);
    drawSix(3, 11.99, 0.01, 0.2);
    drawNine(5 - 0.05, 12.99, 0.01, 0.2);
    drawZero(4, 13, 0.01, 0.2);
    drawFour(0, 13, 0.01, 0.2);


    drawObserver(geser_oberver_X, geser_oberver_Y);

    drawPlayer1(bidak_player1_X, bidak_player1_Y);
    drawPlayer2(bidak_player2_X, bidak_player2_Y);
}


void drawBoard() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (viewMode == 1) {
        // Default atau rotasi tampilan
        glTranslatef(pusat_rotasi_X, pusat_rotasi_Y, pusat_rotasi_Z);
        glRotatef(sudut_rotasi_X, 1.0f, 0.0f, 0.0f);
        glRotatef(sudut_rotasi_Y, 0.0f, 1.0f, 0.0f);
        glRotatef(sudut_rotasi_Z, 0.0f, 0.0f, 1.0f);
        glTranslatef(-pusat_rotasi_X, -pusat_rotasi_Y, -pusat_rotasi_Z);
    }
    glPointSize(4);

    bool isblue = false;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            drawSquare3D(j,i,0,isblue);
            isblue = !isblue;
        }
        isblue = !isblue;
    }

//    GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
//    GLfloat mat_shininess[] = { 10.0 };
//    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    GLfloat mat_specular_1[] = { 0.7, 0.1, 0.1, 1.0 };
//    GLfloat mat_shininess_1[] = { 10.0 };
//    GLfloat mat_diffuse_1[] = { 0.7, 0.1, 0.1, 1.0 };
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_1);
//    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_1);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_1);

    glutSwapBuffers();
    glFlush();
}


void myinit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Setup pencahayaan dan material
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat light_position_diff[] = { -1.0, 1.0, 1.0, 0.0 };
    GLfloat diffuse_light[] = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat light_position_spec[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat specular_light[] = { 0.0, 1.0, 0.0, 1.0 };
    GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Posisi awal objek
    pos[0] = 0.0;
    pos[1] = 0.0;
    pos[2] = 0.0;
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float boardWidth = 6.0f;
    float boardHeight = 14.0f;

    float aspect = (float)w / (float)h;

    if (aspect > (boardWidth / boardHeight)) {
        float newWidth = boardHeight * aspect;
        glOrtho(-(newWidth - boardWidth)/2, newWidth - (newWidth - boardWidth)/2,
                -1.0f, boardHeight + 1.0f,
                -15.0f, 30.0f);
    } else {
        float newHeight = boardWidth / aspect;
        glOrtho(-1.0f, boardWidth + 1.0f,
                -(newHeight - boardHeight)/2, newHeight - (newHeight - boardHeight)/2,
                -15.0f, 30.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-boardWidth/2, -boardHeight/2, 0.0f);
}




void input(unsigned char key, int x, int y) {
    key = tolower(key); //Agar bisa menginput keyboard huruf besar dan kecil


    if (viewMode == 1) { // Percabangan untuk rotasi papan permainan
        switch (key) {
            case 'i': // Putar Atas
                sudut_rotasi_X -= 2.0f;
                break;
            case 'k': // Putar Bawah
                sudut_rotasi_X += 2.0f;
                break;
            case 'j': // Putar Kiri
                sudut_rotasi_Y -= 2.0f;
                break;
            case 'l': // Putar Kanan
                sudut_rotasi_Y += 2.0f;
                break;

        }
    }


    switch (key) {
        case 'v':
        // Mengatur mode tampilan
        viewMode = (viewMode + 1) % 2;

        if (viewMode == 1) {
            // Mengubah mode ke rotasi papan tanpa mereset rotasi
            if (!rotasi_awal_dilakukan) {
                sudut_rotasi_X = -20.0f;
                rotasi_awal_dilakukan = true;
            } else {
                sudut_rotasi_X = sudut_rotasi_terakhir_x;
                sudut_rotasi_Y = sudut_rotasi_terakhir_Y;
                sudut_rotasi_Z = sudut_rotasi_terakhir_Z;
            }
            isRotated = true;
            warna_transparan = true; // Mengaktifkan transparansi 0.5

        } else {
            if (isRotated) {
                sudut_rotasi_terakhir_x = sudut_rotasi_X;
                sudut_rotasi_terakhir_Y = sudut_rotasi_Y;
                sudut_rotasi_terakhir_Z = sudut_rotasi_Z;
            }
            isRotated = false;
            // Reset rotasi
            sudut_rotasi_X = 0.0f;
            sudut_rotasi_Y = 0.0f;
            sudut_rotasi_Z = 0.0f;
            // Nonaktifkan warna transparan jika perlu
            warna_transparan = false;
        }


        break;


        case 'w':
            if (geser_oberver_Y + 0.2 <= batas_observer_atas)
                geser_oberver_Y += 0.2; // Pergeseran ke atas
            break;
        case 'a':
            if (geser_oberver_X - 0.2 >= batas_observer_kiri)
                geser_oberver_X -= 0.2; // Pergeseran ke kiri
            break;
        case 's':
            if (geser_oberver_Y - 0.2 >= batas_observer_bawah)
                geser_oberver_Y -= 0.2; // Pergeseran ke bawah
            break;
        case 'd':
            if (geser_oberver_X + 0.2 <= batas_observer_kanan)
                geser_oberver_X += 0.2; // Pergeseran ke kanan
            break;
        case 27:
            exit(0);
    }
    glutPostRedisplay();


    if (key == 32) {
        if (pemenang == 1) {
            cout << "Player 1 Menang" << endl;
        } else if (pemenang == 2) {
            cout << "Player 2 Menang" << endl;
        } else {
            if (giliran_player1) {
                int rand_player1 = rollDice();
                cout << "Player1 Mendapatkan : " << rand_player1 << " Nilai Dadu" << endl;
                jumlahlemparan += rand_player1;
                cout << "Letak Player 1 : " << jumlahlemparan << endl;
                cout << "===========================================================" << endl;


                if (jumlahlemparan <= 6) {  // Gerakan ke kanan (1-6)
                    // Cek apakah akan mendarat di kotak 3
                    if (jumlahlemparan == 3) {  // Jika posisi di kotak 3
                        jumlahlemparan = 22;  // Langsung pindah ke kotak 22
                        cout << "Player 1 melompat ke kotak 22!" << endl;
                        // Posisikan Player 1 pada koordinat kotak 22
                        bidak_player1_X = 6.5 - (jumlahlemparan - 18);  // Kolom 22, tengah kotak
                        bidak_player1_Y = 3.5 + 0.2;  // Baris yang sesuai untuk kotak 22
                    }
                    else {
                        // Gerakan normal ke kanan
                        bidak_player1_X = (jumlahlemparan - 1) + 0.5;  // Posisikan di tengah kotak
                        bidak_player1_Y = 0.5 + 0.2;  // Menambahkan offset ke atas
                    }
                }
                else if (jumlahlemparan <= 12) {  // Naik pada kolom 6 (7-12)
                    bidak_player1_X = 6.5 - (jumlahlemparan - 6);  // Geser ke kiri
                    bidak_player1_Y = 1.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 18) {  // Gerakan ke kanan (13-18)
                    bidak_player1_X = (jumlahlemparan - 13) + 0.5;  // Posisikan di tengah kotak
                    bidak_player1_Y = 2.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 24) {  // Naik pada kolom 1 (19-24)
                    bidak_player1_X = 6.5 - (jumlahlemparan - 18);  // Geser ke kiri dari kolom 6 ke kolom 1
                    bidak_player1_Y = 3.5 + 0.2;  // Tetap di baris ke-4
                }
                else if (jumlahlemparan <= 30) {  // Gerakan ke kanan (25-30)
                    // Cek apakah akan mendarat di kotak 29
                    if (jumlahlemparan == 29) {
                        jumlahlemparan = 4;  // Langsung pindah ke kotak 4
                        cout << "Player 1 turun ke kotak 4!" << endl;
                        // Gerakan normal ke kanan
                        bidak_player1_X = (jumlahlemparan - 1) + 0.5;  // Posisikan di tengah kotak
                        bidak_player1_Y = 0.5 + 0.2;  // Menambahkan offset ke atas
                    } else {
                        // Gerakan normal ke kanan untuk kotak 25-28 dan 30
                        bidak_player1_X = (jumlahlemparan - 25) + 0.5;  // Posisikan di tengah kotak
                        bidak_player1_Y = 4.5 + 0.2;  // Menambahkan offset ke atas
                    }
                }
                else if (jumlahlemparan <= 36) {  // Naik pada kolom 6 (31-36)
                    // Cek jika mendarat di kotak 31
                    if (jumlahlemparan == 31) {
                        jumlahlemparan = 36;  // Langsung pindah ke kotak 36
                        cout << "Player 1 melompat ke kotak 36!" << endl;
                        // Posisikan di kotak 36
                        bidak_player1_X = 6.5 - (jumlahlemparan - 30);  // 6.5 - 6 = 0.5 (paling kiri kolom 6)
                        bidak_player1_Y = 5.5 + 0.2;  // Baris paling atas dengan offset atas
                    }
                    else {
                        // Gerakan normal
                        bidak_player1_X = 6.5 - (jumlahlemparan - 30);  // Geser ke kiri
                        bidak_player1_Y = 5.5 + 0.2;  // Menambahkan offset ke atas
                    }
                }
                else if (jumlahlemparan <= 42) {  // Gerakan ke kanan (25-30)
                    bidak_player1_X = (jumlahlemparan - 37) + 0.5;  // Posisikan di tengah kotak
                    bidak_player1_Y = 6.5 + 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan <= 48) {  // Naik pada kolom 6 (31-36)
                    bidak_player1_X = 6.5 - (jumlahlemparan - 42);  // Geser ke kiri
                    bidak_player1_Y = 7.5 + 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan <= 54) {  // Gerakan ke kanan (49-54)
                    bidak_player1_X = (jumlahlemparan - 49) + 0.5;  // Posisikan di tengah kotak
                    bidak_player1_Y = 8.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 60) {  // Naik pada kolom 6 (55-60)
                    // Cek jika mendarat di kotak 58
                    if (jumlahlemparan == 58) {
                        jumlahlemparan = 80;  // Langsung pindah ke kotak 80
                        cout << "Player 1 melompat ke kotak 80!" << endl;
                        // Posisikan di kotak 80 (perlu menyesuaikan rumus koordinat untuk kotak 80)
                        bidak_player1_X = 6.5 - (jumlahlemparan - 78);  // Geser ke kiri
                        bidak_player1_Y = 13.5 + 0.2;  // Menambahkan offset ke atas
                    }
                    // Cek jika mendarat di kotak 59
                    else if (jumlahlemparan == 59) {
                        jumlahlemparan = 40;  // Langsung pindah ke kotak 40
                        cout << "Player 1 turun ke kotak 40!" << endl;
                        // Posisikan di kotak 40 (perlu menyesuaikan rumus koordinat untuk kotak 40)
                        bidak_player1_X = (jumlahlemparan - 37) + 0.5;
                        bidak_player1_Y = 6.5 + 0.2;  // Menambahkan offset ke bawah
                    }
                    else {
                        // Gerakan normal untuk 55-57, 59-60
                        bidak_player1_X = 6.5 - (jumlahlemparan - 54);  // Geser ke kiri
                        bidak_player1_Y = 9.5 + 0.2;  // Menambahkan offset ke atas
                    }
                }
                else if (jumlahlemparan <= 66) {  // Gerakan ke kanan (61-66)
                    bidak_player1_X = (jumlahlemparan - 61) + 0.5;  // Posisikan di tengah kotak
                    bidak_player1_Y = 10.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 72) {  // Naik pada kolom 6 (67-72)
                    bidak_player1_X = 6.5 - (jumlahlemparan - 66);  // Geser ke kiri
                    bidak_player1_Y = 11.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 78) {  // Gerakan ke kanan (73-78)
                    bidak_player1_X = (jumlahlemparan - 73) + 0.5;  // Posisikan di tengah kotak
                    bidak_player1_Y = 12.5 + 0.2;  // Menambahkan offset ke atas
                }
                else if (jumlahlemparan <= 83) {  // Naik pada kolom 6 (79-83)
                    // Cek jika mendarat di kotak 83
                    if (jumlahlemparan == 83) {
                        jumlahlemparan = 55;  // Langsung pindah ke kotak 55
                        cout << "Player 1 turun ke kotak 55!" << endl;
                        // Posisikan di kotak 55
                        bidak_player1_X = 6.5 - (jumlahlemparan - 54);  // Geser ke kiri
                        bidak_player1_Y = 9.5 + 0.2;  // Menambahkan offset ke atas
                    } else {
                        // Gerakan normal untuk 79-82
                        bidak_player1_X = 6.5 - (jumlahlemparan - 78);  // Geser ke kiri
                        bidak_player1_Y = 13.5 + 0.2;  // Menambahkan offset ke bawah
                    }
                }

                else if (jumlahlemparan == 84) {  // Naik pada kolom 6 (79-84)
                    bidak_player1_X = 0.5;
                    bidak_player1_Y = 13.5 + 0.2;  // Posisi di kotak 84
                    pemenang = 1;  // Menentukan Player 1 menang
                    cout << "Player 1 Menang!" << endl;  // Menyatakan kemenangan
                }
                else {  // Jika jumlahlemparan lebih dari 84, posisikan di kotak 84 dan Player 1 menang
                    bidak_player1_X = 0.5;
                    bidak_player1_Y = 13.5 + 0.2;  // Posisi di kotak 84
                    pemenang = 1;  // Menentukan Player 1 menang
                    cout << "Player 1 Menang!" << endl;  // Menyatakan kemenangan
                }
                // Setelah update posisi, giliran berakhir
                giliran_player1 = false;  // Mengubah giliran ke Player 2
            }
            else {
                int rand_player2 = rollDice();
                cout << "Player 2 mendapatkan : " << rand_player2 << " Nilai Dadu" << endl;
                jumlahlemparan2 += rand_player2;
                cout << "Letak Player 2 : " << jumlahlemparan2 << endl;
                cout << "===========================================================" << endl;

                // Tentukan posisi berdasarkan jumlah lemparan Player 2
                if (jumlahlemparan2 <= 6) {  // Gerakan ke kanan (1-6)
                    // Cek apakah akan mendarat di kotak 3
                    if (jumlahlemparan2 == 3) {  // Jika posisi di kotak 3
                        jumlahlemparan2 = 22;  // Langsung pindah ke kotak 22
                        cout << "Player 2 naik ke kotak 22!" << endl;
                        // Posisikan Player 2 pada koordinat kotak 22
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 18);  // Kolom 22, tengah kotak
                        bidak_player2_Y = 3.5 - 0.2;  // Baris yang sesuai untuk kotak 22 (dengan offset bawah)
                    }
                    else {
                        // Gerakan normal ke kanan
                        bidak_player2_X = (jumlahlemparan2 - 1) + 0.5;  // Posisikan di tengah kotak
                        bidak_player2_Y = 0.5 - 0.2;  // Menambahkan offset ke bawah
                    }
                }
                else if (jumlahlemparan2 <= 12) {  // Naik pada kolom 6 (7-12)
                    bidak_player2_X = 6.5 - (jumlahlemparan2 - 6);  // Geser ke kiri
                    bidak_player2_Y = 1.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 18) {  // Gerakan ke kanan (13-18)
                    bidak_player2_X = (jumlahlemparan2 - 13) + 0.5;  // Posisikan di tengah kotak
                    bidak_player2_Y = 2.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 24) {  // Naik pada kolom 1 (19-24)
                    bidak_player2_X = 6.5 - (jumlahlemparan2 - 18);  // Geser ke kiri dari kolom 6
                    bidak_player2_Y = 3.5 - 0.2;  // Tetap di baris ke 4
                }

                else if (jumlahlemparan2 <= 30) {  // Gerakan ke kanan (25-30)
                    // Cek apakah akan mendarat di kotak 29
                    if (jumlahlemparan2 == 29) {
                        jumlahlemparan2 = 4;  // Langsung pindah ke kotak 4
                        cout << "Player 2 turun ke kotak 4!" << endl;
                        // Gerakan normal ke kanan untuk kotak 4
                        bidak_player2_X = (jumlahlemparan2 - 1) + 0.5;  // Posisikan di tengah kotak
                        bidak_player2_Y = 0.5 - 0.2;  // Menambahkan offset ke atas untuk Player 2
                    } else {
                        // Gerakan normal ke kanan untuk kotak 25-28 dan 30
                        bidak_player2_X = (jumlahlemparan2 - 25) + 0.5;  // Posisikan di tengah kotak
                        bidak_player2_Y = 4.5 - 0.2;  // Menambahkan offset ke atas untuk Player 2
                    }
                }

                else if (jumlahlemparan2 <= 36) {  // Naik pada kolom 6 (31-36)
                    // Cek jika mendarat di kotak 31
                    if (jumlahlemparan2 == 31) {
                        jumlahlemparan2 = 36;  // Langsung pindah ke kotak 36
                        cout << "Player 2 melompat ke kotak 36!" << endl;
                        // Posisikan di kotak 36
                        bidak_player2_X = 6.5 - (36 - 30);  // 6.5 - 6 = 0.5 (paling kiri kolom 6)
                        bidak_player2_Y = 5.5 - 0.2;  // Baris paling atas
                    }
                    else {
                        // Gerakan normal
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 30);  // Geser ke kiri
                        bidak_player2_Y = 5.5 - 0.2;  // Menambahkan offset ke bawah
                    }
                }
                else if (jumlahlemparan2 <= 42) {  // Gerakan ke kanan (25-30)
                    bidak_player2_X = (jumlahlemparan2 - 37) + 0.5;  // Posisikan di tengah kotak
                    bidak_player2_Y = 6.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 48) {  // Naik pada kolom 6 (31-36)
                    bidak_player2_X = 6.5 - (jumlahlemparan2 - 42);  // Geser ke kiri
                    bidak_player2_Y = 7.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 54) {  // Gerakan ke kanan (49-54)
                    bidak_player2_X = (jumlahlemparan2 - 49) + 0.5;  // Posisikan di tengah kotak
                    bidak_player2_Y = 8.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 60) {  // Naik pada kolom 6 (55-60)
                    if (jumlahlemparan2 == 58) {
                        jumlahlemparan2 = 80;  // Langsung pindah ke kotak 80
                        cout << "Player 2 naik cepat ke kotak 80!" << endl;
                        // Posisikan di kotak 80 (perlu menyesuaikan rumus koordinat untuk kotak 80)
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 78);  // Geser ke kiri
                        bidak_player2_Y = 13.5 - 0.2;  // Menambahkan offset ke atas
                    }
                    // Cek jika mendarat di kotak 59
                    else if (jumlahlemparan2 == 59) {
                        jumlahlemparan2 = 40;  // Langsung pindah ke kotak 40
                        cout << "Player 2 turun ke kotak 40!" << endl;
                        // Posisikan di kotak 40 (perlu menyesuaikan rumus koordinat untuk kotak 40)
                        bidak_player2_X = (jumlahlemparan2 - 37) + 0.5;  // Geser ke kiri
                        bidak_player2_Y = 6.5 - 0.2;  // Menambahkan offset ke bawah
                    }else {
                        // Gerakan normal untuk 55-57, 59-60
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 54);  // Geser ke kiri
                        bidak_player2_Y = 9.5 - 0.2;  // Menambahkan offset ke atas
                    }
                }
                else if (jumlahlemparan2 <= 66) {  // Gerakan ke kanan (61-66)
                    bidak_player2_X = (jumlahlemparan2 - 61) + 0.5;  // Posisikan di tengah kotak
                    bidak_player2_Y = 10.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 72) {  // Naik pada kolom 6 (67-72)
                    bidak_player2_X = 6.5 - (jumlahlemparan2 - 66);  // Geser ke kiri
                    bidak_player2_Y = 11.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 78) {  // Gerakan ke kanan (73-78)
                    bidak_player2_X = (jumlahlemparan2 - 73) + 0.5;  // Posisikan di tengah kotak
                    bidak_player2_Y = 12.5 - 0.2;  // Menambahkan offset ke bawah
                }
                else if (jumlahlemparan2 <= 83) {  // Naik pada kolom 6 (79-83)
                    // Cek jika mendarat di kotak 83
                    if (jumlahlemparan2 == 83) {
                        jumlahlemparan2 = 55;  // Langsung pindah ke kotak 55
                        cout << "Player 2 turun ke kotak 55!" << endl;
                        // Posisikan di kotak 55
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 54);  // Geser ke kiri
                        bidak_player2_Y = 9.5 - 0.2;  // Menambahkan offset ke atas
                    } else {
                        // Gerakan normal untuk 79-82
                        bidak_player2_X = 6.5 - (jumlahlemparan2 - 78);  // Geser ke kiri
                        bidak_player2_Y = 13.5 - 0.2;  // Menambahkan offset ke bawah
                    }
                }
                else if (jumlahlemparan2 == 84) {  // Naik pada kolom 6 (79-84)
                    bidak_player2_X = 0.5;
                    bidak_player2_Y = 13.5 - 0.2;  // Posisi di kotak 84
                    pemenang = 2;  // Menentukan Player 2 menang
                    cout << "Player 2 Menang!" << endl;  // Menyatakan kemenangan
                }
                else {  // Jika jumlahlemparan2 lebih dari 84, posisikan di kotak 84 dan Player 2 menang
                    bidak_player2_X = 0.5;
                    bidak_player2_Y = 13.5 - 0.2;  // Posisi di kotak 84
                    pemenang = 2;  // Menentukan Player 2 menang
                    cout << "Player 2 Menang!" << endl;  // Menyatakan kemenangan
                }

                giliran_player1 = true;
            }
        }
    }


}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ular Tangga 3D");
    glutDisplayFunc(drawBoard);
    glutKeyboardFunc(input);
    glutReshapeFunc(reshape);
    myinit();



    glClearColor(0, 0, 0, 0);
    glutMainLoop();
    return 0;
}
