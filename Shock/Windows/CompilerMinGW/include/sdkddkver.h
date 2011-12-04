/*
 * sdkddkver.h
 *
 *  Created on: 17/10/2010
 *      Author: Adam Griffiths
 */

#ifndef SDKDDKVER_H_
#define SDKDDKVER_H_

// ---------------------------------------------------------------
// Taken from Windows DDK (sdkddkver.h) which is missing
// from MinGW DDK includes

//
// NTDDI version constants
//
#define NTDDI_WIN2K												0x05000000
#define NTDDI_WIN2KSP1											0x05000100
#define NTDDI_WIN2KSP2											0x05000200
#define NTDDI_WIN2KSP3											0x05000300
#define NTDDI_WIN2KSP4											0x05000400

#define NTDDI_WINXP												0x05010000
#define NTDDI_WINXPSP1											0x05010100
#define NTDDI_WINXPSP2											0x05010200
#define NTDDI_WINXPSP3											0x05010300
#define NTDDI_WINXPSP4											0x05010400

#define NTDDI_WS03												0x05020000
#define NTDDI_WS03SP1											0x05020100
#define NTDDI_WS03SP2											0x05020200
#define NTDDI_WS03SP3											0x05020300
#define NTDDI_WS03SP4											0x05020400

#define NTDDI_WIN6												0x06000000
#define NTDDI_WIN6SP1											0x06000100
#define NTDDI_WIN6SP2											0x06000200
#define NTDDI_WIN6SP3											0x06000300
#define NTDDI_WIN6SP4											0x06000400

#define NTDDI_VISTA												NTDDI_WIN6
#define NTDDI_VISTASP1											NTDDI_WIN6SP1
#define NTDDI_VISTASP2											NTDDI_WIN6SP2
#define NTDDI_VISTASP3											NTDDI_WIN6SP3
#define NTDDI_VISTASP4											NTDDI_WIN6SP4

#define NTDDI_LONGHORN											NTDDI_VISTA

#define NTDDI_WS08												NTDDI_WIN6SP1
#define NTDDI_WS08SP2											NTDDI_WIN6SP2
#define NTDDI_WS08SP3											NTDDI_WIN6SP3
#define NTDDI_WS08SP4											NTDDI_WIN6SP4

#define NTDDI_WIN7												0x06010000

// ---------------------------------------------------------------

#endif /* SDKDDKVER_H_ */
