#include "PaintToolFileIO.h"

paint_tool::PaintToolFileIO::PaintToolFileIO() {
	//
}

paint_tool::PaintToolFileIO::~PaintToolFileIO() {
	//
}

const COMDLG_FILTERSPEC paint_tool::PaintToolFileIO::FILE_TYPES[] = {
 {L"JW Paint Tool (*.jwpt)", L"*.jwpt"}
};

void paint_tool::PaintToolFileIO::open() {

	// CoCreate the File Open Dialog object.
	IFileDialog *pfd = NULL;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
			// Set the options on the dialog.
			DWORD dwFlags;

			// Before setting, always get the options first in order not to override existing options.
			hr = pfd->GetOptions(&dwFlags);
			if (SUCCEEDED(hr))
			{
				// In this case, get shell items only for file system items.
				hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
				if (SUCCEEDED(hr))
				{
					// Set the file types to display only. Notice that, this is a 1-based array.
					hr = pfd->SetFileTypes(ARRAYSIZE(FILE_TYPES), FILE_TYPES);
					if (SUCCEEDED(hr))
					{
						// Set the selected file type index to Word Docs for this example.
						hr = pfd->SetFileTypeIndex(1);
						if (SUCCEEDED(hr))
						{
							// Set the default extension to be ".doc" file.
							hr = pfd->SetDefaultExtension(L"jwpt");
							if (SUCCEEDED(hr))
							{
								// Show the dialog
								hr = pfd->Show(NULL);
								if (SUCCEEDED(hr))
								{
									// Obtain the result, once the user clicks the 'Open' button.
									// The result is an IShellItem object.
									IShellItem *psiResult;
									hr = pfd->GetResult(&psiResult);
									if (SUCCEEDED(hr))
									{
										// We are just going to print out the name of the file for sample sake.
										/*PWSTR pszFilePath = NULL;
										hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
										if (SUCCEEDED(hr))
										{
											TaskDialog(NULL,
												NULL,
												L"CommonFileDialogApp",
												pszFilePath,
												NULL,
												TDCBF_OK_BUTTON,
												TD_INFORMATION_ICON,
												NULL);
											CoTaskMemFree(pszFilePath);
										}
										*/
										psiResult->Release();
									}
								}
							}
						}
					}
				}
		}
		pfd->Release();
	}
}
