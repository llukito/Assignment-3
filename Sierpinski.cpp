/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

//constants
const int WIDTH_OF_WINDOW = 800;
const int HEIGHT_OF_WINDOW = 600;

//function prototypes
double getValidEdgeLength();
int getValidFractalOrder();
void drawTriangle(GWindow& window, double edgeLength, int fractalOrder);
void drawStartingTriangle(GWindow& window, double edgeLength, int x, int y);
void drawSierpinskiTriangle(double edgeLength, int fractalOrder, int x, int y, GWindow& window);

int main() {
    double edgeLength = getValidEdgeLength();
    int fractalOrder = getValidFractalOrder();
    GWindow window(WIDTH_OF_WINDOW, HEIGHT_OF_WINDOW); // create window
    drawTriangle(window, edgeLength, fractalOrder);
    return 0;
}

double getValidEdgeLength() {
    while (true) {
        double length = getReal("Enter length of edge: ");
        if (length > 0) {
            return length;
        }
        cout << "Edge of triangle should be positive" << endl;
    }
}

int getValidFractalOrder() {
    while (true) {
        int order = getInteger("Enter fractal order: ");
        if (order >= 0) {
            return order;
        }
        cout << "Fractal order should not be negative" << endl;
    }
}

void drawTriangle(GWindow& window, double edgeLength, int fractalOrder) {
    // initialize variables 
    double heightOfTriangle = edgeLength * sqrt(3) / 2;
    double x = window.getWidth() / 2;
    double y = (window.getHeight() - heightOfTriangle) / 2;

    drawStartingTriangle(window, edgeLength, x, y);
    drawSierpinskiTriangle(edgeLength/2, fractalOrder, x, y, window);
}

void drawStartingTriangle(GWindow& window, double edgeLength, int x, int y) {
    window.drawPolarLine(x, y, edgeLength, 300);
    GPoint point = window.drawPolarLine(x, y, edgeLength, 240);
    window.drawPolarLine(point.getX(), point.getY(), edgeLength, 0);
}

/*
* Here our base case is not written seperately, cause is is better for
* readability to see that we draw triangles until fractalOrder becomes zero
*/
void drawSierpinskiTriangle(double edgeLength, int fractalOrder, int x, int y, GWindow& window) {
    if (fractalOrder != 0) { 
        int heightOfPrev = edgeLength * sqrt(3); // heigh of previous (big) triangle
        // draw current one
        window.drawPolarLine(x, y + heightOfPrev, edgeLength, 120);
        GPoint point = window.drawPolarLine(x, y + heightOfPrev, edgeLength, 60);
        window.drawPolarLine(point.getX(), point.getY(), edgeLength, 180);
        // recursively do the same in three newly created triangles
        drawSierpinskiTriangle(edgeLength / 2, fractalOrder - 1, x, y, window);
        drawSierpinskiTriangle(edgeLength / 2, fractalOrder - 1, x - edgeLength / 2, y + heightOfPrev/2, window);
        drawSierpinskiTriangle(edgeLength / 2, fractalOrder - 1, x + edgeLength / 2, y + heightOfPrev/2, window);
    }
}
