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

	/* show the open dialog in order to know which file we're going to
	   process */

	HRESULT hr = showOpenDialog();

}

HRESULT paint_tool::PaintToolFileIO::showOpenDialog() {

	/* initialise the property which will be used to control the open dialog
	   with */

	IFileDialog *pfd = NULL;

	/* create the file open dialog using CoCreateInstance. from looking at docs,
	   this function is used to instantiate only one object. so perhaps, a
	   singleton-like pattern? not too sure */

	HRESULT hr = ::CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
	
	if (SUCCEEDED(hr)) {

		/* set the options on the dialog. this seems like boilerplate code to
		   show files that are on the file system */

		DWORD dwFlags;
		hr = pfd->GetOptions(&dwFlags);

		if (SUCCEEDED(hr)) {

			hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);

			if (SUCCEEDED(hr)) {

				/* inform the dialog that we're only interested in files that the
				   FILE_TYPES static property holds. this will only ever be
				   .jwpt files for this application */

				hr = pfd->SetFileTypes(ARRAYSIZE(FILE_TYPES), FILE_TYPES);

				if (SUCCEEDED(hr)) {

					/* the file types index begins at 1, and we only have one
					   entry within it. call SetFilTypeIndex to set it to our
					   custom file format (.jwpt) */

					hr = pfd->SetFileTypeIndex(1);

					if (SUCCEEDED(hr)) {

						hr = pfd->SetDefaultExtension(L"jwpt");

						if (SUCCEEDED(hr)) {

							/* show the open dialog! */

							hr = pfd->Show(NULL);
							
							if (SUCCEEDED(hr)) {
								
								/* as a guess, this body of code is only reached
								   once the open file dialog exits somehow
								   (either through the cross button, cancel, or
								   hopefully the open button) */

								/* attempt to fetch the result of the open file
								   dialog */
								
								IShellItem *psiResult;
								hr = pfd->GetResult(&psiResult);

								if (SUCCEEDED(hr)) {

									/* there was a result, and we now have
									   access to the information we need to 
									   begin processing the selected .jwpt 
									   file */

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

	return hr;
}
