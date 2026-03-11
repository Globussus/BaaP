#include <window.h>
#include <canvas.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

Window::Window() {
    Canvas *canvas = new Canvas();
    canvas->setMinimumSize(800, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QHBoxLayout *graphicsLayout = new QHBoxLayout();

    QPushButton *addButton = new QPushButton("Нарисовать новую повозку", this);
    QPushButton *moveButton = new QPushButton("Переместить выбранную повозку горизонтально", this);
    QPushButton *jumpButton = new QPushButton("Переместить выбранную повозку вертикально", this);
    QPushButton *deleteButton = new QPushButton("Удалить выбранную повозку", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(moveButton);
    buttonLayout->addWidget(jumpButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(graphicsLayout);
    graphicsLayout->addWidget(canvas);

    connect(addButton, &QPushButton::clicked, [canvas]() {
       canvas->addCart();
    });
    connect(moveButton, &QPushButton::clicked, [canvas]() {
        canvas->moveSelected();
    });
    connect(jumpButton, &QPushButton::clicked, [canvas]() {
        canvas->jumpSelected();
    });
    connect(deleteButton, &QPushButton::clicked, [canvas]() {
       canvas->removeSelected();
    });
}
