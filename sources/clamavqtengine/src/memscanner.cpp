
/*
 *  Copyright (C) 2013 Andrey Dudakov
 *
 *  Authors: Andrey "amd00" Dudakov
 *
 *  This file is part of clamavqtengine.
 *
 *  clamavqtengine is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  clamavqtengine is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with clamavqtengine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QDir>
#include <QCoreApplication>
#include <QDateTime>

#include "memscanner.h"

namespace Meduzzza
{

	void MemScanner::runThread()
	{
		scanMemory();
	}

	void MemScanner::scanMemory()
	{
		QDateTime time_start = QDateTime::currentDateTime();
		Q_EMIT memScanStartedSignal(time_start);
		QDir proc_dir("/proc");
		QStringList procs = proc_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("\\d+"));
		PidList proc_list;
		foreach(QString proc, procs)
		{
			checkPause();
			if(Scanner::stopped())
				return;
			Q_PID proc_pid = proc.toInt();
			if(proc_pid == QCoreApplication::applicationPid())
				continue;
			proc_list << proc_pid;
		}
		Q_EMIT procsFindedSignal(proc_list);
		Q_EMIT memScanCompletedSignal(time_start, QDateTime::currentDateTime());
	}
}
