<%@ Language=VBScript %>
<%
    dim conv
    dim fileNameIn, fileNameOut, logName

    on error resume next

    set conv    = Server.CreateObject("PDF2PDFAPI.Pdf2Pdf")
    
    if Err.Number <> 0 then
        Response.Write "<p>"
        Response.Write "Failed to load Pdf2PdfAPI.dll:"
        Response.Write "<ul>"
        Response.Write "<li>Register with regsvr32.</li>"
        Response.Write "<li>Make sure that it resides in an executable directory.</li>"
        Response.Write "<li>Make sure you have the correct bit-ness (32bit vs. 64bit).</li>"
        Response.Write "</ul>"
        Response.Write "</p>"
    end if

    If not conv.LicenseIsValid then
        Response.Write "<p>"
        Response.Write "No valid license found."
        Response.Write "</p>"
    End if

    fileNameIn  = "http://www.pdf-tools.com/public/downloads/manuals/Pdf2PdfAPI.pdf"
    fileNameOut = "C:\temp\output.pdf"
    logName     = "C:\temp\output.log"
    
    conv.ReportSummary = True
    if not conv.Convert(fileNameIn, "", fileNameOut, logName) then
        Response.Write "<p>"
        Response.Write "Failed to convert file.<br>"
        Response.Write " * Error: " & conv.ErrorMessage
        Response.Write "</p>"
    else
        Response.Write "<p>"
        Response.Write "File converted successfully."
        Response.Write "</p>"
    end if
    
    Response.Write "<p><ul>"
    Response.Write "<li>Input File  : <a href='" & fileNameIn & "'>" &  fileNameIn & "</a></li>"
    Response.Write "<li>Output File : <a href='" & fileNameOut & "'>" &  fileNameOut & "</a></li>"
    Response.Write "<li>Log File    : <a href='" & logName & "'>" &  logName & "</a></li>"
    Response.Write "</ul></p>"

%>