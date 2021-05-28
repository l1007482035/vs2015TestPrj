// This file is autogenerated: please see the codegen template "Options"
namespace pdftron{ namespace PDF{ 

inline CADConvertOptions::CADConvertOptions()
	: m_obj_set()
	, m_dict()
{
	m_dict = m_obj_set.CreateDict();
}

inline CADConvertOptions::~CADConvertOptions()
{
}


inline bool CADConvertOptions::GetAllowThinLines()
{
	SDF::Obj found = m_dict.FindObj("Thin-lines");
	if(found.IsValid())
	{
		return (found.GetBool());
	}
	return (true);
}

inline CADConvertOptions& CADConvertOptions::SetAllowThinLines(bool value)
{
	OptionsBase::PutBool(m_dict, "Thin-lines", (value));
	return *this;
}


inline bool CADConvertOptions::GetAutoRotate()
{
	SDF::Obj found = m_dict.FindObj("Auto-rotate");
	if(found.IsValid())
	{
		return (found.GetBool());
	}
	return (false);
}

inline CADConvertOptions& CADConvertOptions::SetAutoRotate(bool value)
{
	OptionsBase::PutBool(m_dict, "Auto-rotate", (value));
	return *this;
}


inline ColorPt CADConvertOptions::GetBackgroundColor()
{
	SDF::Obj found = m_dict.FindObj("Background-color");
	if(found.IsValid())
	{
		return OptionsBase::ColorPtFromNumber(found.GetNumber());
	}
	return OptionsBase::ColorPtFromNumber(0xFFFFFFFF);
}

inline CADConvertOptions& CADConvertOptions::SetBackgroundColor(ColorPt value)
{
	OptionsBase::PutNumber(m_dict, "Background-color", OptionsBase::ColorPtToNumber(value));
	return *this;
}

inline CADConvertOptions& CADConvertOptions::SetColorMode(const UString& value)
{
	OptionsBase::PutText(m_dict, "ColorMode", (value));
	return *this;
}


inline double CADConvertOptions::GetPageHeight()
{
	SDF::Obj found = m_dict.FindObj("Page-height");
	if(found.IsValid())
	{
		return (found.GetNumber());
	}
	return (594.0);
}

inline CADConvertOptions& CADConvertOptions::SetPageHeight(double value)
{
	OptionsBase::PutNumber(m_dict, "Page-height", (value));
	return *this;
}


inline double CADConvertOptions::GetPageWidth()
{
	SDF::Obj found = m_dict.FindObj("Page-width");
	if(found.IsValid())
	{
		return (found.GetNumber());
	}
	return (840.0);
}

inline CADConvertOptions& CADConvertOptions::SetPageWidth(double value)
{
	OptionsBase::PutNumber(m_dict, "Page-width", (value));
	return *this;
}


inline double CADConvertOptions::GetRasterDPI()
{
	SDF::Obj found = m_dict.FindObj("Raster-dpi");
	if(found.IsValid())
	{
		return (found.GetNumber());
	}
	return (72.0);
}

inline CADConvertOptions& CADConvertOptions::SetRasterDPI(double value)
{
	OptionsBase::PutNumber(m_dict, "Raster-dpi", (value));
	return *this;
}


inline CADConvertOptions& CADConvertOptions::AddSheets(const UString& value)
{
	OptionsBase::PushBackText(m_dict, "Sheets", (value));
	return *this;
}


inline SDF::Obj& CADConvertOptions::GetInternalObj()
{
	return m_dict;
}

}
}