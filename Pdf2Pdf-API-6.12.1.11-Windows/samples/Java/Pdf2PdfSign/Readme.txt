How to execute the pdf2pdfsign.java sample:

Via Eclipse:
1) Import present .project file into Eclipse. The source file pdf2pdfsign.java is compiled automatically.
2) Start new Java application and pass arguments of the form <inputPDF> <certificate> <outputPDFA>.

Via Command Shell:
1) Compile the Java source file:
    javac -cp ../../../jar/CNVA.jar;. pdf2pdfsign.java
2) Execute:
    java -cp ../../../jar/CNVA.jar;../../../bin;. pdf2pdfsign <inputPDF> <certificate> <outputPDFA>

Native library: Either way the Pdf2PdfAPI.dll pdfocrpluginAbbyy11.ocr pdfocrpluginAbbyy12.ocr pdfocrpluginService.ocr matching the bitness of your JRE is loaded automatically by the sample.