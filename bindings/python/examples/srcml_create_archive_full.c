*
 * @file srcml_create_archive_full.c
 *
 * @copyright Copyright (C) 2013-2014 SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 


  Example program of the use of the C API for srcML.

  Create an archive, file by file, with an output filename, showing
  most of the option features

import srcml

if __name__ == "__main__":
    int i;
    struct srcml_archive* archive;

    
      Setup archive
    

     create a new srcml archive structure 
    archive = srcml_create_archive();

     setup options and attributes 
    srcml_archive_enable_option(archive, SRCML_OPTION_LITERAL | SRCML_OPTION_MODIFIER | SRCML_OPTION_POSITION);
    srcml_archive_set_version(archive, "211");
    srcml_archive_set_tabstop(archive, 4);

     treat "*.h" as C++ 
    srcml_archive_register_file_extension(archive, "h", SRCML_LANGUAGE_CXX);

     change prefix of standard namespace 
    srcml_archive_register_namespace(archive, "s", "http://www.sdml.info/srcML/src");

    /* default prefix is now for cpp namespace */
    srcml_archive_register_namespace(archive, "", "http://www.sdml.info/srcML/cpp");

    /* new prefix for further processing */
    srcml_archive_register_namespace(archive, "doc", "http://www.sdml.info/srcML/doc");

    /*
      Open and write to the archive
    */

    /* open a srcML archive for output */
    srcml_write_open_filename(archive, "project.xml");

    /* add all files on the command line to the archive */
    for (i = 1; i < argc; ++i) {

         Setup this entry 
        struct srcml_unit* unit = srcml_create_unit(archive);
        srcml_unit_set_language(unit, SRCML_LANGUAGE_C);
        srcml_unit_set_filename(unit, argv[i]);

         Translate the entry to srcML 
        srcml_parse_unit_filename(unit, argv[i]);

         Append unit to the archive 
        srcml_write_unit(archive, unit);

         Done with the entry for now 
        srcml_free_unit(unit);
    }

    
      Finish up
    

     close the srcML archive 
    srcml_close_archive(archive);

     free the srcML archive data 
    srcml_free_archive(archive);

