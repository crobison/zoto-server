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
#if !defined(__ZFLAGPACKET_H_INCLUDED__)
#define __ZFLAGPACKET_H_INCLUDED__

#include "ZPlatform.h"

/* System Headers */
#include <string>

/* Local Headers */
#include "ZPacket.h"
#include "ZTypes.h"

/* Macros */

namespace ZOTO
{

/**
 *  @class      ZFlagPacket
 *  @brief      Sent to the server to determine if an image is needed.
 *  @author     Josh Williams
 *  @version    0.1.0
 */
class _ZuluExport ZFlagPacket : public ZPacket
{
public:
	/*==================================*
	 *	   CONSTRUCTION/DESTRUCTION		*
	 *==================================*/
	ZFlagPacket();
	ZFlagPacket(const char *pId, int pFormat, ZULONG pSize, const char *pDate,
					const char *pName);
	virtual ~ZFlagPacket();

public:
	/*==================================*
	 *			  ATTRIBUTES			*
	 *==================================*/
	const char*			GetImageId() const;
	int					GetImageFormat() const;
	ZULONG				GetImageSize() const;
	const char*			GetImageDate() const;
	const char*			GetImageName() const;

public:
	/*==================================*
	 *			  OPERATIONS			*
	 *==================================*/
	void				SetImageId(const char *pId);
	void				SetImageFormat(int pFormat);
	void				SetImageSize(ZULONG pSize);
	void				SetImageDate(const char *pDate);
	void				SetImageName(const char *pName);
	ZRESULT				Build();
	ZRESULT				Parse(ZBYTE *pRaw, int pSize);

public:
	/*==================================*
	 *			   OPERATORS			*
	 *==================================*/

protected:
	/*==================================*
	 *			   CALLBACKS			*
	 *==================================*/

private:
	/*==================================*
	 *			   INTERNALS			*
	 *==================================*/

private:
	/*==================================*
	 *             VARIABLES            *
	 *==================================*/
	std::string			mImageId;
	int					mImageFormat;
	ZULONG				mImageSize;
	std::string			mImageDate;
	std::string			mImageName;
};



/********************************************************************
 *																	*
 *							I N L I N E S							*
 *																	*
 ********************************************************************/
/**
 *	Returns the Id (MD5 hash) of the image.
 */
inline
const char* ZFlagPacket::GetImageId() const
{
	return mImageId.c_str();
}

/**
 *	Returns the format (jpeg, gif, etc) of the image.
 */
inline
int ZFlagPacket::GetImageFormat() const
{
	return mImageFormat;
}

/**
 *	Returns the size (in bytes) of the image file.
 */
inline
ZULONG ZFlagPacket::GetImageSize() const
{
	return mImageSize;
}

/**
 *	Returns the date (as an unformatted string) for the image.
 */
inline
const char*	ZFlagPacket::GetImageDate() const
{
	return mImageDate.c_str();
}

/**
 *	Returns the name (short) of the image.
 */
inline
const char* ZFlagPacket::GetImageName() const
{
	return mImageName.c_str();
}

/**
 *	Sets the id (MD5 hash) for this image.
 */
inline
void ZFlagPacket::SetImageId(const char *pId)
{
	if (pId)
		mImageId = pId;
}

/**
 *	Sets the format (jpeg, gif, etc) of the image.
 */
inline
void ZFlagPacket::SetImageFormat(int pFormat)
{
	mImageFormat = pFormat;
}

/**
 *	Sets the size (in bytes) of the image.
 */
inline
void ZFlagPacket::SetImageSize(ZULONG pSize)
{
	mImageSize = pSize;
}

/**
 *	Sets the date (unformatted: YYYYMMDDhhmmss) for the image.
 */
inline
void ZFlagPacket::SetImageDate(const char *pDate)
{
	if (pDate)
		mImageDate = pDate;
}

/**
 *	Sets the name (short) for the image.
 */
inline
void ZFlagPacket::SetImageName(const char *pName)
{
	if (pName)
		mImageName = pName;
}

} // End Namespace

#endif // __ZFLAGPACKET_H_INCLUDED__

/* vi: set ts=4: */
