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

	/* clear the current canvas to make way for the new drawings from file */

	canvas->removeAllComponents();

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;

	/* load characters into a vector char buffer */

	std::ifstream file(psz_file_name);

	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	buffer.push_back('\0');

	/* parse the buffer into the xml document */

	doc.parse<0>(&buffer[0]);
	
	/* the root node of a .jwpt file is <canvas/> */

	root_node = doc.first_node("canvas");

	/* iterate over each child drawing node and their point nodes */

	for (rapidxml::xml_node<> * drawing_node = root_node->first_node("drawing"); drawing_node; drawing_node = drawing_node->next_sibling()) {

		/* get the type of drawing */

		std::string drawing_type = drawing_node->first_attribute("type")->value();

		/* get the position of the drawing */

		POINT pos = {
			std::stoi(drawing_node->first_attribute("pos_x")->value()),
			std::stoi(drawing_node->first_attribute("pos_y")->value())
		};

		/* get the style of the drawing, first checking to see if the relevant
		   attribute exits. this check is needed as the attributes particular
		   drawing types have can differ (line drawings won't have the bg_col
		   attribute, for example) */

		std::unique_ptr<int> text_colour, bg_colour, line_colour, line_thickness;

		if (rapidxml::xml_attribute<char> *attribute = drawing_node->first_attribute("bg_col")) {

			/* convert the string hexadecimal value into an integer */

			int value;
			std::stringstream ss;
			ss << std::hex << attribute->value();
			ss >> value;

			bg_colour = std::make_unique<int>(value);
		}

		if (rapidxml::xml_attribute<char> *attribute = drawing_node->first_attribute("line_col")) {

			/* convert the string hexadecimal value into an integer */

			int value;
			std::stringstream ss;
			ss << std::hex << attribute->value();
			ss >> value;

			line_colour = std::make_unique<int>(value);
		}

		if (rapidxml::xml_attribute<char> *attribute = drawing_node->first_attribute("line_thickness"))
			line_thickness = std::make_unique<int>(std::stoi(attribute->value()));

		ComponentStyle::StyleSet style_set = {
			std::move(text_colour),
			std::move(bg_colour),
			std::move(line_colour),
			std::move(line_thickness)
		};

		/* get the points of the drawing */

		std::list<POINT *> points;

		for (rapidxml::xml_node<> * point_node = drawing_node->first_node("point"); point_node; point_node = point_node->next_sibling()) {

			POINT *point = new POINT {
				std::stoi(point_node->first_attribute("x")->value()),
				std::stoi(point_node->first_attribute("y")->value())
			};

			points.push_back(point);
		}

		/* call upon the drawing factory to build the drawing with the data we
		   have just processed */

		p_component_t drawing = DrawingFactory::getInstance()->makeDrawing(
			drawing_type,
			pos,
			style_set,
			points
		);

		/* load the drawing to the canvas */

		canvas->addComponent(drawing);
	}

	return 0;
}

HRESULT paint_tool::PaintToolFileIO::save(PCWSTR psz_file_name) {

	/* create the file handle we're going to write to */

	HANDLE h_file = CreateFileW(psz_file_name,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	/* perform a check to ensure handle creation went okay */

	HRESULT hr = (h_file == INVALID_HANDLE_VALUE) ? HRESULT_FROM_WIN32(GetLastError()) : S_OK;

	if (SUCCEEDED(hr)) {

		/* initialise our xml document */

		rapidxml::xml_document<> doc;

		/* create & insert the root canvas node */

		rapidxml::xml_node<> *canvas_node = makeNode(doc, "canvas");
		doc.append_node(canvas_node);

		/* iterate over the drawing components attached to the canvas and create
		   drawing nodes out of them */

		for (p_component_t &component : *canvas->getChildComponents()) {

			Drawing *drawing = dynamic_cast<Drawing *>(component.get());

			if (!drawing)
				continue;

			/* create the drawing node */

			rapidxml::xml_node<> *drawing_node = makeNode(doc, "drawing");

			/* compile component properties into node attributes */

			/* drawing type attribute */

			std::string type = "undefined";

			if (dynamic_cast<PolygonDrawing *>(component.get()))
				type = "polygon";

			else if (dynamic_cast<LineDrawing *>(component.get()))
				type = "line";

			rapidxml::xml_attribute<> *type_attribute = makeAttribute(doc, "type", type);
			drawing_node->append_attribute(type_attribute);

			/* drawing position attributes */

			POINT pos = component->getPosition();
			POINT origin = component->getOrigin();

			rapidxml::xml_attribute<> *pos_x_attribute = makeAttribute(
				doc, "pos_x", std::to_string(pos.x + origin.x)
			);
			drawing_node->append_attribute(pos_x_attribute);

			rapidxml::xml_attribute<> *pos_y_attribute = makeAttribute(
				doc, "pos_y", std::to_string(pos.y + origin.y)
			);
			drawing_node->append_attribute(pos_y_attribute);

			/* colour attributes - only add the attribute if the drawing has
			   the appropriate drawing property to support it */

			const ComponentStyle *style = component->getStyle();
			std::vector<DrawingProperties> drawing_props = drawing->getProperties();

			/* background colour */

			if (std::any_of(drawing_props.begin(), drawing_props.end(), 
				[](DrawingProperties property) {
					return property == DRAW_PROP_COL_FILL;
				}
			)) {

				/* convert the colour value into a 6 digit hexadecimal one */

				std::string value;
				std::stringstream ss;
				ss << std::hex << std::setw(6) << std::setfill('0') <<  *style->getBgColour();
				ss >> value;

				rapidxml::xml_attribute<> *bg_col_attribute = makeAttribute(
					doc, "bg_col", value
				);
				drawing_node->append_attribute(bg_col_attribute);
			}

			/* line colour */

			if (std::any_of(drawing_props.begin(), drawing_props.end(),
				[](DrawingProperties property) {
				return property == DRAW_PROP_COL_LINE;
			}
			)) {

				/* convert the colour value into a 6 digit hexadecimal one */

				std::string value;
				std::stringstream ss;
				ss << std::hex << std::setw(6) << std::setfill('0') << *style->getLineColour();
				ss >> value;

				rapidxml::xml_attribute<> *line_col_attribute = makeAttribute(
					doc, "line_col", value
				);
				drawing_node->append_attribute(line_col_attribute);
			}

			/* line thickness */

			if (std::any_of(drawing_props.begin(), drawing_props.end(),
				[](DrawingProperties property) {
				return property == DRAW_PROP_LINE_THICKNESS;
			}
			)) {

				rapidxml::xml_attribute<> *line_thickness_attribute = makeAttribute(
					doc, "line_thickness", std::to_string(*style->getLineThickness())
				);
				drawing_node->append_attribute(line_thickness_attribute);
			}

			/* iterate over each point that the drawing holds & create a point
			   node out of it */

			for (POINT *point : drawing->getPoints()) {

				/* create the point node */

				rapidxml::xml_node<> *point_node = makeNode(doc, "point");

				/* create the position attributes */

				rapidxml::xml_attribute<> *point_x_attribute = makeAttribute(
					doc, "x", std::to_string(point->x)
				);
				point_node->append_attribute(point_x_attribute);

				rapidxml::xml_attribute<> *point_y_attribute = makeAttribute(
					doc, "y", std::to_string(point->y)
				);
				point_node->append_attribute(point_y_attribute);

				drawing_node->append_node(point_node);
			}

			canvas_node->append_node(drawing_node);
		}

		/* write the document to the file */

		std::stringstream ss;
		ss << doc;
		ss.seekg(0, std::ios::end);
		DWORD bytes_written = 0;
		WriteFile(h_file, ss.str().c_str(), ss.tellg(), &bytes_written, NULL);
		CloseHandle(h_file);
	}

	return hr;
}

rapidxml::xml_node<> *paint_tool::PaintToolFileIO::makeNode(
			rapidxml::xml_document<>	&doc,
	const	std::string					&name
) {
	return doc.allocate_node(
		rapidxml::node_element,
		doc.allocate_string(name.c_str())
	);
}

rapidxml::xml_attribute<> *paint_tool::PaintToolFileIO::makeAttribute(
			rapidxml::xml_document<>	&doc,
	const	std::string					&key,
	const	std::string					&value
) {
	return doc.allocate_attribute(
		doc.allocate_string(key.c_str()),
		doc.allocate_string(value.c_str())
	);
}