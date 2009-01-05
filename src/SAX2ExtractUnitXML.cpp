/*
  srcMLUtility.cpp

  Copyright (C) 2004-2006  SDML (www.sdml.info)

  This file is part of the srcML translator.

  The srcML translator is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  The srcML translator is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the srcML translator; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


*/

#include "SAX2TextWriter.h"
#include "SAX2ExtractUnitXML.h"
#include "SAX2Utilities.h"

#include <iostream>
#include <cstring>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include "Options.h"
#include "srcmlns.h"

/* srcML unit attributes */
const char* const UNIT_ATTRIBUTE_LANGUAGE = "language";
const char* const UNIT_ATTRIBUTE_DIRECTORY = "dir";
const char* const UNIT_ATTRIBUTE_FILENAME = "filename";
const char* const UNIT_ATTRIBUTE_VERSION = "version";

namespace SAX2ExtractUnitXML {

  static int placescount = 0;
  static int placesunit = 0;

  xmlSAXHandler factory() {

    xmlSAXHandler sax = { 0 };

    sax.initialized    = XML_SAX2_MAGIC;
    sax.startElementNs = &startElementNsRoot;
    sax.startDocument  = &SAX2TextWriter::startDocument;

    return sax;
  }

  // handle root unit of compound document
  void startElementNsRoot(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI,
		    int nb_namespaces, const xmlChar** namespaces, int nb_attributes, int nb_defaulted,
		    const xmlChar** attributes) {

    State* pstate = (State*) ctx;

    // start counting units after the root
    pstate->count = 0;

    // collect namespaces
    collect_namespaces(nb_namespaces, namespaces, *(pstate->nsv));

    // collect attributes
    collect_attributes(nb_attributes, attributes, *(pstate->attrv));

    // handle nested units
    pstate->ctxt->sax->startElementNs = pstate->unit == 1 ? &startElementNsUnit : 0;
    pstate->ctxt->sax->endElementNs   = pstate->unit == 1 ? 0 : &endElementNs;

    placescount = 1;
    placesunit = 10;

    // output file status message if in verbose mode
    if (isoption(*(pstate->poptions), OPTION_VERBOSE))
      std::cerr << "Count:  ";
  }

  // start a new output buffer and corresponding file for a
  // unit element
  void startElementNsUnit(void* ctx, const xmlChar* localname, const xmlChar* prefix, const xmlChar* URI,
		    int nb_namespaces, const xmlChar** namespaces, int nb_attributes, int nb_defaulted,
		    const xmlChar** attributes) {

    State* pstate = (State*) ctx;

    // mostly we count the end elements for units, but now count the start
    ++(pstate->count);

    // start element with proper prefix
    const char* name = qname((const char*) prefix, (const char*) localname);
    xmlTextWriterStartElement(pstate->writer, BAD_CAST name);

    // merge this units namespaces
    collect_namespaces(nb_namespaces, namespaces, *(pstate->nsv));

    // output the merged namespaces
    for (PROPERTIES_TYPE::const_iterator iter = pstate->nsv->begin(); iter != pstate->nsv->end(); ++iter)
      xmlTextWriterWriteAttribute(pstate->writer, BAD_CAST iter->second.c_str(), BAD_CAST iter->first.c_str());

    // merge this units attributes
    collect_attributes(nb_attributes, attributes, *(pstate->attrv));

    // output the merged attributes
    for (PROPERTIES_TYPE::const_iterator iter = pstate->attrv->begin(); iter != pstate->attrv->end(); iter++)
      xmlTextWriterWriteAttribute(pstate->writer, BAD_CAST iter->first.c_str(), BAD_CAST iter->second.c_str());

    // now really start
    pstate->ctxt->sax->endDocument    = &SAX2TextWriter::endDocument;
    pstate->ctxt->sax->startElementNs = &SAX2TextWriter::startElementNs;
    pstate->ctxt->sax->endElementNs   = &SAX2TextWriter::endElementNs;
    pstate->ctxt->sax->characters     = &SAX2TextWriter::characters;
  }

  // end unit element and current file/buffer (started by startElementNs
  void endElementNs(void *ctx, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI) {

    State* pstate = (State*) ctx;

    if (pstate->ctxt->nameNr != 2)
      return;

    ++(pstate->count);

    // output file status message if in verbose mode
    if (isoption(*(pstate->poptions), OPTION_VERBOSE)) {
      for (int i = 0; i < placescount; ++i)
	std::cerr << '\b';
      std::cerr << pstate->count;

      if (pstate->count == placesunit) {
	placesunit *= 10;
	++placescount;
      }
    }

    if (pstate->count < pstate->unit - 1)
      return;

    // now ready for the next unit, to treat as root
    pstate->ctxt->sax->startElementNs = &startElementNsUnit;
    pstate->ctxt->sax->endElementNs = 0;
  }
};
