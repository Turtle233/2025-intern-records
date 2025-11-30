#ifndef I_BORDER_WINDOW_H
#define I_BORDER_WINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QRect>
#include <QCursor>

#include "i_border_widget.h"
#include "i_title_widget.h"

class i_border_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit i_border_window(QWidget *parent = nullptr);
    ~i_border_window();

protected slots:
    void on_title_move(int x, int y);
    void on_title_min();
    void on_title_max();
    void on_title_ext();

protected:
    // Widgets
    i_title_widget *title_widget_ = nullptr;
    QWidget *center_widget_ = nullptr;

    // Border Widgets
    i_border_widget *top_left_border_ = new i_border_widget(-1, -1);
    i_border_widget *top_center_border_ = new i_border_widget(0, -1);
    i_border_widget *top_right_border_ = new i_border_widget(1, -1);

    i_border_widget *center_left_border_ = new i_border_widget(-1, 0);
    i_border_widget *center_right_border_ = new i_border_widget(1, 0);

    i_border_widget *bottom_left_border_ = new i_border_widget(-1, 1);
    i_border_widget *bottom_center_border_ = new i_border_widget(0, 1);
    i_border_widget *bottom_right_border_ = new i_border_widget(1, 1);

    // Layout
    QGridLayout *main_grid_ = nullptr;
};

#endif
