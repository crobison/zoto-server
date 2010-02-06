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
#include "ZDoneRespPacket.h"

/* System Headers */
#if ZULU_PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#elif ZULU_PLATFORM == PLATFORM_MAC
#include <netinet/in.h>
#elif ZULU_PLATFORM == PLATFORM_LINUX
#include <netinet/in.h>
#else
#error Unsupported platform.
#endif

/* Local Headers */

/* Macros */

namespace ZOTO
{

DECLARE_CLASS( "ZDoneRespPacket" )

/* Static Variables */

/********************************************************************
 *																	*
 *          C O N S T R U C T I O N / D E S T R U C T I O N         *
 *																	*
 ********************************************************************/
ZDoneRespPacket::ZDoneRespPacket()
	: ZPacket(ZSP_DONE_RESP), mImageId(""), mReturnCode(0), mReturnText("")
{

}

ZDoneRespPacket::ZDoneRespPacket(const char *pId, ZUSHORT pCode, const char *pText)
	: ZPacket(ZSP_DONE_RESP), mImageId(pId), mReturnCode(pCode), mReturnText(pText)
{

}

ZDoneRespPacket::~ZDoneRespPacket()
{

}

/********************************************************************
 *																	*
 *                        A T T R I B U T E S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                        O P E R A T I O N S                       *
 *																	*
 ********************************************************************/

/*------------------------------------------------------------------*
 *								Build()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Builds a properly formatted done response packet.
 *
 *	@author		Josh Williams
 *	@date		12-Apr-2005
 *
 *	@remarks	Function assumes that the image id, return code and
 *				string have already been Set().
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
ZRESULT ZDoneRespPacket::Build()
{
	BEG_FUNC("Build")(NULL);

	ZSP_DONE_RESP_PACKET	*vDoneResp;

	/*
	 * Build the outgoing FILE_RESPONSE packet
	 */
	mPacketLen  = DONE_RESP_SIZE + mReturnText.length();
	vDoneResp = reinterpret_cast<ZSP_DONE_RESP_PACKET *>(BuildHeader());
	memcpy(vDoneResp->image_id, mImageId.c_str(), ZMIN(mImageId.length(),
			sizeof(vDoneResp->image_id)));
	vDoneResp->return_code = htons(mReturnCode);	
	memcpy(&mRaw[FILE_RESP_SIZE], mReturnText.c_str(), mReturnText.length());

	return END_FUNC(ZERR_SUCCESS);
}

/*------------------------------------------------------------------*
 *								Parse()								*
 *------------------------------------------------------------------*/
/**
 *	@brief		Attempts to convert a raw string received into a
 *				a properly formatted done response packet.
 *
 *	@author		Josh Williams
 *	@date		12-Apr-2005
 *
 *	@param		pRaw
 *					The raw bytes received.
 *	@param		pSize
 *					Number of bytes received.
 */
/*------------------------------------------------------------------*
 * MODIFICATIONS													*
 *	Date		Description							Author			*
 * ===========	==================================	===============	*
 *																	*
 *------------------------------------------------------------------*/
ZRESULT ZDoneRespPacket::Parse(ZBYTE *pRaw, int pSize)
{
	BEG_FUNC("Parse")("%p, %d", pRaw, pSize);

	ZSP_DONE_RESP_PACKET	*vDoneResp;
	ZUINT					vTextLen;
	char					vBuffer[256];

	vDoneResp	= reinterpret_cast<ZSP_DONE_RESP_PACKET*>(pRaw);
	mPayloadLen	= ntohs(vDoneResp->header.payload_length);
	mPacketLen	= mPayloadLen + HEADER_SIZE;
	vTextLen	= mPacketLen - FILE_RESP_SIZE;

	/*
	 * Populate the variables.
	 */
	memset(vBuffer, '\0', sizeof(vBuffer));
	memcpy(vBuffer, vDoneResp->image_id, sizeof(vDoneResp->image_id));
	mImageId = vBuffer;
	mReturnCode = ntohs(vDoneResp->return_code);
	memcpy(vBuffer, &pRaw[DONE_RESP_SIZE], vTextLen);
	vBuffer[vTextLen] = '\0';
	mReturnText = vBuffer;

	ZTRACE(" *** Parsed Done Response ***\n");
	ZTRACE("Image Id:    %s\n", mImageId.c_str());
	ZTRACE("Return code: %d\n", mReturnCode);
	ZTRACE("Return text: %s\n", mReturnText.c_str());

	return END_FUNC(ZERR_SUCCESS);
}

/********************************************************************
 *																	*
 *                          O P E R A T O R S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          C A L L B A C K S                       *
 *																	*
 ********************************************************************/

/********************************************************************
 *																	*
 *                          I N T E R N A L S                       *
 *																	*
 ********************************************************************/

} // End Namespace

/* vi: set ts=4: */
