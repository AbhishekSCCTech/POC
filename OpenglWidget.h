#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector3D>
#include <QMouseEvent>
#include <vector>
#include <QOpenGLVertexArrayObject>
using namespace std;

class OpenGlWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    enum DrawStyle
    {
        LINES = 0,
        TRIANGLES = 1
    };
    struct Data
    {
        QVector<GLfloat> vertices;
        QVector<GLfloat> normals;
        QVector<GLfloat> colors;
        DrawStyle drawStyle;
    };

private:
    struct DrawingObject
    {
        QOpenGLVertexArrayObject* vao;
        QOpenGLBuffer vbo;
        size_t numVertices;
        DrawStyle drawStyle;
    };

public:
    explicit OpenGlWidget(QWidget* parent = nullptr);
    ~OpenGlWidget() override;

    int addObject(Data inData);
    void removeObject(int index);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void sync(float zoomLevel, QVector3D rotation, QVector2D panOffset);

signals:
        void viewChange(float zoomLevel, QVector3D rotation, QVector2D panOffset);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool loadShaders();
    void updateModelViewMatrix();
    int buildDrawingObjects(Data data);

    QOpenGLShaderProgram shadedShader;
    QOpenGLShaderProgram wireShader;

    QMatrix4x4 projection;
    QMatrix4x4 modelView;

    float zoomLevel = 1.0f;
    QVector3D rotation = QVector3D(0.0f, 0.0f, 0.0f);
    QVector2D panOffset = QVector2D(0.0f, 0.0f);

    QPoint lastMousePosition;

    QVector<DrawingObject> drawingObjects;
    QMap<int, int> idToIndex;
    bool isInitialized;

};
