/**
 * @file test_UTF8CharBuffer.cpp
 * @copyright
 *
 * Copyright (C) 2013  SDML (www.srcML.org)
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
 */

/*
  Test cases for UTF8CharBuffer.
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include <UTF8CharBuffer.hpp>

int main() {

    std::ofstream file("a.cpp");
    file << "abc";
    file.close();

    file.open("iso.cpp");
    file << "/** ";
    file << (char)254;
    file << (char)255;
    file << " */";
    file.close();

    file.open("long.cpp");
    for(int i = 0; i < 4096; ++i)
	file << 'a';
    file.close();

  /*

    getChar()

   */

  {

    UTF8CharBuffer utf8("a.cpp", "UTF-8");
    assert(utf8.getChar() == 'a');
    assert(utf8.getChar() == 'b');
    assert(utf8.getChar() == 'c');

  }


  {

    UTF8CharBuffer utf8("abc", 3, "UTF-8");
    assert(utf8.getChar() == 'a');
    assert(utf8.getChar() == 'b');
    assert(utf8.getChar() == 'c');

  }


  {

    FILE * file = fopen("a.cpp", "r");
    UTF8CharBuffer utf8(file, "UTF-8");
    assert(utf8.getChar() == 'a');
    assert(utf8.getChar() == 'b');
    assert(utf8.getChar() == 'c');
    fclose(file);

  }

  {

    int fd = open("a.cpp", O_RDONLY);
    UTF8CharBuffer utf8(fd, "UTF-8");
    assert(utf8.getChar() == 'a');
    assert(utf8.getChar() == 'b');
    assert(utf8.getChar() == 'c');
    close(fd);

  }


  {
      unsigned char s[9];

      s[0] = '/';
      s[1] = '*';
      s[2] = '*';
      s[3] = ' ';
      s[4] = 254;
      s[5] = 255;
      s[6] = ' ';
      s[7] = '*';
      s[8] = '/';

    UTF8CharBuffer utf8((const char *)s, 9, "ISO-8859-1");
    assert(utf8.getChar() == '/');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == ' ');
    assert(utf8.getChar() == 195);
    assert(utf8.getChar() == 190);
    assert(utf8.getChar() == 195);
    assert(utf8.getChar() == 191);
    assert(utf8.getChar() == ' ');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == '/');
    

  }

  {

    UTF8CharBuffer utf8("iso.cpp", "ISO-8859-1");
    assert(utf8.getChar() == '/');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == ' ');
    assert(utf8.getChar() == 195);
    assert(utf8.getChar() == 190);
    assert(utf8.getChar() == 195);
    assert(utf8.getChar() == 191);
    assert(utf8.getChar() == ' ');
    assert(utf8.getChar() == '*');
    assert(utf8.getChar() == '/');
    

  }

  unlink("a.cpp");
  unlink("iso.cpp");
  unlink("long.cpp");

  return 0;
}
