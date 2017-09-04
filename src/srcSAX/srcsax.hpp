/**
 * @file srcsax.hpp
 *
 * @copyright Copyright (C) 2013-2014 srcML, LLC. (www.srcML.org)
 *
 * srcSAX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * srcSAX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef INCLUDED_SRCSAX_HPP
#define INCLUDED_SRCSAX_HPP

#include <srcsax_handler.hpp>

#include <libxml/parser.h>

/**
 * srcsax_context
 *
 * Context data structure passed between callbacks.
 */
struct srcsax_context {

    /** user provided data */
    void* data = nullptr;

    /** srcSAX handler callbacks */
    srcsax_handler* handler = nullptr;

    /** error callback need to figure this one out probably message and errorcode. or struct.  Might not need, but might be nice to avoid libxml2 stuff */
    void (*srcsax_error)(const char* message, int error_code);

    /** is the document an archive */
    int is_archive;

    /** the current unit count */
    int unit_count = 0;

    /** size of the srcml_element stack */
    size_t stack_size;

    /** stack of open srcML elements */
    const char** srcml_element_stack;

    /** the xml documents encoding */
    const char* encoding;

    /* Internal context handling NOT FOR PUBLIC USE */

    /** xml parser input buffer */
    xmlParserInputBufferPtr input = nullptr;

    /** boolean to indicate need to free input buffer */
    bool free_input = false;

    /** internally used libxml2 context */
    xmlParserCtxtPtr libxml2_context;

    /** indicate stop parser */
    bool terminate = false;
};

/* srcSAX context creation/open functions */
srcsax_context* srcsax_create_context_filename(const char* filename, const char* encoding);
srcsax_context* srcsax_create_context_memory(const char* buffer, size_t buffer_size, const char* encoding);
srcsax_context* srcsax_create_context_FILE(FILE* srcml_file, const char* encoding);
srcsax_context* srcsax_create_context_fd(int srcml_fd, const char* encoding);
srcsax_context* srcsax_create_context_io(void* srcml_context, int (*read_callback)(void* context, char* buffer, int len), int (*close_callback)(void* context), const char* encoding);
srcsax_context* srcsax_create_context_parser_input_buffer(xmlParserInputBufferPtr input);

/* srcSAX free function */
void srcsax_free_context(srcsax_context * context);

/* srcSAX parse function */
int srcsax_parse(srcsax_context * context);
int srcsax_parse_handler(srcsax_context* context, srcsax_handler* handler);

/* srcSAX terminate parse function */
void srcsax_stop_parser(srcsax_context* context);

#endif
