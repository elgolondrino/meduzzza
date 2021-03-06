
/*
 *  Copyright (C) 2013 Andrey Dudakov
 *
 *  Authors: Andrey "amd00" Dudakov
 *
 *  This file is part of meduzzza-gui.
 *
 *  meduzzza-gui is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  meduzzza-gui is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with meduzzza-gui.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UPDATEMODEL_H_
#define _UPDATEMODEL_H_

#include <QAbstractItemModel>

namespace Meduzzza
{
	class UpdateModel : public QAbstractItemModel
	{
		Q_OBJECT
		
	public:
		enum Status
		{
			InProgress,
			Downloaded,
			Error
		};
		
		enum Columns
		{
			Name = 0,
			Status,
			Progress,
			StartTime,
			EndTime
		};
		
	private:
		struct DownloadItem
		{
			DownloadItem(const QString &_name) : name(_name), status(UpdateModel::InProgress), read(0), total(0) {}
			QString name;
			qint32 status;
			quint64 read;
			quint64 total;
			QDateTime start_time;
			QDateTime end_time;
		};
		
	private:
		QList<DownloadItem> m_items;
		
	public:
		UpdateModel();
		~UpdateModel() {}
		
		void clear();
		
		QVariant data(const QModelIndex &_ind, int _role) const;
		qint32 rowCount(const QModelIndex &_par = QModelIndex()) const { return m_items.size(); }
		qint32 columnCount(const QModelIndex &_ind) const { return 5; }
		QModelIndex index(qint32 _row, qint32 _column, const QModelIndex &_par) const;
		QModelIndex parent(const QModelIndex &_ind) const { return QModelIndex(); }
		QVariant headerData(int section, Qt::Orientation orientation, int _role) const;
		
	private:
		qint32 findItem(const QString &_file);
		
	private Q_SLOTS:
		void updateStartedSlot(bool _is_full, const QDateTime &_start_time);
		void updateCompletedSlot(const QDateTime &_start_time, const QDateTime &_end_time);
		void fileDownloadStartedSlot(const QString &_file, const QDateTime &_start_time);
		void fileDownloadCompletedSlot(const QString &_file, const QDateTime &_start_time, const QDateTime &_end_time);
		void fileDownloadProgressSlot(const QString &_file, quint64 _read, quint64 _total);
		void fileDownloadErrorSlot(const QString &_file, const QString &_error);
	};
}

#endif
