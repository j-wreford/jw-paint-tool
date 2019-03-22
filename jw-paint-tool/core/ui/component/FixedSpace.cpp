#include "FixedSpace.h"

paint_tool::FixedSpace::FixedSpace(
	const	std::string	&id,
	const	SIZE		&size
) : StaticBox(id, POINT{ 0,0 }, size) {
	//
}

paint_tool::FixedSpace::~FixedSpace() {
	//
}