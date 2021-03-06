// This file is autogenerated: please see the codegen template "Options"
#ifndef PDFTRON_H_CPPPDFOfficeToPDFOptions
#define PDFTRON_H_CPPPDFOfficeToPDFOptions

#include <PDF/ConversionOptions.h>

namespace pdftron{ namespace PDF{ 

class OfficeToPDFOptions: public ConversionOptions
{
public:
	OfficeToPDFOptions();
	~OfficeToPDFOptions();

	
	/**
	* Gets the value ApplyPageBreaksToSheet from the options object
	* Whether we should split Excel workheets into pages so that the output resembles print output.
	* @ return a bool, the current value for ApplyPageBreaksToSheet.
	*/
	bool GetApplyPageBreaksToSheet();

	/**
	* Sets the value for ApplyPageBreaksToSheet in the options object
	* Whether we should split Excel workheets into pages so that the output resembles print output.
	* @param value: the new value for ApplyPageBreaksToSheet
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetApplyPageBreaksToSheet(bool value);

	
	/**
	* Gets the value DisplayChangeTracking from the options object
	* If this option is true, will display office change tracking markup present in the document (i.e, red strikethrough of deleted content and underlining of new content). Otherwise displays the resolved document content, with no markup. Defaults to true.
	* @ return a bool, the current value for DisplayChangeTracking.
	*/
	bool GetDisplayChangeTracking();

	/**
	* Sets the value for DisplayChangeTracking in the options object
	* If this option is true, will display office change tracking markup present in the document (i.e, red strikethrough of deleted content and underlining of new content). Otherwise displays the resolved document content, with no markup. Defaults to true.
	* @param value: the new value for DisplayChangeTracking
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetDisplayChangeTracking(bool value);

	
	/**
	* Gets the value ExcelDefaultCellBorderWidth from the options object
	* Cell border width for table cells that would normally be drawn with no border. In units of points. Can be used to achieve a similar effect to the "show gridlines" display option within Microsoft Excel.
	* @ return a double, the current value for ExcelDefaultCellBorderWidth.
	*/
	double GetExcelDefaultCellBorderWidth();

	/**
	* Sets the value for ExcelDefaultCellBorderWidth in the options object
	* Cell border width for table cells that would normally be drawn with no border. In units of points. Can be used to achieve a similar effect to the "show gridlines" display option within Microsoft Excel.
	* @param value: the new value for ExcelDefaultCellBorderWidth
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetExcelDefaultCellBorderWidth(double value);

	
	/**
	* Gets the value ExcelMaxAllowedCellCount from the options object
	* Cell border width for table cells that would normally be drawn with no border. In units of points. Can be used to achieve a similar effect to the "show gridlines" display option within Microsoft Excel.
	* @ return a UInt32, the current value for ExcelMaxAllowedCellCount.
	*/
	UInt32 GetExcelMaxAllowedCellCount();

	/**
	* Sets the value for ExcelMaxAllowedCellCount in the options object
	* Cell border width for table cells that would normally be drawn with no border. In units of points. Can be used to achieve a similar effect to the "show gridlines" display option within Microsoft Excel.
	* @param value: the new value for ExcelMaxAllowedCellCount
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetExcelMaxAllowedCellCount(UInt32 value);

	
	/**
	* Gets the value LayoutResourcesPluginPath from the options object
	* The path at which the pdftron-provided font resource plugin resides
	* @ return a UString, the current value for LayoutResourcesPluginPath.
	*/
	UString GetLayoutResourcesPluginPath();

	/**
	* Sets the value for LayoutResourcesPluginPath in the options object
	* The path at which the pdftron-provided font resource plugin resides
	* @param value: the new value for LayoutResourcesPluginPath
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetLayoutResourcesPluginPath(UString value);

	
	/**
	* Gets the value Locale from the options object
	* ISO 639-1 code of the current system locale. For example: 'en-US', 'ar-SA', 'de-DE', etc.
	* @ return a UString, the current value for Locale.
	*/
	UString GetLocale();

	/**
	* Sets the value for Locale in the options object
	* ISO 639-1 code of the current system locale. For example: 'en-US', 'ar-SA', 'de-DE', etc.
	* @param value: the new value for Locale
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetLocale(UString value);

	
	/**
	* Gets the value ResourceDocPath from the options object
	* The path at which a .docx resource document resides
	* @ return a UString, the current value for ResourceDocPath.
	*/
	UString GetResourceDocPath();

	/**
	* Sets the value for ResourceDocPath in the options object
	* The path at which a .docx resource document resides
	* @param value: the new value for ResourceDocPath
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetResourceDocPath(UString value);

	
	/**
	* Gets the value SmartSubstitutionPluginPath from the options object
	* The path at which the pdftron-provided font resource plugin resides
	* @ return a UString, the current value for SmartSubstitutionPluginPath.
	*/
	UString GetSmartSubstitutionPluginPath();

	/**
	* Sets the value for SmartSubstitutionPluginPath in the options object
	* The path at which the pdftron-provided font resource plugin resides
	* @param value: the new value for SmartSubstitutionPluginPath
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetSmartSubstitutionPluginPath(UString value);

	
	/**
	* Gets the value TemplateParamsJson from the options object
	* JSON string representing the data to be merged into a PDFTron office template
	* @ return a UString, the current value for TemplateParamsJson.
	*/
	UString GetTemplateParamsJson();

	/**
	* Sets the value for TemplateParamsJson in the options object
	* JSON string representing the data to be merged into a PDFTron office template
	* @param value: the new value for TemplateParamsJson
	* @return this object, for call chaining
	*/
	OfficeToPDFOptions& SetTemplateParamsJson(UString value);

	
};

}
}

#include "../Impl/OfficeToPDFOptions.inl"
#endif // PDFTRON_H_CPPPDFOfficeToPDFOptions
