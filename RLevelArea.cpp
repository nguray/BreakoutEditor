
#include "RLevelArea.h"
#include <iostream>
#include <fstream>
#include <sstream>


RLevelArea::RLevelArea(QWidget *parent, QImage *img): QWidget(parent),
	m_select_brick(1), m_imgBricks(img)
{
	//------------------------------------------------------------

	initLevel();

	//setAttribute(Qt::WA_StyledBackground);
}


RLevelArea::~RLevelArea()
{
	//------------------------------------------------------------
	m_tbl_bricks.clear();

}

void RLevelArea::initLevel()
{
	//------------------------------------------------------------
	m_tbl_bricks.clear();
	for (int l=0;l<NB_ROWS;l++) {
		for (int c=0;c<NB_COLUMNS;c++) {
			m_tbl_bricks.push_back(0);
		}
	}

}

void RLevelArea::drawGrid(QPainter &qp)
{
	int		x, y;
	QColor	col(50, 50, 50);
	//-----------------------------------------------------------
	qp.setPen(col);
	for (int iy = 0; iy<(NB_ROWS+1); iy++) {
		y = iy*BRICK_HEIGHT;
		for (int ix = 0; ix<(NB_COLUMNS+1); ix++) {
			x = ix*BRICK_WIDTH;
			qp.drawPoint(x, y);
		}
	}

}

void RLevelArea::drawBricks(QPainter &qp)
{
	int		typ;
	int		x, y;
	//-----------------------------------------------------------
	if (m_imgBricks){
		for (int l = 0; l<NB_ROWS; l++) {
			for (int c = 0; c<NB_COLUMNS; c++) {
				if (typ = m_tbl_bricks[l*NB_COLUMNS + c]) {
					x = c * BRICK_WIDTH;
					y = l * BRICK_HEIGHT;
					qp.drawImage(QRect(x+1, y+1, BRICK_WIDTH-2, BRICK_HEIGHT-2), *m_imgBricks, QRect(0, typ * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT));
				}
			}
		}
	}

}

void RLevelArea::paintEvent(QPaintEvent *e)
{
	//-----------------------------------------------------------
	QPainter qp(this);

	//int h = height();
	//int w = width();
	//qp.drawRect(0, 0, w-1, h-1);

	//--
	drawGrid(qp);

	//--
	drawBricks(qp);


	QWidget::paintEvent(e);
}

void RLevelArea::mousePressEvent(QMouseEvent* event)
{
	int		i, l, c;
	int 	x, y;
	//------------------------------------------------------
	x = event->pos().x();
	y = event->pos().y();

	if (event->buttons() == Qt::LeftButton) {

		//--
		if ((x<NB_COLUMNS*BRICK_WIDTH)&&(y<NB_ROWS*BRICK_HEIGHT)) {
			//--
			l = (int) (y / BRICK_HEIGHT);
			c = (int) (x / BRICK_WIDTH);
			i = l*NB_COLUMNS + c;
			m_tbl_bricks[i] = m_select_brick;
			m_index_last_input = i;
		}
		repaint();

	}
	else if (event->buttons() == Qt::RightButton) {
		//--
		if ((x<NB_COLUMNS*BRICK_WIDTH) && (y<NB_ROWS*BRICK_HEIGHT)) {
			//--
			l = (int) (y / BRICK_HEIGHT);
			c = (int) (x / BRICK_WIDTH);
			i = l*NB_COLUMNS + c;
			m_tbl_bricks[i] = 0;
			m_index_last_input = i;
		}
		repaint();

	}

}

void RLevelArea::mouseMoveEvent(QMouseEvent* event)
{
	int		x, y;
	//------------------------------------------------------
	x = event->pos().x();
	y = event->pos().y();


}

void RLevelArea::setSelectedBrickSlot(int typBrick)
{
	//-----------------------------------------------------------
	m_select_brick = typBrick;

}

void RLevelArea::LoadLevel(QString fileName)
{
	
	//--------------------------------------------------
	if (!fileName.isNull()) {

		std::string fname = fileName.toStdString();
		std::ifstream myfile(fname);

		if (myfile.is_open())
		{
			int				i,c,l;
			std::string		line;
			l = 0;
			while (getline(myfile, line)) {

				if (myfile.eof()) break;

				if (line.size()) {

					c = 0;
					for (char& ci : line) {
						i = l*NB_COLUMNS + c;
						m_tbl_bricks[i] = ci - '0';
						c++;
					}

				}
				//--
				l++;
			}
			repaint();
		}
		//--
		myfile.close();
	}

}

void RLevelArea::SaveLevel(QString fileName)
{
	//--------------------------------------------------
	if (!fileName.isNull()) {
		std::string		fname = fileName.toStdString();
		std::ofstream	myfile(fname);
		if (myfile.is_open()) {
			int				i, c, l, typ;
			char			b;
			//-------------------------------
			for (int l = 0; l < NB_ROWS; l++) {
				//--
				for (int c = 0; c < NB_COLUMNS; c++) {
					i = l*NB_COLUMNS + c;
					typ = m_tbl_bricks[i];
					b = char(typ + '0');
					myfile << b;

				}
				//--
				myfile << std::endl;

			}
			//--
			myfile.close();
		}
	}

}
