#ifndef I_BORDER_WIDGET_H
#define I_BORDER_WIDGET_H

#include <QWidget>
#include <QString>

class i_border_widget : public QWidget
{
    Q_OBJECT

public:
    explicit i_border_widget(int index_x, int index_y, QWidget *parent = nullptr);
    ~i_border_widget();

signals:
    void sig_resize(int offset_x, int offset_y);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private:
    int index_x_;
    int index_y_;

    bool focused_;
    int last_pos_x_;
    int last_pos_y_;

    QString ver_tag(int y)
    {
        if (y < 0)
            return "top";
        if (y > 0)
            return "bottom";
        return "center";
    }

    QString hor_tag(int x)
    {
        if (x < 0)
            return "left";
        if (x > 0)
            return "right";
        return "center";
    }

    void set_hor_size(int x)
    {
        if (x == 0)
            setFixedWidth(4);
        else
            setFixedWidth(6);
    }

    void set_ver_size(int y)
    {
        if (y == 0)
            setFixedHeight(4);
        else
            setFixedHeight(6);
    }
};

#endif
