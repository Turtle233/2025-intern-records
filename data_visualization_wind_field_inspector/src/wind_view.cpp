#include "wind_view.h"
#include "wind_graphs.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QFont>
#include <QColor>
#include <QLabel>
#include <QVector>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QPoint>
#include <QMouseEvent>
#include <QDateTime>

// layout constants
namespace Layout
{
	const int margin_left = 220;
	const int margin_top = 10;
	const int chart_width = 1440;
	const int chart_height = 900;
	const int legend_x = 20;
	const int info_panel_x = margin_left + chart_width + 10;
}

wind_view::wind_view(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setStyleSheet("background-color: white;");
	showMaximized();

	// default font
	font.setFamily("Microsoft Yahei");
	font.setPointSize(10);
	font.setWeight(65);
	setFont(font);

	// default pen
	pen = QPen(Qt::black, 1);

	setWindowTitle(QObject::tr("TITLE"));

	// load sample data (for demo purpose)
	load_data("test_ds.csv");

	QTimer::singleShot(0, this, [this]()
					   { this->update(); });
}

void wind_view::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	// had_drawn_before was defined false
	if (had_drawn_before == false)
	{
		draw_all_levels(painter); // draw all levels of wind graphs
		had_drawn_before = true;
	}

	// legend
	draw_legend(painter);

	// main view
	draw_main_chart(painter);

	// right info view
	draw_info_panel(painter);
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
void wind_view::draw_legend(QPainter &painter)
{
	painter.setBrush(Qt::white);
	painter.setPen(Qt::white);
	painter.setFont(font);

	// horizontal wind direction
	painter.drawRect(Layout::legend_x, Layout::margin_top + 5, 120, 100);
	painter.setPen(pen);
	painter.drawText(Layout::legend_x + 5, Layout::margin_top + 25, QObject::tr("HDIRECT"));

	// NWES diagram
	QPen bold_pen(Qt::black, 1.5);
	painter.setPen(bold_pen);
	painter.drawLine(Layout::legend_x + 15, 70, Layout::legend_x + 65, 70); // horizontal line
	painter.drawLine(Layout::legend_x + 40, 45, Layout::legend_x + 40, 95); // vertical line

	painter.drawLine(Layout::legend_x + 15, 70, Layout::legend_x + 18, 67); // left arrow
	painter.drawLine(Layout::legend_x + 15, 70, Layout::legend_x + 18, 73);
	painter.drawLine(Layout::legend_x + 65, 70, Layout::legend_x + 62, 67); // right arrow
	painter.drawLine(Layout::legend_x + 65, 70, Layout::legend_x + 62, 73);
	painter.drawLine(Layout::legend_x + 40, 45, Layout::legend_x + 37, 48); // top arrow
	painter.drawLine(Layout::legend_x + 40, 45, Layout::legend_x + 43, 48);
	painter.drawLine(Layout::legend_x + 40, 95, Layout::legend_x + 37, 92); // bottom arrow
	painter.drawLine(Layout::legend_x + 40, 95, Layout::legend_x + 43, 92);

	painter.setPen(pen);
	QFont font_in_NWES;
	font_in_NWES.setFamily("Microsoft Yahei");
	font_in_NWES.setPointSize(8);
	font_in_NWES.setWeight(50);

	painter.setFont(font_in_NWES);

	painter.drawText(Layout::legend_x + 2, 74, "W"); // labels
	painter.drawText(Layout::legend_x + 35, 42, "N");
	painter.drawText(Layout::legend_x + 67, 74, "E");
	painter.drawText(Layout::legend_x + 36, 105, "S");

	// horizontal wind speed
	painter.setFont(font);
	painter.setPen(Qt::white);
	painter.drawRect(Layout::legend_x, 130, 120, 300);
	painter.setPen(pen);
	painter.drawText(Layout::legend_x + 5, 140, QObject::tr("HSPEED(m/s)"));

	QFont text_font;
	text_font.setFamily("Microsoft Yahei");
	text_font.setPointSize(10);
	text_font.setWeight(50);

	painter.setFont(text_font);

	float text_dy = 27.13;
	painter.drawText(40, 160 + 5 + 0 * text_dy, "[0.0, 0.2)");
	painter.drawText(40, 165 + 1 * text_dy, "[0.2, 2.0)");
	painter.drawText(40, 165 + 2 * text_dy, "[2.0, 4.0)");
	painter.drawText(40, 165 + 3 * text_dy, "[4.0, 6.0)");
	painter.drawText(40, 165 + 4 * text_dy, "[6.0, 8.0)");
	painter.drawText(40, 165 + 5 * text_dy, "[8.0, 10.0)");
	painter.drawText(40, 165 + 6 * text_dy, "[10.0, 12.0)");
	painter.drawText(40, 165 + 7 * text_dy, "[12.0, 14.0)");
	painter.drawText(40, 165 + 8 * text_dy, "[14.0, 16.0)");
	painter.drawText(40, 165 + 9 * text_dy, "[16.0, 18.0)");
	painter.drawText(40, 165 + 10 * text_dy, "[18.0, 20.0)");
	painter.drawText(40, 165 + 11 * text_dy, "[20.0, 22.0)");
	painter.drawText(40, 165 + 12 * text_dy, "[22.0, 24.0)");
	painter.drawText(40, 165 + 13 * text_dy, "[24.0, INF)");

	for (int i = 1; i <= 13; i++)
	{
		QString filename = QString("wind_flag_graphs/level%1.png").arg(i);
		QImage image(filename);
		painter.drawImage(25, 150 + 27 * i, image);
	}

	int dynamic_interval = 90; // for further adjustment

	// vertical wind direction
	painter.setFont(font);
	painter.setPen(Qt::white);
	painter.drawRect(Layout::legend_x, 450 + dynamic_interval, 120, 50);
	painter.setPen(pen);
	painter.drawText(Layout::legend_x + 5, 460 + dynamic_interval, QObject::tr("VDIRECT"));

	painter.setFont(text_font);

	QColor blue3(0, 91, 234);	 // dark blue
	QColor blue2(0, 198, 251);	 // medium blue
	QColor blue1(172, 203, 238); // light blue

	QColor yellow1(225, 225, 102); // light yellow
	QColor yellow2(249, 212, 35);  // medium yellow
	QColor yellow3(184, 134, 11);  // dark yellow

	painter.setBrush(blue3);
	painter.drawRect(Layout::legend_x + 5, 468 + dynamic_interval, 20, 13);				// + (0,8) unit
	painter.drawText(Layout::legend_x + 50, 479 + dynamic_interval, QObject::tr("UP")); // + (25,11) unit

	painter.setBrush(yellow3);
	painter.drawRect(Layout::legend_x + 5, 485 + dynamic_interval, 20, 13);				// from last rectangle + (0,17) unit
	painter.drawText(Layout::legend_x + 50, 496 + dynamic_interval, QObject::tr("DN")); // from last text lable + (0,17) unit

	// vertical wind speed
	painter.setBrush(Qt::white);
	painter.setFont(font);
	painter.setPen(Qt::white);
	painter.drawRect(Layout::legend_x, 520 + dynamic_interval, 120, 200);
	painter.setPen(pen);
	painter.drawText(Layout::legend_x + 5, 530 + dynamic_interval, QObject::tr("VSPEED(m/s)"));

	painter.setFont(text_font);

	// line 1 as base line
	int vspd_base_rec_x = Layout::legend_x + 5;
	int vspd_base_rec_y = 538 + dynamic_interval;
	int vspd_base_text_x = vspd_base_rec_x + 25;
	int vspd_base_text_y = vspd_base_rec_y + 11;
	int vspd_dy = 17;

	painter.setBrush(blue3);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y, 20, 13);			  // from title label + (0,8) unit
	painter.drawText(vspd_base_text_x, vspd_base_text_y, "(-INF, -0.3]"); // from last rectangle + (25,11) unit

	// line 2
	painter.setBrush(blue2);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (1 * vspd_dy), 20, 13);			  // from last rectangle + (0,17) unit
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (1 * vspd_dy), "(-0.3, -0.1]"); // from last text lable + (0,17) unit

	// line 3
	painter.setBrush(blue1);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (2 * vspd_dy), 20, 13);
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (2 * vspd_dy), "(-0.1, -0.05]");

	// line 4
	painter.setBrush(Qt::white);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (3 * vspd_dy), 20, 13);
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (3 * vspd_dy), "(-0.05, 0.05)");

	// line 5
	painter.setBrush(yellow1);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (4 * vspd_dy), 20, 13);
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (4 * vspd_dy), "[0.05, 0.1)");

	// line 6
	painter.setBrush(yellow2);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (5 * vspd_dy), 20, 13);
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (5 * vspd_dy), "[0.1, 0.3)");

	// line 7
	painter.setBrush(yellow3);
	painter.drawRect(vspd_base_rec_x, vspd_base_rec_y + (6 * vspd_dy), 20, 13);
	painter.drawText(vspd_base_text_x, vspd_base_text_y + (6 * vspd_dy), "[0.3, INF)");

	// legend end
}

void wind_view::draw_main_chart(QPainter &painter)
{
	painter.setFont(font);
	painter.setBrush(Qt::transparent);

	main_rec_width = Layout::chart_width;
	main_rec_height = Layout::chart_height;

	QPen dashdot_pen;
	dashdot_pen.setStyle(Qt::DashDotLine);
	dashdot_pen.setColor(QColor(220, 220, 220));

	// Time axis
	time_scales = 8; // numbers of time scales

	float x_step = main_rec_width / time_scales;
	for (int i = 1; i <= time_scales; i++)
	{
		int x_margin = 50;
		int x = i * x_step + x_margin;

		painter.setPen(dashdot_pen);
		painter.drawLine(x, Layout::margin_top + 1,
						 x, Layout::margin_top + main_rec_height - 1);

		painter.setPen(pen);
		QRect time_rect(x - x_step / 3, (Layout::margin_top + main_rec_height + 10), 200, 200);

		if ((i * 7) < wind_data_list.size())
		{
			QString text = wind_data_list[i * 7].time;
			painter.drawText(time_rect, Qt::AlignLeft, text);
		}
		else
		{
			qDebug() << "[CHECK] The rows are not enough to show the time-axis! Recommend rows: " << max_time_rows;
		}
	}

	painter.drawText(Layout::margin_left + main_rec_width / 2, Layout::margin_top + main_rec_height + 60, QObject::tr("TIME"));

	// Height axis
	height_scales = 16;
	double y_step = 1.00 * main_rec_height / height_scales; // a single large grid step
	for (int i = 1; i <= height_scales; i++)
	{
		int y = Layout::margin_top + main_rec_height - i * y_step;
		painter.setPen(dashdot_pen);
		painter.drawLine(Layout::margin_left + 1, y,
						 Layout::margin_left + main_rec_width - 1, y);
		// height labels
		painter.setPen(pen);
		painter.setBrush(Qt::transparent);
		QRect rect(Layout::margin_left - 80, static_cast<int>(y + 1 * y_step - 10), 70, 15);
		QString text = QString::number((i - 1) * 200);
		painter.drawText(rect, Qt::AlignRight, text);
	}
	painter.drawText((Layout::margin_left - 85), ((Layout::margin_top + main_rec_height - 17 * y_step) + 1 * y_step + 8), "MAX(3200)"); // draw the max-line text

	painter.save();																			   // save the previous painter
	painter.translate(Layout::margin_left - 70, Layout::margin_top + main_rec_height / 2 + 5); // move the (0,0) to a new position (aka new canva)
	painter.rotate(-90);																	   // rotate the new canva
	painter.drawText(0, 0, QObject::tr("HEIGHT"));											   // paint directly to the (0,0) of the new canva, absolute position ((220 - 70), (10 + main_rec_hight / 2) + 5)
	painter.restore();																		   // reload the saved painter

	// cell grids
	time_grids = time_scales * 7;	  // number of x scales * 7 = total number of x-axis grids Currently there are 8 time scales, so there are 56 time grids
	height_grids = height_scales * 5; // number of y scales * 5 = total number of y-axis grids

	grid_width = 1.00 * main_rec_width / time_grids;	 // width of a single grid cell Issue line [solved] Solution: 1.0 * cast to double
	grid_height = 1.00 * main_rec_height / height_grids; // height of a single grid cell Issue line [solved] Solution: 1.0 * cast to double
	max_time_rows = 560;
	time_rows_per_grid = 1.00 * max_time_rows / time_grids; // number of actual time index values (rows) represented by each grid cell = total index values / total time grids
	height_per_grid = 1.00 * 3200 / height_grids;			// actual height value represented by each grid cell

	for (const wind_data &data : wind_data_list)
	{
		// read the data from the list
		QString time_value = data.time;

		// draw F diagram based on horizontal wind speed - begin
		// The following three lines are local variables used only for drawing, to avoid conflicts with on_clicked_rect that needs to be passed later)
		float grid_x = Layout::margin_left + grid_width * data.time_rows; // horizontal coordinate of a specific cell grid

		float height_grid_count = static_cast<float>(data.height) / height_per_grid;
		float grid_y = 5 + main_rec_height - (grid_height * height_grid_count); // height of a single grid cell * number of grid cells represented by this height = height in pixels This calculates the vertical coordinate of a specific cell grid

		if (grid_x <= (Layout::margin_left - grid_width) + main_rec_width)
		{
			// default cell rects
			painter.setPen(QPen(Qt::lightGray, 2));
			painter.setBrush(Qt::transparent);
			QRectF cell_rects(grid_x, grid_y, grid_width, grid_height);
			painter.drawRect(cell_rects);

			// draw color blocks based on vertical wind speed - begin
			QColor vspeed_level = get_vspeed_level(data.vspeed);
			painter.setPen(QPen(Qt::transparent, 1));
			painter.setBrush(vspeed_level);
			painter.drawRect(cell_rects);
			// draw color blocks based on vertical wind speed - end

			// read the icons from the list
			// const QImage &image = wind_icon_list[data.hspeed];
			int hspeed_level = get_hspeed_level(data.hspeed);

			if (hspeed_level >= 0 && hspeed_level < wind_icon_list.size())
			{
				const QImage &image = wind_icon_list[hspeed_level];
				// QImage fit_image = image.scaled(cell_rects.size().toSize(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

				QPointF drawTopLeft = cell_rects.topLeft() + QPointF(6, -12);
				painter.drawImage(drawTopLeft, image);
			}
			else
			{
				qDebug() << "[CHECK] Size of wind_icon_list " << wind_icon_list.size();
				qDebug() << "[CHECKED ERROR] hspeed_level out of range!" << hspeed_level;
			}
			// draw F diagram based on horizontal wind speed - end
		}
		else
		{
			qDebug() << "[CHECK] Too wide time range!! Cannot fill into the graphboard.";
			break;
		}
	}

	// main view end
}

void wind_view::draw_info_panel(QPainter &painter)
{
	painter.setBrush(QColor(240, 255, 250));
	painter.setPen(QPen(QColor(0, 153, 0), 2));
	painter.drawRect(Layout::info_panel_x, Layout::margin_top, 200, 550);

	int labeldy = 75;
	painter.setPen(QPen(QColor(0, 153, 0), 1));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 0, QObject::tr("TIME"));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 1, QObject::tr("HEIGHT"));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 2, QObject::tr("HDIRECT"));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 3, QObject::tr("HSPEED(m/s)"));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 4, QObject::tr("VDIRECT"));
	painter.drawText((Layout::info_panel_x + 5), 30 + labeldy * 5, QObject::tr("VSPEED(m/s)"));

	painter.setBrush(QColor(245, 255, 255));
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 0, 190, 30);
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 1, 190, 30);
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 2, 190, 30);
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 3, 190, 30);
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 4, 190, 30);
	painter.drawRect((Layout::info_panel_x + 5), 38 + labeldy * 5, 190, 30);

	painter.drawText((Layout::margin_left + Layout::chart_width + 130), 550, QObject::tr("INFO_DISPLAY"));

	painter.setPen(QPen(Qt::black, 2));
	painter.setBrush(Qt::transparent);
	painter.drawRect(Layout::margin_left, Layout::margin_top, main_rec_width, main_rec_height);

	if (has_clicked_rect == true)
	{
		// show color change and grid info when clicking on the selected cell gried
		painter.setPen(QPen(QColor(0, 153, 0), 3));
		painter.setBrush(Qt::transparent);
		painter.drawRect(clicked_cell_rect);

		/*------------------------------------------------------------------------------------------------------------------------*/

		// painter.setPen(Qt::black);
		QFont info_font;
		info_font.setFamily("");
		info_font.setWeight(80);
		info_font.setPointSize(15);
		painter.setFont(info_font);

		QRect time_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 0, 185, 30);
		QString time_info_text = shown_time;
		painter.drawText(time_info_rect, time_info_text);

		QRect height_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 1, 185, 30);
		QString height_info_text = QString::number(shown_height);
		painter.drawText(height_info_rect, height_info_text);

		QRect hdirect_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 2, 185, 30);
		QString hdirect_info_text = QString::number(shown_hdirect);
		painter.drawText(hdirect_info_rect, hdirect_info_text);

		QRect hspeed_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 3, 185, 30);
		QString hspeed_info_text = QString::number(shown_hspeed);
		painter.drawText(hspeed_info_rect, hspeed_info_text);

		QRect vdirect_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 4, 185, 30);
		QString vdirect_info_text = get_vspeed_direction(shown_vdirect);
		painter.drawText(vdirect_info_rect, vdirect_info_text);

		QRect vspeed_info_rect((Layout::info_panel_x + Layout::margin_top), 40 + labeldy * 5, 185, 30);
		QString vspeed_info_text = QString::number(shown_vspeed);
		painter.drawText(vspeed_info_rect, vspeed_info_text);
	}
}

void wind_view::mousePressEvent(QMouseEvent *event)
{
	QPointF pos = event->pos();
	bool inside_main_rec = QRectF(Layout::margin_left, Layout::margin_top, main_rec_width, main_rec_height).contains(pos);
	if (!inside_main_rec)
		return;

	double clicked_x = 1.00 * (pos.x() - Layout::margin_left);
	double clicked_y = 1.00 * (pos.y() - Layout::margin_top);

	qDebug() << "[STATE] clicked at (x,y)" << clicked_x << clicked_y;

	clicked_time_rows = std::floor(clicked_x / grid_width);
	clicked_height = 1.00 * (main_rec_height - clicked_y) / grid_height * height_per_grid;

	qDebug() << "[STATE] clicked time rows" << clicked_time_rows;

	qDebug() << "[STATE] time rows per grid" << time_rows_per_grid;

	for (const wind_data &data : wind_data_list)
	{
		// read all data from the list, but only display elements that meet the criteria
		if (std::abs(data.time_rows - clicked_time_rows) < time_rows_per_grid && std::abs(data.height - clicked_height) < height_per_grid)
		{
			// has_clicked_rect was defined false
			has_clicked_rect = true;

			qDebug() << "[STATE] abs: time_rows - clicked_time_rows" << std::abs(data.time_rows - clicked_time_rows);

			qDebug() << "[STATE] clicked" << clicked_height << "while output as" << data.height;
			qDebug() << "[STATE] hspeed of this grid" << data.hspeed;
			qDebug() << "[STATE] vspeed of this grid" << data.vspeed;
			qDebug() << "[STATE] hdirect of this grid" << data.hdirect;
			qDebug() << "[STATE] vdirect of this grid" << data.vdirect;

			float selected_grid_x = Layout::margin_left + grid_width * data.time_rows; // horizontal coordinate of the selected cell grid
			float height_grid_count = static_cast<float>(data.height) / height_per_grid;
			float selected_grid_y = static_cast<int>(5 + main_rec_height - grid_height * height_grid_count); // vertical coordinate of the selected cell grid

			clicked_cell_rect = QRect(selected_grid_x, selected_grid_y, grid_width, grid_height);

			// read the selected raw data from the list and then store it in member variables for display in the info panel on the right
			shown_time = data.time;
			shown_height = data.height;
			shown_hspeed = data.hspeed;
			shown_vspeed = data.vspeed;
			shown_hdirect = data.hdirect;
			shown_vdirect = data.vdirect;

			update(); // when this if statement is updated, that is, when the user re-selects a grid, the paintEvent update event is triggered to redraw
			break;	  // stop searching immediately after finding a grid
		}
	}
}

wind_view::~wind_view()
{
}
