#include "wind_graphs.h"
#include <QPainter>
#include <QColor>
#include <QImage>
#include <QPolygon>
#include <QPoint>

void draw_level(QPainter &painter, int level)
{
	switch (level)
	{
	case 0:
		draw_level0(painter);
		break;
	case 1:
		draw_level1(painter);
		break;
	case 2:
		draw_level2(painter);
		break;
	case 3:
		draw_level3(painter);
		break;
	case 4:
		draw_level4(painter);
		break;
	case 5:
		draw_level5(painter);
		break;
	case 6:
		draw_level6(painter);
		break;
	case 7:
		draw_level7(painter);
		break;
	case 8:
		draw_level8(painter);
		break;
	case 9:
		draw_level9(painter);
		break;
	case 10:
		draw_level10(painter);
		break;
	case 11:
		draw_level11(painter);
		break;
	case 12:
		draw_level12(painter);
		break;
	case 13:
		draw_level13(painter);
		break;
	default:
		break;
	}
}

void draw_all_levels(QPainter &painter)
{
	for (int level = 0; level <= 13; ++level)
	{
		draw_level(painter, level);
	}
}

/* Generates wind flag icons for levels 0–13 and saves them as wind_flag_graphs/leveln.png.These functions only generate offline image files. They do NOT draw directly onto any window or widget. */

int standard_height = 24;
int standard_length = 24 / 2;
int interval = 24 / 6;

void draw_level0(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);
	image.save("wind_flag_graphs/level0.png");
}

void draw_level1(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	// level 1
	QPainter level1(&image);
	level1.save();
	level1.setRenderHint(QPainter::Antialiasing);
	level1.setBrush(Qt::transparent);
	level1.setPen(QPen(Qt::white, 0));
	level1.drawRect(0, 0, 12 * interval, 12 * interval);
	level1.setPen(Qt::black);
	level1.drawLine(1, 0, 1, 12 * interval);
	level1.drawLine(0, 1, 0.5 * standard_length, 1);
	image.save("wind_flag_graphs/level1.png");
	level1.restore();
}

void draw_level2(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	// level 2
	QPainter level2(&image);
	level2.save();
	level2.setRenderHint(QPainter::Antialiasing);
	level2.setBrush(Qt::transparent);
	level2.setPen(Qt::white);
	level2.drawRect(0, 0, 12 * interval, 12 * interval);
	level2.setPen(Qt::black);
	level2.drawLine(1, 0, 1, 12 * interval);
	level2.drawLine(0, 1, 1 * standard_length, 1);
	image.save("wind_flag_graphs/level2.png");
	level2.restore();
}

void draw_level3(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level3(&image);
	level3.save();
	level3.setRenderHint(QPainter::Antialiasing);
	level3.setBrush(Qt::transparent);
	level3.setPen(Qt::white);
	level3.drawRect(0, 0, 12 * interval, 12 * interval);
	level3.setPen(Qt::black);
	level3.drawLine(1, 0, 1, 12 * interval);
	level3.drawLine(0, 1, 1 * standard_length, 1);
	level3.drawLine(0, 1 * interval, 0.5 * standard_length, 1 * interval);
	image.save("wind_flag_graphs/level3.png");
	level3.restore();
}

void draw_level4(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level4(&image);
	level4.save();
	level4.setRenderHint(QPainter::Antialiasing);
	level4.setBrush(Qt::transparent);
	level4.setPen(Qt::white);
	level4.drawRect(0, 0, 12 * interval, 12 * interval);
	level4.setPen(Qt::black);
	level4.drawLine(1, 0, 1, 12 * interval);
	level4.drawLine(0, 1, 1 * standard_length, 1);
	level4.drawLine(0, 1 * interval, 1 * standard_length, 1 * interval);
	image.save("wind_flag_graphs/level4.png");
	level4.restore();
}

void draw_level5(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level5(&image);
	level5.save();
	level5.setRenderHint(QPainter::Antialiasing);
	level5.setBrush(Qt::transparent);
	level5.setPen(Qt::white);
	level5.drawRect(0, 0, 12 * interval, 12 * interval);
	level5.setPen(Qt::black);
	level5.drawLine(1, 0, 1, 12 * interval);
	level5.drawLine(0, 1, 1 * standard_length, 1);
	level5.drawLine(0, 1 * interval, 1 * standard_length, 1 * interval);
	level5.drawLine(0, 2 * interval, 0.5 * standard_length, 2 * interval);
	image.save("wind_flag_graphs/level5.png");
	level5.restore();
}

void draw_level6(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level6(&image);
	level6.save();
	level6.setRenderHint(QPainter::Antialiasing);
	level6.setBrush(Qt::transparent);
	level6.setPen(Qt::white);
	level6.drawRect(0, 0, 12 * interval, 12 * interval);
	level6.setPen(Qt::black);
	level6.drawLine(1, 0, 1, 12 * interval);
	level6.drawLine(0, 1, 1 * standard_length, 1);
	level6.drawLine(0, 1 * interval, 1 * standard_length, 1 * interval);
	level6.drawLine(0, 2 * interval, 1 * standard_length, 2 * interval);
	image.save("wind_flag_graphs/level6.png");
	level6.restore();
}

void draw_level7(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level7(&image);
	level7.save();
	level7.setRenderHint(QPainter::Antialiasing);
	level7.setBrush(Qt::transparent);
	level7.setPen(Qt::white);
	level7.drawRect(0, 0, 12 * interval, 12 * interval);
	level7.setPen(Qt::black);
	level7.drawLine(1, 0, 1, 12 * interval);
	level7.drawLine(0, 1, 1 * standard_length, 1);
	level7.drawLine(0, 1 * interval, 1 * standard_length, 1 * interval);
	level7.drawLine(0, 2 * interval, 1 * standard_length, 2 * interval);
	level7.drawLine(0, 3 * interval, 0.5 * standard_length, 3 * interval);
	image.save("wind_flag_graphs/level7.png");
	level7.restore();
}

void draw_level8(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level8(&image);
	level8.save();
	level8.setRenderHint(QPainter::Antialiasing);
	level8.setBrush(Qt::transparent);
	level8.setPen(Qt::white);
	level8.drawRect(0, 0, 12 * interval, 12 * interval);
	level8.setPen(Qt::black);
	level8.drawLine(1, 0, 1, 12 * interval);
	level8.drawLine(0, 1, 1 * standard_length, 1);
	level8.drawLine(0, 1 * interval, 1 * standard_length, 1 * interval);
	level8.drawLine(0, 2 * interval, 1 * standard_length, 2 * interval);
	level8.drawLine(0, 3 * interval, 1 * standard_length, 3 * interval);
	image.save("wind_flag_graphs/level8.png");
	level8.restore();
}

void draw_level9(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level9(&image);
	level9.save();
	level9.setRenderHint(QPainter::Antialiasing);
	level9.setBrush(Qt::transparent);
	level9.setPen(Qt::black);
	level9.drawRect(0, 0, 12 * interval, 12 * interval);
	level9.setPen(Qt::black);
	level9.drawLine(1, 0, 1, 12 * interval);
	level9.setBrush(QColor(160, 160, 160));
	level9.setPen(QColor(160, 160, 160));

	QPolygon triangle;
	triangle << QPoint(0, 0) << QPoint(1 * standard_length, 1.5 * interval) << QPoint(0, 3 * interval);
	level9.drawPolygon(triangle);

	level9.setPen(Qt::black);
	level9.drawLine(0, 4 * interval, 0.5 * standard_length, 4 * interval);
	image.save("wind_flag_graphs/level9.png");
	level9.restore();
}

void draw_level10(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level10(&image);
	level10.save();
	level10.setRenderHint(QPainter::Antialiasing);
	level10.setBrush(Qt::transparent);
	level10.setPen(Qt::white);
	level10.drawRect(0, 0, 12 * interval, 12 * interval);
	level10.setPen(Qt::black);
	level10.drawLine(1, 0, 1, 12 * interval);
	level10.setBrush(QColor(160, 160, 160));
	level10.setPen(QColor(160, 160, 160));

	QPolygon triangle;
	triangle << QPoint(0, 0) << QPoint(3 * interval, 1.5 * interval) << QPoint(0, 3 * interval);
	level10.drawPolygon(triangle);

	level10.setPen(Qt::black);
	level10.drawLine(0, 4 * interval, 1 * standard_length, 4 * interval);
	image.save("wind_flag_graphs/level10.png");
	level10.restore();
}

void draw_level11(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level11(&image);
	level11.save();
	level11.setRenderHint(QPainter::Antialiasing);
	level11.setBrush(Qt::transparent);
	level11.setPen(Qt::white);
	level11.drawRect(0, 0, 12 * interval, 12 * interval);
	level11.setPen(Qt::black);
	level11.drawLine(1, 0, 1, 12 * interval);
	level11.setBrush(QColor(160, 160, 160));
	level11.setPen(QColor(160, 160, 160));

	QPolygon triangle;
	triangle << QPoint(0, 0) << QPoint(3 * interval, 1.5 * interval) << QPoint(0, 3 * interval);
	level11.drawPolygon(triangle);

	level11.setPen(Qt::black);
	level11.drawLine(0, 4 * interval, 1 * standard_length, 4 * interval);
	level11.drawLine(0, 5 * interval, 0.5 * standard_length, 5 * interval);
	image.save("wind_flag_graphs/level11.png");
	level11.restore();
}

void draw_level12(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level12(&image);
	level12.save();
	level12.setRenderHint(QPainter::Antialiasing);
	level12.setBrush(Qt::transparent);
	level12.setPen(Qt::white);
	level12.drawRect(0, 0, 12 * interval, 12 * interval);
	level12.setPen(Qt::black);
	level12.drawLine(1, 0, 1, 12 * interval);
	level12.setBrush(QColor(160, 160, 160));
	level12.setPen(QColor(160, 160, 160));

	QPolygon triangle;
	triangle << QPoint(0, 0) << QPoint(3 * interval, 1.5 * interval) << QPoint(0, 3 * interval);
	level12.drawPolygon(triangle);

	level12.setPen(Qt::black);
	level12.drawLine(0, 4 * interval, 1 * standard_length, 4 * interval);
	level12.drawLine(0, 5 * interval, 1 * standard_length, 5 * interval);
	image.save("wind_flag_graphs/level12.png");
	level12.restore();
}

void draw_level13(QPainter &painter)
{
	QImage image(standard_length, standard_height, QImage::Format_ARGB32);
	image.fill(Qt::transparent);

	QPainter level13(&image);
	level13.save();
	level13.setRenderHint(QPainter::Antialiasing);
	level13.setBrush(Qt::transparent);
	level13.setPen(Qt::white);
	level13.drawRect(0, 0, 12 * interval, 12 * interval);
	level13.setPen(Qt::black);
	level13.drawLine(1, 0, 1, 12 * interval);
	level13.setBrush(QColor(160, 160, 160));
	level13.setPen(QColor(160, 160, 160));

	QPolygon triangle;
	triangle << QPoint(0, 0) << QPoint(3 * interval, 1.5 * interval) << QPoint(0, 3 * interval);
	level13.drawPolygon(triangle);

	level13.setPen(Qt::black);
	level13.drawLine(0, 4 * interval, 1 * standard_length, 4 * interval);
	level13.drawLine(0, 5 * interval, 1 * standard_length, 5 * interval);
	level13.drawLine(0, 6 * interval - 1, 0.5 * standard_length, 6 * interval - 1);
	image.save("wind_flag_graphs/level13.png");
	level13.restore();
}
