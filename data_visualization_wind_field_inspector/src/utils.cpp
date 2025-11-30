#include "wind_view.h"
#include "wind_graphs.h"
#include <QVector>
#include <QFile>
#include <QColor>
#include <QTextStream>
#include <QDebug>

// load data and icon from outside
void wind_view::load_data(const QString &filepath)
{
	wind_data_list.clear();

	// load data
	wind_data_list.clear();
	QFile file(filepath);
	if (!file.exists())
	{
		qDebug() << "[ERROR] File Missing!";
		return;
	}

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "[ERROR] Cannot Open File";
		return;
	}

	qDebug() << "[STATE] Reading file:" << filepath;

	QTextStream read_file(&file);

	// skip the title line
	if (!read_file.atEnd())
	{
		QString title_line = read_file.readLine();
	}

	int row = 1; // as time index, actually equal to time_index, and equal to the previous int time
	while (!read_file.atEnd())
	{
		QString line = read_file.readLine(); // already read one line before, start reading from the second line here
		if (line.isEmpty())
			continue;

		QStringList tokens = line.split(",");
		qDebug() << tokens;
		if (tokens.size() < 6)
		{
			qDebug() << "[ERROR] Data format error in line:" << line;
			continue;
		}

		// read data and store to list
		wind_data temp_data;
		temp_data.time = tokens[0];
		temp_data.time_rows = row; // does not occupy a token (because there is no such column in the .csv), but still added to the list
		temp_data.height = tokens[1].toInt();
		temp_data.hspeed = tokens[2].toFloat();
		temp_data.vspeed = tokens[3].toFloat();
		temp_data.hdirect = tokens[4].toInt();
		temp_data.vdirect = tokens[5].toInt();

		wind_data_list.append(temp_data);
		row++; // since time is distributed positively in the table, the larger the row number, the larger the time, and the larger the grid_x.
	}

	// load icon
	wind_icon_list.clear();
	for (int i = 0; i <= 13; i++)
	{
		QString filename = QString("wind_flag_graphs/level%1.png").arg(i);
		QImage image(filename);

		if (image.isNull())
		{
			qDebug() << "[ERROR] did not load the icon, retrying" << filename;
			update();
		}

		wind_icon_list.append(image);
	}
}

// get hspeed level and transfer to graphs
int wind_view::get_hspeed_level(float hspeed)
{
	if ((0 <= hspeed) && (hspeed < 0.2))
		return 0;
	else if (hspeed < 2.0)
		return 1;
	else if (hspeed < 4.0)
		return 2;
	else if (hspeed < 6.0)
		return 3;
	else if (hspeed < 8.0)
		return 4;
	else if (hspeed < 10.0)
		return 5;
	else if (hspeed < 12.0)
		return 6;
	else if (hspeed < 14.0)
		return 7;
	else if (hspeed < 16.0)
		return 8;
	else if (hspeed < 18.0)
		return 9;
	else if (hspeed < 20.0)
		return 10;
	else if (hspeed < 22.0)
		return 11;
	else if (hspeed < 24.0)
		return 12;
	else if (hspeed >= 24.0)
		return 13;

	// should not reach here
	return 0;
}

// get vspeed level and transfer to color grids
QColor wind_view::get_vspeed_level(float vspeed)
{
	QColor blue3(0, 91, 234);	   // dark blue
	QColor blue2(0, 198, 251);	   // medium blue
	QColor blue1(172, 203, 238);   // light blue
	QColor yellow1(225, 225, 102); // light yellow
	QColor yellow2(249, 212, 35);  // medium yellow
	QColor yellow3(184, 134, 11);  // dark yellow

	if (vspeed <= -0.3)
		return QColor(blue3);
	else if ((-0.3 < vspeed) && (vspeed <= -0.1))
		return QColor(blue2);
	else if ((-0.1 < vspeed) && (vspeed <= -0.05))
		return QColor(blue1);
	else if ((-0.05 < vspeed) && (vspeed < 0.05))
		return QColor(Qt::white);
	else if ((0.05 <= vspeed) && (vspeed < 0.1))
		return QColor(yellow1);
	else if ((0.1 <= vspeed) && (vspeed < 0.3))
		return QColor(yellow2);
	else if (vspeed >= 0.3)
		return QColor(yellow3);

	// should not reach here
	return QColor(Qt::white);
}

// get vspeed direction and transfer from number to text
QString wind_view::get_vspeed_direction(int vdirect)
{
	return (vdirect < 0)
			   ? QString(QObject::tr("DN"))
			   : QString(QObject::tr("UP"));
}
