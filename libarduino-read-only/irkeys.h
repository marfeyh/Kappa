/*****************************************************************************
* irkeys.h
* Copyright (C) 2009 Michael Spiceland
*************************************************************************
** defines for the values for a common universal remote set to control
** a Sony tv.
*************************************************************************
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software Foundation, 
**  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
**
*****************************************************************************/

#ifndef _IRKEYS_H
#define _IRKEYS_H

#define REMOTE_DEVICE_SONY_TV000	1
#define REMOTE_DEVICE_SONY_VCR000	2


/********************************************
* buttons verified on dollar store universal 
* with tv set to 000 and vcr set to 000
* and on tv mode
********************************************/
#define REMOTE_BUTTON_POWER		0x15 // china miniremote POWER

#define REMOTE_BUTTON_1			0x00
#define REMOTE_BUTTON_2			0x01
#define REMOTE_BUTTON_3			0x02
#define REMOTE_BUTTON_4			0x03
#define REMOTE_BUTTON_5			0x04
#define REMOTE_BUTTON_6			0x05
#define REMOTE_BUTTON_7			0x06
#define REMOTE_BUTTON_8			0x07
#define REMOTE_BUTTON_9			0x08
#define REMOTE_BUTTON_0			0x09
#define REMOTE_BUTTON_11		0x0B
#define REMOTE_BUTTON_12		0x1d
#define REMOTE_BUTTON_TVCATV		0x38
#define REMOTE_BUTTON_TVVCR		0x25 // also on china remote

#define REMOTE_BUTTON_UP		0x5e
#define REMOTE_BUTTON_DOWN		0x5c
#define REMOTE_BUTTON_LEFT		0x75
#define REMOTE_BUTTON_RIGHT		0x74

#define REMOTE_BUTTON_AUDIO		0x5b
#define REMOTE_BUTTON_MENU		0x60
#define REMOTE_BUTTON_VIDEO		0x7c

#define REMOTE_BUTTON_CHANUP		0x10 // china miniremote CHAN UP
#define REMOTE_BUTTON_CHANDOWN		0x11 // china miniremote CHAN DOWN
#define REMOTE_BUTTON_MUTE		0x14 // china miniremote MUTE
#define REMOTE_BUTTON_VOLUME_UP		0x12 // china miniremote VOL UP
#define REMOTE_BUTTON_VOLUME_DOWN	0x13 // china miniremote VOL DOWN


#define REMOTE_BUTTON_REWIND		0x1b
#define REMOTE_BUTTON_PLAY		0x1a
#define REMOTE_BUTTON_FASTFORWARD	0x1c
#define REMOTE_BUTTON_RECORD		0x1d
#define REMOTE_BUTTON_STOP		0x18
#define REMOTE_BUTTON_PAUSE		0x19

/* old unverified defines from Philips universal in Sony mode */
//#define REMOTE_BUTTON_UP                       0x79
//#define REMOTE_BUTTON_DOWN                     0x7a
//#define REMOTE_BUTTON_LEFT                     0x7b
//#define REMOTE_BUTTON_RIGHT                    0x7c
#define REMOTE_BUTTON_OK                       0x0b
//#define REMOTE_BUTTON_CHANUP                   0x31
//#define REMOTE_BUTTON_CHANDOWN                 0x30
#define REMOTE_BUTTON_PREVCHAN                 0x2c
//#define REMOTE_BUTTON_REWIND                   0x33
//#define REMOTE_BUTTON_FASTFORWARD              0x34
//#define REMOTE_BUTTON_PLAY                     0x32
//#define REMOTE_BUTTON_PLAY                     0x1A
//#define REMOTE_BUTTON_RECORD                   0x37
//#define REMOTE_BUTTON_STOP                     0x38
//#define REMOTE_BUTTON_PAUSE                    0x39
#define REMOTE_BUTTON_CHAPTER_PLUS             0x31
#define REMOTE_BUTTON_CHAPTER_MINUS            0x30
#define REMOTE_BUTTON_QUIT                     0x0e
#define REMOTE_BUTTON_SELECTINFO               0x54
#define REMOTE_BUTTON_GUIDE                    0x1f
#define REMOTE_BUTTON_INPUT                    0x53
#define REMOTE_BUTTON_ENT                      0x0b
#define REMOTE_BUTTON_PIP                      0x0e
#define REMOTE_BUTTON_TOGGLE                   0x1a
#define REMOTE_BUTTON_SUBTITLE                 0x62

/* verified on mini remote from china (add URL here) */
#define REMOTE_BUTTON_AVTV		0x25 // china miniremote AV TV

#endif
