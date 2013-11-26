
#include <QFileDialog>

#include <manager.h>

#include <ui_dirscanwidget.h>

#include "mainwindow.h"
#include "dirscanwidget.h"
#include "meduzzzascanmodel.h"

namespace Meduzzza
{
	DirScanModel::DirScanModel() : QSortFilterProxyModel()
	{
		MeduzzzaScanModel *mod = MeduzzzaScanModel::get();
		setSourceModel(mod);
	}

	bool DirScanModel::filterAcceptsRow(qint32 _row, const QModelIndex &_parent) const
	{
		QModelIndex ind = sourceModel() -> index(_row, MeduzzzaScanModel::Pid);
		if(ind.data().isNull())
			return true;
		return false;
	}



	DirScanWidget::DirScanWidget(MainWindow *_med) : 
			MeduzzzaCommonWidget(_med), m_ui(new Ui::DirScanWidget), m_mod()
	{
		m_ui -> setupUi(this);
		connect(&m_mod, SIGNAL(rowsInserted(const QModelIndex&, qint32, qint32)),
			this, SLOT(rowsInsertedSlot(const QModelIndex&, qint32, qint32)));
		m_ui -> m_scan_view -> setModel(&m_mod);
		m_ui -> m_scan_view -> setColumnHidden(MeduzzzaScanModel::Pid, true);
	}

	DirScanWidget::~DirScanWidget() { delete m_ui; }

	void DirScanWidget::fileScanStarted(const QString &_file)
	{
	}

	void DirScanWidget::fileScanCompleted(const QString &_file)
	{
	}

	void DirScanWidget::fileVirusDetected(const QString &_file, const QString &_virus)
	{
	}

	void DirScanWidget::dirScanStarted(const QString &_dir)
	{
		((MeduzzzaScanModel*)m_mod.sourceModel()) -> clear();
		m_ui -> m_start_button -> setIcon(QIcon(":/images/images/pause.png"));
	}

	void DirScanWidget::dirScanCompleted(const QString &_dir)
	{
		m_ui -> m_start_button -> setIcon(QIcon(":/images/images/play.png"));
	}
	
	void DirScanWidget::memScanStarted()
	{
		m_ui -> m_start_button -> setDisabled(true);
		m_ui -> m_stop_button -> setDisabled(true);
	}
	
	void DirScanWidget::memScanCompleted()
	{
		m_ui -> m_start_button -> setDisabled(false);
		m_ui -> m_stop_button -> setDisabled(false);
	}
		
	void DirScanWidget::fullScanStarted(const QDateTime &_time)
	{
		m_ui -> m_start_button -> setDisabled(true);
		m_ui -> m_stop_button -> setDisabled(true);
	}
	
	void DirScanWidget::fullScanCompleted(const QDateTime &_time)
	{
		m_ui -> m_start_button -> setDisabled(false);
		m_ui -> m_stop_button -> setDisabled(false);
	}

	void DirScanWidget::stopped()
	{
		m_ui -> m_start_button -> setDisabled(false);
		m_ui -> m_stop_button -> setDisabled(false);
		m_ui -> m_start_button -> setIcon(QIcon(":/images/images/play.png"));
		QApplication::restoreOverrideCursor();
	}

	void DirScanWidget::paused()
	{
		m_ui -> m_start_button -> setIcon(QIcon(":/images/images/play.png"));
	}

	void DirScanWidget::resumed()
	{
		m_ui -> m_start_button -> setIcon(QIcon(":/images/images/pause.png"));
	}
	
	void DirScanWidget::dirClickedSlot()
	{
		QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
			"/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		if(!dir.isEmpty())
			m_ui -> m_dir_edit -> setText(dir);
	}

	void DirScanWidget::startClickedSlot()
	{
		if(!m_started)
			m_man -> scanDir(m_ui -> m_dir_edit -> text());
		else if(!m_paused)
			m_man -> pause();
		else
			m_man -> resume();
	}
	
	void DirScanWidget::stopClickedSlot()
	{
		QApplication::setOverrideCursor(Qt::WaitCursor);
		m_ui -> m_stop_button -> setDisabled(true);
		m_man -> stop();
	}
	
	void DirScanWidget::rowsInsertedSlot(const QModelIndex &_par, qint32 _start, qint32 _end)
	{
		QModelIndex ind = m_mod.index(_end, 0, _par);
		m_ui -> m_scan_view -> scrollTo(ind);
	}
	
}
