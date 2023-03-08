/**************************************************************************
*
* Copyright (C) 2012 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************/
#ifndef BITS_H
#define BITS_H

/********************************************************************
* Bit Masks
*********************************************************************/
#define BAC_BIT(x)        (1<<(x))
#define BAC_BIT0            (0x01)
#define BAC_BIT1            (0x02)
#define BAC_BIT2            (0x04)
#define BAC_BIT3            (0x08)
#define BAC_BIT4            (0x10)
#define BAC_BIT5            (0x20)
#define BAC_BIT6            (0x40)
#define BAC_BIT7            (0x80)
#define BAC_BIT8          (0x0100)
#define BAC_BIT9          (0x0200)
#define BAC_BIT10         (0x0400)
#define BAC_BIT11         (0x0800)
#define BAC_BIT12         (0x1000)
#define BAC_BIT13         (0x2000)
#define BAC_BIT14         (0x4000)
#define BAC_BIT15         (0x8000)
#define BAC_BIT16       (0x010000UL)
#define BAC_BIT17       (0x020000UL)
#define BAC_BIT18       (0x040000UL)
#define BAC_BIT19       (0x080000UL)
#define BAC_BIT20       (0x100000UL)
#define BAC_BIT21       (0x200000UL)
#define BAC_BIT22       (0x400000UL)
#define BAC_BIT23       (0x800000UL)
#define BAC_BIT24     (0x01000000UL)
#define BAC_BIT25     (0x02000000UL)
#define BAC_BIT26     (0x04000000UL)
#define BAC_BIT27     (0x08000000UL)
#define BAC_BIT28     (0x10000000UL)
#define BAC_BIT29     (0x20000000UL)
#define BAC_BIT30     (0x40000000UL)
#define BAC_BIT31     (0x80000000UL)

/* a=register, b=bit number to act upon 0-n */
#define BAC_BIT_SET(a,b) ((a) |= (1<<(b)))
#define BAC_BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BAC_BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BAC_BIT_CHECK(a,b) ((a) & (1<<(b)))

/* x=target variable, y=mask */
#define BAC_BITMASK_SET(x,y) ((x) |= (y))
#define BAC_BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BAC_BITMASK_FLIP(x,y) ((x) ^= (y))
#define BAC_BITMASK_CHECK(x,y) ((x) & (y))

#ifndef _BV
#define _BV(x) (1<<(x))
#endif

#endif
