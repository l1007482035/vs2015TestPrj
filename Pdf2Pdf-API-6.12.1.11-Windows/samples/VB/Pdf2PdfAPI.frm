VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   BackColor       =   &H00FFFFFF&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "PDF to PDF/A Converter Sample"
   ClientHeight    =   5685
   ClientLeft      =   4455
   ClientTop       =   3270
   ClientWidth     =   8355
   Icon            =   "Pdf2PdfAPI.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5685
   ScaleWidth      =   8355
   Begin VB.Frame Frame2 
      BackColor       =   &H00E2D1AE&
      BorderStyle     =   0  'None
      Height          =   7410
      Left            =   0
      TabIndex        =   19
      Top             =   0
      Width           =   1335
      Begin VB.Label Label3 
         BackColor       =   &H00D7B67A&
         Caption         =   " OUTPUT"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00996600&
         Height          =   315
         Left            =   0
         TabIndex        =   23
         Top             =   1680
         Width           =   1335
      End
      Begin VB.Label Label13 
         BackColor       =   &H00D7B67A&
         Caption         =   " CONVERT"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00996600&
         Height          =   315
         Left            =   0
         TabIndex        =   22
         Top             =   4800
         Width           =   1335
      End
      Begin VB.Label Label11 
         BackColor       =   &H00D7B67A&
         Caption         =   " SETTINGS"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00996600&
         Height          =   315
         Left            =   0
         TabIndex        =   21
         Top             =   2640
         Width           =   1335
      End
      Begin VB.Label Label10 
         BackColor       =   &H00D7B67A&
         Caption         =   " INPUT"
         BeginProperty Font 
            Name            =   "Verdana"
            Size            =   8.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         ForeColor       =   &H00996600&
         Height          =   315
         Left            =   0
         TabIndex        =   20
         Top             =   720
         Width           =   1335
      End
   End
   Begin VB.TextBox TextLogo 
      BackColor       =   &H006699FF&
      BorderStyle     =   0  'None
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      TabStop         =   0   'False
      Text            =   " 3-Heights PDF to PDF/A Converter"
      Top             =   120
      Width           =   6855
   End
   Begin VB.Frame Frame14 
      Appearance      =   0  'Flat
      BackColor       =   &H00996600&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   895
      Left            =   1440
      TabIndex        =   17
      Top             =   600
      Width           =   6775
      Begin VB.Frame Frame3 
         Appearance      =   0  'Flat
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   855
         Left            =   20
         TabIndex        =   18
         Top             =   20
         Width           =   6735
         Begin VB.TextBox txtPW 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   285
            Left            =   2280
            TabIndex        =   4
            Top             =   480
            Width           =   3855
         End
         Begin VB.TextBox txtInput 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   285
            Left            =   2280
            TabIndex        =   2
            Top             =   120
            Width           =   3855
         End
         Begin VB.CommandButton BrowseInFile 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   6240
            TabIndex        =   3
            Top             =   60
            Width           =   375
         End
         Begin MSComDlg.CommonDialog fileDialog 
            Left            =   6120
            Top             =   240
            _ExtentX        =   847
            _ExtentY        =   847
            _Version        =   393216
         End
         Begin VB.Label Label16 
            BackStyle       =   0  'Transparent
            Caption         =   "Password (optional)"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   27
            Top             =   480
            Width           =   2055
         End
         Begin VB.Label Label15 
            BackStyle       =   0  'Transparent
            Caption         =   "Input PDF"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   26
            Top             =   120
            Width           =   2055
         End
      End
   End
   Begin VB.Frame Frame12 
      Appearance      =   0  'Flat
      BackColor       =   &H00996600&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   895
      Left            =   1440
      TabIndex        =   15
      Top             =   1560
      Width           =   6775
      Begin VB.Frame Frame5 
         Appearance      =   0  'Flat
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   855
         Left            =   20
         TabIndex        =   16
         Top             =   20
         Width           =   6735
         Begin VB.CommandButton BrowseLogFile 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   6240
            TabIndex        =   31
            Top             =   450
            Width           =   375
         End
         Begin VB.TextBox txtLogfile 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   285
            Left            =   2280
            TabIndex        =   30
            Text            =   "C:\temp\log.txt"
            Top             =   480
            Width           =   3855
         End
         Begin VB.TextBox txtOutput 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   285
            Left            =   2280
            TabIndex        =   5
            Top             =   120
            Width           =   3855
         End
         Begin VB.CommandButton BrowseOutFile 
            Caption         =   "..."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   6240
            TabIndex        =   6
            Top             =   50
            Width           =   375
         End
         Begin VB.Label Label19 
            BackStyle       =   0  'Transparent
            Caption         =   "Log File (.txt)"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   32
            Top             =   480
            Width           =   2055
         End
         Begin VB.Label Label6 
            BackStyle       =   0  'Transparent
            Caption         =   "Output PDF/A"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   28
            Top             =   120
            Width           =   2055
         End
      End
   End
   Begin VB.Frame Frame9 
      Appearance      =   0  'Flat
      BackColor       =   &H00996600&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   855
      Left            =   1440
      TabIndex        =   13
      Top             =   4680
      Width           =   6775
      Begin VB.Frame Frame4 
         Appearance      =   0  'Flat
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         ForeColor       =   &H80000008&
         Height          =   815
         Left            =   20
         TabIndex        =   14
         Top             =   20
         Width           =   6735
         Begin VB.CheckBox chkAlways 
            BackColor       =   &H00FFFFFF&
            Caption         =   "Convert Always"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   150
            TabIndex        =   33
            Top             =   120
            Value           =   1  'Checked
            Width           =   1935
         End
         Begin VB.CommandButton Convert 
            Caption         =   "Convert"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   375
            Left            =   5640
            TabIndex        =   9
            Top             =   120
            Width           =   975
         End
         Begin VB.Label Label20 
            BackStyle       =   0  'Transparent
            Caption         =   "Convert even if there are errors in the analysis."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   -1  'True
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808080&
            Height          =   255
            Left            =   150
            TabIndex        =   34
            Top             =   480
            Width           =   4215
         End
      End
   End
   Begin VB.Frame Frame13 
      Appearance      =   0  'Flat
      BackColor       =   &H00996600&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   1995
      Left            =   1440
      TabIndex        =   1
      Top             =   2520
      Width           =   6775
      Begin VB.Frame Frame6 
         Appearance      =   0  'Flat
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         Caption         =   "Quality is only affecting JPEG and JPEG 2000. The Compression Type can only be set for TIFF images."
         ForeColor       =   &H80000008&
         Height          =   1965
         Left            =   10
         TabIndex        =   10
         Top             =   10
         Width           =   6735
         Begin VB.TextBox txtReason 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   315
            Left            =   2280
            TabIndex        =   8
            Text            =   "I am the author of the document."
            Top             =   1380
            Width           =   3855
         End
         Begin VB.TextBox txtName 
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   315
            Left            =   2280
            TabIndex        =   7
            Top             =   480
            Width           =   3855
         End
         Begin VB.Line Line1 
            BorderWidth     =   2
            X1              =   120
            X2              =   6540
            Y1              =   360
            Y2              =   360
         End
         Begin VB.Label Label1 
            BackStyle       =   0  'Transparent
            Caption         =   "Digital Signature"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   700
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   29
            Top             =   120
            Width           =   1815
         End
         Begin VB.Label Label14 
            BackStyle       =   0  'Transparent
            Caption         =   "The certificate name corresponds to the value ""Issued To"". See ""cnva.pdf""."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   -1  'True
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808080&
            Height          =   255
            Left            =   120
            TabIndex        =   25
            Top             =   1080
            Width           =   6615
         End
         Begin VB.Label Label12 
            BackStyle       =   0  'Transparent
            Caption         =   "In order to sign a PDF document, a valid certificate name must be provided."
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   8.25
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   -1  'True
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H00808080&
            Height          =   255
            Left            =   120
            TabIndex        =   24
            Top             =   840
            Width           =   6615
         End
         Begin VB.Label Label4 
            BackStyle       =   0  'Transparent
            Caption         =   "Signature Reason"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   12
            Top             =   1380
            Width           =   1815
         End
         Begin VB.Label Label2 
            BackStyle       =   0  'Transparent
            Caption         =   "Certificate Name"
            BeginProperty Font 
               Name            =   "Verdana"
               Size            =   9
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            Height          =   255
            Left            =   120
            TabIndex        =   11
            Top             =   525
            Width           =   1815
         End
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' This is a Visual Basic 6 sample for the 3-Heights PDF to PDF/A
' Converter API from PDF Tools AG. (www.pdf-tools.com)
'
' Copyright (C) 2007-2015 PDF Tools AG, Switzerland
' Permission to use, copy, modify, and distribute this
' software and its documentation for any purpose and without
' fee is hereby granted, provided that the above copyright
' notice appear in all copies and that both that copyright
' notice and this permission notice appear in supporting
' documentation.  This software is provided "as is" without
' express or implied warranty.


Dim ProfilePath As String

Private Sub Convert_Click()
    Dim conv As New Pdf2PdfAPI
    Dim done As Boolean

    Dim sig As New PdfSignature
    
    If Not txtName.Text = "" Then
        sig.Name = txtName.Text
        sig.Reason = txtReason.Text
        conv.AddSignature sig
    End If
    
    conv.ConvertAlways = chkAlways.Value
    'conv.ReportDetails = True
    conv.ReportSummary = True
    
    conv.Compliance = ePDFA2u
    
    If Not conv.Convert(txtInput.Text, txtPW.Text, txtOutput.Text, txtLogfile.Text) Then
        MsgBox "Error converting document: " & conv.ErrorMessage
    Else
        MsgBox "File converted successfully."
    End If
    Set conv = Nothing
    Set sig = Nothing
End Sub


Private Sub BrowseInFile_Click()
    fileDialog.FileName = txtInput.Text
    fileDialog.ShowOpen
    txtInput.Text = fileDialog.FileName
End Sub

Private Sub BrowseOutFile_Click()
    fileDialog.FileName = txtOutput.Text
    fileDialog.ShowSave
    txtOutput.Text = fileDialog.FileName
End Sub

Private Sub BrowseLogFile_Click()
    fileDialog.FileName = txtLogfile.Text
    fileDialog.ShowSave
    txtLogfile.Text = fileDialog.FileName
End Sub


Private Sub Form_Load()
    ' Check license
    Dim conv As New Pdf2PdfAPI
    If Not conv.LicenseIsValid Then
        MsgBox "No valid license found."
        Unload Me
        End
    End If

End Sub

