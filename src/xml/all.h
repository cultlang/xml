
#pragma once

#include "xml/common.h"

namespace cultlang {
namespace pugixml
{
    
    CULTLANG_XML_EXPORTED extern craft::lisp::BuiltinModuleDescription BuiltinPugixml;
    CULTLANG_XML_EXPORTED void make_pugixml_bindings(craft::instance<craft::lisp::Module>);
}}

CRAFT_TYPE_DECLARE(CULTLANG_XML_EXPORTED, pugi::xml_document)
CRAFT_TYPE_DECLARE(CULTLANG_XML_EXPORTED, pugi::xml_node)
CRAFT_TYPE_DECLARE(CULTLANG_XML_EXPORTED, pugi::xml_attribute)
