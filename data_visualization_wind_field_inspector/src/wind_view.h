#pragma once

#include <QtWidgets/QWidget>
#include "ui_wind_view.h"
#include <QPen>

class wind_view : public QWidget
{
	Q_OBJECT

public:
	wind_view(QWidget *parent = nullptr);
	~wind_view();

protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;

private:
	Ui::wind_viewClass ui;
	QFont font;
	QPen pen;

	struct wind_data
	{
		QString time;
		int time_rows;
		int height;
		float hspeed;
		float vspeed;
		int hdirect;
		int vdirect;
	};

	QVector<wind_data> wind_data_list;
	QVector<QImage> wind_icon_list;

	bool had_drawn_before = false;

	int main_rec_width;
	int main_rec_height;

	int time_scales;
	int height_scales;
	int time_grids;	  // total number of time grids
	int height_grids; // total number of height grids
	double grid_width;
	double grid_height;

	int max_time_rows;

	double time_rows_per_grid;
	double height_per_grid;

	bool has_clicked_rect = false;
	QRect clicked_cell_rect;

	double clicked_time_rows;
	double clicked_height;

	QString shown_time;
	int shown_height;
	float shown_hspeed;
	float shown_vspeed;
	int shown_hdirect;
	int shown_vdirect;

	void draw_info_panel(QPainter &painter);
	void draw_legend(QPainter &painter);
	void draw_main_chart(QPainter &painter);
	void load_data(const QString &filepath);
	int get_hspeed_level(float hspeed);
	QColor get_vspeed_level(float vspeed);
	QString get_vspeed_direction(int vdirect);
};
