
#pragma once

#include "pugixml/common.h"

namespace cultlang {
namespace pugixml
{
    
    CULTLANG_PUGIXML_EXPORTED extern craft::lisp::BuiltinModuleDescription BuiltinPugixml;
    CULTLANG_PUGIXML_EXPORTED void make_pugixml_bindings(craft::instance<craft::lisp::Module>);
}}

CRAFT_TYPE_DECLARE(CULTLANG_PUGIXML_EXPORTED, pugi::xml_document)
CRAFT_TYPE_DECLARE(CULTLANG_PUGIXML_EXPORTED, pugi::xml_node)
CRAFT_TYPE_DECLARE(CULTLANG_PUGIXML_EXPORTED, pugi::xml_node_iterator)
CRAFT_TYPE_DECLARE(CULTLANG_PUGIXML_EXPORTED, pugi::xml_attribute)
CRAFT_TYPE_DECLARE(CULTLANG_PUGIXML_EXPORTED, pugi::xml_attribute_iterator)