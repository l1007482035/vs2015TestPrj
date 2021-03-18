
/****************************************************************************
 *
 * File:            pdfcommondecl.h
 *
 * Description:     The include file for native C interfaces using PDF common objects.
 *
 * Author:          Dr. Hans Bärfuss, PDF Tools AG   
 * 
 * Copyright:       Copyright (C) 2001 - 2012 PDF Tools AG, Switzerland
 *                  All rights reserved.
 *                  
 ***************************************************************************/

#ifndef _PDFCOMMONDECL_INCLUDED
#define _PDFCOMMONDECL_INCLUDED

#ifndef __EMSCRIPTEN__

typedef struct TPDFRect
{
    float   m_fRect[4];
} TPDFRect;


/** structure representing a date and time of day (e.g. CreationDate) */
typedef struct TPDFDate
{
    short iYear;   /**< year 1900..2100 */
    short iMonth;  /**< 1..12 */
    short iDay;    /**< 1..31 */
    short iHour;   /**< 0..23 */
    short iMinute; /**< 0..59 */
    short iSecond; /**< 0..59 */
    signed short iUtcOffset; /**< time zone information, offset to UTC in minutes */
} TPDFDate;


/** The page layout shall be used when the document is opened. */
typedef enum TPDFPageLayout
{
    ePageLayoutSinglePage     = 0,  /* Display one page at a time. */
    ePageLayoutOneColumn      = 1,  /* Display the pages in one column. */
    ePageLayoutTwoColumnLeft  = 2,  /* Display the pages in two columns, with oddnumbered pages on the left. */
    ePageLayoutTwoColumnRight = 3,  /* Display the pages in two columns, with oddnumbered pages on the right. */
    ePageLayoutTwoPageLeft    = 4,  /* (PDF 1.5) Display the pages two at a time, with odd-numbered pages on the left. */
    ePageLayoutTwoPageRight   = 5   /* (PDF 1.5) Display the pages two at a time, with odd-numbered pages on the right. */
} TPDFPageLayout;


/** The page mode specifies how the document shall be displayed when opened. */
typedef enum TPDFPageMode
{
    ePageModeUseNone        = 0,    /* Neither document outline nor thumbnail images visible. */
    ePageModeUseOutlines    = 1,    /* Document outline visible. */
    ePageModeUseThumbs      = 2,    /* Thumbnail images visible. */
    ePageModeFullScreen     = 3,    /* Full-screen mode, with no menu bar, window controls, or any other window visible. */
    ePageModeUseOC          = 4,    /* (PDF 1.5) Optional content group panel visible. */
    ePageModeUseAttachments = 5     /* (PDF 1.6) Attachments panel visible. */
} TPDFPageMode;


/** The destination mode specifies a particular view of the document including the page, the location on the page and the zoom factor.
  * Depending on the mode, between 0 and 4 parameters are required to define the destination.
  */
typedef enum TPDFDestMode
{
    eDestModeXYZ   = 0,             /* "XYZ"      left, top, zoom           The upper left corner of the view is positioned at the coordinate (left, top) with the given zoom factor.*/
    eDestModeFit   = 1,             /* "Fit"                                The view is such that the whole page is visible.*/
    eDestModeFitH  = 2,             /* "FitH"     top                       The view is top-aligned with top and shows the whole page width.*/
    eDestModeFitV  = 3,             /* "FitV"     left                      The view is left-aligned with left and shows the whole page height.*/
    eDestModeFitR  = 4,             /* "FitR"     left, bottom, right, top  The view contains the rectangle specified the two coordinates (left, bottom) and (right, bottom).*/
    eDestModeFitB  = 5,             /* "FitB"                               The view is such that the page's bounding box is visible.*/
    eDestModeFitBH = 6,             /* "FitBH"    top                       The view is top-aligned with top and shows the whole width of the page's bounding box.*/
    eDestModeFitBV = 7              /* "FitBV"    left                      The view is left-aligned with left and shows the whole height of the page's bounding box.*/
} TPDFDestMode;


#endif //__EMSCRIPTEN__
#endif //_PDFCOMMONDECL_INCLUDED
