﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34209
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace Pdf2PdfUI.Properties {
    using System;
    
    
    /// <summary>
    ///   A strongly-typed resource class, for looking up localized strings, etc.
    /// </summary>
    // This class was auto-generated by the StronglyTypedResourceBuilder
    // class via a tool like ResGen or Visual Studio.
    // To add or remove a member, edit your .ResX file then rerun ResGen
    // with the /str option, or rebuild your VS project.
    [global::System.CodeDom.Compiler.GeneratedCodeAttribute("System.Resources.Tools.StronglyTypedResourceBuilder", "4.0.0.0")]
    [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
    [global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    internal class Resources {
        
        private static global::System.Resources.ResourceManager resourceMan;
        
        private static global::System.Globalization.CultureInfo resourceCulture;
        
        [global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal Resources() {
        }
        
        /// <summary>
        ///   Returns the cached ResourceManager instance used by this class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Resources.ResourceManager ResourceManager {
            get {
                if (object.ReferenceEquals(resourceMan, null)) {
                    global::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager("Pdf2PdfUI.Properties.Resources", typeof(Resources).Assembly);
                    resourceMan = temp;
                }
                return resourceMan;
            }
        }
        
        /// <summary>
        ///   Overrides the current thread's CurrentUICulture property for all
        ///   resource lookups using this strongly typed resource class.
        /// </summary>
        [global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]
        internal static global::System.Globalization.CultureInfo Culture {
            get {
                return resourceCulture;
            }
            set {
                resourceCulture = value;
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Could not convert document..
        /// </summary>
        internal static string MsgConvertErr {
            get {
                return ResourceManager.GetString("MsgConvertErr", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to 
        ///
        ///In order to resolve this issue, the DLL must be found at execution time. This can be ensured by either:
        ///- adding this DLL as an existing item to the project and set its property “Copy to output directory” to “Copy if newer”, or
        ///- adding the directory where the DLL resides to the environment variable “PATH”, or
        ///- copying it to the output directory of the project, e.g. to bin/Debug.
        ///Also, this DLL shall be of the same version as the PDF Tools&apos; .NET assemblies..
        /// </summary>
        internal static string MsgDLLNotFound {
            get {
                return ResourceManager.GetString("MsgDLLNotFound", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to DLL Not Found.
        /// </summary>
        internal static string MsgDLLNotFoundTitle {
            get {
                return ResourceManager.GetString("MsgDLLNotFoundTitle", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to File not found: .
        /// </summary>
        internal static string MsgFileNotFound {
            get {
                return ResourceManager.GetString("MsgFileNotFound", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to Please select and input and output PDF file..
        /// </summary>
        internal static string MsgNoFileSelected {
            get {
                return ResourceManager.GetString("MsgNoFileSelected", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Icon similar to (Icon).
        /// </summary>
        internal static System.Drawing.Icon pdf_tools {
            get {
                object obj = ResourceManager.GetObject("pdf_tools", resourceCulture);
                return ((System.Drawing.Icon)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to uswebcoatedswop.icc.
        /// </summary>
        internal static string strCMYKProfile {
            get {
                return ResourceManager.GetString("strCMYKProfile", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to \system32\spool\drivers\color\.
        /// </summary>
        internal static string strColorProfilePath {
            get {
                return ResourceManager.GetString("strColorProfilePath", resourceCulture);
            }
        }
        
        /// <summary>
        ///   Looks up a localized resource of type System.Drawing.Bitmap.
        /// </summary>
        internal static System.Drawing.Bitmap stripe_gray {
            get {
                object obj = ResourceManager.GetObject("stripe_gray", resourceCulture);
                return ((System.Drawing.Bitmap)(obj));
            }
        }
        
        /// <summary>
        ///   Looks up a localized string similar to srgb color space profile.icm.
        /// </summary>
        internal static string strsRGBProfile {
            get {
                return ResourceManager.GetString("strsRGBProfile", resourceCulture);
            }
        }
    }
}
