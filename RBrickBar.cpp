#include <QtGui>
#include "RBrickBar.h"


RBrickBar::RBrickBar(QWidget *parent, QImage *img):
	QWidget(parent),
	m_id_brick(1),
	m_imgBricks(img)
{
	//------------------------------------------------------------

	for (int i = 0;i<11;i++) {
		m_listBricks.push_back(QRect(0, 0, BRICK_WIDTH, BRICK_HEIGHT));
	}

}


RBrickBar::~RBrickBar()
{
	m_listBricks.clear();
}


void RBrickBar::paintEvent(QPaintEvent *e)
{
	int		x, y;
	//-----------------------------------------------------------
	QPainter qp(this);

	//int h = height();
	//int w = width();

	if (m_imgBricks) {

		//qp.drawRect(x, 2, 32-2, 16-2);
		//qp.drawLine(x, 2, x + 32, 16);
		//qp.drawLine(x, 18, x + 32, 2);

		x = width() / 2 - BRICK_WIDTH/2;

		QRect *r;
		for (int i = 0;i<11;i++) {
			y = i*(BRICK_HEIGHT+4)+4;
			m_listBricks[i] = QRect(x, y, BRICK_WIDTH, BRICK_HEIGHT);
			qp.drawImage( m_listBricks[i], *m_imgBricks, QRect(0, i * BRICK_HEIGHT, BRICK_WIDTH, BRICK_HEIGHT));
		}

		//--
		drawSelectedMark(qp);

	}

	QWidget::paintEvent(e);
}

int RBrickBar::YtoIndex(int y)
{
	int index = -1;
	//------------------------------------------------------
	if ((y>1)&&(y<(11 * (BRICK_HEIGHT+2)+1))) {
		index = int ((y - 2) / (BRICK_HEIGHT));
	}
	return index;
}

void RBrickBar::drawSelectedMark(QPainter &qp)
{
	int		left, right;
	int		top, bottom;
	//------------------------------------------------------
	if (m_id_brick>=0) {

		QPen pen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		qp.setPen(pen);

		auto l = m_listBricks[m_id_brick].left()-2;
		auto t = m_listBricks[m_id_brick].top()-2;
		auto r = m_listBricks[m_id_brick].right()+2;
		auto b = m_listBricks[m_id_brick].bottom()+2;

		QPoint pointsLeft[4] = {
			QPoint(l,t),
			QPoint(r,t),
			QPoint(r, b),
			QPoint(l, b)
		};

		qp.drawPolygon(pointsLeft, 4);

	}

}

void RBrickBar::mousePressEvent(QMouseEvent* event)
{
	int x, y, idBrick;
	//------------------------------------------------------
	x = event->pos().x();
	y = event->pos().y();
	if (event->buttons() == Qt::LeftButton)
	{
		//m_id_brick = -1;
		for (int idBrick=0; idBrick < m_listBricks.size(); idBrick++) {
			if (m_listBricks[idBrick].contains(x,y)){
				m_id_brick = idBrick;
				emit brickChanged(m_id_brick);
			}
		}
		repaint();
	}
}
