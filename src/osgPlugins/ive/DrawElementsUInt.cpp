/**********************************************************************
 *
 *	FILE:			DrawElementsUInt.cpp
 *
 *	DESCRIPTION:	Read/Write osg::DrawElementsUInt in binary format to disk.
 *
 *	CREATED BY:		Copied from DrawElementsUShort.cpp by Marco Jez
 *					
 *
 *	HISTORY:		Created 20.3.2003
 *
 *	Copyright 2003 VR-C
 **********************************************************************/

#include "Exception.h"
#include "DrawElementsUInt.h"
#include "PrimitiveSet.h"

using namespace ive;

void DrawElementsUInt::write(DataOutputStream* out){
	// Write DrawElementsUInt's identification.
	out->writeInt(IVEDRAWELEMENTSUINT);

	// If the osg class is inherited by any other class we should also write this to file.
	osg::PrimitiveSet*  prim = dynamic_cast<osg::PrimitiveSet*>(this);
	if(prim){
		((ive::PrimitiveSet*)(prim))->write(out);
	}
	else
		throw Exception("DrawElementsUInt::write(): Could not cast this osg::DrawElementsUInt to an osg::PrimitiveSet.");
	// Write DrawElementsUInt's properties.

	// Write array length and its elements.
	out->writeInt(size());
	for(unsigned int i=0; i<size(); i++){
		out->writeUInt((*this)[i]);
	}
}

void DrawElementsUInt::read(DataInputStream* in){
	// Read DrawElementsUInt's identification.
	int id = in->peekInt();
	if(id == IVEDRAWELEMENTSUINT){
		// Code to read DrawElementsUInt's properties.
		id = in->readInt();
		// If the osg class is inherited by any other class we should also read this from file.
		osg::PrimitiveSet*  prim = dynamic_cast<osg::PrimitiveSet*>(this);
		if(prim){
			((ive::PrimitiveSet*)(prim))->read(in);
		}
		else
			throw Exception("DrawElementsUInt::read(): Could not cast this osg::DrawElementsUInt to an osg::PrimtiveSet.");

		// Read array length and its elements.
		int size = in->readInt();
		for(int i=0; i<size; i++){
			push_back(in->readUInt());
		}
	}
	else{
		throw Exception("DrawElementsUInt::read(): Expected DrawElementsUInt identification.");
	}
}
