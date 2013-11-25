
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

#ifndef _MEMSCANNER_H_
#define _MEMSCANNER_H_

#include <QProcess>

#include "scanner.h"

namespace Meduzzza
{
	class MemScanner : public Scanner
	{
		Q_OBJECT

	public:
		MemScanner()  : Scanner() {}
		~MemScanner() {}

	protected:
		void run();

	private:
		void scanMemory();
		qint32 scanProcess(Q_PID _pid, const char **_virname);

	Q_SIGNALS:
		void procsFindedSignal(const QList<Q_PID> &_proc_list);
		
		void procScanStartedSignal(const QString &_name, qint32 _pid);
		void procScanCompletedSignal(const QString &_name, qint32 _pid, qint32 _result, const QString &_virname);
		
		void memScanStartedSignal();
		void memScanCompletedSignal();
	};
}
#endif
