/**
 * @file Mode.cpp
 *
 * @copyright Copyright (C) 2014 SDML (www.srcML.org)
 *
 * This file is part of the srcML Toolkit.
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
 
#include "ModeStack.hpp"

/* Set of mode flags */
const srcMLState::MODE_TYPE ModeStack::MODE_STATEMENT                 (std::string("0000000000000000000000000000000000000000000000000000000000000001"));
const srcMLState::MODE_TYPE ModeStack::MODE_LIST                      (std::string("0000000000000000000000000000000000000000000000000000000000000010"));
const srcMLState::MODE_TYPE ModeStack::MODE_EXPECT                    (std::string("0000000000000000000000000000000000000000000000000000000000000100"));
const srcMLState::MODE_TYPE ModeStack::MODE_DETECT_COLON              (std::string("0000000000000000000000000000000000000000000000000000000000001000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TEMPLATE                  (std::string("0000000000000000000000000000000000000000000000000000000000010000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ARGUMENT                  (std::string("0000000000000000000000000000000000000000000000000000000000100000"));
const srcMLState::MODE_TYPE ModeStack::MODE_NAMESPACE                 (std::string("0000000000000000000000000000000000000000000000000000000001000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_PARAMETER                 (std::string("0000000000000000000000000000000000000000000000000000000010000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_EXPRESSION                (std::string("0000000000000000000000000000000000000000000000000000000100000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_CALL                      (std::string("0000000000000000000000000000000000000000000000000000001000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_CONDITION                 (std::string("0000000000000000000000000000000000000000000000000000010000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TOP                       (std::string("0000000000000000000000000000000000000000000000000000100000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_BLOCK                     (std::string("0000000000000000000000000000000000000000000000000001000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_INIT                      (std::string("0000000000000000000000000000000000000000000000000010000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FUNCTION_TAIL             (std::string("0000000000000000000000000000000000000000000000000100000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_PARSE_EOL                 (std::string("0000000000000000000000000000000000000000000000001000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_LOCAL                     (std::string("0000000000000000000000000000000000000000000000010000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_VARIABLE_NAME             (std::string("0000000000000000000000000000000000000000000000100000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_IF                        (std::string("0000000000000000000000000000000000000000000001000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TOP_SECTION               (std::string("0000000000000000000000000000000000000000000010000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FOR_CONTROL               (std::string("0000000000000000000000000000000000000000000100000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FOR_INITIALIZATION        (std::string("0000000000000000000000000000000000000000001000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FOR_CONDITION             (std::string("0000000000000000000000000000000000000000010000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FOR_INCREMENT             (std::string("0000000000000000000000000000000000000000100000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_PREPROC                   (std::string("0000000000000000000000000000000000000001000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_NEST                      (std::string("0000000000000000000000000000000000000010000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_EXPRESSION_BLOCK          (std::string("0000000000000000000000000000000000000100000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_INTERNAL_END_PAREN        (std::string("0000000000000000000000000000000000001000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ACCESS_REGION             (std::string("0000000000000000000000000000000000010000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_DO_STATEMENT              (std::string("0000000000000000000000000000000000100000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_IGNORE_TERMINATE          (std::string("0000000000000000000000000000000001000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_USING                     (std::string("0000000000000000000000000000000010000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_EXTERN                    (std::string("0000000000000000000000000000000100000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TRAILING_RETURN           (std::string("0000000000000000000000000000001000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_INTERNAL_END_CURLY        (std::string("0000000000000000000000000000010000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ISSUE_EMPTY_AT_POP        (std::string("0000000000000000000000000000100000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_INITIALIZATION_LIST       (std::string("0000000000000000000000000001000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_CLASS                     (std::string("0000000000000000000000000010000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_AT_ENDIF              (std::string("0000000000000000000000000100000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_AT_BLOCK              (std::string("0000000000000000000000001000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_ONLY_AT_RPAREN        (std::string("0000000000000000000000010000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_AT_BLOCK_NO_TERMINATE (std::string("0000000000000000000000100000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ARGUMENT_LIST             (std::string("0000000000000000000001000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ASSOCIATION_LIST          (std::string("0000000000000000000010000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FUNCTION_NAME             (std::string("0000000000000000000100000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ELSE                      (std::string("0000000000000000001000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TYPEDEF                   (std::string("0000000000000000010000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_DECL                      (std::string("0000000000000000100000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_EAT_TYPE                  (std::string("0000000000000001000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_FUNCTION_PARAMETER        (std::string("0000000000000010000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TERNARY                   (std::string("0000000000000100000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_OBJECTIVE_C_CALL          (std::string("0000000000001000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_INNER_DECL                (std::string("0000000000010000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_SWITCH                    (std::string("0000000000100000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TERNARY_CONDITION         (std::string("0000000001000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_THEN                      (std::string("0000000010000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_IN_INIT                   (std::string("0000000100000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TRY                       (std::string("0000001000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_LIST_AT_BLOCK         (std::string("0000010000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_TEMPLATE_PARAMETER_LIST   (std::string("0000100000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ONLY_END_TERMINATE        (std::string("0001000000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ENUM                      (std::string("0010000000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ANONYMOUS                 (std::string("0100000000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_END_AT_COMMA              (std::string("1000000000000000000000000000000000000000000000000000000000000000"));




// Modes greater than 64-bit
const srcMLState::MODE_TYPE ModeStack::MODE_RANGED_FOR               (std::string("10000000000000000000000000000000000000000000000000000000000000000"));
const srcMLState::MODE_TYPE ModeStack::MODE_ASSOCIATION_TYPE         (std::string("100000000000000000000000000000000000000000000000000000000000000000"));