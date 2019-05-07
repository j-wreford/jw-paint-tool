#include "PaintToolFileIO.h"

paint_tool::PaintToolFileIO::PaintToolFileIO() :
	canvas(nullptr) {
	//
}

paint_tool::PaintToolFileIO::~PaintToolFileIO() {
	//
}

const COMDLG_FILTERSPEC paint_tool::PaintToolFileIO::FILE_TYPES[] = {
 {L"JW Paint Tool (*.jwpt)", L"*.jwpt"}
};

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

									/* get the path of the file */

									PWSTR psz_new_file_name;
									hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &psz_new_file_name);

									if (SUCCEEDED(hr)) {

										/* open the file! */

										open(psz_new_file_name);

									}

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

HRESULT paint_tool::PaintToolFileIO::showSaveDialog() {

	/* initialise the property which will be used to control the save dialog
	   with */

	IFileDialog *pfd = NULL;

	/* create the file save dialog */

	HRESULT hr = ::CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

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

							/* show the save dialog! */

							hr = pfd->Show(NULL);

							if (SUCCEEDED(hr)) {

								IShellItem *psiResult;
								hr = pfd->GetResult(&psiResult);

								if (SUCCEEDED(hr)) {

									/* there was a result, and we now have
									   access to the information we need to
									   begin writing data to the intended .jpwt
									   file */

									/* get the path of the file */

									PWSTR psz_new_file_name;
									hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &psz_new_file_name);

									if (SUCCEEDED(hr)) {

										/* save the file! */

										save(psz_new_file_name);

										CoTaskMemFree(psz_new_file_name);
									}

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

HRESULT paint_tool::PaintToolFileIO::open(PCWSTR psz_file_name) {
	return 0;
}

HRESULT paint_tool::PaintToolFileIO::save(PCWSTR psz_file_name) {

	/* create the file we're going to write to */

	HANDLE h_file = CreateFileW(psz_file_name,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	/* perform a check to ensure file creation went okay */

	HRESULT hr = (h_file == INVALID_HANDLE_VALUE) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;

	if (SUCCEEDED(hr)) {

		/* loop through the list of components attached to the canvas & write
		   data depending on the properties of the drawing */

		for (p_component_t &component : *canvas->getChildComponents()) {

			if (Drawing *drawing = dynamic_cast<Drawing *>(component.get())) {

				std::string type = "undefined";

				if (dynamic_cast<PolygonDrawing *>(component.get()))
					type = "polygon";

				else if (dynamic_cast<LineDrawing *>(component.get()))
					type = "line";

				const ComponentStyle *style = component->getStyle();

				std::stringstream ss;
				ss << std::setfill('0');

				ss << "<drawing ";
				ss << "type=\"" << type << "\" ";
				ss << "pos_x=\"" << component->getPosition().x << "\" ";
				ss << "pos_y=\"" << component->getPosition().y << "\" ";
				ss << "bg_col=\"" << std::hex << std::setw(6) << *style->getBgColour() << "\" ";
				ss << "line_col=\"" << std::hex << std::setw(6) << *style->getLineColour() << "\" ";
				ss << "line_thickness=\"" << *style->getLineThickness() << "\"";
				ss << ">" << std::endl;

				for (POINT *point : drawing->getPoints()) {

					std::stringstream pt_ss;

					pt_ss << '\t' << "<point ";;
					pt_ss << "x=\"" << point->x << "\" ";
					pt_ss << "y=\"" << point->y << "\"";
					pt_ss << "/>" << std::endl;

					ss << pt_ss.str();
				}

				ss << "</drawing>" << std::endl;

				ss.seekg(0, std::ios::end);

				DWORD dwBytesWritten = 0;
				hr = WriteFile(h_file, ss.str().c_str(), ss.tellg(), &dwBytesWritten, NULL);
			}
		}

		CloseHandle(h_file);
	}

	return hr;
}