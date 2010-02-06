/*============================================================================*
 *                                                                            *
 *	This file is part of the Zoto Software Suite.  							  *
 *																			  *
 *	Copyright (C) 2004, 2005 Zoto, Inc.  123 South Hudson, OKC, OK  73102	  *
 *																			  *
 *  This program is free software; you can redistribute it and/or modify      *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation; either version 2 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This program is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this program; if not, write to the Free Software               *
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
 *                                                                            *
 *============================================================================*
 *                                  CHANGELOG                                 *
 *   Date       Description                                    Author         *
 * -----------  ---------------------------------------------  -------------- *
 *                                                                            *
 *============================================================================*/
#if !defined(__ZLOG_H_INCLUDED__)
#define __ZLOG_H_INCLUDED__

#include "ZPlatform.h"

/* System Headers */
#include <string>

/* Local Headers */
#include "ZErrorBlock.h"
#include "ZMutex.h"

/* Macros */
#define ZTRACE ZLog::GetLog().Trace
#define ZERROR (ZErrorBlock(__FILE__, __FUNCTION__, __LINE__))

namespace ZOTO
{

/**
 *	@class		ZLog
 *
 *	@brief		Simple tracing utility used to capture debugging information
 *	@author		Josh Williams
 *	@version	0.2.0
 *	@date		24-Dec-2004
 *
 *	@remarks	Quick and dirty tracing routines to generate decent debugging
 *				information.  The trace files generated by this class will be
 *				indented to help make them more readable.  The indentation
 *				helps denote the level of execution of the library logic.
 *
 *				The facilities provided by this class must be enabled in 2 ways.
 *				First, the macro TRACE_ENABLE must be defined at compile-time.
 *				Secondly, InitTrace() must be called to set the file name and
 *				turn on the tracing facilities.  If either of these are not done, 
 *				no output will be generated.
 */
class _ZuluExport ZLog
{
friend class ZErrorBlock;

protected:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	ZLog();
public:
	virtual ~ZLog();

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	static ZLog&		GetLog();
	int					GetIndent();

public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void				InitTrace(const char *pPgmName);
	void				Timestamps(bool pTimestamps = true);
	void				SetIndent(int pIndent);
#ifdef TRACE_ENABLE
	void				Trace(const char *pMsg, ...);
#else
	void				Trace(const char *pMsg, ...) {if (pMsg) (void)0;}
#endif

public:
	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

protected:
	/*==================================*
	 *             CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *			   INTERNALS			*
	 *==================================*/
	void				WriteRaw(const char *pText) const;
	void 				Write(const char *pText) const;

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	bool				mTraceOn;		/**< whether or not tracing has been enabled
										 	 at run-time */
	std::string			mLogName;		/**< name of the trace file used for output */
	FILE*				mLogHandle;		/**< file-system handle to the trace file */
	int					mIndentLvl;		/**< level of indentation to perform when
										 	 writing trace info	*/
	bool				mLogOpen;		/**< whether or not the log file is open */
	bool				mTimestamps;	/**< whether or not to add timestamps to
											 each line of trace output */
	ZMutex				mLogLock;		/**< Mutex for thread safety. */
};



/********************************************************************
 *																	*
 *							I N L I N E S							*
 *																	*
 ********************************************************************/

/**
 *	Returns the level of indention currently set for the trace log.
 */
inline
int ZLog::GetIndent()
{
	return mIndentLvl;
}

/**
 *	Sets whether or not timestamps should be inserted for each line
 *	of trace output.
 */
inline
void ZLog::Timestamps(bool pTimestamps /*=true*/)
{
	mTimestamps = pTimestamps;
}
/**
 *	Sets the level of indentation to use for tracing.  Never call this function
 *	directly.  It is handled by the ZFuncWrapper class.
 */
inline
void ZLog::SetIndent(int pIndent)
{
	mIndentLvl += pIndent;
}

} // End Namespace

#endif // __ZLOG_H_INCLUDED__

/* vi: set ts=4: */
